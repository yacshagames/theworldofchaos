#include <string.h>
#include <stdio.h>
#include <graphics.h>
#include <conio.h>

#define MAXX		getmaxx()
#define MAXY		getmaxy()
#define CX			(MAXX / 2) /* Esta combinacion de macros definen el centro de */
#define CY			(MAXY / 2) /* de coordenadas en la pantalla */
#define DESDEX	-10 /* Define desde que valor de x se empezara a graficar */
#define HASTAX	10 /* Necesita explicacion? */
#define ZOOM		4 /* Mientras mas grande es, mayor rango de coordenadas es mostrada eb pantalla */
#define CADA		(MAXX / 10) /* Para la cantidad de valores que seran mostrados en los ejes */
/* En realidad, el zoom verdadero es la combnacion entre ZOOM, y CADA */

#define F(X) (X*2/3)+4 /* Esta es la funcion que se graficara */
#define DEFINICION 0.001

void ejes();
void dibuja_func();


void main()
{
	int gm, gd = DETECT;
	initgraph(&gd, &gm, "");
	ejes();
	dibuja_func();
	getchar();
	closegraph();
}


void ejes() /* Este procedimento dibuja los ejes de acuerdo con los valores de las macros */
{
	register int i;
	float j;
	char res[20];

	setcolor(WHITE);
	line(0, CY, MAXX, CY);	/* Dibujar el eje X */
	line(CX, 0, CX, MAXY);  /* Dibujar el eje Y */


	settextstyle(DEFAULT_FONT, VERT_DIR, 1);
	for (i = CX - CADA, j = 0; i >= 0; i -= CADA)	/* Dibujar en -X */
	{
		line(i, CY - 3, i, CY + 3);
		j -= ZOOM;
		sprintf(res, "%.2f", j);
		setcolor(BLUE);
		outtextxy(i, CY + 5, res);
		setcolor(WHITE);
	}

	for (i = CX + CADA, j = 0; i >= 0; i += CADA)	/* Dibujar en +X */
	{
		line(i, CY - 3, i, CY + 3);
		j += ZOOM;
		sprintf(res, "%.2f", j);
		setcolor(BLUE);
		outtextxy(i, CY + 5, res);
		setcolor(WHITE);
	}
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	for (i = CY - CADA, j = 0; i >= 0; i -= CADA)	/* Dibujar en +Y */
	{
		line(CX - 3, i, CX + 3, i);
		j += ZOOM;
		sprintf(res, "%.2f", j);
		setcolor(BLUE);
		outtextxy(CX + 5, i, res);
		setcolor(WHITE);
	}

	for (i = CY + CADA, j = 0; i <= MAXY; i += CADA)	/* Dibujar en -Y */
	{
		line(CX - 3, i, CX + 3, i);
		j -= ZOOM;
		sprintf(res, "%.2f", j);
		setcolor(BLUE);
		outtextxy(CX + 5, i, res);
		setcolor(WHITE);
	}
	setcolor(GREEN);
	outtextxy(0, CY - 16, "-X");
	outtextxy(MAXX - 20, CY - 16, "+X");
	outtextxy(CX - 20, 0, "+Y");
	outtextxy(CX - 20, MAXY - 20, "-Y");
}

void dibuja_func() /* Este procedimiento dibuja la funcion en la pantalla */
{
	float y, x, proporcion = CADA / ZOOM;
	for (x = DESDEX; x <= HASTAX; x += DEFINICION)
	{
		y = F(x);
		// ERROR
		putpixel(CX + x * proporcion, CY - y * proporcion, YELLOW);
	}
}