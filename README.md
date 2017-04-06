# Diego Fernando Ruiz - 1510074
# util.h
  El proposito de util.h es declarar las funciones que luego se van
  a implementar en el util.c
# util.c
  En el util.c se implementan las funciones:
   -contarArchivos, esta función recibe un puntero a un char que contiene 
    una ruta de acceso al directorio en el cual cuenta los archivos y luego 
    retorna un entero con ese valor.

   -buildArray, esta función recibe un puntero a un char que contiene una ruta
    a un directorio y un entero que corresponde al número total de archivos en 
    el mismo y luego contruye un doble apuntador con tantas filas como archivos 
    hayan en el directorio y las columnas si varían en tamaño de acuerdo a la 
    longitud de la palabra correspondiente a los nombres de los archivos en el 
    directorio. en conclusión, retorna un doble apuntador a una matriz de nombres
    de archivos.

   -pesoFichero, recibe un puntero a un char que contiene la ruta a un fichero,
    luego lo abre y lo recorre de byte a byte para luego retornar el número de 
    bytes en el mismo.

   -calculoSinFork, a partir de la matriz que retorna buildArray y una ruta a 
    al directorio, se concatena la ruta a cada archivo y se solicita su peso a
    pesoFichero. se acomulan todos estos pesos para luego imprimirlos en consola.

   -calculoConFork, la función es la misma de calculoSinFork, pero se parte la 
    matriz a la mitad. Luego se invoca la función fork() para generar un proceso 
    adicional, de esta forma el proceso original hace el trabajo de la mitad de
    la matriz y el nuevo proceso hace el trabajo de la otra matriz.
 #io.c
   -Este archivo contiene una función principal main(), se incluye el encabezado 
    util.h, para poder acceder a las funciones de util.c, en este caso 
    calculoSinFork. 
 #iofork.c
   -Este archivo contiene una función principal main(), se incluye el encabezado 
    util.h, para poder acceder a las funciones de util.c, en este caso 
    calculoConFork.   
 #Makefile
   Se encarga de gestionar las dependencias entre archivos, en este caso se usa para:
   limpieza de archivos temporales con la etiqueta clean.
   creación de objeto
   obj:
	gcc -c util.c -o util.o
   creación de librería
   lib:
	ar rcs libutil.a util.o
   creación de ejecutables
   io: obj lib
	gcc -static io.c -L. -I. -lutil -o io