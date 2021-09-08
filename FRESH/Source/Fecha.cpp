/*
 * Fecha.cpp
 *
 *  Created on: 16 ago. 2021
 *      Author: isrev
 */

#include "Fecha.h"

Fecha::Fecha() {
}

void Fecha::iniciarRTC(){

	if(!configSystem.MODULO_RTC)
		return;

	 if (! rtc.begin()) {
		 Serial.println("Modulo RTC no encontrado !");

		 pantallaDeErrorInicial(F("  SYSTM ERROR!  ERR INICIAR  RTC"));
		 }
		 //rtc.adjust(DateTime(__DATE__, __TIME__));  //Establecer tiempo
}

String Fecha::imprimeFecha(DateTime paramFecha){

	(paramFecha > 0)? fecha = paramFecha : fecha = rtc.now();
	char buffer[] = "DD/MM/YYYY hh:mm:ss";
	return fecha.toString(buffer);
}

String Fecha::imprimeFechaSimple(DateTime paramFecha){

	(paramFecha > 0)? fecha = paramFecha : fecha = rtc.now();
	char buffer[] = "DD/MM/YYYY";
	return fecha.toString(buffer);

}

String Fecha::imprimeFechaSQL(){
	fecha = rtc.now();
	char buffer[] = "YYYY-MM-DD hh:mm:ss";

	return fecha.toString(buffer); //@develop
	//return "2020-09-22 13:02:25";
}

String Fecha::imprimeHora(){
	fecha = rtc.now();
	char buffer[] = "hh:mm";
	return fecha.toString(buffer);
}

void Fecha::establecerFechaReset(byte dia, byte hora, byte minuto, byte segundo){

	DateTime fechaFutura (rtc.now() + TimeSpan(dia,hora,minuto,segundo));
	fechaReset = fechaFutura;

}

DateTime Fecha::getFechaReset(){
	return fechaReset;
}


bool Fecha::comprobarFecha(DateTime paramFecha){

	if(rtc.now() >= paramFecha){
		return true;
	}else{
		return false;
	}

}
bool Fecha::comprobarHora(byte horas, byte minutos){ //Hora concreta

	 fecha = rtc.now();

	if(horas == fecha.hour()){

		if (minutos == fecha.minute() || minutos == 0){

			return true;
		}else {
			return false;
		}

	}else {
		return false;
	}

}

bool Fecha::comprobarRangoHorario(byte hora_inicio, byte hora_fin,  byte min_inicio, byte min_fin){ //Rango de horas

	fecha = rtc.now();

	int aux=0;

	if(hora_inicio > hora_fin) { //Si hay diferencia entre dias entrara aqui

		if((int)fecha.hour() >= hora_inicio) {

			hora_fin = hora_fin +24; //Hasta las 12 contempla horas posteriores como mayores(+24 horas)

		}

		if((int)fecha.hour() <= 23){ //Cuando son menos de las 12 contempla la hora de inicio como inferior (-24 horas)

			hora_inicio = hora_inicio - 24;

		}

		aux = 24; //Ajusta el tiempo las primeras horas del ultimo dia
	}else {
		aux = 0;
	}


	if((int)fecha.hour() == hora_inicio+aux) {

		if(((int)fecha.hour() >= hora_inicio && (int)fecha.minute() >= min_inicio) && (hora_fin > (int)fecha.hour())) {

			return true;
		}else {
			return false;
		}


	}else if((int)fecha.hour() == hora_fin) {

		if(((int)fecha.hour() >= hora_inicio) && (hora_fin >= (int)fecha.hour() && (int)fecha.minute() < min_fin )) {

			return true;
		}else {
			return false;
		}

	}else if ((int)fecha.hour() != hora_inicio && (int)fecha.hour() != hora_fin){

		if(((int)fecha.hour() >= hora_inicio ) && (hora_fin > (int)fecha.hour())) {

			return true;
		}else {
			return false;
		}
	}else {
		return false;
	}

}
