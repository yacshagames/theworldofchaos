/*********************************************************************
METODOS PARA CALCULAR LAS RAICES DE UNA FUNCION: f(x)=0
programado por:
JOSE LUIS DE LA CRUZ LAZARO 	UNI-FIEE 30 Nov 1999
ramondc@hotmail.com
Pagina Web: http://www.geocities.com/joseluisdl/jldl.htm
*********************************************************************/
#include <iostream>
#include "conio.h"

using namespace std;

int MENU(const char *vec[], int x, int y, int dim, int puntero, int col);
///
void CUADRO(int x1, int y1, int ancho, int largo, int col);

void Imprimir_Raiz(int iteracion, double raiz)
{
	cout << "\nIteraci¢n " << iteracion << "\tRaiz = " << raiz;
}

//definicion de la funcion f(x)
double f(double x)
{
	//f(x)=xtan(x)-x^2-0.168=0
	return x * tan(x) - x * x - 0.168;
}

//definicion de la funcion g(x)
//para obtener g(x) se despeja convenientemente f(x)
//de forma que quede x=g(x) donde g'(x)<1 ( derivada de g(x) <1 )
//esta funcion se utiliza en el metodo del punto fijo
double g(double x)
{
	//x=g(x)=(x^2+0.168)/tan(x);
	return (x*x + 0.168) / tan(x);
}

double fderivada(double x)
{
	/*
	derivamos por definicion
	 lim  ( f(x+h)-f(x) )/h
	h->0
	*/
	double h = 1e-6;
	return (f(x + h) - f(x)) / h;

}

//Metodo de Newton-Raphson
double Newton_Raphson(double x, double error = 1e-6)
{
	double x_anterior;

	int iteracion = 1;

	do
	{
		x_anterior = x;
		x = x - f(x) / fderivada(x);
		Imprimir_Raiz(iteracion++, x);
	} while (fabs(x - x_anterior) > error);

	return x;

}

//Metodo de la bisecci¢n
double Biseccion(double a, double b, double error = 1e-6)
{
	double m;
	int iteracion = 1;
	do
	{
		m = (a + b) / 2;
		if (f(a)*f(m) < 0)b = m;
		else a = m;
		Imprimir_Raiz(iteracion++, (a + b) / 2);
	} while (fabs(a - b) > error);

	return (a + b) / 2;
}

//Metodo de la falsa posici¢n
void Falsa_Posicion(double a, double b, double error = 1e-6)
{
	double x1, x2, fa, fx2;
	int iteracion = 1;
	x2 = a;
	do
	{
		x1 = x2;
		x2 = a - (b - a)*f(a) / (f(b) - f(a));
		fa = f(a);
		fx2 = f(x2);
		if ((fa*fx2) > 0) a = x2; else b = x2;
		Imprimir_Raiz(iteracion++, x2);
	} while (fabs(x2 - x1) > error);
}

//Metodo de la secante
void Secante(double x1, double x2, double error = 1e-6)
{
	double fx1, fx2, x;
	int iteracion = 1;
	do
	{
		fx1 = f(x1); fx2 = f(x2);
		x = x2 - fx2 * (x2 - x1) / (fx2 - fx1);
		x1 = x2; x2 = x;
		Imprimir_Raiz(iteracion++, x2);
	} while (fabs(x2 - x1) > error);
}

void Punto_Fijo(double x, double error = 1e-6)
{
	double x1;
	int iteracion = 1;
	do
	{
		x1 = x;
		x = g(x);
		Imprimir_Raiz(iteracion++, x);
	} while (fabs(x1 - x) > error);
}

int main()
{
	const char *Calculo_de_Raices[8] = {
   "Cambiar par metros",
   "Visualizar par metros",
   "M‚todo de Bisecci¢n",
   "M‚todo de la Falsa Posici¢n",
   "M‚todo de la Secante",
   "M‚todo de Newton-Raphson",
   "M‚todo del Punto Fijo",
   "Salir" }; //inicializacion del menu

	char opc = 0; //definicion de variables

	double a, b, Xo, error = 0;//par metros para los m‚todos

	clrscr();
	while (opc != -1)
	{
		clrscr();
		CUADRO(12, 6, 50, 15, LIGHTRED);
		gotoxy(14, 8);
		textcolor(LIGHTCYAN);
		printf("METODOS PARA CALCULAR LAS RAICES DE LA FUNCION");
		gotoxy(25, 9); printf("f(x)=xtan(x)-x^2-0.168=0");
		gotoxy(1, 23); printf("Utilice las flechas ARRIBA y ABAJO para desplazar el cursor sobre las opciones");

		opc = MENU(Calculo_de_Raices, 20, 11, 8, -1, 15);//se crea el menu de opciones

		switch (opc)
		{
		case 0:
			textcolor(WHITE);
			clrscr();
			cout << "\n\nIngresar el intervalo [A,B] donde se desea buscar la raiz\n"
				<< "Ingrese A (N£mero Real):";
			cin >> a;
			cout << "Ingrese B (N£mero Real):";
			cin >> b;
			cout << "\n\nPara M‚todo de Newton y Punto fijo\nIngrese valor inicial de la raiz (N£mero Real): ";
			cin >> Xo;
			cout << "\n\nIngrese el error de aproximaci¢n ( \"N£mero peque¤o\" 0<error<=0.1 ): ";
			cin >> error;
			break;

		case 1:
			if (error == 0)break;
			clrscr();
			cout << "\n\n";
			textcolor(YELLOW);
			printf("Intervalo [a,b] donde se desea buscar la raiz = [ %g , %g ]", a, b);
			cout << "\n\n";
			textcolor(LIGHTCYAN);
			printf("Para M‚todo de Newton y Punto fijo");
			cout << "\n";
			printf("Valor inicial de x = %g", Xo);
			cout << "\n\n";
			textcolor(LIGHTRED);
			printf("Error de aproximaci¢n (en valor decimal) = %g ", error);
			cgetch();
			break;

		case -1:
		case  7:
			clrscr();
			gotoxy(25, 12);
			printf("Esta seguro que desea salir S/N: ");
			opc = toupper(cgetch());
			if (opc == 'S')
			{
				opc = -1;
				error = 1;
			}
			break;

		}

		if (opc > 1 && error != 0)
		{
			clrscr();
			printf(Calculo_de_Raices[opc]);
			cout << "\n\nTabla de Raices:\n";
			switch (opc)
			{
			case 2: Biseccion(a, b, error); break;
			case 3: Falsa_Posicion(a, b, error); break;
			case 4: Secante(a, b, error); break;
			case 5: Newton_Raphson(Xo, error); break;
			case 6: Punto_Fijo(Xo, error); break;
			}
			cgetch();
		}

		if (error == 0)
		{
			textcolor(LIGHTCYAN);
			clrscr();
			gotoxy(20, 12);
			printf("No se ha ingresado los par metros");
			gotoxy(17, 13);
			printf("Por favor seleccione la opci¢n ");
			textcolor(LIGHTGREEN);
			printf("Cambiar par metros");
			cgetch();
		}

	}
	return 1;
}


int MENU(const char *vec[], int x, int y, int dim, int puntero, int col)
{
	/*Esta funcion resive unvector tipo caracter
	  definido de la siguiente manera
	  char *nomvec[dim]={"OPC1","OPC2","OPC3"..... ,"OPCn"};
	  necesita las siguientes librerias:
	  #include <conio.h>
	  #include <stdio.h>
	  #include <bios.h>
	  ejemplo de como se envia
	  opc=MENU(10,10,nomvec,dim);
	  puntero= opcion por defecto donde aparecera el puntero
	*/
	textcolor(col);
	int con = 0, con_ant = 0, sal = 0;
	if (dim >= 1 && x >= 2 && y + (dim - 1) <= 24)
	{
		for (int k = 0; k < dim; k++)
		{
			gotoxy(x, y + k); printf("%s", vec[k]);
		}
		if (puntero != -1 && puntero < dim) { con = puntero; }

		while (sal != 1)
		{
			gotoxy(x - 1, y + con); printf(">");

			textcolor(col);
			gotoxy(x, y + con_ant); printf("%s", vec[con_ant]);
			textcolor(LIGHTGREEN);
			gotoxy(x, y + con); printf("%s", vec[con]);
			con_ant = con;
			/*
			while (bioskey(1) == 0);
			gotoxy(x - 1, y + con); printf(" ");
			switch (bioskey(0))
			{
			case 0x11b:sal = 1; con = -1; break;//ESC
			case 0x1c0d:sal = 1; break;//ENTER
			case 0x4800:
				con--;
				if (con < 0)con = (dim - 1);

				break;//Fle. Arriba
			case 0x5000:con++; if (con > (dim - 1))con = 0; break;//Fle. Abajo
			}*/
			if (ckbhit()) cgetch();
		}

		return(con);
	}
	else
	{
		printf("El menu no tiene la dimension correcta o se salio de la pantalla");
		cgetch();
		return(con = -1);
	}
}

///
void CUADRO(int x1, int y1, int ancho, int largo, int col)
{
	/*necesita
	 #include <conio.h>
	 #include <stdio.h>
	*/
	if (x1 >= 0 && y1 >= 0 && (x1 + ancho) <= 70 && (y1 + largo) <= 25)
	{
		textcolor(col);
		for (int i = x1 + 1; i <= x1 + ancho - 1; i++)
		{
			gotoxy(i, y1); printf("Í");
			gotoxy(i, y1 + largo); printf("Í");
		}
		for (int k = y1 + 1; k <= y1 + largo - 1; k++)
		{
			gotoxy(x1, k); printf("º");
			gotoxy(x1 + ancho, k); printf("º");
		}
		gotoxy(x1, y1); printf("É");
		gotoxy(x1, y1 + largo); printf("È");
		gotoxy(x1 + ancho, y1 + largo); printf("¼");
		gotoxy(x1 + ancho, y1); printf("»");
	}
	else
	{
		gotoxy(x1, y1); printf("Cuadro fuera de pantalla"); cgetch();
	}
}





//METODO DE NEWTON(2 VARIABLES)
// Si se tiene 2 funciones: F(x,y)=0 y G(x,y)=0
// se puede hallar los conjuntos de solución (x,y)
//que verifiquen simultaneamente este par de ecuaciones
//utilizando este método 

float F(float x, float y)
{
	return x * y*y - y - 2;          //  F(x) = xy^2-y-2 = 0
}                            //  G(x) = x^3y-6x-9 = 0
float G(float x, float y)
{
	return x * x*x*y - 6 * x - 9;
}
float Fx(float x, float y)
{
	return y * y;
}
float Fy(float x, float y)
{
	return 2 * y*x - 1;
}
float Gx(float x, float y)
{
	return 3 * x*x*y - 6;
}
float Gy(float x, float y)
{
	return x * x*x;
}
void Newton2Variables()
{
	double x, y, e, f, g, fx, fy, gx, gy, x1, y1;
	clrscr();
	cout << "\n\tMETODO DE NEWTON (2 VARIABLES)\n";
	cout << "\n\tIngrese Xo = "; cin >> x;
	cout << "\tIngrese Yo = "; cin >> y;
	cout << "\tIngrese Error = "; cin >> e;
	do {
		x1 = x; y1 = y;
		f = F(x, y); g = G(x, y);
		fx = Fx(x, y); fy = Fy(x, y);
		gx = Gx(x, y); gy = Gy(x, y);
		x = x + (-f * gy + g * fy) / (fx*gy - gx * fy);
		y = y + (-g * fx + gx * f) / (fx*gy - gx * fy);
		cout << "\n\tSoluci¢n X = " << x;
		cout << "\tSoluci¢n Y = " << y;
	} while (sqrt((x1 - x)*(x1 - x) + (y1 - y)*(y1 - y)) > e);
	cgetch();
}
