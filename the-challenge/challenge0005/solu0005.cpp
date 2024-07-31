/* RETO0005.C
 * ==========     cworld@egroups.com
 *
 * 1. (y fundamental): ¨Por que no puedes obtener el mensaje de ACERTASTE ?
 *                     ¨que es lo que falla y por que?
 * 2. (secundario):    Como habria que cambiar el programa para que funcione?
 *                     (es decir para que acepte 1.2 como solucion)
 *
 * Notas: Comprobado en TurboC++, BorlandC++ , DJGPP
 *
 *     (C) Antonio Romeral   3-Sept-2000
 */

#include <stdio.h>

int main()
{
	float  vfloat;
	int exito = 0;

	puts(" RETO0005.C   Adivina el numero secreto");
	puts(" ==========   (por cierto, ese numero es 1.2)");
	puts(" (c) Antonio Romeral   3- Sept - 2000\n");

	do {
		puts("(Para rendirse introducir 0)");
		printf("¨Cual es el numero decimal secreto (entre 1 y 2) ? El numero es: ");
		scanf("%f", &vfloat);
		printf("\n Has introducido el numero: %f ", vfloat);

		if (vfloat == (float)1.2) { puts(">>> ACERTASTE !!!! "); exito = 1; break; }
		else { puts(">>> NO ES ESE NUMERO. Intentalo de nuevo\n"); }
	} while (vfloat);

	puts("\n\n\n");
	if (exito)  puts("PERFECTO. CONSEGUISTE LO IMPOSIBLE");
	else {
		puts("Intentalo en otra ocasion (¨que demonios pasa aqui?)");
		puts("(atiende... la solucion es 1.2). Intentalo !!!");
	}
	return 0;
}