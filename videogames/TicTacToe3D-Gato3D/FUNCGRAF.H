//MAS FUNCIONES GRAFICAS QUE LE FALTA GRAPHICS.H

#include "graphics.h"
//#include "mousebgi.h"  //funcion WaitRetrace()

/*
void WaitRetrace() {

  _DX = 0x03DA;

  l1: asm {
	in  al,dx;
	and al,0x08;
	jnz l1;
	  }

  l2: asm {
	in  al,dx;
	and al,0x08;
	jz  l2;
	  }
}
  */

void linea_inversa(int x1, int y1, int x2, int y2)
{
	float m;
	int x, y;

	//si x1>x2 se intercambia valores
	if (x1 > x2)
	{
		x = x1;
		x1 = x2;
		x2 = x;
	}
	//si y1>y2 se intercambia valores
	if (y1 > y2)
	{
		y = y1;
		y1 = y2;
		y2 = y;
	}

	//se nesecita x1<x2 y y1<y2
	if (x1 != x2)
	{
		m = (y2 - y1) / (float)(x2 - x1);

		for (x = x1; x <= x2; x++)
		{
			y = m * x + y1 - m * x1;
			putpixel(x, y, getpixel(x, y) ^ 15);
		}
	}
	else
		for (y = y1; y <= y2; y++)
			putpixel(x1, y, getpixel(x1, y) ^ 15);


}

void rectangulo_inverso(int x1, int y1, int x2, int y2)
{
	//WaitRetrace();
	linea_inversa(x1, y1, x1, y2);
	linea_inversa(x1, y2, x2, y2);
	linea_inversa(x2, y2, x2, y1);
	linea_inversa(x2, y1, x1, y1);
}
