/*
 *  main.c
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

int main(int argc, char *argv[])
{
  if(argc!=2) {
     printf("debe ingresar parametros correctos, ej: ./iofork /bin \n"); 
     exit(1);
   }
  const char * ruta = argv[1]; //Toma la ruta que llega como parametro
  int cantidad_nombres;
  cantidad_nombres = contarArchivos(ruta);
  printf("Estudiante_1: 1510074 \n");
  printf("Total archivos: %d \n", cantidad_nombres);
  char **my_array = buildArray (ruta, cantidad_nombres);
   if (!my_array) {
     printf ("ERROR: Unable to allocate my_array!\n");
     return 1;
   }
   else {
	   calculoConFork(my_array, cantidad_nombres, ruta);
   }
   return 0;
} //end main
