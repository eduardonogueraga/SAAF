/*
 * InterStrike.cpp
 *
 *  Created on: 23 jun. 2020
 *      Author: isrev
 */
#include "Arduino.h"
#include "InterStrike.h"
#include "Datos.h"


	InterStrike::InterStrike(byte numero, byte max, Datos &datos, long tiempoCeguera, long tiempoExposicion, long tiempoStrikeFondo)
	{
		this->numero = numero;
		this->max = max;
		this->datos = datos;
		this->tiempoCeguera = tiempoCeguera;
		this->tiempoExposicion = tiempoExposicion;
		this->tiempoStrikeFondo = tiempoStrikeFondo;
	}

	int InterStrike::getStrike(){
		return strike;
	}

	int InterStrike::matarStrike(){
		strike =0;
		return strike;
	}

	int InterStrike::matarStrikeFondo(){
		strikeFondo=0;
		return strikeFondo;
	}

	void InterStrike::pingSensor(){
		gotoPing = 1;
	}

	void InterStrike::setStart(){  //Evita que se cargen strikes antes de tiempo
		matarStrike();
		matarStrikeFondo();
	}

	void InterStrike::compruebaEstado(bool sensor){

		this->sensor = sensor;

		if(gotoPing==1){ //Control serie
			goto ping;
			gotoPing=0;
		}


		if(millis()>tiempoBase){
			if (sensor && !sensorant) {
				ping:
				gotoPing=0;
				if(configSystem.SENSORES_HABLITADOS[this->numero]){
					tiempoBase = millis()+tiempoCeguera;
					if(strike==0){
						tiempoBaseAux = millis()+tiempoExposicion+tiempoCeguera;
					}
					strike++;
					Serial.print("\nSignal strike ");
					Serial.print(this->numero);
					Serial.print(": ");
					Serial.println(strike);
					insertQuery(&sqlSensorEstandar, ("PIR"+(String)(this->numero)), "ONLINE");
					insertQuery(&sqlSalto);

					if(!MODO_DEFAULT)
					bocina.bocinaAlert();

				} else {
					Serial.print("\nSensor ");
					Serial.print(this->numero);
					Serial.print(" deshabilitado");
					insertQuery(&sqlSensorEstandar, ("PIR"+(String)(this->numero)), "OFFLINE");
					insertQuery(&sqlSalto);

				}
			}

			sensorant = sensor;
		}

		if((millis()>tiempoBaseAux) ){

			if(strike > 0){

				if(strikeFondo==0){
					//tiempoFondo = millis()+80000;
					tiempoFondo = millis()+tiempoStrikeFondo;
				}
				strikeFondo++;
				matarStrike();
				Serial.print("\nEliminar strike ");
				Serial.print(this->numero);
				Serial.print(": ");
				Serial.println(strike);
			}

		}

		if((millis()>tiempoFondo) ){
			strikeFondo= matarStrikeFondo();

		}

	}

	void InterStrike::compruebaEstadoMG(bool sensor){

		this->sensor = sensor;

		if(gotoPing==1){ //Control serie
			goto ping;
			gotoPing=0;
		}

		if(millis()>tiempoMargen){
			if (sensor == LOW) { // @develop("Cambiado a LOW para evitar saltos en sensor MG")
				ping:
				gotoPing=0;
				if(configSystem.SENSORES_HABLITADOS[this->numero]){
					if(strike==0){
						strike++;
						Serial.print("\nSignal strike MG");
						insertQuery(&sqlSensorEstandar, "PUERTA COCHERA", "ONLINE");
						insertQuery(&sqlSalto);
					}
				}
			}
		}
	}


	bool InterStrike::disparador(){

		int auxStrike = this->strike;

		if(this->strike < this->max){
			datos.setDatos(this->numero, this->strike);
		}

		if (this->strike == this->max) {

			datos.setDatos(this->numero, this->strike);

			strike=matarStrike();
			strikeFondo= matarStrikeFondo();

			Serial.print("\nSignal PIR");
			Serial.println(this->numero);
			Serial.print("\nEliminar strike ");
			Serial.print(this->numero);
			Serial.print(": ");
			Serial.println(this->strike);

		}

		if(strikeFondo>this->max){ //Cambiado 2 por el maximo

			auxStrike = this->max;
			datos.setDatos(this->numero, 1);
			strikeFondo= matarStrikeFondo();
			strike=matarStrike();
			Serial.print("\nStirke fondo");
			Serial.println(this->numero);
			Serial.print("\nSignal strike ");
			Serial.print(this->numero);
			Serial.print(": ");
			Serial.println(this->strike);

		}


		return(auxStrike == this->max)?true:false;
	}

	void InterStrike::compruebaPhantom(bool sensor, Datos &_datos){

		this->sensor = sensor;

		if(gotoPing==1){ //Control serie
			goto ping;
			gotoPing=0;
		}

		if (sensor && !sensorant) {
			ping:
			gotoPing=0;
			if(configSystem.SENSORES_HABLITADOS[this->numero]){

				if(strike <= 100){ //Saltos maximos

					strike++;
					Serial.print("\nSignal phantom ");
					Serial.print(this->numero);
					Serial.print(": ");
					Serial.println(strike);

					_datos.setDatos(this->numero, strike);
					insertQuery(&sqlSensorPhantom, ("PIR"+(String)(this->numero)), "ONLINE");
					insertQuery(&sqlSalto);
				}
			} else {
				Serial.print("\nSensor ");
				Serial.print(this->numero);
				Serial.print(" deshabilitado");
				insertQuery(&sqlSensorPhantom, ("PIR"+(String)(this->numero)), "OFFLINE");
				insertQuery(&sqlSalto);
			}
		}

		sensorant = sensor;

	}
