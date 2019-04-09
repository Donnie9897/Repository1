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


#define MAX_COL  80
#define MAX_ROW  25

void getfreq(char str[],int freq[]);
void juego(int, int,int);
void imp(char c, int cant, int px, int py, int line);
int freqconsonante(int freq[]);
int freqvocal(int freq[]);
int valor(char letra);

int main()
{

    char letra[CHARS];
    char pal;
    int i = 0,j = 0, espacio = 0;
    int x, y, temp = 0;
    int inicial = 0;
    char temporal[CHARS];
    int longitud = 0;
    int rep[CHARS];
    int win = 0, repet = 0, acertado = 0;
    int oportunidades = 0;
    int freq[MAXABC] = {0};
    int errores,vocal,conso,cantidad;
    int racha = 0,puntos = 0;
    ///juego(1,1,5);
    gotoxy(8,1);printf("Juego del ahorcado ");
    gotoxy(8,3);printf("Ingrese la palabra:");

    cantidad = tomafrase(letra,&espacio);
    getfreq(letra,freq);
    vocal = (float)freqvocal(freq)*0.5;
    conso = (float)(freqconsonante(freq)-vocal)*0.6;
    errores = vocal+conso+1;

    gotoxy(8,6);printf("Cantidad de errores: %d\n",errores);

    gotoxy(8,7);system("pause");



    longitud = 0;
    inicial = 0;
    j = 0;

    rep[0] = ' ';
    rep[1] = '\0';


    do {
        system("cls");
        temp = 0;
        if(inicial == 0)
        {
         for(i=0;i<cantidad;i++)
          {
          if(letra[i] == ' ')
            {
            temporal[i] = ' ';
             longitud++;
             espacio++;
            }
          else
            {
             temporal[i] = '*';
             longitud++;
            }
          }
        }

        inicial = 1;

        temporal[longitud] = '\0';

        for(i=0;i<cantidad;i++)
        {
           if(rep[i] == pal)
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
              temporal[i] = pal;
              acertado++;
              racha += valor(pal);
              puntos+=valor(pal) + racha;
              temp=1;
            }
          }
        }

        if(repet == 0)
        {
         if(temp == 0)
           errores--;
            ///juego(18,1,errores);
        }
        else
        {
         printf("Ya se ha introducido este caracter");
         printf("\n\n");
        }



        printf("\n");

        for(i=0;i<cantidad;i++)
            printf("%c ",temporal[i]);



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


        printf("Introduzca una letra:");
        scanf("\n%c",&pal);

    }while(errores != 0);


    if(win != 0)
    {
        printf("\n\n");
        printf("Felicidades, has ganado.");
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

int tomafrase(char letra[])
{
   int cantidad = 0,i = 0;
   char digi;

   do
    {
        digi = getch();

        if((digi >= 'A' && digi <= 'Z' || digi >= 'a' && digi <= 'z'
          || digi >= '0' && digi <= '9'))
        {
            printf("*");
            cantidad++;
            letra[i] = digi;
            i++;
        }
        if(digi == 32)
        {
            printf(" ");
            letra[i] = digi;
            cantidad++;
            i++;
        }
        if(digi == ENTER)
            break;

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
dibujar el muñequito
averiguar sobre el backspace
averiguar
*/
void imp(char c, int cant, int px, int py, int line)
{

   int i;
   for (i = 0; i < cant; i++)
   {
      if (line)
         gotoxy(px, py++);
      else
         gotoxy(px++, py);
      printf("%c", c);
   }

   return;
}
/*
*/
void juego(int px,int py,int errores)
{
   int x = 25, y,i;
   int col = 0;
   clrscr();



    ///Parte superior
    if(errores <= 3)
    gotoxy(px, py++); printf("%c%c%c%c%c%c",ESPC,ESPC, IQS,HL2, HL2, DQS);
   ///Palo
    if(errores <= 4)
      {gotoxy(x,py++);printf("%c",VL2);
      gotoxy(x,py++);printf("%c",VL2);
      gotoxy(x,py++);printf("%c",VL2);
      gotoxy(x,py++);printf("%c",VL2);
      gotoxy(x,py++);printf("%c",VL2);}
    ///Soga
    if(errores <= 2)
    for(py;py<4;py+2)
    {
        gotoxy(px, py++); printf("%c%c%c%c%c",ESPC,ESPC,VL,ESPC, ESPC);
        gotoxy(px, py++); printf("%c%c%c%c%c",ESPC,ESPC,VL,ESPC, ESPC);
        gotoxy(px, py++); printf("%c%c%c%c%c",ESPC,ESPC,VL,ESPC, ESPC);
    }

    ///Cabeza del muñeco
    if(errores <= 1)
    if(py>3)
    {
    gotoxy(px, py++); printf("%c%c%c%c%c",ESPC, IQS2, HL, DQS2,ESPC);
    gotoxy(px, py++); printf("%c%c%c%c%c",ESPC,IQS2, '_',DQS2,ESPC);
    gotoxy(px, py++); printf("%c%c%c%c%c",ESPC, EII2, HL,EID2, ESPC);
    }
    ///Cuerpo del muñeco
   if(errores <= 0)
    if(py>2)
    {
    gotoxy(px, py++); printf("%c%c%c%c%c",ESPC, DG1, VL,DG2,ESPC);
    gotoxy(px, py++); printf("%c%c%c%c%c",DG1, ESPC, VL, ESPC,DG2);
    gotoxy(px, py++); printf("%c%c%c%c%c",ESPC, DG1, ESPC, DG2,ESPC);
    gotoxy(px, py++); printf("%c%c%c%c%c",DG1, ESPC, ESPC, ESPC,DG2);
    gotoxy(px, py++); printf("%c%c%c%c%c",ESPC, ESPC, ESPC,ESPC,ESPC);
    gotoxy(px, py++); printf("%c%c%c%c%c",ESPC, ESPC, ESPC, ESPC,ESPC);
    }


    ///Piso
    if(errores <= 5)
    gotoxy(px, py++); printf("%c%c%c%c%c%c",HL, HL, HL, HL,HL,HL);
    col = 6;

}



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

