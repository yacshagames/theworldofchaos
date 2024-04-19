/***********************************************************************
 :::CUADRADOS MAGICOS:::
  >> Versión 1.0 17-IV-2001
 Solución al clásico problema matemático del cuadrado mágico (orden impar).
 Para los que no saben de que trata, se tiene que ubicar los n primeros
 numeros naturales (n impar) en una matriz de nxn de tal forma que la
 suma de cualquier fila, columna o diagonal debe ser siempre la misma.

 Ejemplo:

 Cuadrado Mágico de orden 3 :

 8 1 6
 3 5 7
 4 9 2

 Suma = 15

  >> ALGORITMO GENERAL

 Un modo de construir fácilmente cuadrados mágicos de orden impar.

1. Tomemos una serie aritmética cualquiera, para mayor comodidad la
   serie de los números naturales, y coloquemos el número 1 en la
   celda central de la fila superior.
2. La cifra consecutiva a una cualquiera debe colocarse en la celda
   que le sigue diagonalmente hacia arriba y hacia la derecha.
3. Si al hacer esto se sale del cuadrado por el límite superior del
   contorno del mismo, saltaremos a la celda de la columna siguiente
   hacia la derecha y en su fila inferior, si se sale por la derecha,
   se sigue por la primera celda, a partir de la izquierda, de la fila
   superior.
4. Cuando la celda siguiente está ocupada, el número consecutivo de la
   serie se coloca en la celda inmediatamente inferior a la del número
   precedente, comenzando así un nuevo camino en la dirección de la
   diagonal.

 :::Programado por:::
 José Luis De La Cruz Lázaro
 YACSHA - Software & Desing 2002
  >> yacsha@elmundodelcaos.tk    
  >> www.elmundodelcaos.tk -> EL MUNDO DEL CAOS - Unlimited Programming
  >> www.foros3d.tk  -> Foros de discusión  Flash/ActionScript - C/C++

***********************************************************************/



//Códificación basada en el algoritmo anterior

#include <stdio.h>

//limitar rango ( limita los valores de x al rango [0, N] )
#define lr( x, N ) ( (x)<0 ? N+(x)%N : ( (x)>=N ? (x)%N : (x) ) )

void main()
{
	int cuadrado[17][17], x, y, n, N;

	//restricción del orden a los impares entre 3 y 17, por motivos
	//de dar mayor facilidad para entender el código
	do {
		printf("\nIngrese el orden ( impar entre 3 y 17 ): ");
		scanf("%i", &N);
	} while (!(N % 2));
	printf("\nCuadrado Mágico de orden %ix%i :\n\n", N, N);

	//Se inicia los elementos del cuadrado mágico con ceros
	for (x = 0; x < N; x++)
		for (y = 0; y < N; y++)
			cuadrado[x][y] = 0;

	//Se aplica el algoritmo general para obtener cuadrados mágicos
	//de orden impar
	for (x = N / 2, y = 0, n = 1; n <= N * N; ) //se hace N*N iteraciones...
		if (!cuadrado[x][y])  //si el elemento seleccionado es cero
			cuadrado[x][y] = n++, //se inserta un número natural
			x = lr(x + 1, N),          //se incrementa x en 1
			y = lr(y - 1, N);          //se decrementa y en 1
		else x = lr(x - 1, N),      //se decrementa x en 1
			y = lr(y + 2, N);      //se incrementa y en 2

	  //se imprime el cuadrado mágico en pantalla
	for (y = 0; y < N; y++)
	{
		printf("\n");
		for (x = 0; x < N; x++)
			printf("%4i", cuadrado[x][y]);
	}

	printf("\n\n Suma = %i\n\n", (N*(N*N + 1)) / 2);//se imprime la suma

}
