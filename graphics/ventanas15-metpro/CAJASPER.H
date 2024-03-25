#pragma once
//CAJAS DE DIALOGO PERSONALIZADAS miembros p£blicos de CVentana

//Aqui he creado las ventanas t¡picas de una aplicaci¢n visual como son
//la ventana de AcercaDe y la ventana de ingresar datos desde el teclado
//(ingresar una cadena de texto)
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
	Aceptar = CBoton((derecha + 7 * izquierda) / 8, abajo - 30, 20, (derecha - izquierda) / 3, "Aceptar");
	Cancelar = CBoton((5 * derecha + 3 * izquierda) / 8, abajo - 30, 20, (derecha - izquierda) / 3, "Cancelar");
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
			strcpy(funcion.cad, funcion.cad);
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
		: CVentana(Titulo, izq, arr, der, aba) {};

	void Mostrar_ventana(void);
	void Mover_ventana(Evento raton);
	unsigned esperar_eventos(Evento &);

};

void CAcercaDe::Mostrar_ventana(void)
{

	CVentana::Mostrar_ventana();

	//mousehide(); //oculta el mouse para no da¤ar los graficos de la ventana

	 //se inserta el logo de mi querida UNIVERSIDAD NACIONAL DE INGENIERIA
	logoUNI = CGrafico(izquierda + 10, arriba_cliente + 10, "logouni.pcx");
	//se pinta el logo en la caja de di logo
	logoUNI.pintar();

	//se inserta el bot¢n Aceptar
	Aceptar = CBoton(izquierda + ancho / 2 + 20, abajo - 30, 20, ancho / 3, "Aceptar");
	//se inserta los mensajes de cr‚ditos del autor
	outtextxy(izquierda + 150, arriba_cliente + 10, "   METPRO FUE");
	outtextxy(izquierda + 150, arriba_cliente + 20, "PROGRAMADO POR:");
	setcolor(BLUE);
	outtextxy(izquierda + 150, arriba_cliente + 40, "   JOSE LUIS");
	outtextxy(izquierda + 150, arriba_cliente + 50, "   DE LA CRUZ");
	outtextxy(izquierda + 150, arriba_cliente + 60, "   LAZARO");
	setcolor(MAGENTA);
	outtextxy(izquierda + 150, arriba_cliente + 80, "  UNIVERSIDAD");
	outtextxy(izquierda + 150, arriba_cliente + 90, "  NACIONAL DE");
	outtextxy(izquierda + 150, arriba_cliente + 100, "  INGENIERIA");
	setcolor(RED);
	outtextxy(izquierda + 150, arriba_cliente + 120, "   LIMA-PERU");
	//mouseshow();//se muestra el mouse
}

//si la ventana se mueve con un arrastre en su barra de t¡tulo
void CAcercaDe::Mover_ventana(Evento raton)
{
	CVentana::Mover_ventana(raton);
	logoUNI.pintar();
}

//se espera a que se mueva el rat¢n o se presione una tecla
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
