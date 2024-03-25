#pragma once
/******************************************************
MOUSEBGI.H
Rutinas para controlar el mouse:

MODIFICADO POR:
Jos‚ Luis De la Cruz L zaro
correos:
 jcruz@ec-red.com
 ramondc@hotmail.com

P gina Web (El Mundo del Caos):
 http://www.geocities.com/joseluisdl

ICQ: 46906401

 Universidad Nacional de Ingenier¡a
  Facultad de Ingenier¡a El‚ctrica y Electr¢nica
 Lima - Per£

Version 1.1a 06 - Agosto - 2000
-Ya pas¢ casi un a¤o desde que Silvia me dio el fuente original del
 presente. Y pues eso merece nuevas mejoras...
-Ahora se soporta el cursor estandar en el modo grafico
 320x200 256 colores, y tambien el cursor estandar en modo texto.
-Se agrego las estructuras originales para cargar cursores estandar
 ( arrowcursor, handcursor y cruz )
-La funcion mousesetup es modificada para seleccionar el modo grafico
 y el tipo de cursor estandar a utilizar (por defecto es el arrowcursor)

Version 1.1 - 28 Jun 1999
-Se borra el puntero despues de dibujarlo temporalmente para cargarlo a
 memoria ( ver funcion obtener_cursor )

Version 1.0b - 28 Dic 1999
-Se agrega una pausa de 5 milisegundos antes de llamar a la funcion
 "actualizar_puntero", esto se hace para mover el puntero del mouse
 suavemente por la pantalla, antes de esto el puntero se movia haciendo
 algunas pausas. Todo esto tiene lugar en la implementacion de la funcion
 "mousestatus".

Version 1.0a - 16 Nov 1999
-Se agregan comentarios detallados sobre el funcionamiento de todas
 las funciones

Version 1.0 - 11 Sep 1999
- Modificacion de las rutinas originales
  correspondientes a la cabecera mousec.h que trabaja solo con el
  modo grafico en 16 colores
- se trabaja perfectamente en el modo grafico de 256 colores
  mediante con el controlador bgi svga256.bgi, esto se hace mediante las
  funciones de control para la bgi creadas para este fin.

Version 0 - 11 Agosto 1999
- Fuentes originales extraidos de MOUSEC.H
- gracias a Silvia Garcia - 16 Agosto 1999

*******************************************************/
//# include <dos.h>
//# include <stdlib.h>
#include "graphics.h"
//#include <conio.h>
//#include "pcxbgi.h"
#include <vector>

//Estructura que almacena los eventos generados por el rat¢n y teclado
struct Evento
{
	int x;	//posici¢n x del puntero del rat¢n
	int y; //posici¢n y del puntero del rat¢n
	unsigned int evento; //Evento actual del rat¢n (ver definici¢n de codigos de Eventos m s abajo)
	char tecla; //si se presiona alguna tecla desde el teclado, se almacena aqu¡ su codigo ASCII
};


//Retorna una estructura Evento, con los eventos generados por el rat¢n y teclado
Evento Detectar_click_o_tecla(void);
/*
struct mousecursor
{
 void *puntero,*fondo;
 int x_anterior, y_anterior, x,y;
 int alto,ancho;
// unsigned char mascara;
}cursor;
*/
////////////////////////////////////////////////////////////////////////
//CONSTANTES DE CONTROL

	// mascaras de los botones del raton
	/*const unsigned LBUTTON   =0x0001; //boton izquierdo
	const unsigned RBUTTON   =0x0002; //boton derecho*/

	// codigos de eventos del raton
const unsigned IDLE = 0x0000; //no hay eventos
//const unsigned BUTTON_DOWN                 =0xff01; //se presiono el boton principal del mouse
const unsigned LBUTTON_DOWN = 0xff01; //se presiono el boton izquierdo del mouse
const unsigned RBUTTON_DOWN = 0xff02; //se presiono el boton derecho del mouse
/*const unsigned BUTTON_STILL_DOWN           =0xff04; //se mantiene presionado el boton principal
const unsigned LBUTTON_STILL_DOWN          =0xff04; //se mantiene presionado el boton izquierdo
const unsigned RBUTTON_STILL_DOWN          =0xff08; //se mantiene presionado el boton derecho
const unsigned BUTTON_UP                   =0xff10; //se hizo click con el boton principal
const unsigned LBUTTON_UP                  =0xff10; //se solto el boton izquierdo
const unsigned RBUTTON_UP                  =0xff20; //se solto el boton derecho*/
/*
NOTA IMPORTANTE:
cuando se presiona un boton del mouse se genera primero un evento
DOWN ( cuando se presiona el boton ) luego un evento
STILL_DOWN ( si se mantiene presionado ) y luego un evento
UP ( cuando se suelta el boton )
*/
/*
// modos de video
enum videomodetype { texto, egavga, svga, svga320x200, lowresgr };

// el raton
struct mousestr{
	int oldx,oldy;
	char ok;
	char mouseoff;
	char lowres;
	char textmode;
	char cursorestandar;
	int x,y,dx,dy;
	char oculto;
}mouse;

// utilerias del raton

 const int mouseInt =0x33;
 const int iret     =0xcf;
 const int false    =0;
 const int true     =1;

// define estilos de cursor graficos
struct hotspotstruct{ int x, y; };

struct mousecursorestandar
{
	struct hotspotstruct hotspot;
	unsigned screenmask[16];
	unsigned cursormask[16];
};

 const struct mousecursorestandar arrowcursor={
 {0,0},
 { 0x3fff, 0x1fff,0x0fff,0x07ff,
   0x03ff, 0x01ff,0x00ff,0x007f,
   0x003f, 0x00ff,0x01ff,0x10ff,
   0x30ff, 0xf87f,0xf87f,0xfc3f },
 { 0x0000, 0x4000,0x6000,0x7000,
   0x7800, 0x7c00,0x7e00,0x7f00,
   0x7f80, 0x7e00,0x7c00,0x4600,
   0x0600, 0x0300,0x0300,0x0180 }
   };

   const struct mousecursorestandar handcursor={
   {4,0},
   {0xf3ff, 0xe1ff,0xe1ff,0xe1ff,
   0xe001,0xe000,0xe000,0xe000,
   0x8000,0x0000,0x0000,0x0000,
   0x0000,0x0000,0x8001,0xc003, },
 { 0x0c00,0x1200,0x1200,0x1200,
   0x13fe,0x1249,0x1249,0x1249,
   0x7249,0x9001,0x9001,0x9001,
   0x8001,0x8001,0x4002,0x3ffc  }
   };

   const struct mousecursorestandar cruz={
   {8,8},
   {0xfe7f,0xfe7f,0xfe7f,0xfe7f,
   0xfe7f,0xfe7f,0xfe7f,0x0000,
   0x0000,0xfe7f,0xfe7f,0xfe7f,
   0xfe7f,0xfe7f,0xfe7f,0xfe7f},
   {0x0180,0x0180,0x0180,0x0180,
   0x0180,0x0180,0x0180,0xfe7f,
   0xfe7f,0x0180,0x0180,0x0180,
   0x0180,0x0180,0x0180,0x0180}
   };
*/

///////////////////////////////////////////////////////////////////
//FUNCIONES DE CONTROL ESTANDAR
#ifdef _XXX
/*inicia el raton*/
void mouseInit(void);

/*devuelve cierto si esta instalado el driver del raton*/
int driverexist(void);

/* Esta funci¢n sirve para testear el rat¢n.*/
int mtest(void);

/*oculta el cursor del raton*/
void mousehide(void);

/*muestra el cursor del raton*/
void mouseshow(void);

/*desactiva el raton*/
void mouseoff(void);

/*activa el raton*/
void mouseon(void);

/* mueve el cursor del raton*/
void movemouse(int, int);

void mousesetup(enum videomodetype, const struct mousecursorestandar);

/*retorna la ubicacion del raton*/
unsigned mousestatus(int *, int *);

/*devuelve la condicion de los botones*/
unsigned Mbuttonstatus(void);

int mpresscnt(unsigned);

int mreleasecnt(unsigned);
#endif
/*obtiene el ultimo evento del raton */
unsigned int mouseevent(int&, int&);

#ifdef _XXX
//espera por la ocurrencia de cualquier evento y retorna dicho evento
unsigned mwaitforanyevent(int *, int *);

//espera por la ocurrencia de un evento especifico y retorna dicho evento
void mwaitforevent(unsigned, int *, int *);

//arroja 1 cuando el puntero se esta moviendo
//y arroja 0 cuando el puntero esta estatico
int mmoved(void);
void setmgcursor(const struct mousecursorestandar *);
#endif
/////////////////////////
//FUNCIONES DE CONTROL DE LA BGI
/*
int obtener_cursor(void);
void obtener_fondo(void);
void recuperar_fondo(void);
void dibujar_puntero(void);
void actualizar_puntero( int &, int &);
//destruir los punteros utilizados por la bgi
void mousedestroy(void);
void WaitRetrace();*/
////////////////////////////////////////////////////////////////////////////
//IMPLEMENTACION DE LAS FUNCIONES DE CONTROL ESTANDAR
#ifdef _XXX
////////////////////////////////////////////////////////////////////////////
void mouseInit(void)
/*inicia el raton*/
{
	mouse.ok = false;
	mouse.mouseoff = true;
}
////////////////////////////////////////////////////////////////////////////
int driverexist(void)
/*devuelve cierto si esta instalado el driver del raton*/
{
	void far *addres;
	addres = getvect(mouseInt);
	return (addres != NULL) && (*(unsigned char far *) addres != iret);
}
////////////////////////////////////////////////////////////////////////////
	/* Esta funci¢n sirve para testear el rat¢n.*/
int mtest(void)
{
	/* Retorna: 0 => no hay rat¢n instalado.        */
	/*          n => el n£mero de botones del rat¢n.*/
	union REGS regs;

	regs.x.ax = 0x0;
	int86(0x33, &regs, &regs);
	if (regs.x.ax > 0) return regs.x.bx; /* n£mero de botones */
	else return 0;
}
////////////////////////////////////////////////////////////////////////////
void mousehide(void)
/*oculta el cursor del raton*/
{
	union REGS regs;
	if (mouse.mouseoff) return;

	if (!mouse.textmode)
		WaitRetrace();

	if (mouse.cursorestandar)   //muestras el cursor del mouse mediante los graficos estandar del controlador actual ( texto, egavga )
	{
		regs.x.ax = 2;
		int86(mouseInt, &regs, &regs);
	}
	else  //muestra el cursor del mouse utilizando un bitmap ( svga )
	{
		if (mouse.oculto == 0)
			putimage(cursor.x_anterior, cursor.y_anterior, cursor.fondo, COPY_PUT);
	}

	mouse.oculto = 1;

}
////////////////////////////////////////////////////////////////////////////
void mouseshow(void)
/*muestra el cursor del raton*/
{
	union REGS regs;
	if (mouse.mouseoff)return;

	//cursor.x=0;
	if (mouse.cursorestandar) //modo texto y egavga
	{
		regs.x.ax = 1;
		int86(mouseInt, &regs, &regs);
		mousestatus(&(cursor.x), &(cursor.y));
	}
	else //modo svga
		cursor.x_anterior = -1;

	mouse.oculto = 0;
}
////////////////////////////////////////////////////////////////////////////
void mouseoff(void)
/*desactiva el raton*/
{
	if (mouse.ok && !mouse.mouseoff) {
		mouse.mouseoff = true;
		mousehide();
	}
}
////////////////////////////////////////////////////////////////////////////
void mouseon(void)
/*activa el raton*/
{
	if (mouse.ok && mouseoff) {
		mouse.mouseoff = false;
		mouse.oculto = 1;
	}
}
////////////////////////////////////////////////////////////////////////////

void movemouse(int Mx, int My)
/* mueve el cursor del raton*/
{
	union REGS regs;
	if (mouse.mouseoff)return;
	regs.x.ax = 4;
	regs.x.cx = Mx;
	regs.x.dx = My;
	if (mouse.textmode) {
		regs.x.cx <<= 3;
		regs.x.dx <<= 3;
	}
	if (mouse.lowres)regs.x.cx <<= 1;
	int86(mouseInt, &regs, &regs);
	Mx = mousex();
	My = mousey();
}

////////////////////////////////////////////////////////////////////////////
void mousesetup(enum videomodetype videomodo,
	const struct mousecursorestandar newcursor = arrowcursor)
{
	union REGS regs;
	mouse.ok = driverexist();
	if (mouse.ok) {
		regs.x.ax = 0;
		int86(mouseInt, &regs, &regs);
		if (regs.x.ax == 0) mouse.ok = false;
	}

	if (!mouse.ok)
	{
		mouseoff();
		return;
	}

	if (videomodo == svga) mouse.cursorestandar = false;
	else mouse.cursorestandar = true;

	if (!mouse.cursorestandar)
		if (!obtener_cursor())
		{
			mouseoff();
			return;
		}

	mouseon();
	setmgcursor(&newcursor);

	if (videomodo == texto) mouse.textmode = true;
	else mouse.textmode = false;
	if (videomodo == svga320x200)mouse.lowres = true;
	else mouse.lowres = false;


	mouse.oldx = 0;       	mouse.oldy = 0;
	mouse.x = 0;		mouse.y = 0;
	mouse.dx = 0;		mouse.dy = 0;
	movemouse(0, 0);
	mouse.oculto = 1;

}
////////////////////////////////////////////////////////////////////////////
unsigned mousestatus(int *Mx, int *My)
/*retorna la ubicacion del raton*/

{
	union REGS regs;
	if (mouse.mouseoff) { *Mx = 0; *My = 0; return 0; }
	regs.x.ax = 3;
	int86(mouseInt, &regs, &regs);
	*Mx = regs.x.cx;  *My = regs.x.dx;
	if (mouse.textmode)
	{
		*Mx >>= 3;
		*My >>= 3;
	}
	if (mouse.lowres)  *Mx >>= 1;

	if (!mouse.cursorestandar)
	{
		if (!mouse.oculto)
			actualizar_puntero(*Mx, *My);
	}
	else
	{
		cursor.x = *Mx;
		cursor.y = *My;
	}
	//	      else recuperar_fondo();

	return regs.x.bx;
}
////////////////////////////////////////////////////////////////////////////
unsigned Mbuttonstatus(void)
/*devuelve la condicion de los botones*/
{
	int Mx, My;
	if (mouse.mouseoff)return 0;
	else
		return mousestatus(&Mx, &My);
}
////////////////////////////////////////////////////////////////////////////
int mpresscnt(unsigned buttonmask)
{
	union REGS regs;
	if (mouse.mouseoff)return 0;
	regs.x.ax = 5;
	regs.x.bx = buttonmask >> 1;
	int86(mouseInt, &regs, &regs);
	return regs.x.bx;
}
////////////////////////////////////////////////////////////////////////////
int mreleasecnt(unsigned buttonmask)
{
	union REGS regs;
	if (mouse.mouseoff)return 0;
	regs.x.ax = 6;
	regs.x.bx = buttonmask >> 1;
	int86(mouseInt, &regs, &regs);
	return regs.x.bx;
}
#endif
bool bLBUTTONPRESSED = false;
bool bRBUTTONPRESSED = false;
bool bMOUSEMOVE = false;

void OnLButtonDown(int x, int y) {
	bLBUTTONPRESSED = true;
}

void OnRButtonDown(int x, int y) {
	bRBUTTONPRESSED = true;
}

void OnMButtonDown(int x, int y) {
}

void OnLButtonUp(int x, int y) {
	bLBUTTONPRESSED = false;
}

void OnRButtonUp(int x, int y) {
	bRBUTTONPRESSED = false;
}

void OnMButtonUp(int x, int y) {
}

void OnMouseMove(int x, int y) {

}

void RegistrarEventosMouse() {
	registermousehandler(WM_LBUTTONDOWN, OnLButtonDown);
	registermousehandler(WM_RBUTTONDOWN, OnRButtonDown);
	registermousehandler(WM_MBUTTONDOWN, OnMButtonDown);
	registermousehandler(WM_LBUTTONUP, OnLButtonUp);
	registermousehandler(WM_RBUTTONUP, OnRButtonUp);
	registermousehandler(WM_MBUTTONUP, OnMButtonUp);
	registermousehandler(WM_MOUSEMOVE, OnMouseMove);
}

////////////////////////////////////////////////////////////////////////////
unsigned int mouseevent(int& Mx, int& My)
/*obtiene el ultimo evento del raton */

{
	unsigned int E;

	if (bLBUTTONPRESSED) {
		E = LBUTTON_DOWN;
		//cleardevice();
		//outtext("L");			
	}
	else if (bRBUTTONPRESSED) {
		E = RBUTTON_DOWN;
		//cleardevice();
		//outtext("R");

	}
	else
		E = IDLE;

	Mx = mousex();
	My = mousey();

	/*
	//unsigned int E;

	std::vector<int> vkinds = { WM_LBUTTONDOWN, WM_RBUTTONDOWN, WM_MBUTTONDOWN, WM_LBUTTONUP, WM_RBUTTONUP, WM_MBUTTONUP };

	for (auto kind : vkinds) {
		if (ismouseclick(kind)) {
			clearmouseclick(kind);
		}
	}
	*/

	return E;

	/*unsigned E;
	if(mouse.mouseoff){ *Mx=0;  *My=0; return IDLE;}

	E=mousestatus(Mx,My);
	//si no se presiona ningun boton

	if(E==0)
	{
		if(mpresscnt(LBUTTON)>0) E=LBUTTON_DOWN;
	else	if(mpresscnt(RBUTTON)>0) E=RBUTTON_DOWN;
	else	if(mreleasecnt(LBUTTON)>0) E=LBUTTON_UP;
	else	if(mreleasecnt(RBUTTON)>0) E=RBUTTON_UP;
	}
	//si se presiona por lo menos un boton a la vez
	else
	{
	 if( E & LBUTTON)
	  {
	   if(mpresscnt(LBUTTON)>0)
	   E=LBUTTON_DOWN;
	   else
	   E=LBUTTON_STILL_DOWN;
	  }
	 else if(mpresscnt(RBUTTON)>0)
		  E=RBUTTON_DOWN;
		  else
		  E=RBUTTON_STILL_DOWN;
	}

	return E;*/
}
////////////////////////////////////////////////////////////////////////////
/*	 unsigned mwaitforanyevent( int *Mx, int *My)
	 {
		unsigned E;

		if(mouse.mouseoff){  *Mx=0;  *My=0; return IDLE;   }
		do{
			E=mouseevent(Mx,My);
		 }while(E==IDLE);
		 return E;
	 }
////////////////////////////////////////////////////////////////////////////
	 void mwaitforevent(unsigned E, int *Mx ,int *My)
	 {
		 unsigned entry;
		 if(mouse.mouseoff){ *Mx=0;  *My=0; return; }
		 do{
			entry=mouseevent(Mx,My);
		 }while(entry!=E);
	 }
////////////////////////////////////////////////////////////////////////////
	 int mmoved(void)
	 {
		if(mouse.mouseoff)return false;

		 mouse.oldx=mouse.x;       mouse.oldy=mouse.y;
		 //mousestatus(&mouse.x,&mouse.y);
		 mouse.dx=mouse.x-mouse.oldx;     mouse.dy=mouse.y-mouse.oldy;
		 return(mouse.dx!=0) || (mouse.dy!=0);
	 }
////////////////////////////////////////////////////////////////////////////

	 void setmgcursor (const struct mousecursorestandar *newcursor)
	 {
		union  REGS regs;
		 struct SREGS sregs;
		 if(mouse.mouseoff)return;
		 regs.x.ax=9;
		 regs.x.bx=newcursor ->hotspot.x;
		 regs.x.cx=newcursor ->hotspot.y;
		 regs.x.dx=FP_OFF(newcursor->screenmask);
		 sregs.es =FP_SEG(newcursor->screenmask);
		 int86x(mouseInt,&regs,&regs,&sregs);
	 }

////////////////////////////////////////////////////////////////////////////
//IMPLEMENTACION DE LAS FUNCIONES DE CONTROL DE LA BGI

////////////////////////////////////////////////////////////////////////////
//se carga el cursor de un archivo grafico pcx
int obtener_cursor(void)
{

 PCX cursorpcx;

 if( !cursorpcx.leer_cabecera(0,"cursor.pcx") ) return 0;
 //dibuja temporalmente el puntero para cargarlo en la memoria
 cursorpcx.Dibujar(0,0);
 //dimensiones del puntero
 cursor.alto = cursorpcx.alto-1;
 cursor.ancho = cursorpcx.ancho-1;
 //carga el puntero en memoria
 unsigned int tamano;
 tamano=imagesize(0,0,cursor.ancho,cursor.alto);
 cursor.puntero=malloc(tamano);
 getimage(0,0,cursor.ancho,cursor.alto,cursor.puntero );
 //borra el puntero temporal
 setfillstyle(1,0);
 bar(0,0,cursor.ancho,cursor.alto);

 cursor.x_anterior=cursor.y_anterior=1;
 cursor.x=cursor.y=0;

 return 1;

}
////////////////////////////////////////////////////////////////////////////
//se guarda el fondo sobre el cual se va desplegar el puntero
void obtener_fondo(void)
{
  cursor.x_anterior=cursor.x;
  cursor.y_anterior=cursor.y;
  unsigned int tamano;
  tamano=imagesize(cursor.x,cursor.y,cursor.x+cursor.ancho,cursor.y+cursor.alto);
   cursor.fondo=malloc(tamano);
   getimage(cursor.x,cursor.y,cursor.x+cursor.ancho,cursor.y+cursor.alto,cursor.fondo );
}

////////////////////////////////////////////////////////////////////////////
//se recupera el fondo sobre el cual se va desplegar el puntero
void recuperar_fondo(void)
{
  WaitRetrace();
  putimage(cursor.x_anterior,cursor.y_anterior, cursor.fondo, COPY_PUT);
  free(cursor.fondo);
}
////////////////////////////////////////////////////////////////////////////
//dibuja el puntero en la posicion actual
void dibujar_puntero(void)
{
  WaitRetrace();
  putimage(cursor.x,cursor.y, cursor.puntero, COPY_PUT);
}
////////////////////////////////////////////////////////////////////////////
//se dibuja el puntero solo si el cursor esta en movimiento
void actualizar_puntero( int &x, int &y)
{

  if( cursor.x!=cursor.x_anterior || cursor.y!=cursor.y_anterior )
  {
   obtener_fondo();
   dibujar_puntero();
  }
	cursor.x=x;
	cursor.y=y;

  if( cursor.x!=cursor.x_anterior || cursor.y!=cursor.y_anterior && cursor.x_anterior!=-1)
   recuperar_fondo();

}
////////////////////////////////////////////////////////////////////////////
//destruir los punteros utilizados
  void mousedestroy(void)
  {
   if( cursor.puntero ) //destruye el puntero a el cursor
	free(cursor.puntero);
   if( cursor.fondo ) //destruye el puntero al fondo
	free(cursor.fondo);
	cursor.puntero=NULL;
	cursor.fondo=NULL;
  }

////////////////////////////////////////////////////////////////////////////

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
/////////////////////////////////////
//IMPLEMENTACION DE EVENTOS
Evento Detectar_click_o_tecla(void)
{
	Evento p;

	p.evento = 0;
	p.tecla = -1;

	p.evento = mouseevent(p.x, p.y);

	if (kbhit())
	{
		p.tecla = getch();
	}

	return p;
}


