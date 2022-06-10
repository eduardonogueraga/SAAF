/*
 * Mensajes.h
 *
 *  Created on: 23 jun. 2020
 *      Author: isrev
 *
 */

#ifndef PROYECTO_MENSAJES_H_
#define PROYECTO_MENSAJES_H_
#include "Arduino.h"
#include "Datos.h"
#include <SoftwareSerial.h>
#include <EEPROM.h>
#include "Macros.h"
#include "Env.h"
#include "Fecha.h"

extern SoftwareSerial SIM800L;
extern byte INTENTOS_REACTIVACION;
extern byte MODO_DEFAULT;
extern String nombreZonas[4];
extern byte zona;
extern byte mensajesEnviados;
extern ConfigSystem configSystem;
extern Fecha fecha;
extern CODIGO_ERROR codigoError;
extern byte flagPuertaAbierta;

class Mensajes {

private:

	byte MAX_SALTO [4] = {1,3,2,2};
	byte cont = 0;

	byte tipoMensaje;
	String asuntoMensaje = "";
	String cuerpoMensaje = "";
	String pieMensaje = "";

	String asuntoAlerta(Datos &datos);
	const byte LIMITE_MAXIMO_SMS = 15;
	void procesarSMS();

public:
	Mensajes();
	void inicioSIM800(SoftwareSerial &SIM800L);
	void enviarSMS();
	void enviarSMSEmergencia();
	void mensajeAlerta(Datos &datos);
	void mensajeReactivacion(Datos &datos);
	void mensajeError(Datos &datos);
	void llamarTlf(char* tlf);
	void colgarLlamada();
	void pieFechaBateria();
	const String& getAsuntoMensaje() const;
	const String& getCuerpoMensaje() const;
	byte getTipoMensaje() const;
};

#endif /* PROYECTO_MENSAJES_H_ */
