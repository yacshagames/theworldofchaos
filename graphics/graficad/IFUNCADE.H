/***************************************************************************
 FUNCION:  IFUNCADE  versi¢n 1.0
 (Ingresar FUNcion como una CADEna de texto)

 PROGRAMA QUE PERMITE EVALUAR UNA FUNCION F(X)
 DONDE LA FUNCION ES INGRESADA COMO UNA CADENA DE TEXTO.

 AUTOR: JOSE LUIS DE LA CRUZ LAZARO UNI-FIEE ( 16 Mayo de 1999 )
	ramondc@hotmail.com
***************************************************************************/

#include "iostream.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"

char funcion[5][3]={ "SIN","COS","EXP","LOG","TAN"};
char Numeros[]="0123456789";
char Variables[]="X";
char Formula[80];
char c;
float FF,x;
int p, ruptura, error;
float Xi;

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
  char Num[80], *Cod;

  if( strchr(Variables, Formula[p]) &&  (Formula[p] != '\x0') )
  {
   switch(Formula[p])
   {
	case 'X': FF=x;break;
   };

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
    FF=strtod( Num, &Cod);
  };

 };

 float Expr();

 void Procesar_como_nueva_expr()
 {
  sigP();
  FF=Expr();
  if(c==')') sigP(); else ruptura = p;
 };

 void Procesar_como_func_estandar();

 float fct()
 {
 if(strchr(Numeros,c) || strchr(Variables,c) && (c!='\x0') )
  Procesar_como_numero();
  else if( c=='(' ) Procesar_como_nueva_expr();
  else Procesar_como_func_estandar();
  return FF;
 };

 float Fact_s()
 {
  if(c=='-')
  {
   sigP();
   return -fct();
   }
   else	return fct();
 };

 float Termino()
 {
  float T;
  T=Fact_s();
  while(c=='^')
  {
   sigP();
   if(T) T=pow(T,Fact_s()); else T=T*Fact_s();
  };
  return T;
 };

 float ExprSimp()
 {
  float S;
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

 float Expr()
 {
  float E;
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

 void eval( char Formula[], float &valor )
 {
  strupr(Formula);
  p=0;
  c=Formula[0];
  valor=Expr();
  if(c=='\x0') error=0; else error=1;
  ruptura=p;
 };

 float Calcular_formula(char cad[])
 {
  float r;
  eval(cad,r);
  return r;
 };

 float f( float xi, char Cadena[] )
 {
  x=xi;
  strcpy(Formula,Cadena);
  return Calcular_formula(Formula);
 };

















