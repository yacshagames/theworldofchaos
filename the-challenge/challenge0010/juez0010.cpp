/********************************************
SOLUCION JUEZ AL RETO0010:

Programado por:
   Jos‚ Luis De la Cruz L zaro - 20/XII/2000
   jcruz@ec-red.com
   http://www.geocities.com/joseluisdl

ENUNCIADO:

¨COMO HACER UNA PAUSA DURANTE UN TIEMPO INFERIOR A 55ms?

donde:
  ms = milisegundos = mil‚simas de segundo.

  El tiempo ingresado debe ser un n£mero entero de milisegundos.

ACLARACIONES:
  Como sabemos, la funci¢n delay, gettime, etc; dependen del procesador de
  tiempo de nuestra PC ( Timer), el cual trabaja con unidades de tiempo
  llamados ticks, donde cada tick equivale aproximadamente a 55ms. La pregunta
  es como se dise¤ar¡a una funci¢n que ponga una pausa durante 1ms, 2ms,
  3ms,...,55ms, 56ms, 57ms, 58ms,... en adelante ; y claro... tambi‚n hacer la
  codificaci¢n en C/C++.

  Para estandarizar las respuestas, la funci¢n debe tener la siguiente
  declaraci¢n:

DECLARACION:
  //Precision Delay
  //mseg = n£mero entero de milisegundos
  void pdelay( unsigned mseg );

SOLUCION:
La idea es muy simple, contar cuantos incrementos de un contador
de tipo entero suceden en 1 milisegundo.

A dichos incrementos les denomin‚ subticks, debido a que un tick
puede ser divido en un n£mero entero de subticks, y mejor aun,
1 milisegundo tiene tambi‚n un n£mero entero de subticks,
el cual se tiene calcular por m‚todos estad¡sticos.

El n£mero de "subticks por milisegundo" depende principalmente del
compilador que se use y de la velocidad del procesador, por lo que
es necesario implementar una funci¢n que cuente cuantos subticks
existen en 1 tick ( SubTicks() ) y otra que calcule el promedio
de en un cierto n£mero de ensayos, del resultado arrojado por SubTicks()
( esto lo hace SubTicksMedio() ).

Una vez calculado el n£mero de "subticks por milisegundo", reci‚n
se podria utilizar pdelay ya que bastar¡a una interpolaci¢n lineal
( o regla de tres simple ), para determinar el n£mero de subticks
en t miliseguntos ( T ), y poner una pausa ejecutando un bucle
que tendr¡a T pasos.

PORTABILIDAD DE pdelay(): ANSI C
Funciones necesarias para su uso: Subticks() y SucTicksMedio()
Variable global necesaria: SubTicks_por_ms


********************************************/
//NECESARIAS
#include <stdio.h> //printf scanf
#include <time.h>  //clock()

//OPCIONAL ( solo para el ejemplo de Simulaci¢n de un reloj )
#include <conio.h> //clrscr() getch() kbhit() gotoxy()

unsigned long SubTicks()
{
 clock_t inicio=clock();  //reseteo de cronometro
 unsigned long i=0;
 while( clock()==inicio )i++; //cuenta el n£mero de subticks de 1 solo tick
 return i; //retorna el n£mero de subticks en 1 tick
}

//Retorna la media del n£mero de SubTicks de 1 tick ( 55ms )
unsigned long SubTicksMedio( int NumMuestras )
{
 unsigned long S=0;

 for(int i=0;i<NumMuestras;i++)
  S+=SubTicks();

 return S/NumMuestras;
}

//Contiene el n£mero de Subticks por milisegundo
unsigned long SubTicks_por_ms;

//Precision Delay
//mseg = n£mero entero de milisegundos
void pdelay( unsigned mseg )
{
 unsigned long i=0, //contador de subticks
	     T = SubTicks_por_ms*mseg; //subticks transcurridos en "mseg" milisegundos
 while( ++i<T ) clock();//cuenta el n£mero de subticks ocurridos
                        //considerando el tiempo que dura en
                        //ejecutarse la funci¢n clock(), debido a que
                        //esta funci¢n se utiliz¢ para contar los subticks
}

void main(void)
{
  clrscr();

  int NumMuestras;
  printf("**********************************************\n");
  printf("* C lculo estadistico del n£mero de subticks *\n");
  printf("*    que da el procesador por milisegundo    *\n");
  printf("**********************************************\n");
  printf("\nIngrese el n£mero de muestras ( Sugerencia = 100 ) : ");
  scanf("%i", &NumMuestras);

  printf("\n\nEspere un momento por favor\n");
  printf("Mientras se calcula el numero de subticks que\n");
  printf("entrega el procesador por milisegundo...");

  SubTicks_por_ms = SubTicksMedio( NumMuestras )/55L;

  printf("\n\nC lculo terminado!!!");
  printf("\n\nN£mero de subticks por milisegundo promedio = %u", SubTicks_por_ms);
  printf("\n\nPresione cualquier tecla para continuar...");
  getch();

  //EJEMPLO DEL USO DE PDELAY
  clrscr();

  printf("Ejemplo del uso de pdelay()\n\n");
  //Prueba para 1 segundo
  clock_t tini = clock();
  pdelay(1000);
  printf("Tiempo transcurrido con el reloj de la BIOS : %f milisegundos", (float)(clock()-tini)/CLOCKS_PER_SEC)*1000 ;

  //Simulaci¢n de un Reloj, pero no es tan precisa porque parece que
  //el tiempo conjunto de operaci¢n de kbhit() gotoxy() y prinft()
  //atraza mucho el reloj
  //ES MAS NOTORIO EN DJGPP QUE EN BORLAND C 3.1...muy curioso...
  printf("\n\nPresione cualquier tecla para SALIR...\n\n");
  printf("Simulando un Reloj:\n\n");
  printf("Segundos transcurridos = 0");

  unsigned ms=0,s=0;

  while( !kbhit() )
  {
   ms++;

   pdelay(1); //pausa de 1 milisegundo

   if( ms==1000) //cada 1000ms transcurre 1 segundo
   {
    gotoxy(26,9);
    printf("%u",++s);
    ms=0;
   }

  }

}


