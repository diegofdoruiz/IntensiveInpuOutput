/*
 *  util.h
 *
 *  Created on: 28/03/2017
 *  Author: Diego Fernando Ruiz
 */

#ifndef UTIL_H_
#define UTIL_H_

	void error(const char *s);
	int contarArchivos(const char *ruta);
	char **buildArray (const char *ruta, int numero_archivos);
	int pesoFichero(const char * ruta);
	void calculoSinFork(char **matrizNombres, int numeroNombres, const char *ruta);
	void calculoConFork(char **matrizNombres, int numeroNombres, const char *ruta);

#endif /* UTIL_H_ */
