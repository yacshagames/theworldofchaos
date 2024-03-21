/* Solucionado por RiMS */

#include "stdio.h"
#include "math.h"

/* Espero que esta sea la secante... */
#define SEC(x) (1 / cos( x ) )

/* defino las Expresiones para cada intervalo con Macros */
/* Esto no es obligatorio, lo podría haber puesto dentro 
    del return(...) pero me queda mas claro al codificar */
#define Exp1(x) ( 2 * sin( (x)/2 ) * pow( cos( (x)/2 ), 2.0 ) )
#define Exp2(x) ( 1.0/4.0 * sin(2 * (x) ) * SEC( (x)/2 ) )
#define Exp3(x) ( exp( (x) ) * tan( (x) ) )


double f( double x) {
	return(  Exp1(x) * (x<0) +
		  Exp2(x) * (x>=0) * (x<2) +
		  Exp3(x) * (x > 2) );
}

void main() {
	double x;
	printf("\nIngrese X: ");
	scanf("%lf", &x);

	printf("\nResultado: f( %lg ): %lf", x, f(x));
}


