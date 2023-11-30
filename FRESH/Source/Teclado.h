/*
 * Teclado.h
 *
 *  Created on: 20 mar. 2023
 *      Author: isrev
 */

#ifndef TECLADO_H_
#define TECLADO_H_

#include "Arduino.h"
#include <Keypad.h>
#include <Keypad_I2C.h>
#include <Wire.h>

#define I2CADDR 0x20

char key;

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
// Digitran keypad, bit numbers of PCF8574 i/o port

byte rowPins[ROWS] = {3,2,1,0};
byte colPins[COLS] = {7,6,5,4};

TwoWire *jwire = &Wire;   //test passing pointer to keypad lib
Keypad_I2C keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR, PCF8574, jwire );


void iniciarTecladoI2C(){
	jwire->begin( );
	keypad.begin( );
}

#endif /* TECLADO_H_ */
