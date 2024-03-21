/*
NIBBLES 5.6 13/06/98

Idea original de Microsoft.

Programado en C++ por JOSE LUIS DE LA CRUZ LAZARO UNI-FIEE
*/

#include <iostream.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include <graphics.h>
#include <math.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
//Funcion linea_var; modificacion de la funcion  sys_var
char *linea_var(char *cad,char *VAR1,char *VAR2)
{
char *p,*q;
char linea[115]="";
p=strchr(cad,'%');
strncpy(linea,cad,strlen(cad)-strlen(p));
strcat(linea,VAR1);
p=p+2;
q=strrchr(cad,'%');
strncat(linea,p,strlen(p)-strlen(q));
strcat(linea,VAR2);
q=q+2;
strcat(linea,q);
return linea;
}

main()
{

//ENTRADA DE DATOS DEL JUGADOR:

//Menu Principal
Menu:

clrscr();
int opcion,Jubi_Player=0,Editor=0,Cargar=0;
int cambio_de_fase=1,Editar_fase=0;
for(int bb=1;bb<=60;bb+=10){
gotoxy(bb,15+bb/10);cout<<"<<JLDL Software--UNI-FIEE>>";}
gotoxy(1,1);
cout<<"\07\n\n\t\t ~~~~~~~~~~~~NIBLES VERSION XX_____________";
cout<<"\n\n";
cout<<"\n\t\t\t (1) 1 JUGADOR";
cout<<"\n\t\t\t (2) 2 JUGADORES";
cout<<"\n\t\t\t (3) 3 JUGADORES";
cout<<"\n\t\t\t (4) CREAR UNA FASE";
cout<<"\n\t\t\t (5) EDITAR UNA FASE CREADA";
cout<<"\n\t\t\t (6) SALIR";
cout<<"\n\n";
cout<<"\t\t\tSeleccione una opci¢n :";
cin>>opcion;

switch(opcion){

case 1:	Jubi_Player=1;break;
case 2: Jubi_Player=2;break;
case 3: Jubi_Player=3;break;
case 4:	Editor=1;break;
case 5:	Editor=1,Editar_fase=1;cambio_de_fase=0;break;
case 6: exit(0);break;
default: goto Menu;
}

//Escala de velocidad del juego
Escala:

int escala_velocidad=88;

if(Jubi_Player!=0){
clrscr();
gotoxy(20,11);
cout  	<<"Su velocidad debe estar entre 1 y 100"
	<<"\n\n\t\t\tBEBES   : (de 1 a 69)"
	<<"\n\n\t\t\tNORMALES: (de 70 a 89)"
	<<"\n\n\t\t\tRAYADOS : (m s 90)";

gotoxy(20,8);
cout<<"Ingrese su Velocidad : ";
cin>>escala_velocidad;
if(escala_velocidad<1||escala_velocidad>100)goto Escala;
}//fin de escala


//FIN DE ENTRADA DE DATOS DEL JUGADOR

int gd=DETECT,gm;
initgraph(&gd,&gm,"");

int N=0;//Declaracion de variable N para cambio de fase
	//Se utiliza en el bucle de "NIVELES DE JUEGO"

int puntaje_1=0,puntaje_2=0,puntaje_3=0;//Declaracion de las variables de puntaje

inicio:
cleardevice();
//setbkcolor(1);

int unid_div=(getmaxx()+1)/64;//getmaxx()+1=Maxima resolucion en pixeles del eje X
			      //La resolucion mas usada es 640*480
			      //Luego getmaxx()=639, getmaxy()=479

int x_cola[55]={0},y_cola[55]={0},i=0,k=0;
int x=36*unid_div,y=26*unid_div,perdiste_1=0,x_ant,y_ant,longitud_cola1=1;

int xx_cola[55]={0},yy_cola[55]={0},ii=0,kk=0;
int xx=28*unid_div,yy=25*unid_div,perdiste_2=0,xx_ant,yy_ant,longitud_cola2=1;

int xxx_cola[55]={0},yyy_cola[55]={0},iii=0,kkk=0;
int xxx=30*unid_div,yyy=23*unid_div,perdiste_3=0,xxx_ant,yyy_ant,longitud_cola3=1;


int captura_numero=1,X,Y,color_detect=7;
int n=1,nn=1,nnn=1,num=1;

char tecla=1;
char flecha2=77,flecha2_ant=77,flecha1='A',flecha1_ant='A';//flecha2_ANT;
char flecha3='K',flecha3_ant='K';


//BUCLE DE NIVELES DEL JUEGO (FASES):
if(cambio_de_fase){
N++;
Editar_fase=0;Cargar=1;cambio_de_fase=0;}else Cargar=1;


//BUCLE CARGAR UN JUEGO:

if(Cargar){
	//BUCLE DE LECTURA DE UNA FASE YA ESCRITA:
	int leer,I,J,K,px,py;
	char *p,*nombre;

	int direccion[6],z=0,color;

	cleardevice();

	if(Editar_fase){
	cout<<"\n\n\n\n\t\tIngrese el nombre de la fase que desea editar: ";
	cin>>nombre;}else{

	char *numero=" ",digito;
	digito=char(48+N);
	*numero=digito;

	strcpy(nombre,linea_var("%1_%2","fase",numero));}


	leer=open(linea_var("%1.%2",nombre,"nib"),0);

	cleardevice();

	gotoxy(27,12);
	if(leer==-1){closegraph();clrscr();gotoxy(26,12);cout<<"Error al cargar la fase!!!";getch();goto Menu;}

	for(J=30;J<getmaxy()+1;J+=unid_div){
	K=0;
	read(leer,p,64);

	for(I=0;I<getmaxx()+1;I+=unid_div,K++)
	       {
		color=int(*(p+K))-48;
	       switch(color){
	       case 14:	x=I;y=J;color=0;break;
	       case 5:	xx=I;yy=J;color=0;break;
	       case 2:	xxx=I;yyy=J;color=0;break;
	       case 7:	direccion[z]=I;z++;direccion[z]=J;z++;color=0;break;}


	       setfillstyle(1,color);//Estilo:solido, color:negro o rojo
		bar(I,J,I+unid_div-1,J+unid_div-1);}

	}//fin del for
close(leer);

for(z=0;z<6;z+=2){

switch(x-direccion[z]){

case -10:flecha2=75;break;
case 10:flecha2=77;break;

case 0:switch(y-direccion[z+1]){

	case -10:flecha2=72;break;
	case 10:flecha2=80;break; };break;}

switch(xx-direccion[z]){

case -10:flecha1='A';break;
case 10:flecha1='D';break;

case 0:switch(yy-direccion[z+1]){

	case -10:flecha1='W';break;
	case 10:flecha1='S';break; };break;}

switch(xxx-direccion[z]){

case -10:flecha3='K';break;
case 10:flecha3=';';break;

case 0:switch(yyy-direccion[z+1]){

	case -10:flecha3='O';break;
	case 10:flecha3='L';break; };break;}

flecha1_ant=flecha1;
flecha2_ant=flecha2;
flecha3_ant=flecha3;

}//fin del for

//FIN DE LA LECTURA

}//fin del if Cargar


//EDITOR DE UNA FASE:

if(Editor){
	int color=14,color_ant=0,pintar=0,px=x,py=y,px_ant,py_ant;

	do{

	moveto(px,py);
	gotoxy(1,1);cout<<getx()<<","<<gety()<<"  ";
	gotoxy(58,1);cout<<"Color Activo: ";

	switch(color){
	case 0:	gotoxy(72,1);cout<<"NEGRO";break;
	case 4:	gotoxy(72,1);cout<<"ROJO ";break;
	}

	px_ant=px;
	py_ant=py;

	flecha1=toupper(getch());
	if(flecha1==0){
	flecha2=toupper(getch());

	switch(flecha2){

		case 72:py-=unid_div;break; //ARRIBA

		case 80:py+=unid_div;break; //ABAJO

		case 75:px-=unid_div;break; //IZQUIERDA

		case 77:px+=unid_div;break; //DERECHA
		}
	}

	switch(flecha1){
	case '`':pintar=0;break;
	case '1':color=0;pintar=1;break;//tecla '1':color negro
	case '2':color=4;pintar=1;break;//tecla '2':color rojo
	case '3':color=14;pintar=1;break;//tecla '3':color amarillo
	case '4':color=5;pintar=1;break;//tecla '4':color morado
	case '5':color=2;pintar=1;break;//tecla '5':color verde
	case '6':color=7;pintar=1;break;//tecla '6':color ligthgray

	}

	if(pintar){

	setfillstyle(1,color);//Estilo:solido, color:negro o rojo
	bar(px,py,px+unid_div-1,py+unid_div-1);

	}else{
	//Borrador transparente

	setfillstyle(1,color_ant);//Estilo:solido, color:transparente
	bar(px_ant,py_ant,px_ant+unid_div-1,py_ant+unid_div-1);

	color_ant=getpixel(px,py);

	setfillstyle(1,7);//Estilo:solido, color:negro o rojo
	bar(px,py,px+unid_div-1,py+unid_div-1);}


	}while(flecha1!=13);

	//BUCLE PARA ESCRITURA DE UNA FASE(NIVEL) DEL JUEGO:

	int I,J,K,escribir;
	char *p,numero[64],*nombre;

	escribir=creat("fase_00.nib",0);

	for(J=30;J<getmaxy()+1;J+=unid_div){
	K=0;

	for(I=0;I<getmaxx()+1;I+=unid_div,K++)
		numero[K]=char(48+getpixel(I,J));

	p=numero;

	write(escribir,p,64);}

	close(escribir);

	cleardevice();

	closegraph();

	cout<<"\n\n¨ Desea grabar su nueva fase ?";
	cout<<"\n\n\n\t\tPresione ESC para Salir\n\t\t\to cualquier tecla para continuar...\n\n";
	tecla=getch();
	if(tecla==27){
	system("del fase_00.nib");
	goto Menu;}
	tecla=1;

	cout<<"\n\n\n\t\tIngrese un nombre para la fase :";
	cin>>nombre;

	system(linea_var("ren fase_00.nib %1.%2",nombre,"nib"));

	//FIN DE ESCRITURA

}//fin del if Editor

int tm,tm_ant=clock();
float t,velocidad;
velocidad=(0.01-0.5)/(100-1)*(escala_velocidad-1)+0.5;
t=velocidad;	//Ajuste de la velocidad en una recta cuyo dominio
		//es [1,100] (escala_velocidad) y cuyo rango
		//es [0.01,0.5] (velocidad)
		//(la recta es de pendiente negativa)

time_t segundos;
time(&segundos);
srand(segundos%62536);

if(Jubi_Player==1)        //Bucle para cancelar movimientos de Jubi_Player2
{flecha1=0;flecha1_ant=0;//y Jubi_Player3 cuando solo juega Jubi_Player1
 flecha3=0;flecha3_ant=0;}

if(Jubi_Player==2)        //Bucle para cancelar movimientos de Jubi_Player3
{flecha3=0;flecha3_ant=0;}//cuando juega Jubi_Player1 con Jubi_Player2

gotoxy(27,1);cout<<"JubiPlayer 2: "<<puntaje_2;
gotoxy(60,1);cout<<"JubiPlayer 3: "<<puntaje_3;

//Puntaje del Jubiplayer2
X=x+5;Y=y+5;
puntaje_1=puntaje_1-(abs(X-325)/10+abs(Y-205)/10);


//BUCLE PRINCIPAL:
//Se ejecuta si Jubi_Player diferente de 0

while(tecla!=27&&Jubi_Player!=0){
do{

x_ant=x;
y_ant=y;

xx_ant=xx;
yy_ant=yy;

xxx_ant=xxx;
yyy_ant=yyy;

//Bucle que detiene el bucle MUERTE SEGURA

if(color_detect==7){
perdiste_1=0;perdiste_2=0;perdiste_3=0;}  //si el color delante de nible es 7 (lightgray)

//RECOLECCION DE NUMERO, NIBBLE1, NIBLE2:

if((X==x+5&&Y==y+5)||(X==xx+5&&Y==yy+5)||(X==xxx+5&&Y==yyy+5)){//Se ejecuta al empezar por inicio:
captura_numero=1;                        //y cuando se atrapa un #
if(X==x+5&&Y==y+5){
n=num;
puntaje_1=puntaje_1+abs(X-325)/10+abs(Y-205)/10;
		//Formula para el puntaje de Jubi_Player1
gotoxy(2,1);cout<<"JubiPlayer 1: "<<puntaje_1;
}else{

if(X==xx+5&&Y==yy+5){
nn=num;
puntaje_2=puntaje_2+abs(X-325)/10+abs(Y-205)/10;
		//Formula para el puntaje de Jubi_Player1
gotoxy(27,1);cout<<"JubiPlayer 2: "<<puntaje_2;
}else{
nnn=num;
puntaje_3=puntaje_3+abs(X-325)/10+abs(Y-205)/10;
		//Formula para el puntaje de Jubi_Player1
gotoxy(60,1);cout<<"JubiPlayer 3: "<<puntaje_3;
}

}

//borrar numero anterior
//setfillstyle(1,0);//Estilo:solido, color:negro
//bar(X-5,Y-5,X+5,Y+5);
color_detect=0;
}else captura_numero=0;

//MUERTE SEGURA NIBBLE1:

if(flecha2==flecha2_ant&&perdiste_1)		//Si bucle es verdadero
{						//Muerte Segura
setcolor(0);//color de letra
setfillstyle(1,14); //estilo:solido, color:amarillo
bar(getmaxx()/2-5*unid_div , getmaxy()/2-3*unid_div , getmaxx()/2+5*unid_div,getmaxy()/2+3*unid_div);
settextjustify(1,1);	//justificacion centrada
outtextxy(getmaxx()/2 , getmaxy()/2-10 ,"MUERE!!!");	     //Mensaje de Muerte
outtextxy(getmaxx()/2 , getmaxy()/2+10 ,"JubiPlayer 1");	     //Mensaje de Muerte

getch();
goto inicio;

}else
perdiste_1=0;//El jugador1 se salvo por un pelo

//MUERTE SEGURA NIBBLE2:

if(flecha1==flecha1_ant&&perdiste_2)		//Si bucle es verdadero
{						//Muerte Segura
setcolor(0);//color de letra
setfillstyle(1,5); //estilo:solido, color:morado
bar(getmaxx()/2-5*unid_div , getmaxy()/2-3*unid_div , getmaxx()/2+5*unid_div,getmaxy()/2+3*unid_div);
settextjustify(1,1);	//justificacion centrada
outtextxy(getmaxx()/2 , getmaxy()/2-10 ,"MUERE!!!");	     //Mensaje de Muerte
outtextxy(getmaxx()/2 , getmaxy()/2+10 ,"JubiPlayer 2");	     //Mensaje de Muerte

getch();
goto inicio;

}else
perdiste_2=0;//El jugador2 se salvo por un pelo

if(flecha3==flecha3_ant&&perdiste_3)		//Si bucle es verdadero
{						//Muerte Segura
setcolor(0);//color de letra
setfillstyle(1,2); //estilo:solido, color:verde
bar(getmaxx()/2-5*unid_div , getmaxy()/2-3*unid_div , getmaxx()/2+5*unid_div,getmaxy()/2+3*unid_div);
settextjustify(1,1);	//justificacion centrada
outtextxy(getmaxx()/2 , getmaxy()/2-10 ,"MUERE!!!");	     //Mensaje de Muerte
outtextxy(getmaxx()/2 , getmaxy()/2+10 ,"JubiPlayer 3");	     //Mensaje de Muerte

getch();
goto inicio;

}else
perdiste_3=0;//El jugador3 se salvo por un pelo


if(abs(flecha2_ant-flecha2)==8||abs(flecha2_ant-flecha2)==2)//Bucle para
flecha2=flecha2_ant;//impedir que el nibble Ü se dirija al lado opuesto al que se esta avanzando

switch(flecha2){

	case 72:y-=unid_div;    //ARRIBA
		if(getpixel(x+5,y-1)!=0){
		perdiste_1=1;
		color_detect=getpixel(x+5,y-1);}break;

	case 80:y+=unid_div; //ABAJO
		if(getpixel(x+5,y+1+unid_div)!=0){
		perdiste_1=1;
		color_detect=getpixel(x+5,y+1+unid_div);}break;

	case 75:x-=unid_div; //IZQUIERDA
		if(getpixel(x-1,y+5)!=0){
		perdiste_1=1;
		color_detect=getpixel(x-1,y+5);}break;

	case 77:x+=unid_div; //DERECHA
		if(getpixel(x+1+unid_div,y+5)!=0){
		perdiste_1=1;
		color_detect=getpixel(x+1+unid_div,y+5);}break;
}

if(abs(flecha1_ant-flecha1)==int('W'-'S')||abs(flecha1_ant-flecha1)==int('D'-'A'))//Bucle para
flecha1=flecha1_ant;//impedir que el nibble Ü se dirija al lado opuesto al que se esta avanzando

switch(flecha1){
	case 'W':yy-=unid_div;    //ARRIBA
		if(getpixel(xx+5,yy-1)!=0){
		perdiste_2=1;
		color_detect=getpixel(xx+5,yy-1);}break;

	case 'S':yy+=unid_div; //ABAJO
		if(getpixel(xx+5,yy+1+unid_div)!=0){
		perdiste_2=1;
		color_detect=getpixel(xx+5,yy+1+unid_div);}break;

	case 'A':xx-=unid_div; //IZQUIERDA
		if(getpixel(xx-1,yy+5)!=0){
		perdiste_2=1;
		color_detect=getpixel(xx-1,yy+5);}break;

	case 'D':xx+=unid_div; //DERECHA
		if(getpixel(xx+1+unid_div,yy+5)!=0){
		perdiste_2=1;
		color_detect=getpixel(xx+1+unid_div,yy+5);}break;

}

//AQUI SE CAMBIA PARA OTRO PLAYER
if(flecha3=='I')flecha3=0;         //Este bucle impide que cuando se presione
if(flecha3_ant=='I')flecha3_ant=0;//la tecla I, no se pueda mover el nible

if(abs(flecha3_ant-flecha3)==int('O'-'L')||abs(flecha3_ant-flecha3)==int('K'-';'))//Bucle para
flecha3=flecha3_ant;//impedir que el nibble Ü se dirija al lado opuesto al que se esta avanzando

switch(flecha3){
	case 'O':yyy-=unid_div;    //ARRIBA
		if(getpixel(xxx+5,yyy-1)!=0){
		perdiste_3=1;
		color_detect=getpixel(xxx+5,yyy-1);}break;

	case 'L':yyy+=unid_div; //ABAJO
		if(getpixel(xxx+5,yyy+1+unid_div)!=0){
		perdiste_3=1;
		color_detect=getpixel(xxx+5,yyy+1+unid_div);}break;

	case 'K':xxx-=unid_div; //IZQUIERDA
		if(getpixel(xxx-1,yyy+5)!=0){
		perdiste_3=1;
		color_detect=getpixel(xxx-1,yyy+5);}break;

	case ';':xxx+=unid_div; //DERECHA
		if(getpixel(xxx+1+unid_div,yyy+5)!=0){
		perdiste_3=1;
		color_detect=getpixel(xxx+1+unid_div,yyy+5);}break;

}

flecha2_ant=flecha2;

//"LO QUE SE VE EN PANTALLA":


//APARECER UN NUMERO ALEATORIAMENTE EN PANTALLA:

if(captura_numero){

int num_aleatorio;

num_aleatorio=random(20)+1;
X=15+num_aleatorio*3*unid_div;

num_aleatorio=random(13)+1;
Y=55+num_aleatorio*3*unid_div;

num_aleatorio=random(3)+1;//genera numero aleatorio entero en el intervalo [1,4]

if(num_aleatorio==1){

num_aleatorio=random(3)+1;//genera numero aleatorio entero en el intervalo [1,4]

switch(num_aleatorio){

case 1: X=15;break;

case 2:	X=625;break;

case 3:	Y=65;break;

case 4:	Y=465;break;
}//fin del switch

}
char *numero=" ",digito;
digito=char(48+num);
*numero=digito;

if(num==10){cambio_de_fase=1;goto inicio;}//Bucle para cambiar de fase
				    //cuando se llega al numero 9
setcolor(7);
outtextxy(X,Y,numero);

num++;
}
//FIN DE APARECER UN NUMERO

//(1)NIBBLE1:
//Muestra la posicion actual del nibble
//Se muestra en pantalla como una serpiente infinita

setfillstyle(1,14);//Estilo:solido, color:amarillo
bar(x,y,x+unid_div-1,y+unid_div-1);

//Fin de (1)

//(2)NIBLE1:
//Bucle que situa un borrador en la posicion final de la cola
//Este bucle carga(muestra cola) y descarga(borra cola) en
//un proceso en serie

//x_cola[], y_cola[] : posicion de la cola del nible 1

if(k==55)k=0;//CARGA utiliza parte ya usada  de la cadena x_cola[], y_cola[]

x_cola[k]=x_ant;    //bucle de
y_cola[k]=y_ant;    //CARGA
k++;


//Bucle que desfasa la carga y la descarga en "((n+2)*(n+1))/2" unidades


if(longitud_cola1==((n+2)*(n+1))/2)//bucle que se ejecuta solo en la DESCARGA
{

//Sentencia: borrador

if(i==55)i=0;//DESCARGA utiliza parte ya usada de la cadena x_cola[], y_cola[]

int a=x_cola[i],b=y_cola[i];
setfillstyle(1,0);//Estilo:solido, color:negro
bar(a,b,a+unid_div-1,b+unid_div-1);
i++;
//Fin de sentencia borrador

}else{			//bucle que se ejecuta solo en la CARGA
longitud_cola1++;}  	//y en la DESCARGA no se ejecuta
//Fin del bucle desfasa

//Fin de (2)


if(Jubi_Player>=2){
	//(1)NIBBLE2:
	//Muestra la posicion actual del nibble
	//Se muestra en pantalla como una serpiente infinita

	setfillstyle(1,5);//Estilo:solido, color:morado
	bar(xx,yy,xx+unid_div-1,yy+unid_div-1);

	//Fin de (1)

	//(2)
	//Bucle que situa un borrador en la posicion final de la cola
	//Este bucle carga(muestra cola) y descarga(borra cola) en
	//un proceso en serie

	//xx_cola[], yy_cola[] : posicion de la cola del nible 2

	if(kk==55)kk=0;//CARGA utiliza parte ya usada  de la cadena xx_cola[], y_cola[]

	xx_cola[kk]=xx_ant;    //bucle de
	yy_cola[kk]=yy_ant;    //CARGA
	kk++;


	//Bucle que desfasa la carga y la descarga en "((n+2)*(n+1))/2" unidades


	if(longitud_cola2==((nn+2)*(nn+1))/2)//bucle que se ejecuta solo en la DESCARGA
	{

	//Sentencia: borrador

	if(ii==55)ii=0;//DESCARGA utiliza parte ya usada de la cadena xx_cola[], y_cola[]

	int aa=xx_cola[ii],bb=yy_cola[ii];
	setfillstyle(1,0);//Estilo:solido, color:negro
	bar(aa,bb,aa+unid_div-1,bb+unid_div-1);
	ii++;
	//Fin de sentencia borrador

	}else{			//bucle que se ejecuta solo en la CARGA
	longitud_cola2++;}  	//y en la DESCARGA no se ejecuta
	//Fin del bucle desfasa

	//Fin de (2)
	//FIN DE NIBBLE2
}//Fin del if Jubi_player


if(Jubi_Player==3){
		//(1)NIBBLE2:
		//Muestra la posicion actual del nibbble
		//Se muestra en pantalla como una serpiente infinita

		setfillstyle(1,2);//Estilo:solido, color:verde
		bar(xxx,yyy,xxx+unid_div-1,yyy+unid_div-1);

		//Fin de (1)

		//(2)
		//Bucle que situa un borrador en la posicion final de la cola
		//Este bucle carga(muestra cola) y descarga(borra cola) en
		//un proceso en serie

		//xxx_cola[], yyy_cola[] : posicion de la cola del nible 3

		if(kkk==55)kkk=0;//CARGA utiliza parte ya usada  de la cadena xxx_cola[], y_cola[]

		xxx_cola[kkk]=xxx_ant;    //bucle de
		yyy_cola[kkk]=yyy_ant;    //CARGA
		kkk++;


		//Bucle que desfasa la carga y la descarga en "((n+2)*(n+1))/2" unidades


		if(longitud_cola3==((nnn+2)*(nnn+1))/2)//bucle que se ejecuta solo en la DESCARGA
		{

		//Sentencia: borrador

		if(iii==55)iii=0;//DESCARGA utiliza parte ya usada de la cadena xxx_cola[], y_cola[]

		int aaa=xxx_cola[iii],bbb=yyy_cola[iii];
		setfillstyle(1,0);//Estilo:solido, color:negro
		bar(aaa,bbb,aaa+unid_div-1,bbb+unid_div-1);
		iii++;
		//Fin de sentencia borrador

		}else{			//bucle que se ejecuta solo en la CARGA
		longitud_cola3++;}  	//y en la DESCARGA no se ejecuta
		//Fin del bucle desfasa

		//Fin de (2)
		//FIN DE NIBBLE2
}//Fin del if Jubi_player

//Fin de LO QUE SE VE EN PANTALLA

//CONGELA TIEMPO PARA UNA REACCION DEL JUGADOR:
//Bucle que paraliza un tiempo predeterminado el juego
//Este bucle sirve para reaccionar a "LO QUE SE VE EN PANTALLA"
do{
tm=clock()-tm_ant;
}while(tm/CLK_TCK<t);
t+=velocidad;
//Fin del bucle de CONGELA TIEMPO PARA UNA REACCION DEL JUGADOR

flecha1_ant=flecha1;
flecha3_ant=flecha3;

}while(!kbhit());

tecla=toupper(getch());

if(tecla==0){
flecha2=toupper(getch());
flecha1=flecha1_ant;
flecha3=flecha3_ant;}

if((tecla=='W'||tecla=='S'||tecla=='A'||tecla=='D'||tecla=='Q')&&Jubi_Player>=2){
flecha1=tecla;}

if((tecla=='O'||tecla=='L'||tecla=='K'||tecla==';'||tecla=='I')&&Jubi_Player==3){
flecha3=tecla;}

}//fin del while principal

closegraph();

goto Menu;
}