/******************************************************
MOUSEC.H
Rutinas para controlar el mouse:
gracias a Silvia Garcia 16/08/1999

11/09/1999
MODIFICADA POR:
JOSE LUIS DE LA CRUZ LAZARO ramondc@hotmail.com
*******************************************************/

# ifndef __MOUSEBGI_H
# define __MOUSEBGI_H

# ifndef __DOS_H
# include <dos.h>
# endif
# ifndef __STDLIB_H
# include <stdlib.h>
# endif

#include <graphics.h>
#include <conio.h>
//#include "c:\bc31\graficas\ventanas\mousec.h"

#include "pcxbgi.h"

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
	const unsigned BUTTON_DOWN                 =0xff01; //se solto el boton principal del mouse
	const unsigned LBUTTON_DOWN                =0xff01; //se solto el boton izquierdo del mouse
	const unsigned RBUTTON_DOWN                =0xff02; //se solto el boton derecho del mouse
	const unsigned BUTTON_STILL_DOWN           =0xff04; //se mantiene presionado el boton principal
	const unsigned LBUTTON_STILL_DOWN          =0xff04; //se mantiene presionado el boton izquierdo
	const unsigned RBUTTON_STILL_DOWN          =0xff08; //se mantiene presionado el boton derecho
	const unsigned BUTTON_UP                   =0xff10; //se hizo click con el boton derecho
	const unsigned LBUTTON_UP                  =0xff10; //se mantiene presionado el boton derecho
	const unsigned RBUTTON_UP                  =0xff20; //se mantiene presionado el boton derecho

	/*define estilos de cursor graficos*/
	/*
	struct hotspotstruct{ int x, y; };

	struct mousecursor
	{
		struct hotspotstruct hotspot;
		unsigned screenmask[16];
		unsigned cursormask[16];
	};
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
//FUNCIONES DE CONTROL

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

 unsigned mwaitforanyevent( int *, int *);

 void mwaitforevent(unsigned , int * ,int *);

 int mmoved(void);

 void setmgcursor (const struct mousecursor *newcursor);
/////////////////////////
//PARA LA BGI
void obtener_cursor(void);
void obtener_fondo(void);
void recuperar_fondo(void);
void dibujar_puntero(void);
void actualizar_puntero( int &, int &);

////////////////////////////////////////////////////////////////////////////
//IMPLEMENTACION DE LAS FUNCIONES

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

		if(mouse.oculto==0)putimage(cursor.x_anterior,cursor.y_anterior, cursor.fondo, COPY_PUT);

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
		*/
		//mousestatus(&(cursor.x),&(cursor.y));
		cursor.x_anterior=-1;
		cursor.x=0;
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
		cleardevice();

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

	      if(!mouse.oculto)actualizar_puntero(*Mx,*My);
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
		//sin no se presiona ningun boton

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
/*
	 void setmgcursor (const struct mousecursor *newcursor)
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
	 const struct mousecursor arrowcursor={
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

	   const struct mousecursor handcursor={
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

	   const struct mousecursor cruz={
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

//MOUSEBGI.H


void obtener_cursor(void)
{
 PCX cursorpcx;
 cursorpcx.Dibujar(0,0,16,"cursor.pcx");
 cursor.alto=cursorpcx.alto-1;
 cursor.ancho=cursorpcx.ancho-1;
 unsigned int tamano;
 tamano=imagesize(0,0,cursor.ancho,cursor.alto);
 cursor.puntero=malloc(tamano);
 getimage(0,0,cursor.ancho,cursor.alto,cursor.puntero );

 cursor.x_anterior=cursor.y_anterior=1;
 cursor.x=cursor.y=0;

 //se busca la mascara el color rgb (0,255,0) (VERDE)
 /*
 for(x=0;x<256;x++)
  if( cursor.paleta[x][0]==0 && cursor.paleta[x][1]==255 && cursor.paleta[x][2]==0 )
  {
   mascara=x;
   break;
  }
 */
}

void obtener_fondo(void)
{
  cursor.x_anterior=cursor.x;
  cursor.y_anterior=cursor.y;
  unsigned int tamano;
  tamano=imagesize(cursor.x,cursor.y,cursor.x+cursor.ancho,cursor.y+cursor.alto);
  cursor.fondo=malloc(tamano);
  getimage(cursor.x,cursor.y,cursor.x+cursor.ancho,cursor.y+cursor.alto,cursor.fondo );
}



void recuperar_fondo(void)
{
  //mousehide();
  putimage(cursor.x_anterior,cursor.y_anterior, cursor.fondo, COPY_PUT);
//  mouseshow();
  free(cursor.fondo);
}

void dibujar_puntero(void)
{
 /*setfillstyle(1,2);
 bar(x,y,x+ancho,y+alto);
 */
 /*
 for(i=0;i<ancho;i++)
 for(j=0;j<alto;j++)
 putpixel(x+i,y+j,getpixel(x+i,y+j)^mascara);
   */
  putimage(cursor.x,cursor.y, cursor.puntero, COPY_PUT);


}

void actualizar_puntero( int &x, int &y)
{
// ModoGrafico();

// obtener_cursor();

// PCX pcx;
// pcx.Dibujar(0,0,"c:\\windows\\escrit~1\\nena.pcx");

// mousesetup(graphics);

// mouseshow();

// while(!kbhit())
// {
  if( cursor.x!=cursor.x_anterior || cursor.y!=cursor.y_anterior )
  {
   obtener_fondo();
   dibujar_puntero();
  }
    cursor.x=x;
    cursor.y=y;
//    mousestatus(&x,&y);
  if( cursor.x!=cursor.x_anterior || cursor.y!=cursor.y_anterior && cursor.x_anterior!=-1)
   recuperar_fondo();
 //}

//  getch();
//  closegraph();

//  free(puntero);

}


#endif