/*
 * SQL.h
 *
 *  Created on: 27 ago. 2021
 *      Author: isrev
 */

#ifndef SOURCE_SQL_H_
#define SOURCE_SQL_H_
extern Mensajes mensaje;
extern LLAMADAS_GSM estadoLlamada;

void insertQuery(void (*otherFunction)(String*)) {
	if(MODO_DEFAULT){
		(*otherFunction)(&registro.getInsertSql());
		registro.registrarEventoSQL();
	}
}

void insertQuery(void (*otherFunction)(String*, String, String), String param1, String param2) {
	(*otherFunction)(&registro.getInsertSql(), param1, param2);
	registro.registrarEventoSQL();
}

void sqlInicioAlarma(String *p){

	String query = F("INSERT INTO `alarma` (`descripcion`, `fecha`) VALUES ('ALARMA INICIADA', '");
	query += fecha.imprimeFechaSQL();
	query += F("');");
	*p = query;
}

void sqlIntentosRecuperados(String *p){

	String query = F("INSERT INTO `alarma` (`descripcion`, `fecha`) VALUES ('INTENTOS SMS DIARIOS RECUPERADOS', '");
	query += fecha.imprimeFechaSQL();
	query += F("');");
	*p = query;
}

void sqlSensorPuertaDeshabilitado(String *p){

	String query = F("INSERT INTO `alarma` (`descripcion`, `fecha`) VALUES ('SENSOR DE PUERTA DESCONECTADO', '");
	query += fecha.imprimeFechaSQL();
	query += F("');");
	*p = query;
}

void sqlBateriaEmergenciaActivada(String *p){ //Sobre carga para enviar param?

	String query = F("INSERT INTO `alarma` (`descripcion`, `fecha`) VALUES ('BATERIA DE EMERGENCIA ACTIVADA', '");
	query += fecha.imprimeFechaSQL();
	query += F("');");
	*p = query;
}

void sqlBateriaEmergenciaDesactivada(String *p){

	String query = F("INSERT INTO `alarma` (`descripcion`, `fecha`) VALUES ('BATERIA DE EMERGENCIA DESACTIVADA', '");
	query += fecha.imprimeFechaSQL();
	query += F("');");
	*p = query;
}


void sqlSmsIntentosRealizados(String *p){

	String query = F("INSERT INTO `alarma` (`descripcion`, `fecha`) VALUES ('INTENTOS SMS REALIZADOS: ");
	query += EEPROM.read(MENSAJES_ENVIADOS);
	query += F("', '");
	query += fecha.imprimeFechaSQL();
	query += F("');");
	*p = query;
}

void sqlSmsIntentosAcabados(String *p){

	String query = F("INSERT INTO `alarma` (`descripcion`, `fecha`) VALUES ('INTENTOS SMS DIARIOS ACABADOS', '");
	query += fecha.imprimeFechaSQL();
	query += F("');");
	*p = query;
}

void sqlModoAlarma(String *p){

	String modo;

	MODO_DEFAULT? modo = "DEFAULT" : modo = "PRUEBA";

	String query = F("INSERT INTO `alarma` (`descripcion`, `fecha`) VALUES ('ALARMA ESTABLECIDA EN MODO: ");
	query += modo;
	query += "', '";
	query += fecha.imprimeFechaSQL();
	query += F("');");
	*p = query;
}

void sqlLlamadas(String *p){

	String query = F("INSERT INTO `alarma` (`descripcion`, `fecha`) VALUES ('LLAMANDO A MOVIL");
	query += estadoLlamada;
	query += "', '";
	query += fecha.imprimeFechaSQL();
	query += F("');");
	*p = query;
}

void sqlActivarAlarmaManual(String *p){

	String query = F("INSERT INTO `entradas` (`tipo`, `modo`, `restaurado`, `intentos_reactivacion`, `fecha`)"
			" VALUES ('activacion', 'manual', '0', '");
	query += (3-INTENTOS_REACTIVACION);
	query += F("', '");
	query += fecha.imprimeFechaSQL();
	query += F("');");
	*p = query;
}

void sqlActivarAlarmaAutomatico(String *p){

	String query = F("INSERT INTO `entradas` (`tipo`, `modo`, `restaurado`, `intentos_reactivacion`, `fecha`)"
			" VALUES ('activacion', 'auto', '0', '");
	query += (3-INTENTOS_REACTIVACION);
	query += F("', '");
	query += fecha.imprimeFechaSQL();
	query += F("');");
	*p = query;
}


void sqlDesactivarAlarma(String *p){

	String query = F("INSERT INTO `entradas` (`tipo`, `modo`, `restaurado`, `intentos_reactivacion`, `fecha`)"
			" VALUES ('desactivacion', 'manual', '0', '");
	query += (3-INTENTOS_REACTIVACION);
	query += F("', '");
	query += fecha.imprimeFechaSQL();
	query += F("');");
	*p = query;
}

void sqlSensorEstandar(String *p, String tipo, String estado){

	String query = F("INSERT INTO `sensores` (`tipo`, `estado`, `modo`, `fecha`) VALUES ('");
	query += tipo;
	query += F("', '");
	query += estado;
	query += F("', 'estandar', '");
	query += fecha.imprimeFechaSQL();
	query += F("');");
	*p = query;
}

void sqlSensorPhantom(String *p, String tipo, String estado){

	String query = F("INSERT INTO `sensores` (`tipo`, `estado`, `modo`, `fecha`) VALUES ('");
	query += tipo;
	query += F("', '");
	query += estado;
	query += F("', 'phantom', '");
	query += fecha.imprimeFechaSQL();
	query += F("');");
	*p = query;
}

void sqlSalto(String *p){

	String query = F("INSERT INTO `saltos` (`intrusismo`, `restaurado`, `entradas_id`, `sensores_id`) VALUES ('0', "
			"'0',(SELECT max(id) FROM entradas), (SELECT max(id) FROM sensores));");
	*p = query;
}

void sqlMensajes(String *p){

	String tipo;
	switch(mensaje.getTipoMensaje()){

	case SMS_TIPO_SALTO:
		tipo = "salto";
		break;

	case SMS_TIPO_INFO:
		tipo = "salto";
		break;


	case SMS_TIPO_ERROR:
		tipo = "error";
		break;
	}

	String query = F("INSERT INTO `mensajes` (`tipo`, `asunto`, `cuerpo`, `fecha_sms`) VALUES ('");
	query += tipo;
	query += F("', '");
	query += mensaje.getAsuntoMensaje();
	query += F("', '");
	query += mensaje.getCuerpoMensaje();
	query += F("', '");
	query += fecha.imprimeFechaSQL();
	query += F("');");
	*p = query;
}

void sqlUpdateSalto(String *p){
	String query = F("UPDATE `saltos` SET `intrusismo` = '1', `mensajes_id` = (SELECT max(id) FROM mensajes) "
			"WHERE (id = (SELECT * FROM(SELECT max(id) FROM saltos) as ultimo_id));");
	*p = query;
}

void sqlUpdateEntrada(String *p){
	String query = F("UPDATE `entradas` SET `mensajes_id` = (SELECT max(id) FROM mensajes) "
			"WHERE (id = (SELECT * FROM(SELECT max(id) FROM entradas) as ultimo_id));");
	*p = query;
}

void sqlUpdateErrores(String *p){
	String query = F("UPDATE `errores` SET `mensajes_id` = (SELECT max(id) FROM mensajes) "
			"WHERE (id = (SELECT * FROM(SELECT max(id) FROM errores) as ultimo_id));");
	*p = query;
}

void sqlUpdateEntradaRestaurada(String *p){
	String query = F("UPDATE `entradas` SET `restaurado` = '1' WHERE (id = (SELECT * FROM(SELECT max(id) FROM entradas) as ultimo_id));");
	*p = query;
}

void sqlUpdateSaltoRestaurado(String *p){
	String query = F("UPDATE `saltos` SET `restaurado` = '1' WHERE (id = (SELECT * FROM(SELECT max(id) FROM saltos) as ultimo_id));");
	*p = query;
}


void sqlUpdateEntradaModoAuto(String *p){
	String query = F("UPDATE `entradas` SET `modo` = 'auto' WHERE (id = (SELECT * FROM(SELECT max(id) FROM entradas) as ultimo_id));");
	*p = query;
}

void sqlReset(String *p){

	String modo;

	if(alertsInfoLcd[INFO_RESET_AUTO] == 1){
		modo = "AUTOMATICO";
	}else {
		modo = "MANUAL";
	}

	String query = F("INSERT INTO `reset` (`modo`, `fecha`) VALUES ('");
	query += modo;
	query += "', '";
	query += fecha.imprimeFechaSQL();
	query += F("');");
	*p = query;
}

void sqlError(String *p){

	String err;
	switch(codigoError){

	case ERR_FALLO_ALIMENTACION:
		err = "FALLO EN ALIMENTACION";
		break;

	case ERR_FALLO_SENSOR:
		err = "FALLO EN SENSOR";
		break;
	}
	String query = F("INSERT INTO `errores` (`descripcion`, `fecha`) VALUES ('");
	query += err;
	query += F("', '");
	query += fecha.imprimeFechaSQL();
	query += F("');");
	*p = query;
}

#endif /* SOURCE_SQL_H_ */
