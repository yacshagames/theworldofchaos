/*
* Here's something not so difficult, pay close attention.
* What are the three main errors in the program?
*/

#include <iostream>

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
	ELEMENTO *nuevo, *posicion, *anterior=NULL;

	posicion = lista->primero;
	while (posicion) {
		anterior = posicion;
		posicion = posicion->proximo;
	}

	nuevo = new ELEMENTO;
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
			delete elemento;
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

	lista = new LISTA;
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
		delete posicion;
		posicion = posicion->proximo;
	}

	delete lista;
}



void imprimir_lista(LISTA *lista)
{
	ELEMENTO *posicion = lista->primero;

	while (posicion) {
		std::cout << "a="<< posicion->a << " b=" << posicion->b << " c=" << posicion->c << std::endl;
		posicion = posicion->proximo;
	}
}



int main(void)
{
	LISTA *lista = crear_lista();
	ELEMENTO *elemento;

	std::cout << "--\n";

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


