/* ========================================================================== */
/*                                                                            */
/*   Filename.c                                                               */
/*   (c) 2012 Author                                                          */
/*                                                                            */
/*   Description                                                              */
/*                                                                            */
/* ========================================================================== */
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<conio.h> 
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<io.h>
#include<fcntl.h>
#include<sys\stat.h>
//#include<stdbool.h>
#include<windows.h>


//funcion que dibuja
void dibujar(void);

//Funcion del ingreso de datos
void capturadatos(int codigo, struct ingresodatos *ingreso_t, struct datos *datos_t);

//Funcion que me actualiza la posicion 
void actualizarposicionpelota(struct datospelota *datospelota_t, struct datos *datos_t);
//Funcion que me muestra la pelotita. Opera con las posiciones que se actializan con el tiempo.
void mostrarposicionpelota(struct datospelota *datospelota_t, struct datos *datos_t);
//Funcion que me imprime el obstaculo en pantalla
void imprimirobstaculo(struct datos *datos_t);
//Funcion que me crea el Bmp en blanco
void escribirBMP (void);
//Funcion que me carga las posiciones de la pelotita en la matriz para el Bmp.
void guardarcirculo(double posX, double posY, double radio);
//Funcion que me restablece el bmp 
void restablecerBMP(void);
//Funcion de redondeo
int round(double numero);
//Funcion de trunkeo
int trunk(double numero);
//funcion que me muestra e imprime el bmp 
void mostrarBMP(void);
 



  
char BMP[800][1200][3];
char cabeceraBMP[54];
typedef int bool;
#define true 1
#define false 0
//Constantes
#define G 9.8
#define P 3.14
#define fps 30
#define cifras 7
//Estructura del tiempo 
struct timer{
    clock_t timep,tiempoinicio,tiempofinal;
};
//Estructura de ingreso de datos 
struct ingresodatos
{
    char numero[cifras];
    int cursor;
    int x;
    int y;
    int marcadorvar;
    bool coma;
};
//Estructura de datos
struct datos
{
    double v0;
    double SCALE;
    double X0;
    double Y0;
    double Phi0;
    double AlphaX;
    double AlphaY; 
    double Time;           
    double D;
    double ObsX1;
    double ObsY1;
    double ObsX2;
    double ObsY2;
    bool PATH;
    bool STATUS;
    bool OBSTACULO;
};
//Datos de la pelota
struct datospelota{
    double posX0;
    double posY0;
    double posXf;
    double posYf;
    double velocidadX0;
    double velocidadY0;
    double velocidadYf ;
    clock_t time;
};                        




int main()
{
    int codigo,i,j,k;
    //Variables de posicion inicial de la pelota
    bool posinicial;
    //Estructuras de datos para los calculos     
    struct datos datos_t;
    struct timer timerMostrarpelota;//Tiempo para la impresion de la pelotita en pantalla
    struct timer timerActualizarpelota;// Temporizador para lograr el efecto de impresion de la pelotita
    struct datospelota datospelota_t;
    //Estructura de ingreso de datos
    struct ingresodatos ingreso_t; 
    ingreso_t.x=ingreso_t.y=ingreso_t.cursor=0;
    ingreso_t.marcadorvar=0;
    memset(ingreso_t.numero,NULL,10);
    ingreso_t.coma=false;
    
    //Estructura de datos aceradas
    datos_t.D=datos_t.X0=datos_t.Y0=datos_t.v0=datos_t.AlphaY=datos_t.AlphaX=datos_t.Phi0=datos_t.Time=datos_t.SCALE=0;
    datos_t.ObsX1=datos_t.ObsX2=datos_t.ObsY1=datos_t.ObsY2=0; 
    //Restablesco el BMP 
    restablecerBMP();
        
    datos_t.STATUS=false;
    datos_t.PATH=false;
    datos_t.OBSTACULO=false; 
    
    //Configuracion del tiempo de actualizacion del programa
    timerMostrarpelota.timep = round(1000.0/fps);// Se configura el tiempo de llamada
    timerMostrarpelota.tiempoinicio = clock();// Se le da un ajuste de tiempo 
    
    //Configuracion del tiempo de calculo 
    timerActualizarpelota.timep = datos_t.Time;
    timerActualizarpelota.tiempoinicio = clock(); 
        
    dibujar(); 
    gotoxy(16,1);
    _setcursortype(_NORMALCURSOR);    
while((codigo!=27)){

     //Tiempo de actualizacion de la pelotita;
    timerActualizarpelota.timep=datos_t.Time;
    
    timerActualizarpelota.tiempofinal = clock();
    timerMostrarpelota.tiempofinal = clock(); 
    
    if(kbhit())
        {
        //Captura de teclas 
            codigo=getch();
            if(codigo==0)
            {
                    codigo=getch()+1000;    
            }
            switch(codigo){
             
            //Si se presiona Tab        
                case 9:
                    //Condiciones para saber en que variable guardar los datos.
                    capturadatos(codigo,&ingreso_t,&datos_t);
                    if(ingreso_t.marcadorvar==12)
                    {
                        _setcursortype(_NOCURSOR);    
                    }
                    if((ingreso_t.marcadorvar<12)&&((int)strlen(ingreso_t.numero)>0)){                     
                        if(ingreso_t.y < 4)
                        {
                            ingreso_t.y++;
                        }else
                        {
                            ingreso_t.x=ingreso_t.x+23;
                            ingreso_t.y=0;     
                        }
                        //Paso las datos a las posiciones iniciales a la estructura de la pelota.
                        if(ingreso_t.marcadorvar==2)
                        {
                            datospelota_t.posX0 = datos_t.X0;    
                        }
                        if(ingreso_t.marcadorvar==3)
                        {
                            datospelota_t.posY0 = datos_t.Y0;         
                        }          
                        ingreso_t.marcadorvar++;
                        ingreso_t.cursor=0;
                        memset(ingreso_t.numero,NULL,10);
                        ingreso_t.coma=false;
                        //Posicionamiento del cursor
                        _setcursortype(_NORMALCURSOR);
                        gotoxy(16+ingreso_t.x,1+ingreso_t.y); 
                    }
                     
                    break;                                       
                //Para que pueda ingresar solo un punto en el numero.
                case 46:
                    if(ingreso_t.coma==false)
                    {
                        capturadatos(codigo,&ingreso_t,&datos_t);
                        ingreso_t.coma=true;    
                    }
                    break;
                                        
                //Si se presiona F10  
                case 1068:
                    datos_t.PATH =! datos_t.PATH;
                    break;                     
                //Si se presiona F9
                case 1067: 
                        //El lanzamiento o Stop
                        if(!datos_t.STATUS){    
                             if(ingreso_t.marcadorvar<12)
                            {
                                gotoxy(62,4);
                                printf("Faltan datos");
                            }else
                            {
                                //Si se presiono F9 se reinicion toadas las variables del ingreso de dato
                                ingreso_t.x=ingreso_t.y=ingreso_t.cursor=0;
                                ingreso_t.marcadorvar=0;
                                memset(ingreso_t.numero,NULL,10);
                                ingreso_t.coma=false;
                                //Se le da los valores iniciales a los datos de la pelota.
                                datos_t.STATUS=true;
                                datospelota_t.time=0.0;   
                                datospelota_t.velocidadX0 = datos_t.v0 * cos((datos_t.Phi0 * (P / 2.0)) / 90.0);
    						    datospelota_t.velocidadY0 = datos_t.v0 * sin((datos_t.Phi0 * (P / 2.0)) / 90.0);                  
                            }
                        }else
                        {
                            datos_t.STATUS=false;                            
                            mostrarposicionpelota(&datospelota_t,&datos_t);
                            // Se escribe el bmp
                            mostrarBMP();
                            dibujar(); 
                        }   
                    break;
                //Si se presiona F8
                case 1066:
                    if((datospelota_t.posX0 > datos_t.ObsX1 && datospelota_t.posX0 < datos_t.ObsX2 && datospelota_t.posY0 > datos_t.ObsY1 && datospelota_t.posY0 < datos_t.ObsY2)
                    ||(datospelota_t.posXf > datos_t.ObsX1 && datospelota_t.posXf < datos_t.ObsX2 && datospelota_t.posYf > datos_t.ObsY1 
                    && datospelota_t.posYf < datos_t.ObsY2))
                    {
                        gotoxy(47,4);
                        printf("ERROR POSICION DE LA PELOTA ES IGUAL AL LA DE OBSTACULO");
                    }else
                    {
                        gotoxy(47,4);
                        printf("                                                       ");
                        datos_t.OBSTACULO=!datos_t.OBSTACULO;   
                        imprimirobstaculo(&datos_t); 
                    }                                
                    break;            
                //Si se preciono otra tecla en caso de numero lo evaluo en la funcion de capturar datos.                         
                default:
                    capturadatos(codigo,&ingreso_t,&datos_t); 
                    break; 
            }           
        }
    
    //Actializaciones del tiempo de llamada a las funciones. 
    if(((timerActualizarpelota.tiempofinal-timerActualizarpelota.tiempoinicio) > (timerActualizarpelota.timep))
    &&datos_t.STATUS)
    {
        actualizarposicionpelota(&datospelota_t,&datos_t);
        guardarcirculo(datospelota_t.posXf / datos_t.SCALE, datospelota_t.posYf / datos_t.SCALE, (datos_t.D / (2.0 * datos_t.SCALE)));
        timerActualizarpelota.tiempoinicio = clock();                   
    }
    if(((timerMostrarpelota.tiempofinal-timerMostrarpelota.tiempoinicio) > timerMostrarpelota.timep)
    &&datos_t.STATUS)
    {
        mostrarposicionpelota(&datospelota_t,&datos_t);
        timerMostrarpelota.tiempoinicio = clock();
    }                      
}

    return 0; 
}

//Funcion que me dibuja la interfaz 
void dibujar(void)
{
    int i,j;
    
    textbackground(BLUE);
    _setcursortype(_NOCURSOR);
    for(i=5;i<50;i++){
        for(j=0;j<80;j++)
        {
            gotoxy(1 + j,1 + i);
            cprintf(" ");
        }
    }
    textbackground(BLACK);
     for(i=0;i<5;i++){
        for(j=0;j<80;j++)
        {
            gotoxy(1 + j,1 + i);
            cprintf(" ");
        }
    }
    _setcursortype(_NOCURSOR);
    gotoxy(1,1);
    cprintf("Veloc ini(m/s): "); 
    gotoxy(1,2);
    cprintf("Escala     (m): ");
    gotoxy(1,3);
    cprintf("Pos inici X(m): ");
    gotoxy(1,4);
    cprintf("Pos inici Y(m): ");
    gotoxy(1,5);
    cprintf("Angu inic(Grd): ");
    gotoxy(24,1);
    cprintf("Perd ener X(%): ");
    gotoxy(24,2);
    cprintf("Perd ener Y(%): ");
    gotoxy(24,3);
    cprintf("Time calcu (s): ");
    gotoxy(24,4);
    cprintf("Diame pelot(m): "); 
    gotoxy(24,5);
    cprintf("Pos Obs X1 (m): "); 
    gotoxy(47,1);
    cprintf("Pos Obs X2 (m): "); 
    gotoxy(47,2);
    cprintf("Pos Obs Y1 (m): ");
    gotoxy(47,3);
    cprintf("Pos Obs Y2 (m): ");        
}


//Funcion que captura los datos
void capturadatos(int codigo, struct ingresodatos *ingreso_t, struct datos *datos_t)
{
    int i,j; 
    switch(codigo){
        case 9:        
            switch(ingreso_t->marcadorvar)
            {                  
                case 0:
                    datos_t->v0=atof(ingreso_t->numero);
                    break;
                case 1:
                    datos_t->SCALE=atof(ingreso_t->numero);
                    break;
                case 2:
                    datos_t->X0=atof(ingreso_t->numero);                
                    break;
                case 3:
                    datos_t->Y0=atof(ingreso_t->numero);                
                    break;                                                                                                                                     
                case 4:          
                    datos_t->Phi0=atof(ingreso_t->numero);
                    break;
                case 5:
                    datos_t->AlphaX=atof(ingreso_t->numero);
                    break;
                case 6:
                    datos_t->AlphaY=atof(ingreso_t->numero);
                    break;
                case 7:
                    datos_t->Time=atof(ingreso_t->numero);
                    break;
                case 8:
                    datos_t->D=atof(ingreso_t->numero);
                    break;
                case 9:
                    datos_t->ObsX1=atof(ingreso_t->numero);
                    break;
                case 10:
                    datos_t->ObsX2=atof(ingreso_t->numero);
                    break;
                case 11:
                    datos_t->ObsY1=atof(ingreso_t->numero);
                    break;
                case 12:
                    datos_t->ObsY2=atof(ingreso_t->numero);
                    break;
                default:
                    break;
            }
            break;            
        case 8://Suprimir
            if((int)strlen(ingreso_t->numero)>0){       
                ingreso_t->cursor--;     
                ingreso_t->numero[ingreso_t->cursor]=NULL;
            }                 
            break;  
        case 45: //Menos
            if(((int)strlen(ingreso_t->numero)==0)&&(ingreso_t->marcadorvar==0||ingreso_t->marcadorvar==4))
            {
                ingreso_t->numero[ingreso_t->cursor++]=codigo;
            }
            break;             
        default:            
            if((codigo=='.')||isdigit(codigo)&&(ingreso_t->cursor<11)&&((int)strlen(ingreso_t->numero)<cifras)){                      
                    ingreso_t->numero[ingreso_t->cursor++]=codigo;    
            }
            break;
    }
    //Borro la linea eh imprimo la cadena nuevamente.
    _setcursortype(_NOCURSOR);
    gotoxy(16+ingreso_t->x,1+ingreso_t->y);
    printf("        "); 
    //Imprimo el numero en pantalla
        for(i=0;i<ingreso_t->cursor;i++){
            gotoxy(16+ingreso_t->x+i,1+ingreso_t->y);
            printf("%c",ingreso_t->numero[i]);
        }
    if(ingreso_t->cursor==0)
    {   
        gotoxy(16+ingreso_t->x,1+ingreso_t->y);
    }
    _setcursortype(_NORMALCURSOR);
    //Posiciones iniciales de la pelotita.
    if((ingreso_t->marcadorvar==2))
    {      
        textcolor(WHITE);     
        textbackground(BLUE);
        gotoxy(round(1.0+datos_t->X0/datos_t->SCALE),round(50.0-datos_t->Y0/datos_t->SCALE));
        cprintf(" ");
        datos_t->X0=atof(ingreso_t->numero); 
        gotoxy(round(1.0+datos_t->X0/datos_t->SCALE),round(50.0-datos_t->Y0/datos_t->SCALE));
        cprintf("%c",254);
    }else
    {
        if((ingreso_t->marcadorvar==3))
        {
            
            gotoxy(round(1.0+datos_t->X0/datos_t->SCALE),round(50.0-datos_t->Y0/datos_t->SCALE));
            cprintf(" ");
            datos_t->Y0=atof(ingreso_t->numero); 
            gotoxy(round(1.0+datos_t->X0/datos_t->SCALE),round(50.0-datos_t->Y0/datos_t->SCALE));
            cprintf("%c",254);     
        }else
        {
            textcolor(WHITE);     
            textbackground(BLACK);    
        }  
    }
} 


//Funcion de calculo de la posicion
void actualizarposicionpelota(struct datospelota *datospelota_t, struct datos *datos_t)
{   
    
    //Variables Auxiliares 
    double t, posXa, posYa;  
    //Imprime el recorrido
    if(datos_t->PATH==false){
        textcolor(WHITE);
        textbackground(BLUE);
        gotoxy(round(1.0+datospelota_t->posXf/datos_t->SCALE),round(50.0-datospelota_t->posYf/datos_t->SCALE));
        cprintf(" ");
    }
    
    //Se actualiza el tiempo  
    datospelota_t->time = datospelota_t->time + datos_t->Time; 
    //Se actualizan las posiciones de la pelotita.
    datospelota_t->posXf = datospelota_t->posX0 + datospelota_t->velocidadX0 * (datospelota_t->time / 1000.0);   
    datospelota_t->posYf = datospelota_t->posY0 + datospelota_t->velocidadY0*(datospelota_t->time/1000.0)-
    (1.0/2.0)* G * pow((datospelota_t->time/1000.0),2.0);
    
    
    //Colision contra el piso
     if((50.0-datospelota_t->posYf / datos_t->SCALE)>50.0)
    {
        //Determino la velocidad de impato con el piso para luego calcular el tiempo y la velocidad inicial con perdida.
        datospelota_t->velocidadYf = -sqrt(pow(datospelota_t->velocidadY0, 2.0) - 2.0 * G * (0.0 - datospelota_t->posY0));     
        //Tiempo de choque contra el piso.
        t=((datospelota_t->velocidadY0-datospelota_t->velocidadYf)/G);
        if(t > 0.01)
        {
            datospelota_t->time = datospelota_t->time - round(t*1000.0);
            datospelota_t->posX0 = datospelota_t->posX0 + datospelota_t->velocidadX0 * (t);
        }else
        {
            datospelota_t->time = 0;
            datospelota_t->posX0=datospelota_t->posXf;
        }
        
        //Nuevas posiciones iniciales.
        datospelota_t->posY0=0.0;
                
        //Perdida de energia en X e Y.        
        datospelota_t->velocidadX0= (datospelota_t->velocidadX0 * (1.0 - datos_t->AlphaX / 100.0));
        datospelota_t->velocidadY0= -(datospelota_t->velocidadYf * (1.0 - datos_t->AlphaY / 100.0));
        //Imprime el punto de choque en consola y bmp
        gotoxy(round(1+datospelota_t->posX0/datos_t->SCALE),50);
        if(datos_t->PATH==true){
            cprintf("%c",254);
        }else
        {
            cprintf(" ");
        }
        guardarcirculo((datospelota_t->posX0/datos_t->SCALE),(0.0),(datos_t->D/(2.0*datos_t->SCALE)));
        
        //Actualizo los datos en base al tiempo calculado 
        datospelota_t->posXf = datospelota_t->posX0 + datospelota_t->velocidadX0 * (datospelota_t->time / 1000.0);
        datospelota_t->posYf = datospelota_t->posY0 + datospelota_t->velocidadY0 * (datospelota_t->time / 1000.0) -
		  (1.0/2.0) * G * pow((datospelota_t->time / 1000.0), 2.0);
                
    }
    //Colision contra el techo  
    if((50.0-datospelota_t->posYf/datos_t->SCALE)<6.0)
    {
        //Determino la velocidad de impato con el techo para luego calcular el tiempo y la velocidad inicial con perdida.
        datospelota_t->velocidadYf = sqrt(pow(datospelota_t->velocidadY0, 2.0) - 2.0 * G * (44.0 * datos_t->SCALE - datospelota_t->posY0));

		t = ((datospelota_t->velocidadY0-datospelota_t->velocidadYf) / G); 

		datospelota_t->posY0 = 44.0 * datos_t->SCALE;
		datospelota_t->posX0 = datospelota_t->posX0 + datospelota_t->velocidadX0 * (t);

		datospelota_t->time = datospelota_t->time - round(t*1000.0);
    
        //Perdida de energia en X e Y.        
        datospelota_t->velocidadX0= (datospelota_t->velocidadX0 * (1.0 - datos_t->AlphaX / 100.0));
        datospelota_t->velocidadY0 = -(datospelota_t->velocidadYf * (1.0 - datos_t->AlphaY / 100.0));
        
        //Imprime el punto de choque en consola y bmp
        gotoxy(round(1+datospelota_t->posX0/datos_t->SCALE),6.0);
        if(datos_t->PATH==true){
            cprintf("%c",254);
        }else
        {
            cprintf(" ");
        }
        guardarcirculo((datospelota_t->posX0/datos_t->SCALE),(44.0*datos_t->SCALE),(datos_t->D/(2.0*datos_t->SCALE)));
        
                
		datospelota_t->posXf = datospelota_t->posX0 + datospelota_t->velocidadX0 * (datospelota_t->time / 1000.0);
        datospelota_t->posYf = datospelota_t->posY0 + datospelota_t->velocidadY0 * (datospelota_t->time / 1000.0) -
		  (1.0/2.0) * G * pow((datospelota_t->time / 1000.0), 2.0); 
         
    } 
    //Choque pared derecha
    if((1.0+datospelota_t->posXf/datos_t->SCALE) > 80)
    {    
        //Determino el tiempo de impacto con la pared para tomar la diferencia entre el tiempo del programa 
        //como datos para el inicio del siguiente recorrido.
        t=((79.0 * datos_t->SCALE) - datospelota_t->posX0)/datospelota_t->velocidadX0;
        if(t < 0.0)
        {
            t=0;
        }
        datospelota_t->posX0=79.0 * datos_t->SCALE;
        datospelota_t->posY0 = datospelota_t->posY0 + datospelota_t->velocidadY0*(t)-
        (1.0/2.0)* G * pow(t, 2.0);
        
        datospelota_t->velocidadY0 = (datospelota_t->velocidadY0 - G * t);
        
        datospelota_t->time = datospelota_t->time - round(t*1000.0);
        
        //Perdida de energia en X e Y.        
        datospelota_t->velocidadX0 = -(datospelota_t->velocidadX0 * (1.0 - datos_t->AlphaX / 100.0));
        datospelota_t->velocidadY0 = (datospelota_t->velocidadY0 * (1.0 - datos_t->AlphaY / 100.0));
        
        //Imprime el punto de choque en consola y bmp
        gotoxy(80, round(50.0 - datospelota_t->posY0/datos_t->SCALE));
        if(datos_t->PATH==true){
            cprintf("%c",254);
        }else
        {
            cprintf(" ");
        }
        guardarcirculo(79.0 ,(datospelota_t->posY0/datos_t->SCALE),(datos_t->D/(2.0*datos_t->SCALE)));
        
        //Actualizo posiciones. 
        datospelota_t->posXf = datospelota_t->posX0 + datospelota_t->velocidadX0 * (datospelota_t->time / 1000.0);
		datospelota_t->posYf = datospelota_t->posY0 + datospelota_t->velocidadY0 * (datospelota_t->time / 1000.0) -
			(1.0/2.0) * G * pow((datospelota_t->time / 1000.0), 2.0);                               
        
    }
    
    //Choque pared izquierda 
    if((1+datospelota_t->posXf/datos_t->SCALE) < 1.0)
    {
         //Determino el tiempo de impacto con la pared para tomar la diferencia entre el tiempo del programa 
        //como datos para el inicio del siguiente recorrido.
        t = ((0.0 - datospelota_t->posX0) / datospelota_t->velocidadX0);
        if(t < 0.0)
        {
            t=0;
        }
        datospelota_t->posX0=0.0;
        datospelota_t->posY0 = datospelota_t->posY0 + datospelota_t->velocidadY0 * t -
            (1.0/2.0)* G * pow(t, 2.0);
        
        datospelota_t->velocidadY0 = (datospelota_t->velocidadY0 - G * t);
     
        datospelota_t->time = datospelota_t->time - round(t*1000.0);

        //Perdida de energia en X e Y. 
		datospelota_t->velocidadX0 = -(datospelota_t->velocidadX0 * (1.0 - datos_t->AlphaX / 100.0));
        datospelota_t->velocidadY0 = (datospelota_t->velocidadY0 * (1.0 - datos_t->AlphaY / 100.0));
       
       //Imprime el punto de choque en consola y bmp
        gotoxy(1, round(50.0 - datospelota_t->posY0 / datos_t->SCALE));
        if(datos_t->PATH==true){
            cprintf("%c",254);
        }else
        {
            cprintf(" ");
        }
        guardarcirculo(0.0, datospelota_t->posY0 / datos_t->SCALE, (datos_t->D / (2.0 * datos_t->SCALE)));

        datospelota_t->posXf = datospelota_t->posX0 + datospelota_t->velocidadX0 * (datospelota_t->time / 1000.0);
		datospelota_t->posYf = datospelota_t->posY0 + datospelota_t->velocidadY0 * (datospelota_t->time / 1000.0) -
			(1.0/2.0) * G * pow((datospelota_t->time / 1000.0), 2.0);                           
    }
    
    if (datospelota_t->posYf < 0.0)
    {
		datospelota_t->posYf = 0.0;
    }
    

    //Coliciones con el obstaculo 
    if(datos_t->OBSTACULO==true)
    {   
        t=datospelota_t->time - datos_t->Time;
        if(t<0)
        {
            t=0.0;
        }
		posXa = datospelota_t->posX0 + datospelota_t->velocidadX0 * ((t) / 1000.0);
		posYa = datospelota_t->posY0 + datospelota_t->velocidadY0 * ((t) / 1000.0) -
			(1.0/2.0) * G * pow(((datospelota_t->time - datos_t->Time) / 1000.0), 2.0);
        
		// Colision pared izquierda
		if (posXa < datos_t->ObsX1 && datospelota_t->posXf > datos_t->ObsX1)
		{
			t = (datos_t->ObsX1 - datospelota_t->posX0) / datospelota_t->velocidadX0;
            if(t<0.0)
            {
                t=0.0;
            }
			if ((datospelota_t->posY0 + datospelota_t->velocidadY0 * t - (1.0/2.0) * G * pow(t, 2.0)+0.1) > datos_t->ObsY1 &&
				(datospelota_t->posY0 + datospelota_t->velocidadY0 * t - (1.0/2.0) * G * pow(t, 2.0)+0.1) < datos_t->ObsY2)
			{
				datospelota_t->posX0 = datos_t->ObsX1;
				datospelota_t->posY0 = datospelota_t->posY0 + datospelota_t->velocidadY0 * t -
					(1.0/2.0) * G * pow(t, 2.0);

				datospelota_t->velocidadY0 = (datospelota_t->velocidadY0 - G * t);

				datospelota_t->time -= round(t * 1000.0);

				datospelota_t->velocidadY0 = (datospelota_t->velocidadY0 * (1.0 - datos_t->AlphaY / 100.0));
				datospelota_t->velocidadX0 = -(datospelota_t->velocidadX0 * (1.0 - datos_t->AlphaX / 100.0));

				if (datos_t->PATH)
				{
					gotoxy(round(datos_t->ObsX1 / datos_t->SCALE) , round(50.0 - datospelota_t->posY0 / datos_t->SCALE));
					cprintf("%c", 254);
				}

				guardarcirculo(datos_t->ObsX1 / datos_t->SCALE, datospelota_t->posY0 / datos_t->SCALE, (datos_t->D / (2.0 * datos_t->SCALE)));

				datospelota_t->posXf = datospelota_t->posX0 + datospelota_t->velocidadX0 * (datospelota_t->time / 1000.0);

				datospelota_t->posYf = datospelota_t->posY0 + datospelota_t->velocidadY0 * (datospelota_t->time / 1000.0) -
					(1.0/2.0) * G * pow((datospelota_t->time / 1000.0), 2.0);
            }
		}
        
        
		// Colision pared derecha
		if (posXa > datos_t->ObsX2 && datospelota_t->posXf < datos_t->ObsX2)
		{
			t = (datos_t->ObsX2 - datospelota_t->posX0) / datospelota_t->velocidadX0;
            if(t<0.0)
            {
                t=0.0;
            }
			if ((datospelota_t->posY0 + datospelota_t->velocidadY0 * t - (1.0/2.0) * G * pow(t, 2.0))+ 0.1 > datos_t->ObsY1 &&
				(datospelota_t->posY0 + datospelota_t->velocidadY0 * t - (1.0/2.0) * G * pow(t, 2.0))+ 0.1 < datos_t->ObsY2)
			{
				datospelota_t->posX0 = datos_t->ObsX2;
				datospelota_t->posY0 = datospelota_t->posY0 + datospelota_t->velocidadY0 * t -
					(1.0/2.0) * G * pow(t, 2.0);

				datospelota_t->velocidadY0 = (datospelota_t->velocidadY0 - G * t);

				datospelota_t->time -= round(t * 1000.0);

				datospelota_t->velocidadY0 = (datospelota_t->velocidadY0 * (1.0 - datos_t->AlphaY / 100.0));
				datospelota_t->velocidadX0 = -(datospelota_t->velocidadX0 * (1.0 - datos_t->AlphaX / 100.0));

				if (datos_t->PATH)
				{
					gotoxy(round(datos_t->ObsX2 / datos_t->SCALE) , round(50.0 - datospelota_t->posY0 / datos_t->SCALE));
					cprintf("%c", 254);
				}

				guardarcirculo(datos_t->ObsX2 / datos_t->SCALE, datospelota_t->posY0 / datos_t->SCALE, (datos_t->D / (2.0 * datos_t->SCALE)));

				datospelota_t->posXf = datospelota_t->posX0 + datospelota_t->velocidadX0 * (datospelota_t->time / 1000.0);

				datospelota_t->posYf = datospelota_t->posY0 + datospelota_t->velocidadY0 * (datospelota_t->time / 1000.0) -
					(1.0/2.0) * G * pow((datospelota_t->time / 1000.0), 2.0);
            }
		}
        
		// Colision techo
		if (posXa >= datos_t->ObsX1 && posXa <= datos_t->ObsX2 && posYa > datos_t->ObsY1 && datospelota_t->posYf < datos_t->ObsY2)
		{
			datospelota_t->velocidadYf = -sqrt(pow(datospelota_t->velocidadY0, 2.0) - 2.0 * G * (datos_t->ObsY2 - datospelota_t->posY0));

			t = (datospelota_t->velocidadY0 - datospelota_t->velocidadYf) / G;

			if (((datospelota_t->posX0 + datospelota_t->velocidadX0 * t) > datos_t->ObsX1 &&
				(datospelota_t->posX0 + datospelota_t->velocidadX0 * t) < datos_t->ObsX2))
			{
				if (t < 0.001)
				{
					datospelota_t->time -= round(t * 1000.0);
					datospelota_t->posX0 = datospelota_t->posX0 + datospelota_t->velocidadX0 * t;
				}

				else
				{
					datospelota_t->time = 0.0;
					datospelota_t->posX0 = datospelota_t->posXf;
				}

				datospelota_t->posY0 = datos_t->ObsY2;

				datospelota_t->velocidadY0 = -((datospelota_t->velocidadYf) * (1.0 - datos_t->AlphaY / 100.0));
				datospelota_t->velocidadX0 = ((datospelota_t->velocidadX0) * (1.0 - datos_t->AlphaX / 100.0));

				if (datos_t->PATH)
				{
					gotoxy(round(1.0 + datospelota_t->posX0 / datos_t->SCALE), round(50.0 - (datos_t->ObsY2 / datos_t->SCALE)));
					cprintf("%c", 254);
				}

				guardarcirculo(datospelota_t->posX0 / datos_t->SCALE, datos_t->ObsY2 / datos_t->SCALE, (datos_t->D / (2.0 * datos_t->SCALE)));

				datospelota_t->posXf = datospelota_t->posX0 + datospelota_t->velocidadX0 * datospelota_t->time / 1000.0;
				datospelota_t->posYf = datospelota_t->posY0 + datospelota_t->velocidadY0 * datospelota_t->time / 1000.0 - (1.0 / 2.0)
					* G * pow(datospelota_t->time / 1000.0, 2.0);
			}
		}
		// Colision piso
		if (posYa < datos_t->ObsY1 && datospelota_t->posYf > datos_t->ObsY1)
		{
			datospelota_t->velocidadYf = sqrt(pow(datospelota_t->velocidadY0, 2.0) - 2.0 * G * (datos_t->ObsY1 - datospelota_t->posY0));

			t = (datospelota_t->velocidadY0 - datospelota_t->velocidadYf) / G;

			if ((datospelota_t->posX0 + datospelota_t->velocidadX0 * t) > datos_t->ObsX1 &&
				(datospelota_t->posX0 + datospelota_t->velocidadX0 * t) < datos_t->ObsX2)
			{
				datospelota_t->time -= round(t * 1000.0);

				datospelota_t->posX0 = datospelota_t->posX0 + datospelota_t->velocidadX0 * t;

				datospelota_t->posY0 = datos_t->ObsY1;

				datospelota_t->velocidadY0 = -((datospelota_t->velocidadYf) * (1.0 - datos_t->AlphaY / 100.0));
				datospelota_t->velocidadX0 = ((datospelota_t->velocidadX0) * (1.0 - datos_t->AlphaX / 100.0));

				if (datos_t->PATH)
				{
					gotoxy(round(1.0 + datospelota_t->posX0 / datos_t->SCALE), round(50.0 - (datos_t->ObsY1 / datos_t->SCALE)));
					cprintf("%c", 254);
				}

				guardarcirculo(datospelota_t->posX0 / datos_t->SCALE, datos_t->ObsY1 / datos_t->SCALE, (datos_t->D / (2.0 * datos_t->SCALE)));

				datospelota_t->posXf = datospelota_t->posX0 + datospelota_t->velocidadX0 * datospelota_t->time / 1000.0;
				datospelota_t->posYf = datospelota_t->posY0 + datospelota_t->velocidadY0 * datospelota_t->time / 1000.0 - (1.0 / 2.0)
					* G * pow(datospelota_t->time / 1000.0, 2.0);
            }
		}
    }
    // Control de detension de la pelota
	if ((sqrt(pow(datospelota_t->velocidadY0, 2.0) + pow(datospelota_t->velocidadX0, 2.0)) < 0.1) &&
		(datospelota_t->posY0 < 0.2 || datospelota_t->posY0 <= datos_t->ObsY2))
	{
		datos_t->STATUS = false;

		datospelota_t->posYf = 0.0;

		mostrarposicionpelota(datospelota_t, datos_t);

		mostrarBMP();
        
        dibujar();
        
	}     
}

//Funcion que me muestra la posicion de la pelota en la pantalla
void mostrarposicionpelota(struct datospelota *datospelota_t, struct datos *datos_t)
{   
         
    textcolor(WHITE);
    textbackground(BLUE);
    gotoxy(round(1.0+datospelota_t->posXf/datos_t->SCALE),round(50.0-datospelota_t->posYf/datos_t->SCALE));  
    cprintf("%c",254);        
}


void escribirBMP (void)
{
    int i,j,k;
    //Cabecera del BMP
    int file = open("Ploteo.bmp", O_CREAT | O_RDWR | O_TRUNC | O_TEXT, S_IREAD | S_IWRITE);
    cabeceraBMP[0] = 0x42;
	cabeceraBMP[1] = 0x4D;
	cabeceraBMP[2] = 0x36;
	cabeceraBMP[3] = 0xF2;
	cabeceraBMP[4] = 0x2B;
	cabeceraBMP[5] = 0x00;
	cabeceraBMP[6] = 0x00;
	cabeceraBMP[7] = 0x00;
	cabeceraBMP[8] = 0x00;
	cabeceraBMP[9] = 0x00;
	cabeceraBMP[10] = 0x36;
	cabeceraBMP[11] = 0x00;
	cabeceraBMP[12] = 0x00;
	cabeceraBMP[13] = 0x00;
	cabeceraBMP[14] = 0x28;
	cabeceraBMP[15] = 0x00;
	cabeceraBMP[16] = 0x00;
	cabeceraBMP[17] = 0x00;
	cabeceraBMP[18] = 0xB0;
	cabeceraBMP[19] = 0x04;
	cabeceraBMP[20] = 0x00;
	cabeceraBMP[21] = 0x00;
	cabeceraBMP[22] = 0x20;
	cabeceraBMP[23] = 0x03;
	cabeceraBMP[24] = 0x00;
	cabeceraBMP[25] = 0x00;
	cabeceraBMP[26] = 0x01;
	cabeceraBMP[27] = 0x00;
	cabeceraBMP[28] = 0x18;
	cabeceraBMP[29] = 0x00;
	cabeceraBMP[30] = 0x00;
	cabeceraBMP[31] = 0x00;
	cabeceraBMP[32] = 0x00;
	cabeceraBMP[33] = 0x00;
	cabeceraBMP[34] = 0x00;
	cabeceraBMP[35] = 0x00;
	cabeceraBMP[36] = 0x00;
	cabeceraBMP[37] = 0x00;
	cabeceraBMP[38] = 0x10;
	cabeceraBMP[39] = 0x27;
	cabeceraBMP[40] = 0x00;
	cabeceraBMP[41] = 0x00;
	cabeceraBMP[42] = 0x00;
	cabeceraBMP[43] = 0x00;
	cabeceraBMP[44] = 0x00;
	cabeceraBMP[45] = 0x00;
	cabeceraBMP[46] = 0x00;
	cabeceraBMP[47] = 0x00;
	cabeceraBMP[48] = 0x00;
	cabeceraBMP[49] = 0x00;
	cabeceraBMP[50] = 0x00;
	cabeceraBMP[51] = 0x00;
	cabeceraBMP[52] = 0x00;
	cabeceraBMP[53] = 0x00;
   
	lseek(file, 0, SEEK_SET);

	write(file, &cabeceraBMP, sizeof(char) * 54);

	write(file, &BMP, sizeof(BMP));
    close(file);
}

//Funcion que me carga las posiciones de la pelotita en la matriz para el Bmp.
void guardarcirculo(double posX, double posY, double radio)
{
    double angle, r;

	posX = posX * (1200.0 / 79.0);
	posY = posY * (800.0 / 44.0);

	for (r = radio ; r >= 0 ; r-=1)
	{
		for (angle = 0.0 ; angle < 360 ; angle+=1)
		{
			if (posY + r * sin(angle) > 0.0 && posY + r * sin(angle) < 800.0 && posX + r * cos(angle) > 0.0 && posX + r * cos(angle) < 1200.0)
			{
				BMP[trunk(posY + r * sin(angle))][trunk(posX + r * cos(angle))][0] = 0x00;
				BMP[trunk(posY + r * sin(angle))][trunk(posX + r * cos(angle))][1] = 0x00;
				BMP[trunk(posY + r * sin(angle))][trunk(posX + r * cos(angle))][2] = 0x00;
			}
		}
	}

}

int trunk(double numero)
{
	return floor(numero);
}

void imprimirobstaculo(struct  datos *datos_t)                                                
{
    int i, j, k, l;

	if (datos_t->OBSTACULO)
	{
		textbackground(GREEN);
		textcolor(GREEN);
        for (k = round(datos_t->ObsX1 * (1200.0 / (79.0 * datos_t->SCALE))); k < round(datos_t->ObsX2 * (1200.0 / (79.0 * datos_t->SCALE))) ; k++)
		{
			for (l = round(datos_t->ObsY1 * (800.0 / (44.0 * datos_t->SCALE))) ; l < round(datos_t->ObsY2 * (800.0 / (44.0 * datos_t->SCALE))) ; l++)
			{
				BMP[l][k][0] = 0x00;
				BMP[l][k][1] = 0xFF;
				BMP[l][k][2] = 0x00;
			}
		}       
	}

	else
	{
		textbackground(BLUE);
		textcolor(BLUE);
	}

	for (i = datos_t->ObsX1 / datos_t->SCALE ; i <= datos_t->ObsX2 / datos_t->SCALE ; i++)
	{
		for (j = datos_t->ObsY1 / datos_t->SCALE ; j <= datos_t->ObsY2 / datos_t->SCALE ; j++)
		{
			gotoxy(round(1.0 + i) , round(50.0 - j));
			cprintf(" ");
		}
	}
}                        

void restablecerBMP(void)
{
    int i, j;

    // Inicializo el bmp
	for (i = 0 ; i < 800 ; i++)
	{
		for (j = 0 ; j < 1200 ; j++)
		{
			BMP[i][j][0] = 0xFF;
			BMP[i][j][1] = 0xFF;
			BMP[i][j][2] = 0xFF;
		}
	}
}

//Funcion de redondeo
int round (double numero)
{
    return floor(numero + 0.5);
} 

//Mostrar e BMP
void mostrarBMP(void)
{
        // Se escribe el bmp
	    gotoxy(47,5);
	    printf("Imprimiendo bmp");
        escribirBMP();
        gotoxy(47,5);
	    printf("BMP impreso bmp");  
        system("Ploteo.bmp");  
        restablecerBMP();
} 