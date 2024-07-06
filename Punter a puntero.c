/* ========================================================================== */
/*                                                                            */
/*   Filename.c                                                               */
/*   (c) 2012 Author                                                          */
/*                                                                            */
/*   Description                                                              */
/*                                                                            */
/* ========================================================================== */
//programa que pueda asignar que guarde datos. 
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
    int ROWs, COLs;
    int *pInt;
    int i,j;
    int **pInt2, aInt[5][3];
    ROWs=5;
    COLs=3;
    randomize();
    pInt2= (int **)malloc(sizeof (int *)*ROWs);
    for(i=0;i<ROWs;i++)
    {
        pInt2[i]= (int *)malloc(sizeof(int)*COLs);
    }
    
    for(i=0;i<ROWs;i++)
    {
        for(j=0;j<COLs;j++)
        {
            *(*(pInt2+i)+j) = random(100);
        }   
    }
     for(i=0;i<ROWs;i++)
    {
        for(j=0;j<COLs;j++)
        {
            printf("%d ",(pInt2[i][j]));
            
        } 
        printf("\n");  
    }
   //Liberar un puntero a puntero 
   for(i=0;i<ROWs;i++)
   {
        free(pInt2[i]);
   }
   free(pInt2); 
    
    
   getch(); 
    
    
    return 0;
}
