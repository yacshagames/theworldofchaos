/***********************************************************************
 ::: DETECTAR CUALQUIER TECLA DEL TECLADO :::

  Programa que detecta cualqueir tecla presionada en el teclado.
  Esto se hace por medio de la función GetTecla() ( similar a getch()
  de conio.h ) que retorna el codigo de cualquier tecla indididual del
  teclado ( teclas caracteres, extendidas , de control y de bloqueo ).
  Esto incluye a CTRL, ALT, SHIFT, CAPSLOCK, NUMLOCK, etc.

 >> Version 2.0  07-IX-2000
 - Se crea la funcion PresTecla() ( similar a kbhit() de conio.h )
   que detecta si se presiono el codigo de cualquier tecla indididual
   del teclado ( teclas caracteres, extendidas , de control y de bloqueo )
   Retorna un valor diferente de cero si se presiono alguna tecla y 0
   en caso contrario.

 >> Version 1.0  7-VIII-2000
 - Se crea la funcion GetTecla() ( similar a getch() de conio.h )
   que retorna el codigo de cualquier tecla indididual del teclado
   ( teclas caracteres, extendidas , de control y de bloqueo )

 :::Programado por:::
 José Luis De La Cruz Lázaro
 YACSHA - Software & Desing 2002
  >> yacsha@elmundodelcaos.tk    
  >> www.elmundodelcaos.tk -> EL MUNDO DEL CAOS - Unlimited Programming
  >> www.foros3d.tk  -> Foros de discusión  Flash/ActionScript - C/C++

***********************************************************************/

#include <bios.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

//DEFINICION DE TECLAS USASDAS POR GetTecla()

//CARACTERES ESPECIALES
#define _BKSPC 0x8   //BACKSPACE ( tecla Retroceso)
#define _TAB   0x9   //TAB
#define _ENTER 0xD  //ENTER
#define _ESC   0x1B  //ESCAPE
#define _ESP   0x20  //ESPACIO

//TECLAS DE CODIGO EXTENDIDO
#define _ARR  0x4800 //0x48 = 72
#define _ABJ  0x5000
#define _IZQ  0x4B00
#define _DER  0x4D00

#define _INS  0x5200
#define _DEL  0x5300
#define _HOME 0x4700
#define _END  0x4F00
#define _PGUP 0x4900
#define _PGDN 0x5100

#define _F1  0x3B00
#define _F2  0x3C00
#define _F3  0x3D00
#define _F4  0x3E00
#define _F5  0x4F00
#define _F6  0x4000
#define _F7  0x4100
#define _F8  0x4200
#define _F9  0x4300
#define _F10 0x4400

//MASCARAS PARA LAS TECLAS DE CONTROL
#define _LSHIFT  0x2    //SHIFT IZQUIERDO
#define _RSHIFT  0x1	//SHIFT DERECHO

#define _LSHIFT  0x2    //SHIFT IZQUIERDO
#define _RSHIFT  0x1	//SHIFT DERECHO

#define _LCTRL   0x100	//CONTROL IZQUIERDO
#define _RCTRL   0x400	//CONTROL DERECHO
#define _LALT    0x200  //ALT IZQUIERDO
#define _RALT    0x800	//ALT DERECHO

//MASCARAS PARA LAS TECLAS DE BLOQUEO
#define _SCROLL 0x1000 //SCROLL LOCK
#define _NUM    0x2000 //NUM LOCK
#define __CAPS  0x4000 //CAPS LOCK (MASCARA)
#define _CAPS   0x40FF  //CAPS LOCK ( SE DEFINE OTRA CONSTANTE, PORQUE EL
			//VALOR DE SU MASCARA SE CRUZA CON EL VALOR DE F6)

#define _TODASTC 0x7F03 //DEFINE UNA MASCARA COMUN PARA TODAS
			//LAS TECLAS DE CONTROL (ES LA SUMA DE LOS VALORES
			//DE TODAS LAS TECLAS DE CONTROL Y BLOQUEO)


//Retorna el codigo de cualquier tecla indididual del teclado
//( teclas caracteres, extendidas, de control y de bloqueo )
// GetTecla retorna un entero sin signo (unsigned)
// *Si es una tecla de caracter se retorna su ASCII correspondiente
// *Si es una tecla de caracter min£scula se retorna el ASCII de la tecla
//  may£scula
// *Si es una tecla extendida se retorna su codigo extendido en el byte alto
//  y 0 en el byte bajo
// *si es una tecla de control ( ALT, CTRL o SHIFT ) o una tecla de bloqueo
//  (CAPS LOCK, NUM LOCK, etc) se retorna un valor predeterminado cosntante
//  ( ver la definicion de teclas arriba )

unsigned GetTecla()
{
  unsigned tecla;

  for(;;)
  {
   tecla = _bios_keybrd(_NKEYBRD_SHIFTSTATUS);

    //Busca si se presion¢ alguna tecla de control o bloqueo
    if( _LSHIFT & tecla ) return _LSHIFT;
    else if( _RSHIFT & tecla ) return _RSHIFT;
    else if( _LCTRL & tecla ) return _LCTRL;
    else if( _RCTRL & tecla ) return _RCTRL;
    else if( _LALT & tecla ) return _LALT;
    else if( _RALT & tecla ) return _RALT;
    else if( _SCROLL & tecla ) return _SCROLL;
    else if( _NUM & tecla ) return _NUM;
    else if( __CAPS & tecla ) return _CAPS;

    if( bioskey(1) )
    {
     tecla = bioskey(0);

     if( (char)tecla ) //se examina el byte bajo de tecla
      return toupper((char)tecla); //tecla caracter
     else
     return tecla; //tecla extendida
    }

  }

}

int PresTecla()
{
 //busca si se presiono alguna tecla de: caracter, extendida o de control
 if( bioskey(1) || _bios_keybrd(_NKEYBRD_SHIFTSTATUS) & _TODASTC )
  return 1;
 else
  return 0;

}


void GetNombreTecla( char *Nombre, unsigned Tecla )
{

if( Tecla ==_BKSPC ) strcpy(Nombre,"BKSPC" );    //BACKSPACE ( tecla Retroceso)
else if( _TAB   == Tecla) strcpy(Nombre,"TAB");   //TAB
else if( _ENTER == Tecla) strcpy(Nombre,"ENTER");  //ENTER
else if( _ESC   == Tecla) strcpy(Nombre,"ESC");  //ESCAPE
else if( _ESP   == Tecla) strcpy(Nombre,"ESP");  //ESPACIO
//TECLAS DE CODIGO EXTENDIDO
else if( _ARR== Tecla)  strcpy( Nombre,"ARR");
else if( _ABJ== Tecla)  strcpy( Nombre,"ABJ");
else if( _IZQ== Tecla)  strcpy( Nombre,"IZQ");
else if( _DER== Tecla)  strcpy( Nombre,"DER");

else if( _INS== Tecla)  strcpy( Nombre, "INS");
else if( _DEL== Tecla)  strcpy( Nombre, "DEL");
else if( _HOME== Tecla) strcpy( Nombre, "HOME");
else if( _END== Tecla)  strcpy( Nombre, "END");
else if( _PGUP== Tecla) strcpy( Nombre, "PGUP");
else if( _PGDN== Tecla) strcpy( Nombre, "PGDN");

else if( _F1== Tecla)  strcpy( Nombre, "F1");
else if( _F2== Tecla)  strcpy( Nombre, "F2");
else if( _F3== Tecla)  strcpy( Nombre, "F3");
else if( _F4== Tecla)  strcpy( Nombre, "F4");
else if( _F5== Tecla)  strcpy( Nombre, "F5");
else if( _F6== Tecla)  strcpy( Nombre, "F6");
else if( _F7== Tecla)  strcpy( Nombre, "F7");
else if( _F8== Tecla)  strcpy( Nombre, "F8");
else if( _F9== Tecla)  strcpy( Nombre, "F9");
else if( _F10== Tecla) strcpy( Nombre, "F10");

//MASCARAS PARA LAS TECLAS DE CONTROL
else if( _LSHIFT== Tecla)  strcpy( Nombre, "LSHITF");    //SHIFT IZQUIERDO
else if( _RSHIFT== Tecla)  strcpy( Nombre, "RSHITF");	//SHIFT DERECHO
else if( _LCTRL== Tecla)   strcpy( Nombre, "LCTRL"); 	//CONTROL IZQUIERDO
else if( _RCTRL== Tecla)   strcpy( Nombre, "RCTRL"); 	//CONTROL DERECHO
else if( _LALT== Tecla)   strcpy( Nombre, "LALT");   //ALT IZQUIERDO
else if( _RALT== Tecla)    strcpy( Nombre, "RALT"); 	//ALT DERECHO

//MASCARAS PARA LAS TECLAS DE BLOQUEO
else if( _SCROLL== Tecla) strcpy( Nombre, "SCROLL");  //SCROLL LOCK
else if( _NUM== Tecla)    strcpy( Nombre, "NUM");  //NUM LOCK
else if( _CAPS== Tecla)   strcpy( Nombre, "CAPS"); //CAPS LOCK
else if( (char)Tecla ) //se examina el byte bajo de tecla
     sprintf(Nombre, "%c", (char)Tecla); //tecla caracter
}

//FIN DE TECLADO.H
/*************************************************************************/

//Ejemplo del uso de TECLADO.H
#include <iostream.h>

void main(void)
{
  cout<<"Presione cualquier tecla...\n( incluyendo CTRL, ALT, NUMLOCK, etc...): ";

  unsigned tecla;
  char nombretecla[6];

  tecla = GetTecla();
  GetNombreTecla(nombretecla,tecla);
  cout<<"\nUsted Presion¢: "<<nombretecla;
  cout<<"\nC¢digo de Tecla: "<<tecla; //retorna el c¢digo de la tecla pulsada
  cout<<"\n\npresione cualquier tecla para continuar...\n\n";
  GetTecla(); //puede usarse GetTecla similar a getch() es decir puede poner una pausa
}

