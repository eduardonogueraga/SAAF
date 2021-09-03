/*
 * Datos.h
 *
 *  Created on: 23 jun. 2020
 *      Author: isrev
 */

#ifndef PROYECTO_DATOS_H_
#define PROYECTO_DATOS_H_
#include "Arduino.h"

class Datos {

private:

	static const int tam = 4;
	int* idSensor = new int[tam];  //Puntero idSensor a un array del mismo nombre de dimension tam creado en el heap

public:

	Datos();
	virtual ~Datos();

	int getTam();
	void setDatos(int indice, int dato);
	int* getDatos();
	String imprimeDatos();
	bool comprobarDatos();
	void borraDatos();
};

#endif /* PROYECTO_DATOS_H_ */
