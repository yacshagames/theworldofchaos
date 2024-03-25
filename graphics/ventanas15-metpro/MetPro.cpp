/**********************************************************************
VENTANAS
Dibuja ventanas y botones al estilo Windows.

El programa METPRO es un ejemplo del uso de ventanas.h . Lo que hace es
graficar una funci¢n y=f(x) en el plano XY, utilizando cajas de dialogo
y botones.

programado por:
 JOSE LUIS DE LA CRUZ LAZARO
correos:
 jcruz@ec-red.com
 ramondc@hotmail.com
Pagina Web ( EL MUNDO DEL CAOS ):
 http://www.geocities.com/joseluisdl


NOTA: AQUI SE EXPLICAN ALGUNAS DE LAS FUNCIONES MAS UTILIZADAS DE VENTANAS.H
PERO SI QUIERE VER EL FUNCIONAMIENTO DE MAS FUNCIONES PUEDE VER LAS
DEFINICIONES DE LOS CONSTRUCTORES DE CADA CLASE INCLUIDA EN VENTANAS.H

HISTORIA...

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

Versi¢n 1.5  17-Agosto-2000
-Se agrega comentarios a casi todas las lineas de c¢digo.
-Se actualiza las cabeceras mousebgi.h y pcxbgi.h con otras versiones
 mas actuale, que son mas eficientes.
-Se borra c¢digo inservible

Versi¢n 1.4  28-Diciembre-1999
Version aun no terminada... falta perfeccionar algunas cosas... pero presento
lo que he avanzado...

************************************************************************/

//#include <conio.h>

#include "ventanas.h"  //funciones para dibujar ventanas y botones tipo
			// Windows, las ventanas se pueden mover
			//arrastrandolas desde su barra de t¡tulo
			//con el mouse y los botones son ocultables cuando
			//no se tiene el foco sobre ellos
			//Nota: Solo funciona con la BGI de Borland C++

#include "grafxy.h"    //funciones para graficar una funci¢n y=f(x)

#include "cajasper.h"  //funciones que definen las clases de cajas de dialogo
			//personalizadas, como por ejemplo
			//CAcercaDe para mostrar la ventana Acerca de...
			//CEntrarCadena para mostrar una ventana de ingreso
			//de datos en forma de cadena de texto

void main()
{
	int maxx = 1024 , maxy = 768;
	ModoGrafico(maxx, maxy); //activa el modo gr fico SVGA con resoluci¢n 640x480
		   //y 256 colores. Tambi‚n activa el raton en dicho modo gr fico
		   //cargando el puntero desde un archivo pcx; el puntero
		   //queda oculto

	//Crea la ventana principal del tama¤o total de la pantalla
	CVentana ventana_principal("METPRO 2.0", //Titulo de la ventana
		0, 0, //esquina superior izquierda =  (0,0)
		maxx, maxy, //esquina inferior derecha = (640,480)
		VENTANA_PADRE); //se debe especificar que esta
				// ser  la ventana padre (ventana
				// que albergar  a mas ventanas hijas)

	unsigned int	mainBoxWidth = int(0.975* double(maxx)),
					mainBoxHeight = (mainBoxWidth * maxy) / maxx,
					mainBoxLeft = 10, mainBoxTop = 80;

	//se muestra la ventana anterior
	ventana_principal.Mostrar_ventana();

	//se crea un cuadro para graficar la funci¢n f(x)
	cuadro( mainBoxLeft, mainBoxTop, //esquina superior izquierda
			mainBoxWidth, mainBoxHeight, //esquina superior derecha
			2); //muestra un cuadro entrante

	Evento raton; //estructura que contiene datos sobre la posici¢n y
		   //la tecla presionada. Para mas informaci¢n vea la
		   // definici¢n de la estructura Evento en MOUSEBGI.H

	//se crean 3 botones
	CBoton //bot¢n para mostrar la ventana de ingresar la funci¢n f(x)
		Graficar(10, 40, //esquina superior izquierda
			20, //alto
			100, //ancho
			"Plot function"), //T¡tulo del boton

		Salir(120, 40, 20, 80, "Exit"), //Bot¢n para salir del programa

		AcercaDe(210, 40, 20, 120, "About METPRO"); //Bot¢n para ver la caja de dialogo Acerca de...

	 //movemouse(300,300); //mueve el puntero del mouse a la posici¢n (300,300)
	 //mouseshow(); //muestra el puntero de mouse

	  //Inicia un bucle para mostrar el programa mientras no se presione
	  //la tecla ESCAPE o no se presione el Bot¢n "Salir"
	do
	{
		//notar que al mostrar el bot¢n ( Funci¢n "mostrar", miembro de CBoton )
		//se tiene que pasar la estructura raton como
		//argumento, esto se hace para saber cuando el raton esta encima del bot¢n
		//y asi mostrar el bot¢n en estado sobresaliente o estado oculto

		if (Salir.mostrar(raton)) break; // si se presiona el boton "Salir",
						  // se sale del bucle

		if (AcercaDe.mostrar(raton)) //si sepresiona "AcercaDe" se muestra la caja de dialogo
		{

			//Muestra la ventana AcercaDe, aqui se muestra los creditos de autor
			CAcercaDe acercade("About of METPRO 2.0", //T¡tulo de la ventana
				200, //coordenada izquierda
				100,// coord. arr.
				500,//coord. der.
				310);//coord. abj.
		//si se mueve el raton sobre la ventana o se presiona una tecla mientras
		//la ventana est  activa, se actualiza la estructura raton con este evento
			acercade.responder_eventos(raton);

		}

		if (Graficar.mostrar(raton))
		{
			//crea un cuadro vac¡o para graficar la funci¢n f(x)
			cuadro(mainBoxLeft, mainBoxTop, mainBoxWidth, mainBoxHeight, 2);

			//se crea un plano cartesiano virtual con la clase CRegionXY de
			//grafxy.h
			CRegionXY R(//se define la regi¢n XY donde se graficar  la funci¢n f(x) ( valores en n£meros reales )
				-10, //x m¡nimo
				10, //x m ximo
				-10, //y m¡nimo
				10, //y m ximo
				//cuadro donde se dibujar  la regi¢n XY ( valores en p¡xeles )
				mainBoxLeft, mainBoxTop, //esquina superior izquierda
				mainBoxWidth, mainBoxHeight); //esquina inferior derecha

			R.Ejes(); //dibuja los ejes cartesianos en el plano XY creado

			//muestra una caja de di logo para entrar una cadena de texto
			CEntrarCadena Mensaje("Enter function f(x)", //T¡tulo de la ventana
				200, 100, //esquina superior izquierda
				400, 190); //esquina inferior derecha

			//se espera que el usuario genere un evento sobre la ventana
			if (Mensaje.responder_eventos(raton) == SE_ACEPTA)
			{
				//Al recibir el evento SE_ACEPTA, el usuario presion¢ el bot¢n Aceptar
				//o la tecla ENTER. Luego la ventana se cierra automaticamente
				//Si el usuario presiona el bot¢n Cancelar, el bot¢n X o la tecla
				//ESCAPE se recibe el evento SE_CANCELA. Luego la ventana se cierra
				//automaticamente

				//mousehide(); //oculta el rat¢n

				//si se ingres¢ una cadena de texto mientras estuvo visible la ventana
				//Mensaje, esta cadena se almacena en funcion.cad miembro de CEntrarCadena
				//Luego esta cadena es procesada por la funci¢n Graficar, miembro de
				//CRegionXY, para graficar esta funci¢n f(x) en la region especificada
				//anteriormente.
				R.Graficar(Mensaje.funcion.cad, //cadena de texto conteniendo f(x)
					CONECTAR,  //conectar  los puntos de la gr fica por rectas
					LIGHTBLUE, // color del trazo ( azul claro )
					0.01);     //Paso del intervalo (valor de la partici¢n del intervalo x)
				 //mouseshow(); //muestra el raton
			}

		}

		//Se obtiene los eventos generados con el rat¢n o teclado
		raton = MouseBGI::Detectar_click_o_tecla();

		//se sale del bucle si se presiona ESCAPE
	} while (raton.tecla != 27);

	//mousehide(); //se oculta el rat¢n

	closegraph(); //se cierra el modo gr fico SVGA

}
