/*
 * Fecha.h
 *
 *  Created on: 16 ago. 2021
 *      Author: isrev
 */

#ifndef SOURCE_FECHA_H_
#define SOURCE_FECHA_H_
#include <RTClib.h>
#include "Macros.h"
extern ConfigSystem configSystem;

class Fecha {
private:
	RTC_DS3231 rtc;
	DateTime fecha;
	DateTime fechaReset;

public:

	Fecha();
	void iniciarRTC();
	String imprimeFecha(DateTime paramFecha = 0);
	String imprimeFechaSimple(DateTime paramFecha = 0);
	String imprimeFechaSQL();
	String imprimeHora();
	void establecerFechaReset(byte dia, byte hora = 0, byte minuto = 0, byte segundo = 0);
	DateTime getFechaReset();
	bool comprobarFecha(DateTime paramFecha);
	bool comprobarHora(byte horas, byte minutos = 0);
	bool comprobarRangoHorario(byte hora_inicio, byte hora_fin, byte min_inicio = 0, byte min_fin = 0);
};

#endif /* SOURCE_FECHA_H_ */
