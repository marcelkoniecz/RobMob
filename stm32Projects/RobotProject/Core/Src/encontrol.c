/*
 * encontrol.c
 *
 *  Created on: Apr 25, 2022
 *      Author: marcel
 */

#include "tim.h"
#include "stm32f3xx_it.c"
#define MAX_DEGREE 180

struct angles {
	uint8_t angle_x;
	uint8_t angle_y;
};

enum Move {Forward,Backwards,Left, Right}

HAL_StatusTypeDef readUARTData(struct angles data) {
	uint8_t readBuf[2]; //Bufor to read data from UART

}

uint8_t degToPercent(uint8_t angle) {
	uint8_t degree = angle / MAX_DEGREE;
	return degree;
}

HAL_StatusTypeDef moveRobot(struct angles data) {
	uint8_t PWMAVal = 0;
	uint8_t PWMBVal = 0;

	// (% nachylenia * 1/(counter period timera))
	PWMAVal = (degToPercent(data.angle_x) * 1 / 59);

	//Moze poczatkowo zrobi poruszanie do przodu do tylu i skrecanie

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, PWMAVal);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, PWMAVal);

}

