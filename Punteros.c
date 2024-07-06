/* ========================================================================== */
/*                                                                            */
/*   Filename.c                                                               */
/*   (c) 2012 Author                                                          */
/*                                                                            */
/*   Description                                                              */
/*                                                                            */
/* ========================================================================== */
#include<stdio.h>
#include<conio.h>

int main()
{
    //Declaracion de una variable puntero.
    int *punteroentero;
    char *pchar;
    int entero[3];
    int valor;

    punteroentero=&valor;
    pchar=punteroentero;



    /*Consigo la direccion de un entero en la memoria ambos tienen la misma direccion de memoria.
    punteroentero = &entero[1];
    entero[0]=10;
    entero[1]=20;
    entero[2]=30;

    punteroentero[1]=50;//es lo mismo que *punteroentero=50;



     printf("%d--%d--%d",entero[0],entero[1],entero[2]);
    /*
    entero=10;
    printf("El puntero direccion: %p -- valor: %d",punteroentero,*punteroentero);
    getch();
    *punteroentero=100;
    printf("\n El puntero direccion: %p -- valor: %d",&entero,entero);
    */



    getch();
    return 0;
}
