/*******************************************/
/* Solucionada por:                        */
/* Copyright (C) 2000 por David A. Capello */
/*******************************************/

#include <dos.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void borrar_pantalla()
{
  union REGS regs;

  regs.h.ah = 0x06;
  regs.h.al = 25; /* number of lines to scroll */
  regs.h.bh = 7; /* attribute to be used on blank line */
  regs.h.ch = 0; /* row of upper left corner of scroll window */
  regs.h.cl = 0; /* column of upper left corner of scroll window */
  regs.h.dh = 24; /* row of lower right corner of scroll window */
  regs.h.dl = 79; /* column of lower right corner of scroll window */

  int86(0x10, &regs, &regs);
}



/* X, Y son igual como en el gotoxy (comienzan del punto 1,1) */
void imprimir_caracter(char chr, int x, int y, int repeticiones)
{
  union REGS regs;

  x--;
  y--;

  if ((x>=0) && (y>=0) && (x<80) && (y<25)) {
    /* cambiar la posici¢n del cursor */

    regs.h.ah = 0x02;
    regs.h.bh = 0; /* page number */
    /* positions relative to 0,0 origin */
    regs.h.dh = y; /* row */
    regs.h.dl = x; /* column */

    int86(0x10, &regs, &regs);

    /* escribir el texto en la posici¢n indicada anteriormente */
    regs.h.ah = 0x09;
    regs.h.al = chr; /* ASCII character to write */
    regs.h.bh = 0; /* display page */
    regs.h.bl = 7; /* character attribute */
    regs.x.cx = repeticiones; /* count of characters to write */

    int86(0x10, &regs, &regs);
  }
}



/* ver `imprimir_caracter' para m s informaci¢n sobre X, Y */
void imprimir_cadena(char *str, int x, int y)
{
  int i;

  for (i=0; str[i]; i++)
    imprimir_caracter(str[i], x++, y, 1);
}



void dibujar(void)
{
  char *msg[] = { "El\0", "Lenguaje\0", "C++\0", "­­­Es\0", "el\0", "Mejor!!!\0",
                  "ESC: Salir\0", "ESPACIO:Repetir...\0" };
  long i, j;

  borrar_pantalla();

  /* primer animaci¢n */
  for (i=0; i<=1000; i++) {
    j = 12 - 12 * i / 1000;
    imprimir_caracter(' ', 40, 12-j-1, strlen(msg[0]));
    imprimir_cadena(msg[0], 40, 12-j);

    j = 34 - 34 * i / 1000;
    imprimir_caracter(' ', 34-j-1, 13, 1);
    imprimir_cadena(msg[1], 34-j, 13);

    j = 46 - 46 * i / 1000;
    imprimir_caracter(' ', 46+j+strlen(msg[2]), 13, 1);
    imprimir_cadena(msg[2], 46+j, 13);
  }

  /* segunda animaci¢n */
  for (i=0; i<=1000; i++) {
    j = 31 - 31 * i / 1000;
    imprimir_caracter(' ', 31-j-1, 14, 1);
    imprimir_cadena(msg[3], 31-j, 14);

    j = 14 - 14 * i / 1000;
    imprimir_caracter(' ', 40, 14+j+1, strlen(msg[4]));
    imprimir_cadena(msg[4], 40, 14+j);

    j = 49 - 49 * i / 1000;
    imprimir_caracter(' ', 49+j+strlen(msg[5]), 14, 1);
    imprimir_cadena(msg[5], 49+j, 14);
  }

  imprimir_cadena(msg[6], 10, 25);
  imprimir_cadena(msg[7], 52, 25);
}



int obtener_tecla()
{
  union REGS regs;

  regs.h.ah = 0x00;

  int86(0x16, &regs, &regs);

  return regs.h.al;
}



int main(void)
{
  int tecla = ' ';

  /* ESC (27), para el programa */
  while (tecla != 27) {
    /* ESPACIO (32), dibuja la pantalla */
    if (tecla == ' ')
      dibujar();

    tecla = obtener_tecla();
  }

  return 0;
}





