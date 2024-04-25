/***********************************************************************
 ::: DATA MATRICIAL :::
  >> Versión 1.0 31-X-2000

 CALCULA LA INVERSA DE UNA MATRIZ

 :::Programado por:::
 José Luis De La Cruz Lázaro
 YACSHA - Software & Desing 2002
  >> yacsha@elmundodelcaos.tk    
  >> www.elmundodelcaos.tk -> EL MUNDO DEL CAOS - Unlimited Programming
  >> www.foros3d.tk  -> Foros de discusión  Flash/ActionScript - C/C++

***********************************************************************/

#include <iostream.h>

void main(){

     float A[30][30],AI[30][30];
     int n,a,b,c,d,g,f,h,i,j,k,m,p,r,s,t;
     cout<<"ingrese el valor de n=";
     cin>>n;
     //elegir matriz
     for(a=0;a<n;a++)
      for(b=0;b<n;b++){
	   cout<<"A["<<a<<"]["<<b<<"]=";
	   cin>>A[a][b];
	  }
     //Ordenar matriz
     cout<<" Matriz ordenada: ";
     for(c=0;c<n;c++){
       cout<<"\n";
       for(d=0;d<n;d++){
		cout<<A[c][d]<<" ";
		}
	      }


     //Aumentando matriz identidad
     for(g=0;g<n;g++)
     {
	for(h=n;h<2*n;h++)
	{
	       if(g==h-n)
	       {
		A[g][h]=1;
	       }
	       else A[g][h]=0;
	}
     }
     //Pivotear matriz aumentada
     for(j=0;j<n;j++)
      for(i=0;i<n;i++)
      {
	   if(A[j][j]!=0)
	   {
	      if(i!=j)
	      {
		   float cte=A[i][j]/A[j][j];
		   for(k=0;k<2*n;k++)
		   {
				A[i][k]=A[i][k]-cte*A[j][k];
		   }
	      }
	   }
	   else
	   {
	    for(r=j+1;r<n;r++)
	    {
	      for(m=0;m<2*n;m++)
	      {
			   A[j][m]=A[j][m]+A[r][m];
	      }
	      if(A[j][j]!=0)break;
	    }
	      if(i!=j)
	      {
		for(p=0;p<2*n;p++)
		{
		   A[i][p]=A[i][p]-(A[i][j]/A[j][j])*A[j][p];
		}
	      }
	   }
      }


     //Comversion a identidad el lado izquierdo
     for(s=0;s<n;s++)
     {
      float cte=A[s][s];
      for(t=0;t<2*n;t++)
      {
	 A[s][t]=A[s][t]/cte;
      }
     }

     //Llamando matriz inversa AI;
     cout<<"\n\n Mostrar matriz inversa: ";
     for(i=0;i<n;i++)
     {
	 cout<<"\n";
      for(j=n;j<2*n;j++)
      {
       cout<<A[i][j]<<" ";
      }
     }
}
