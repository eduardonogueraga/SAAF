/*
 * Autenticacion.h
 *
 *  Created on: 27 jul. 2021
 *      Author: isrev
 */

#ifndef AUTENTICACION_H_
#define AUTENTICACION_H_

#include "Arduino.h"
#include "Macros.h"
#include <Keypad.h>
#include "Env.h"

extern unsigned long lcd_clave_tiempo;
extern unsigned long lcd_info_tiempo;
extern char key;

class Autenticacion {

private:
	String entradaTeclado = "";
	byte passwordCacheada = false;

public:
	Autenticacion();
	String getEntradaTeclado();
    void comprobarEntrada();
    void construirEntrada(char key);
    bool comprobarClave(String clave);
    bool isPasswordCached();
    void limpiarEntrada();
};

#endif /* AUTENTICACION_H_ */
