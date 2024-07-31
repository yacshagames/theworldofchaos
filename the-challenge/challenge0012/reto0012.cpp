/* Copyright (C) 2000 por David A. Capello */
/*
 * El programa debe de dibujar 10 rect ngulos de un tama¤o que var¡a
 * siempre entre 1 a 10 tanto de ancho como de alto (10x10);
 * Ahora que pasa, hay un problema, los rect ngulos quieren aprobechar
 * el espacio al m ximo y no ponerse uno encima de otro, por lo que
 * la tarea ser  generar el algoritmo que busque la mejor posici¢n
 * para que se ubique el rect ngulo (ver la funci¢n `dibujar_rectangulo');
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>



#define ANCHO   64
#define ALTO    38 /* alto debe ser siempre par (ya que se dibujan
					  de dos en dos las l¡neas) */



char pantalla[ALTO][ANCHO]; /* modo de acceso: pantalla[y][x] */



/* borra todo el buffer de la pantalla con 0 (ceros) */
void borrar_pantalla()
{
	int x, y;

	/* recorrer de arriba hacia abajo */
	for (y = 0; y < ALTO; y++)
		/* recorrer de izquierda a derecha*/
		for (x = 0; x < ANCHO; x++)
			pantalla[y][x] = 0;
}



/* dibuja un rect ngulo del tama¤o dado en cualquier posici¢n de la
   pantalla, eso s¡, no puede tapar zonas ya ocupadas por otros
   rect ngulos */
void dibujar_rectangulo(int alto, int ancho)
{
	int x, y, comienzox, comienzoy;

	/* AQUI DEBEN COMPLETAR USTEDES: ****************************************/
	/* Deben realizar la funci¢n que busque posicionar
	 * bien el rect ngulo en la pantalla como para que no
	 * tape a los otros... si no, les dar  un error y
	 * se acaba la ejecuci¢n;
	 *
	 * NOTA: la funci¢n deber¡a de dibujar siempre bien,
	 * por lo que esta propuesta del random no vale
	 * ya que es al azar, y algunas veces anda y otras NO,
	 * por lo que cualquier otra forma que utilice random
	 * o generadores de n£meros aleatorios o pseudo-aleatorios
	 * estar  err¢nea;
	 */
	comienzox = rand() % 32;
	comienzoy = rand() % 20;

	/* Y HASTA AQUI TERMINA SU TRABAJO **************************************/

	if ((comienzox < 0) || (comienzox + ancho > ANCHO) ||
		(comienzoy < 0) || (comienzoy + alto > ALTO)) {
		printf("Lo siento, perdiste!, dibujaste fuera de los l¡mites de la pantalla\n");
		exit(1);
	}

	/* dibujarlo */
	for (y = comienzoy; y < comienzoy + alto; y++)
		for (x = comienzox; x < comienzox + ancho; x++) {
			if (pantalla[y][x]) {
				printf("Lo siento, perdiste!, dibujaste encima de otro rect ngulo\n");
				exit(1);
			}

			pantalla[y][x] = 1;
		}
}



/* dibuja la pantalla completa */
void dibujar_pantalla()
{
	int x, y;

	/* dibujar algo para separar del resto de las l¡neas */
	printf("-------- [PANTALLA] --------\n");

	/* dibujar la pantalla (NOTA: se van dibujan de a 2 l¡neas seguidas
	   con los caracteres:
		 'Û' (lleno), 'ß' (superior), 'Ü' (inferior), ' ' (vac¡o);
	*/
	for (y = 0; y < ALTO; y += 2) {
		putc((unsigned char)'³', stdout);

		/* dibujar dos l¡neas */
		for (x = 0; x < ANCHO; x++) {
			/* primer l¡nea llena */
			if (pantalla[y][x]) {
				/* segunda tambi‚n */
				if (pantalla[y + 1][x])
					putc((unsigned char)219, stdout);
				/* segunda vac¡a */
				else
					putc((unsigned char)223, stdout);
			}
			/* primer l¡nea vac¡a */
			else {
				/* pero segunda llena */
				if (pantalla[y + 1][x])
					putc((unsigned char)220, stdout);
				/* todo vac¡o */
				else
					putc((unsigned char)32, stdout);
			}
		}

		/* saltar a la pr¢xima l¡nea */
		printf("³\n");
	}

	/* dibujar otro separador */
	printf("----------------------------\n");
}



int main()
{
	int c;

	/* comenzar el generador de n£meros aleatorios */
	srand(time(NULL));

	/* borrar la pantalla */
	borrar_pantalla();

	/* dibujar diez rect ngulos */
	for (c = 0; c < 10; c++)
		dibujar_rectangulo((rand() % 10) + 1, (rand() % 10) + 1);

	/* dibujar totalmente la pantalla */
	dibujar_pantalla();

	/* como lo anterior puede producir safadas, vamos a probar ahora
	   la funci¢n con los l¡mites je je je :-) */
	borrar_pantalla();
	for (c = 0; c < 10; c++)
		dibujar_rectangulo(10, 10);
	dibujar_pantalla();

	printf("GANASTE! Recuerda mandar el programa a <cworld@egroups.com> lo\n");
	printf("antes posible para ganar, y adjunta el archivo .c (y £nicamente el\n");
	printf("c¢digo fuente), cualquiera que mande un ejecutable ser  descalificado.\n");
	return 0;
}


