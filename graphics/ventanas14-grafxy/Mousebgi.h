/******************************************************
MOUSEBGI.H
Rutinas para controlar el mouse:
gracias a Silvia Garcia - 16 Agosto 1999

MODIFICADA POR:
JOSE LUIS DE LA CRUZ LAZARO ramondc@hotmail.com

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
*******************************************************/

# ifndef __MOUSEBGI_H
# define __MOUSEBGI_H

# ifndef __DOS_H
# include <dos.h>
# endif
# ifndef __STDLIB_H
# include <stdlib.h>
# endif

//#include <string.h>
#include <iostream.h>

#ifndef __GRAPHICS_H
#include <graphics.h>
#endif

//#include <conio.h>
#ifndef __PCXBGI_H
#include "pcxbgi.h"
#endif

struct Evento
{
 int x;
 int y;
 unsigned int evento;
 char tecla;
};


Evento Detectar_click_o_tecla( void );

struct mousecursor
{
 void *puntero,*fondo;
 int x_anterior, y_anterior, x,y;
 int alto,ancho;
// unsigned char mascara;
}cursor;

////////////////////////////////////////////////////////////////////////
//CONSTANTES DE CONTROL

	/* mascaras de los botones del raton*/
	const unsigned LBUTTON   =0x0001; //boton izquierdo
	const unsigned RBUTTON   =0x0002; //boton derecho

	/*codigos de eventos del raton*/
	const unsigned IDLE                        =0x0000; //no hay eventos
	const unsigned BUTTON_DOWN                 =0xff01; //se presiono el boton principal del mouse
	const unsigned LBUTTON_DOWN                =0xff01; //se presiono el boton izquierdo del mouse
	const unsigned RBUTTON_DOWN                =0xff02; //se presiono el boton derecho del mouse
	const unsigned BUTTON_STILL_DOWN           =0xff04; //se mantiene presionado el boton principal
	const unsigned LBUTTON_STILL_DOWN          =0xff04; //se mantiene presionado el boton izquierdo
	const unsigned RBUTTON_STILL_DOWN          =0xff08; //se mantiene presionado el boton derecho
	const unsigned BUTTON_UP                   =0xff10; //se hizo click con el boton principal
	const unsigned LBUTTON_UP                  =0xff10; //se solto el boton izquierdo
	const unsigned RBUTTON_UP                  =0xff20; //se solto el boton derecho
	/*
	NOTA IMPORTANTE:
	cuando se presiona un boton del mouse se genera primero un evento
	DOWN ( cuando se presiona el boton ) luego un evento
	STILL_DOWN ( si se mantiene presionado ) y luego un evento
	UP ( cuando se suelta el boton )
	*/

	/* modos de video*/
	enum videomodetype{textscrn,lowresgr,Herculesgr,graphics};

	/*el raton*/
	struct mousestr{
		int oldx,oldy;
		char ok;
		char mouseoff;
		char lowres;
		char textmode;
		int x,y,dx,dy;
		char oculto;
	}mouse;

	/*utilerias del raton*/

	 const int mouseInt =0x33;
	 const int iret     =0xcf;
	 const int false    =0;
	 const int true     =1;

///////////////////////////////////////////////////////////////////
//FUNCIONES DE CONTROL ESTANDAR

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
 void movemouse(int , int );

 void mousesetup(enum videomodetype );

/*retorna la ubicacion del raton*/
 unsigned mousestatus(int *,int *);

/*devuelve la condicion de los botones*/
 unsigned Mbuttonstatus(void);

 int mpresscnt(unsigned );

 int mreleasecnt(unsigned );

/*obtiene el ultimo evento del raton */
 unsigned mouseevent(int *, int *);

 //espera por la ocurrencia de cualquier evento y retorna dicho evento
 unsigned mwaitforanyevent( int *, int *);

 //espera por la ocurrencia de un evento especifico y retorna dicho evento
 void mwaitforevent(unsigned , int * ,int *);

 //arroja 1 cuando el puntero se esta moviendo
 //y arroja 0 cuando el puntero esta estatico
 int mmoved(void);

/////////////////////////
//FUNCIONES DE CONTROL DE LA BGI

void obtener_cursor(void);
void obtener_fondo(void);
void recuperar_fondo(void);
void dibujar_puntero(void);
void actualizar_puntero( int &, int &);
//destruir los punteros utilizados por la bgi
int mousedestroy(void);
////////////////////////////////////////////////////////////////////////////
//IMPLEMENTACION DE LAS FUNCIONES DE CONTROL ESTANDAR

	 void mouseInit(void)
	 /*inicia el raton*/
	{
		mouse.ok =false;
		mouse.mouseoff=true;
	}

	int driverexist(void)
	/*devuelve cierto si esta instalado el driver del raton*/
	{
		void far *addres;
		addres=getvect(mouseInt);
		return (addres != NULL)&&(*(unsigned char far *) addres !=iret);
	}

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


	void mousehide(void)
	/*oculta el cursor del raton*/
	{
		union REGS regs;
		if(mouse.mouseoff) return;

		/*
		regs.x.ax=2;
		int86(mouseInt,&regs,&regs);
		*/

		if(mouse.oculto==0)
		{
		 WaitRetrace();
		 putimage(cursor.x_anterior,cursor.y_anterior, cursor.fondo, COPY_PUT);
		}
		mouse.oculto=1;

	}

	void mouseshow(void)
	/*muestra el cursor del raton*/
	{
		union REGS regs;
		if(mouse.mouseoff)return;
		/*
		regs.x.ax=1;
		int86(mouseInt,&regs,&regs);
		mousestatus(&(cursor.x),&(cursor.y));
		*/

	       //cursor.x=0;
	       cursor.x_anterior=-1;


		mouse.oculto=0;
	}

	void mouseoff(void)
	/*desactiva el raton*/
	{
		if(mouse.ok && !mouse.mouseoff){
			mousehide();
			mouse.mouseoff=true;
		}
	}

	void mouseon(void)
	/*activa el raton*/
	{
		if(mouse.ok && mouseoff){
			mouse.mouseoff=false;
			mouseshow();
		}
	}

	void movemouse(int Mx, int My)
	/* mueve el cursor del raton*/
	{
		union REGS regs;
		if(mouse.mouseoff)return;
		regs.x.ax=4;
		regs.x.cx=Mx;
		regs.x.dx=My;
		if(mouse.textmode){
			regs.x.cx <<=3;
			regs.x.dx <<=3;
		}
		if(mouse.lowres)regs.x.cx <<=1;
		int86(mouseInt,&regs,&regs);
	}

	void mousesetup(enum videomodetype videomodo)
	{
		union REGS regs;
		mouse.ok=driverexist();
		if(mouse.ok){
			regs.x.ax=0;
			int86(mouseInt,&regs,&regs);
			if(regs.x.ax==0) mouse.ok =false;
		}
		if(!mouse.ok){
			mouseoff();
			return;
		}
		mouseon();

		obtener_cursor();

		if(videomodo==textscrn) mouse.textmode=true;
		else mouse.textmode=false;
		if(videomodo==lowresgr)mouse.lowres=true;
		else mouse.lowres=false;
		mouse.oldx=0;       	mouse.oldy=0;
		mouse.x=0;		mouse.y=0;
		mouse.dx=0;		mouse.dy=0;
		movemouse(0,0);
		mouse.oculto=1;

	}

	unsigned mousestatus(int *Mx,int *My)
	/*retorna la ubicacion del raton*/

	{
		union REGS regs;
		if(mouse.mouseoff){ *Mx=0; *My=0; return 0; }
		regs.x.ax =3;
		int86(mouseInt, &regs,&regs);
		*Mx=regs.x.cx;  *My=regs.x.dx;
		if(mouse.textmode)
		{
			*Mx >>=3;
			*My >>=3;
		}
		if(mouse.lowres)  *Mx>>=1;

	      if(!mouse.oculto)
	      {
	       //delay(5);
	       actualizar_puntero(*Mx,*My);
	      }
//	      else recuperar_fondo();

		return regs.x.bx;
	}

	unsigned Mbuttonstatus(void)
	/*devuelve la condicion de los botones*/
	{
		int Mx,My;
		if(mouse.mouseoff)return 0;
		else
		return mousestatus(&Mx,&My);
	}



	int mpresscnt(unsigned buttonmask)
	{
		union REGS regs;
		if(mouse.mouseoff)return 0;
		regs.x.ax=5;
		regs.x.bx=buttonmask >>1;
		int86(mouseInt,&regs,&regs);
		return regs.x.bx;
	}

	int mreleasecnt(unsigned buttonmask)
	{
		union REGS regs;
		if(mouse.mouseoff)return 0;
		regs.x.ax=6;
		regs.x.bx=buttonmask >>1;
		int86(mouseInt,&regs,&regs);
		return regs.x.bx;
	}

	unsigned mouseevent(int *Mx, int *My)
		/*obtiene el ultimo evento del raton */

	{
		unsigned E;
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

		return E;
	 }

	 unsigned mwaitforanyevent( int *Mx, int *My)
	 {
		unsigned E;

		if(mouse.mouseoff){  *Mx=0;  *My=0; return IDLE;   }
		do{
			E=mouseevent(Mx,My);
		 }while(E==IDLE);
		 return E;
	 }

	 void mwaitforevent(unsigned E, int *Mx ,int *My)
	 {
		 unsigned entry;
		 if(mouse.mouseoff){ *Mx=0;  *My=0; return; }
		 do{
			entry=mouseevent(Mx,My);
		 }while(entry!=E);
	 }

	 int mmoved(void)
	 {
		if(mouse.mouseoff)return false;

		 mouse.oldx=mouse.x;       mouse.oldy=mouse.y;
		 mousestatus(&mouse.x,&mouse.y);
		 mouse.dx=mouse.x-mouse.oldx;     mouse.dy=mouse.y-mouse.oldy;
		 return(mouse.dx!=0) || (mouse.dy!=0);
	 }

//IMPLEMENTACION DE LAS FUNCIONES DE CONTROL DE LA BGI

//se carga el cursor de un archivo grafico pcx
void obtener_cursor(void)
{
// cursor.puntero=NULL;
// cursor.fondo=NULL;

 PCX cursorpcx;

 cursorpcx.leer_cabecera(0,"cursor.pcx");
 cursorpcx.Dibujar(0,0/*,"cursor.pcx"*/);

 cursor.alto = cursorpcx.alto-1;
 cursor.ancho = cursorpcx.ancho-1;
 unsigned tamano;
 tamano=imagesize(0,0,cursor.ancho,cursor.alto);
 cursor.puntero=malloc(tamano);
 getimage(0,0,cursor.ancho,cursor.alto,cursor.puntero );

 cursor.x_anterior=cursor.y_anterior=1;
 cursor.x=cursor.y=0;

}

//se guarda el fondo sobre el cual se va desplegar el puntero
void obtener_fondo(void)
{
  cursor.x_anterior=cursor.x;
  cursor.y_anterior=cursor.y;
  unsigned int tamano;
  tamano=imagesize(cursor.x,cursor.y,cursor.x+cursor.ancho,cursor.y+cursor.alto);
/*  if( !(cursor.fondo) )
  {*/
   cursor.fondo=malloc(tamano);
   getimage(cursor.x,cursor.y,cursor.x+cursor.ancho,cursor.y+cursor.alto,cursor.fondo );
 // }
}


//se recupera el fondo sobre el cual se va desplegar el puntero
void recuperar_fondo(void)
{
/*  if( cursor.fondo )
  {*/
  WaitRetrace();
  putimage(cursor.x_anterior,cursor.y_anterior, cursor.fondo, COPY_PUT);
  free(cursor.fondo);
//  cursor.fondo=NULL;
 /* }*/
}

//dibuja el puntero en la posicion actual
void dibujar_puntero(void)
{
  WaitRetrace();
  putimage(cursor.x,cursor.y, cursor.puntero, COPY_PUT);
}

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

//destruir los punteros utilizados
  int mousedestroy(void)
  {
   if( cursor.puntero ) //destruye el puntero a el cursor
    free(cursor.puntero);
   if( cursor.fondo ) //destruye el puntero al fondo
    free(cursor.fondo);
    cursor.puntero=NULL;
    cursor.fondo=NULL;
  }


/////////////////////////////////////
//IMPLEMENTACION DE EVENTOS
Evento Detectar_click_o_tecla( void )
{
 Evento p;

 p.evento=0;
 p.tecla=-1;

 p.evento=mouseevent( &(p.x), &(p.y) );

  if( kbhit() )
  {
    p.tecla=getch();
   // if(p.tecla==0)getch();
  }

 return p;
}



#endif