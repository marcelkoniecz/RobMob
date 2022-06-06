
#ifndef INC_ENCONTROL_H_
#define INC_ENCONTROL_H_

#include "tim.h"
#include <stdlib.h>
#include "parser.h"

#define MAX_DEGREE 100.0
#define PWM_MAX_VAL 999									//MAX PWM
#define PWM_MIN_VAL (PWM_MAX_VAL*0.3)					//40% MAX PWM
#define NO_ACCTBL_VALUE 15.0                            //wartosc dla ktorej wystepuje minimalne poruszenie
#define NO_TURN_VALUE 70.0                            	//wartosc dla ktorej nie skręcamy
#define CONST_CONVERT ((PWM_MAX_VAL- PWM_MIN_VAL)/100) //obliczenie stalej do pwm


typedef enum move_t {
	None, Forward, Backwards, Left, Right
} Move;

uint16_t calculateSpeed(double angle);

Move calculateDirection(Measurment *data);

HAL_StatusTypeDef moveRobot(Measurment *data);

#endif /* INC_ENCONTROL_H_ */
