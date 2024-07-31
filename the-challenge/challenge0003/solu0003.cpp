#include "graphics.h"
#include "conio.h"
#include <string>
#include <iomanip>
#include <sstream>

#define MAXX		getmaxx()
#define MAXY		getmaxy()
#define CX		(MAXX / 2) /* This combination of macros defines the center of */
#define CY		(MAXY / 2) /* the coordinates on the screen */
#define DESDEX	-10 /* Defines from which x value the graphing will begin */
#define HASTAX	10 /* Needs explanation? */
#define ZOOM	4 /* The larger it is, the greater the range of coordinates that is shown on the screen */
#define CADA	(MAXX / 10) /* For the number of values ​​that will be shown on the axes */
/* In reality, the true zoom is the combination between ZOOM, and CADA */

#define F(X) (X*2/3)+4 /* This is the function that will be graphed */
#define DEFINICION 0.001

void axis();
void draw_func();


void main()
{	
	initwindow(1024, 768, "The world of chaos in C++ - Unlimited Programming");
	axis();
	draw_func();
	getchar();
	closegraph();
}


void axis() /* This procedure draws the axes according to the values ​​of the macros */
{
	int i;
	double j;
	std::string res;

	setcolor(WHITE);
	line(0, CY, MAXX, CY);	/* Draw the X axis */
	line(CX, 0, CX, MAXY);  /* Draw the Y axis */


	settextstyle(DEFAULT_FONT, VERT_DIR, 1);
	for (i = CX - CADA, j = 0; i >= 0; i -= CADA)	/* Draw at -X */
	{
		line(i, CY - 3, i, CY + 3);
		j -= ZOOM;

		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << j;
		res = stream.str();

		setcolor(CYAN);
		outtextxy(i, CY + 5, res.c_str());
		setcolor(WHITE);
	}

	for (i = CX + CADA, j = 0; i <= MAXX; i += CADA)	/* Draw at +X */
	{
		line(i, CY - 3, i, CY + 3);
		j += ZOOM;

		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << j;
		res = stream.str();

		setcolor(CYAN);
		outtextxy(i, CY + 5, res.c_str());
		setcolor(WHITE);
	}
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	for (i = CY - CADA, j = 0; i >= 0; i -= CADA)	/* Draw at +Y */
	{
		line(CX - 3, i, CX + 3, i);
		j += ZOOM;

		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << j;
		res = stream.str();

		setcolor(CYAN);
		outtextxy(CX + 5, i, res.c_str());
		setcolor(WHITE);
	}

	for (i = CY + CADA, j = 0; i <= MAXY; i += CADA)	/* Draw at -Y */
	{
		line(CX - 3, i, CX + 3, i);
		j -= ZOOM;

		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << j;
		res = stream.str();

		setcolor(CYAN);
		outtextxy(CX + 5, i, res.c_str());
		setcolor(WHITE);
	}
	setcolor(GREEN);
	outtextxy(0, CY - 16, "-X");
	outtextxy(MAXX - 20, CY - 16, "+X");
	outtextxy(CX - 20, 0, "+Y");
	outtextxy(CX - 20, MAXY - 20, "-Y");
}

void draw_func() /* This procedure draws the function on the screen */
{
	double y, x, proporcion = CADA / ZOOM;
	for (x = DESDEX; x <= HASTAX; x += DEFINICION)
	{
		y = F(x);
		// ERROR
		putpixel(CX + x * proporcion, CY - y * proporcion, YELLOW);
	}
}