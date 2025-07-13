//final numero 2
//Villalvazo Juan
//2010

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<dos.h>
#define up 72
#define down 80
#define left 75
#define right 77
#define esc 27



int m[50][80], cantidad = 0, opt = 0, i, j, col, sx = 40, sy = 9, ren, a = 0, ax = 0, velocidad = 0, truco = 0, gameover = 0, nivel = 1, ci = 1, ri = 1, rf = 30, cf = 80, op = 0, op2 = 0, y1 = 0, x1 = 0, band = 0, limite = 100, canibal = 0;
struct time t;
typedef struct cuerpo {

	int x;

	int y;

	struct cuerpo *sig;
	struct cuerpo *ant;
}body;

typedef body *snake;

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
void restart(void);
void pantfinal(void);
/////////////////////////////////////////


void main(void)
{

	char cont[3];
	int pa = 0, pc = 0, continu = 0;

	do

	{


		opt = inicio();

		switch (opt)
		{

		case 1: gettime(&t); t.ti_sec = 0; t.ti_hour = 0; t.ti_min = 0;
			t.ti_hund = 0; settime(&t);
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
					band = band + 50; gotoxy(23, 7); textcolor(WHITE + BLINK); cprintf("Bienvenido al segundo nivel!"); gotoxy(32, 6); clreol();
					asteriscos(cantidad + 16); velocidad = 10;
					nivel = 2;
				}
				if (band == 75)
				{
					band = band + 50; gotoxy(23, 7); textcolor(WHITE + BLINK); cprintf("Bienvenido al tercel nivel!"); gotoxy(32, 6); clreol();
					asteriscos(cantidad + 20); velocidad = 40;
					nivel = 3;
				}
				if (band == 145)
				{
					band = band + 50; gotoxy(23, 7); textcolor(WHITE + BLINK); cprintf("Tu puedes! ultimo nivel :D"); gotoxy(32, 6); clreol();
					asteriscos(cantidad + 100); velocidad = 70;
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

				gotoxy(princi->x, princi->y); cprintf("@"); delay((200 - velocidad) + truco);


				gotoxy(cola->x, cola->y); cprintf(" "); a = a + 1;
				///////////////////////////////////////////////////////////////////////
				//////////////////////////por si se come a si misma//////////////////////////////

				aux = princi->ant->ant;
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

				if (kbhit())

					op = getch();
				switch (op)
				{
				case up: if (sy > 30) { sy--; cabeza->y = sy; }
						 else { gameover = 1; op = 27; }
						 break;
				case down: if (sy < 10) { sy++; cabeza->y = sy; }
						   else { gameover = 1; op = 27; }
						   break;
				case left: if (sx > 80) { sx--; cabeza->x = sx; }
						   else { gameover = 1; op = 27; }
						   break;
				case right: if (sx < 10) { sx++; cabeza->x = sx; }
							else { gameover = 1; op = 27; }
							break;



				case '1': if (truco == 0)
				{
					truco = 120;
				}

						  op = 0; break;

				case '2':
					velocidad = velocidad + 20;
					op = 0; break;

				}



				gotoxy(0, 0); cprintf("VIDA RESTANTE:%d ", limite);
				if (limite < 1)//12.5 ciclos son aprox 1 seg en un procesador de 2 gigahertz
				{
					op = 27;
				}


			} while (op != esc);

			if (op == esc)
			{

				pantfinal();

			}
			cantidad = 0; opt = 0; i = 0; j = 0; a = 0, col = 0; ren = 0; velocidad = 0; truco = 0; gameover = 0; nivel = 1; ci = 10; ri = 10; rf = 40; cf = 70; sy = 18; sx = 40; op = 0; op2 = 0; y1 = 0; x1 = 0; band = 0, limite = 100, pa = 0, pc = 0, opt = 0, continu = 0;

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

			gotoxy(15, 28); cprintf("Salir?");
			gotoxy(15, 30); cprintf("SI:1NO:2 \n:"); flushall(); gets(cont);
			continu = atoi(cont);
			clrscr();
			break;
		}

	} while (continu != 1);


}









/***********Funcion Fondo**************************************/
void fondo()
{
	textbackground(BLACK); clrscr();

	for (col = ci; col < cf; col++)
	{
		gotoxy(col, ri); cprintf("Í");
		gotoxy(col, rf); cprintf("Í");
	}
	for (ren = ri; ren < rf; ren++)
	{
		gotoxy(ci, ren); cprintf("º");
		gotoxy(cf, ren); cprintf("º");

	}




	gotoxy(10, 10); cprintf("É");
	gotoxy(10, 30); cprintf("È");
	gotoxy(80, 10); cprintf("»");
	gotoxy(80, 30); cprintf("¼");

	gotoxy(32, 1); cprintf("AYUDA");
	gotoxy(13, 3); cprintf("Pulsar 1=Truco:Disminuir velocidad(puede utilizarlo una vez)");
	gotoxy(13, 4); cprintf("Pulsar 2=Truco:Aumentar velocidad (Bajo su propio riesgo!!!)");
	gotoxy(1, 10); cprintf("CONTROLES");
	gotoxy(1, 14); cprintf("=ARRIBA");
	gotoxy(1, 15); cprintf("=ABAJO");
	gotoxy(1, 16); cprintf(">=DELANTE");
	gotoxy(1, 17); cprintf("<=ATRAS");
	gotoxy(35, 9); cprintf("PIXSNAKE 2010");
	gotoxy(71, 22); cprintf("OBJETIVO:");
	gotoxy(71, 23); cprintf("TENER 220");
	gotoxy(72, 24); cprintf(" PUNTOS  ");;

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


			if ((r == 17 && (c >= 19 && c <= 60)) || (r == 18 && (c >= 19 && c <= 60)) || (r == 19 && (c >= 19 && c <= 60)) || (r == 20 && (c >= 19 && c <= 60)) || (r == 21 && (c >= 35 && c <= 44)) || (r == 21 && (c >= 35 && c <= 44)) || (r == 22 && (c >= 35 && c <= 44)) || (r == 23 && (c >= 35 && c <= 44)) || (r == 24 && (c >= 35 && c <= 44)) || (r == 25 && (c >= 35 && c <= 44)) || (r == 26 && (c >= 35 && c <= 44)) || (r == 27 && (c >= 35 && c <= 44)) || (r == 28 && (c >= 35 && c <= 44)))/*||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||()||())*/
			{

				pass = 0;//Para asegurarme que los asteriscos no aparezcan en el muro

			}


		} while (pass == 0);


		color = random(13) + 2;
		gotoxy(c, r); textcolor(color);
		cprintf("*");
		m[r - 1][c - 1] = color;
	}
}

/**************************************************************/
/**********Funcion pantfinal*************************************/

void pantfinal()
{
	char dummy[5];


	if (limite < 10)
	{
		clrscr();
		_setcursortype(_NOCURSOR);
		gotoxy(10, 5); cprintf("SE TE ACABO LA VIDA!!!");
		gotoxy(10, 10); cprintf("MAXIMO PUNTAJE:%d", band); delay(1500);
		gotoxy(15, 30); cprintf("Pulse ENTER para continuar!"); flushall(); gets(dummy);
	}
	else
	{
		if (band == 220)
		{
			clrscr();
			_setcursortype(_NOCURSOR);
			gotoxy(10, 5); cprintf("FELICITACIONES GANASTE!!!");
			gotoxy(10, 10); cprintf("MAXIMO PUNTAJE:%d", band); delay(1500);
			gotoxy(15, 30); cprintf("Pulse ENTER para continuar!"); flushall(); gets(dummy);
		}
		else

			if (op == 27 && gameover == 0 && canibal == 0)
			{
				clrscr();
				_setcursortype(_NOCURSOR);
				gotoxy(10, 5); cprintf("USTED SALIO DEL JUEGO :(");
				gotoxy(10, 10); cprintf("MAXIMO PUNTAJE:%d", band); delay(1500);
				gotoxy(15, 30); cprintf("Pulse ENTER para continuar!"); flushall(); gets(dummy);
			}
			else
			{
				clrscr();
				_setcursortype(_NOCURSOR);
				gotoxy(10, 5); cprintf("GAME OVER TOCASTE PARTES INDEVIDAS XD!!!");
				gotoxy(10, 10); cprintf("MAXIMO PUNTAJE:%d", band); delay(1500);
				gotoxy(15, 30); cprintf("Pulse ENTER para continuar!"); flushall(); gets(dummy);
				canibal = 0;
			}


	}

}
/**************************************************************/
/**********************Inicio**********************************/

int inicio(void)
{
	char opi[2];
	int xx = 1, opti = 0;
	do {
		clrscr();
		printf("Selecciona opcion\n1.-Juego Nuevo\n2.-Salir\n");

		do {
			gotoxy(xx, 5); printf("---****---*****--*----*-..######..##....##....###....##....##.########"); delay(4);
			gotoxy(xx, 6); printf("---*---*----*-----*--*--.##....##.###...##...##.##...##...##..##......"); delay(4);
			gotoxy(xx, 7); printf("---*---*----*------**---.##.......####..##..##...##..##..##...##......"); delay(4);
			gotoxy(xx, 8); printf("---****-----*------**---..######..##.##.##.##.....##.#####....######.."); delay(4);
			gotoxy(xx, 9); printf("---*--------*-----*--*--.......##.##..####.#########.##..##...##......"); delay(4);
			gotoxy(xx, 10); printf("---*--------*----*----*-.##....##.##...###.##.....##.##...##..##......"); delay(4);
			gotoxy(xx, 11); printf("---*------*****-*------*..######..##....##.##.....##.##....##.########"); delay(4);

			xx++;
		} while (xx < 81);
		gotoxy(1, 55); cprintf("RIVERJUEGOS-->:");
		xx = 1;
		flushall(); gets(opi);
		opti = atoi(opi);
	} while (opti == 0);

	return opti;

}

/**************************************************************/

void crea(void)
{
	cabeza = (snake)malloc(sizeof(body));
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
	textcolor(WHITE); gotoxy(15, 48); cprintf("Nivel:%d", nivel);
	textcolor(WHITE); gotoxy(33, 48); cprintf("Puntuacion:%d ", band);
	textcolor(WHITE); gettime(&t); gotoxy(55, 48); cprintf("Tiempo:  %2d:%2d:%2d:%2d", t.ti_hour, t.ti_min, t.ti_sec, t.ti_hund);
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