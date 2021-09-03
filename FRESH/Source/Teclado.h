/*
 * Teclado.h
 *
 *  Created on: 02 ago. 2021
 *      Author: isrev
 */

#ifndef TECLADO_H_
#define TECLADO_H_

#include "Arduino.h"
#include <Keypad.h>
#include "Macros.h"

char key;

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {

		{'1','2', '3'},
		{'4','5', '6'},
		{'7','8', '9'},
		{'*','0', '#'}
};

byte rowPins[ROWS] = {ROW_1, ROW_2, ROW_3, ROW_4};
byte colPins[COLS] = {COL_1, COL_2, COL_3};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); // @suppress("Ambiguous problem")

#endif /* TECLADO_H_ */
