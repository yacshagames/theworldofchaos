/******************************************************************
SHEET MUSIC PLAYER

Allows you to read a score from a txt file with the format of
the QBASIC play function, and then allows you to play the melody
on the computer speaker using the beep function, or also allows
you to export the melody to WAV using the play2wav library
by Alexey Frunze

The recognized sheet music format corresponds to the old format of
the QBASIC PLAY function. Since it is an easy format for the
user to learn

SHEET MUSIC FORMAT

https://www.qbasic.net/en/reference/qb11/Statement/PLAY-006.htm
SoundPlayDataString:	A string expression that contains one or more of the following PLAY commands :
Octave and tone commands :
Ooctave    Sets the current octave(0 - 6).
< or >     Moves up or down one octave.
A - G      Plays the specified note in the current octave.
Nnote      Plays a specified note(0 - 84) in the seven - octave
			range(0 is a rest).

Duration and tempo commands :
Llength    Sets the length of each note(1 - 64).L1 is whole note,
L2 is a half note, etc.
ML         Sets music legato.
MN         Sets music normal.
MS         Sets music staccato.
Ppause     Specifies a pause(1 - 64).P1 is a whole - note pause,
P2 is a half - note pause, etc.
Ttempo     Sets the tempo in quarter notes per minute(32 - 255).

Mode commands :
MF          Plays music in foreground.
MB          Plays music in background.

Suffix commands :
# or + Turns preceding note into a sharp.
- Turns preceding note into a flat.
. Plays the preceding note 3 / 2 as long as specified.

EXAMPLE (Creep Radiohead - sheet music encoded by Yacsha)
"O4 AGF+G.  F+F+ L5AGG L4 F+.  AAGF+GEDC P10"
"AAGF+G.. DC<B BB>AGF+F+.. P10 L5GAGL4A+.F..  GAGGA+.G.. P10"
"GBB.. GBB.F+.ED+.. P10 B>C<BAB.. GAGA+.G.. P10"
"EG... AGF+.ED+.F+B.AGF+.. P15"
"L2G. L4 AGF+..E.D+... L2F L2G L2A L1A L4 G.. F+.. G L1F+ P5"
"L2A L3G.. L4F+.. G L2G

Developed by:

	JOSE LUIS DE LA CRUZ LAZARO
	ramondc@hotmail.com

	UNIVERSIDAD NACIONAL DE INGENIERIA
	Faculty of Electrical and Electronic Engineering
	Lima-Peru

	YACSHA - Software & Desing
	>> The World of chaos - EL MUNDO DEL CAOS - Unlimited Programming

------------------------------------------------------------
Thanks to Alexey Frunze for creating the play2wav library,
which is used to convert the melody into a .wav file
------------------------------------------------------------

HISTORY...

  >> Version 2 - 06-IV-2024
	- Allows you to read a score from a txt file with the format of
	  the QBASIC play function, and then allows you to play the	  
	  melody on the computer speaker using the beep function, or
	  also allows you to export the melody to WAV using the
	  play2wav library by Alexey Frunze

  >> Version 1 - 17-VII-2000
	- Based in graphics\tecladmu (Musical KEYBOARD).
	  This remained an unfinished project.

******************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <cctype>  // std::isdigit
#include <algorithm>
#include "play2wav.h"
#include "graphics.h"
#include "conio.h"

using namespace std;

class CSheetMusicPlayer {

public:
	CSheetMusicPlayer(string _soundPlayDataString);

	// Sheet Music "QBASIC PLAY" parser
	bool decode(unsigned int& positionError);

	void playNote( unsigned int note, unsigned int currentDuration );

	// Draw procedures
	void DrawKey(int accion, int octava, int nota);
	static void DrawKeyboard();

public:
	int Octave;
	unsigned int Tempo;
	unsigned int Duration;
	string soundPlayDataString;
};



CSheetMusicPlayer::CSheetMusicPlayer(string _soundPlayDataString)
{
	soundPlayDataString = _soundPlayDataString;

	// To uppercase
	std::transform(soundPlayDataString.begin(), soundPlayDataString.end(), soundPlayDataString.begin(), ::toupper);

	Octave = 4;
	Tempo = 120;
	Duration = 4;
}

bool CSheetMusicPlayer::decode(unsigned int& positionError)
{
	// Sheet Music "QBASIC PLAY" parser

	unsigned int i, size = static_cast<unsigned int>(soundPlayDataString.size());

	for (i = 0; i < size; i++) {
		const char& code = soundPlayDataString.at(i);

		unsigned int note = 0, dot=0, silence = 0;

		switch (code) {
		case 'O': {
			const unsigned int& octave = static_cast<unsigned int>(soundPlayDataString.at(++i)) - '0';

			if (octave < 0 || octave > 6) {
				positionError = i - 1;
				return false;
			}

			Octave = octave;
			continue;
		}
			break;

		case '>': {			
			Octave++;
			continue;
		}
		break;
		case '<': {
			Octave--;
			continue;
		}
		break;
		case 'P':
		case 'L':
		case 'T':
		{
			unsigned int number = 0;			
			while(true)
			{
				char digit = soundPlayDataString.at(i+1);
				if ( std::isdigit(digit))
				{
					number = number * 10 + digit - '0';	
					i++;
				}
				else break;
			}

			unsigned int numberMax = code == 'T' ? 255 : 64;
			unsigned int numberMin = code == 'T' ? 32 : 1;

			if (number < numberMin || number > numberMax) {
				positionError = i - 1;
				return false;
			}

			if (code == 'P')
				silence = number;
			else if( code=='L' ){
				Duration = number;
				continue;
			}
			else {
				Tempo = number;
				continue;
			}
		}
			break;		
			// Music notes
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		{

			if( code <'C' )
				note = (code - 'A'+5) * 2;
			else
				note = ( code - 'C' ) * 2;

			if (i < size - 1) {
				//case 'N':
				//case 'P':
				char nextCode = soundPlayDataString.at(i + 1);

				switch (nextCode) {
				case '#':
				case '+':
					note = note == 13 ? 0 : note + 1;
					i++;
					break;
				case '-':
					note = note == 0 ? 13 : note - 1;
					i++;
					break;					
				}

				while (soundPlayDataString.at(i + 1) == '.')
				{
					dot++;
					i++;
				}
				break;
			}
		}
		break;
		default:
			continue;

		}

		double duration = silence>0 ? double(silence): double(Duration);

		double NoteDuration = 1.0 / duration;
		while (dot--)
		{
			duration *= 2;
			NoteDuration += 1.0 / duration;
		}
		NoteDuration *= 60000.0 * 4.0 / double(Tempo); // in miliseconds now

		if (silence > 0)
			Sleep(static_cast<unsigned int>(NoteDuration));
		else
			playNote(note, static_cast<unsigned int>(NoteDuration));
	}

	return true;
}


void CSheetMusicPlayer::playNote(unsigned int note, unsigned int currentDuration)
{
	int i;

	double frecuencia = 123.75, f=0.0;

	//Estas constantes son para las 12 notas de la octava 4

	//60,80,70,90,100,120 son las variaciones de las frecuencias
	//de 2 notas musicales consecutivas ejm: fFA-fMI=70
	//La suma de todas estas variaciones consecutivas es
	//Sumavarfrec=60+60+80+70+...+120=990 PARA LA OCTAVA 4
	//PARA LA OCTAVA X: Sumavarfrec=990*2^(X-4)
	//NOTA: frecuencia de DO en la octava 4 = 1050
	switch (note)
	{
	case 13:// not defined
	case 12:f += 120;//SI
	case 11:f += 100;//LA#
	case 10:f += 100;//LA
	case 9:f += 90;//SOL#
	case 8:f += 90;//SOL
	case 7:f += 90;//FA#
	case 6:f += 70;//FA
	case 5:// not defined
	case 4:f += 70;//MI
	case 3:f += 80;//RE#
	case 2:f += 60;//RE
	case 1:f += 60;//DO#
	case 0:f += 60;//DO   //OCTAVA4
	}

	//Se calcula la sumatoria de las frecuencias de las octavas anteriores
	//es decir, frecuenciaAcumulada = 123.75+990/8+990/4+990/2+...
	//  PARA LA OCTAVA:                oct1  oct2  oct3  oct4

	//NOTA: 990=Sumavarfrec
	for (i = 0; i < Octave - 1; i++)
		frecuencia += 990 * pow(2, i - 3);

	auto a = pow(2, -1);
	double aa = pow(2, Octave - 4);
	//Se calcula la frecuencia de la nota musical a tocar
	//frecuencia=frecuenciaAcumulada+f*2^(octava-4)
	frecuencia += f * pow(2, Octave - 4);

	//sound(frecuencia);
	// delay(200);
	//nosound();
	delay(50);
	DrawKey(1, Octave, note);//pinta el circulo rojo

	Beep(static_cast<DWORD>(frecuencia), currentDuration);
	//Sleep(currentDuration);
	
	DrawKey(0, Octave, note); // borra el circulo rojo
	/*
	if (getx() >= getmaxx() - 50) moveto(10, gety() + 15);

	setcolor(14);

	string Nota;

	switch (nota)
	{
	case 12:Nota = "SI"; break;//SI
	case 11:Nota = "LA#"; break;//LA#
	case 10:Nota = "LA"; break;//LA
	case 9:Nota = "SOL#"; break;//SOL#
	case 8:Nota = "SOL"; break;//SOL
	case 7:Nota = "FA#"; break;//FA#
	case 6:Nota = "FA"; break;//FA
	case 5:Nota = "MI"; break;//MI
	case 4:Nota = "RE#"; break;//RE#
	case 3:Nota = "RE"; break;//RE
	case 2:Nota = "DO#"; break;//DO#
	case 1:Nota = "DO"; break;//DO   //OCTAVA4

	}

	outtext(Nota.c_str());
	outtext(" ");
	*/
}

void CSheetMusicPlayer::DrawKey(int accion, int octava, int nota)
{

	int octavesMax = 8, octaveMin = 0;
	int formfactor = int(1015.0 / double(octavesMax * 7));

	int pos, x, y, color;

	int sostenido = 1;
	switch (nota)
	{
	case 1:pos = 1; break;
	case 3:pos = 2; break;
	case 7:pos = 4; break;
	case 9:pos = 5; break;
	case 11:pos = 6; break;

	default:
		sostenido = 0;
		switch (nota)
		{
		case 0:pos = 1; break;
		case 2:pos = 2; break;
		case 4:pos = 3; break;
		case 6:pos = 4; break;
		case 8:pos = 5; break;
		case 10:pos = 6; break;
		case 12:pos = 7; break;
		}
	}

	if (sostenido)
	{
		x = 5 + (7 * (octava - octaveMin) + pos)*formfactor;
		y = 30;
	}
	else
	{
		x = 5 + (7 * (octava - octaveMin) + pos)*formfactor - formfactor / 2;
		y = 80;
	}

	//accion=1 pintar bola
	//accion=0 borrar bola
	if (accion)
		color = LIGHTRED;
	else if (sostenido)
		color = BLACK;
	else
		color = WHITE;

	setcolor(color);
	setfillstyle(1, color);

	fillellipse(x, y, 5, 5);

}

void CSheetMusicPlayer::DrawKeyboard()
{
	setcolor(BLACK);

	//PINTA TECLADO
	setfillstyle(1, WHITE); 
	bar(5, 0, 1020, 100);//dibuja el contorno del teclado	

	int octavesMax = 8;
	unsigned int i, keys = octavesMax * 7;

	double formfactor = 1015.0 / double(keys);
	int blackKeyWidth = int(0.3 *formfactor);

	for (i = 1; i < keys; i++)
	{
		
		int x = i * int(formfactor);
		line(5 + x, 0, 5 + x, 100); //dibuja cada tecla

		setfillstyle(1, BLACK); 

		

		if (i % 7 != 0 && i % 7 != 3) 
			bar((x - blackKeyWidth) + 5, 0, (x + blackKeyWidth) + 5, 60); //dibuja cada tecla bemol/sostenido

		if (i % 7 == 1) 
			fillellipse(x - int(formfactor) / 2 + 5, 90, 3, 3); //dibuja un circulo a todas las notas DO
	}
	
	settextstyle(3, HORIZ_DIR, 3);
	setcolor(WHITE);
	outtextxy(10, 110, "SHEET MUSIC PLAYER");

	//settextstyle(7, HORIZ_DIR, 2);
	setcolor(LIGHTRED);
	outtextxy(100, 150, "This is another production made by:");
	setcolor(LIGHTGREEN);
	outtextxy(300, 180, "Jose Luis De la Cruz Lazaro");
	//settextstyle(11, HORIZ_DIR, 2);

}


int main(int argc, char** argv)
{
	if (argc == 3)
		//    return PlayToFile(argv[1], argv[2], 44100); // Use this for 44100 sample rate
		return PlayToFile(argv[1], argv[2], 16000);
	
	unsigned int option = 0;

	while (option != 4 ){

		clrscr();

		cout <<"SHEET MUSIC PLAYER" << endl << endl;
		cout << "1) Listen to melody on the computer speaker as beeps" << endl;	
		cout << "2) Convert melody to a WAV file" << endl;
		cout << "3) See specifications on how to compose your own melody" << endl;
		cout << "4) Exit" << endl << endl;
		cout << "Enter an option: ";
		cin >> option;

		if (option == 4) {
			break;
		} else if (option == 3) {


			clrscr();

			cout << endl << "The txt file to be loaded must contain one or more rows of a" << endl;
			cout << "SoundPlayDataString: Example: CCDCFEP10CCDCGFP10CC > C<AFEDP8>CC < AFGF" << endl;
			cout << "SoundPlayDataString: A string expression that contains one or" << endl;
			cout << "more of the following PLAY commands :" << endl;
			cout << "Octave and tone commands :" << endl;
			cout << "Ooctave    Sets the current octave(0 - 6)." << endl;
			cout << "< or >     Moves up or down one octave." << endl;
			cout << "A - G      Plays the specified note in the current octave." << endl;
			cout << "Nnote      Plays a specified note(0 - 84) in the seven - octave" << endl;
			cout << "           range(0 is a rest)." << endl;
			cout << endl;
			cout << "Duration and tempo commands :" << endl;
			cout << "Llength    Sets the length of each note(1 - 64).L1 is whole note," << endl;
			cout << "L2 is a half note, etc." << endl;
			cout << "ML         Sets music legato." << endl;
			cout << "MN         Sets music normal." << endl;
			cout << "MS         Sets music staccato." << endl;
			cout << "Ppause     Specifies a pause(1 - 64).P1 is a whole - note pause," << endl;
			cout << "P2 is a half - note pause, etc." << endl;
			cout << "Ttempo     Sets the tempo in quarter notes per minute(32 - 255)." << endl;
			cout << endl;
			cout << "Mode commands :" << endl;
			cout << "MF         Plays music in foreground." << endl;
			cout << "MB         Plays music in background." << endl;
			cout << endl << endl;

			cout << "Press any key to continue..." << endl;
			cgetch();

			cout << "Suffix commands :" << endl;
			cout << "# or + Turns preceding note into a sharp." << endl;
			cout << "- Turns preceding note into a flat." << endl;
			cout << ". Plays the preceding note 3 / 2 as long as specified." << endl << endl;

			cout << "Press any key to continue..." << endl;
			cgetch();

		}
		else {


			clrscr();

			cout << endl << endl << "Enter the name of the file that contains the melody (Example: happybirthday.txt): ";

			string fileNameTXT;
			cin >> fileNameTXT;

			std::ifstream infile(fileNameTXT.c_str(), ifstream::in);

			if (infile.is_open() == false) {
				cout << "File not found " << fileNameTXT;
				//return 0;
			}

			switch (option) {

			case 1:
			{

				// Happy Birthday
				//CSheetMusicPlayer melody("CCDCFEP10CCDCGFP10CC > C<AFEDP8>CC < AFGF");

				// Creep - Radiohead (the melody needs to be polished)
				//CSheetMusicPlayer melody("O4 AGF+G.  F+F+ L5AGG L4 F+.  AAGF+GEDC P10 AAGF+G.. DC<B BB>AGF+F+.. P10 L5GAGL4A+.F..  GAGGA+.G.. P10 GBB.. GBB.F+.ED+.. P10 B>C<BAB.. GAGA+.G.. P10 EG... AGF+.ED+.F+B.AGF+.. P15 L2G. L4 AGF+..E.D+... L2F L2G L2A L1A L4 G.. F+.. G L1F+ P5 L2A L3G.. L4F+.. G L2G");

				// Triciclo Peru Intro - Los Mojarras
				//CSheetMusicPlayer melody("L14 AA>CDEDC<A A>CDEDC P10 <FFAB>C<BAF FAB>C<BA P10 GGB>CDC<BG G B>CDC<B L13 AA>CDE");

				// Jingle bells
				//CSheetMusicPlayer melody("t200l4o2mneel2el4eel2el4egl3cl8dl1el4ffl3fl8fl4fel2el8eel4edde l2dgl4eel2el4eel2el4egl3cl8dl1el4ffl3fl8fl4fel2el8efl4ggfdl2c");

				string line, stringMelody;
				while (std::getline(infile, line))
				{
					stringMelody += line;
				}

				CSheetMusicPlayer melody(stringMelody);

				// Init WinBGI window
				initwindow(1024, 300, "The world of chaos in C++ - Unlimited Programming");
				CSheetMusicPlayer::DrawKeyboard();

				unsigned int positionError;
				if (melody.decode(positionError) == false) {
					cout << "Error decoding melody when reading character [" << stringMelody.at(positionError) << "] at position" << positionError;
					//return 0;
				}

				closegraph();

			}break;
			case 2:
			{

				string fileNameWAV;

				auto pos = fileNameTXT.find_last_of(".");
				if (pos != std::string::npos)
					fileNameWAV = fileNameTXT.substr(0, pos) + ".wav";

				if ( PlayToFile(fileNameTXT.c_str(), fileNameWAV.c_str(), 16000) == EXIT_SUCCESS ) // Sample rate: It can be 16000, 44100, etc...
					cout << "Successful conversion to file " << fileNameWAV << endl;
				else
					cout << "Error while converting" << endl;

			}break;
			}

			infile.close();

			cout << "Press any key to continue..." << endl;
			cgetch();
		}
	}
	

	return 1;
}
