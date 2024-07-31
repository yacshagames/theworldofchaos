/********************************************
SOLUTION TO CHALLENGE0009:

7/8 ASCII FILES COMPRESSION:
Programmed by:
   Jose Luis De la Cruz Lazaro - 16/XI/2000
   contact@theworldofchaos.com
   https://www.theworldofchaos.com
********************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using std::cout;
using std::cin;

// Returns a character bit
// position: The position of the bit to be returned (Takes values ​​from 0 to 7)
// If position = 0 indicates that the lowest order bit will be returned
unsigned char GetBit(unsigned char caracter, unsigned char posicion);

// Change the value of a character bit
// position: The position of the bit to change (Takes values ​​from 0 to 7)
// bit: Value of the bit to insert in the desired position
void SetBit(unsigned char *caracter, unsigned char posicion, unsigned char bit);

// Compress the input file into the output file
int comprimir(std::ifstream& entrada, std::ofstream& salida);

// Decompress the input file into the output file
int descomprimir(std::ifstream& entrada, std::ofstream& salida);

// Check if the input file is a simple ASCII, that is,
// that the characters in the input file are less than 128
bool Comprobar_ASCII_Simple(std::ifstream& entrada);

void MostrarSintaxis();

int main(int narg, char *arg[])
{
	//Title and credits
	cout << "\n7/8 ASCII FILES COMPRESSION:\n";
	cout << "Programmed by:\n";
	cout << " Jose Luis De la Cruz Lazaro - 16/XI/2000\n";
	cout << " for CWORLD Challenge0009\n\n";
	
	if (narg != 4)
	{
		cout << "Error1: Missing arguments\n";
		MostrarSintaxis();
		return 1;
	}
		
	char flag;

	std::string sarg(arg[1]);

	if (sarg=="C" || sarg == "c" )
		flag = 'C';
	else
		if (sarg == "D" || sarg == "d")
			flag = 'D';
		else
		{
			cout << "Error2: The flag is incorrect\n";
			MostrarSintaxis();
			return 2;
		}

	std::ifstream entrada(arg[2], std::ios::binary);
	std::ofstream salida(arg[3], std::ios::binary);
		
	// Open the input file
	if (entrada.is_open()==false)
	{
		cout << "Error3: The input file " << arg[2] << " does not exist!\n";
		salida.close();
		return 2;
	}

	// Check if the input file is an ASCII, before
	// creating the output file
	if ( flag=='C' && Comprobar_ASCII_Simple(entrada)==false)
	{
		cout << "Error5: The input file is not a Plain ASCII\n";
		entrada.close();
		return 4;
	}

	// Open the output file
	if (salida.is_open() == false)
	{
		cout << "Error4: Cannot create output file: " << arg[3] << "\n";
		entrada.close();
		return 3;
	}
	
	// Select the process to take
	switch (flag)
	{
	case 'C': comprimir(entrada, salida); break;
	case 'D': descomprimir(entrada, salida); break;
	}

	entrada.close();
	salida.close();

	cout << "The program ran successfully! :)\n";

	return 0; // Success
}

// Returns a character bit
// position: Takes values ​​from 0 to 7
// If position = 0 indicates that the lowest order bit will be returned (order=0)
unsigned char GetBit(unsigned char caracter, unsigned char posicion)
{
	return (caracter & 1 << posicion) && 1;//returns 1 or 0
}

// Change the value of a character bit
// position: The position of the bit to change (Takes values ​​from 0 to 7)
// bit: Value of the bit to insert in the desired position
void SetBit(unsigned char *caracter, unsigned char posicion, unsigned char
	bit)
{
	if (bit)
		*caracter |= 1 << posicion; // insert bit 1
	else
		*caracter &= ~(1 << posicion); // insert bit 0
}

// Compress the input file into the output file
int comprimir(std::ifstream& entrada, std::ofstream& salida)
{
	unsigned char
		PaqueteD[8],	// PackD will contain 8 consecutive bytes of the
						// INPUT file (Uncompressed)
		PaqueteC[7],	// PackC will contain 8 consecutive bytes of the
						// OUTPUT file (Compressed)
		id, // Index of the currently processed PacketD ( id<64 )
		ic; // Index of the currently processed PacketC ( ic<56 )

	std::streampos fsize = entrada.tellg();
	entrada.seekg(0, std::ios::end); // Go to the end of the file
	fsize = entrada.tellg() - fsize; // Size in bytes of the input file	

	long TamEnt = static_cast<long>(fsize), // Size in bytes of the input file
		NumPaq,			// Number of groups of 8 packets in the input file
		i = 0;

	char NumBits = 64,  // Number of bits of the packet currently
						// parsed in the input file
		TamPaqD = 8,	// PaqueteD size in bytes
		TamPaqC = 7,	// PaqueteC size in bytes
		BytesSob;		// Number of bytes left over in the input file,
						// when forming groups of 8 packets

	BytesSob = TamEnt % 8; // The remainder of TamEnt/8 is assigned

	NumPaq = TamEnt >> 3;  // TamEnt = TamEnt/8 (integer division)

	entrada.seekg(0, std::ios::beg); // Go to the beginning of the file

	do
	{
		if (i == NumPaq) // If the groups of 8 Packs are finished
		{
			NumBits = BytesSob << 3;		// Get the leftover bits
			TamPaqD = TamPaqC = BytesSob;	// Get the leftover bytes
			for (int j = 0; j < 7; j++)
				PaqueteC[j] = 0;			// Fill the bits of PaqueteC with zeros
		}

		// Read packets from the input file from the beginning
		entrada.read((char*)&PaqueteD, TamPaqD);

		// COMPRESSION PROCESS
		id = ic = 0;
		while (id < NumBits) // As long as all bits of the packet are not read
		{
			if (id % 8) //The 7th bit of the byte currently read in
						//PaqueteD is skipped (because it contains zero)
			{
				//Move bits from PaqueteD to PaqueteC
				SetBit(&PaqueteC[ic >> 3], 7 - ic % 8, GetBit(PaqueteD[id >> 3], 7 - id % 8));
				ic++;
			}
			id++;
		}

		// Write compressed packets to the output file
		salida.write((char*)&PaqueteC, TamPaqC);

	} while (++i <= NumPaq);	//As long as not all package groups
								// are read from the input file
	return 1;
}

// Decompress the input file into the output file
int descomprimir(std::ifstream& entrada, std::ofstream& salida)
{
	unsigned char
		PaqueteD[8],	// PackD will contain 8 consecutive bytes of the
						// OUTPUT file (Uncompressed)
		PaqueteC[7],	// PackC will contain 8 consecutive bytes of the
						// INPUT file (Compressed)
		id,	// Index of the currently processed PacketD ( id<64 )
		ic;	// Index of the currently processed PacketC ( ic<56 )

	std::streampos fsize = entrada.tellg();
	entrada.seekg(0, std::ios::end); // Go to the end of the file
	fsize = entrada.tellg() - fsize; // Size in bytes of the input file	

	long TamEnt = static_cast<long>(fsize), // Size in bytes of the input file
		NumPaq,			// Number of groups of 8 packets in the input file
		i = 0;

	char NumBits = 64,	// Number of bits of the packet currently
						// parsed in the input file
		TamPaqD = 8,	// PaqueteD size in bytes
		TamPaqC = 7,	// PaqueteC size in bytes
		BytesSob;		// Number of bytes left over in the input file,
						// when forming groups of 8 packets

	BytesSob = TamEnt % 7; // The remainder of TamEnt/8 is assigned

	NumPaq = TamEnt / 7;   // TamEnt = TamEnt/8 (integer division)

	entrada.seekg(0, std::ios::beg); // Go to the beginning of the file

	do
	{
		if (i == NumPaq) // If the groups of 8 Packs are finished
		{
			NumBits = BytesSob << 3;        // Get the leftover bits
			TamPaqD = TamPaqC = BytesSob;	// Get the leftover bytes
		}

		// Read packets from the input file from the beginning
		entrada.read((char*)&PaqueteC, TamPaqC);

		// DECOMPRESSION PROCESS
		id = ic = 0;
		while (id < NumBits) // As long as all bits of PacketS are not written
		{
			if (id % 8) // Omit writing the 7th bit of the currently
						// processed byte of PaqueteD
			{
				// Move bits from PaqueteC to PaqueteD
				SetBit(&PaqueteD[id >> 3], 7 - id % 8, GetBit(PaqueteC[ic >> 3], 7 - ic % 8));
				ic++;
			}
			else
				SetBit(&PaqueteD[id >> 3], 7, 0);	// Zero is inserted into the 7th bit
													// of the byte currently
													// processed in PaqueteD
			id++;
		}

		// Write compressed packets to the output file
		salida.write((char*)&PaqueteD, TamPaqD);

	} while (++i <= NumPaq);	// As long as not all package groups
								// are read from the input file
	return 1;
}

// Check if the input file is a simple ASCII, that is,
// that the characters in the input file are less than 128
bool Comprobar_ASCII_Simple(std::ifstream& entrada)
{
	// Copy the read file into a buffer
	const std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(entrada), {});	

	for (const auto& caracter : buffer) {
		if (caracter >= 128)
			return false;
	}

	// Go to the beginning of the file, 
	// that the file can be read again
	entrada.seekg(0, std::ios::beg); 
	
	return true;
}

void MostrarSintaxis()
{
	cout << "\nSYNTAX: CHALLENGE0009 flag[C/D] InputFile OutputFile\n\n";
	cout << "for example:\n\n";
	cout << " CHALLENGE0009 C test.txt Output.enc\n";
	cout << "     (to compress the file test.txt and generate the file output.enc)\n";
	cout << " CHALLENGE0009 D Output.enc test.txt\n";
	cout << "     (to decompress the file output.enc)\n\n";
}

