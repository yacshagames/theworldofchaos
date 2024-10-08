#pragma once
/*************************************************************************
CUSTOM DIALOG BOXES
CVentana public members

Here I have created the typical windows of a visual application such
as the About window and the window for entering data from the keyboard
(entering a text string).

Developed by:

	JOSE LUIS DE LA CRUZ LAZARO
	contact@theworldofchaos.com

	YACSHA - Software & Desing
	>> The World of Chaos - EL MUNDO DEL CAOS - Unlimited Programming
	www.theworldofchaos.com

LICENSE
	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

HISTORY...

>> Version 2 - 24 - III - 2024
- Update graphics / ventanas - Porting to VC++ 2017 using winbgi
- logoUNI is initialized in the CGrafico constructor
- Minor improvements in the definition of classes and member variables
- CAcercaDe::Mostrar_ventana, in PUTPIXEL mode, it no longer loads the
  bmp, it just directly draws the bmp from a preloaded bitmap, without
  reading it from disk as it was before

*************************************************************************/

#include "ventanas.h"

class CEntrarCadena : public CVentana
{

	CBoton Aceptar;
	CBoton Cancelar;
public:
	CCajaTexto funcion;

	CEntrarCadena(const char *Titulo, int izq, int arr, int der, int aba)
		: CVentana(Titulo, izq, arr, der, aba)
	{
		funcion = CCajaTexto(izquierda, arriba_cliente, derecha, abajo);
	}

	void Mostrar_ventana(void);
	unsigned esperar_eventos(Evento &);

};

void CEntrarCadena::Mostrar_ventana(void)
{

	CVentana::Mostrar_ventana();

	//mousehide();
	Aceptar = CBoton((derecha + 7 * izquierda) / 8, abajo - 30, 20, (derecha - izquierda) / 3, "OK");
	Cancelar = CBoton((5 * derecha + 3 * izquierda) / 8, abajo - 30, 20, (derecha - izquierda) / 3, "Cancel");
	funcion.cambiar_posicion(izquierda, arriba_cliente, derecha, abajo);
	funcion.mostrar_ventana_virtual();
	//mouseshow();
}

unsigned CEntrarCadena::esperar_eventos(Evento &raton)
{

	while (1)
	{

		if (CVentana::esperar_eventos(raton) == SE_CANCELA)
			return SE_CANCELA;

		funcion.editar_texto(raton);

		if (raton.tecla == ENTER || Aceptar.mostrar(raton))
		{
			funcion.cad[funcion.longitud] = '\0';
			return SE_ACEPTA;
		}

		if (raton.tecla == ESC || Cancelar.mostrar(raton))
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

	CAcercaDe(const char *Titulo, int izq, int arr, int der, int aba)
		
		: logoUNI(izquierda + 10, arriba_cliente + 10, "logouni.bmp", CGrafico::DRAWMODE::READIMAGEFILE),
		CVentana(Titulo, izq, arr, der, aba)
	{};

	void Mostrar_ventana(void);
	void Mover_ventana(Evento raton);
	unsigned esperar_eventos(Evento &);

};

void CAcercaDe::Mostrar_ventana(void)
{

	CVentana::Mostrar_ventana();

	//mousehide(); //oculta el mouse para no da�ar los graficos de la ventana

	 // Update a new position
	logoUNI.izq = izquierda + 10;
	logoUNI.arr = arriba_cliente + 10;
	
	// Se pinta el logo en la caja de di�logo
	logoUNI.pintar();

	//se inserta el bot�n Aceptar
	Aceptar = CBoton(izquierda + ancho / 2 + 20, abajo - 30, 20, ancho / 3, "OK");
	
	//se inserta los mensajes de cr�ditos del autor
	int top = arriba_cliente - 5;
	outtextxy(izquierda + 150, top + 10, "   METPRO WAS");
	outtextxy(izquierda + 150, top + 25, "PROGRAMMED BY:");
	setcolor(BLUE);
	outtextxy(izquierda + 150, top + 45, "   JOSE LUIS");
	outtextxy(izquierda + 150, top + 60, "   DE LA CRUZ");
	outtextxy(izquierda + 150, top + 75, "   LAZARO");
	setcolor(MAGENTA);
	outtextxy(izquierda + 150, top + 95, "  UNIVERSIDAD");
	outtextxy(izquierda + 150, top + 110, "  NACIONAL DE");
	outtextxy(izquierda + 150, top + 125, "  INGENIERIA");
	setcolor(RED);
	outtextxy(izquierda + 150, top + 140, "   LIMA-PERU");
	//mouseshow();//se muestra el mouse
}

//si la ventana se mueve con un arrastre en su barra de t�tulo
void CAcercaDe::Mover_ventana(Evento raton)
{
	CVentana::Mover_ventana(raton);
	//logoUNI.pintar();
}

//se espera a que se mueva el rat�n o se presione una tecla
unsigned CAcercaDe::esperar_eventos(Evento &raton)
{

	while (1)
	{

		if (CVentana::esperar_eventos(raton) == SE_CANCELA) return SE_CANCELA;

		if (raton.tecla == ENTER || Aceptar.mostrar(raton))
			return SE_ACEPTA;

		if (raton.tecla == ESC || Salir.mostrar(raton))
			return SE_CANCELA;

	}

}
