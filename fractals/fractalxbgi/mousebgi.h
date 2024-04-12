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

 >> Version 2 - 24-III-2024
	- Update graphics/MouseBGI - Porting to VC++ 2017 using winbgi
	- The entire library is migrated to the MouseBGI class, using 
	  the mouse functionalities of WinBGI

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

struct Evento;

class MouseBGI {

public:
	enum class EVENTO {
		////////////////////////////////////////////////////////////////////////
		//CONSTANTES DE CONTROL
		// codigos de eventos del raton
		IDLE,			//no hay eventos
		LBUTTON_DOWN,	//se presiono el boton izquierdo del mouse
		RBUTTON_DOWN	//se presiono el boton derecho del mouse
	};

public:
	MouseBGI();
	~MouseBGI();

	// Mouse handler for WinBGI mouse controller
	static void OnLButtonDown(int x, int y);
	static void OnRButtonDown(int x, int y);
	static void OnMButtonDown(int x, int y);
	static void OnLButtonUp(int x, int y);
	static void OnRButtonUp(int x, int y);
	static void OnMButtonUp(int x, int y);
	static void OnMouseMove(int x, int y);

	static void RegisterMouseEvents();

	// obtiene el ultimo evento del raton
	static EVENTO mouseevent(int&, int&);

	//Retorna una estructura Evento, con los eventos generados por el ratón y teclado
	static Evento Detectar_click_o_tecla();	

private:
	// Variables for monitoring mouse clicks
	static bool bLBUTTONPRESSED;
	static bool bRBUTTONPRESSED;
	static bool bMOUSEMOVE;

};

//Estructura que almacena los eventos generados por el rat¢n y teclado
struct Evento
{
	int x;	//posici¢n x del puntero del rat¢n
	int y; //posici¢n y del puntero del rat¢n
	MouseBGI::EVENTO evento; //Evento actual del rat¢n (ver definici¢n de codigos de Eventos m s abajo)
	char tecla; //si se presiona alguna tecla desde el teclado, se almacena aqu¡ su codigo ASCII
};


MouseBGI::MouseBGI() {
}

MouseBGI::~MouseBGI() {
}

bool MouseBGI::bLBUTTONPRESSED = false;
bool MouseBGI::bRBUTTONPRESSED = false;
bool MouseBGI::bMOUSEMOVE = false;

///////////////////////////////////////////////////////////////////
//FUNCIONES DE CONTROL ESTANDAR


void MouseBGI::OnLButtonDown(int x, int y) {
	bLBUTTONPRESSED = true;
}

void MouseBGI::OnRButtonDown(int x, int y) {
	bRBUTTONPRESSED = true;
}

void MouseBGI::OnMButtonDown(int x, int y) {
}

void MouseBGI::OnLButtonUp(int x, int y) {
	bLBUTTONPRESSED = false;
}

void MouseBGI::OnRButtonUp(int x, int y) {
	bRBUTTONPRESSED = false;
}

void MouseBGI::OnMButtonUp(int x, int y) {
}

void MouseBGI::OnMouseMove(int x, int y) {

}

void MouseBGI::RegisterMouseEvents() {
	registermousehandler(WM_LBUTTONDOWN, MouseBGI::OnLButtonDown);
	registermousehandler(WM_RBUTTONDOWN, MouseBGI::OnRButtonDown);
	registermousehandler(WM_MBUTTONDOWN, MouseBGI::OnMButtonDown);
	registermousehandler(WM_LBUTTONUP, MouseBGI::OnLButtonUp);
	registermousehandler(WM_RBUTTONUP, MouseBGI::OnRButtonUp);
	registermousehandler(WM_MBUTTONUP, MouseBGI::OnMButtonUp);
	registermousehandler(WM_MOUSEMOVE, MouseBGI::OnMouseMove);
}

////////////////////////////////////////////////////////////////////////////
// obtiene el ultimo evento del raton
MouseBGI::EVENTO MouseBGI::mouseevent(int& Mx, int& My) {
	EVENTO E;

	if (bLBUTTONPRESSED) {
		E = EVENTO::LBUTTON_DOWN;
		//cleardevice();
		//outtext("L");			
	}
	else if (bRBUTTONPRESSED) {
		E = EVENTO::RBUTTON_DOWN;
		//cleardevice();
		//outtext("R");

	}
	else
		E = EVENTO::IDLE;

	Mx = mousex();
	My = mousey();
	
	return E;
}

/////////////////////////////////////
//IMPLEMENTACION DE EVENTOS
Evento MouseBGI::Detectar_click_o_tecla()
{
	Evento p;

	p.evento = EVENTO::IDLE;
	p.tecla = -1;

	p.evento = mouseevent(p.x, p.y);

	if (kbhit())
	{
		p.tecla = getch();
	}

	return p;
}


