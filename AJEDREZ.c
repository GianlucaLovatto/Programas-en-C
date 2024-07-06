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
#include <windows.h>  
int main()
{      
//Variables del tablero y menu
int i=0, j=0,color,aux=0, l = 8;
char menu;
//Variales del programa .
int x=1,y=1; 
int x1,y1;      
char codigo; 
SetConsoleTitle("Ajedrez");
do{

//Imprimo los bordes//
textbackground(BLUE);
//Barra superior
gotoxy(1,1);
cprintf("        a      b      c      d      e      f      g      h        ");
gotoxy(1,2);
cprintf("                                                                  "); 
//barra inferior
gotoxy(1,27);
cprintf("        a      b      c      d      e      f      g      h        ");
gotoxy(1,28);                                          
cprintf("                                                                  "); 
//Barras laterales.
l=8;
for(j=0;j<8;j++){
    //Lateral izquierda
    gotoxy(1, j*3+3);
    cprintf("     ");
    gotoxy(1, j*3+4);
    cprintf("  %d  ",j+1);
    gotoxy(1, j*3+5);
    cprintf("     ");  
    //Lateral derecha
    gotoxy(62, j*3+3);
    cprintf("     ");
    gotoxy(62, j*3+4);
    cprintf("  %d  ",l-j);
    gotoxy(62, j*3+5);
    cprintf("     ");  
}           
                                                                    
//imprimo el tablero.
   for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if(((i+j)%2)==0){
                  color=BLACK;
            }else{
                  color=RED;
            }
            
            textbackground(color);
            gotoxy(i*7+6, j*3+3);
            cprintf("       ");
            gotoxy(i*7+6, j*3+4);
            cprintf("       ");
            gotoxy(i*7+6, j*3+5);
            cprintf("       ");  
        }
   }
   

//Imprimo el menu de seleccion de pieza considerando mayusculas y minusculas o entradas erroneas . 
 do{
 gotoxy(70,1);
 printf("BIENVENIDO AL AJEDREZ.");
 gotoxy(70,2);
 printf("Seleccione la pieza.");
 gotoxy(70,3);
 printf("A. Torre. ");
 gotoxy(70,4);
 printf("B. Alfil. ");
 gotoxy(70,5);
 printf("C. Reina. ");
 gotoxy(70,6);
 printf("D. Caballo. ");
 gotoxy(70,7);
 printf("E. Rey. ");
 gotoxy(70,8);
    if(aux==2){
        printf("Opcion no existente");
        gotoxy(70,9);                    
    }
 menu=getch();
   switch(menu)
	{
		case 'A':
		case 'a':

			aux = 1;

			break;

		case 'B':
		case 'b':

			aux = 1;

			break;

		case 'C':
		case 'c':

			aux = 1;

			break;

		case 'D':
		case 'd':

			aux = 1;

			break;

		case 'E':
		case 'e':
			aux = 1;
			break;

		default:
                 aux=2;
			break;
	}
    gotoxy(87,8);
 }while(aux!=1);
 
 //Controlo los movimientos de mis coordenadas entre 1 y 8 con x e y.
    do{
     x1=2+(x*7);
     y1=1+(y*3);
    gotoxy(x1,y1);
    // Captura de teclas //
		codigo = getch();

		if(codigo == 0)
		{
			codigo = getch();

			if(codigo == 72)
			{
				if(y > 1)
				{
					y--;
				}else{
                  y=8;
                }
			}

			if(codigo == 80)
			{
				if(y < 8)
				{
					y++;
				}else{
                   y=1;
                }
			}

			if(codigo == 75)
			{
				if(x > 1)
				{
					x--;
				}else{
                  x=8;
                }
			}

			if(codigo == 77)
			{
				if(x < 8)
				{
					x++;
				}else{
                    x=1;
                }
			}
		}
    }while(codigo != 13);
//Comienzo con los movimientos de las piezas
if((menu=='B')||(menu=='b')){   
//Movimientos del alfil 
//Primer brazo de la diagonal.
    i=y;
    j=x;
    while(i >= 1 && j >= 1){
        x1=2+(j*7);
        y1=1+(i*3);
        gotoxy(x1,y1);
        if(((i+j)%2)==0){
            color=BLACK;
        }else{
            color=RED;
        }
        textbackground(color);
        cprintf("*");
        j--;
        i--;
    }
//Segundo brazo de la diagonal
    i=y;
    j=x;
    while(i <= 8 && j <= 8){
        x1=2+(j*7);
        y1=1+(i*3);
        gotoxy(x1,y1);
        if(((i+j)%2)==0){
            color=BLACK;
        }else{
            color=RED;
        }
        textbackground(color);
        cprintf("*");
        j++;
        i++;
    }
//Tercer Brazo de la diagonal
    i=y;
    j=x;
    while(i >= 1  && j <= 8){
        x1=2+(j*7);
        y1=1+(i*3);
        gotoxy(x1,y1);
        if(((i+j)%2)==0){
            color=BLACK;
        }else{
            color=RED;
        }
        textbackground(color);
        cprintf("*");
        j++;
        i--;
    }    
//Cuarto brazo de la diagonal.
    i=y;
    j=x;
    while(i <= 8  && j >= 1){
        x1=2+(j*7);
        y1=1+(i*3);
        gotoxy(x1,y1);
        if(((i+j)%2)==0){
            color=BLACK;
        }else{
            color=RED;
        }
        textbackground(color);
        cprintf("*");
        j--;
        i++;
    }
//vuelvo a mi posicion inicial y sobre escribo B que representa el alfil
    i=y;
    j=x;    
    x1=2+(j*7);
    y1=1+(i*3);
    gotoxy(x1,y1);
    if(((i+j)%2)==0){
        color=BLACK;
    }else{
        color=RED;
    }
    textbackground(color);
    cprintf("B");
}else{
        if((menu=='A')||(menu=='a')){   
//Movimientos de la Torre
//Primer brazo de la torre.
        i=y;
        j=x;
        while(j >= 1){
            x1=2+(j*7);
            y1=1+(i*3);
            gotoxy(x1,y1);
            if(((i+j)%2)==0){
                color=BLACK;
            }else{
                color=RED;
            }
            textbackground(color);
            cprintf("*");
            j--;
        }
//Segundo brazo de la torre.
        i=y;
        j=x;
     while(j<=8){
            x1=2+(j*7);
            y1=1+(i*3);
            gotoxy(x1,y1);
            if(((i+j)%2)==0){
                color=BLACK;
            }else{
                color=RED;
            }
            textbackground(color);
            cprintf("*");
            j++;
        }
//Tercer Brazo de la torre.
        i=y;
        j=x;
        while(i >= 1){
            x1=2+(j*7);
            y1=1+(i*3);
            gotoxy(x1,y1);
            if(((i+j)%2)==0){
                color=BLACK;
            }else{
                color=RED;
            }
            textbackground(color);
            cprintf("*");
            i--;
        }    
//Cuarto brazo de la torre.
        i=y;
        j=x;
        while(i <= 8){
            x1=2+(j*7);
            y1=1+(i*3);
            gotoxy(x1,y1);
            if(((i+j)%2)==0){
                color=BLACK;
            }else{
                color=RED;
            }
            textbackground(color);
            cprintf("*");
            i++;
        }
//vuelvo a mi posicion inicial y sobreescribo A que representa a la torre.
        i=y;
        j=x;    
        x1=2+(j*7);
        y1=1+(i*3);
        gotoxy(x1,y1);
        if(((i+j)%2)==0){
            color=BLACK;
        }else{
            color=RED;
        }
        textbackground(color);
        cprintf("A");
    }else{
//Movimientos de la reina     
        if((menu=='C')||(menu=='c')){
               //Primer brazo de la diagonal.
                i=y;
                j=x;
                while(i >= 1 && j >= 1){
                        x1=2+(j*7);
                        y1=1+(i*3);
                        gotoxy(x1,y1);
                            if(((i+j)%2)==0){
                                color=BLACK;
                            }else{
                                color=RED;
                            }
                    textbackground(color);
                    cprintf("*");
                    j--;
                    i--;
                }
               //Segundo brazo de la diagonal
                 i=y;
                 j=x;
                    while(i <= 8 && j <= 8){
                        x1=2+(j*7);
                        y1=1+(i*3);
                        gotoxy(x1,y1);
                        if(((i+j)%2)==0){
                            color=BLACK;
                        }else{
                            color=RED;
                        }
                        textbackground(color);
                        cprintf("*");
                        j++;
                        i++;
                    } 
                //Tercer Brazo de la diagonal
                    i=y;
                    j=x;
                    while(i >= 1  && j <= 8){
                            x1=2+(j*7);
                            y1=1+(i*3);
                            gotoxy(x1,y1);
                            if(((i+j)%2)==0){
                                color=BLACK;
                            }else{
                                color=RED;
                            }
                            textbackground(color);
                            cprintf("*");
                            j++;
                            i--;
                    } 
                //Cuarto brazo de la diagonal.
                        i=y;
                        j=x;
                        while(i <= 8  && j >= 1){
                                x1=2+(j*7);
                                y1=1+(i*3);
                                gotoxy(x1,y1);
                                if(((i+j)%2)==0){
                                    color=BLACK;
                                }else{
                                    color=RED;
                                }
                                textbackground(color);
                                cprintf("*");
                                j--;
                                i++;
                            }
                 // Quito brazo de la reina.
                            i=y;
                            j=x;
                            while(j >= 1){
                                x1=2+(j*7);
                                y1=1+(i*3);
                                gotoxy(x1,y1);
                                if(((i+j)%2)==0){
                                    color=BLACK;
                                }else{
                                    color=RED;
                                }
                                textbackground(color);
                                cprintf("*");
                                j--;
                            }  
                    //Sexto brazo de la reina.
                            i=y;
                            j=x;
                            while(j<=8){
                                x1=2+(j*7);
                                y1=1+(i*3);
                                gotoxy(x1,y1);
                                if(((i+j)%2)==0){
                                    color=BLACK;
                                }else{
                                    color=RED;
                                }
                                textbackground(color);
                                cprintf("*");
                                j++;
                                } 
                //Septimo Brazo de la reina.
                        i=y;
                        j=x;
                        while(i >= 1){
                                x1=2+(j*7);
                                y1=1+(i*3);
                                gotoxy(x1,y1);
                                if(((i+j)%2)==0){
                                    color=BLACK;
                                }else{
                                    color=RED;
                                }
                                textbackground(color);
                                cprintf("*");
                                i--;
                        }   
                    //Octavo brazo de la torre.
                        i=y;
                        j=x;
                        while(i <= 8){
                            x1=2+(j*7);
                            y1=1+(i*3);
                            gotoxy(x1,y1);
                            if(((i+j)%2)==0){
                                color=BLACK;
                            }else{
                                color=RED;
                            }
                                textbackground(color);
                                cprintf("*");
                                i++;
                        }   
        //vuelvo a mi posicion inicial y sobreescribo A que representa a la torre.
                    i=y;
                    j=x;    
                    x1=2+(j*7);
                    y1=1+(i*3);
                    gotoxy(x1,y1);
                    if(((i+j)%2)==0){
                        color=BLACK;
                    }else{
                        color=RED;
                    }
                    textbackground(color);
                    cprintf("C");   
                     
        }     
    }
}    
/*_setcursortype(_SOLIDCURSOR);//ME ELIMINA EL CURSOR.
gotoxy(70,13);
printf(" Precione [ESC] para salir."); */ 
}while((getch())!=27);    
return 0; 
}
