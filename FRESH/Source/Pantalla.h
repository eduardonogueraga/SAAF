/*
 * Pantalla.h
 *
 *  Created on: 29 jul. 2021
 *      Author: isrev
 */

#ifndef SOURCE_PANTALLA_H_
#define SOURCE_PANTALLA_H_

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
#include "Autenticacion.h"
#include "InterStrike.h"
#include "Macros.h"
#include "Fecha.h"

extern byte MODO_DEFAULT;
extern const char* version[];
extern unsigned long tiempoMargen;
extern InterStrike pir1, pir2, pir3;
extern Autenticacion auth;
extern Fecha fecha;
extern String nombreZonas[];
extern byte zona;
extern byte desactivaciones, mensajesEnviados;
extern ConfigSystem configSystem;



class Pantalla {

public:
	Pantalla();
	void lcdLoadView(Pantalla *obj,void (Pantalla::*otherFunction)());
	void lcdLoadView(Pantalla *obj,void (Pantalla::*otherFunction)(byte*, char[]), byte* var, char parameter[15] = nullptr);
	void iniciar();
	void limpiarPantalla();
	void lcdInicio();
	void lcdFalloBateria();
	void lcdSensorPuertaDesconectado();
	void lcdAvisoResetAuto();
	void lcdAvisoBluetooh();
	void lcdClave();
	void lcdReposo();
	void lcdGuardia();
	void lcdAlerta();
	void lcdAvisoEnviado();
	void lcdMenu();
	void menuConfig();
	void menuConfigModulos();
	void menuConfigModos();
	void menuConfigSensores();
	void menuConfigSensoresPir();
	void menuConfigChangeMode(byte* var, char name[15]);
	void menuInfo();
	void menuInfoTiempo(byte* var, char s[15] = nullptr);
	void menuInfoSMSActual();
	void menuInfoSMSHistorico();
	void menuInfoErrHistorico();
	void menuInfoVersion();
	void menuInfoResetAuto();
	void menuInfoSMSDiario();
	void menuInfoRegistros();
	void menuInfoRegistrosBorrar();
	void menuInfoRegBorrado();
	void menuInfoRegBorradoError();
	void menuInfoRegDescargando();
	void menuInfoRegDescargandoError();
	void menuInfoBluetoohAviso();
	void menuCheck();
	void errorEmergencia();
};

#endif /* SOURCE_PANTALLA_H_ */
