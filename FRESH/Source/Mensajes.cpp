/*
 * Mensajes.cpp
 *
 *  Created on: 06 ago. 2020
 *      Author: isrev
 *
 */

#include "Mensajes.h"
#include "Datos.h"
#include <SoftwareSerial.h>
#include "Env.h"

Mensajes::Mensajes(){
	this->tipoMensaje = SMS_TIPO_SALTO;
}

void Mensajes::inicioSIM800(SoftwareSerial &SIM800L){
	SIM800L.begin(9600); 					//Inicializamos la segunda comunicacion Serial.
	SIM800L.println("AT+CMGF=1"); 			//Vamos utilizar los SMS.
	delay(100);
	SIM800L.println("AT+CNMI=1,2,0,0,0"); 	//Configurar el SIM800L p/ que muestre msm por com. serie.
 }

void Mensajes::mensajeAlerta(Datos &datos){
	this->tipoMensaje = SMS_TIPO_SALTO;
	this->asuntoMensaje = this->asuntoAlerta(datos);
	this->cuerpoMensaje = datos.imprimeDatos();

	this->pieMensaje = "Intentos restantes: "+ (String)(3-INTENTOS_REACTIVACION);
	if(flagPuertaAbierta)
		this->pieMensaje += "\nLa puerta esta abierta";

	pieFechaBateria();
	this->enviarSMS();

	insertQuery(&sqlMensajes);
	insertQuery(&sqlUpdateSalto);
}

void Mensajes::mensajeReactivacion(Datos &datos){

	this->tipoMensaje = SMS_TIPO_INFO;
	this->asuntoMensaje = "ALARMA REACTIVADA CON EXITO";
	this->cuerpoMensaje = datos.imprimeDatos();
	this->pieMensaje = "";

	pieFechaBateria();

	this->enviarSMS();
	insertQuery(&sqlMensajes);
	insertQuery(&sqlUpdateEntrada);
}


void Mensajes::mensajeError(Datos &datos){

	this->tipoMensaje = SMS_TIPO_ERROR;
	switch(codigoError){

	case ERR_FALLO_ALIMENTACION:

		if(datos.comprobarDatos()){
			this->asuntoMensaje = "MOVIMIENTO DETECTADO Y SABOTAJE EN LA ALIMENTACION";
		}else{
			this->asuntoMensaje = "FALLO EN LA ALIMENTACION PRINCIPAL";
		}
		break;


	case ERR_FALLO_SENSOR:
		//
		break;
	}

	this->cuerpoMensaje = datos.imprimeDatos();

	pieFechaBateria();

	this->enviarSMSEmergencia();
	insertQuery(&sqlMensajes);
	insertQuery(&sqlUpdateErrores);
}

void Mensajes::enviarSMS(){

	if(!MODO_DEFAULT)
		return;

	procesarSMS();

	insertQuery(&sqlSmsIntentosRealizados);

}

void Mensajes::enviarSMSEmergencia(){

	if(!MODO_DEFAULT)
		return;

	if(EEPROM.read(EE_MENSAJE_EMERGENCIA) == 1)
	return;

	/*Serial.println(this->asuntoMensaje+"\n");
	Serial.println(this->cuerpoMensaje);
	Serial.println(this->pieMensaje);*/

	procesarSMS();
	EEPROM.update(EE_MENSAJE_EMERGENCIA, 1);

}

void Mensajes::procesarSMS(){


	if(EEPROM.read(MENSAJES_ENVIADOS) >= LIMITE_MAXIMO_SMS){
		Serial.println(F("Intentos diarios acabados")); //No se enviaran mas mensajes


		if(configSystem.MODULO_RTC){
			insertQuery(&sqlSmsIntentosAcabados);
		}

		return;
	}

	SIM800L.println("AT+CMGF=1");
	delay(200);
	SIM800L.println("AT+CMGS=\"+34"+(String)telefonoPrincipal+"\"");
	delay(200);

	Serial.print(this->asuntoMensaje+"\n");//@develop
	Serial.println(this->cuerpoMensaje);//@develop
	Serial.println(this->pieMensaje);//@develop

	delay(200);
	SIM800L.print((char)26);
	delay(200);
	SIM800L.println("");
	delay(200);


	mensajesEnviados++;

	configSystem.SMS_HISTORICO++;
	EEPROM_SaveData(EE_CONFIG_STRUCT, configSystem);
	EEPROM.update(MENSAJES_ENVIADOS, (EEPROM.read(MENSAJES_ENVIADOS)+1));
}

void Mensajes::llamarTlf(char* tlf){

	if(!MODO_DEFAULT)
	return;

	if(EEPROM.read(MENSAJES_ENVIADOS) >= (LIMITE_MAXIMO_SMS-7)){
		Serial.println(F("Intentos diarios acabados")); //No se haran mas llamadas
		return;
	}


	Serial.println("Llamando "+(String)tlf);
	SIM800L.println("AT");
	delay(200);
	SIM800L.println("ATD+ +34"+(String)tlf+';');
	delay(200);
}

void Mensajes::colgarLlamada(){
	Serial.println("Llamada finalizada");
	SIM800L.println("ATH");
}

String Mensajes::asuntoAlerta(Datos &datos){

	int* mapSensor= datos.getDatos();
	cont=0; //Reinicia el contador

	for (int i = 0; i < 4; i++) { //TODO enlaza con tam el tamano de los array

		if(mapSensor[i] == MAX_SALTO[i]) {
			//Salto principal
			asuntoMensaje = "AVISO ALARMA:";
			if(nombreZonas[i] == ("PUERTA COCHERA")) {
				asuntoMensaje += " PUERTA ABIERTA EN COCHERA";
			}else {
				asuntoMensaje += " MOVIMIENTO DETECTADO EN "+nombreZonas[i];
			}

			for (int j= 0; j < 4; j++) {
				if((mapSensor[j] != 0)&&(mapSensor[j] != MAX_SALTO[j])) {
					//Saltos secundarios

					if(cont == 0) {
						asuntoMensaje += " JUNTO CON MOVIMIENTO EN "+nombreZonas[j];
						cont++;

					}else {
						asuntoMensaje += " Y "+nombreZonas[j];
					}
				}
			}
		}
	}

	return asuntoMensaje;
}

void Mensajes::pieFechaBateria(){
	if(configSystem.MODULO_RTC)
		this->pieMensaje = fecha.imprimeFecha();

	if(digitalRead(SENSOR_BATERIA_RESPALDO) == LOW){
		this->pieMensaje += " Bateria de emergencia desactivada";
	}
}


const String& Mensajes::getAsuntoMensaje() const {
	return asuntoMensaje;
}

const String& Mensajes::getCuerpoMensaje() const {
	return cuerpoMensaje;
}

byte  Mensajes::getTipoMensaje() const {
		return tipoMensaje;
	}
