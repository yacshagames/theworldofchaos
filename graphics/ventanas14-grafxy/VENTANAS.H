/*****************************************************************************
VENTANAS.H version 1.2
SIMULA UN ENTORNO GRAFICO SIMILAR A WINDOWS 98

AUTOR: JOSE LUIS DE LA CRUZ LAZARO ramondc@hotmail.com

13/09/1999 version 1.3
*Se creo la clase CCajaTexto, que crea una caja donde se puede ingresar texto
 a una cadena (el texto es mostrado virtualmente)
*Se creo la clase CVentana que crea una ventana estilo Windows 98

11/09/1999 version 1.2
 * Se adapto todas las funciones a la cabecera mousec.h, la cual controla los
   eventos del raton perfectamente

10/09/1999 version 1.1
 * modificacion la funcion CBoton::Mostrar
   se agrego el efecto de mostrar el boton SIN_FOCO cuando se mantiene
   presionado el click y se esta fuera del area del boton, y mostrarlo
   PRESIONADO cuando se esta en su area.

14/08/1999 version 1.0
 creacion de:
 * Funcion Ventana
 * Clase CBoton
*****************************************************************************/
#ifndef __VENTANAS_H
#define __VENTANAS_H

#if !defined(__GRAPHICS_H)
#include <graphics.h>
#endif

#if !defined(__CONIO_H)
#include <conio.h>
#endif

#if !defined(__STRING_H)
#include <string.h>
#endif

#include "funcgraf.h"

//#include "mousec.h"
#include "mousebgi.h"

#include <alloc.h>

#ifndef __PCXBGI_H
#include "pcxbgi.h"
#endif

#include <time.h>

//#include <iostream.h>

//Define los estados del boton
#define SIN_FOCO 0
#define CON_FOCO 1
#define PRESIONADO 2


/*
struct Evento
{
 int x;
 int y;
 unsigned evento;
 char tecla;
};
*/

void ModoGrafico( void );
void cuadro(int x, int y, int x1, int y1, int modo3D = 0,int color_fondo = 7);

///////////////////////////////////////////////////////////////////////////
//Clase Boton
class CBoton
{
 public:
 int posx,posy;
 int alto,ancho;
 int estado,estado_anterior;
 char titulo[16];

 CBoton(){};

 CBoton(int _posx, int _posy, int _alto, int _ancho, char *_titulo);

 int mostrar(Evento &raton);
 void mostrar( int modo);
 void cambiar_titulo( char *_titulo );

 private:
  int mousemove(int x, int y);
  void mostrar_titulo(int x = 0, int y = 0);

};

CBoton::CBoton(int _posx, int _posy, int _alto, int _ancho, char *_titulo)
{
posx=_posx;
posy=_posy;
alto=_alto;
ancho=_ancho;
strcpy(titulo,_titulo);
estado_anterior=CON_FOCO; //es para que el estado anterior sea diferente del SIN_FOCO y se pueda dibujar el botn sin el FOCO
}

void CBoton::mostrar( int modo )
{

estado=modo;

if(estado!=estado_anterior)
{
 mousehide();  //oculta el puntero para que este no corte el grafico del boton
 cuadro(posx,posy,posx+ancho,posy+alto,modo);

 switch( modo )
 {
   case CON_FOCO:
   setcolor(15);
   mostrar_titulo();
   break;
   case SIN_FOCO:
   setcolor(0);
   mostrar_titulo();
   break;
   case PRESIONADO:
   setcolor(8);
   mostrar_titulo(2,2);
 }

 mouseshow(); //el puntero se ve otra vez

}
estado_anterior=estado;

}

int CBoton::mousemove(int x, int y)
{
 if( ( posx<x && x<(posx+ancho) ) && ( posy<y && y<(posy+alto) ) ) return 1;
 else return 0;
}


//Muestra los estados del boton dependiendo de la posicion del cursor
int CBoton::mostrar(Evento &raton)
{

 switch( raton.evento )
 {
  case IDLE: //No se hizo click

  if( mousemove(raton.x,raton.y) )
   mostrar(CON_FOCO);
  else
   mostrar(SIN_FOCO);

  break;

 case LBUTTON_DOWN: //se hizo un click izquierdo

  if( mousemove( raton.x, raton.y ) )
   {
    mostrar(PRESIONADO);
    delay(100); //para que se note el efecto de presionar se pone una peque¤a pausa
    while( mouseevent( &(raton.x), &(raton.y) )  == LBUTTON_STILL_DOWN )//mientras no se suelte el boton
     if( !mousemove( raton.x, raton.y ) )
      mostrar(SIN_FOCO);
     else
      mostrar(PRESIONADO);

    if( mousemove( raton.x, raton.y ) ) return 1; //se ejecuta la orden del boton
   }


 }
 return 0;//no se ejecuta la orden del boton
}

void CBoton::mostrar_titulo(int x, int y)
{
 int longitud=strlen( titulo );
 outtextxy(x+posx+ancho/2-textwidth("W")/2*longitud,y+posy+alto/2-3,titulo);
}

void CBoton::cambiar_titulo( char *_titulo )
{
 strcpy(titulo,_titulo);
}

///////////////////////////////////////////////////////////////////////////
//INICIA EL MODO GRAFICO

  /*
void ModoGrafico( void )
{
 int gdriver = DETECT, gmode;
 initgraph(&gdriver, &gmode, "");

 mousesetup(graphics);//inicia el raton
 mousehide(); //oculta el raton
}

*/
int huge func()
{
 return 2;
}


void ModoGrafico( void )
{
 int controlador=0,modo=0;

 controlador=DETECT;
 installuserdriver("Svga256",func);
 initgraph(&controlador,&modo,"");

 mousesetup(graphics);//inicia el raton
 mousehide(); //oculta el raton

}

///////////////////////////////////////////////////////////////////////////
//Dibuja una ventana vacia tipo WINDOWS98
void cuadro(int x, int y, int x1, int y1, int modo3D, int color_fondo )
{
//  modo3D=0 -> muestra una ventana sin efecto 3D
//  modo3D=1 -> muestra una ventana saliente
//  modo3D=2 -> muestra una ventana entrante


int marco1,marco2,color_actual;

switch( modo3D )
{
 case 0:
  marco1=marco2=color_fondo;
  break;
 case 1:
  marco1=15;
  marco2=8;
  break;
 case 2:
  marco1=8;
  marco2=15;
}

 setfillstyle(1,color_fondo);
 bar3d(x,y,x1,y1,0,0);

 color_actual=getcolor();

 setcolor(marco1);
 line(x,y,x1,y);
 line(x,y,x,y1);

 setcolor(marco2);
 line(x,y1,x1,y1);
 line(x1,y,x1,y1);

 setcolor(color_actual);

}

/*
Evento Detectar_click_o_tecla( void )
{
 Evento p;

 p.evento=p.tecla=0;

 p.evento=mouseevent( &(p.x), &(p.y) );

  if( kbhit() )
  {
    p.tecla=getch();
    if(p.tecla==0)getch();
  }

//  if( p.boton )
//   delay(200); //retrasa 200 milisegundos para que se actualice el registro de no tener ningun boton presionado

 return p;
}
 */

#define IZQUIERDA 75
#define DERECHA   77
#define DEL       83
#define HOME      71
#define END       79
#define ESC       27
#define ENTER     13
#define BACKSPACE '\b'

class CCajaTexto
{

 int x1;
 int x2;
 int y1;
 int y2;

 int x_real;
 int y_real;
 int ancho_real;
 int alto_real;
 int color_fondo;
 int color_fuente;
 int ancho_fuente;

 int i; //posicion actual en la cadena cad[]
 int longitud; //longitud de la cadena cad[]

 ///contadores para el desplazamineto horizontal sobre la caja

 int inicio;//posicion horizontal inicial del contador x (normalmente es cero)
 int x;//posicion horizontal actual del cursor sobre la caja ( inicio<x< ancho )
 int ancho; //contiene cuantas unidades de ancho de la fuente estan
	    //contenidas en la caja ancho =ancho_real/ancho_fuente

 int y;//coord. en pixeles de la posicion vertical inicial de la zona donde se mostrara texto
 int desplazamiento_x; //coord. en pixeles de la posicion horizontal inicial de la zona donde se mostrara texto

 char c[2]; //caracter que actualmente ha sido ingresado a la funcion editar_texto

// char *caja;
char caja[80]; //contiene el texto que sera mostrado virtualwente por
	       //la funcion mostrar_texto_virutal

 void moverse(int x, int y);
 void mostrar_cursor(int color);
 void mostrar_texto_virtual( int pos_inicial );

 public:

//  char *cad;
char cad[80];
 CCajaTexto()
 {
  /*
  cad = new char;
  caja = new char;
  */
 };

 CCajaTexto( int X1, int Y1, int X2, int Y2 /*CVentana ventana_padre*/ )
 {
  /*
  x1=X1;
  y1=Y1;
  x2=X2;
  y2=Y2;
    */

  cambiar_posicion(X1,Y1,X2,Y2);

  x=0;//x_real/ancho_fuente;
  inicio=x;
  i=0;
  longitud=0;

  c[1]='\0';

// caja = new char[ancho];
 //cad = new char[80];

  //Se crea la caja de texto
//  mostrar_ventana_virtual();

  setcolor(color_fuente);

  moveto(desplazamiento_x,y);

 }

 /*
 ~CCajaTexto()
 {
  delete caja;
  delete cad;
 }
   */
 char editar_texto(Evento &);
 void cambiar_posicion( int , int , int , int  );
 void mostrar_ventana_virtual(void);

};

void CCajaTexto::cambiar_posicion( int X1, int Y1, int X2, int Y2 )
 {
  x1=X1;
  y1=Y1;
  x2=X2;
  y2=Y2;

  x_real=20;
  y_real=10;
  ancho_real=x2-x1-2*x_real;
  alto_real=15;
  color_fondo=GREEN;
  color_fuente=BLACK;
  ancho_fuente=textwidth("W");
  ancho=ancho_real/ancho_fuente-2; // se le resta 2 uaf: una para que el texto no se salga por el lado izquierdo de la caja, y otra para que el cursor no se salga de la caja
  desplazamiento_x=x_real+x1+ancho_fuente/2; //desde este valor (en pixeles) se comenzara a escribir, se le aumenta la mitad del ancho_fuente para que haya un margen del texto con la caja
  y=y_real+y1+textheight("W")/2;

 }

void CCajaTexto::mostrar_ventana_virtual(void)
{
 cuadro(x_real+x1,y_real+y1,x_real+x1+ancho_real,y_real+y1+alto_real,2,color_fondo);
 setcolor(color_fuente);
 mostrar_texto_virtual( i+inicio-x );
}

void CCajaTexto::moverse(int x, int y)
{
 moveto(desplazamiento_x+x*ancho_fuente,y);
}

void CCajaTexto::mostrar_cursor(int color)
{
 setcolor(color);
 moverse(x,y+1); // y+1 es para que el cursor no se superponga a algun caracter de la cadena
 outtext("_");
}

void CCajaTexto::mostrar_texto_virtual(int pos_inicial)
{
 for(int j=0;j<ancho;j++)
  if((pos_inicial+j)<longitud)
   caja[j]=cad[pos_inicial+j];
   else
   {
   caja[j++]=' ';
   break;
   }

 caja[j]='\0';
 moveto(desplazamiento_x,y);

 cuadro(x_real+x1,y_real+y1,x_real+x1+ancho_real,y_real+y1+alto_real,2,color_fondo);

 outtext(caja);

}
/*
clock_t __t=clock();

int TPeriodo( int periodo )
{
 // periodo en milisegundos
 if( (clock()-__t)/CLK_TCK*1000 > periodo )
 {
    __t=clock();
    return 1;
 }
 return 0;
}
  */
char CCajaTexto::editar_texto( Evento &raton)
{

 int j;

/*
  //Se crea la caja de texto

  cuadro(x_real+x1,y_real+y1,x_real+x1+ancho_real,y_real+y1+alto_real,2,color_fondo);
  setcolor(color_fuente);

  moveto(desplazamiento_x,y);
*/
// do
// {

  //muestra el cursor mientras se espera reaccion del usuario

//  while( !kbhit() )
 // {
//   WaitRetrace();
   mostrar_cursor(color_fuente);
   delay(30);//pone una pausa para mostrar el parpareo del cursor
//   WaitRetrace();
   mostrar_cursor(color_fondo);
   delay(20);


 // }

  //oculta el cursor
 // mostrar_cursor(color_fondo);
  setcolor(color_fuente);

 if( raton.tecla>=0 )
 {
  c[0]=raton.tecla;//getch();

  moverse(x,y);

  switch( c[0] )
  {
   case 0: //TECLAS DE CODIGO EXTENDIDO
    c[0]=getch();
    switch( c[0] )
    {
     case IZQUIERDA:
      if(x>inicio)
      {
       moverse(--x,y);
       i--;
      }
      else
       if(i>0)
       {
/*
	int des;
	if( i>8)des=i-8; //crea un efecto de texto virtual, es decir recupera el texto que esta virtualmente a la derecha de la caja
	else des=i;
	i--;*/
	mostrar_texto_virtual( --i );
	/*
	if(des==8)
	{x+=8;
	moverse( x ,y);
	}*/
       }
     break;

     case DERECHA:
      if(x<inicio+ancho)
      {
       moverse(++x,y);
       i++;
      }else
	if( longitud>=ancho && i<longitud) //crea un efecto de texto virtual, es decir recupera el texto que esta virtualmente a la derecha de la caja
	mostrar_texto_virtual( ++i-ancho );

     break;

     case DEL:
      if( longitud>0  && i<longitud)
      {
       longitud--;

       for(j=i;j<longitud;j++) //se saca el caracter i de la cadena, haciendo que la ultima parte de la cadena se desplace un caracter a la izquierda
	cad[j]=cad[j+1];

   //LO QUE SE MUESTRA EN PANTALLA
    //borra virtualmente
   mostrar_texto_virtual( i+inicio-x );

      }
     break;

     case HOME:
      x=inicio;
      i=0;
      moverse(x,y);
      mostrar_texto_virtual( i );

     break;

     case END:

      if( i<longitud)
      {
       if(longitud>ancho)
       {
	x=inicio+ancho;
	mostrar_texto_virtual( longitud-ancho );
       }
       else x+=(longitud-i);

       i=longitud;
       moverse(x,y);
      }

     break;

    }
   break;

   case BACKSPACE: //TECLA RETROCESO (BACKSPACE)

    if( i>0 && longitud>0 )
    {
     i--;
     longitud--;

     for(j=i;j<longitud;j++) //se saca el caracter i de la cadena, haciendo que la ultima parte de la cadena se desplace un caracter a la izquierda
      cad[j]=cad[j+1];

    if(x>inicio)x--;
     moverse(x,y);

    //LO QUE SE MUESTRA EN PANTALLA
    //borra virtualmente
    mostrar_texto_virtual( i+inicio-x );
    moverse(x,y);//retrocede el cursor


    }

    break;

   case ESC:
    *cad = NULL; //se anula la cadena
//    return c[0]; //se escapa
    break;

   default:
    if( c[0]==ENTER )
    {
      cad[longitud]='\0';
    }
    else
    {

     if(x<inicio+ancho)
      {
	x++;
	outtext( c ); //COUT AVANZA UN CARACTER
     }

     //si el cursor esta antes que el final de la cadena se inserta texto
      if(i<longitud)
       for(j=longitud;j>=i;j--) //se desplaza la cadena a partir de i un caracter a la derecha
	cad[j+1]=cad[j];

     longitud++;
     cad[i++]=c[0];

     //LO QUE SE MUESTRA EN PANTALLA

     //se muestra el texto insertado
     if(i<longitud)
       mostrar_texto_virtual( i+inicio-x );

     //si se esta al final de la caja de texto, se inserta el caracter
     // en este espacio y el primer caracter de la derecha se desplazara
     // virtualmente a la derecha
     if( longitud>=ancho && x==inicio+ancho)
      mostrar_texto_virtual( i-ancho );

    }

  }

 }//while(c[0]!='\0');

 return c[0];
}


#define VENTANA_PADRE  0
#define VENTANA_HIJA   1
#define VENTANA_SIN_TITULO 2
//DEFINE ORDENES QUE DETERMINAN SI EL USUARIO ACEPTA O NO ACEPTA LOS CAMBIOS QUE VA A MODIFICAR LA VENTANA
#define SE_CANCELA     0
#define SE_ACEPTA      1
//#define SIN_EVENTOS    2

class CVentana
{
 int margen_superior;

 public:

 int arriba_cliente;//coordenada superior del area cliente

 int arriba;
 int abajo;
 int izquierda;
 int derecha;

 int ancho;
 int alto;

 int tipo;

 char titulo[100];

 void far *lugar_prestado;

 CBoton Salir;

 CVentana(char *Titulo, int izq, int arr, int der, int aba )
 {
   CVentana::CVentana( Titulo, izq, arr, der, aba, VENTANA_HIJA);
 }

 CVentana( char *Titulo, int izq, int arr, int der, int aba, int Tipo )
 {
  strcpy(titulo, Titulo);

  if( Tipo == VENTANA_SIN_TITULO )
    margen_superior=0;
  else margen_superior=15;

  arriba=arr;
  abajo=aba;
  izquierda=izq;
  derecha=der;

  ancho=der-izq;
  alto=aba-arr;

  tipo=Tipo;

  arriba_cliente=arr+margen_superior;

 }

  virtual void Mostrar_ventana(void);
  virtual void Cerrar_ventana(void);
  virtual void Mover_ventana(Evento);
  virtual unsigned esperar_eventos( Evento &);
  unsigned responder_eventos( Evento &);

  void devolver_lugar(void);
  void mostrar_titulo(void);
  int puntero_en_area_de_titulo( Evento );

};
void CVentana::Mostrar_ventana(void)
{

 mousehide();
 if( tipo != VENTANA_PADRE )
 {
  unsigned int tamano;
  tamano=imagesize(izquierda,arriba,derecha,abajo);
  lugar_prestado=farmalloc(tamano);
  getimage(izquierda,arriba,derecha,abajo, lugar_prestado );
 }

 cuadro(izquierda, arriba, derecha, abajo, 1);

 if( tipo != VENTANA_SIN_TITULO )
 {
 cuadro(izquierda, arriba, derecha, arriba+margen_superior, 1, 1);
 mostrar_titulo();

 //Construye el boton X (salir)
 Salir = CBoton(derecha-margen_superior,arriba+(20*margen_superior)/100,
		  (70*margen_superior)/100,(75*margen_superior)/100,"X");
 Salir.mostrar(SIN_FOCO);
 }

 mouseshow();
}


void CVentana::Cerrar_ventana(void)
{
 devolver_lugar();
}

void CVentana::Mover_ventana(Evento raton)
{

 int dx=raton.x-izquierda, dy=raton.y-arriba;

 int arr=0, aba=0, izq=0, der=0;

  int color_actual=getcolor();
 // setwritemode(XOR_PUT);
//  setcolor(WHITE);

//  mousehide();

// int izq1=-1,arr1=-1;//,estado=0,estado1=0;  //0 =puntero detenido
					//1 =puntero en movimiento
				       // estado1 = estado_anterior

  do
  {


//  if( izq==izq1 && arr==arr1)
//  rectangle(izq,arr,der,aba);

//  izq1=izq;
  //arr1=arr;

  arr=raton.y-dy;
  izq=raton.x-dx;
  aba=arr+alto;
  der=izq+ancho;

//  if( izq==izq1 && arr==arr1) estado=0 else estado=1;
/*
  estado = ( izq!=izq1 || arr!=arr1);

   if(det==0)
    {
    */
     rectangulo_inverso(izq,arr,der,aba); //pinta un rectangulo de las dimensiones de la ventana
     //delay(5);
     rectangulo_inverso(izq,arr,der,aba); //borra el rectangulo anterior
   /* }
    else
    {
     rectangulo_inverso(izq1,arr1,izq1+ancho,arr1+alto); //borra el rectangulo anterior
     det=0;
    }
  }
  else
  if(det==0)
  {
//   cout<<"loco ";
   rectangulo_inverso(izq,arr,der,aba); //pinta un rectangulo de las dimensiones de la ventana
   det=1;
  }

  estado1=estado;
     */
  raton=Detectar_click_o_tecla();

  }while( raton.evento == LBUTTON_STILL_DOWN );

  //rectangulo_inverso(izq,arr,der,aba);

  //mouseshow();

  //setwritemode(COPY_PUT);

  devolver_lugar();

  arriba=arr;
  arriba_cliente=arr+margen_superior;
  abajo=aba;
  izquierda=izq;
  derecha=der;

  Mostrar_ventana();

  setcolor(color_actual);

}


unsigned CVentana::responder_eventos( Evento &raton)
{
 Mostrar_ventana();
 unsigned respuesta = esperar_eventos(raton);
 Cerrar_ventana();
 return respuesta;
}

unsigned CVentana::esperar_eventos( Evento &raton)
{

  raton=Detectar_click_o_tecla();

 if( tipo != VENTANA_SIN_TITULO )
  if( Salir.mostrar(raton) ) return SE_CANCELA;

  if( puntero_en_area_de_titulo(raton) && raton.evento==LBUTTON_DOWN )
  Mover_ventana(raton);

  return SE_ACEPTA;

}

void CVentana::devolver_lugar(void)
{
 if( tipo == VENTANA_HIJA )
 {
  mousehide();
  putimage(izquierda, arriba, lugar_prestado, COPY_PUT);
  mouseshow();
  farfree(lugar_prestado);
 }
}

void CVentana::mostrar_titulo()
{
// int longitud=strlen( titulo );
 int color_actual=getcolor();
 setcolor( WHITE );
 outtextxy(izquierda+margen_superior/2,arriba+margen_superior/3,titulo);
 setcolor(color_actual);

}

int CVentana::puntero_en_area_de_titulo(Evento raton)
{
 if( ( izquierda<raton.x && raton.x<derecha ) &&
     ( arriba<raton.y && raton.y<arriba_cliente ) ) return 1;
 else return 0;
}



//#include <iostream.h>

class CGrafico
{
 PCX pcx;

 int izq;
 int arr;
// int alto;
// int ancho;

 char nombre[12];

 public:

 CGrafico(){};

 CGrafico( int x, int y, char *Nombre)
 {
//  nombre = new char[ strlen(Nombre)+1 ];

  strcpy(nombre,Nombre);
//  cout<<nombre;

  izq=x;
  arr=y;
 // alto=pcx.alto;
 // ancho=pcx.alto;

   pcx.leer_cabecera(1,nombre);
 }

 /*
 ~CGrafico()
 {
  //delete nombre;
  } */

 void pintar(void);

};

void CGrafico::pintar(void)
 {
  pcx.Dibujar(izq,arr/*,nombre*/);
 }


class CMenu
{

 protected:

  int posx;
  int posy;
  int alto;
  int ancho;


 int numero_de_menus;

 CBoton *Menu;
 CVentana *marco_despliegue;

 public:
 CMenu(int _posx, int _posy, int _alto, int _ancho, int num_menus);
 inline ~CMenu(){ delete Menu; }

// void crear_submenus(void);

 //unsigned esperar_eventos( Evento &raton);

 /*
 void InsertarTitulo(int num_menu,Titulo)
 {
 // Menu[0].cambiar_titulo("")
 }
 */

};

 CMenu::CMenu(int _posx, int _posy, int _alto, int _ancho, int num_menus)
 {
  posx = _posx;
  posy = _posy;
  alto = _alto;
  ancho = _ancho;

  numero_de_menus=num_menus;

  Menu = new CBoton[numero_de_menus];

  int ancho_boton = ancho/numero_de_menus-1;
  for( int i=0;i<numero_de_menus;i++)
   Menu[i] = CBoton( posx+(ancho_boton+1)*i, posy, alto,ancho_boton ,"Hola");

  marco_despliegue = new CVentana("Menu",posx, posy, posx+100,
					posy+100, VENTANA_SIN_TITULO);

 }

/*
unsigned CMenu::esperar_eventos( Evento &raton)
{

 for(int i=0;i<numero_de_menus;i++)
 if( raton.tecla==ENTER || Menu[i].mostrar(raton) )
 {

    delete marco_despliegue;

    int x=Menu[i].posx, y=Menu[i].posy+Menu[i].alto+1;

    marco_despliegue = new CVentana("Menu",x,y, x+100, y+100,
				     VENTANA_SIN_TITULO);

  marco_despliegue->Mostrar_ventana();

  while(1)
  {
  crear_submenus();
  }

  return SE_ACEPTA;
 }

 return SE_CANCELA;

} */

/*
void CMenu::crear_submenus(int num_menu, int num_submenus)
{
} */
#endif

