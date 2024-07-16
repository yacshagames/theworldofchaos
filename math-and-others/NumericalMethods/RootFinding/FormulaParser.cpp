/*************************************************************************

LICENSE

	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

*************************************************************************/

#include "FormulaParser.h"
#include <algorithm>

const string CFormulaParser::Numeros = "0123456789";

const vector<string> CFormulaParser::funcion =  { "SIN", "COS", "EXP", "SQR", "LOG", "TAN" };

const double CFormulaParser::M_PI = 3.14159265358979323846;

CFormulaParser::CFormulaParser(const string& formula, const string& vars)
{
	Formula = formula;
	Variables = vars;

	// To uppercase
	std::transform(Formula.begin(), Formula.end(), Formula.begin(), ::toupper);
	std::transform(Variables.begin(), Variables.end(), Variables.begin(), ::toupper);
}

CFormulaParser::~CFormulaParser()
{
}

void CFormulaParser::sigP()
{
	do {
		p++;
		
		if (p <= static_cast<unsigned int>(Formula.size()) )
			c = Formula[p];

	} while (c == ' ');
}

void CFormulaParser::Procesar_como_numero()
{
	//int codigo;
	unsigned int inicio = p;
	/*char Num[80], *pIni, *pFin;
	
	pIni = Variables;
	pFin = strchr(Variables, Formula[p]);

	if (pFin && (Formula[p] != '\x0')) // '\x0' es un caracter de espacio
	{*/

	string::size_type pos = Variables.rfind(Formula[p]);

	if (pos != string::npos && (Formula[p] != '\x0'))// '\x0' es un caracter de espacio
	{

		//FF = VarReal[pFin - pIni];
		FF = VarReal[pos];

		sigP();

	}
	else
	{
		do
			sigP();
		//while (strchr(Numeros, c) && (c != '\x0'));
		while ( Numeros.rfind(c)!= string::npos && (c != '\x0'));

		if (c == '.')
			do
				sigP();
		//while (strchr(Numeros, c) && (c != '\x0'));
		while (Numeros.rfind(c) != string::npos && (c != '\x0'));

		if (c == 'E')
		{
			sigP();
			do
				sigP();
			//while (strchr(Numeros, c) && (c != '\x0'));
			while (Numeros.rfind(c) != string::npos && (c != '\x0'));
		}

		//strncpy(Num, &Formula[inicio], p - inicio);
		//Num[p - inicio] = '\0';
		//FF = strtod(Num, &pIni);
		FF = std::stod(Formula.substr(inicio, p - inicio));
	}

}

void CFormulaParser::Procesar_como_nueva_expr()
{
	sigP();
	FF = Expr();
	if (c == ')') sigP(); else ruptura = p;
}

double CFormulaParser::fct()
{
	//if (strchr(Numeros, c) || strchr(Variables, c) && (c != '\x0'))
	if (Numeros.rfind(c) != string::npos || Variables.rfind(c) != string::npos && (c != '\x0'))
		Procesar_como_numero();
	else if (c == '(') Procesar_como_nueva_expr();
	else Procesar_como_func_estandar();
	return FF;
}

double CFormulaParser::Fact_s()
{
	if (c == '-')
	{
		sigP();
		return -fct();
	}
	else	return fct();
}

double CFormulaParser::Termino()
{
	double T;
	T = Fact_s();
	while (c == '^')
	{
		sigP();
		if (T)
		{
			double exponente = Fact_s();

			if (T >= 0)         //si la base es positiva, exponente puede ser cualquier numero real
				T = pow(T, exponente);
			else if (std::abs(exponente - (double)(int)exponente) < 1e-5)//si T<0 ; exponente debera ser entero
				T = pow(T, exponente);
			else { T = 0; error = 1; } // si T<0 y exponente no es entero ocurre un error

		}
		else T = T * Fact_s();
	}
	return T;
}

double CFormulaParser::ExprSimp()
{
	double S;
	char operador;
	S = Termino();
	
	//while (strchr("*/", c) && (c != '\x0'))
	string standardOperators = "*/";
	while ( standardOperators.rfind(c) != string::npos && (c != '\x0'))
	{
		operador = c;
		sigP();
		switch (operador) {
		case '*': S *= Termino(); break;
		case '/':
			double divisor = Termino();
			if (fabs(divisor) > 1e-2) //evita la division por cero
				S /= divisor;
			else { S = 0; error = 1; }
			break;
		}
	}
	return S;
}

double CFormulaParser::Expr()
{
	double E;
	char operador;
	E = ExprSimp();
	
	//while (strchr("+-", c) && (c != '\x0'))
	string standardOperators = "+-";
	while (standardOperators.rfind(c) != string::npos && (c != '\x0'))
	{
		operador = c;
		sigP();
		switch (operador) {
		case '+': E += ExprSimp(); break;
		case '-': E -= ExprSimp(); break;
		}
	}
	return E;
}

void CFormulaParser::Procesar_como_func_estandar()
{
	//char cpy[80];
	//strcpy(cpy, "");

	int i;

	for (i = 0; i < 6; i++)
	{
		//if (!strncmp(strncpy(cpy, &Formula[p], 3), funcion[i], 3))
		if ( Formula.compare(p, 3, funcion[i]) == 0 )
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
		//if (!strncmp(strncpy(cpy, &Formula[p], 2), "PI", 2))
		if (Formula.compare(p, 3, "PI") != 0)
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

void CFormulaParser::eval(const string& formula, double &valor)
{
	//_strupr(Formula);
	p = 0;
	c = Formula[0];
	valor = Expr();
	if (c != '\x0')error = 1;
	ruptura = p;
}

double CFormulaParser::Calcular_formula()
{
	double r;
	error = 0;
	eval(Formula, r);
	return r;
}


// double CFuncad::Entrar_Funcion( char Cadena[] )
// {
//  strcpy(Formula,Cadena);
// };

double CFormulaParser::f(double x, double y, double z)
{
	VarReal[0] = x;
	VarReal[1] = y;
	VarReal[2] = z;

	return Calcular_formula();
}

string CFormulaParser::ExampleOfUse()
{
	unsigned int nVariables = static_cast<unsigned int>(Variables.size());

	string vars= Variables; // Variables in lowercase
	// To uppercase
	std::transform(vars.begin(), vars.end(), vars.begin(), ::tolower);

	string formula, varlist;

	switch (nVariables) {
	default:
		varlist = vars[0];
		// formula = 1-(x^2*sin(x)/(2*x^2+3*x+1)
		formula = string("1-(") + vars[0] + "^2*sin(" + vars[0] + ")/(2*" + vars[0] + "^2+3*" + vars[0] + "+1)";
		break;
	case 2:
		varlist = string(1,vars[0]) + ","+ vars[1];
		// formula = 1-(y^2*sin(x)/(2*x^2+3*y+1)
		formula = string("1-(") + vars[1] + "^2*sin(" + vars[0] + ")/(2*" + vars[0] + "^2+3*" + vars[1] + "+1)";
		break;
	case 3:
		varlist = string(1, vars[0]) + "," + vars[1] + string(",") + vars[2];
		// formula = 1-(y^2*sin(x)/(2*z^2+3*y+1)
		formula = string("1-(") + vars[1] + "^2*sin(" + vars[0] + ")/(2*" + vars[3] + "^2+3*" + vars[1] + "+1)";
		break;
	}

	return 
		"Example Usage : A f("+varlist+") function can be written as" +
		"\n     " + formula +
		"\nRecognized operators : + - * / ^" +
		"\nRecognized math funtions : sin cos log tan exp sqr" +
		"\nMore info en FormulaParser.h library --> by Yacsha Software";
}

/*
  void CFuncad::f( char Cadena[], char Vars[],
		double var1 = 0 , double var2 = 0, double var3 = 0 )
 {

  VarReal[0]=var1;
  VarReal[1]=var2;
  VarReal[2]=var3;

  strcpy(Variables,Vars);
  strcpy(Formula,Cadena);
//  return Calcular_formula(Formula);
 };
  */

#ifdef FP_COMPLEX

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

#endif