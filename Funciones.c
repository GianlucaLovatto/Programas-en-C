/* ========================================================================== */
/*                                                                            */
/*   Filename.c                                                               */
/*   (c) 2012 Author                                                          */
/*                                                                            */
/*   Description                                                              */
/*                                                                            */
/* ========================================================================== */
#include<stdio.h>
#include<math.h>
#include<conio.h> 
#include<stdlib.h>
#include<ctype.h>
//Prototipo de una funcion 
//float suma(float a, float b);
//float sumaRef(float *a, float b);
void sumaVoid(float *resu, float a, float b);
//void ordenar(int *array, int tamaño);
//void ordenar(int arra[100]);


int main()
{
    float a,b,*resu;
    resu=(float *)malloc(sizeof(float));
    printf("Ingrese a:");
    scanf("%f",&a);
    printf("Ingrese b:");
    scanf("%f",&b);
    sumaVoid(resu,a,b);
    printf("Suma: %2.f",*resu);

    getch();

    return 0;
}

void sumaVoid(float *resu, float a, float b)
{
    *resu=a+b;
}

//float * mi funcion devule la direccion de un float tienen que devolver un puntero return &resu.