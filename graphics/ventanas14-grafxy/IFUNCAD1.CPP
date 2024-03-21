/***************************************************************************
 FUNCION:  IFUNCADE  versi¢n 1.2
 (Ingresar FUNcion como una CADEna de texto)

 RECONOCEDOR SINTACTICO DE UNA FUNCION INGRESADA COMO CADENA DE TEXTO

 EL PROGRAMA QUE PERMITE EVALUAR UNA FUNCION F(X,Y,Z,...)
 DONDE LA FUNCION ES INGRESADA COMO UNA CADENA DE TEXTO.

 *archivo fuente original gracias a Luis Serna

 *REVISADA Y MODIFICADA POR: 		( 16 Mayo de 1999 )
  JOSE LUIS DE LA CRUZ LAZARO 	UNI-FIEE
  ramondc@hotmail.com

  versi¢n 1.0 21/05/1999
  - Las funciones originales se adaptaron para que acepten variables complejas
  - Modificacion del reconocimiento de constantes y funciones
    ( PI, cos, sin ... ), con el objetivo de hacer mas corto el tiempo
    empleado en dicho proceso.
  - Se agrego las funciones log y tan

  versi¢n 1.1 22/05/1999
  - Se adapto la funcion f(...,x,y,z)para
    que acepte hasta un maximo de 3 variables

  versi¢n 1.2 11/09/1999
  - Se modificaron las funciones para que acepten tanto variables
    reales como variables complejas, utilizando funciones sobrecargadas
  - Se dio prioridad en el reconocimiento de la unidad imaginaria frente a
    otras constantes y funciones ( PI, cos, log ... ) , para
    acelerar procesos de calculos.
  - Se arreglo el error ( BUG ):
     de que si la cadena de texto contiene una variable desconocida esta
     contiene cualquier valor y luego f(x...) arroja cualquier valor.
     Dicha variable desconocida es reeemplazada por el valor de cero.

***************************************************************************/

#include "string.h"
#include "stdlib.h"
#include "math.h"
#include "complex.h"

char funcion[6][3]={ "SIN","COS","EXP","SQR","LOG","TAN"};
char Numeros[]="0123456789";
char Variables[4];
char Formula[80];
char c;
int p, ruptura, error;
float FF,VarReal[3];

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

   FF=VarReal[pFin-pIni];

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
    case 3:
      if(FF>0)
      FF=sqrt(FF);
      else {FF=0;error=1;}

       break;
    case 4: FF=log(FF); break;
    case 5: FF=tan(FF); break;
    }
  }
  else
     if(!strncmp(strncpy(cpy,&Formula[p],2),"PI",2))
     {
      p++;
      sigP();
      FF=fct();
      FF=M_PI;
     }
     else
     {
     FF=0; // si la cadena de texto contiene una variable desconocida esta
	   // es reeemplazada por el valor de cero
     ruptura=p;
     }
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

 float Calcular_formula(void/*char cad[]*/)
 {
  float r;
  eval(Formula,r);
  if(error==1)return 0;
  return r;
 };


 float Entrar_Funcion( char Cadena[] )
 {
  strcpy(Formula,Cadena);
 };

 float f( float xi)
 {
  VarReal[0]=xi;
  return Calcular_formula();
 }

  void/*float*/ f( char Cadena[], char Vars[],
	    float var1 = 0 , float var2 = 0, float var3 = 0 )
 {

  VarReal[0]=var1;
  VarReal[1]=var2;
  VarReal[2]=var3;

  strcpy(Variables,Vars);
  strcpy(Formula,Cadena);
//  return Calcular_formula(Formula);
 };




//char funcion[5][3]={ "SIN","COS","EXP","LOG","TAN"};
//char Numeros[]="0123456789";
//char Variables[4];
//char Formula[80];
//char c;
complex FC, VarCompleja[3]; //FC : Funcion Compleja
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

 void Procesar_como_numero_C( void )
 {
  int codigo;
  int inicio=p;
  char Num[80], *pIni, *pFin;

  pIni=Variables;
  pFin=strchr(Variables, Formula[p]);

  if( *pFin  &&  (Formula[p] != '\x0') )
  {

   FC=VarCompleja[pFin-pIni];

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
    FC=strtod( Num, &pIni);
  };

 };

 complex Expr_C();

 void Procesar_como_nueva_expr_C()
 {
  sigP();
  FC=Expr_C();
  if(c==')') sigP(); else ruptura = p;
 };

 void Procesar_como_func_estandar_C();

 complex fct_C()
 {
 if(strchr(Numeros,c) || strchr(Variables,c) && (c!='\x0') )
  Procesar_como_numero_C();
  else if( c=='(' ) Procesar_como_nueva_expr_C();
  else Procesar_como_func_estandar_C();
  return FC;
 };

 complex Fact_s_C()
 {
  if(c=='-')
  {
   sigP();
   return -fct_C();
   }
   else	return fct_C();
 };

 complex Termino_C()
 {
  complex T;
  T=Fact_s_C();
  while(c=='^')
  {
   sigP();
   if(T!=complex(0,0)) T=pow(T,Fact_s_C()); else T=T*Fact_s_C();
  };
  return T;
 };

 complex ExprSimp_C()
 {
  complex S;
  char operador;
  S=Termino_C();
  while( strchr("*/",c) && (c!='\x0') )
  {
   operador=c;
   sigP();
   switch(operador){
	case '*': S*=Termino_C();break;
	case '/': S/=Termino_C();break;
   }
  };
  return S;
 };

 complex Expr_C()
 {
  complex E;
  char operador;
  E=ExprSimp_C();
  while(strchr("+-",c)&&(c!='\x0'))
  {
   operador=c;
   sigP();
   switch(operador){
   case '+': E+=ExprSimp_C();break;
   case '-': E-=ExprSimp_C();break;
   };
  };
  return E;
 };

 void Procesar_como_func_estandar_C()
 {
  char cpy[80];
  strcpy(cpy,"");


  if( Formula[p]=='I' ) //el imaginario puro i=sqrt(-1)
   {
    sigP();
    FC=fct_C();
    FC=complex(0,1);
   }
  else
  {
    for(int i=0;i<5;i++)
    {
     if(!strncmp(strncpy(cpy,&Formula[p],3),funcion[i],3))
     break;
    }

    if(i<5)
    {
     p+=2;
     sigP();
     FC=fct_C();

     switch(i)
     {
      case 0: FC=sin(FC); break;
      case 1: FC=cos(FC); break;
      case 2: FC=exp(FC); break;
      case 3: FC=log(FC); break;
      case 4: FC=tan(FC); break;
      }
    }
    else
      if(!strncmp(strncpy(cpy,&Formula[p],2),"PI",2))
      {
       p++;
       sigP();
       FC=fct_C();
       FC=M_PI;
      }
      else
      {
      FC=0;// si la cadena de texto contiene una variable desconocida esta
	   // es reeemplazada por el valor de cero
      ruptura=p;
      }

  }
 };

 void eval( char Formula[], complex &valor )
 {
  strupr(Formula);
  p=0;
  c=Formula[0];
  valor=Expr_C();
  if(c=='\x0') error=0; else error=1;
  ruptura=p;
 };

 complex Calcular_formula_C(char cad[])
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
  return Calcular_formula_C(Formula);
 };















