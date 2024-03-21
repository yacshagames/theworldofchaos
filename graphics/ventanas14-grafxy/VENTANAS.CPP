#include "ventanas.h"
#include <conio.h>
//#include <iostream.h>
#include "grafxy.h"
//#include "ifuncade.h"
#include "cajasper.h"

//#include <alloc.h>

//#include "pcxbgi.h"

void main()
{
  //autoini("");

//   cout<<farcoreleft();
  //cout<<farcoreleft();
/*
 clrscr();
 CFuncad fun;
 cout<<fun.f("x^2","X",complex(3,4));
// cout<<fun.f(complex(5,0));
   getch();
  */

 ModoGrafico();

 CVentana ventana_principal("METPRO 1.0",0,0,640,480,VENTANA_PADRE);

// getch();

 ventana_principal.Mostrar_ventana();

 cuadro(10,100,630,470,2);

 Evento raton;

 CBoton Aceptar(10,40,20,80,"Graficar"),Salir(100,40,20,80,"Salir"),
	AcercaDe(190,40,20,80,"Acerca de");

//CMenu Menu_Principal(10,20,15,150,3);
  //char ecuacion[80];

// setmgcursor(&handcursor);
 movemouse(0,0);
 mouseshow();
  do
  {

//  Menu_Principal.esperar_eventos(raton);


  if( Salir.mostrar(raton) )break;

  if( AcercaDe.mostrar(raton) )
   {

    CAcercaDe acercade("Acerca de METPRO 1.0",200,100,500,310);
    acercade.responder_eventos(raton);

   }

  if( Aceptar.mostrar(raton) )
  {

     cuadro(10,100,630,470,2);
     CRegionXY R(-10,10,-10,10,10,100,630,470);

     R.Ejes();

     CEntrarCadena Mensaje("Ingrese funci¢n f(x)",200,100,400,190);
     if( Mensaje.responder_eventos(raton) == SE_ACEPTA)
     {
      mousehide();
      R.Graficar( Mensaje.funcion.cad , CONECTAR);
      mouseshow();
     }

  }


  raton=Detectar_click_o_tecla();

  }while(raton.tecla!=27);

 mousehide();

 closegraph();


//getch();
}
