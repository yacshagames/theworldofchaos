/***********************************************************************
 ::: BMPPlus :::
  >> Versión 1.0 8-IX-2000
 Similar al PCXPlus pero grafica mapas de bits (BMP) utilizando
 rutinas de dibujo a bajo nivel en las resoluciones de 320x200
 y 640x480 con 256 colores.

 :::Programado por:::
 José Luis De La Cruz Lázaro
 YACSHA - Software & Desing 2002
  >> yacsha@elmundodelcaos.tk    
  >> www.elmundodelcaos.tk -> EL MUNDO DEL CAOS - Unlimited Programming
  >> www.foros3d.tk  -> Foros de discusión  Flash/ActionScript - C/C++

***********************************************************************/
#include <stdio.h>
#include <conio.h>

#include <dos.h>
#include <mem.h>
#include <alloc.h>
#include <math.h>
#include <iostream.h>


// Clase VIDEO (original) gracias a:
// Emmanuel Garc‚s - Manolo_1981@yahoo.com
// Optimizado por:
// Jos‚ Luis De la Cruz L zaro - webmaster@elmundodelcaos.cjb.net
//			       - ramondc@hotmail.com

class VIDEO
{

	public:

	unsigned char far *vga;

	VIDEO();
	~VIDEO();

	void pixel(int x, int y, unsigned char color);
	void linea(int x1, int y1, int x2, int y2, unsigned char color);
	void limpiar(unsigned char color);
	void desplegar();
};

unsigned char far *vga_mem = (unsigned char far *) 0xA0000000L;

void modo_grafico(int);
void modo_texto();


VIDEO::VIDEO()
{
	vga=(unsigned char far*)farmalloc(sizeof(unsigned char far)*64000);
}

VIDEO::~VIDEO()
{
	farfree(vga);
}

void VIDEO::pixel(int x, int y, unsigned char color)
{
	if (x>=0 && x<320 && y>=0 && y<200)
	vga[(y<<8)+(y<<6)+x]=color;
}

void VIDEO::linea(int x1, int y1, int x2, int y2, unsigned char color)
{
	int i,dx,dy,sdx=0,sdy=1,dxabs,dyabs,x,y,px,py;

	x1=160+x1*200;
	x2=160+x2*200;
	y1=100-y1*200;
	y2=100-y2*200;

	dx=x2-x1;
	dy=y2-y1;
	dxabs=abs(dx);
	dyabs=abs(dy);	if (dx) sdx=dx/dxabs;
	if (dy) sdy=dy/dyabs;
	x=dyabs>>1;
	y=dxabs>>1;
	px=x1;
	py=y1;
    pixel(px,py,color);

	if (dxabs>=dyabs)
	{
		for(i=0;i<dxabs;i++)
		{
			y+=dyabs;
			if (y>=dxabs)
			{
				y-=dxabs;
				py+=sdy;
			}
		px+=sdx;
	    pixel(px,py,color);
		}
	}
	else
	{
		for (i=0;i<dyabs;i++)
		{
			x+=dxabs;
			if (x>=dyabs);
			{
				x-=dyabs;
				px+=sdx;
			}
			py+=sdy;
		   pixel(px,py,color);
		}
	}
}

void VIDEO::limpiar(unsigned char color)
{
	for (unsigned int i=0;i<64000;i++)
	 vga[i]=color;

	desplegar();
}

void VIDEO::desplegar()
{
	_fmemcpy(vga_mem,vga,64000);
}

void modo_grafico(int modo)
{
	if( modo==0 )_AX=0x00013;
	else
	{
	 _AX=0x4f02;
	 _BX=0x101;
	}
	geninterrupt(0x10);
}

void modo_texto()
{
	_AX=0x0003;
	geninterrupt(0x10);
}


void putpixel(unsigned int x,unsigned int y,unsigned char color)
  {

    asm{
    mov ah,0x0c;
    mov al,color;
    mov cx,x;
    mov dx,y;
    mov bx,0x01;
    int 0x10;
    }

  }

/*
 Clase BMP desarrollada por:
  Jos‚ Luis De la Cruz L zaro - webmaster@elmundodelcaos.cjb.net
			      - ramondc@hotmail.com

 Rutinas para control de la paleta gracias a:
  Emmanuel Garc‚s - Manolo_1981@yahoo.com

 Informaci¢n acercade la estructura interna del BMP, gracias a:
  Fabi n Sierra C. - magic_century@hotmail.com

Tipo es un 'n£mero m gico' que se usa para comprobar que el archivo es .bmp.
tamano es el tama¤o del archivo bmp incluyendo la cabecera y bmp_info
reservado no se usa normalmente (por lo menos hasta el a¤o pasado no se usaba).
Desplazamiento es el desplazamiento de los datos con respecto al inicio del archivo.
Es igual al tama¤o de las estructuras de cabecera, cuando no hay paleta y
cuando hay paleta se suman los bytes utilizados por la paleta.

Bytes_en_cabecera es exactamente eso y a m¡ me parece un dato in£til.
Planos es un campo que nunca he utilizado.Bits_por_pixel es importante;
ya lo explicar‚ en detalle. Compresion... no tengo idea.
Si me topo con un archivo con un valor an¢malo en este campo,lo descarto.
Los colores se generan en la pantalla usando una combinaci¢n de rojo,verde
y azul. Al conjunto de combinaciones se le llama la paleta de colores.
Un color es referenciado como un n£mero.El rango del n£mero depende de los
bits usados para referenciarlo.Si es 1 bit,se permiten 2 colores.
Si son 4,16,etc. Para cada pixel se especifica su color.Entonces, el campo
bits_por_pixel indica cu ntos bits representan un pixel en la pantalla.
Si vas leyendo pixel a pixel...
Inmediatamente despu‚s de ambas cabeceras comienza la especificaci¢n de qu‚
componentes de rojo,verde y azul se usar n para cada color. El tama¤o de esta
secci¢n se calcula sabiendo el n£mero de colores y que se utilizan 4 bytes
para especificar cada color;uno para el rojo,otro para el verde y otro para
el azul; el otro no se utiliza, no s‚ por qu‚. Debes usar setpalette para
especificar la paleta a usar.
Dos datos.Los colores est n invertidos en la paleta;primero el azul y al
final el rojo. Los pixels est n en orden inverso;comienzan en la £ltima l¡nea.
*/


#define PALETTE_INDEX       0x03c8
#define PALETTE_DATA        0x03c9

class BMP
{
 protected:

 unsigned char far *bitmap;
 unsigned char far paleta[256*3];

  void fskip(FILE *fp, int n);

 public:

 //CABECERA     			//#bytes
 char tipo[2];         		        //2
 unsigned long tamano;  		//4
 char reservado[4];     		//4
 unsigned long desplazamiento;          //4
				 //Total: 14 bytes

 //INFORMACION DEL BMP		//#bytes
 unsigned long bytes_en_cabecera; //4
 unsigned long ancho;             //4
 unsigned long alto;              //4
 int planos;                      //2
 int bits_por_pixel;              //2
 unsigned long compresion;        //4
 unsigned long tamano_de_imagen;  //4
 unsigned long resolucion_h;      //4
 unsigned long resolucion_v;      //4
 unsigned long n_indices;         //4  retorna el numero de colores de la paleta
 unsigned long n_i_indices;       //4
			 //Total: 40 bytes

 ~BMP();
 int abrir(char *nom);
 void asign_paleta();
 void rotar_paleta();
 void dibujar(VIDEO &video,int x,int y);
 void dibujarppp(int x,int y);
 void pintar();

};

BMP::~BMP()
{
	if (bitmap) farfree(bitmap);
}

int BMP::abrir(char *nom)
{
  FILE *fp;

  if ((fp=fopen(nom,"rb"))==NULL) return 0;

  //LEE LA CABECERA
  fread(&tipo,sizeof(unsigned int), 1, fp);
  fread(&tamano,sizeof(unsigned long), 1, fp);
  fread(&reservado,sizeof(unsigned long), 1, fp);
  fread(&desplazamiento,sizeof(unsigned long), 1, fp);

  //LEE INFO DEL BMP
  fread(&bytes_en_cabecera,sizeof(unsigned long), 1, fp);
  fread(&ancho,sizeof(unsigned long), 1, fp);
  fread(&alto,sizeof(unsigned long), 1, fp);
  fread(&planos,sizeof(unsigned int), 1, fp);
  fread(&bits_por_pixel,sizeof(unsigned int), 1, fp);
  fread(&compresion,sizeof(unsigned long), 1, fp);
  fread(&tamano_de_imagen,sizeof(unsigned long), 1, fp);
  fread(&resolucion_h,sizeof(unsigned long), 1, fp);
  fread(&resolucion_v,sizeof(unsigned long), 1, fp);
  fread(&n_indices,sizeof(unsigned long), 1, fp);
  fread(&n_i_indices,sizeof(unsigned long), 1, fp);

  if (n_indices==0 && bits_por_pixel==8) n_indices=256;


   for(int i=0;i<n_indices;i++)
    {
	paleta[i*3+2] = fgetc(fp) >> 2;
	paleta[i*3+1] = fgetc(fp) >> 2;
	paleta[i*3+0] = fgetc(fp) >> 2;
	fgetc(fp);
    }

     bitmap = (unsigned char far *)
			   farmalloc(sizeof(unsigned char far)*(ancho)*(alto));

      int ex_ancho=(4-ancho%4)%4,k;

       for (int j=alto-1;j>=0;j--)
	 {
	 for(i=0;i<ancho;i++)
	     bitmap[j*ancho+i]=(unsigned char)fgetc(fp);
	 for(k=0;k<ex_ancho;k++)fgetc(fp);
	 }

  fclose(fp);

  return 1;
}

void BMP::asign_paleta()
{
  outp(PALETTE_INDEX,0);

  for (int i=0;i<256*3;i++)
   outp(PALETTE_DATA,paleta[i]);
}

void BMP::rotar_paleta()
{
  int r,g,b;

  r = paleta[3];
  g = paleta[4];
  b = paleta[5];

  for(int i=3;i<256*3-3;i++)
	paleta[i]=paleta[i+3];

  paleta[256*3-3]=r;
  paleta[256*3-2]=g;
  paleta[256*3-1]=b;

  asign_paleta();
}


void BMP::dibujar(VIDEO &video,int x,int y)
{
  unsigned int pos_pantalla = 320*y;//(y<<8)+(y<<6);
  unsigned int indice_bmp = 0;
  unsigned char byte;

  for(int i=0;i<alto;i++)
  {
	for (int j=0;j<ancho;j++)
		{
		 byte=bitmap[indice_bmp];
		 video.vga[pos_pantalla+x+j]=byte;
		 indice_bmp++;
		 }
		 pos_pantalla+=320;
  }

  video.desplegar();
}

//Dibujar pixel por pixel
void BMP::dibujarppp(int x,int y)
{
  for(int i=0;i<alto;i++)
   for (int j=0;j<ancho;j++)
    putpixel(j+x,i+y,bitmap[i*ancho+j]);
}

void main()
{
     BMP bmp;

     VIDEO mivideo; // declara una pantalla de vga

     cout<<"Prueba en 320x200 con 256 colores...";

     getch();

     modo_grafico(0);  // inicia modo grafico 320x200

     bmp.abrir("bella.bmp");    // abre dibujo.bmp

     bmp.asign_paleta();

     bmp.dibujar(mivideo,0,0); //dibuja el bmp en la posicion (0,0)


     getch();

     modo_texto();          // restaura modo texto

     cout<<"Prueba en 640x480 con 256 colores...";
     cout<<"\nSi no ve nada. Puede que su tarjeta de video no soporte este modo.";

     getch();

     modo_grafico(1);  // inicia modo grafico 640x480

     bmp.abrir("bella.bmp");    // abre dibujo.bmp

     bmp.asign_paleta();

     bmp.dibujar(mivideo, 0,0);  //descarga bmp a la memoria de video

     getch();

     bmp.dibujarppp(0,0);        //pinta el bmp pixel por pixel

     getch();

     modo_texto();          // restaura modo texto

}
