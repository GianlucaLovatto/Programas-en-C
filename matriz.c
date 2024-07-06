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
  
int main()
{ 
    //Variables de la matriz principal.
    int codigo,filas=10,columnas=10,i,j,aux1,aux2,salir,aux4,aux3;
    int matriz[12][12];
    //Variables de la matriz auxiliar
    int matrizOrd[12][12];
    int filas2,columnas2;
    //Lleno mi primer matriz con ceros.
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            matriz[i][j]=0;  
        }
    }
    //Impresion del menu
    gotoxy(1,30);
    printf("MENU: ");
    printf("\nSELECCIONE UNA OPCION PRECIONANDO: ");
    printf("\n[ESC].Para salir.");
    printf("\n[F1].Carga la matriz con numeros aleatorios entre 0 y 999.");
    printf("\n[F2].Carga la matriz con numeros aleatorios que no se repiten entre 100 y 500.");
    printf("\n[F3].Infresando un N y una posicion, la Matriz se rellena con un incremento en 1 del N rodiando la posicion.");
    printf("\n[F4].Carga la Matriz con una conbinacion aleatoria de caracteres entre A y H.");
    printf("\n[ARRIBA].Ordena por Columnas de Menor a Mayor.");
    printf("\n[ABAJO].Ordenar por Columnas de Mayor a Menor.");
    printf("\n[DERECHA].Ordenar por Filas de Menor a Mayor.");
    printf("\n[IZQUIERDA].Ordenar por Filas de Mayor a Menor.");
    printf("\n[N].Cambiar el numero de Filas.[M]. Cambiar el numero de Columnas.");
    printf("\n[F5].Valor y posicion del Mayor de la FIla y Menor de la Columna.");
    
    
    
    randomize(); //Para inicializar la semilla.
//Estructura del programa.     
    while((codigo!=27))        
    {
        codigo=getch();
        if(codigo==0)
        {
            codigo=getch()+1000;
        }
        switch(codigo)
        {
                
                //Para el caso de presionar F1.
                case 1059:
                    //Cargo la matriz con los datos.
                    for(i=0;i<filas;i++)
                    {
                        for(j=0;j<columnas;j++)
                        {
                            matriz[i][j]=random(1000);  
                        }
                    }
                    break;
                    
                //Para el caso de presionar F2.               
                case 1060: 
                    //Cargo la matriz con los datos.
                    for(i=0;i<filas;i++)
                    {
                        for(j=0;j<columnas;j++)
                        {   
                            salir=0;                            
                            while(salir==0)
                            {
                                matriz[i][j]=(random(400)+100);
                                for(aux1=0;aux1<filas;aux1++)
                                {
                                    for(aux2=0;aux2<columnas;aux2++)
                                    {
                                         if((aux1==i) && (aux2==j))
                                         {
                                            aux1=filas;
                                            aux2=columnas;
                                         }else
                                         {
                                            if(matriz[i][j]==matriz[aux1][aux2])
                                            {
                                                salir=1;
                                            }
                                         }
                                    }    
                                }
                                if(salir==1)
                                {  
                                    salir=0;
                                }else
                                {
                                    salir=1;
                                }
                                
                            }        
                        }    
                    }
                    break;
                case 1061:
                      
                    break;
                case 1062:
                
                    break;
                case 1063:
                
                    break; 
                case 1064:
                
                    break;                    
                case 1065:
                
                    break; 
                case 1066:
                
                    break;
                case 1067:
                    
                    break;
                case 1080:
                    
                    break;  
            case 110: case 78: 
            break;
        }
        //Imprimo la matriz
            gotoxy(1,1);
            for(i=0;i<filas;i++)
            {                        
                for(j=0;j<columnas;j++)
                {
                    printf("%0.3d\t",matriz[i][j]);   
                }
                printf("\n");
            }
    }    
return 0; 
}
