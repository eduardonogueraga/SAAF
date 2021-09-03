/*
 * ComandoSerie.cpp
 *
 *  Created on: 29 jul. 2021
 *      Author: isrev
 */

#include "ComandoSerie.h"
#include <SoftwareSerial.h>


ComandoSerie::ComandoSerie() {
	// TODO Auto-generated constructor stub

}

void ComandoSerie::demonioSerie(){

	if (Serial.available() > 0 || bluetooh.available() > 0){

		if(Serial.available() > 0)
			data = Serial.readStringUntil('\n');

		if(bluetooh.available() > 0)
			data = bluetooh.readStringUntil('\n');


		comprobarComando();
	}

}

void ComandoSerie::comprobarComando() {

	if (data.indexOf("set on") >= 0) {

		setEstadoGuardia();
	}
	if (data.indexOf("set off") >= 0) {

		setEstadoReposo();
	}
	if (data.indexOf("set mode") >= 0) {

		if(MODO_DEFAULT){
			Serial.println("Alarma en modo de purebas");
			MODO_DEFAULT = 0;
		}else {
			Serial.println("Alarma en modo default");
			MODO_DEFAULT = 1;
		}
	}

	if (data.indexOf("menu") >= 0) {

		if(procesoCentral == ALARMA){
			procesoCentral = MENU;

			return;
		}

		if(procesoCentral == MENU){

			procesoCentral = ALARMA;
			return;
		}

	}

	if (data.indexOf("pir1") >= 0) {

		pir1.pingSensor();
	}

	if (data.indexOf("pir2") >= 0) {

		pir2.pingSensor();
	}

	if (data.indexOf("pir3") >= 0) {

		pir3.pingSensor();
	}

	if (data.indexOf("mg") >= 0) {

		mg.pingSensor();
	}

	if (data.indexOf("mail") >= 0) {

		setEstadoEnvio();
	}

	if (data.indexOf("show reg")>=0){
		registro.mostrarRegistro((char*)"REGISTRO.txt");
	}


	if (data.indexOf("show sql")>=0){
		registro.mostrarRegistro((char*)"SQL.txt");
	}

	if (data.indexOf("clear")>=0){
		registro.truncateRegistro((char*)"REGISTRO.txt");
		registro.truncateRegistro((char*)"SQL.txt");
	}

	if(data.indexOf("power")>=0){
		interrupcionFalloAlimentacion();
	}

	if(data.indexOf("d")>=0){
		Serial.println(datosSensores.imprimeDatos());
	}

}









