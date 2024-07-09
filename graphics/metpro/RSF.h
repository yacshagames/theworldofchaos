/***************************************************************************
 RSF.H
 Reconocedor Sint ctico de Funciones desde una cadena de texto

 LA CLASE CFUNCAD PERMITE EVALUAR UNA FUNCION F(X,Y,Z,...),
 DONDE LA FUNCION ES INGRESADA COMO UNA CADENA DE TEXTO.

 *archivo fuente original gracias a Luis Serna

 *REVISADA Y MODIFICADA POR:

  JOSE LUIS DE LA CRUZ LAZARO
 correos:
  jcruz@ec-red.com
  ramondc@hotmail.com
 Pagina Web ( EL MUNDO DEL CAOS ):
  http://www.geocities.com/joseluisdl

  HISTORIA:

  >> Version 2 - 24-III-2024
	- Update graphics/RSF - Porting to VC++ 2017 using winbgi

  versi¢n 1.3  24-Agosto-2000
  -Se cambi¢ el nombre de IFUNCADE.H por el de RSF.H (Reconocedor
   Sint ctico de Funciones).
  -Se modific¢ la funci¢n real "f" miembro de CFunCad, para que acepte 3 variables
   como m ximo.

  versi¢n 1.2  11-Septiembre-1999
  - Se modificaron las funciones para que acepten tanto variables
	reales como variables complejas, utilizando funciones sobrecargadas
  - Se dio prioridad en el reconocimiento de la unidad imaginaria frente a
	otras constantes y funciones ( PI, cos, log ... ) , para
	acelerar procesos de calculos.
  - Se arreglo el error ( BUG ):
	 de que si la cadena de texto contiene una variable desconocida esta
	 contiene cualquier valor y luego f(x...) arroja cualquier valor.
	 Dicha variable desconocida es reeemplazada por el valor de cero.

  versi¢n 1.1  22-Mayo-1999
  - Se adapto la funcion f(...,x,y,z)para
	que acepte hasta un maximo de 3 variables

  versi¢n 1.01  21-Mayo-1999
  - Las funciones originales se adaptaron para que acepten variables complejas
  - Modificacion del reconocimiento de constantes y funciones
	( PI, cos, sin ... ), con el objetivo de hacer mas corto el tiempo
	empleado en dicho proceso.
  - Se agrego las funciones log y tan

  versi¢n 1.00  16-Mayo-1999
  -Se revis¢ y corrigi¢ algunos errores en los fuentes originales, ademas de
   que se modific¢ algunas funciones para acelerar el proceso de evaluaci¢n.

***************************************************************************/

#include <string.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "complex.h"

class CFuncad
{
private:

	char *Numeros;
	char funcion[6][4];
	char *Variables;
	char *Formula;
	char c;
	int p, ruptura;
	float FF, VarReal[3];

public:

	int error;
	//constructor
	CFuncad(char *, const char *);
	~CFuncad();

private:

	void sigP();
	void Procesar_como_numero();
	void Procesar_como_nueva_expr();
	float fct();
	float Fact_s();
	float Termino();
	float ExprSimp();
	float Expr();
	void Procesar_como_func_estandar();
	void eval(char* Formula, float &valor);
	float Calcular_formula(void);
	//float Entrar_Funcion( char Cadena[] );
public:
	float f(float, float, float);
	/*
	void f( char Cadena[], char Vars[],
		   float var1 , float var2, float var3 );
	  */
	  //FUNCIONES EN VARIABLE COMPLEJA
private:
	complex FC, VarCompleja[3]; //FC : Funcion Compleja

	void Procesar_como_numero_C(void);
	void Procesar_como_nueva_expr_C();
	complex fct_C();
	complex Fact_s_C();
	complex Termino_C();
	complex ExprSimp_C();
	complex Expr_C();
	void Procesar_como_func_estandar_C();
	void eval(char Formula[], complex &valor);
	complex Calcular_formula_C(char cad[]);
public:
	complex f(char Cadena[], char Vars[],
		complex var1, complex var2, complex var3);

};

CFuncad::CFuncad(char * formula, const char *vars)
{

	Formula = new char[strlen(formula) + 1];
	Variables = new char[strlen(vars) + 1];
	Numeros = new char[11];

	strcpy(Formula, formula);
	strcpy(Variables, vars);

	strcpy(Numeros, "0123456789");
	strcpy(funcion[0], "SIN");
	strcpy(funcion[1], "COS");
	strcpy(funcion[2], "EXP");
	strcpy(funcion[3], "SQR");
	strcpy(funcion[4], "LOG");
	strcpy(funcion[5], "TAN");
}

CFuncad::~CFuncad()
{
	delete Formula;
	delete Variables;
	delete Numeros;
}
void CFuncad::sigP()
{
	do {
		p++;
		if (p <= strlen(Formula)) c = Formula[p];
	} while (c == ' ');
};

void CFuncad::Procesar_como_numero()
{
	int codigo;
	int inicio = p;
	char Num[80], *pIni, *pFin;

	pIni = Variables;
	pFin = strchr(Variables, Formula[p]);

	if (pFin && (Formula[p] != '\x0')) // '\x0' es un caracter de espacio
	{

		FF = VarReal[pFin - pIni];

		sigP();

	}
	else
	{
		do
			sigP();
		while (strchr(Numeros, c) && (c != '\x0'));

		if (c == '.')
			do
				sigP();
		while (strchr(Numeros, c) && (c != '\x0'));

		if (c == 'E')
		{
			sigP();
			do
				sigP();
			while (strchr(Numeros, c) && (c != '\x0'));
		};

		strncpy(Num, &Formula[inicio], p - inicio);
		Num[p - inicio] = '\0';
		FF = strtod(Num, &pIni);
	};

};

void CFuncad::Procesar_como_nueva_expr()
{
	sigP();
	FF = Expr();
	if (c == ')') sigP(); else ruptura = p;
};

float CFuncad::fct()
{
	if (strchr(Numeros, c) || strchr(Variables, c) && (c != '\x0'))
		Procesar_como_numero();
	else if (c == '(') Procesar_como_nueva_expr();
	else Procesar_como_func_estandar();
	return FF;
};

float CFuncad::Fact_s()
{
	if (c == '-')
	{
		sigP();
		return -fct();
	}
	else	return fct();
};

float CFuncad::Termino()
{
	float T;
	T = Fact_s();
	while (c == '^')
	{
		sigP();
		if (T)
		{
			float exponente = Fact_s();

			if (T >= 0)         //si la base es positiva, exponente puede ser cualquier numero real
				T = pow(T, exponente);
			else if (exponente == (int)exponente)//si T<0 ; exponente debera ser entero
				T = pow(T, exponente);
			else { T = 0; error = 1; } // si T<0 y exponente no es entero ocurre un error

		}
		else T = T * Fact_s();
	};
	return T;
};

float CFuncad::ExprSimp()
{
	float S;
	char operador;
	S = Termino();
	while (strchr("*/", c) && (c != '\x0'))
	{
		operador = c;
		sigP();
		switch (operador) {
		case '*': S *= Termino(); break;
		case '/':
			float divisor = Termino();
			if (fabs(divisor) > 1e-2) //evita la division por cero
				S /= divisor;
			else { S = 0; error = 1; }
			break;
		}
	};
	return S;
};

float CFuncad::Expr()
{
	float E;
	char operador;
	E = ExprSimp();
	while (strchr("+-", c) && (c != '\x0'))
	{
		operador = c;
		sigP();
		switch (operador) {
		case '+': E += ExprSimp(); break;
		case '-': E -= ExprSimp(); break;
		};
	};
	return E;
};

void CFuncad::Procesar_como_func_estandar()
{
	char cpy[80];
	strcpy(cpy, "");

	int i;

	for (i = 0; i < 6; i++)
	{
		if (!strncmp(strncpy(cpy, &Formula[p], 3), funcion[i], 3))
			break;
	}

	if (i < 6)
	{
		p += 2;
		sigP();
		FF = fct();

		switch (i)
		{
		case 0: FF = sin(FF); break;
		case 1: FF = cos(FF); break;
		case 2: FF = exp(FF); break;
		case 3:
			if (FF >= 0)
				FF = sqrt(FF);
			else { FF = 0; error = 1; }
			break;
		case 4:
			if (FF > 0)
				FF = log(FF);
			else { FF = 0; error = 1; }
			break;
		case 5: FF = tan(FF); break;
		}
	}
	else
		if (!strncmp(strncpy(cpy, &Formula[p], 2), "PI", 2))
		{
			p++;
			sigP();
			FF = fct();
			FF = M_PI;
		}
		else
		{
			FF = 0; // si la cadena de texto contiene una variable desconocida esta
			  // es reeemplazada por el valor de cero
			ruptura = p;
		}
};

void CFuncad::eval(char* Formula, float &valor)
{
	_strupr(Formula);
	p = 0;
	c = Formula[0];
	valor = Expr();
	if (c != '\x0')error = 1;
	ruptura = p;
};

float CFuncad::Calcular_formula(void/*char cad[]*/)
{
	float r;
	error = 0;
	eval(Formula, r);
	return r;
};


// float CFuncad::Entrar_Funcion( char Cadena[] )
// {
//  strcpy(Formula,Cadena);
// };

float CFuncad::f(float x, float y = 0, float z = 0)
{
	VarReal[0] = x;
	VarReal[1] = y;
	VarReal[2] = z;

	return Calcular_formula();
}

/*
  void CFuncad::f( char Cadena[], char Vars[],
		float var1 = 0 , float var2 = 0, float var3 = 0 )
 {

  VarReal[0]=var1;
  VarReal[1]=var2;
  VarReal[2]=var3;

  strcpy(Variables,Vars);
  strcpy(Formula,Cadena);
//  return Calcular_formula(Formula);
 };
  */



  //char funcion[5][3]={ "SIN","COS","EXP","LOG","TAN"};
  //char Numeros[]="0123456789";
  //char Variables[4];
  //char Formula[80];
  //char c;
  //complex FC, VarCompleja[3]; //FC : Funcion Compleja
  //int p, ruptura, error;
  //complex Zi;
	/*
   void sigP()
   {
	do{
	  p++;
	  if( p<=strlen(Formula) ) c=Formula[p];
	}while( c==' ' );
   };*/

void CFuncad::Procesar_como_numero_C(void)
{
	int codigo;
	int inicio = p;
	char Num[80], *pIni, *pFin;

	pIni = Variables;
	pFin = strchr(Variables, Formula[p]);

	if (*pFin && (Formula[p] != '\x0'))
	{

		FC = VarCompleja[pFin - pIni];

		sigP();

	}
	else
	{
		do
			sigP();
		while (strchr(Numeros, c) && (c != '\x0'));

		if (c == '.')
			do
				sigP();
		while (strchr(Numeros, c) && (c != '\x0'));

		if (c == 'E')
		{
			sigP();
			do
				sigP();
			while (strchr(Numeros, c) && (c != '\x0'));
		};

		strncpy(Num, &Formula[inicio], p - inicio);
		Num[p - inicio] = '\0';
		FC = strtod(Num, &pIni);
	};

};

void CFuncad::Procesar_como_nueva_expr_C()
{
	sigP();
	FC = Expr_C();
	if (c == ')') sigP(); else ruptura = p;
};

complex CFuncad::fct_C()
{
	if (strchr(Numeros, c) || strchr(Variables, c) && (c != '\x0'))
		Procesar_como_numero_C();
	else if (c == '(') Procesar_como_nueva_expr_C();
	else Procesar_como_func_estandar_C();
	return FC;
};

complex CFuncad::Fact_s_C()
{
	if (c == '-')
	{
		sigP();
		return -fct_C();
	}
	else	return fct_C();
};

complex CFuncad::Termino_C()
{
	complex T;
	T = Fact_s_C();
	while (c == '^')
	{
		sigP();
		if (T != complex(0, 0))
			T = pow(T, Fact_s_C());
		else
			T = T * Fact_s_C();
	};
	return T;
};

complex CFuncad::ExprSimp_C()
{
	complex S;
	char operador;
	S = Termino_C();
	while (strchr("*/", c) && (c != '\x0'))
	{
		operador = c;
		sigP();
		switch (operador) {
		case '*': S = S * Termino_C(); break;
		case '/': S = S / Termino_C(); break;
		}
	};
	return S;
};

complex CFuncad::Expr_C()
{
	complex E;
	char operador;
	E = ExprSimp_C();
	while (strchr("+-", c) && (c != '\x0'))
	{
		operador = c;
		sigP();
		switch (operador) {
		case '+': E = E + ExprSimp_C(); break;
		case '-': E = E - ExprSimp_C(); break;
		};
	};
	return E;
};

void CFuncad::Procesar_como_func_estandar_C()
{
	char cpy[80];
	strcpy(cpy, "");


	if (Formula[p] == 'I') //el imaginario puro i=sqrt(-1)
	{
		sigP();
		FC = fct_C();
		FC = complex(0, 1);
	}
	else
	{
		int i;
		for (i = 0; i < 5; i++)
		{
			if (!strncmp(strncpy(cpy, &Formula[p], 3), funcion[i], 3))
				break;
		}

		if (i < 5)
		{
			p += 2;
			sigP();
			FC = fct_C();

			switch (i)
			{
			case 0: FC = sin(FC); break;
			case 1: FC = cos(FC); break;
			case 2: FC = exp(FC); break;
			case 3: FC = log(FC); break;
			case 4: FC = tan(FC); break;
			}
		}
		else
			if (!strncmp(strncpy(cpy, &Formula[p], 2), "PI", 2))
			{
				p++;
				sigP();
				FC = fct_C();
				FC = M_PI;
			}
			else
			{
				FC = 0;// si la cadena de texto contiene una variable desconocida esta
				 // es reeemplazada por el valor de cero
				ruptura = p;
			}

	}
};

void CFuncad::eval(char Formula[], complex &valor)
{
	_strupr(Formula);
	p = 0;
	c = Formula[0];
	valor = Expr_C();
	if (c == '\x0') error = 0; else error = 1;
	ruptura = p;
};

complex CFuncad::Calcular_formula_C(char cad[])
{
	complex r;
	eval(cad, r);
	return r;
};

complex CFuncad::f(char Cadena[], char Vars[],
	complex var1 = 0, complex var2 = 0, complex var3 = 0)
{

	VarCompleja[0] = var1;
	VarCompleja[1] = var2;
	VarCompleja[2] = var3;

	strcpy(Variables, Vars);
	strcpy(Formula, Cadena);
	//cout<<Numeros;
	return Calcular_formula_C(Formula);
};