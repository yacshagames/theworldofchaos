/***********************************************************************
 ::: LAS TORRES DE HANOI :::
  >> Versi�n 1.0 19-X-2000
 Cl�sico algoritmo de las torres de hanoi solucionado mediante una
 funci�n recursiva.

 :::Programado por:::
 Jos� Luis De La Cruz L�zaro
 YACSHA - Software & Desing 2002
  >> yacsha@elmundodelcaos.tk    
  >> www.elmundodelcaos.tk -> EL MUNDO DEL CAOS - Unlimited Programming
  >> www.foros3d.tk  -> Foros de discusi�n  Flash/ActionScript - C/C++

***********************************************************************/

#include <iostream.h>

void Hanoi(int n,char A,char B,char C)
   {
    if(n>0)
    {
     Hanoi(n-1,A,C,B);
     cout<<"\nMover el disco "<<n<<" de "<<A<<" a "<<C;
     Hanoi(n-1,B,A,C);
    }
   }

void main()
{
 int n;
 cout<<"\n\nIngrese el n�mero de discos por torre: ";
 cin>>n;
 Hanoi(n,'A','B','C');
}
