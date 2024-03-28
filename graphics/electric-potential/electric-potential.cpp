#include <grafxy.h>

int huge func()
{
 return 2;
}

void ModoGrafico( void )
{
 int controlador,modo;

 controlador=DETECT;
 installuserdriver("Svga256",func);
 initgraph(&controlador,&modo,"c:\\bc31\\bgi");

}

void Paleta(unsigned char r, unsigned char g, unsigned char b)
{
	unsigned char cont1,Paleta[256][3];
	int cont;

	for (cont=0;cont<256;cont++)
		{
		      Paleta[cont][0]=r*(cont+1);
		      Paleta[cont][1]=g*(cont+1);
		      Paleta[cont][2]=b*(cont+1);
		}


	cont=0;
	cont1=0;

	// El c¢digo que sigue a continuaci¢n pasa el contenido del array "Paleta"
	//a la paleta de la VGA
	for (cont=0;cont<256;cont++)
	{
		outportb (0x03c8,cont);
		for (cont1=0;cont1<3;cont1++)
			outportb (0x03c9,Paleta[cont][cont1]);
			//cout<<Paleta
	}

}

void potenciales( CRegionXY &campo, float x, float y, float radio,
	    float arr, float der , float aba, float izq )
{
 float potencial[13][3];

  potencial[0][0]=(izq+der+aba+arr)/4;
  potencial[1][0]=(izq+arr)/2;
  potencial[2][0]=(arr+der)/2;
  potencial[3][0]=(der+aba)/2;
  potencial[4][0]=(aba+izq)/2;
  potencial[5][0]=(potencial[1][0]+arr+potencial[0][0]+izq)/4;
  potencial[6][0]=(arr+potencial[2][0]+der+potencial[0][0])/4;
  potencial[7][0]=(potencial[0][0]+der+potencial[3][0]+aba)/4;
  potencial[8][0]=(izq+potencial[0][0]+aba+potencial[4][0])/4;
  potencial[9][0]=(potencial[5][0]+potencial[0][0]+potencial[8][0]+izq)/4;
  potencial[10][0]=(arr+potencial[6][0]+potencial[0][0]+potencial[5][0])/4;
  potencial[11][0]=(potencial[6][0]+der+potencial[7][0]+potencial[0][0])/4;
  potencial[12][0]=(potencial[0][0]+potencial[7][0]+aba+potencial[9][0])/4;

  float R=radio/4;

  potencial[0][1]=x+2*R;
  potencial[0][2]=y+2*R;

  potencial[1][1]=x;
  potencial[1][2]=y+radio;
  potencial[2][1]=x+radio;
  potencial[2][2]=y+radio;
  potencial[3][1]=x+radio;
  potencial[3][2]=y;
  potencial[4][1]=x;
  potencial[4][2]=y;

  potencial[5][1]=x+R;
  potencial[5][2]=y+3*R;
  potencial[6][1]=x+3*R;
  potencial[6][2]=y+3*R;
  potencial[7][1]=x+3*R;
  potencial[7][2]=y+R;
  potencial[8][1]=x+R;
  potencial[8][2]=y+R;

  potencial[9][1]=x+R;
  potencial[9][2]=y+2*R;
  potencial[10][1]=x+2*R;
  potencial[10][2]=y+3*R;
  potencial[11][1]=x+3*R;
  potencial[11][2]=y+2*R;
  potencial[12][1]=x+2*R;
  potencial[12][2]=y+R;

  for(int i=0;i<13;i++)
   campo.punto(potencial[i][1],potencial[i][2],(int)(100*potencial[i][0])%256);

 if(radio>0.05)
 {
   R=radio/2;
   potenciales(campo, x,   y+R, R, arr,potencial[10][0],potencial[9][0],izq) ;
   potenciales(campo, x+R, y+R, R, arr,der,potencial[11][0],potencial[10][0]);
   potenciales(campo, x+R, y  , R, potencial[11][0],der,aba,potencial[12][0]);
   potenciales(campo, x, y    , R, potencial[9][0],potencial[12][0],aba,izq);
 }


}

void main()
{
 ModoGrafico();

 CRegionXY campo(0,10,0,10);

 Paleta(10,5,1);

 potenciales(campo,0,0,10,2.54,0,0,0);

 getch();
 closegraph();

}




