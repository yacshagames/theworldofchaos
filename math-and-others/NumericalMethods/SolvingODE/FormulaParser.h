#pragma once
/***************************************************************************
 FORMULA PARSER

  Syntactic Function Recognizer from a text string. Allows you to evaluate
  a function f(x,y,z), where the function is entered as a text string.

  *original source file thanks to Luis Serna

  *REVISED AND MODIFIED BY:
  
  JOSE LUIS DE LA CRUZ LAZARO  
  ramondc@hotmail.com
  Website (THE WORLD OF CHAOS):
   

  HISTORY:

 >> Version 3 - 04-IV-2024
	- Change project name from RSF.H to FormulaParser.h
	- Separate files in to FormulaParser.h and FormulaParser.cpp
	- The RSF_COMPLEX definition is added that allows defining whether the
	  functions in a complex variable will be compiled from the library.

 >> Version 2 - 24-III-2024
	- Update graphics/RSF - Porting to VC++ 2017 using winbgi

 >>	Version 1.3 - 24-VIII-2000
   - The name of IFUNCADE.H was changed to RSF.H 
     (Syntactic Function Recognizer).
   - The real function "f" member of CFunCad was modified so that it accepts
     a maximum of 3 variables.

>>	Version 1.2 - 11-IX-1999
   - Modified functions to accept both real variables and complex variables,
     using overloaded functions
   - Priority was given to the recognition of the imaginary unit over
     other constants and functions (PI, COS, LOG...), to accelerate
	 calculation processes.
   - The error (BUG) was fixed: if the text string contains an unknown
     variable, it contains any value and then f(x...) returns any value.
	 Said unknown variable is replaced by the value of zero.

>>	Version 1.1 - 22-V-1999
   - The function f(...,x,y,z) was adapted to accept up to a maximum
     of 3 variables

>>	Version 1.01 - 21-V-1999
   - The original functions were adapted to accept complex variables
   - Modification of the recognition of constants and functions
     (PI, COS, SIN...), with the aim of making the time spent in
	 said process shorter.
   - The LOG and TAN functions were added

>>	Version 1.00 - 16-V-1999
   - Some errors in the original sources were reviewed and corrected,
     in addition to some functions being modified to speed up the
	 evaluation process.

***************************************************************************/

#include <string.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#ifdef RSF_COMPLEX
	#include "complex.h"
#endif

class CFormulaParser
{
private:

	char *Numeros;
	char funcion[6][4];
	char *Variables;
	char *Formula;
	char c;
	int p, ruptura;
	double FF, VarReal[3];

public:

	int error;
	//constructor
	CFormulaParser(char *, const char *);
	~CFormulaParser();

private:

	void sigP();
	void Procesar_como_numero();
	void Procesar_como_nueva_expr();
	double fct();
	double Fact_s();
	double Termino();
	double ExprSimp();
	double Expr();
	void Procesar_como_func_estandar();
	void eval(char* Formula, double &valor);
	double Calcular_formula(void);
	//double Entrar_Funcion( char Cadena[] );
public:
	double f(double, double, double);


	/*
	void f( char Cadena[], char Vars[],
		   double var1 , double var2, double var3 );
	  */
#ifdef RSF_COMPLEX
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
#endif
};