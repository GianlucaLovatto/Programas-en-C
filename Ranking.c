#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE* fd; 
char direcciones []= "C:\\Users\\gianluca\\Desktop\\Archivo\\Ranking.txt";  

struct datosjugadores {
	char nombre [10]; 
	char apellido [10]; 
	char equipo [15]; 
	char goles [3];
	char asistencia [3];
	 
}datos;

void crear (){
	int repetir; 
	fd=fopen(direcciones, "wt");
	if(fd==NULL){
		printf("\n Error al tratar de crear el archivo \n");
	}
	printf ("Creando Nueva Lista"); 
	do{
	fflush (stdin); 
	printf ("\nNombre: ");gets(datos.nombre);
	printf ("\nApellido: "); gets(datos.apellido);
	printf("\nEquipo: "); gets (datos.equipo); 
	printf("\nGoles: "); gets (datos.goles);
	printf("\nAsistencias: "); gets(datos.asistencia);
	//Escribir los datos al Archivo. 
	fprintf(fd,"Nombre: "); 
	fwrite(datos.nombre,1,strlen(datos.nombre),fd); 
	fprintf (fd,"\nApellido: "); 
	fwrite(datos.apellido,1,strlen(datos.apellido),fd); 
	fprintf(fd,"\nEquipo: "); 
	fwrite(datos.equipo,1,strlen(datos.equipo),fd);
	fprintf(fd,"\nGoles: "); 
	fwrite(datos.goles,1,strlen(datos.goles),fd);
	fprintf(fd,"\nAsistencias: ");
	fwrite(datos.asistencia,1,strlen(datos.asistencia),fd);
	//Condicion de salida.   
	printf ("Para dejar de introducir datos precione 1 \n"); 
	scanf ("%i",&repetir);
}while(repetir != 1);
fclose(fd);
}

void agregar (){
	int repetir; 
	fd=fopen(direcciones, "at");
	if(fd==NULL){
		printf("Error al tratar de crear el archivo");
	}
	printf("Agregando jugadores a Lista"); 
	do{
	fflush (stdin); 
	printf ("\nNombre: ");gets(datos.nombre);
	printf ("\nApellido: "); gets(datos.apellido);
	printf("\nEquipo: "); gets(datos.equipo); 
	printf("\nGoles: "); gets (datos.goles);
	printf("\nAsistencias: "); gets(datos.asistencia);
	//Escribir los datos al Archivo 
	fprintf(fd,"Nombre: "); 
	fwrite(datos.nombre,1,strlen(datos.nombre),fd); 
	fprintf (fd,"\nApellido: "); 
	fwrite(datos.apellido,1,strlen(datos.apellido),fd); 
	fprintf(fd,"\nEquipo: "); 
	fwrite(datos.equipo,1,strlen(datos.equipo),fd);
	fprintf(fd,"\nGoles: "); 
	fwrite(datos.goles,1,strlen(datos.goles),fd);
	fprintf(fd,"\nAsistencias: ");
	//Condicion de salida.
	fwrite(datos.asistencia,1,strlen(datos.asistencia),fd);
	printf ("Para dejar de introducir datos precione 1\n"); 
	scanf ("%i",&repetir);
}while(repetir != 1);
fclose(fd);
}
//Tomo el archivo creado y con la funcion fgetc () leeo todo su contenido 
//fgetc(puntero,archivo)
void visualizar (){
	int c; 
	fd=fopen (direcciones,"rt"); //read text "leer el texto". 
	if(fd==NULL){
		printf ("Error al abrir el archivo");
	}
	//bucle que se repetira hasta que el puntero sea igual a EOF final de archivo. En c se almacena caracter a caracter y tengo que saber si hay saltos de linea  
	//putchar (c);
	while((c=fgetc(fd))!=EOF){
		if(c=='\n'){
			printf("\n");
		}else{
			putchar(c); 
		}
	}
	fclose(fd); 
}
int main (){
int opc;
printf("Ranking de Goles y Asistencias"); 
	do{
		printf("\n\t.:MENU:.\n");
		printf("\n1. Crear nueva Lista");
		printf("\n2. Agregar a la Lista ");
		printf("\n3. Visualizar Lista existente");
		printf("\n4. Salir \n");
		printf ("Opcion: "); 
		scanf("%i",&opc);
		switch(opc){
			case 1: crear();break;
			case 2: agregar();break;
			case 3: visualizar();break;
		}
	}while(opc != 4);
	return 0;
}
