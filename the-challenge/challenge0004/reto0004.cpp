/*
 * Aqui hay algo no tan dificil, presten mucha atencion.
 * Cuales son los tres errores principales del programa?
 */

#include <stdio.h>
#include <stdlib.h>
#include <mem.h>


#undef NULL
#define NULL   0



typedef struct ELEMENTO
{
	int a, b, c;
	struct ELEMENTO *proximo;
} ELEMENTO;



typedef struct LISTA
{
	ELEMENTO *primero;
	int elementos;
} LISTA;



ELEMENTO *agregar_elemento_al_final(LISTA *lista, int a, int b, int c)
{
	ELEMENTO *nuevo, *posicion, *anterior;

	posicion = lista->primero;
	while (posicion) {
		anterior = posicion;
		posicion = posicion->proximo;
	}

	nuevo = malloc(sizeof(ELEMENTO));
	if (!nuevo)
		return NULL;

	nuevo->a = a;
	nuevo->b = b;
	nuevo->c = c;
	nuevo->proximo = NULL;

	if (!posicion)
		lista->primero = nuevo;
	else
		anterior->proximo = nuevo;

	lista->elementos++;

	return nuevo;
}



void borrar_elemento(LISTA *lista, ELEMENTO *elemento)
{
	ELEMENTO *posicion = lista->primero, *anterior = NULL;

	while (posicion) {
		if (posicion == elemento) {
			anterior->proximo = posicion->proximo;
			free(elemento);
			lista->elementos--;
			break;
		}
		anterior = posicion;
		posicion = posicion->proximo;
	}
}



LISTA *crear_lista(void)
{
	LISTA *lista;

	lista = malloc(sizeof(LISTA));
	if (!lista)
		return NULL;

	lista->primero = NULL;
	lista->elementos = 0;

	return lista;
}



void borrar_lista(LISTA *lista)
{
	ELEMENTO *posicion = lista->primero;

	while (posicion) {
		free(posicion);
		posicion = posicion->proximo;
	}

	free(lista);
}



void imprimir_lista(LISTA *lista)
{
	ELEMENTO *posicion = lista->primero;

	while (posicion) {
		printf("a=%d; b=%d; c=%d;\n", posicion->a, posicion->b, posicion->c);
		posicion = posicion->proximo;
	}
}



int main(void)
{
	LISTA *lista = crear_lista();
	ELEMENTO *elemento;

	printf("--\n");

	elemento =
		agregar_elemento_al_final(lista, 20, 1, -5);
	agregar_elemento_al_final(lista, 10, 2, -6);
	agregar_elemento_al_final(lista, 0, 3, -7);
	agregar_elemento_al_final(lista, 1, 3, -7);

	borrar_elemento(lista, elemento);

	imprimir_lista(lista);
	borrar_lista(lista);
	return 0;
}


