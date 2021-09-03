/*
 * Pantalla.cpp
 *
 *  Created on: 29 jul. 2021
 *      Author: isrev
 */

#include "Pantalla.h"

LiquidCrystal_I2C lcd (CODEC_LCD, 16, 2);

Pantalla::Pantalla() {
	// TODO Auto-generated constructor stub
}

void Pantalla::iniciar(){
	Wire.begin();
	lcd.begin(16, 2);
	lcd.clear();
	lcd.backlight();
}

void Pantalla::limpiarPantalla(){
	lcd.clear();
}

void Pantalla::lcdLoadView(Pantalla *obj,void (Pantalla::*lcdFunction)()) {

	static void (Pantalla::*lcdFunctionAnterior)(void);

    if(lcdFunctionAnterior != lcdFunction){lcd.clear();}

    lcdFunctionAnterior = lcdFunction; //Puntero copia

  	(obj->*lcdFunction)();
}

void Pantalla::lcdLoadView(Pantalla *obj,void (Pantalla::*lcdFunction)(byte*, char[]), byte* var, char parameter[15]) {
	//Sobrecarga

	static void (Pantalla::*lcdFunctionAnterior)(byte*, char[]);
	static byte anteriorVar;


	if(lcdFunctionAnterior != lcdFunction){lcd.clear();}

	if(anteriorVar != *var){lcd.clear();}

	anteriorVar = *var;
	lcdFunctionAnterior = lcdFunction; //Puntero copia

  	(obj->*lcdFunction)(var,parameter);
}

void Pantalla::lcdInicio(){
	lcd.setCursor(3,0);
	lcd.print(F("BIENVENIDO!"));
	lcd.setCursor(2,1);
	lcd.print(version[0]);
}

void Pantalla::lcdFalloBateria()
{
	lcd.setCursor(0,0);
	lcd.print(F("ATENCION BATERIA"));
	lcd.setCursor(0,1);
	lcd.print(F("  DESCONECTADA  "));
}

void Pantalla::lcdSensorPuertaDesconectado()
{
	lcd.setCursor(0,0);
	lcd.print(F("SENSOR DE PUERTA"));
	lcd.setCursor(0,1);
	lcd.print(F("  DESCONECTADO  "));
}

void Pantalla::lcdAvisoResetAuto(){

	lcd.setCursor(0,0);
	lcd.print(F("RESET AUTOMATICO"));
	lcd.setCursor(0,1);
	lcd.print(F("HOY A LAS: 16:30"));

}

void Pantalla::lcdAvisoBluetooh(){

	lcd.setCursor(0,0);
	lcd.print(F("EL BLUETOOH ESTA"));
	lcd.setCursor(0,1);
	lcd.print(F("    ACTIVADO    "));
}

void Pantalla::lcdClave()
{
	lcd.setCursor(5,0);
	lcd.print(F("Clave"));
	lcd.setCursor(5,1);
	lcd.print(auth.getEntradaTeclado());
}


void Pantalla::lcdReposo()
{
	lcd.setCursor(0,0);
	lcd.print(F("ALARMA <> MENU>2"));
	lcd.setCursor(0,1);
	lcd.print(F("APAGADA"));
	lcd.setCursor(7,1);
	if(fecha.comprobarFecha(fecha.getFechaReset())){
		lcd.print(F(" R>"));
	}else{
		lcd.print(F("   "));
	}
	lcd.setCursor(10,1);
	if(configSystem.MODULO_RTC){
		lcd.print(fecha.imprimeHora());
	}else{
		lcd.print(F("__-__ "));
	}
	lcd.setCursor(15,1);

	if(digitalRead(SENSOR_BATERIA_RESPALDO) == HIGH){
		lcd.print(F(" "));
	}else{
		lcd.print(F("!"));

	}
}

void Pantalla::lcdGuardia(){

	if(MODO_DEFAULT){
		lcd.setCursor(0,0);
		lcd.print(F("ALARMA  ACTIVADA"));
	} else{
		lcd.setCursor(0,0);
		lcd.print(F("PRUEBA  ACTIVADA"));
	}

	lcd.setCursor(0,1);
	lcd.print(F("C:"));
	lcd.setCursor(2,1);
	if(configSystem.SENSORES_HABLITADOS[1]){
		lcd.print(pir1.getStrike());
	}else{
		lcd.print(F("X"));
	}

	lcd.setCursor(4,1);
	lcd.print(F("P:"));
	lcd.setCursor(6,1);
	if(configSystem.SENSORES_HABLITADOS[2]){
		lcd.print(pir2.getStrike());
	}else{
		lcd.print(F("X"));
	}

	lcd.setCursor(8,1);
	lcd.print(F("A:"));
	lcd.setCursor(10,1);
	if(configSystem.SENSORES_HABLITADOS[3]){
		lcd.print(pir3.getStrike());
	}else{
		lcd.print(F("X"));
	}

	if(millis()> tiempoMargen){
		lcd.setCursor(12,1);
		lcd.print(F(">RDY"));


	} else {
		lcd.setCursor(13,1);
		lcd.print(F(">OK"));

	}

}

	void Pantalla::lcdAlerta(){

		lcd.setCursor(0,0);
		lcd.print(F("INTRUSISMO"));
		lcd.setCursor(0,1);
		lcd.print(nombreZonas[zona]);
	}

	void Pantalla::lcdAvisoEnviado(){

		lcd.setCursor(0,0);
		lcd.print(F("ALARMA CONFIRMADA"));
		lcd.setCursor(0,1);
		lcd.print(F("AVISO ENVIADO"));

	}

	void Pantalla::lcdMenu(){

		lcd.setCursor(0,0);
		lcd.print(F("INFO>1  CONFIG>2"));
		lcd.setCursor(0,1);
		lcd.print(F("CHECK>3  SALIR>#"));
	}

	void Pantalla::menuConfig(){

		lcd.setCursor(0,0);
		lcd.print(F("MODO>1  SENSOR>2"));
		lcd.setCursor(0,1);
		lcd.print(F("HARDWR>3 ATRAS>#"));
	}

	void Pantalla::menuConfigModulos(){
		lcd.setCursor(0,0);
		lcd.print(F("BLUETOOH>1  SD>2"));
		lcd.setCursor(0,1);
		lcd.print(F("RTC>3    ATRAS>#"));
	}

	void Pantalla::menuConfigModos(){

		lcd.setCursor(0,0);
		lcd.print(F("REAL>1 SENSBLE>2"));
		lcd.setCursor(0,1);
		lcd.print(F("<Modos   ATRAS>#"));
	}

	void Pantalla::menuConfigSensores(){

		lcd.setCursor(0,0);
		lcd.print(F("PUERTA>1   PIR>2"));
		lcd.setCursor(0,1);
		lcd.print(F("<Sensor  ATRAS>#"));
	}

	void Pantalla::menuConfigSensoresPir(){

		lcd.setCursor(0,0);
		lcd.print(F("P1>1  P2>2  P3>3"));
		lcd.setCursor(0,1);
		lcd.print(F("Pag>*    ATRAS>#"));
	}


	void Pantalla::menuConfigChangeMode(byte* var, char name[15]){

		lcd.setCursor(0,0);
		lcd.print("CAMBIAR  "+(String)name+">1     ");
		lcd.setCursor(0,1);
		if(*var==1){
			lcd.print(F(">>ON>>  "));
		} else {
			lcd.print(F(">>OFF>> "));
		}

		lcd.setCursor(8,1);
		lcd.print(F(" ATRAS>#"));
	}


	void Pantalla::menuInfo(){

		lcd.setCursor(0,0);
		lcd.print(F("TIEMPO>1 DATOS>2"));
		lcd.setCursor(0,1);
		lcd.print(F("REGISTRO>3 ATR>#"));
	}

	void Pantalla::menuInfoTiempo(byte* var, char s[15]){

		double tiempo = (millis()/1000);

		lcd.setCursor(0,0);
		if(*var == static_cast<int>(TIME_MINUTOS)){
			tiempo = (tiempo/60);
			lcd.print(F("MINUTO: "));
		}

		if(*var == static_cast<int>(TIME_HORAS)){
			tiempo = ((tiempo/60)/60);
			lcd.print("HORAS:  ");
		}

		if(*var == static_cast<int>(TIME_DIAS)){
			tiempo = (((tiempo/60)/60)/24);
			lcd.print(F("DIAS:   "));
		}

		if(*var == static_cast<int>(TIME_SEMANAS)){
			tiempo = ((((tiempo/60)/60)/24)/7);
			lcd.print(F("SEMANAS:"));
		}
		lcd.setCursor(8,0);
		lcd.print(tiempo);
		lcd.setCursor(0,1);
		lcd.print(F("TIME>1   ATRAS>#"));
	}

	void Pantalla::menuInfoSMSActual(){

		lcd.setCursor(0,0);
		lcd.print(F("SMS Enviados:"));
		lcd.setCursor(13,0);
		lcd.print(mensajesEnviados);
		lcd.setCursor(0,1);
		lcd.print(F("Entradas:"));
		lcd.print(desactivaciones);
		lcd.setCursor(13,1);
		lcd.print(F("A>#"));
	}

	void Pantalla::menuInfoSMSHistorico(){

		lcd.setCursor(0,0);
		lcd.print(F("SMS:"));
		lcd.setCursor(4,0);
		lcd.print(configSystem.SMS_HISTORICO);
		lcd.setCursor(7,0);
		lcd.print(F("  RESET>3"));

		lcd.setCursor(0,1);
		lcd.print(configSystem.FECHA_SMS_HITORICO);
		lcd.setCursor(10,1);
		lcd.print(F("   A>#"));
	}

	void Pantalla::menuInfoErrHistorico(){
		lcd.setCursor(0,0);
		lcd.print(F("ERROR - SABOTAJE"));
		lcd.setCursor(0,1);
		lcd.print("->");
		lcd.setCursor(2,1);
		lcd.print(EEPROM.read(EE_INTERRUPCIONES_HISTORICO));
		lcd.setCursor(5,1);
		lcd.print(F("RESET>3 A>#"));
	}

	void Pantalla::menuInfoVersion(){
		lcd.setCursor(0,0);
		lcd.print(version[0]);
		lcd.setCursor(0,1);
		lcd.print(version[1]);
		lcd.setCursor(13,1);
		lcd.print(F("A>#"));
	}

	void Pantalla::menuInfoResetAuto(){
		lcd.setCursor(0,0);
		lcd.print(F("RESET AUTO:  A>#"));
		lcd.setCursor(0,1);
		lcd.print((String)fecha.imprimeFechaSimple(fecha.getFechaReset())+" 16:30");
	}

	void Pantalla::menuInfoSMSDiario(){

		lcd.setCursor(0,0);
		lcd.print(F("SMS:"));
		lcd.setCursor(4,0);
		lcd.print(EEPROM.read(MENSAJES_ENVIADOS));
		lcd.setCursor(7,0);
		lcd.print(F("  RESET>3"));

		lcd.setCursor(0,1);
		lcd.print(F("LIMITE -> 15 A>#"));
	}

	void Pantalla::menuInfoRegistros(){
		lcd.setCursor(0,0);
		lcd.print(F("DESCARGA DATOS>1"));
		lcd.setCursor(0,1);
		lcd.print(F("BORRAR>2 ATRAS>#"));
	}

	void Pantalla::menuInfoRegistrosBorrar(){
		lcd.setCursor(0,0);
		lcd.print(F("ELIMINAR  DATOS?"));
		lcd.setCursor(0,1);
		lcd.print(F("SI>1        NO>#"));
	}

	void Pantalla::menuCheck(){
		lcd.setCursor(0,0);
		lcd.print(F("BOCINA>1        "));
		lcd.setCursor(0,1);
		lcd.print(F("<Check   ATRAS>#"));
	}

	void Pantalla::errorEmergencia(){
		lcd.setCursor(0,0);
		lcd.print(F("ERROR INESPERADO"));
		lcd.setCursor(0,1);
		lcd.print(F("DESACTIVAR>#    "));
	}

	void Pantalla::menuInfoRegBorrado(){
		lcd.setCursor(0,0);
		lcd.print(F("EL REGISTRO FUE "));
		lcd.setCursor(0,1);
		lcd.print(F("ELIMINADO  ATR>#"));
	}

	void Pantalla::menuInfoRegBorradoError(){
		lcd.setCursor(0,0);
		lcd.print(F("ERROR AL BORRAR "));
		lcd.setCursor(0,1);
		lcd.print(F("EL REGISTRO  A>#"));
	}

	void Pantalla::menuInfoRegDescargando(){
		lcd.setCursor(0,0);
		lcd.print(F("DESCARGANDO LOS "));
		lcd.setCursor(0,1);
		lcd.print(F(" DATOS ESPERE..."));
	}

	void Pantalla::menuInfoRegDescargandoError(){
		lcd.setCursor(0,0);
		lcd.print(F("  NO HAY DATOS  "));
		lcd.setCursor(0,1);
		lcd.print(F(" ERROR AL ABRIR "));
	}

	void Pantalla::menuInfoBluetoohAviso(){
		lcd.setCursor(0,0);
		lcd.print(F(" ERROR ACTIVE EL"));
		lcd.setCursor(0,1);
		lcd.print(F("BLUETOOH PRIMERO"));
	}
