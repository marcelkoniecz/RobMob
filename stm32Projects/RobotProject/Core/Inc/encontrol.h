/*
 * encontrol.h
 *
 *  Created on: May 7, 2022
 *      Author: marcel
 */

#ifndef INC_ENCONTROL_H_
#define INC_ENCONTROL_H_
#include "tim.h"
#include<stdlib.h>

#define MAX_DEGREE 100
#define PWM_MAX_VAL 100									//MAX PWM
#define PWM_MIN_VAL (PWM_MAX_VAL*0.40)					//40% MAX PWM
#define NO_ACCTBL_VALUE 10                              //wartosc dla ktorej wystepuje minimalne poruszenie
#define CONST_CONVERT ((PWM_MAX_VAL- PWM_MIN_VAL)/100) //obliczenie stalej do pwm

typedef struct angles {
	int8_t angle_x;
	int8_t angle_y;
} angles;

typedef enum move {
	None, Forward, Backwards, Left, Right
} move;

HAL_StatusTypeDef readUARTData(struct angles data);
uint8_t degToPercent(uint8_t angle);
enum move calculateDir(angles data);
HAL_StatusTypeDef moveRobot(struct angles data);

#endif /* INC_ENCONTROL_H_ */
