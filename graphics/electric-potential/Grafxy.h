/*********************************************************************
GRAFXY.H

Plot points of a function on the screen, in the specified Cartesian
plane region.

The screen is taken as if it were the specified region of the
Cartesian plane.

Developed by:

	JOSE LUIS DE LA CRUZ LAZARO
	contact@theworldofchaos.com

	YACSHA - Software & Desing, since 1999, Lima-Peru
	>> The World of Chaos - EL MUNDO DEL CAOS - Unlimited Programming
	www.theworldofchaos.com

LICENSE
	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

HISTORY...

>> Version 2.1 - 30-III-2024
	- The Grafxy class is improved to draw directly in memory, using
	  bitmaps and putimage, instead of using the putpixel function,
	  which is quite slow. Considerably increasing the program's
	  performance in time

>> Version 2 - 26-III-2024
	- Update graphics/gxydemo - Porting to VC++ 2017 using winbgi
	- grafxy and grafxya they are merged in grafxy, for better maintenance
	- Added define USING_RSF that allows including or excluding the rsf.h
	  library. If rsf.h is not needed, its definition can be ignored.

Version 1.8 -> 24-Agosto-2000
-Se arregla parcialmente el error de que cuando la función se salia de la ventana
 marco y despues volvia entrar, se unia con una linea el punto de salida
 y el punto de entrada.

Version 1.7 -> 15/Mayo/2000
-Se dividio grafxy en:
 grafxy (grafxy basico) que contiene las funciones mas usadas.
 grafxya (grafxy avanzado) que contiene funciones que complementan a grafxy
-Se elimina el trabajo con vectores para darle mayor velocidad a la
 transformacion
-se eliminan funciones que nunca son usadas, y se agiliza el proceso de
 transformacion creando constantes ( ki, kj ).
-La funcion CFungraf pasa a formar parte de grafxya

Version 1.65 -> 20/09/1999
- Graficar function is added: It allows graphing a function on the drawn axes,
  this function is processed from a text string using the syntactic
  function recognizer rsf.h
- conver function is added: Converts a vector R of real coordinates to a vector M 
  of integer coordinates, relative to the screen size
- punto function is improved: Which now works with vectors: Draw a point that 
  represents point P in the rectangular region specified by II and SD
  and paints it the color specified in color

Version 1.6 -> 11/08/1999
-Se modifica la clase CRegionXY, añadiendo las variables miembro
 (Imin,Jmin,Imax,Jmax) que representan las coordenadas de una
 pantalla virtual, donde se graficaran los puntos (estas coordenadas
 son en pixels).
-Se modifico todas las funciones, para que trabajen con las nuevas variables.
-Se modifica la funcion miembro Ejes(), ahora utiliza sprintf para convertir
 un numero float a cadena de texto

Version 1.5 -> 25/07/99

Se añade la funcion Conectar() para conectar los puntos de la grafica

Version 1.4 -> 23/05/99

Se acoplo la cabecera ifuncade a grafxy, para graficar funciones instantaneamente
Se añade la funcion Ejes() para graficar los ejes

Version 1.3 -> 10/04/99

Se adapto todas las funciones a la clase CRegionXY

Version 1.2 -> 7/12/98

Funcion:
	converl() //Converitdor de longitudes

Version 1.1 -> 27/11/98

Funcion:
	autoini()

Version 1.0 -> 26/11/98

**********************************************************************/
//#include "graphics.h"
#include "vector.h"

#ifdef USING_RSF
#include "rsf.h"
#endif

#define CONECTAR 1
#define NOCONECTAR 0

class CRegionXY
{

protected:

	//coordenadas de la region XY, (VALOR EN COORDENAS REALES)
	double Xmin;
	double Xmax;
	double Ymin;
	double Ymax;

	//VENTANA MARCO
	//coordenadas de la ventana donde se mostrara el grafico (VALOR EN PIXELES)
	int Imin;
	int Imax;
	int Jmin;
	int Jmax;

	double ki, kj; //constanstes utilizadas en la transformacion

public:
	//constructor
	CRegionXY(double XMIN, double XMAX, double YMIN, double YMAX) :
		CRegionXY::CRegionXY(XMIN, XMAX, YMIN, YMAX,
			0, 0, getmaxx(), getmaxy())
	{
		/*Xmin=XMIN;
		Xmax=XMAX;
		Ymin=YMIN;
		Ymax=YMAX;
		Imin=0;
		Imax=getmaxx();
		Jmin=0;
		Jmax=getmaxy();
		ki=(Imax-Imin)/(Xmax-Xmin);
		kj=(Jmax-Jmin)/(Ymax-Ymin);
		*/
	

	}

	CRegionXY(double XMIN, double XMAX, double YMIN, double YMAX,
		int IMIN, int JMIN, int IMAX, int  JMAX)
	{
		Xmin = XMIN;
		Xmax = XMAX;
		Ymin = YMIN;
		Ymax = YMAX;
		Imin = IMIN;
		Jmin = JMIN;
		Imax = IMAX;
		Jmax = JMAX;
		ki = (Imax - Imin) / (Xmax - Xmin);
		kj = (Jmax - Jmin) / (Ymax - Ymin);

		bmpScreen.bmHeight = (JMAX - JMIN)+1;
		bmpScreen.bmWidth = (IMAX - IMIN)+1;
		bmpScreen.bmWidthBytes = sizeof(unsigned int) * bmpScreen.bmWidth;
		bmpScreen.bmBits = new unsigned int[bmpScreen.bmHeight*bmpScreen.bmWidth];
	}

	~CRegionXY() {
		if (bmpScreen.bmBits)
			delete bmpScreen.bmBits;
	}

	double xmin() const { return Xmin; };
	double xmax() const { return Xmax; };
	double ymin() const { return Ymin; };
	double ymax() const { return Ymax; };

	//Funciones Miembro
	void transfor(int &i, int &j, double x, double y);
	vector conver(vector P) const;
	vector converl(vector R);
	void punto(vector P, int color, char conectar) const;
	void punto(double x, double y, int color, char conectar) const;
	void punto(double x, double y, int color, double minX, double maxX, double minY, double maxY) const;
#ifdef USING_RSF
	void Graficar(char* Formula, char conectar, char color, float Particion);
#endif
	void Ejes();

	void draw();

private:
	void putpixel(int x, int y, int color) const;

private:
	unsigned int anchoScreen;
	BITMAP bmpScreen;

};//fin de la clase CRegionXY

//Convierte un punto de coordenadas reales (x,y) , a un pixel de
//coordenadas enteras (i,j) respecto al origen grafico de la pantalla
//NOTA: el valor de i y j se sobreescribiran
void CRegionXY::transfor(int &i, int &j, double x, double y)
{
	i = Imin + (x - Xmin)*ki + 1;//Transformación de real a entero x-->i
	j = Jmax - (y - Ymin)*kj + 1;//Transformación de real a entero y-->j
}


//Convierte un vector R de coordenadas reales a un vector M de
//coordenadas enteras, relativas al tamaño de la pantalla
//II=(0,0) SD=(getmaxx,getmaxy)
//      |          |
//    entero      entero
//
//Donde la pantalla representara a una región rectangular R donde
//las esquinas son los vectores de coordenadas reales II y SD;
//II=InferiorIzquierda de la pantalla
//SD=SuperiorDerecha de la pantalla
//En resumen la Region R se transforma a una region rectangular W pero
//de coordenadas enteras que encaja en la pantalla

/*
vector CRegionXY::conver(vector P)
{

return vector( (P.x-Xmin)*getmaxx()/(Xmax-Xmin)+1, 	//Conversion de real a entero x-->m
		getmaxy()-(P.y-Ymin)*getmaxy()/(Ymax-Ymin)+1 );//Conversion de real a entero y-->n
}
*/

vector CRegionXY::conver(vector P) const
{

	return vector((P.x - Xmin)*(Imax - Imin) / (Xmax - Xmin) + Imin + 1, 	//Conversion de real a entero x-->m
		Jmax - (P.y - Ymin)*(Jmax - Jmin) / (Ymax - Ymin) + 1);//Conversion de real a entero y-->n
}


vector CRegionXY::converl(vector R)
{
	vector M;
	M = conver(R);
	M = vector(M.x, getmaxy() - M.y);

	return M;
}

//Grafica un punto que representa al punto P en la region rectangular
//especificada por II y SD y lo pinta del color especificado en color

void CRegionXY::punto(vector P, int color, char conectar = 0) const
{
	vector M = conver(P);

	if (Imin < M.x && M.x < Imax && Jmin < M.y && M.y < Jmax) //para que no se pinte fuera de la ventana marco
	{
		if (conectar)
		{
			if (getcolor() != color)moveto(M.x, M.y);
			setcolor(color);
			lineto(M.x, M.y); //conecta los puntos
		}
		else
			putpixel(M.x, M.y, color);  //grafica la funcion en pantalla

	}

}

void CRegionXY::punto(double x, double y, int color, char conectar = 0) const
{
	punto(vector(x, y), color, conectar);
}


//Igual que la funcion anterior pero sin vectores
//Grafica un punto en la pantalla pero tomando coordenadas reales (x,y)
//y un color especificado en color, donde su dominio es la region
//rectangular de esquinas:
//inferior izquierda (minX,minY) hasta superior derecha (maxX,maxY)

void CRegionXY::punto(double x, double y, int color, double minX, double maxX, double minY, double maxY) const {
	//Se establece las particiones de la pantalla (RANGO DE VISION DE LA FUNCION)
	//desde (minX,minY) hasta (maxX,maxY)
	int m, n;

	m = (x - minX)*getmaxx() / (maxX - minX) + 1; 	//Conversion de real a entero x-->m
	n = getmaxy() - (y - minY)*getmaxy() / (maxY - minY) + 1;//Conversion de real a entero y-->n

	this->putpixel(m, n, color);  //grafica la funcion en pantalla

}

#ifdef USING_RSF
void CRegionXY::Graficar(char* Formula, char conectar = 0, char color = 9, float Particion = 0.01)
{

	float x, y;

	CFuncad funcion(Formula, "X");
	//Funcion a graficar y=f(x)

	for (x = Xmin; x < Xmax; x += Particion)
	{
		y = funcion.f(x);
		if (!funcion.error)
			punto(vector(x, y), color, conectar);
		else punto(vector(x, y), GREEN, conectar);
	}

}
#endif

void CRegionXY::Ejes()
{
	//Se grafican los ejes cartesianos
	vector M = conver(vector(0, 0));
	setcolor(14);
	int x = (int)M.x, y = (int)M.y;


	line(x, Jmin, x, Jmax); //eje y
	line(Imin, y - 1, Imax, y - 1); // eje x

	char str[18];

	int i;
	float num;

	setcolor(15);

	for (i = 0; i < 20; i++)
	{
		//Eje Y
		num = Ymin + (Ymax - Ymin) / 20 * i;
		//gcvt(num, 6, str);
		sprintf(str, "%g", num);

		M = conver(vector(0, num));
		x = (int)M.x;
		y = (int)M.y;

		fillellipse(x, y, 2, 1);
		outtextxy(x, y, str);

		if (i % 2)
		{
			//Eje X
			num = Xmin + (Xmax - Xmin) / 20 * i;
			// gcvt(num, 6, str);
			sprintf(str, "%g", num);
			M = conver(vector(num, 0));
			x = (int)M.x;
			y = (int)M.y;

			fillellipse(x, y, 1, 3);
			outtextxy(x, y - 10, str);
		}

	}

}

void CRegionXY::draw()
{
	putimage(Imin, Jmin, &bmpScreen, COPY_PUT);
}

void CRegionXY::putpixel(int x, int y, int color) const
{
	auto screen = (unsigned int*)bmpScreen.bmBits;		
	screen[x + bmpScreen.bmWidth * y] = color;
}



/*void autoini(char *ruta)
{
int gd=DETECT,gm;
initgraph(&gd,&gm,ruta);
}*/


