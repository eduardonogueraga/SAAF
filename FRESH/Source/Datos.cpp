/*
 * Datos.cpp
 *
 *  Created on: 23 jun. 2020
 *      Author: isrev
 */
#include "Arduino.h"
#include "Datos.h"

	Datos::Datos() //Se inicia cada instancia formateando el array a cero
	{
		for (int i = 0; i <tam; i++) {

			idSensor[i] = 0;
		}
	}

	Datos::~Datos()
	{}


	int Datos::getTam(){ //Envia la longitud del array
		return tam;
	}
	void Datos::setDatos(int indice, int dato){

		idSensor[indice] = dato;
	}

	int* Datos::getDatos(){

		return idSensor;  //Devuelve el puntero
	}



	String Datos::imprimeDatos(){
		String sensor[tam]={"Puerta ", "Cochera ", "Porche ", "Almacen "};
		String mapSensor="";
		for (int i = 0; i <tam; i++) {

			mapSensor += "Lectura "+ sensor[i] + ": " + (String)idSensor[i] +"\n";
		}

		return mapSensor;
	}

	bool Datos::comprobarDatos(){ //Comprueba si existen datos en la instancia

		int suma = 0;
		for (int i = 0; i <tam; i++) {
			suma += idSensor[i];
		}

		if(suma == 0){
			return false;
		}else{
			return true;
		}
	}


	void Datos::borraDatos(){

		for (int i = 0; i <tam; i++) {

			idSensor[i] = 0;
		}

	}
