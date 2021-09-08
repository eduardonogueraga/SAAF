/*
 * Autenticacion.cpp
 *
 *  Created on: 27 jul. 2021
 *      Author: isrev
 */

#include "Autenticacion.h"

Autenticacion::Autenticacion() {
	// TODO Auto-generated constructor stub

}

String Autenticacion::getEntradaTeclado(){
	return this->entradaTeclado;
}

void Autenticacion::comprobarEntrada(){

	this->passwordCacheada = this->comprobarClave(this->entradaTeclado);


	if (key != NO_KEY){
		//Serial.println(key);
		if(entradaTeclado.length() < 4){
			construirEntrada(key);

		}else{
			this->limpiarEntrada();
		}
	}

}

void Autenticacion::construirEntrada(char key){

	if(!(key == '*' || key == '#')){

		lcd_clave_tiempo = millis() + 2000; //Margen para clave
		//chekear que esta en estado clave
		this->entradaTeclado = this->entradaTeclado + key;
		Serial.println("(Entrada:" + this->entradaTeclado + ") ");
	}else {
		lcd_info_tiempo = millis(); //Skipea los alerts
	}

}

bool Autenticacion::comprobarClave(String clave){
	return clave == password;
}

bool Autenticacion::isPasswordCached(){
	return this->passwordCacheada == true;
}

void Autenticacion::limpiarEntrada(){
	this->entradaTeclado = "";
}
