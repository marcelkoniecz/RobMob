/*
 * encontrol.c
 *
 *  Created on: Apr 25, 2022
 *      Author: marcel
 */

#include "tim.h"
#include "stm32f3xx_it.c"
#include<stdlib.h>

#define MAX_DEGREE 180
#define PWM_MAX_VAL 100

typedef struct angles {
	int8_t angle_x;
	int8_t angle_y;
} angles;

typedef enum move {
	None, Forward, Backwards, Left, Right
} move;

HAL_StatusTypeDef readUARTData(struct angles data) {
	uint8_t readBuf[2];

}

uint8_t degToPercent(uint8_t angle) {
	uint8_t percent = angle / MAX_DEGREE;
	return percent;
}

enum move calculateDir(angles data) {
	enum move tmp;

	if ((abs(data.angle_x) < 5) && (abs(data.angle_y) < 5))
		return None;

	if (abs(data.angle_x) > abs(data.angle_y) && data.angle_x > 0)
		return Forward;

	if (abs(data.angle_x) < abs(data.angle_y) && data.angle_x < 0)
		return Backwards;

	if (abs(data.angle_x) < abs(data.angle_y) && data.angle_y < 0)
		return Left;

	if (abs(data.angle_x) < abs(data.angle_y) && data.angle_y > 0)
		return Right;

}

HAL_StatusTypeDef moveRobot(struct angles data) {
	uint8_t PWMAVal = 0;
	uint8_t PWMBVal = 0;
	enum move moveType = 0;

	moveType = calculateDir(data);

	// (% nachylenia * Max value PWM/100)
	PWMAVal = (degToPercent(data.angle_x) * 1 / 99);

	switch (moveType) {
	case None:
		HAL_GPIO_WritePin(A1_IN_GPIO_Port, A1_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B1_IN_GPIO_Port, B1_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(A2_IN_GPIO_Port, A2_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B2_IN_GPIO_Port, B2_IN_Pin, GPIO_PIN_RESET);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,PWM_MAX_VAL);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, PWM_MAX_VAL);
		break;
	case Forward:
		HAL_GPIO_WritePin(A2_IN_GPIO_Port, A2_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B2_IN_GPIO_Port, B2_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(A1_IN_GPIO_Port, A1_IN_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(B1_IN_GPIO_Port, B1_IN_Pin, GPIO_PIN_SET);
		PWMAVal = (degToPercent(data.angle_x) * PWM_MAX_VAL / 100);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, PWMAVal);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, PWMAVal);
		break;
	case Backwards:
		HAL_GPIO_WritePin(A1_IN_GPIO_Port, A1_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B1_IN_GPIO_Port, B1_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(A2_IN_GPIO_Port, A2_IN_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(B2_IN_GPIO_Port, B2_IN_Pin, GPIO_PIN_SET);
		PWMAVal = (degToPercent(data.angle_x) * PWM_MAX_VAL / 100);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, PWMAVal);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,PWMAVal);
		break;
	case Left:
		HAL_GPIO_WritePin(A2_IN_GPIO_Port, A2_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B2_IN_GPIO_Port, B2_IN_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(A1_IN_GPIO_Port, A1_IN_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(B1_IN_GPIO_Port, B1_IN_Pin, GPIO_PIN_RESET);
		PWMBVal = (degToPercent(data.angle_y) * PWM_MAX_VAL / 100);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, PWMAVal);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, PWMAVal);
		break;
	case Right:
		HAL_GPIO_WritePin(A2_IN_GPIO_Port, A2_IN_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(B2_IN_GPIO_Port, B2_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(A1_IN_GPIO_Port, A1_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B1_IN_GPIO_Port, B1_IN_Pin, GPIO_PIN_SET);
		PWMBVal = (degToPercent(data.angle_y) * PWM_MAX_VAL / 100);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, PWMBVal);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, PWMBVal);
		break;
	}

}

