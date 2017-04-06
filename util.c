/*
 *  util.c
 *
 *  Created on: 28/03/2017
 *  Author: Diego Fernando Ruiz
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include "util.h"
 
 void error(const char *s){
  /* perror() devuelve la cadena S y el error (en cadena de caracteres) que tenga errno */
  perror (s);
  exit(EXIT_FAILURE);
}


int contarArchivos(const char *ruta){
	/* Con un puntero a DIR abriremos el directorio */
	DIR *dir;
	/* en *ent habr‡ informaci—n sobre el archivo que se est‡ "sacando" a cada momento */
    struct dirent *ent;
	int num_archivos = 0;
	/* Empezaremos a leer en el directorio actual */
	dir = opendir(ruta);
	/* Miramos que no haya error */
	if (dir == NULL)
	    error("No puedo abrir el directorio");
	/* Una vez nos aseguramos de que no hay error, Ávamos a jugar! */
	/* Leyendo uno a uno todos los archivos que hay */
	while((ent = readdir (dir)) != NULL){
		if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) ){
		      /* Una vez tenemos el archivo, lo contamos */
		    	  if(ent->d_type != DT_DIR)
		    		  num_archivos ++;
		}
	}
	closedir(dir);
	return num_archivos;
}

char **buildArray (const char *ruta, int numero_archivos){
	  /* Con un puntero a DIR abriremos el directorio */
	  DIR *dir;
	  /* en *ent habr‡ informaci—n sobre el archivo que se est‡ "sacando" a cada momento */
      struct dirent *ent;
	  char **array = malloc (numero_archivos*sizeof(char *));
	  if (!array)
		return NULL;

	  //Empezaremos a leer en el directorio actual
	  dir = opendir(ruta);
	  //Miramos que no haya error
	  if (dir == NULL)
		error("No puedo abrir el directorio");
	  //Una vez nos aseguramos de que no hay error, Ávamos a jugar!
	  //Leyendo uno a uno todos los archivos que hay
	  int j=0;
	  while((ent = readdir (dir)) != NULL){
		if ((strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..") != 0)){
		   //Una vez tenemos el archivo, lo asignamos a una fila de la matriz, con un l’mite de car‡cteres
		   if(ent->d_type != DT_DIR){
			   array[j] = (char *)malloc(strlen(ent->d_name)*sizeof(char*));
			   strcpy (array[j], ent->d_name);
			   j++;
		   }
		}
	  }
	  //cerramos el directorio
	  closedir(dir);
	  return array;
}

//Funcion que abre un archivo y evalua su peso.
int pesoFichero(const char * ruta ){
	 int peso = 0;
	FILE *fich;
    fich=fopen(ruta,"rb");
    while(fgetc(fich) != EOF){
		peso ++;
	}
    fclose(fich);
	return peso;
}

//Funcion que calcula la totalidad del peso de los archivos que hay dentro de un directorio.
void calculoSinFork(char **matrizNombres, int numeroNombres, const char *ruta){
	long pesoTotal = 0;
	int i=0;
	for(i=0; i<numeroNombres; i++){
	   char  ruta_temp[strlen(ruta)+1+strlen(matrizNombres[i])];
	   strcpy(ruta_temp, ruta);
	   strcat(ruta_temp, "/");
	   strcat(ruta_temp, matrizNombres[i]);
	   int peso = pesoFichero(ruta_temp);
	   pesoTotal = pesoTotal + peso;
	   //printf ("archivo %d: %s - su peso es %d bytes\n", i, matrizNombres[i], peso);
    }
	printf("Total bytes: %ld \n", pesoTotal );
}

void calculoConFork(char **matrizNombres, int numeroNombres, const char *ruta){
	long i, pesoTotal;
	int length = numeroNombres;
	int pid;
	int fd[2];
	pesoTotal = 0;
	pipe(fd);
	
	if ((pid = fork())) {
		long pesoTotalh;
		close(fd[1]);
		for ( i = 0; i < (length/2); i++){
		   char  ruta_temp[strlen(ruta)+1+strlen(matrizNombres[i])];
		   strcpy(ruta_temp, ruta);
		   strcat(ruta_temp, "/");
		   strcat(ruta_temp, matrizNombres[i]);
		   pesoTotal = pesoTotal + pesoFichero(ruta_temp);
		}
		//printf("El proceso [%d] conto %d bytes\n",getpid(),pesoTotal);
		//printf("Esperando por el proceso %d\n",pid);
		read(fd[0],&pesoTotalh,sizeof(pesoTotalh));
		//printf("Peso total: (%d + %d) bytes = %d bytes\n", pesoTotalh, pesoTotal, pesoTotalh + pesoTotal);
		close(fd[0]);
		printf("Total bytes: %ld \n", pesoTotalh + pesoTotal );
	} else {
		close(fd[0]);
		for ( i = length/2; i < length; i++){
			char  ruta_temp[strlen(ruta)+1+strlen(matrizNombres[i])];
		    strcpy(ruta_temp, ruta);
		    strcat(ruta_temp, "/");
		    strcat(ruta_temp, matrizNombres[i]);
		    pesoTotal = pesoTotal + pesoFichero(ruta_temp);
		}
		//printf("El proceso [%d] conto %d bytes\n",getpid(),pesoTotal);
		write(fd[1],&pesoTotal,sizeof(pesoTotal));
		close(fd[1]);
	}
}
