#include <conio.h>
#include <iostream.h>
#include <dos.h>
#include <string.h>

//Clase Texto Flotante
class CTF{

 public:
  int x, y, xant, yant;
  CTF( const char* Texto );
  void Desplazar( int x, int y );

 private:
  char texto[8];
  int longitud;
};

CTF::CTF( const char* Texto ){
 strcpy(texto, Texto );
 longitud = strlen( texto );
 xant=yant=1;
}

void CTF::Desplazar( int x, int y ){
 gotoxy(xant,yant);
 for(int i=0;i<longitud;i++)
  cout<<" ";
 gotoxy(xant=x,yant=y);
 cout<<texto;
}

void EfectText(CTF *texto)
{
 int x,y;
 for( y=1,x=1; y<=12; y++,x+=3 ){
  texto[0].Desplazar( 40, y );
  texto[1].Desplazar( x, 13 );
  texto[2].Desplazar( 80-x, 13 );
  delay(100);
 }

 for( y=1,x=1; y<=11; y++,x+=3 ){
  texto[3].Desplazar( x, 14 );
  texto[4].Desplazar( 40, 25-y );
  texto[5].Desplazar( 80-x, 14 );
  delay(80);
 }
}

void main()
{
 CTF texto[6]={ CTF("El"), CTF("Lenguaje"), CTF("C++"),
		CTF("­­­Es"), CTF("el"), CTF("Mejor!!!") };

 char tecla;
 do
 {
  clrscr();
  EfectText( texto ); //muestra el efecto
  gotoxy(10,25);
  cout<<"ESC: Salir";
  gotoxy(52,25);
  cout<<"ESPACIO:Repetir...";

  do //se filtra solo las teclas ESC y ESPACIO
   tecla = getch();
  while( tecla!=27 && tecla!=32 );

 }while(tecla!=27); //se sale con ESC
}