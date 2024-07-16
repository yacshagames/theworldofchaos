/**********************************************************************
VENTANAS
Draw windows and buttons in the Windows style.

The METPRO program is an example of using ventanas.h. What it does is
graph a function y=f(x) in the XY plane, using dialog boxes and buttons.

NOTE: SOME OF THE MOST USED FUNCTIONS OF WINDOWS.H ARE EXPLAINED HERE,
BUT IF YOU WANT TO SEE HOW MORE FUNCTIONS WORK YOU CAN SEE THE
DEFINITIONS OF THE BUILDERS OF EACH CLASS INCLUDED IN WINDOWS.H

Developed by:

	JOSE LUIS DE LA CRUZ LAZARO
	contact@theworldofchaos.com

	YACSHA - Software & Desing, since 1999, Lima-Peru
	>> The World of Chaos - EL MUNDO DEL CAOS - Unlimited Programming
	www.theworldofchaos.com

LICENSE
	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

HISTORY...

>> Version 2 - 24 - III - 2024
- Update graphics / ventanas - Porting to VC++ 2017 using winbgi
- The painting of the picture shown in the about box is updated, 
  now it can be painted with PUTPIXEL (slow) or
  with READIMAGEFILE (fast). The latter is the one that is
  configured by default.
- bmpplus is used instead of imgbgi, to draw the bmp faster on the screen
- Logouni.bmp is loaded in the About box instead of logouni.pcx.
  Because the pcx format has been obsolete
- Translate credits for english
- 

Versión 1.5  17-Agosto-2000
-Se agrega comentarios a casi todas las lineas de código.
-Se actualiza las cabeceras mousebgi.h y pcxbgi.h con otras versiones
 mas actuale, que son mas eficientes.
-Se borra código inservible

Versión 1.4  28-Diciembre-1999
Version aun no terminada... falta perfeccionar algunas cosas... pero presento
lo que he avanzado...

************************************************************************/

//#include <conio.h>

#include "ventanas.h"  //funciones para dibujar ventanas y botones tipo
			// Windows, las ventanas se pueden mover
			//arrastrandolas desde su barra de título
			//con el mouse y los botones son ocultables cuando
			//no se tiene el foco sobre ellos
			//Nota: Solo funciona con la BGI de Borland C++

#include "grafxy.h"    //funciones para graficar una función y=f(x)

#include "cajasper.h"  //funciones que definen las clases de cajas de dialogo
			//personalizadas, como por ejemplo
			//CAcercaDe para mostrar la ventana Acerca de...
			//CEntrarCadena para mostrar una ventana de ingreso
			//de datos en forma de cadena de texto

void main()
{
	int maxx = 1024 , maxy = 768;
	ModoGrafico(maxx, maxy); //activa el modo gráfico SVGA con resolución 640x480
		   //y 256 colores. También activa el raton en dicho modo gráfico
		   //cargando el puntero desde un archivo pcx; el puntero
		   //queda oculto

	//Crea la ventana principal del tamaño total de la pantalla
	CVentana ventana_principal("METPRO 2.0", //Titulo de la ventana
		0, 0, //esquina superior izquierda =  (0,0)
		maxx, maxy, //esquina inferior derecha = (640,480)
		VENTANA_PADRE); //se debe especificar que esta
				// será la ventana padre (ventana
				// que albergará a mas ventanas hijas)

	unsigned int	mainBoxWidth = int(0.975* double(maxx)),
					mainBoxHeight = (mainBoxWidth * maxy) / maxx,
					mainBoxLeft = 10, mainBoxTop = 80;

	//se muestra la ventana anterior
	ventana_principal.Mostrar_ventana();

	//se crea un cuadro para graficar la función f(x)
	cuadro( mainBoxLeft, mainBoxTop, //esquina superior izquierda
			mainBoxWidth, mainBoxHeight, //esquina superior derecha
			2); //muestra un cuadro entrante

	Evento raton; //estructura que contiene datos sobre la posición y
		   //la tecla presionada. Para mas información vea la
		   // definición de la estructura Evento en MOUSEBGI.H

	//se crean 3 botones
	CBoton //botón para mostrar la ventana de ingresar la función f(x)
		Graficar(10, 40, //esquina superior izquierda
			20, //alto
			100, //ancho
			"Plot function"), //Título del boton

		Salir(120, 40, 20, 80, "Exit"), //Botón para salir del programa

		AcercaDe(210, 40, 20, 120, "About METPRO"); //Botón para ver la caja de dialogo Acerca de...

	 //movemouse(300,300); //mueve el puntero del mouse a la posición (300,300)
	 //mouseshow(); //muestra el puntero de mouse

	  //Inicia un bucle para mostrar el programa mientras no se presione
	  //la tecla ESCAPE o no se presione el Botón "Salir"
	do
	{
		//notar que al mostrar el botón ( Función "mostrar", miembro de CBoton )
		//se tiene que pasar la estructura raton como
		//argumento, esto se hace para saber cuando el raton esta encima del botón
		//y asi mostrar el botón en estado sobresaliente o estado oculto

		if (Salir.mostrar(raton)) break; // si se presiona el boton "Salir",
						  // se sale del bucle

		if (AcercaDe.mostrar(raton)) //si sepresiona "AcercaDe" se muestra la caja de dialogo
		{

			//Muestra la ventana AcercaDe, aqui se muestra los creditos de autor
			CAcercaDe acercade("About of METPRO 2.0", //Título de la ventana
				200, //coordenada izquierda
				100,// coord. arr.
				500,//coord. der.
				310);//coord. abj.
		//si se mueve el raton sobre la ventana o se presiona una tecla mientras
		//la ventana está activa, se actualiza la estructura raton con este evento
			acercade.responder_eventos(raton);

		}

		if (Graficar.mostrar(raton))
		{
			//crea un cuadro vacío para graficar la función f(x)
			cuadro(mainBoxLeft, mainBoxTop, mainBoxWidth, mainBoxHeight, 2);

			//se crea un plano cartesiano virtual con la clase CRegionXY de
			//grafxy.h
			CRegionXY R(//se define la región XY donde se graficará la función f(x) ( valores en números reales )
				-10, //x mínimo
				10, //x máximo
				-10, //y mínimo
				10, //y máximo
				//cuadro donde se dibujará la región XY ( valores en píxeles )
				mainBoxLeft, mainBoxTop, //esquina superior izquierda
				mainBoxWidth, mainBoxHeight); //esquina inferior derecha

			R.Ejes(); //dibuja los ejes cartesianos en el plano XY creado

			//muestra una caja de diálogo para entrar una cadena de texto
			CEntrarCadena Mensaje("Enter function f(x)", //Título de la ventana
				200, 100, //esquina superior izquierda
				400, 190); //esquina inferior derecha

			//se espera que el usuario genere un evento sobre la ventana
			if (Mensaje.responder_eventos(raton) == SE_ACEPTA)
			{
				//Al recibir el evento SE_ACEPTA, el usuario presionó el botón Aceptar
				//o la tecla ENTER. Luego la ventana se cierra automaticamente
				//Si el usuario presiona el botón Cancelar, el botón X o la tecla
				//ESCAPE se recibe el evento SE_CANCELA. Luego la ventana se cierra
				//automaticamente

				//mousehide(); //oculta el ratón

				//si se ingresó una cadena de texto mientras estuvo visible la ventana
				//Mensaje, esta cadena se almacena en funcion.cad miembro de CEntrarCadena
				//Luego esta cadena es procesada por la función Graficar, miembro de
				//CRegionXY, para graficar esta función f(x) en la region especificada
				//anteriormente.
				R.Graficar(Mensaje.funcion.cad, //cadena de texto conteniendo f(x)
					CONECTAR,  //conectará los puntos de la gráfica por rectas
					LIGHTBLUE, // color del trazo ( azul claro )
					0.01);     //Paso del intervalo (valor de la partición del intervalo x)
				 //mouseshow(); //muestra el raton
			}

		}

		//Se obtiene los eventos generados con el ratón o teclado
		raton = MouseBGI::Detectar_click_o_tecla();

		//se sale del bucle si se presiona ESCAPE
	} while (raton.tecla != 27);

	//mousehide(); //se oculta el ratón

	closegraph(); //se cierra el modo gráfico SVGA

}
