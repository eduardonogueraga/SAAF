/*
 * Bocina.h
 *
 *  Created on: 26 jun. 2020
 *      Author: isrev
 */

#ifndef PROYECTO_BOCINA_H_
#define PROYECTO_BOCINA_H_

#include "Arduino.h"
#include "Macros.h"

class Bocina {

private:

	unsigned short bocinaIntervalo = 5000;
    unsigned long bocinaTiempoAnt = 0;

public:
	Bocina();
	void sonarBocina(unsigned short bocinaIntervalo = 5000);
	void stopBocina();
};

#endif /* PROYECTO_BOCINA_H_ */
