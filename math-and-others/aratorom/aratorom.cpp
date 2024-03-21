/***********************************************************************
 :::CONVERTIDOR DE ARABIGOS A ROMANOS:::
  >> Versión 1.0 31-X-2000
 Convierte un número Arabigo (numeración ordinaria) de 4 cifras
 a números Romanos.

 Ejemplo:
 Si ingreso 59 y retorna LIX.

 :::Programado por:::
 José Luis De La Cruz Lázaro
 YACSHA - Software & Desing 2002
  >> yacsha@elmundodelcaos.tk    
  >> www.elmundodelcaos.tk -> EL MUNDO DEL CAOS - Unlimited Programming
  >> www.foros3d.tk  -> Foros de discusión  Flash/ActionScript - C/C++

***********************************************************************/

#include <iostream.h>

void transf(int cifra,int orden){
		    char  ui,um,uf;
		    switch(orden){ case 0: ui='I';
					   um='V';
					   uf='X';
					   break;
				   case 1: ui='X';
					   um='L';
					   uf='C';
					   break;
				   case 2: ui='C';
					   um='D';
					   uf='M';
					   break;
				   case 3: ui='M';
					   break;
				}
		    switch(cifra){ case 1: cout<<ui;break;
				   case 2: cout<<ui<<ui;  break;
				   case 3: cout<<ui<<ui<<ui; break;
				   case 4: cout<<ui<<um;break;
				   case 5: cout<<um;break;
				   case 6: cout<<um<<ui;break;
				   case 7: cout<<um<<ui<<ui;break;
				   case 8: cout<<um<<ui<<ui<<ui;break;
				   case 9: cout<<ui<<uf;break;
				 }
			       }
void main(){
       int N,a,b,c,d;
       cout<<"Ingrese un numero arabigo: "; cin>>N;
       d=N%10;
       c=N%100/10;
       b=N%1000/100;
       a=N/1000;

       transf(a,3);
       transf(b,2);
       transf(c,1);
       transf(d,0);

  }
