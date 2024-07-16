/*********************************************************************
Musical KEYBOARD

A musical keyboard is simulated using the computer keyboard.

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

>> Version 2 - 25-III-2024
- Update graphics/tecladmu - Porting to VC++ 2017 using winbgi

- Versión 1.4 - 17 Julio del 2000
  Se actualiza y optimiza los fuentes de la versión anterior.

- Versión 1.3 - 31 de Octubre de 1998
 *Se crea un algoritmo que calcula la frecuencia de cualquier nota
  musical en cualquier octava del teclado.
 *Se pinta un teclado en la pantalla, para poder visualizar
  las notas que se están presionando.
 *Se imprime en pantalla las notas musicales que que se estan tocando.

- Versión 1.0-1.2 - Julio de 1998
  Se simula un teclado musical utilizando el teclado del computador,
  cada tecla toca un sonido de diferente frecuencia.

*********************************************************************/

//#include"dos.h"
//#include"ctype.h"
//#include"conio.h"
//#include"math.h"
//#include"stdio.h"
#include "graphics.h"
#include <string>
using std::string;

void pinta_tecla(int accion, int octava, int nota)
{

	int k = 630 / 21, pos, x, y, color;

	int sostenido = 1;
	switch (nota)
	{
	case 2:pos = 1; break;
	case 4:pos = 2; break;
	case 7:pos = 4; break;
	case 9:pos = 5; break;
	case 11:pos = 6; break;

	default:
		sostenido = 0;
		switch (nota)
		{
		case 1:pos = 1; break;
		case 3:pos = 2; break;
		case 5:pos = 3; break;
		case 6:pos = 4; break;
		case 8:pos = 5; break;
		case 10:pos = 6; break;
		case 12:pos = 7; break;
		}
	}

	if (sostenido)
	{
		x = 5 + (7 * (octava - 3) + pos)*k;
		y = 30;
	}
	else
	{
		x = 5 + (7 * (octava - 3) + pos)*k - k / 2;
		y = 80;
	}

	//accion=1 pintar bola
	//accion=0 borrar bola
	if (accion)color = 4;
	else if (sostenido)color = 0; else color = 1;

	setcolor(color);
	setfillstyle(1, color);

	fillellipse(x, y, 5, 5);

}


void tocar(int octava, int nota)
{
	pinta_tecla(1, octava, nota);//pinta el circulo rojo

	int i, f = 0;

	double frecuencia = 123.75;

	//Estas constantes son para las 12 notas de la octava 4

	//60,80,70,90,100,120 son las variaciones de las frecuencias
	//de 2 notas musicales consecutivas ejm: fFA-fMI=70
	//La suma de todas estas variaciones consecutivas es
	//Sumavarfrec=60+60+80+70+...+120=990 PARA LA OCTAVA 4
	//PARA LA OCTAVA X: Sumavarfrec=990*2^(X-4)
	//NOTA: frecuencia de DO en la octava 4 = 1050
	switch (nota)
	{
	case 12:f += 120;//SI
	case 11:f += 100;//LA#
	case 10:f += 100;//LA
	case 9:f += 90;//SOL#
	case 8:f += 90;//SOL
	case 7:f += 90;//FA#
	case 6:f += 70;//FA
	case 5:f += 70;//MI
	case 4:f += 80;//RE#
	case 3:f += 60;//RE
	case 2:f += 60;//DO#
	case 1:f += 60;//DO   //OCTAVA4
	}

	//Se calcula la sumatoria de las frecuencias de las octavas anteriores
	//es decir, frecuenciaAcumulada = 123.75+990/8+990/4+990/2+...
	//  PARA LA OCTAVA:                oct1  oct2  oct3  oct4

	//NOTA: 990=Sumavarfrec
	for (i = 0; i < octava - 1; i++)
		frecuencia += 990 * pow(2, i - 3);

	//Se calcula la frecuencia de la nota musical a tocar
	//frecuencia=frecuenciaAcumulada+f*2^(octava-4)
	frecuencia += f * pow(2, octava - 4);

	//sound(frecuencia);
	// delay(200);
	//nosound();
	Beep(frecuencia, 200);

	pinta_tecla(0, octava, nota);//borra el circulo rojo

	if (getx() >= getmaxx() - 50) moveto(10, gety() + 15);

	setcolor(14);

	string Nota;

	switch (nota)
	{
	case 12:Nota = "SI"; break;//SI
	case 11:Nota = "LA#"; break;//LA#
	case 10:Nota = "LA"; break;//LA
	case 9:Nota = "SOL#"; break;//SOL#
	case 8:Nota = "SOL"; break;//SOL
	case 7:Nota = "FA#"; break;//FA#
	case 6:Nota = "FA"; break;//FA
	case 5:Nota = "MI"; break;//MI
	case 4:Nota = "RE#"; break;//RE#
	case 3:Nota = "RE"; break;//RE
	case 2:Nota = "DO#"; break;//DO#
	case 1:Nota = "DO"; break;//DO   //OCTAVA4

	}

	outtext(Nota.c_str());
	outtext(" ");
}

void TocarNotaMusical(char tecla1, char tecla2)
{
	switch (tecla1)
	{
	case '`':tocar(3, 7); break;//FA#
	case  9: tocar(3, 8); break;//SOL
	case '1':tocar(3, 9); break;//SOL#
	case 'Q':tocar(3, 10); break;//LA   - frecuencia(Hz)=880
	case '2':tocar(3, 11); break;//LA#
	case 'W':tocar(3, 12); break;//SI
	case 'E':tocar(4, 1); break;//DO   //OCTAVA4
	case '4':tocar(4, 2); break;//DO#
	case 'R':tocar(4, 3); break;//RE
	case '5':tocar(4, 4); break;//RE#
	case 'T':tocar(4, 5); break;//MI
	case 'Y':tocar(4, 6); break;//FA
	case '7':tocar(4, 7); break;//FA#
	case 'U':tocar(4, 8); break;//SOL
	case '8':tocar(4, 9); break;//SOL#
	case 'I':tocar(4, 10); break;//LA
	case '9':tocar(4, 11); break;//LA#
	case 'O':tocar(4, 12); break;//SI
	case 'P':tocar(5, 1); break;//DO   //OCTAVA5
	case '-':tocar(5, 2); break;//DO#
	case '[':tocar(5, 3); break;//RE
	case '=':tocar(5, 4); break;//RE#
	case ']':tocar(5, 5); break;//MI
	case 13:tocar(5, 6); break;//FA
	}

	if (!tecla1) //si se presionó teclas con codigo extendido
	{
		switch (tecla2)
		{
		case 82:tocar(5, 7); break;//FA#
		case 83:tocar(5, 8); break;//SOL
		case 71:tocar(5, 9); break;//SOL#
		case 79:tocar(5, 10); break;//LA
		case 73:tocar(5, 11); break;//LA#
		case 81:tocar(5, 12); break;//SI
		}
	}

}

void PintarTeclado()
{
	//PINTA TECLADO
	setfillstyle(1, 1); //1=AZUL
	bar(5, 0, 635, 100);//dibuja el contorno del teclado

	for (int i = 1; i < 21; i++)
	{
		int x = i * 630 / 21;
		line(5 + x, 0, 5 + x, 100); //dibuja cada tecla

		setfillstyle(1, 0); //0=NEGRO
		if (i % 7 != 0 && i % 7 != 3) bar((x - 10) + 5, 0, (x + 10) + 5, 60); //dibuja cada tecla bemol/sostenido

		if (i % 7 == 1) fillellipse(x - (630 / 21) / 2 + 5, 90, 3, 3); //dibuja un circulo a todas las notas DO
	}

	//PINTA TEXTO INFORMATIVO Y COPYRIGHT
	setfillstyle(1, 16); //16=BLANCO
	outtextxy(10, 140, "NOTES PLAYED:");
	moveto(10, 160);

	settextstyle(3, HORIZ_DIR, 3);
	setcolor(2);
	outtextxy(10, 110, "Musical Keyboard *** Version 2");

	settextstyle(7, HORIZ_DIR, 2);
	setcolor(3);
	outtextxy(100, 430, "This is another production made by:");
	setcolor(12);
	outtextxy(300, 450, "Jose Luis De la Cruz Lazaro");
	//settextstyle(11, HORIZ_DIR, 2);

}

int main()
{

	// Init WinBGI window
	initwindow(1024, 768, "The world of chaos in C++ - Unlimited Programming");

	PintarTeclado();

	char tecla1 = 0, tecla2 = 0;

	do
	{
		tecla1 = toupper(getch());//captura tecla presionada
		if (!tecla1) tecla2 = toupper(getch()); //captura tecla presionada si es de codigo extendido
		TocarNotaMusical(tecla1, tecla2); //Toca la nota musical correspondiente a la tecla presionada
	} while (tecla1 != 27);//Se toca el teclado hasta que se presione ESCAPE

	closegraph();

	return 1;

}

