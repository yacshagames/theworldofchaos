/********************************************
SOLUCION AL RETO0009:

COMPRESION 7/8 DE FICHEROS ASCII:
Programado por:
   Jos‚ Luis De la Cruz L zaro - 16/XI/2000
   jcruz@ec-red.com
   http://www.geocities.com/joseluisdl
********************************************/
#include <stdio.h>
#include <string.h>

//Retorna un bit de caracter
//posici¢n: La posici¢n del bit a retornar (Toma valores de 0 a 7)
//Si posici¢n = 0 indica que se retornar  el bit de menor orden
unsigned char GetBit(unsigned char caracter, unsigned char posicion);

//Cambia el valor de un bit de caracter
//posici¢n: La posici¢n del bit a cambiar (Toma valores de 0 a 7)
//bit: Valor del bit a insertar en la posici¢n deseada
void SetBit(unsigned char *caracter, unsigned char posicion, unsigned char 
bit);

//Comprime el archivo entrada en el archivo salida
int comprimir( FILE *entrada, FILE *salida);

//Descomprime el archivo entrada en el archivo salida
int descomprimir( FILE *entrada, FILE *salida);

//Comprueba si el archivo de entrada es un ASCII simple,
//es decir, que los caracteres del fichero entrada, sean
//menores a 128
int Comprobar_ASCII_Simple( FILE *entrada );

void MostrarSintaxis();

int main(int narg, char *arg[] )
{
//T¡tulo y cr‚ditos
printf("\nCOMPRESION 7/8 DE FICHEROS ASCII:\n");
printf("Programado por:\n");
printf("   Jos‚ Luis De la Cruz L zaro - 16/XI/2000\n");
printf("   para el Reto0009 de CWORLD\n\n");

if( narg!=4 )
{
  printf("Error1: Faltan argumentos\n");
  MostrarSintaxis();
  return 1;
}

FILE *entrada, *salida;
char flag;

  if( !strcmp(strupr(arg[1]),"C") )
   flag = 'C';
  else
   if( !strcmp(strupr(arg[1]),"D") )
    flag= 'D';
   else
   {
    printf("Error2: El flag es incorrecto\n");
    MostrarSintaxis();
    return 2;
   }

//abre el fichero de entrada
if( (entrada = fopen( arg[2], "rb" ))==NULL )
{
  printf("Error3: El fichero de entrada %s no existe!\n",arg[2]);
  fclose(entrada);
  return 2;
}

//Comprueba si el fichero entrada es un ASCII, antes de crear
//el fichero de salida
if( !strcmp(strupr(arg[1]),"C") && Comprobar_ASCII_Simple(entrada) )
{
  printf("Error5: El fichero de entrada no es un ASCII Simple\n");
  fclose(entrada);
  return 4;
}

//abre el fichero de salida
if( (salida = fopen( arg[3], "wb" ))==NULL )
{
  printf("Error4: No se puede crear el fichero de salida: %s\n",arg[3]);
  fclose(entrada);
  return 3;
}

//Selecciona el proceso a tomar
switch( flag)
{
  case 'C': comprimir( entrada,salida); break;
  case 'D': descomprimir( entrada,salida); break;
}

fcloseall();

printf("El programa se ejecut¢ satisfactoriamente! :)\n");

return 0; //‚xito
}

//Retorna un bit de caracter
//posici¢n: Toma valores de 0 a 7
//Si posici¢n = 0 indica que se retornar  el bit de menor orden ( orden=0 )
unsigned char GetBit(unsigned char caracter, unsigned char posicion)
{
return ( caracter&1<<posicion ) && 1;//retorna 1 ¢ 0
}

//Cambia el valor de un bit de caracter
//posici¢n: Toma valores de 0 a 7
//bit: Valor del bit a insertar en la posici¢n deseada
void SetBit(unsigned char *caracter, unsigned char posicion, unsigned char 
bit)
{
if( bit )
  *caracter|=1<<posicion; //inserta el bit 1
else
  *caracter&=~(1<<posicion); //inserta el bit 0
}

//Comprime el archivo entrada en el archivo salida
int comprimir( FILE *entrada, FILE *salida)
{

char PaqueteD[8], //contendr  8 bytes consecutivos del
		   //fichero ENTRADA (Descomprimido)
      PaqueteC[7], //contendr  8 bytes consecutivos del
		   //fichero SALIDA (Comprimido)
      id,          //Indice del PaqueteD actualmente procesado ( id<64 )
      ic;          //Indice del PaqueteC actualmente procesado ( ic<56 )

fseek(entrada,0L,SEEK_END);   //Se va hasta el final del fichero
long TamEnt = ftell(entrada), //Tama¤o en bytes del fichero entrada
      NumPaq,                  //N£mero de grupos de 8 paquetes en
			       //en el fichero entrada
      i=0;

char NumBits = 64,  //N£mero de bits del paquete actualmente
		     //analizado en el fichero entrada
      TamPaqD = 8,   //Tama¤o de PaqueteD en bytes
      TamPaqC = 7,   //Tama¤o de PaqueteC en bytes
      BytesSob;      //N£mero de bytes sobrantes en el fichero
		     //entrada, al formar grupos de 8 paquetes

BytesSob = TamEnt%8; //Se asigna el residuo de TamEnt/8

NumPaq = TamEnt>>3;  //TamEnt = TamEnt/8 (divisi¢n entera)

fseek(entrada,0L,SEEK_SET); //Se va hasta el inicio del fichero

do
{
  if( i==NumPaq ) //Si se acabaron los grupos de 8 PaquetesD
  {
   NumBits = BytesSob<<3;        //Se obtienen los bits sobrantes
   TamPaqD = TamPaqC = BytesSob; //Se obtienen los bytes sobrantes
   for( int j=0;j<7;j++)
    PaqueteC[j] = 0;             //Llena los bits del PaqueteC con ceros
  }

  //Se lee paquetes del fichero de entrada desde el inicio
  fread( &PaqueteD, TamPaqD , 1, entrada );

  //PROCESO DE COMPRESION
  id=ic=0;
  while( id<NumBits ) //Mientras no se lea todos los bits de PaqueteD
  {
   if( id%8 ) //Se omite el bit de orden 7 del byte actualmente leido en
	      //PaqueteD ( porque contiene cero )
   {
    //Se traslada bits de PaqueteD a PaqueteC
    SetBit( &PaqueteC[ic>>3], 7-ic%8, GetBit( PaqueteD[id>>3], 7-id%8 ));
    ic++;
   }
   id++;
  }

  //Se escribe los paquetes comprimidos en el fichero de salida
  fwrite( &PaqueteC, TamPaqC, 1, salida);

}while( ++i<=NumPaq); //Mientras no se lea todos los grupos de paquetes
		       //del fichero de entrada
return 1;
}

//Descomprime el archivo entrada en el archivo salida
int descomprimir( FILE *entrada, FILE *salida)
{

char PaqueteD[8], //contendr  8 bytes consecutivos del
		   //fichero SALIDA (Descomprimido)
      PaqueteC[7], //contendr  8 bytes consecutivos del
		   //fichero ENTRADA (Comprimido)
      id,          //Indice del PaqueteD actualmente procesado ( id<64 )
      ic;          //Indice del PaqueteC actualmente procesado ( ic<56 )

fseek(entrada,0L,SEEK_END);   //Se va hasta el final del fichero
long TamEnt = ftell(entrada), //Tama¤o en bytes del fichero entrada
      NumPaq,                  //N£mero de grupos de 8 paquetes
			       //en el fichero entrada
      i=0;

char NumBits = 64,  //N£mero de bits del paquete actualmente
		     //analizado en el fichero entrada
      TamPaqD = 8,   //Tama¤o de PaqueteD en bytes
      TamPaqC = 7,   //Tama¤o de PaqueteC en bytes
      BytesSob;      //N£mero de bytes sobrantes en el fichero
		     //entrada, al formar grupos de 8 paquetes

BytesSob = TamEnt%7; //Se asigna el residuo de TamEnt/8

NumPaq = TamEnt/7;  //TamEnt = TamEnt/8 (divisi¢n entera)

fseek(entrada,0L,SEEK_SET); //Se va hasta el inicio del fichero

do
{
  if( i==NumPaq ) //Si se acabaron los grupos de 8 PaquetesD
  {
   NumBits = BytesSob<<3;        //Se obtienen los bits sobrantes
   TamPaqD = TamPaqC = BytesSob; //Se obtienen los bytes sobrantes
  }

  //Se lee paquetes del fichero de entrada desde el inicio
  fread( &PaqueteC, TamPaqC , 1, entrada );

  //PROCESO DE DESCOMPRESION
  id=ic=0;
  while( id<NumBits ) //Mientras no se escirba todos los bits de PaqueteD
  {
   if( id%8 ) //Se omite escribir el bit de orden 7 del byte actualmente
	     //procesado de PaqueteD
   {
    //Se traslada bits de PaqueteC a PaqueteD
    SetBit( &PaqueteD[id>>3], 7-id%8, GetBit( PaqueteC[ic>>3], 7-ic%8 ));
    ic++;
   }
   else
    SetBit( &PaqueteD[id>>3], 7, 0 ); //Se inserta cero en el bit de
				      //orden 7 del byte actualmente
				      //procesado en PaqueteD
   id++;
  }

  //Se escribe los paquetes comprimidos en el fichero de salida
  fwrite( &PaqueteD, TamPaqD, 1, salida);

}while( ++i<=NumPaq); //Mientras no se lea todos los grupos de paquetes
		       //del fichero de entrada
return 1;
}

//Comprueba si el fichero de entrada es un ASCII simple,
//es decir, que los caracteres del fichero entrada, sean
//menores a 128
int Comprobar_ASCII_Simple( FILE *entrada )
{

fseek(entrada,0L,SEEK_END);//Se va hasta el final del fichero
long TamEnt = ftell(entrada); //Tama¤o en bytes del fichero entrada

fseek(entrada,0L,SEEK_SET);//Se va hasta el inicio del fichero
for( long i=0;i<TamEnt;i++)
  if( fgetc(entrada)>=128 )
   return 1;

return 0;

}

void MostrarSintaxis()
{
printf("\nSINTAXIS: RETO0009 flag[C/D] I:ArchivoEntrada 
O:ArchivoSalida\n\n");
printf("por ejemplo:\n\n");
printf("  RETO0009 C I:prueba.txt O:Salida.enc\n");
printf("     (para comprimir el archivo prueba.txt y generar archivo 
salida.enc)\n");
printf("  RETO0009 D I:Salida.enc O:prueba.txt\n");
printf("     (para descomprimir el archivo salida.enc)\n\n");
}

