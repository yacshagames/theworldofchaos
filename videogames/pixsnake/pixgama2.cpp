//final numero 2
//Villalvazo Juan
//2010

/*
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<dos.h>
*/
/////////////////////////////////////////////////////////
// Encabezados actualizados al C++ moderno
/////////////////////////////////////////////////////////
#include "conio.h" // gotoxy, clrscr
#include <stdio.h>
#include <conio.h> // _kbhit, _getch
#include <chrono>

//////////////////////////////////////////////////////////
// Funciones y deficiones no compatibles directamente 
// con WinBGIDLL y que necesitan adaptarse para ser
// implementadas correctamente
//////////////////////////////////////////////////////////
#define _NOCURSOR 0
#define BLINK 0

void _setcursortype(int tipo_cursor) {
	// Falta implementar
}

void textbackground(int color) {
	// Falta implementar
}

void delay(int msec) {
	Sleep(msec);
}

//////////////////////////////////////////////////////////
// A partir de aquí el código original ha tratado de
// no ser modificado en lo posible
// para mantener la mágia del programador original
//////////////////////////////////////////////////////////

#define up 72
#define down 80
#define left 75
#define right 77
#define esc 27

char smiley[2] = { 2, '\n' };

int m[50][80], cantidad = 0, opt = 0, i, j, col, 
sx = 40, sy = 18,//sx = 40, sy = 9,
ren, a = 0, ax = 0,
velocidad = 0, truco = 0, gameover = 0, nivel = 1,
ci = 10, ri = 10, rf = 41, cf = 72, //ci = 1, ri = 1, rf = 30, cf = 80,
op = 0, op2 = 0, __y1 = 0, x1 = 0,
band = 0, limite = 100, canibal = 0;

// habilitar
//struct time t;
std::chrono::time_point<std::chrono::steady_clock>  t;

struct cuerpo {
	int x;
	int y;
	cuerpo *sig;
	cuerpo *ant;
};

typedef cuerpo* snake;

snake cabeza;
snake princi = NULL;
snake cola = NULL;
snake temp = NULL;
snake aux = NULL;
////////FUNCIONES/////////////////////////
int inicio(void);
void crea(void);
void asteriscos(int);
void fondo(void);
void dinamicos(void);
void puertac(void);
void puertaa(void);
void puertal(void);
//void restart(void); // Función no implementada en el código Original
void pantfinal(void);
/////////////////////////////////////////


int main(void)
{

	//char cont[3]; // no se usa esta variable
	int pa = 0, pc = 0, continu = 0;
	
	do

	{


		opt = inicio();

		switch (opt)
		{

		case 1: 
		
			t = std::chrono::steady_clock::now();

			_setcursortype(_NOCURSOR);

			////////////inicializar la metriz///////////////////

			for (i = 0; i < 50; i++)
			{
				for (j = 0; j < 80; j++)
				{
					m[i][j] = 0;
				}
			}
			///////////////////////////////////////////////////
			///////////Fondo estatico//////////////////////

			fondo();




			////////////////Crear asteriscos///////////////////
			asteriscos(18);
			///////////////////////////////////////////////////
			do
			{
				limite--;
				if (band == 10)
				{
					band = band + 50; gotoxy(23, 6); textcolor(LIGHTMAGENTA + BLINK); printf("Bienvenido al segundo nivel!"); //gotoxy(32, 6); clreol();
					asteriscos(cantidad + 16); velocidad = 50;					
					nivel = 2;
				}
				if (band == 75)
				{
					band = band + 50; gotoxy(23, 6); textcolor(LIGHTCYAN + BLINK); printf("Bienvenido al tercel nivel!"); //gotoxy(32, 6); clreol();
					asteriscos(cantidad + 20); velocidad = 100;					
					nivel = 3;
				}
				if (band == 145)
				{
					band = band + 50; gotoxy(23, 6); textcolor(LIGHTGREEN + BLINK); printf("Tu puedes! ultimo nivel :D"); //gotoxy(32, 6); clreol();
					asteriscos(cantidad + 100); velocidad = 150;					
					nivel = 4;
				}
				if (band == 220)
				{
					op = 27;


				}


				//////////////////////////////////////////////////
				crea();
				//////////////////////////////////////////////
				if (sy < 18 && pc == 0)
				{
					puertac();
				}




				if (sy == 19 && pa == 0)
				{
					puertaa();
				}


				if (sy == 25 || pa == 1) {
					puertal();
					pa = 1; pc = 1;
				}

				////////////////////////////////////////////////////////////


				if (m[sy - 1][sx - 1] != 0)//si esta tocando
				{
					textcolor(m[sy - 1][sx - 1]);
					m[sy - 1][sx - 1] = 0; limite = limite + 85;
					band++;


				}
				else
				{
					if (a != 0) {
						cola = temp->sig;
						cola->ant = temp->ant;
						free(temp);
						temp = cola;
					}


				}


				///////////////////////////////////////////////////////////////////


				///////////////////////////Imprimir snake/////////////////////////////////////
				
				gotoxy(princi->x, princi->y); printf(smiley); delay((200 - velocidad) + truco);


				gotoxy(cola->x, cola->y); printf(" "); a = a + 1;
				///////////////////////////////////////////////////////////////////////
				//////////////////////////por si se come a si misma//////////////////////////////


				// Se corrige bug que cerraba el programa en el caso que
				// princi->ant sea NULL
				if (princi->ant)
					aux = princi->ant->ant;
				else
					aux = NULL;

				while (aux != NULL)
				{
					if (princi->x == aux->x&&princi->y == aux->y)
					{

						op = 27;

						canibal = 1;

					}

					aux = aux->ant;

				}






				///////////Condiciones para el muro/////////////////////////////////////
				 /*if(sy==37&&(sx>=39&&sx<=70))
					  {
					  op=27 ;
					  canibal=1;
					  }
				   */
				   /////////////////////////////////////////////////////////////////////////

				dinamicos();			

				if (_kbhit()) {
					op = toupper(_getch());

					if( op > 128)
						op = toupper(_getch());
					
				}
		
				switch (op) {

				case up: 
					
					if (sy < rf) {
						sy--; 
						cabeza->y = sy;
					} else {
						gameover = 1;
						op = 27;
					}						 
					break;
				case down: 

					if (sy > ri) {
						sy++; 
						cabeza->y = sy;
					} else { 
						gameover = 1;
						op = 27;
					}
					break;
				case left: 
					if (sx < cf) {
						sx--;
						cabeza->x = sx;
					} else {
						gameover = 1;
						op = 27;
					}
					break;
				case right: 
					if (sx > ci) {
						sx++;
						cabeza->x = sx;
					} else {
						gameover = 1;
						op = 27;
					}
					break;

				case '1': 
					if (truco == 0)
						truco = 120;

					op = 0; break;

				case '2':
					velocidad = velocidad + 100;
					op = 0; 
					break;

				}


				gotoxy(0, 0); printf("VIDA RESTANTE:%d ", limite);
				if (limite < 1)//12.5 ciclos son aprox 1 seg en un procesador de 2 gigahertz
				{
					op = 27;
				}


			} while (op != esc);

			if (op == esc)
			{

				pantfinal();

			}

			cantidad = 0; opt = 0; i = 0; j = 0; a = 0, col = 0; 
			ren = 0; velocidad = 0; truco = 0; gameover = 0; nivel = 1; 
			//ci = 10; ri = 10; rf = 41; cf = 70;
			sx = 40; sy = 18;
			op = 0; op2 = 0; __y1 = 0; x1 = 0;
			band = 0, limite = 100, pa = 0, pc = 0, opt = 0, continu = 0;

			///////Para limpiar a la serpiente XD///////////////
			while (temp->sig != NULL)
			{
				cola = temp->sig;
				cola->ant = temp->ant;
				free(temp);
				temp = cola;
				aux = NULL;
			}
			///////////////////////////////////////////////////
			clrscr();
			break;

		case 2:

			gotoxy(15, 28); printf("Salir?");
			gotoxy(15, 30); printf("SI:1 NO:2:");
			continu = _getch() == '1' ? 1 : 2;
			clrscr();
			break;
		}

	} while (continu != 1);

	return 1;
}



/***********Funcion Fondo**************************************/
void fondo()
{
	textbackground(BLACK); clrscr();
	
	for (col = ci; col < cf; col++)
	{
		gotoxy(col, ri); printf("Í");
		gotoxy(col, rf); printf("Í");
	}
	for (ren = ri; ren < rf; ren++)
	{
		gotoxy(ci, ren); printf("º");
		gotoxy(cf, ren); printf("º");

	}

	gotoxy(ci, ri); printf("É");
	gotoxy(ci, rf); printf("È");
	gotoxy(cf, ci); printf("»");
	gotoxy(cf, rf); printf("¼");

	gotoxy(32, 1); printf("AYUDA");
	gotoxy(13, 3); printf("Pulsar 1=Truco:Disminuir velocidad(puede utilizarlo una vez)");
	gotoxy(13, 4); printf("Pulsar 2=Truco:Aumentar velocidad (Bajo su propio riesgo!!!)");
	gotoxy(1, 10); printf("CONTROLES");
	gotoxy(1, 14); printf("=ARRIBA");
	gotoxy(1, 15); printf("=ABAJO");
	gotoxy(1, 16); printf(">=DELANTE");
	gotoxy(1, 17); printf("<=ATRAS");
	textcolor(LIGHTGREEN);
	gotoxy(35, 6); printf("PIXSNAKE 2010");
	gotoxy(cf + 2, 22); printf("OBJETIVO:");
	gotoxy(cf + 2, 23); printf("TENER 220");
	gotoxy(cf + 3, 24); printf(" PUNTOS  ");

}
/***********Funcion asteriscos*********************************/

void asteriscos(int n)
{
	int k, c = 0, r = 0, color = 0, pass = 1;
	randomize();
	for (k = 0; k < n; k++)
	{

		do {
			pass = 1;
			c = random(59) + 11;
			r = random(29) + 11;


			if ((r == 17 && (c >= 19 && c <= 60)) ||
				(r == 18 && (c >= 19 && c <= 60)) ||
				(r == 19 && (c >= 19 && c <= 60)) ||
				(r == 20 && (c >= 19 && c <= 60)) ||
				(r == 21 && (c >= 35 && c <= 44)) ||
				(r == 21 && (c >= 35 && c <= 44)) ||
				(r == 22 && (c >= 35 && c <= 44)) ||
				(r == 23 && (c >= 35 && c <= 44)) ||
				(r == 24 && (c >= 35 && c <= 44)) ||
				(r == 25 && (c >= 35 && c <= 44)) ||
				(r == 26 && (c >= 35 && c <= 44)) ||
				(r == 27 && (c >= 35 && c <= 44)) ||
				(r == 28 && (c >= 35 && c <= 44)))
				/*||()||()||()||()||()||()||()||()||
				()||()||()||()||()||()||()||()||()||
				()||()||()||()||()||()||()||()||()||
				()||()||()||()||()||()||()||()||()||
				()||()||()||()||()||()||()||()||()||
				()||())*/
			{

				pass = 0;//Para asegurarme que los asteriscos no aparezcan en el muro

			}


		} while (pass == 0);


		color = random(13) + 2;
		gotoxy(c, r); textcolor(color);
		printf("*");
		m[r - 1][c - 1] = color;
	}
}

/**************************************************************/
/**********Funcion pantfinal*************************************/

void pantfinal()
{

	if (limite < 10)
	{
		clrscr();
		_setcursortype(_NOCURSOR);
		gotoxy(10, 5); printf("SE TE ACABO LA VIDA!!!");
		gotoxy(10, 10); printf("MAXIMO PUNTAJE:%d", band); delay(1500);
		gotoxy(15, 30); printf("Pulse ENTER para continuar!"); _getch();
	}
	else
	{
		if (band == 220)
		{
			clrscr();
			_setcursortype(_NOCURSOR);
			gotoxy(10, 5); printf("FELICITACIONES GANASTE!!!");
			gotoxy(10, 10); printf("MAXIMO PUNTAJE:%d", band); delay(1500);
			gotoxy(15, 30); printf("Pulse ENTER para continuar!"); _getch();
		}
		else

			if (op == 27 && gameover == 0 && canibal == 0)
			{
				clrscr();
				_setcursortype(_NOCURSOR);
				gotoxy(10, 5); printf("USTED SALIO DEL JUEGO :(");
				gotoxy(10, 10); printf("MAXIMO PUNTAJE:%d", band); delay(1500);
				gotoxy(15, 30); printf("Pulse ENTER para continuar!"); _getch();
			}
			else
			{
				clrscr();
				_setcursortype(_NOCURSOR);
				gotoxy(10, 5); printf("GAME OVER TOCASTE PARTES INDEVIDAS XD!!!");
				gotoxy(10, 10); printf("MAXIMO PUNTAJE:%d", band); delay(1500);
				gotoxy(15, 30); printf("Pulse ENTER para continuar!"); _getch();
				canibal = 0;
			}


	}

}
/**************************************************************/
/**********************Inicio**********************************/

int inicio(void)
{
	int xx = 1, opti = 0;
	do {
		clrscr();
		printf("Selecciona opcion\n1.-Juego Nuevo\n2.-Salir\n");
		do {
			gotoxy(xx, 5); printf("---****---*****--*----*-..######..##....##....###....##....##.########"); delay(1);
			gotoxy(xx, 6); printf("---*---*----*-----*--*--.##....##.###...##...##.##...##...##..##......"); delay(1);
			gotoxy(xx, 7); printf("---*---*----*------**---.##.......####..##..##...##..##..##...##......"); delay(1);
			gotoxy(xx, 8); printf("---****-----*------**---..######..##.##.##.##.....##.#####....######.."); delay(1);
			gotoxy(xx, 9); printf("---*--------*-----*--*--.......##.##..####.#########.##..##...##......"); delay(1);
			gotoxy(xx, 10); printf("---*--------*----*----*-.##....##.##...###.##.....##.##...##..##......"); delay(1);
			gotoxy(xx, 11); printf("---*------*****-*------*..######..##....##.##.....##.##....##.########"); delay(1);

			xx++;
		} while (xx < 120);
		gotoxy(1, 13); printf("RIVERJUEGOS-->:");
		xx = 1;
		opti = _getch()=='1' ? 1 : 2;
		
	} while (opti == 0);

	return opti;

}

/**************************************************************/

void crea(void)
{
	cabeza = (snake)malloc(sizeof(cuerpo));
	cabeza->x = sx;
	cabeza->y = sy;
	cabeza->sig = NULL;
	cabeza->ant = NULL;



	if (temp == NULL) {


		princi = cabeza;
		temp = cabeza;
		cola = cabeza;

	}

	else {

		cabeza->ant = princi;
		princi->sig = cabeza;
		princi = cabeza;


	}


}
/****************************************************************/

void dinamicos(void)
{
	textcolor(WHITE); gotoxy(15, 48); printf("Nivel:%d", nivel);
	textcolor(WHITE); gotoxy(33, 48); printf("Puntuacion:%d ", band);
	
	// Mejora en la obtención del tiempo usando el moderno y mas preciso chrono
	// disponible desde C++11
	auto elapsed_time =  std::chrono::steady_clock::now() - t;
	auto h = std::chrono::duration_cast<std::chrono::hours>(elapsed_time);
	elapsed_time -= h;
	auto m = std::chrono::duration_cast<std::chrono::minutes>(elapsed_time);
	elapsed_time -= m;
	auto s = std::chrono::duration_cast<std::chrono::seconds>(elapsed_time);
	elapsed_time -= s;
	auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time);	
	textcolor(WHITE); gotoxy(55, 48); printf("Tiempo:  %2d:%2d:%2d:%2d", 
		static_cast<int>(h.count()), 
		static_cast<int>(m.count()), 
		static_cast<int>(s.count()), 
		static_cast<int>(msec.count()));
}
/*******************************************************************/

void puertac(void)
{

	gotoxy(18, 7); printf(" ========================================== ");
	gotoxy(18, 8); printf("|x x x x x x     Bienvenido!   x x x x x x |");
	gotoxy(18, 9); printf("| '   ï   .                     u   +   3  |");
	gotoxy(18, 10); printf(" ================          ================ ");
	gotoxy(35, 11); printf("|        |");
	gotoxy(35, 12); printf("|        |");
	gotoxy(35, 13); printf("|        |");
	gotoxy(35, 14); printf("|        |");
	gotoxy(35, 15); printf("| Puerta |");
	gotoxy(35, 16); printf("|   ||   |");
	gotoxy(35, 17); printf("|   VV   |");
	gotoxy(35, 18); printf(" -------- ");




}
/**********************************************************************/
void puertaa(void)
{

	gotoxy(18, 7); printf(" ========================================== ");
	gotoxy(18, 8); printf("|x x x x x x     Bienvenido!   x x x x x x |");
	gotoxy(18, 9); printf("| '   ï   .                     u   +   3  |");
	gotoxy(18, 10); printf(" ================          ================ ");
	gotoxy(35, 11); printf("|        |");
	gotoxy(35, 12); printf("|        |");
	gotoxy(35, 13); printf("|        |");
	gotoxy(35, 14); printf("|        |");
	gotoxy(35, 15); printf("|Abierto!|");
	gotoxy(35, 16); printf("|        |");
	gotoxy(35, 17); printf("|        |");
	gotoxy(35, 18); printf("1        1");
	gotoxy(35, 19); printf("1        1");
	gotoxy(35, 20); printf("1        1");
	gotoxy(35, 21); printf("1        1");
	gotoxy(35, 22); printf("1        1");
	gotoxy(35, 23); printf("1        1");
	gotoxy(35, 24); printf("1        1");
}
/*************************************************************************/
void puertal(void)
{

	gotoxy(18, 7); printf(" ========================================== ");
	gotoxy(18, 8); printf("|x x x x x xCuidado con la puerta! x x x x |");
	gotoxy(18, 9); printf("| '   ï   .                         +   3  |");
	gotoxy(18, 10); printf(" ================          ================ ");
	gotoxy(35, 11); printf("|        |");
	gotoxy(35, 12); printf("|        |");
	gotoxy(35, 13); printf("|        |");
	gotoxy(35, 14); printf("|        |");
	gotoxy(35, 15); printf("|        |");
	gotoxy(35, 16); printf("|        |");
	gotoxy(35, 17); printf("|CERRADO!|");
	gotoxy(35, 18); printf(" -------- ");
	gotoxy(35, 19); printf("(        )");
	gotoxy(35, 20); printf("( TUNEL  )");
	gotoxy(35, 21); printf("(        )");
	gotoxy(35, 22); printf("(        )");
	gotoxy(35, 23); printf("(        )");
	gotoxy(35, 24); printf("(        )");
	gotoxy(35, 25); printf("(        )");

}