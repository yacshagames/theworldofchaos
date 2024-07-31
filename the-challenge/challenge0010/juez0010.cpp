
/********************************************

Hello to all those following the Challenge...

As I promised, here I am giving the complete JUDGE solution to Challenge 0010 (attached file). I would like to be excused for the delay, since due to lack of time I had not commented on it properly, nor had I created an application example. I say this because to test the operation of the pdelay function, I do it by simulating a clock.

**********************************************
JUDGE SOLUTION TO CHALLENGE0010 - 20/XII/2000
created by: Jose Luis De la Cruz Lazaro
			contact@theworldofchaos.com
			www.theworldofchaos.com
**********************************************

The idea is very simple, to count how many increments of an integer counter occur in 1 millisecond.

I called these increments subticks, because a tick can be divided into an integer number of subticks, and better yet, 1 millisecond also has an integer number of subticks, which must be calculated by statistical methods.

The number of "subticks per millisecond" depends mainly on the compiler used and the speed of the processor, so it is necessary to implement a function that counts how many subticks exist in 1 tick ( SubTicks() ) and another that calculates the average of the result returned by SubTicks() over a certain number of trials (this is done by SubTicksAverage() ).

Once the number of "subticks per millisecond" has been calculated, pdelay can then be used, since a linear interpolation (or simple rule of three) would be enough to determine the number of subticks in t milliseconds ( T ), and to pause by executing a loop that would have T steps.

PORTABILITY OF pdelay(): ANSI C
Functions required for its use: Subticks() and SucTicksMedio()
Global variable required: SubTicks_per_ms

Regards

	   o  o José Luis De la Cruz Lázaro o   220KV of Chaos
	 o       o  Visit my homepage:          o      o
   o    o o    o EL MUNDO DEL CAOS            o   o o
  o   o  o     o   https://www.theworldofchaos.com   o  o
  o    o     o                                   o    o  o
   o     o o     Chaos = Chaos & math ? C++ : ++C;        o
	 o                                                     o
		o  o  o o o  FRACTALS UNLIMITED ooo o  o  o  o  o   o
					o  o   o   o   o   o
	 o               o   o   o   o   o
   o   o      o
 o      o   o  o  o  o  o o oooo      Yacsha Software & Desing
								 O  O  o ooo Lima - Perú ooo o o O  O

********************************************/
//NECESARIAS
#include <iostream>
#include <time.h>
using std::cout;
using std::cin;
using std::endl;

unsigned long SubTicks()
{
	clock_t inicio = clock();  //reseteo de cronometro
	unsigned long i = 0;
	while (clock() == inicio)i++; //cuenta el n£mero de subticks de 1 solo tick
	return i; //retorna el n£mero de subticks en 1 tick
}

//Retorna la media del n£mero de SubTicks de 1 tick ( 55ms )
unsigned long SubTicksMedio(int NumMuestras)
{
	unsigned long S = 0;

	for (int i = 0; i < NumMuestras; i++)
		S += SubTicks();

	return S / NumMuestras;
}

//Contiene el n£mero de Subticks por milisegundo
unsigned long SubTicks_por_ms;

//Precision Delay
//mseg = n£mero entero de milisegundos
void pdelay(unsigned mseg)
{
	unsigned long i = 0, //contador de subticks
		T = SubTicks_por_ms * mseg; //subticks transcurridos en "mseg" milisegundos
	while (++i < T) clock();//cuenta el n£mero de subticks ocurridos
						   //considerando el tiempo que dura en
						   //ejecutarse la funci¢n clock(), debido a que
						   //esta funci¢n se utiliz¢ para contar los subticks
}

void main(void)
{

	int NumMuestras;
	cout << "**********************************************\n";
	cout << "* Calculo estadistico del numero de subticks *\n";
	cout << "*    que da el procesador por milisegundo    *\n";
	cout << "**********************************************\n";
	cout << "\nIngrese el numero de muestras ( Sugerencia = 100 ) : ";
	cin >> NumMuestras;

	cout << "\n\nEspere un momento por favor\n";
	cout << "Mientras se calcula el numero de subticks que\n";
	cout << "entrega el procesador por milisegundo...";

	SubTicks_por_ms = SubTicksMedio(NumMuestras) / 55L;

	cout << "\n\nCalculo terminado!!!";
	cout << "\n\nNumero de subticks por milisegundo promedio = " << SubTicks_por_ms;
	cout << "\n\nIngrese 1 para continuar...";
	int n;
	cin >> n;

	//EJEMPLO DEL USO DE PDELAY


	cout << "Ejemplo del uso de pdelay()\n\n";
	//Prueba para 1 segundo
	clock_t tini = clock();
	pdelay(1000);
	cout << "Tiempo transcurrido con el reloj de la BIOS : " << ((double)(clock() - tini) / CLOCKS_PER_SEC)*1000.0 << " milisegundos";

	//Simulaci¢n de un Reloj, pero no es tan precisa porque parece que
	//el tiempo conjunto de operaci¢n de kbhit() gotoxy() y prinft()
	//atraza mucho el reloj
	//ES MAS NOTORIO EN DJGPP QUE EN BORLAND C 3.1...muy curioso...
	cout << "\n\nPresione cualquier tecla para SALIR...\n\n";
	cout << "Simulando un Reloj:\n\n";
	cout << "Segundos transcurridos:" << endl;

	unsigned int ms = 0, s = 0;

	while (true)
	{
		ms++;

		pdelay(1); //pausa de 1 milisegundo

		if (ms == 1000) //cada 1000ms transcurre 1 segundo
		{
			cout << (++s) << endl;
			ms = 0;
		}

		if (s == 11)
			break;
	}

}


