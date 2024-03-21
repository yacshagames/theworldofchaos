/***************************************************************************
 FUNCION:  IFCOMPLE
 (Ingresar FUNcion como una CADEna de texto)

 PROGRAMA QUE PERMITE EVALUAR UNA FUNCION F(X)
 DONDE LA FUNCION ES INGRESADA COMO UNA CADENA DE TEXTO.

 AUTOR: JOSE LUIS DE LA CRUZ LAZARO UNI-FIEE ( 16 Mayo de 1999 )
	ramondc@hotmail.com

  versi¢n 1.0 21/05/99
  - La funcion ifuncade se adapto a variables complejas

  versi¢n 1.1 22/05/99
  - Se adapto la funcion f(...,x,y,z)para
    que acepte hasta un maximo de 3 variables

***************************************************************************/

#include "iostream.h"
#include "string.h"
#include "stdlib.h"
#include "complex.h"
#include "conio.h"

char funcion[5][3]={ "SIN","COS","EXP","LOG","TAN"};
char Numeros[]="0123456789";
char Variables[4];
char Formula[80];
char c;
complex FF, VarCompleja[20];
int p, ruptura, error;
//complex Xi;

 void sigP()
 {
  do{
    p++;
    if( p<=strlen(Formula) ) c=Formula[p];
  }while( c==' ' );
 };

 void Procesar_como_numero()
 {
  int codigo;
  int inicio=p;
  char Num[80], *pIni, *pFin;

  pIni=Variables;
  pFin=strchr(Variables, Formula[p]);

  if( *pFin  &&  (Formula[p] != '\x0') )
  {

   FF=VarCompleja[pFin-pIni];

   sigP();

  }
  else
  {
    do
     sigP();
    while( strchr(Numeros,c) && (c!='\x0') );

    if(c=='.')
     do
      sigP();
     while( strchr(Numeros,c) && (c!='\x0') );

    if(c=='E')
    {
     sigP();
     do
      sigP();
     while( strchr(Numeros,c) && (c!='\x0') );
    };

    strncpy(Num,&Formula[inicio],p-inicio);
    Num[p-inicio]='\0';
    FF=strtod( Num, &pIni);
  };

 };

 complex Expr();

 void Procesar_como_nueva_expr()
 {
  sigP();
  FF=Expr();
  if(c==')') sigP(); else ruptura = p;
 };

 void Procesar_como_func_estandar();

 complex fct()
 {
 if(strchr(Numeros,c) || strchr(Variables,c) && (c!='\x0') )
  Procesar_como_numero();
  else if( c=='(' ) Procesar_como_nueva_expr();
  else Procesar_como_func_estandar();
  return FF;
 };

 complex Fact_s()
 {
  if(c=='-')
  {
   sigP();
   return -fct();
   }
   else	return fct();
 };

 complex Termino()
 {
  complex T;
  T=Fact_s();
  while(c=='^')
  {
   sigP();
   if(T!=complex(0,0)) T=pow(T,Fact_s()); else T=T*Fact_s();
  };
  return T;
 };

 complex ExprSimp()
 {
  complex S;
  char operador;
  S=Termino();
  while( strchr("*/",c) && (c!='\x0') )
  {
   operador=c;
   sigP();
   switch(operador){
	case '*': S*=Termino();break;
	case '/': S/=Termino();break;
   }
  };
  return S;
 };

 complex Expr()
 {
  complex E;
  char operador;
  E=ExprSimp();
  while(strchr("+-",c)&&(c!='\x0'))
  {
   operador=c;
   sigP();
   switch(operador){
   case '+': E+=ExprSimp();break;
   case '-': E-=ExprSimp();break;
   };
  };
  return E;
 };

 void Procesar_como_func_estandar()
 {
  char cpy[80];
  strcpy(cpy,"");

  for(int i=0;i<5;i++)
  {
   if(!strncmp(strncpy(cpy,&Formula[p],3),funcion[i],3))
   break;
  }

  if(i<5)
  {
   p+=2;
   sigP();
   FF=fct();

   switch(i)
    {
    case 0: FF=sin(FF); break;
    case 1: FF=cos(FF); break;
    case 2: FF=exp(FF); break;
    case 3: FF=log(FF); break;
    case 4: FF=tan(FF); break;
    }
  }
  else
     if(!strncmp(strncpy(cpy,&Formula[p],2),"PI",2))
     {
      p++;
      sigP();
      FF=fct();
      FF=M_PI;
     }else ruptura=p;
 };

 void eval( char Formula[], complex &valor )
 {
  strupr(Formula);
  p=0;
  c=Formula[0];
  valor=Expr();
  if(c=='\x0') error=0; else error=1;
  ruptura=p;
 };

 complex Calcular_formula(char cad[])
 {
  complex r;
  eval(cad,r);
  return r;
 };

 complex f( char Cadena[], char Vars[],
	    complex var1 = 0 , complex var2 = 0, complex var3 = 0 )
 {

  VarCompleja[0]=var1;
  VarCompleja[1]=var2;
  VarCompleja[2]=var3;

  strcpy(Variables,Vars);
  strcpy(Formula,Cadena);
  return Calcular_formula(Formula);
 };














