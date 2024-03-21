//CAJAS DE DIALOGO PERSONALIZADAS
#ifndef __VENTANAS_H
#include "ventanas.h"
#endif

//#include <iostream.h>

class CEntrarCadena : public CVentana
{

 CBoton Aceptar;
 CBoton Cancelar;
 public:
  CCajaTexto funcion;

 CEntrarCadena(char *Titulo, int izq, int arr, int der, int aba )
	       : CVentana(Titulo, izq, arr, der, aba )
 {
   funcion =CCajaTexto( izquierda,arriba_cliente,derecha,abajo);
 }

  void Mostrar_ventana(void);
  unsigned esperar_eventos( Evento &);

};

void CEntrarCadena::Mostrar_ventana(void)
{

 CVentana::Mostrar_ventana();

 mousehide();
  Aceptar = CBoton( (derecha+7*izquierda)/8,abajo-30,20,(derecha-izquierda)/3,"Aceptar");
  Cancelar = CBoton( (5*derecha+3*izquierda)/8,abajo-30,20,(derecha-izquierda)/3,"Cancelar");
  funcion.cambiar_posicion( izquierda,arriba_cliente,derecha,abajo);
  funcion.mostrar_ventana_virtual();
 mouseshow();
}

unsigned CEntrarCadena::esperar_eventos( Evento &raton)
{

 while(1)
 {

  if( CVentana::esperar_eventos( raton ) == SE_CANCELA )
   return SE_CANCELA;

  funcion.editar_texto( raton );

  if( raton.tecla==ENTER || Aceptar.mostrar(raton) )
  {
   strcpy(funcion.cad,funcion.cad);
   return SE_ACEPTA;
  }

  if( raton.tecla==ESC || Cancelar.mostrar(raton))
   return SE_CANCELA;

 }


}
///////////////////////////////////////////////////////////////////////////
//ACERCADE MUESTRA LOS CREDITOS DE AUTOR
class CAcercaDe : public CVentana
{
 CGrafico logoUNI;

 CBoton Aceptar;

 public:

 CAcercaDe(char *Titulo, int izq, int arr, int der, int aba )
	       : CVentana(Titulo, izq, arr, der, aba ){};

  void Mostrar_ventana(void);
  void Mover_ventana(Evento raton);
  unsigned esperar_eventos( Evento &);

};

void CAcercaDe::Mostrar_ventana(void)
{

 CVentana::Mostrar_ventana();

 mousehide();
  logoUNI = CGrafico(izquierda+10,arriba_cliente+10,"logouni.pcx");
  logoUNI.pintar();
  Aceptar = CBoton( (derecha+2*izquierda)/3,abajo-30,20,(derecha-izquierda)/3,"Aceptar");
  outtextxy(izquierda+10,arriba_cliente+10,"METPRO FUE PROGRAMADO POR");
  outtextxy(izquierda+10,arriba_cliente+20,"JOSE LUIS DE LA CRUZ LAZARO");
 mouseshow();
}

void CAcercaDe::Mover_ventana(Evento raton)
{
 CVentana::Mover_ventana(raton);
 logoUNI.pintar();
}


unsigned CAcercaDe::esperar_eventos( Evento &raton)
{

 while(1)
 {

 if( CVentana::esperar_eventos( raton ) == SE_CANCELA ) return SE_CANCELA;

 if( raton.tecla==ENTER || Aceptar.mostrar(raton) )
  return SE_ACEPTA;

 if( raton.tecla==ESC || Salir.mostrar(raton) )
  return SE_CANCELA;

 }

}
