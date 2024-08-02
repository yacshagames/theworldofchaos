/********************************************
SOLUTION #3 TO CHALLENGE0012:
Programmed by:
   Jose Luis De la Cruz Lazaro - 10-I-2001
   contact@theworldofchaos.com
   https://www.theworldofchaos.com
********************************************/

//CHALLENGE 0012
//* Copyright (C) 2000 by David A. Capello - davidcapello.com */
/*
* The program must draw 10 rectangles of a size that always
* varies between 1 and 10 both in width and height(10x10);
* Now what happens is that there is a problem, the rectangles
* want to use the space to the maximum and not be on top of
* each other, so the task will be to generate the algorithm
* that looks for the best position for the rectangle to be
* located(see the function `draw_rectangle');
*/
#include <iostream>
#include <cstdio>
#include <ctime>
using std::cout;

#define ANCHO   64
#define ALTO    38 /* height must always be even (since the lines are drawn two by two) */



char pantalla[ALTO][ANCHO]; /* access mode: screen[y][x] */



/* clear the entire screen buffer with 0 (zeros) */
void borrar_pantalla()
{
	int x, y;

	/* traverse from top to bottom */
	for (y = 0; y < ALTO; y++)
		/* traverse from left to right*/
		for (x = 0; x < ANCHO; x++)
			pantalla[y][x] = 0;
}



/* draws a rectangle of the given size at any position
on the screen, but it cannot cover areas already
occupied by other rectangles */
bool dibujar_rectangulo(int alto, int ancho)
{
	int x, y, comienzox, comienzoy;

	/* HERE YOU MUST COMPLETE: ****************************************/
	/* You must carry out the function that seeks to position
	 * the rectangle on the screen so that it does not cover
	 * the others... if not, it will give you an error and
	 * the execution will end;
	 *
	 * NOTE: the function should always draw correctly, so
	 * this random proposal is not valid since it is random,
	 * and sometimes it works and other times it DOESN'T,
	 * so any other way that uses random or random or
	 * pseudo-random number generators will be wrong;
	 */

	 // THE OLD METHOD OF PRODUCTION
	int salir = 0, i, j;

	for (y = 0; y <= ALTO - alto; y++) //se busca el punto de comienzo adecuado
	{
		for (x = 0; x <= ANCHO - ancho; x++)
		{
			salir = 1;

			for (i = 0; i < ancho; i++)          //Se hace el producto de todos los
				for (j = 0; j < alto; j++)           //valores de los puntos dentro del
					salir *= !pantalla[y + j][x + i];  //espacio virtual ( pantalla )
								 //donde se pintar  el rect ngulo.

			if (salir)                      //Si se obtiene 1, entonces
				break;                        //se termina todos los bucles.
							  //En caso contrario se sigue buscando
		}                                //el punto ideal.
		if (salir)
			break;
	}

	//Si no se puede encajar un rect ngulo se muestra el siguiente mensaje
	if (!salir)
	{
		cout << "\n\nLA PANTALLA ES DEMASIADO PEQUE¥A PARA INSERTAR MAS RECTANGULOS\n";
		return false;
	}

	comienzox = x;
	comienzoy = y;

	/* AND THIS IS WHERE YOUR WORK ENDS ********************************/

	if ((comienzox < 0) || (comienzox + ancho > ANCHO) ||
		(comienzoy < 0) || (comienzoy + alto > ALTO)) {
		cout << "Sorry, you lost! You drew outside the screen limits\n";
		return false;
	}

	/* draw it */
	for (y = comienzoy; y < comienzoy + alto; y++)
		for (x = comienzox; x < comienzox + ancho; x++) {
			if (pantalla[y][x]) {
				cout << "Sorry, you lost! Draw on top of another rectangle\n";
				return false;
			}

			pantalla[y][x] = 1;
		}

	return true;
}



/* draw the full screen */
void dibujar_pantalla()
{
	int x, y;

	/* draw something to separate from the rest of the lines */
	cout << "-------- [SCREEN] --------\n";

	/* draw the screen (NOTE: 2 lines are drawn in a row
	   with the characters:
		 '█' (full), '▀' (top), '▄' (lower), ' ' (empty);
	*/
	for (y = 0; y < ALTO; y += 2) {
		std::putc((unsigned char)'³', stdout);

		/* draw two lines */
		for (x = 0; x < ANCHO; x++) {
			/* first line full */
			if (pantalla[y][x]) {
				/* second too */
				if (pantalla[y + 1][x])
					std::putc((unsigned char)219, stdout);
				/* second empty */
				else
					std::putc((unsigned char)223, stdout);
			}
			/* first empty line */
			else {
				/* but second full */
				if (pantalla[y + 1][x])
					std::putc((unsigned char)220, stdout);
				/* all empty */
				else
					std::putc((unsigned char)32, stdout);
			}
		}

		/* jump to next line */
		cout << "³\n";
	}

	/* draw another separator */
	cout << "----------------------------\n";
}



int main()
{
	int c;

	/* start the random number generator */
	srand((unsigned int)time(NULL));

	/* clear screen */
	borrar_pantalla();

	/* draw ten rectangles */
	for (c = 0; c < 10; c++)
		if (dibujar_rectangulo((rand() % 10) + 1, (rand() % 10) + 1)==false)
			return 1;

	/* draw the entire screen */
	dibujar_pantalla();

	/* Since the above can cause problems, we will now test
	   the function with the limits he he he :-) */
	borrar_pantalla();
	for (c = 0; c < 10; c++)
		dibujar_rectangulo(10, 10);
	dibujar_pantalla();

	cout << "YOU WON! If you liked this challenge remember to leave a comment\n";
	cout << "in our guestbook www.theworldofchaos.com/contact/#guestbook and\n";
	cout << "also thank the author of the challenge davidcapello.com\n\n";
	cout << "Thank you\n";

	return 0;
}