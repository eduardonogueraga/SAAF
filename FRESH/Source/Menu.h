/*
 * Menu.h
 *
 *  Created on: 12 ago. 2021
 *      Author: isrev
 */

#ifndef SOURCE_MENU_H_
#define SOURCE_MENU_H_

#include "Arduino.h"
#include "Macros.h"
#include "Pantalla.h"
#include "Fecha.h"
#include "Registro.h"

extern char key;
extern Pantalla pantalla;
extern Fecha fecha;
extern ProcesoCentral procesoCentral;
extern byte MODO_DEFAULT;
extern byte sensorHabilitado[];
extern byte alertsInfoLcd[];
extern SLEEPMODE_BT sleepModeBT;
extern Registro registro;
extern ConfigSystem configSystem;

extern void sonarBocina();
extern void pararBocina();
extern void setMargenTiempo(unsigned long &tiempoMargen, const unsigned long tiempo, float porcentaje);
extern unsigned long tiempoBocina;

class Menu {

private:
	EstadosMenu estadoMenu;
	MENU_CONFIG menuConfig;
	MENU_INFO menuInfo;

	MENU_CONFIG_MODULOS menuModulos;
	MENU_CONFIG_MODOS menuModos;
	MENU_CONFIG_SENSORES menuSensores;
	MENU_INFO_TIME menuInfoTime;
	MENU_INFO_DATOS menuInfoDatos;
	MENU_INFO_REGISTROS menuInfoRegistros;

	byte menuSensoresPir;
	byte timeSelector;

public:
	Menu();
	void procesoMenu();
	void configMenu();
	void infoMenu();
	void checkMenu();
	void configModos();
	void configSensores();
	void configModulos();
	void configComunicaciones();
	void modficarSensorPir(byte num);
	void infoTiempo();
	void infoDatos();
	void infoRegistro();
};

#endif /* SOURCE_MENU_H_ */
