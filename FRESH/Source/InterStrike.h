/*
 * InterStrike.h
 *
 *  Created on: 23 jun. 2020
 *      Author: isrev
 */

#ifndef PROYECTO_INTERSTRIKE_H_
#define PROYECTO_INTERSTRIKE_H_
#include "Arduino.h"
#include "Datos.h"
#include "Macros.h"
#include "Bocina.h"

extern unsigned long tiempoMargen;
extern ConfigSystem configSystem;
extern Bocina bocina;
extern byte MODO_DEFAULT;

class InterStrike {

private:

	byte numero, max;
	Datos datos;

	unsigned long tiempoBase = 0;
	unsigned long tiempoBaseAux=0;
	unsigned long tiempoFondo=0;
	int strike = 0;
	int strikeFondo = 0;
	bool sensor = false, sensorant = true;
	long tiempoCeguera = 5000; //default
	long tiempoExposicion = 15000; //default
	long tiempoStrikeFondo = 80000; //defult
	byte gotoPing= 0;


public:

	InterStrike(byte numero, byte max, Datos &datos, long tiempoCeguera = 5000, long tiempoExposicion = 15000, long tiempoStrikeFondo = 80000);
	int getStrike();
	int matarStrike();
	int matarStrikeFondo();
	void pingSensor();
	void setStart(); //Limpia los strikes
	void compruebaEstado(bool sensor);
	void compruebaEstadoMG(bool sensor);
	bool disparador();
	void compruebaPhantom(bool sensor, Datos &datos);



};

#endif /* PROYECTO_INTERSTRIKE_H_ */
