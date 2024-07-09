#pragma once
/*****************************************************************************
GATOMANIA 3D
TIC-TAC-TOE GAME ON A 4x4x4 CUBE

programmed by:
 JOSE LUIS DE LA CRUZ LAZARO
 ramondc@hotmail.com
Pagina Web ( EL MUNDO DEL CAOS )

HISTORY...

 >> Version 2 - 25-III-2024
	- Update graphics/gato3d - Porting to VC++ 2017 using winbgi
	- The width and height of the screen can be customized from the global
	  constants maxx and maxy. And the board adapts to the new resolution
	- Fix bug that caused them to not be interleaved correctly between X and 0,
	  where sometimes two consecutive x's or two consecutive zeros appeared.
	- Using updates librarys ventanas.h and mousebgi.h

>> Version 1 - 16-XIII-1999
	- First version for Borland C++ 3.1 and Turbo C 3.0

*****************************************************************************/
#include "graphics.h"
#include "conio.h"
#include "mousebgi.h"
#include "ventanas.h"

const unsigned int maxx = 1024;
const unsigned int maxy = 768;
const unsigned int X = int( double(50 * maxx) / 640.0); //Longitud horizontal de un elemento de la cuadricula
const unsigned int Y = int( double(50 * maxy) / 480.0); //longitud vertical de un elemento de la cuadricula

///////////////////////////////////////////////////////////////////////////
int Cubo[4][4][4];

void inicializar();
int Gato3D();
int Jugar(int x, int y, int z, int figura);
int Gato2D(int Gato[4][4]);


void inicializar()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
				Cubo[i][j][k] = 2;
}


int Gato2D(int Gato[4][4])
{
	int i, j, Sx, Sy, Px, Py;
	//Sx y Sy suman los ceros
	//Px y Py es el producto de los unos
	//Sabemos que una O es un 0 y una X es un 1
	//luego si la suma de todo una fila o columna es cero gano el O
	//analogamente con el producto si es 1 gano la X

	//Revisa si se gano horizontal o vertical
	for (i = 0; i < 4; i++)
	{
		Sx = Sy = 0;
		Px = Py = 1;

		for (j = 0; j < 4; j++)
		{
			Sx += Gato[i][j];
			Px *= Gato[i][j];
			Sy += Gato[j][i];
			Py *= Gato[j][i];
		}

		if (Sx == 0 || Px == 1 || Sy == 0 || Py == 1) return 1;
	}

	//Revisa si se gano en las 2 diagonales
	Sx = Sy = 0;
	Px = Py = 1;
	for (i = 0; i < 4; i++)
	{
		Sx += Gato[i][i];
		Px *= Gato[i][i];
		Sy += Gato[3 - i][i];
		Py *= Gato[3 - i][i];
	}

	if (Sx == 0 || Px == 1 || Sy == 0 || Py == 1) return 1;
	//if( !( Sx*Sy*(Px-1)*(Py-1) ) ) return 1;

	return 0;

}

int Gato3D()
{

	//Se revisa si se gano en los planos paralelos a XY XZ e YZ respectivamente
	//es decir en 12 planos
	int Tablero[3][4][4], x, y, i;

	for (i = 0; i < 4; i++)
	{

		for (x = 0; x < 4; x++)
			for (y = 0; y < 4; y++)
			{
				Tablero[0][x][y] = Cubo[x][y][i];//XY
				Tablero[1][x][y] = Cubo[x][i][y];//XZ
				Tablero[2][x][y] = Cubo[i][x][y];//YZ
			}

		for (x = 0; x < 3; x++)
			if (Gato2D(Tablero[x]))return 1;


	}

	//Revisa si se gano en las 4 diagonales del cubo
	int S[4] = { 0,0,0,0 }, P[4] = { 1,1,1,1 }, s = 1, p = 1;

	for (i = 0; i < 4; i++)
	{
		S[0] += Cubo[i][i][i];
		P[0] *= Cubo[i][i][i];
		S[1] += Cubo[i][i][3 - i];
		P[1] *= Cubo[i][i][3 - i];
		S[2] += Cubo[3 - i][i][i];
		P[2] *= Cubo[3 - i][i][i];
		S[3] += Cubo[3 - i][i][3 - i];
		P[3] *= Cubo[3 - i][i][3 - i];
	}
	for (i = 0; i < 4; i++)
	{
		s *= S[i];
		p *= (P[i] - 1);
	}
	if (s == 0 || p == 0) return 1;

	return 0;

}


//Se ingresa una X o una O
int Jugar(int x, int y, int z, int figura)
{

	if (Cubo[x][y][z] < 2)return 0;
	else Cubo[x][y][z] = figura;

	return 1;

}

///////////////////////////////////////////////////////////////////////////
//GRAFICOS
class tablero
{
public:
	int x, y;

	//constructor
	tablero(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	void pintar_cuadricula(int color);
	bool Marcar(int i, int j, int k, int figura);
	int Dominio(int i, int j);

};


void tablero::pintar_cuadricula(int color)
{

	int m;

	setcolor(color);
	for (m = 1; m < 4; m++)
	{
		moveto(x + X * m, y);
		linerel(0, 4 * Y);
		moveto(x, y + Y * m);
		linerel(4 * X, 0);
	}
}

//Grafica un O ¢ X en el centro del elemento (x,y) de la cuadricula
bool tablero::Marcar(int i, int j, int k, int figura)
{
	//figura = 0 "dibuja un O"
	//figura = 1 "dibuja una X"

	int fil, col;

	fil = (i - x) / X;
	col = (j - y) / Y;


	if (Jugar(fil, col, k, figura))
	{
		i = x + (fil + 0.5)*X; //se toma coordenadas del centro del elemento
		j = y + (col + 0.5)*Y; //

		int r = Y / 3;

		//mocultar();

		switch (figura)
		{
		case 0:
			circle(i, j, r);
			/*sound(50);
			delay(200);
			nosound();*/
			break;
		case 1:
			line(i - r, j - r, i + r, j + r);
			line(i - r, j + r, i + r, j - r);
			/*sound(100);
			delay(200);
			nosound();*/

			break;
		}

		//mver();

		return true;
	}

	return false;
}

int tablero::Dominio(int i, int j)
{
	if ((x < i && i < (x + 4 * X)) && (y < j && j < (y + 4 * Y))) return 1;
	else return 0;
}
//////////////////////////////////////////////////////////////////////////

tablero tab[4] = { tablero(10,10),
		tablero(100 + 4 * Y,10),
		tablero(10,60 + 4 * X),
		tablero(100 + 4 * Y,60 + 4 * X) };


int Reiniciar()
{	
	cuadro(56 + 2 * X, 20 + 4 * Y, 56 + 6 * X, 50 + 4 * Y, 2);
	setcolor(WHITE);
	outtextxy(4 * X, 30 + 4 * Y, "Gatoman¡a en 3D");

	for (int i = 0; i < 4; i++)
	{

		cuadro(tab[i].x, tab[i].y, tab[i].x + 4 * Y, tab[i].y + 4 * X, 2, 2);
		tab[i].pintar_cuadricula(1);

	}

	inicializar();

	return 0;
}


int main()
{
	//int gdriver = DETECT, gmode;
	//initgraph(&gdriver, &gmode, ""); //CAMBIAR AQUI LA RUTA DE TU archivo egabgi.bgi
	
	ModoGrafico(maxx, maxy); // Activate WinBGI graphics mode with 1024x768 resolution	

	setbkmode(TRANSPARENT);

	const char *cad[2] = { "Player X wins the game",
						   "Brilliant game player O" };

	int x, y, z, n, i = 0;


	CBoton	Reset(14 + 4 * X, 80, 20, 85, "Reset game"),
			Exit(14 + 4 * X, 110, 20, 85, "Exit");

	Evento raton;

	cuadro(0, 0, maxx, maxy, 1);

	int Gano_el_juego;

	Gano_el_juego = Reiniciar();

	//mver();

	////////////////////////////////
	//Bucle principal
	//Marca una X ¢ O utilizando el mouse


	do
	{

		if (Reset.mostrar(raton))
			Gano_el_juego = Reiniciar();

		if (Exit.mostrar(raton))
			break;

		raton = MouseBGI::Detectar_click_o_tecla();

		if (raton.evento == MouseBGI::EVENTO::LBUTTON_DOWN && Gano_el_juego == 0)
		{

			x = raton.x; //capturamos posicion x del mouse sobre las coordenadas de la cuadricula
			y = raton.y; //capturamos posicion y del mouse sobre las coordenadas de la cuadricula

			for (z = 0; z < 4; z++)
				if (tab[z].Dominio(x, y))break;

			if (z < 4)
			{
				//i = (i + 1) % 2;
				setcolor(12 + i);

				if (tab[z].Marcar(x, y, z, i))
					i = (i + 1) % 2;

				if (Gato3D())
				{
					cuadro(56 + 2 * X, 20 + 4 * Y, 56 + 6 * X, 50 + 4 * Y, 1, BLACK);
					outtextxy(4 * X-20, 30 + 4 * Y, cad[i]);
					/*sound(500);
					delay(600);
					nosound();*/
					Gano_el_juego = 1;
				}
			}
		}
	} while (raton.tecla != 27);
	/////////////////////////////////

	//mocultar();	

	// CREDITS!
	setcolor(10);
	printf("\n\nGATOMANIA 3D was programmed by: ");
	setcolor(14);
	gotoxy(24,4);
	printf("Jose Luis De la Cruz Lazaro - Lima - Peru\n\n\n\n\n\n\n\n\n\n");	

	closegraph();

	return 1;
}


