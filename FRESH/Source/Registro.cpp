/*
 * Registro.cpp
 *
 *  Created on: 13 ago. 2021
 *      Author: isrev
 */

#include "Registro.h"

Registro::Registro() {
	// TODO Auto-generated constructor stub

}

void Registro::iniciar(){
	if(!configSystem.MODULO_SD)
		return;

	 if (!sd.begin(REGISTRO_SS_PIN, SPI_HALF_SPEED)) Serial.println(F("ERROR AL INICIAR SD"));
	 //sd.initErrorHalt();
}


void Registro::registrarEvento(char descripcion[190]){

	if(!configSystem.MODULO_SD)
		return;

	if (!file.open("REGISTRO.txt", O_RDWR | O_CREAT | O_AT_END)) {
		//sd.errorHalt("opening test.txt for write failed");
		Serial.println(F("Error al abrir el archivo REGISTRO.txt"));
	}
	file.println(descripcion);
	file.close();
}

void Registro::registrarEventoSQL(){

	if(!configSystem.MODULO_SD)
		return;

	if (!file.open("SQL.txt", O_RDWR | O_CREAT | O_AT_END)) {
		Serial.println(F("Error al abrir el archivo SQL.txt"));
	}
	file.println(this->insertSql);
	file.close();
}

bool Registro::mostrarRegistro(char archivo[20], bool download){

	if(!configSystem.MODULO_SD)
		return false;

	if (!file.open(archivo, O_READ)) {
		Serial.println(F("El fichero esta vacio"));
		return false;
	}

	int data;

	if(download){
		pantalla.lcdLoadView(&pantalla, &Pantalla::menuInfoRegDescargando);

		while ((data = file.read()) >= 0){
			watchDog();
			bluetooh.write(data);
		}
	}else {
		while ((data = file.read()) >= 0){
			Serial.write(data);
		}
	}

	file.close();
	return true;
}

bool Registro::truncateRegistro(char archivo[20])
{
	if(!configSystem.MODULO_SD)
		return false;

	if (!file.open(archivo, O_RDWR)) {
		Serial.println(F("Error al abrir el archivo"));
		return false;
	}

	if (!file.remove()) {
		Serial.println(F("Error al eliminar el archivo"));
		return false;
	}else{
		Serial.print(F("El contenido de "));
		Serial.print(archivo);
		Serial.println(F(" ha sido eliminado"));
		return true;
	}
}


String& Registro::getInsertSql()  {
	return insertSql;
}

void Registro::setInsertSql(const String &insertSql) {
	this->insertSql = insertSql;
}
