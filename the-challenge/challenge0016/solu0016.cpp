//
// Programa CUADRADO.CPP. // Testeado en TC y BC.
//
// Soluci¢n al reto 16, creado por Antonio Gonz†lez para C World.
//
// Autor : Fabi†n Silva Pavez (CHILE), especialmente para el reto.
//
//
// Operaci¢n : Seleccione el orden y vea el cuadrado m†gico en
// C:\CUADRADO.TXT, lo hice as° ya que la pantalla limita hasta 80x50.
//
//

#include <fstream.h>
#include <iomanip.h>

class Cuadrado {
      int **Cuad;             // El cuadrado m†gico
      int
	  n,                  // Orden del cuadrado
	  Cifras;             // N£mero de cifras del mayor n¯ del cuadrado
  public:
      Cuadrado (int N);       // Constructor, s¢lo asigna memoria
      ~Cuadrado();            // Destructor, libera la memoria
      void Procesar();        // Genera el cuadrado m†gico
      void Listar();          // Listar el cuadrado en el archivo
};
Cuadrado::Cuadrado(int N) {
      n=N;
      Cuad = new int*[n];
      for (int i=0; i<n; i++)
	Cuad[i] = new int[n];
};
Cuadrado::~Cuadrado() {
      for (int i=0; i<n; i++)
	  delete Cuad[i];
      delete Cuad;
};
void Cuadrado::Procesar() {
int i=0, j, X, Y;
      X=n*n;                  // n^2 es el mayor n£mero, sirve para
      while (X) {             // saber cuantos espacios se salta
	  X/=10;              // entre cada n£mero del cuadrado al archivo
	  i++;
      };
      Cifras = i;             // N£mero de cifras
      for (i=0; i<n; i++)     // Avanza por fila
      {
	  X = (n/2 + i) % n;  // Ver algoritmo, al final de este archivo.
	  Y = (X + 1) % n;
	  for (j=0; j<n; j++)
	      Cuad [(X - j + n)%n][(Y + j)%n] = i * n + j + 1;
      };
};
void Cuadrado::Listar() {
int i, j;
fstream f;

    f.open ("C:\\CUADRADO.TXT", ios::out);

    f << "Cuadrado M†gico lado " << n << ", Suma = " << n*(n*n+1)/2 << endl;
    f << "------------------------" << endl;

    for (i=0; i<n; i++) {
	for (j=0; j<n; j++)
	    f << setfill(' ') << setw(Cifras+1) << Cuad[i][j];
	f << endl;
    };
    f.close();
};
void main ()
{
unsigned int orden;
Cuadrado *c;

     cout << "Ingrese un n£mero positivo n (n > 2, y n es impar): ";
     cin >> orden;

     if (orden > 2 && orden%2)
     {
	 c = new Cuadrado(orden);
	 c->Procesar();
	 c->Listar();
	 cout << "El cuadrado m†gico de orden " << orden;
	 cout << " se encuentra en C:\\CUADRADO.TXT.";
     }
     else
	 cout << "El numero " << orden << " no es > 2 o no es impar.";
     asm { mov ah, 7; int 21h; }; // pausilla
};

/* ALGORITMO:

Para n == 5

1. Cuadrado M†gino vac°o

		€€€€€€€€€€€€€€€€€€€€€€€€€€€
		€€   €€   €€   €€   €€   €€
		€€€€€€€€€€€€€€€€€€€€€€€€€€€
		€€   €€   €€   €€   €€   €€
		€€€€€€€€€€€€€€€€€€€€€€€€€€€
		€€   €€   €€   €€   €€   €€
		€€€€€€€€€€€€€€€€€€€€€€€€€€€
		€€   €€   €€   €€   €€   €€
		€€€€€€€€€€€€€€€€€€€€€€€€€€€
		€€   €€   €€   €€   €€   €€
		€€€€€€€€€€€€€€€€€€€€€€€€€€€


2. Generar las siguientes extensiones al cuadrado.
3. Escribir los n£meros en forma escalonada, tal como se muestra.

			  ±±±±±±±
			  ±± 5 ±±
		     ±±±±±±±±±±±±±±±±±
		     ±± 4 ±±   ±± 10±±
		€€€€€€€€€€€€€€€€€€€€€€€€€€€
		€€ 3 €€   €€ 9 €€   €€ 16€€
	   ±±±±±€€€€€€€€€€€€€€€€€€€€€€€€€€€±±±±±
	   ±± 2 €€   €€ 8 €€   €€ 15€€   €€ 21±±
      ±±±±±±±±±±€€€€€€€€€€€€€€€€€€€€€€€€€€€±±±±±±±±±±
      ±± 1 ±±	€€ 7 €€   €€ 13€€   €€ 20€€   ±± 25±±
      ±±±±±±±±±±€€€€€€€€€€€€€€€€€€€€€€€€€€€±±±±±±±±±±
	   ±± 6 €€   €€ 12€€   €€ 19€€   €€ 24±±
	   ±±±±±€€€€€€€€€€€€€€€€€€€€€€€€€€€±±±±±
		€€ 11€€   €€ 18€€   €€ 23€€
		€€€€€€€€€€€€€€€€€€€€€€€€€€€
		     ±± 17±±   ±± 22±±
		     ±±±±±±±±±±±±±±±±±
			  ±± 21±±
			  ±±±±±±±


4. Mover las extensiones hasta su lado contrario,
   ejemplo la extensi¢n izquierda

			  ±±±±±±±
			  ±± 5 ±±
		     ±±±±±±±±±±±±±±±±±
		     ±± 4 ±±   ±± 10±±
		€€€€€€€€€€€€€€€€€€€€€€€€€€€
		€€ 3 €€   €€ 9 €€   €€ 16€€
		€€€€€€€€€€€€€€€€€€€€≤≤≤≤≤≤≤±±±±±
		€€   €€ 8 €€   €€ 15≤≤ 2 ≤≤ 21±±
		€€€€€€€€€€€€€€€≤≤≤≤≤≤≤≤≤≤≤≤±±±±±±±±±±
		€€ 7 €€   €€ 13≤≤ 1 ≤≤ 20≤≤   ±± 25±±
		€€€€€€€€€€€€€€€≤≤≤≤≤≤≤≤≤≤≤≤±±±±±±±±±±
		€€   €€ 12€€   €€ 19≤≤ 6 ≤≤ 24±±
		€€€€€€€€€€€€€€€€€€€€≤≤≤≤≤≤≤±±±±±
		€€ 11€€   €€ 18€€   €€ 23€€
		€€€€€€€€€€€€€€€€€€€€€€€€€€€
		     ±± 17±±   ±± 22±±
		     ±±±±±±±±±±±±±±±±±
			  ±± 21±±
			  ±±±±±±±

5. Y as° sucesivamente, hasta completar el cuadrado.

Para buscar la sucesi¢n hice:

n¯| Posicion
------------
1 : (2,3)                          = (5/2, 5/2+1)
2 : (1,4) = ( (2-1+5)%5, (3+1)%5 )
3 : (0,0) = ( (2-2+5)%5, (3+2)%5 )
4 : (4,1) = ( (2-3+5)%5, (3+3)%5 )
5 : (3,2) = ( (2-4+5)%5, (3+4)%5 )
6 : (3,4) =                        = ( (2+1)%5, (3+1)%5 )
7 : (2,0) = ( (3-1+5)%5, (4+1)%5 )
8 : (1,1) = ( (3-2+5)%5, (4+2)%5 )
9 : (0,2) = ( (3-3+5)%5, (4+3)%5 )
10: (4,3) = ( (3-4+5)%5, (4+4)%5 )
11: (4,0)                          = ( (2+2)%5, (3+2)%5 )
12: (3,1) = ( (4-1+5)%5, (0+1)%5 )
13: (2,2) = ( (4-2+5)%5, (0+2)%5 )
14: (1,3) = ( (4-3+5)%5, (0+3)%5 )
15: (0,4) = ( (4-4+5)%5, (0+4)%5 )
16: (0,1)                          = ( (2+3)%5, (3+3)%5 )
17: (4,2) = ( (0-1+5)%5, (1+1)%5 )
18: (3,3) = ( (0-2+5)%5, (1+2)%5 )
19: (2,4) = ( (0-3+5)%5, (1+3)%5 )
20: (1,0) = ( (0-4+5)%5, (1+4)%5 )
21: (1,2)                          = ( (2+4)%5, (3+4)%5 )
22: (0,3) = ( (1-1+5)%5, (2+1)%5 )
23: (4,4) = ( (1-2+5)%5, (2+2)%5 )
24: (3,0) = ( (1-3+5)%5, (2+3)%5 )
25: (2,1) = ( (1-4+5)%5, (2+4)%5 )

*/