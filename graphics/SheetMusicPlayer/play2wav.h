
// PLAY2WAV
// Original file: play2wav.c
// By Alexey Frunze
// https://stackoverflow.com/questions/11355353/how-can-i-convert-qbasic-play-commands-to-something-more-contemporary
//
// Example: (Jingle Bells)
//
// t200l4o2mneel2el4eel2el4egl3cl8dl1el4ffl3fl8fl4fel2el8eel4edde
// l2dgl4eel2el4eel2el4egl3cl8dl1el4ffl3fl8fl4fel2el8efl4ggfdl2c

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358
#endif

enum STATE
{
	StateParsing,
	StateGenerating,
};

enum MODE
{
	ModeNormal,
	ModeLegato,
	ModeStaccato,
};

double Note2Freq(int Note) // Note=1 = C1 (32.7032 Hz), Note=84 = B7 (3951.07 Hz)
{
	double f = 0;
	if (Note > 0)
		f = 440 * exp(log(2) * (Note - 46) / 12);
	return f;
}

int Name2SemitonesFromC(char c)
{
	static const int semitonesFromC[7] = { 9, 11, 0, 2, 4, 5, 7 }; // A,B,C,D,E,F,G
	if (c < 'A' && c > 'G') return -1;
	return semitonesFromC[c - 'A'];
}

typedef struct tPlayer
{
	STATE State;

	int Tempo;
	int Duration;
	int Octave;
	MODE Mode;

	int Note;
	double NoteDuration;
	double NoteTime;
	unsigned SampleRate;
} tPlayer;

void PlayerInit(tPlayer* pPlayer, unsigned SampleRate)
{
	pPlayer->State = StateParsing;
	pPlayer->Tempo = 120; // [32,255] quarter notes per minute
	pPlayer->Duration = 4; // [1,64]
	pPlayer->Octave = 4; // [0,6]
	pPlayer->Mode = ModeNormal;
	pPlayer->Note = 0;
	pPlayer->SampleRate = SampleRate;
}

int PlayerGetSample(tPlayer* pPlayer, const char** ppMusicString, short* pSample)
{
	int number;
	int note = 0;
	int duration = 0;
	int dotCnt = 0;
	double sample;
	double freq;

	*pSample = 0;

	while (pPlayer->State == StateParsing)
	{
		char c = **ppMusicString;

		if (c == '\0') return 0;

		++*ppMusicString;

		if (isspace(c)) continue;

		c = toupper(c);

		switch (c)
		{
		case 'O':
			c = **ppMusicString;
			if (c < '0' || c > '6') return 0;
			pPlayer->Octave = c - '0';
			++*ppMusicString;
			break;

		case '<':
			if (pPlayer->Octave > 0) pPlayer->Octave--;
			break;

		case '>':
			if (pPlayer->Octave < 6) pPlayer->Octave++;
			break;

		case 'M':
			c = toupper(**ppMusicString);
			switch (c)
			{
			case 'L':
				pPlayer->Mode = ModeLegato;
				break;
			case 'N':
				pPlayer->Mode = ModeNormal;
				break;
			case 'S':
				pPlayer->Mode = ModeStaccato;
				break;
			case 'B':
			case 'F':
				// skip MB and MF
				break;
			default:
				return 0;
			}
			++*ppMusicString;
			break; // ML/MN/MS, MB/MF

		case 'L':
		case 'T':
			number = 0;
			for (;;)
			{
				char c2 = **ppMusicString;
				if (isdigit(c2))
				{
					number = number * 10 + c2 - '0';
					++*ppMusicString;
				}
				else break;
			}
			switch (c)
			{
			case 'L':
				if (number < 1 || number > 64) return 0;
				pPlayer->Duration = number;
				break;
			case 'T':
				if (number < 32 || number > 255) return 0;
				pPlayer->Tempo = number;
				break;
			}
			break; // Ln/Tn

		case 'A': case 'B': case 'C': case 'D':
		case 'E': case 'F': case 'G':
		case 'N':
		case 'P':
			switch (c)
			{
			case 'A': case 'B': case 'C': case 'D':
			case 'E': case 'F': case 'G':
				note = 1 + pPlayer->Octave * 12 + Name2SemitonesFromC(c);
				break; // A...G
			case 'P':
				note = 0;
				break; // P
			case 'N':
				number = 0;
				for (;;)
				{
					char c2 = **ppMusicString;
					if (isdigit(c2))
					{
						number = number * 10 + c2 - '0';
						++*ppMusicString;
					}
					else break;
				}
				if (number < 0 || number > 84) return 0;
				note = number;
				break; // N
			} // got note #

			if (c >= 'A' && c <= 'G')
			{
				char c2 = **ppMusicString;
				if (c2 == '+' || c2 == '#')
				{
					if (note < 84) note++;
					++*ppMusicString;
				}
				else if (c2 == '-')
				{
					if (note > 1) note--;
					++*ppMusicString;
				}
			} // applied sharps and flats

			duration = pPlayer->Duration;

			if (c != 'N')
			{
				number = 0;
				for (;;)
				{
					char c2 = **ppMusicString;
					if (isdigit(c2))
					{
						number = number * 10 + c2 - '0';
						++*ppMusicString;
					}
					else break;
				}
				if (number < 0 || number > 64) return 0;
				if (number > 0) duration = number;
			} // got note duration

			while (**ppMusicString == '.')
			{
				dotCnt++;
				++*ppMusicString;
			} // got dots

			pPlayer->Note = note;
			pPlayer->NoteDuration = 1.0 / duration;
			while (dotCnt--)
			{
				duration *= 2;
				pPlayer->NoteDuration += 1.0 / duration;
			}
			pPlayer->NoteDuration *= 60 * 4. / pPlayer->Tempo; // in seconds now
			pPlayer->NoteTime = 0;

			pPlayer->State = StateGenerating;
			break; // A...G/N/P

		default:
			return 0;
		} // switch (c)
	}

	// pPlayer->State == StateGenerating
	// Calculate the next sample for the current note

	sample = 0;

	// QuickBasic Play() frequencies appear to be 1 octave higher than
	// on the piano.
	freq = Note2Freq(pPlayer->Note) * 2;

	if (freq > 0)
	{
		double f = freq;

		while (f < pPlayer->SampleRate / 2 && f < 8000) // Cap max frequency at 8 KHz
		{
			sample += exp(-0.125 * f / freq) * sin(2 * M_PI * f * pPlayer->NoteTime);
			f += 2 * freq; // Use only odd harmonics
		}

		sample *= 15000;
		sample *= exp(-pPlayer->NoteTime / 0.5); // Slow decay
	}

	if ((pPlayer->Mode == ModeNormal && pPlayer->NoteTime >= pPlayer->NoteDuration * 7 / 8) ||
		(pPlayer->Mode == ModeStaccato && pPlayer->NoteTime >= pPlayer->NoteDuration * 3 / 4))
		sample = 0;

	if (sample > 32767) sample = 32767;
	if (sample < -32767) sample = -32767;

	*pSample = (short)sample;

	pPlayer->NoteTime += 1.0 / pPlayer->SampleRate;

	if (pPlayer->NoteTime >= pPlayer->NoteDuration)
		pPlayer->State = StateParsing;

	return 1;
}

int PlayToFile(const char* pFileInName, const char* pFileOutName, unsigned int SampleRate)
{
	int err = EXIT_FAILURE;
	FILE *fileIn = NULL, *fileOut = NULL;
	tPlayer player;
	short sample;
	char* pMusicString = NULL;
	const char* p;
	size_t sz = 1, len = 0;
	char c;
	unsigned char uc;
	unsigned long sampleCnt = 0, us;

	if ((fileIn = fopen(pFileInName, "rb")) == NULL)
	{
		fprintf(stderr, "can't open file \"%s\"\n", pFileInName);
		goto End;
	}

	if ((fileOut = fopen(pFileOutName, "wb")) == NULL)
	{
		fprintf(stderr, "can't create file \"%s\"\n", pFileOutName);
		goto End;
	}

	if ((pMusicString = (char*)malloc(sz)) == NULL)
	{
	NoMemory:
		fprintf(stderr, "can't allocate memory\n");
		goto End;
	}

	// Load the input file into pMusicString[]

	while (fread(&c, 1, 1, fileIn))
	{
		pMusicString[len++] = c;

		if (len == sz)
		{
			char* p;

			sz *= 2;
			if (sz < len)
				goto NoMemory;

			p = (char*)realloc(pMusicString, sz);
			if (p == NULL)
				goto NoMemory;

			pMusicString = p;
		}
	}

	pMusicString[len] = '\0'; // Make pMusicString[] an ASCIIZ string

	// First, a dry run to simply count samples (needed for the WAV header)

	PlayerInit(&player, SampleRate);
	p = pMusicString;
	while (PlayerGetSample(&player, &p, &sample))
		sampleCnt++;

	if (p != pMusicString + len)
	{
		fprintf(stderr,
			"Parsing error near byte %u: \"%c%c%c\"\n",
			(unsigned)(p - pMusicString),
			(p > pMusicString) ? p[-1] : ' ',
			p[0],
			(p - pMusicString + 1 < len) ? p[1] : ' ');
		goto End;
	}

	// Write the output file

	// ChunkID
	fwrite("RIFF", 1, 4, fileOut);

	// ChunkSize
	us = 36 + 2 * sampleCnt;
	uc = us % 256;
	fwrite(&uc, 1, 1, fileOut);
	uc = us / 256 % 256;
	fwrite(&uc, 1, 1, fileOut);
	uc = us / 256 / 256 % 256;
	fwrite(&uc, 1, 1, fileOut);
	uc = us / 256 / 256 / 256 % 256;
	fwrite(&uc, 1, 1, fileOut);

	// Format + Subchunk1ID
	fwrite("WAVEfmt ", 1, 8, fileOut);

	// Subchunk1Size
	uc = 16;
	fwrite(&uc, 1, 1, fileOut);
	uc = 0;
	fwrite(&uc, 1, 1, fileOut);
	fwrite(&uc, 1, 1, fileOut);
	fwrite(&uc, 1, 1, fileOut);

	// AudioFormat
	uc = 1;
	fwrite(&uc, 1, 1, fileOut);
	uc = 0;
	fwrite(&uc, 1, 1, fileOut);

	// NumChannels
	uc = 1;
	fwrite(&uc, 1, 1, fileOut);
	uc = 0;
	fwrite(&uc, 1, 1, fileOut);

	// SampleRate
	uc = SampleRate % 256;
	fwrite(&uc, 1, 1, fileOut);
	uc = SampleRate / 256 % 256;
	fwrite(&uc, 1, 1, fileOut);
	uc = 0;
	fwrite(&uc, 1, 1, fileOut);
	fwrite(&uc, 1, 1, fileOut);

	// ByteRate
	us = (unsigned long)SampleRate * 2;
	uc = us % 256;
	fwrite(&uc, 1, 1, fileOut);
	uc = us / 256 % 256;
	fwrite(&uc, 1, 1, fileOut);
	uc = us / 256 / 256 % 256;
	fwrite(&uc, 1, 1, fileOut);
	uc = us / 256 / 256 / 256 % 256;
	fwrite(&uc, 1, 1, fileOut);

	// BlockAlign
	uc = 2;
	fwrite(&uc, 1, 1, fileOut);
	uc = 0;
	fwrite(&uc, 1, 1, fileOut);

	// BitsPerSample
	uc = 16;
	fwrite(&uc, 1, 1, fileOut);
	uc = 0;
	fwrite(&uc, 1, 1, fileOut);

	// Subchunk2ID
	fwrite("data", 1, 4, fileOut);

	// Subchunk2Size
	us = sampleCnt * 2;
	uc = us % 256;
	fwrite(&uc, 1, 1, fileOut);
	uc = us / 256 % 256;
	fwrite(&uc, 1, 1, fileOut);
	uc = us / 256 / 256 % 256;
	fwrite(&uc, 1, 1, fileOut);
	uc = us / 256 / 256 / 256 % 256;
	fwrite(&uc, 1, 1, fileOut);

	// Data
	PlayerInit(&player, SampleRate);
	p = pMusicString;
	while (PlayerGetSample(&player, &p, &sample))
	{
		uc = (unsigned)sample % 256;
		fwrite(&uc, 1, 1, fileOut);
		uc = (unsigned)sample / 256 % 256;
		fwrite(&uc, 1, 1, fileOut);
	}

	err = EXIT_SUCCESS;

End:

	if (pMusicString != NULL) free(pMusicString);
	if (fileOut != NULL) fclose(fileOut);
	if (fileIn != NULL) fclose(fileIn);

	return err;
}

/*
// Example main

int main(int argc, char** argv)
{
	if (argc == 3)
		//    return PlayToFile(argv[1], argv[2], 44100); // Use this for 44100 sample rate
		return PlayToFile(argv[1], argv[2], 16000);

	printf("Usage:\n  play2wav <Input-QBASIC-Play-String-file> <Output-Wav-file>\n");
	

	PlayToFile("creep.txt", "test.wav", 16000);

	return EXIT_FAILURE;
}
*/