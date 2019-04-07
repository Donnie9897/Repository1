#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <unistd.h>

#define CHARS    80
#define ABC      26
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
#define DQS2     191
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
void juego(void);
void imp(char c, int cant, int px, int py, int line);
float freqconsonante(int freq[]);
float freqvocal(int freq[]);

int main()
{

    char letra[CHARS];
    char pal;
    int i = 0,j = 0;
    int x, y, temp = 0;
    int inicial = 0;
    int temporal[CHARS];
    int longitud = 0;
    int rep[CHARS];
    int gano = 0, repetido = 0, acertado = 0;
    int oportunidades = 0;
    int freq[ABC];
    int errores,vocal,conso;

    gotoxy(1,1);
    juego();
    printf("\nJuego del ahorcado ");
    printf("\nIngrese la palabra:");

    do
    {
        letra[i] = getch();

        if(letra[i]>='A' && letra[i]<='Z'||letra[i]>='a'&&letra[i]<='z')
        {
            printf("*");
            j++;
            i++;
        }
        if(letra[i]== 32)
        {
            printf(" ");
            j++;
            i++;
        }
        if(letra[i] == ENTER)
            break;
        if(letra[i] == BACKSPACE)
        {
            i--;
            j--;

        }




    printf("%d",i);
    }while(i<CHARS);

    printf("\n");

    for (i = 0; i < j; i++)
        printf("%c",letra[i]);

    getfreq(letra,freq);
    vocal = (float)freqvocal(freq)*0.5;
    conso = (float)(freqconsonante(freq)-vocal)*0.6;
    errores = vocal+conso;

    printf("\nCantidad de errores: %d",errores);


/*


    longitud = 0;
    inicial = 0;
    j = 0;

    rep[0] = ' ';
    rep[1] = '\0';


    do {
        system("cls");
        temp=0;

        if(inicial == 0) {
         for(i=0;i<strlen(letra);i++) {
          if(letra[i] == ' ') {
            temporal[i] = ' ';
             longitud++;
          }
          else {
             temporal[i] = '_';
             longitud++;
          }
         }
        }

        inicial = 1;

        temporal[longitud] = '\0';

        for(i=0;i<strlen(rep);i++) {
           if(rep[i] == pal) {
            repetido = 1;
            break;
          }
          else {
           repetido = 0;
         }
        }

        if(repetido == 0) {
         for(i=0;i<strlen(letra);i++) {
                    if(letra[i] == pal) {
             temporal[i] = pal;
              acertado++;
              temp=1;
            }
          }
        }

        if(repetido == 0) {
         if(temp == 0) {
           oportunidades = oportunidades - 1;
         }
        }
        else {
         printf("Ya se ha introducido este caracter");
         printf("\n\n");
        }

        printf("\n");

        for(i=0;i<strlen(temporal);i++) {
         printf(" %c ",temporal[i]);
        }

        printf("\n");

        if(strcmp(letra,temporal) == 0) {
            gano = 1;
            break;
        }

        printf("\n");
        printf("Letras Acertadas: %d",acertado);
        printf("\n");
        printf("Oportunidades Restantes: %d",oportunidades);
        printf("\n");

        rep[j] = pal;
        j++;

        if (oportunidades==0)
        {
           break;
        }

        printf("Introduzca una letra:");
        scanf("\n%c",&pal);

    }while(oportunidades != 0);


    if(gano) {
                printf("\n\n");
        printf("Enhorabuena, has ganado.");
    }
    else {
                printf("\n\n");
        printf("Has perdido.");
    }

    printf("\n\n");
    system("PAUSE");




*/


    return 0;
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
void juego(void)
{
   int px = 1, py = 1, i;
   int col = 0;
   clrscr();

    ///Parte superior
    gotoxy(px, py++); printf("%c%c%c%c%c%c",ESPC,ESPC, IQS,HL2, HL2, DQS);

    ///Soga
    for(py;py<4;py+2)
    {
        gotoxy(px, py++); printf("%c%c%c%c%c%c",ESPC,ESPC,VL,ESPC, ESPC, VL2);
        gotoxy(px, py++); printf("%c%c%c%c%c%c",ESPC,ESPC,VL,ESPC, ESPC, VL2);
        gotoxy(px, py++); printf("%c%c%c%c%c%c",ESPC,ESPC,VL,ESPC, ESPC, VL2);
    }

    ///Cabeza del muñeco
    if(py>3)
    {
    gotoxy(px, py++); printf("%c%c%c%c%c%c",ESPC, IQS2, HL, DQS2,ESPC, VL2);
    gotoxy(px, py++); printf("%c%c%c%c%c%c",ESPC,IQS2, '_',DQS2,ESPC, VL2);
    gotoxy(px, py++); printf("%c%c%c%c%c%c",ESPC, EII2, HL,EID2, ESPC,VL2);
    }
    ///Cuerpo del muñeco
    if(py>2)
    {
    gotoxy(px, py++); printf("%c%c%c%c%c%c",ESPC, DG1, VL,DG2,ESPC,VL2);
    gotoxy(px, py++); printf("%c%c%c%c%c%c",DG1, ESPC, VL, ESPC,DG2,VL2);
    gotoxy(px, py++); printf("%c%c%c%c%c%c",ESPC, DG1, ESPC, DG2,ESPC,VL2);
    gotoxy(px, py++); printf("%c%c%c%c%c%c",DG1, ESPC, ESPC, ESPC,DG2,VL2);
    gotoxy(px, py++); printf("%c%c%c%c%c%c",ESPC, ESPC, ESPC,ESPC,ESPC,VL2);
    gotoxy(px, py++); printf("%c%c%c%c%c%c",ESPC, ESPC, ESPC, ESPC,ESPC,VL2);
    }

    ///Piso
    gotoxy(px, py++); printf("%c%c%c%c%c%c",HL, HL, HL, HL,HL,HL);
    col = 6;

}



float freqvocal(int freq[])
{
    int ind,vocal = 0;

    for (ind = 0; ind < ABC; ind++)
        { if(ind == 0 || ind == 4 || ind == 8 || ind == 14 || ind == 20 )
        if(freq[ind])
            vocal++;
        }

    return vocal;


}



float freqconsonante(int freq[])
{

  int ind;
  int consonante = 0;

    for (ind = 0; ind < ABC; ind++)
        {
        if(ind != 0 || ind != 4 || ind != 8 || ind != 14 || ind != 20 )
            if(freq[ind])

                consonante++;
        }

    return consonante;
}
