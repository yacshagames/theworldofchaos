/*******************************************************
RUTINA PARA CREAR UN MENU VIRTUAL EN EL MODO TEXTO
revisado por:
JOSE LUIS DE LA CRUZ LAZARO UNI-FIEE 30 Nov 1999
ramondc@hotmail.com
Pagina Web: http://www.geocities.com/joseluisdl/jldl.htm
*******************************************************/
#ifndef __STDLIB_H
#include <stdlib.h>
#endif

#ifndef __CONIO_H
#include <conio.h>
#endif

#ifndef __STDIO_H
#include <stdio.h>
#endif

#ifndef __BIOS_H
#include <bios.h>
#endif

/*
int  MENU  (char *vec[],int,int,int,int,int);
void CUADRO(int,int,int,int,int);
//////////
void main (void)
{
 char *mnuppal[6]={"OPCION1","OPCION2","Salir H.A 31173"}; //inicializacion del menu
 int con=0,opc; //definicion de variables
 clrscr();
 while(con !=1)
 {
  CUADRO(30,10,20,7,9);
  opc=MENU(mnuppal,32,11,3,-1,15);//mnuppal
  clrscr();gotoxy(1,1);
  switch(opc)
  {
   case -1:cprintf("Se preciono ESC"); break;
   case  0:cprintf("Se preciono OPCION 1 uno uno uuuu nnn ooo");break;
   case  1:cprintf("Se preciono OPCION 2 ###!!!&&&");break;
   case  2:cprintf("Se preciono Salir jejeje");
	   con=1;getch(); break;
   default:break;
  }

 }
}
///////////////////////////////
*/

int MENU (char *vec[],int x,int y,int dim,int puntero,int col)
{
 /*Esta funcion resive unvector tipo caracter
   definido de la siguiente manera
   char *nomvec[dim]={"OPC1","OPC2","OPC3"..... ,"OPCn"};
   necesita las siguientes librerias:
   #include <conio.h>
   #include <stdio.h>
   #include <bios.h>
   ejemplo de como se envia
   opc=MENU(10,10,nomvec,dim);
   puntero= opcion por defecto donde aparecera el puntero
 */
 textcolor(col);
 int con=0,con_ant=0,sal=0;
 if (dim >=1 && x>=2 && y+(dim-1)<=24)
 {
  for(int k=0;k<dim;k++)
  {
   gotoxy(x,y+k);cprintf("%s",vec[k]);
  }
  if(puntero!=-1 && puntero<dim){con=puntero;}

  while(sal != 1)
  {
   gotoxy(x-1,y+con);cprintf(">");

    textcolor(col);
    gotoxy(x,y+con_ant);cprintf("%s",vec[con_ant]);
    textcolor(LIGHTGREEN);
    gotoxy(x,y+con);cprintf("%s",vec[con]);
    con_ant=con;

   while(bioskey(1)==0);
   gotoxy(x-1,y+con);cprintf(" ");
   switch(bioskey(0))
   {
    case 0x11b :sal=1;con=-1;break;//ESC
    case 0x1c0d:sal=1;break;//ENTER
    case 0x4800:
    con--;
    if(con < 0)con=(dim-1);

    break;//Fle. Arriba
    case 0x5000:con++;if(con > (dim-1))con=0;break;//Fle. Abajo
   }
   if( kbhit() ) getch();
  }

  return(con);
 }
 else
 {
  printf("El menu no tiene la dimension correcta o se salio de la pantalla");
  getche();
  return(con=-1);
 }
}
///
void CUADRO(int x1,int y1,int ancho,int largo,int col)
{
 /*necesita
  #include <conio.h>
  #include <stdio.h>
 */
 if(x1 >= 0 && y1>=0 && (x1+ancho)<=70 && (y1+largo)<=25)
 {
  textcolor(col);
  for(int i=x1+1;i<=x1+ancho-1;i++)
  {
   gotoxy(i,y1);cprintf("Í");
   gotoxy(i,y1+largo);cprintf("Í");
  }
  for(int k=y1+1;k<=y1+largo-1;k++)
  {
   gotoxy(x1,k);cprintf("º");
   gotoxy(x1+ancho,k);cprintf("º");
  }
  gotoxy(x1,y1);cprintf("É");
  gotoxy(x1,y1+largo);cprintf("È");
  gotoxy(x1+ancho,y1+largo);cprintf("¼");
  gotoxy(x1+ancho,y1);cprintf("»");
 }
 else
 {
  gotoxy(x1,y1);cprintf("Cuadro fuera de pantalla");getch();
 }
}

