#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <unistd.h>

#define CHARS    80
#define MAXABC   26
#define ENTER    13
#define BACKSPACE 8
#define HL      196
#define HL2     205
#define VL2     186
#define VL      124
#define CUAD    219
#define ESPC     32
#define HEAD      1
#define DG1      47
#define DG2      92
#define DQS2    191
#define DQS     187
#define IQS     201
#define IQS2    218
#define EID     188
#define EID2    217
#define EII     200
#define EII2    192

void getfreq(char [],int []);
void juego(int, int, int);
int freqconsonante(int []);
int freqvocal(int []);
int valor(char );

int main()
{
   char letra[CHARS];
   char pal;
   int i = 0,j = 0, espacio = 0;
   int x, y, temp = 0;
   int inicial = 0;
   char temporal[CHARS]; ///arreglo para la impresi�n de las letras adivinadas.
   int longitud = 0; ///longitud acorde a la palabra.
   int rep[CHARS];
   int win = 0, repet = 0, acertado = 0;
   int oportunidades = 0;
   int freq[MAXABC] = {0};
   int errores,vocal,conso,cantidad;
   int racha = 0,puntos = 0;

   gotoxy(1,1);printf("Juego del ahorcado ");
   gotoxy(1,3);printf("Ingrese la palabra:");

   cantidad = tomafrase(letra,&espacio);
   getfreq(letra,freq);
   vocal = (float)freqvocal(freq)*0.5;
   conso = (float)(freqconsonante(freq)-vocal)*0.6;
   errores = vocal+conso;

   gotoxy(8,6);printf("Cantidad de errores: %d\n",errores);

   gotoxy(8,7);system("pause");


   longitud = 0;
   inicial = 0;
   j = 0;

   rep[0] = ' ';    ///Se organiza el arreglo de repeticiones.
   rep[1] = '\0';


   do {
      system("cls");
      temp = 0;
      if(inicial == 0)
      {
         for(i=0;i<cantidad;i++)
         {
            if(letra[i] == 32) /// por si hay un espacio en la frase
            {
               printf(" ");
               longitud++;
               espacio++;
            }
            else
            {
               temporal[i] = '*'; ///Esto hace que la frase sea desplagada en asteriscos desde un principio
               longitud++;
            }
         }
      }

      inicial = 1; ///Sigue el bucle

      temporal[longitud] = '\0';

      for(i=0;i<cantidad;i++)
      {
         if(rep[i] == pal) ///Aqu� se empieza a verificar si se ha repetido una palabra
         {
            repet = 1;
            break;
         }
         else
         {
            repet = 0;
         }
      }

      if(repet == 0)
      {
         for(i=0;i<cantidad;i++)
         {
            if(letra[i] == pal)
            {
               temporal[i] = pal; ///la letra ingresada se agrega a temporal
               acertado++;
               puntos+=valor(pal) + racha; /// aumenta la racha
               racha += valor(pal);
               temp=1;
            }
         }
      }

      if(repet == 0)
         {
         if(temp == 0)
         {
            errores--; ///Si falla, se restan las oportunidades y se reinicia la racha
            racha = 0;
         }
      }
      else
      {
         gotoxy(1,10);printf("Ya se ha introducido este caracter");
         printf("\n\n");
      }

      juego(1,1,errores);

      printf("\n");

      for(i=0;i<cantidad;i++)
         if (temporal[i]!= 32)
            printf("%c",temporal[i]);

      printf("\n");

      if(acertado == cantidad-espacio)
      {
         win = 1;
         break;
      }

      if(acertado == cantidad)
      {
         win = 1;
         break;
      }

      printf("\nPuntos: %d\nRacha: %d",puntos,racha);
      printf("\n");
      printf("Letras Acertadas: %d",acertado);
      printf("\n");
      printf("Oportunidades Restantes: %d",errores);
      printf("\n");

      rep[j] = pal;
      j++;

      if (errores==0)
         break;


      gotoxy(1,14);printf("Introduzca una letra:");
      scanf("\n%c",&pal); ///Se van capturando las letras que el usuario intenta adivinar

   }while(errores != 0);


   if(win != 0)
   {
      printf("\n\n");
      printf("Felicidades, has ganado.");
      printf("\n\n");
      printf("Has ganado $%d",puntos);
   }
   else
   {
      printf("\n\n");
      printf("Has perdido.");
   }

   printf("\n\n");
   system("PAUSE");

   return 0;
}

/*
Nombre de funci�n: tomafrase.
Objetivo: Permitir que el usuario ingrese una frase para jugar.
Argumentos: (char)    letra.
Retorno: cantidad.
*/

int tomafrase(char letra[])
{
   int cantidad = 0,i = 0;
   char digi;

   do
   {
      digi = getch();

      if(digi == BACKSPACE)
      {
         if (i > 0)
         {
            i--;
            printf("\b \b");
         }


      if (i > 0)
         cantidad--;
      }

      else{
         if((digi >= 'A' && digi <= 'Z' || digi >= 'a' && digi <= 'z'))
         {
            printf("*");
            cantidad++;
            letra[i] = digi;
            i++;
         }
         if(digi == ' ')
         {
            printf(" ");
            letra[i] = digi;
            cantidad++;
            i++;
         }
         if(digi == ENTER)
            break;
         if(digi >= '0' && digi <= '9')
         {
            printf("%c",digi);
            letra[i] = digi;
            cantidad++;
            i++;
         }
      }
   }while(i<CHARS);

return cantidad;
}
void getfreq(char str[],int freq[])
{
   int ind;

   for (ind = 0; str[ind]; ind ++ )
   {
      if ( tolower(str[ind]) >= 'a' && tolower(str[ind]) <= 'z' )
      freq[str[ind] - 'a']++;
   }
return;
}

/*
Nombre de funci�n: juego.
Objetivo: Dibujar el mu�eco del ahorcado.
Argumentos: (int)     px.
       (int)     py.
       (int)     errores.
Retorno: Impresi�n del mu�eco.
*/
void juego(int px,int py,int errores)
{

   int x = 6, y = 1, i;
   float propor = errores/7;


   clrscr();

   ///Palo

   if(propor == errores/6)
      for(y=2;y<10;y++)
      {
         gotoxy(x,y);printf("%c",VL2);
      }

   ///Parte superior

   if(propor == errores/5)
      gotoxy(px, py++); printf("%c%c%c%c%c%c",ESPC,ESPC, IQS,HL2, HL2, DQS);
      gotoxy(1,10);

   ///Soga

   if(propor == errores/4)
   {
      gotoxy(px, py++); printf("%c%c%c%c%c",ESPC,ESPC,VL,ESPC, ESPC);
      gotoxy(px, py++); printf("%c%c%c%c%c",ESPC,ESPC,VL,ESPC, ESPC);
      gotoxy(px, py++); printf("%c%c%c%c%c",ESPC,ESPC,VL,ESPC, ESPC);
   }
   gotoxy(1,10);


   ///Cabeza del mu�eco
   if(propor == errores/3)
   {
      gotoxy(px, py++); printf("%c%c%c%c%c",ESPC, IQS2, HL, DQS2,ESPC);
      gotoxy(px, py++); printf("%c%c%c%c%c",ESPC,IQS2, '_',DQS2,ESPC);
      gotoxy(px, py++); printf("%c%c%c%c%c",ESPC, EII2, HL,EID2, ESPC);
   }
   gotoxy(1,10);

   ///Brazos
   if(propor == errores/2)
   {
      gotoxy(px, py++); printf("%c%c%c%c%c",ESPC, DG1, VL,DG2,ESPC);
      gotoxy(px, py++); printf("%c%c%c%c%c",DG1, ESPC, VL, ESPC,DG2);
   }
   gotoxy(1,10);

   ///Pierna
   if(errores == 0)
   {
      gotoxy(px, py++); printf("%c%c%c%c%c",ESPC, DG1, ESPC, DG2,ESPC);
      gotoxy(px, py++); printf("%c%c%c%c%c",DG1, ESPC, ESPC, ESPC,DG2);
      gotoxy(px, py++); printf("%c%c%c%c%c",ESPC, ESPC, ESPC,ESPC,ESPC);
      gotoxy(px, py++); printf("%c%c%c%c%c",ESPC, ESPC, ESPC, ESPC,ESPC);
   }
   gotoxy(1,12);

}

/*
Nombre de funci�n: freqvocal.
Objetivo: Calcular la frecuencia de las vocales en la frase.
Argumentos: (int)  freq.
Retorno: vocal.
*/

int freqvocal(int freq[])
{
   int ind,vocal = 0;

   for (ind = 0; ind < MAXABC; ind++)
   {
      if(ind == 0 || ind == 4 || ind == 8 || ind == 14 || ind == 20 )
         if(freq[ind])
            vocal++;
   }
   return vocal;
}

/*
Nombre de funci�n: freqconsonante.
Objetivo: Calcular la frecuencia de las letras consonantes.
Argumentos: (int)  freq.
Retorno: (consonante).
*/

int freqconsonante(int freq[])
{
   int ind,consonante = 0;

   for (ind = 0; ind < MAXABC; ind++)
   {
      if(ind != 0 || ind != 4 || ind != 8 || ind != 14 || ind != 20 )
         if(freq[ind])
            consonante++;
   }

   return (consonante);
}

/*
Nombre de funci�n: valor.
Objetivo: Darle el valor del puntaje acorde a la letra adivinada.
Argumentos: (char)     letra.
Retorno: Valor acorde a la letra,para el puntaje.
*/

int valor(char letra)
{
   if(letra == 'a' || letra == 'e' || letra == 'i' || letra == 'o' || letra == 'c' || letra == 's')
      return 10;

   if(letra == 'u' || letra == 'd' || letra == 'l' || letra == 'p' || letra == 'r' )
      return 15;

   if(letra == 'b' || letra == 't' || letra == 'f' || letra == 'm' || letra == 'n')
      return 20;

   if(letra == 'g' || letra == 'h' || letra == 'j' ||letra == 'q' || letra == 'v')
      return 25;

   if(letra == 'k' || letra == 'w' || letra == 'x' || letra == 'y' || letra == 'z')
      return 30;

   else
      return 0;
}
