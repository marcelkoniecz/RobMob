/*
 * encontrol.c
 *
 *  Created on: Apr 25, 2022
 *      Author: marcel
 */

#include "tim.h"
#include<stdlib.h>
#include "encontrol.h"

HAL_StatusTypeDef readUARTData(struct angles data) {
	uint8_t readBuf[2];

}

uint8_t degToPercent(uint8_t angle) {
	uint8_t percent = abs(angle) / MAX_DEGREE;
	return percent;
}

enum move calculateDir(angles data) {
	if ((abs(data.angle_x) < NO_ACCTBL_VALUE) && (abs(data.angle_y) < NO_ACCTBL_VALUE))
		return None;

	if (abs(data.angle_x) < abs(data.angle_y) && data.angle_y > NO_ACCTBL_VALUE)
		return Forward;

	if (abs(data.angle_x) < abs(data.angle_y) && data.angle_y < -(NO_ACCTBL_VALUE))
		return Backwards;

	if (abs(data.angle_x) > abs(data.angle_y) && data.angle_x > NO_ACCTBL_VALUE)
		return Left;

	if (abs(data.angle_x) > abs(data.angle_y) && data.angle_x < -(NO_ACCTBL_VALUE))
		return Right;
return None;
}

HAL_StatusTypeDef moveRobot(struct angles data) {
	uint8_t PWMVal = 0;
	//uint8_t PWMBVal = 0;
	enum move moveType = 0;

	moveType = calculateDir(data);

	// (% nachylenia * Max value PWM/100)
	PWMVal = (degToPercent(data.angle_x) * 1 / 99);

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
		PWMVal = (degToPercent(data.angle_y) *CONST_CONVERT + PWM_MIN_VAL);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, PWMVal);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, PWMVal);
		break;
	case Backwards:
		HAL_GPIO_WritePin(A1_IN_GPIO_Port, A1_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B1_IN_GPIO_Port, B1_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(A2_IN_GPIO_Port, A2_IN_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(B2_IN_GPIO_Port, B2_IN_Pin, GPIO_PIN_SET);
		PWMVal = (degToPercent(data.angle_y) *CONST_CONVERT + PWM_MIN_VAL);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, PWMVal);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,PWMVal);
		break;
	case Left:
		HAL_GPIO_WritePin(A2_IN_GPIO_Port, A2_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B2_IN_GPIO_Port, B2_IN_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(A1_IN_GPIO_Port, A1_IN_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(B1_IN_GPIO_Port, B1_IN_Pin, GPIO_PIN_RESET);
		PWMVal = (degToPercent(data.angle_y) *CONST_CONVERT + PWM_MIN_VAL);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, PWMVal);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, PWMVal);
		break;
	case Right:
		HAL_GPIO_WritePin(A2_IN_GPIO_Port, A2_IN_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(B2_IN_GPIO_Port, B2_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(A1_IN_GPIO_Port, A1_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B1_IN_GPIO_Port, B1_IN_Pin, GPIO_PIN_SET);
		PWMVal = (degToPercent(data.angle_y) *CONST_CONVERT + PWM_MIN_VAL);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, PWMVal);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, PWMVal);
		break;
	}

}

