/*
 * Registro.h
 *
 *  Created on: 13 ago. 2021
 *      Author: isrev
 */
#include <SdFat.h>
#include "Macros.h"
#include "Fecha.h"
#include <SoftwareSerial.h>
#include "Pantalla.h"

extern Fecha fecha;
extern ConfigSystem configSystem;
extern SoftwareSerial bluetooh;
extern Pantalla pantalla;
extern void watchDog();

#ifndef SOURCE_REGISTRO_H_
#define SOURCE_REGISTRO_H_

class Registro {
private:
	//File fichero;
	SdFat sd;
	SdFile file;
	String insertSql;

public:
	Registro();
	void iniciar();
	void registrarEvento(char descripcion[190]);
	void registrarEventoSQL();
	bool mostrarRegistro(char archivo[20], bool download = false);
	bool truncateRegistro(char archivo[20]);

	String& getInsertSql();
	void setInsertSql(const String &insertSql);
};

#endif /* SOURCE_REGISTRO_H_ */
