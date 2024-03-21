#include <stdio.h>

void main()
{
 FILE *fp;

 if( (fp= fopen( "estrella.txt","rt" ))==NULL )
  {
   printf("Estrella.txt debe estar en la misma carpeta de este programa");
   return;
  }

  char c;

  while( (c=fgetc(fp))!=EOF )
   printf("%c", c );

 fclose( fp );

}