/***************************************************************************
DBZ CARDS ( 16 Nov 1999 )

EJEMPLO DE COMO CONTROLAR LAS RUTINAS DEL MOUSE EN EL MODO GRAFICO
DE 256 COLORES

programado por:
JOSE LUIS DE LA CRUZ LAZARO 
ramondc@hotmail.com
Pagina Web: http://www.geocities.com/joseluisdl/jldl.htm
***************************************************************************/

#include <graphics.h>
#include <conio.h>

#include "grafimpl.h"
#include "mousebgi.h"
/*
#define wait1 1
#define wait2 2

void WaitRetrace(void)
{
 Espera el retrace horizontal, es decir el retorno horizontal
del rayo en el CRT. Es conveniente ejecutarlo antes de dibujar en una
animaci¢n para asegurar que los cambios se hagan durante el retrace delrayo

 asm{
  mov dx,3dah
  wait1:
  in al,dx
  test al,08h
  jnz wait1
  wait2:
  in al,dx
  test al,08h
  jz wait2
  }

}//WaitRetrace
  */
int main(void)
{

 IniciarSVGA(_800x600); //se inicia la supervga (256 colores )
			//con una resolucion de 800x600

 cuadro(0, 0, getmaxx(), getmaxy(), 1); //se dibuja el cuadro de fondo

 Evento raton,raton_anterior;

 movemouse(100,100); //se mueve el puntero a la posicion (100,100)
 mouseshow();//se muestra el raton

 PCX freezer,goku; // se crea el objeto grafico

 freezer.leer_cabecera(0,"freezer.pcx"); // se lee informacion del archivo pcx
 goku.leer_cabecera(1,"goku.pcx");

 outtextxy(10,20,"Deja presionado el bot¢n derecho");
 outtextxy(10,30,"y has un arrastre con el mouse para ver a KAKAROTO");
 outtextxy(10,40,"y lo mismo pero con el bot¢n izquierdo para ver a FREEZER");

 raton=Detectar_click_o_tecla();

  do
  {

   raton_anterior=raton;

   raton=Detectar_click_o_tecla(); //se obtiene informacion sobre las coordenadas del raton

   //muestra la card de Goku
   if( raton.evento == LBUTTON_STILL_DOWN )
   if( raton.x != raton_anterior.x ||
      raton.y != raton_anterior.y )
   {
    cuadro(raton_anterior.x,raton_anterior.y,
	   raton_anterior.x+160,raton_anterior.y+150,0); //borra la ventana
    ventana(raton.x,raton.y,raton.x+160,raton.y+150); //dibuja la ventana

    goku.Dibujar(raton.x+10,raton.y+20); //dibuja a GOKU sobre la ventana en la posicion indicada

    outtextxy(raton.x+30,raton.y+130,"GOKU");

    }

   //muestra la card de freezer
   if( raton.evento == RBUTTON_STILL_DOWN )
   if( raton.x != raton_anterior.x ||
      raton.y != raton_anterior.y )
   {
    cuadro(raton_anterior.x,raton_anterior.y,
	   raton_anterior.x+100,raton_anterior.y+150,0); //borra la ventana
    ventana(raton.x,raton.y,raton.x+100,raton.y+150); //dibuja la ventana

    freezer.Dibujar(raton.x+10,raton.y+20); //dibuja a freezer sobre la ventana en la posicion indicada

    outtextxy(raton.x+30,raton.y+130,"FREEZER");
   }


  }while(raton.tecla!=27);


 mousehide();
 mousedestroy();

 closegraph();

 textcolor( GREEN+BLINK );

 cprintf("DBZ CARDS -- programado por Jos‚ Luis De la Cruz L zaro\n\n");

 getch();

 return 0;
}