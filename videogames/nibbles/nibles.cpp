/***************************************************************************
NIBBLES

SKILL GAME (1 or 2 players)

Developed by:

	JOSE LUIS DE LA CRUZ LAZARO
	contact@theworldofchaos.com

	YACSHA - Software & Desing, since 1999, Lima-Peru
	>> The World of chaos - EL MUNDO DEL CAOS - Unlimited Programming
	www.theworldofchaos.com

LICENSE
	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

HISTORY...

>> Version 7 - 21-III-2024
  - Update graphics/nibles - Porting to VC++ 2017 using winbgi

>> Version 6.1 - 29-XII-1999
 - 	The use of the joystick was added to control the nibble of player 1,
 	and at the same time it can also be controlled using the keyboard...
	this is due to the routines to control the joystick: joystick.h and
	calijoy.h .. .which I include with the sources
 	* the joystick is calibrated in text mode
 	* the joystick is used to control player 1's nibble


>> NIBBLES 6.0 BETA - 26-VI-1999
Versions after 5.6 and before this version have been a failure,
so I decided to remake the game from scratch with objects (OOP),
which has given me good results (a compact and understandable code),
I have made this new version BETA because it did not The editor for
new phases has still been added, there is no third player and also
because I have not yet finished making the new backgrounds for the
phases, all this in assembly language...

>> NIBBLES 5.6 - 13-VI-1998
Well you won't believe it but this is one of my first programs in C++,
so you will notice the excessive use of variables, also I didn't know
objects yet, now I do... 20-VI-1999

SMALL COMMENT
It took me more than 3 months (my entire summer!) to do it, but after
finishing this program I was already working on something in C++...

INSTRUCTIONS

For those who have never played the famous Nibbles in Basic, the objective
is to eat all the numbers from 1 to 9 that appear on the screen, when you
eat the latter you change the level (I recommend playing between 2 people,
or three), NO YOU SHOULD CRASH, NOT EVEN WITH YOURSELVES
YOU CAN'T GO BACK!!!!!

MOVEMENTS
  LEFT RIGHT UP DOWN
PLAYER 1: LEFT RIGHT UP DOWN
PLAYER 2: A D W S
PLAYER 3: K ; O L

USING THE PHASE EDITOR
If you're bored of my pre-programmed phases, make your own:
Choose option 4

then edit the phase by moving with the keyboard, and changing color
with the following keys:

` = GRAY (cursor) with this key you can move without dirtying the screen
1 = BLACK
2 = RED

Don't put another color!!!

When you finish press enter.

Then give it the following name: phase_n and press enter
Where n is a number greater than 10, if you put a smaller n you could
delete some of the preprogrammed phases.

Well, this phase will be played in phase n (level n), so if you want to
play it at the beginning, you just change the name of phase_1 to another
name and your phase_n to phase_1.

KNOWN BUGS

Rather, I wouldn't say a bug, but rather a relief, because you have
infinite lives (I'm not that cruel maybe...)

***************************************************************************/

//#include <graphics.h>
//#include <conio.h>
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include "graphics.h"
#include "conio.h"

#include <ctype.h>
#include <dos.h>
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <io.h>

//#include "joystick.h"
//#include "calijoy.h"



//#include <conio.h> //getch()
//#include "grafxy.h"

using namespace std;

class NIBBLE
{
protected:
	//Variables Miembro protegidas
	int x0, y0;
	int xant, yant;
	int color;

	int ucmax;//(Unidad de Cola Maxima)
		  //numero maximo de unidades de division de la cola
	int ucact;//(Unidad de Cola Actual) unidad de cola actualmente procesada
	int ucbor;//(Unidad de Cola Borrada) unidad de cola actualmente borrada
	int lcact;//(Longitud de Cola Actual)

	int cola[55][2];
	int sensor[2];
	int muerte;
	long Puntaje;
	char Nombre[11];


public:

	//Teclas de Direccion
	char TeclaINI, teclaAnt, IZQ, DER, ARR, ABJ;


	//Constructor
	NIBBLE(char *_Nombre, int _x, int _y, int _color,
		char _IZQ, char _DER, char _ARR, char _ABJ, char _TeclaINI);

	//Variables Miembro
	int x, y;

	//Ciclo de Vida
	void Nacimiento();
	int  Evolucion(int &num, int &X, int &Y);
	void Crecimiento(char tecla);
	int  Muerte(char tecla);

};

/////////////////////////////////////////////////////////////////////////
NIBBLE::NIBBLE(char *_Nombre, int _x, int _y, int _color,
	char _IZQ, char _DER, char _ARR, char _ABJ, char _TeclaINI)
{
	color = _color;
	x0 = _x;
	y0 = _y;

	IZQ = _IZQ;
	DER = _DER;
	ARR = _ARR;
	ABJ = _ABJ;
	TeclaINI = _TeclaINI;

	strcpy(Nombre, _Nombre);

	Puntaje = 0;

	Nacimiento();
};

/////////////////////////////////////////////////////////////////////////
void NIBBLE::Nacimiento()
{
	xant = x = x0;
	yant = y = y0;

	teclaAnt = TeclaINI;

	ucact = ucbor = 0;
	lcact = 1;
	ucmax = 3;
	muerte = 0;

}

int NIBBLE::Evolucion(int &num, int &X, int &Y)
{
	//Evolucion del Nibble
	int logico = (x + 5 == X && y + 5 == Y), px;

	//settextjustify(1,1);	//justificacion centrada
	//outtextxy

	px = (color == 14) ? 45 : 450;
	setfillstyle(1, color);
	bar(px, 3, px + 9, 12);

	px = (color == 14) ? 10 : 60;
	gotoxy(px, 1); cout << Nombre << ": " << Puntaje;

	if (logico)
	{
		ucmax = (num + 1)*(num + 2) / 2;
		//Formula para el puntaje del jugador
		Puntaje += (abs(X - 325) / 10 + abs(Y - 205) / 10);
	}

	return logico;

}


/////////////////////////////////////////////////////////////////////////
void NIBBLE::Crecimiento(char tecla)
{

	//verifica si no se presiono ninguna tecla de movimiento del NIBBLE
	if (tecla != ARR && tecla != ABJ && tecla != DER && tecla != IZQ)
		//se tomara la tecla anterior como la tecla actual presionada
		//esto servira para mantener el nible moviendose en una sola
		//direccion cuando no se presiona ninguna tecla
		tecla = teclaAnt;
	else
		// se detecta si se quiere retroceder y se impide tal accion
		if (abs(tecla - teclaAnt) == abs(ABJ - ARR) ||
			abs(tecla - teclaAnt) == abs(IZQ - DER))
			tecla = teclaAnt;


	teclaAnt = tecla;
	xant = x;
	yant = y;

	//DETECTA QUE TECLA SE PRESIONO
	if (tecla == ARR)
	{
		y -= 10;
		sensor[0] = x + 5;
		sensor[1] = y - 1;
	}
	else
		if (tecla == ABJ)
		{
			y += 10;
			sensor[0] = x + 5;
			sensor[1] = y + 11;
		}
		else
			if (tecla == IZQ)
			{
				x -= 10;
				sensor[0] = x - 1;
				sensor[1] = y + 5;
			}
			else
				if (tecla == DER)
				{
					x += 10;
					sensor[0] = x + 11;
					sensor[1] = y + 5;
				}

	//el sensor detecta un color diferente del fondo negro=0
	//esto es un posible choque (se avecina la muerte)
	int color_detect = getpixel(sensor[0], sensor[1]);

	//si no se detecta el color de fondo o el color de un numero capturadp
	//quiere decir que se choco con algo ( esto es la muerte no oficial del jugador)
	if (color_detect != 0 && color_detect != 7) muerte = 1;

	if (ucact == 55)ucact = 0;

	//CARGA DE UNIDADES DE COLA
	setfillstyle(1, color);

	bar(x, y, x + 10, y + 10);

	cola[ucact][0] = xant;
	cola[ucact][1] = yant;
	ucact++;


	//DESCARGA DE UNIDADES DE COLA
	if (lcact == ucmax)
	{
		if (ucbor == 55)ucbor = 0;

		int i = cola[ucbor][0], j = cola[ucbor][1];
		ucbor++;

		setfillstyle(1, 0);

		bar(i, j, i + 10, j + 10);

	}
	else lcact++;

}

/////////////////////////////////////////////////////////////////////////
int NIBBLE::Muerte(char tecla)
{

	if (tecla != ARR && tecla != ABJ && tecla != DER && tecla != IZQ)
		tecla = teclaAnt;

	//para entrar aqui (muerte=1) esto quiere decir que el jugador
	//debio haber sido declarado muerto no oficialmente
	if (teclaAnt == tecla && muerte)//el jugador no fue muy rapido y colisiono
	{
		//al entrar aqui el jugado esta muerto oficialmente
		setcolor(0);//color de letra
		setfillstyle(1, color); //estilo:solido, color: del nible
		bar(getmaxx() / 2 - 50, getmaxy() / 2 - 30, getmaxx() / 2 + 50, getmaxy() / 2 + 30);
		settextjustify(1, 1);	//justificacion centrada
		outtextxy(getmaxx() / 2, getmaxy() / 2 - 10, "MUERE!!!");	     //Mensaje de Muerte
		outtextxy(getmaxx() / 2, getmaxy() / 2 + 10, Nombre);	     //Mensaje de Muerte
		getch();
		return 1;
	}
	else muerte = 0;//teclaAnt!=tecla quiere decir:
			 //la rapida reaccion del jugador lo salvo de su muerte
	return 0;
}

/////////////////////////////////////////////////////////////////////////
//FUNCIONES ESPECIALES
void AparecerNumero(int &X, int &Y, int num);

void Doble_Nacimiento(NIBBLE &Nibble1,
	NIBBLE &Nibble2, int &num, char &tecla);

int Cargar_Fase(int num);

/////////////////////////////////////////////////////////////////////////
//APARECER UN NUMERO ALEATORIAMENTE EN PANTALLA:

void AparecerNumero(int &X, int &Y, int num)
{

	int num_aleatorio;

	//Se busca una posicion (X,Y) adecuada donde poner el numero
	//es decir que este sobre el fondo negro
	//y no aparesca encima del nibble o encima de las paredes
	do {

		num_aleatorio = random(20) + 1;
		X = 15 + num_aleatorio * 30;

		num_aleatorio = random(13) + 1;
		Y = 55 + num_aleatorio * 30;

		num_aleatorio = random(3) + 1;//genera numero aleatorio entero en el intervalo [1,4]

		if (num_aleatorio == 1)
		{
			num_aleatorio = random(3) + 1;//genera numero aleatorio entero en el intervalo [1,4]

			switch (num_aleatorio)
			{
			case 1: X = 15; break;

			case 2:	X = 625; break;

			case 3:	Y = 65; break;

			case 4:	Y = 465; break;
			}//fin del switch

		}

	}//repetir mientras el numero no se encuntre en el fondo negro
	while (getpixel(X - 2, Y - 2) != 0);


	/*
	 char *numero=" ",digito;
	 digito=char(48+num);
	 *numero=digito;
	 */
	char numero[2];
	itoa(num, numero, 10);
	setcolor(7);
	outtextxy(X - 2, Y - 2, numero);

}

/////////////////////////////////////////////////////////////////////////
void Doble_Nacimiento(NIBBLE &Nibble1, NIBBLE &Nibble2,
	int &num, char &tecla)
{
	num = 1;
	tecla = 1;
	Nibble1.Nacimiento();
	Nibble2.Nacimiento();
}

/////////////////////////////////////////////////////////////////////////
//LECTURA DE UNA FASE PREPROGRAMADA


int Cargar_Fase(int num)
{

	char p[64], nombre[13], numero[2];

	int leer, i, j, k, color;

	itoa(num, numero, 10);

	strcpy(nombre, "fase_");

	strcat(nombre, numero);

	strcat(nombre, ".nib");

	leer = open(nombre, 0);

	// leer=open("fase_1.nib",0);

	cleardevice();
	// cout<<nombre;getch();getch();

   // gotoxy(27,12);
	
	if (leer == -1)
	{
		closegraph();

		clrscr();
		gotoxy(26, 12);
		cout << "Error al cargar la fase!!!";
		getch();

		return 0;
	}
	int aa = getmaxx();

	for (j = 30; j <= getmaxy(); j += 10)
	{
		k = 0;
		read(leer, p, 64);

		for (i = 0; i <= getmaxx(); i += 10, k++)
		{
			color = p[k] - 48;
			setfillstyle(1, color);//Estilo:solido, color:negro o rojo
			bar(i, j, i + 10, j + 10);
		}
	}

	close(leer);


	return 1;

}

int main()
{
	
	int opcion;
	clrscr();
	gotoxy(50, 24); cout << "<<JLDL-Software UNI-FIEE>>";
	gotoxy(1, 1);
	cout << "\n\n\t\t ~~~~~~~~~~~~NIBLES VERSION 6.0_____________";
	cout << "\n\n";
	cout << "\n\t\t\t (1) 1 JUGADOR";
	cout << "\n\t\t\t (2) 2 JUGADORES";
	cout << "\n\t\t\t (3) SALIR";
	cout << "\n\n\t\t\tSeleccione una opcion :";
	cin >> opcion;

	if (opcion == 3) return 0;

	//Escala de velocidad del juego

	int escala_velocidad;

	clrscr();
	gotoxy(20, 11);
	cout << "Su velocidad debe estar entre 1 y 100"
		<< "\n\n\t\t\tBABYS     : (de 1  a 35)"
		<< "\n\n\t\t\tGENTE BIEN: (de 36 a 70)"
		<< "\n\n\t\t\tVICIOSO   : (de 71 a 90)"
		<< "\n\n\t\t\tDROGOS    : (mas de 90)";

	gotoxy(20, 8);
	cout << "Ingrese su Velocidad : ";
	cin >> escala_velocidad;
	
	//Calibrar_Joystick();


	//int gd = DETECT, gm;
	//initgraph(&gd, &gm, "");//modifica esta linea si tienes problemas con el bgi
	initwindow(650, 490, "The world of chaos in C++ - Unlimited Programming");

	//se ajusta los valores aleatorios que arrojara la funcion random
	//mediante la funcion srand, la cual toma como argumento una variable segundos
	time_t segundos;
	//segundos es inicializada con los segundos transcurridos desde el 1/1/1970
	//(algunos diran este programa tendra el ERROR DEL 2000, pero no luego inventare un parche)
	time(&segundos);
	//ramdom arrojara valores aleatorios que dependen del tiempo en que
	//se inicie el programa
	srand(segundos % 62536);

	int tpausa = (-200) / (100 - 1)*(escala_velocidad - 1) + 200;
	//Ajuste de la velocidad en una recta cuyo dominio
	//es [1,100] (escala_velocidad) y cuyo rango
	//es [0,200] milisegundos (tiempo de pausa)

	NIBBLE Nibble1((char*)"Lombrizo", 360, 260, 14, 75, 77, 72, 80, 77),
		Nibble2((char*)"Cientiezo", 280, 250, 5, 'A', 'D', 'W', 'S', 'A');

	char tecla = 1;
	int X = 0, Y = 0, num = 1, Nivel = 1;

	//BUCLE DE LA VIDA
	Cargar_Fase(Nivel);

	clock_t t = clock();


	do
	{

		//EVOLUCION
		if (Nibble1.Evolucion(num, X, Y) || Nibble2.Evolucion(num, X, Y) || num == 1)
		{
			if (num < 10) AparecerNumero(X, Y, num++);
			else
			{
				Doble_Nacimiento(Nibble1, Nibble2, num, tecla);
				Nivel++;
				Cargar_Fase(Nivel);
			}
		}

		
		//CONGELA EL TIEMPO PARA UNA REACCION DEL JUGADOR
	   // delay(tpausa);

		/*LeerEventos();
		LeerPosicionPad();*/
		//    Mostrar_Posicion_JoyPad(10,10,200,200);


		/*   if( joy.Padx!=joy.Pady )
			{
		  */


		//if ((clock() - t) / CLK_TCK) > tpausa / 1000)
		if ((clock() - t)  > tpausa )
		{

			//CRECIMIENTO
			Nibble1.Crecimiento(tecla);
			if (opcion == 2) Nibble2.Crecimiento(tecla);


			/*if (joy.Padx == IZQ_) tecla = Nibble1.IZQ;
			else if (joy.Padx == DER_) tecla = Nibble1.DER;
			if (joy.Pady == ABA_) tecla = Nibble1.ABJ;
			else if (joy.Pady == ARR_) tecla = Nibble1.ARR;*/
			t = clock();

			//CAPTURAR LA TECLA PRESIONADA
			if (kbhit()) tecla = toupper(getch());
			if (!tecla) tecla = toupper(getch());


		}
		// }


	  //MUERTE
		if (Nibble1.Muerte(tecla) || Nibble2.Muerte(tecla))
		{
			Doble_Nacimiento(Nibble1, Nibble2, num, tecla);
			Cargar_Fase(Nivel);
		}


	} while (tecla != 27);

	closegraph();

	return 1;
}