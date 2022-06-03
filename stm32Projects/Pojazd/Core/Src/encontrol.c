#include "tim.h"
#include <stdlib.h>
#include "encontrol.h"
#include <string.h>

uint16_t calculateSpeed(double angle) {
	angle = abs(angle);

	if(angle > MAX_DEGREE)
		angle = MAX_DEGREE;

	angle *= PWM_MAX_VAL / MAX_DEGREE;

	if(angle < PWM_MIN_VAL)
		angle = PWM_MIN_VAL;

	return (uint16_t)angle;
}

Move calculateDirection(Measurment *m) {
	if ((abs(m->angles.x) < NO_ACCTBL_VALUE) && (abs(m->angles.y) < NO_ACCTBL_VALUE))
		return None;

	if (abs(m->angles.x) < abs(m->angles.y) && m->angles.y > NO_ACCTBL_VALUE)
		return Left;

	if (abs(m->angles.x) < abs(m->angles.y) && m->angles.y < -(NO_ACCTBL_VALUE))
		return Right;

	if (abs(m->angles.x) > abs(m->angles.y) && m->angles.x > NO_ACCTBL_VALUE)
		return Forward;

	if (abs(m->angles.x) > abs(m->angles.y) && m->angles.x < -(NO_ACCTBL_VALUE))
		return Backwards;
return None;
}

HAL_StatusTypeDef moveRobot(Measurment *m) {
	uint16_t PWMVal = 0;
	Move curr_move = None;

	curr_move = calculateDirection(m);

	if(curr_move == Left || curr_move == Right)
		PWMVal = calculateSpeed(m->angles.x);
	else if(curr_move == Forward || curr_move == Backwards)
		PWMVal = calculateSpeed(m->angles.y);
	else
		PWMVal = PWM_MAX_VAL;

	switch (curr_move) {
	case None:
		HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(A1_IN_GPIO_Port, A1_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B1_IN_GPIO_Port, B1_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(A2_IN_GPIO_Port, A2_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B2_IN_GPIO_Port, B2_IN_Pin, GPIO_PIN_RESET);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, PWMVal);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, PWMVal);
		break;
	case Forward:
		HAL_GPIO_WritePin(A2_IN_GPIO_Port, A2_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B2_IN_GPIO_Port, B2_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(A1_IN_GPIO_Port, A1_IN_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(B1_IN_GPIO_Port, B1_IN_Pin, GPIO_PIN_SET);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, PWMVal);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, PWMVal);
		HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_SET);
		break;
	case Backwards:
		HAL_GPIO_WritePin(A1_IN_GPIO_Port, A1_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B1_IN_GPIO_Port, B1_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(A2_IN_GPIO_Port, A2_IN_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(B2_IN_GPIO_Port, B2_IN_Pin, GPIO_PIN_SET);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, PWMVal);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3,PWMVal);
		HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_SET);
		break;
	case Left:
		HAL_GPIO_WritePin(A2_IN_GPIO_Port, A2_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B2_IN_GPIO_Port, B2_IN_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(A1_IN_GPIO_Port, A1_IN_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(B1_IN_GPIO_Port, B1_IN_Pin, GPIO_PIN_RESET);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, PWMVal);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, PWMVal);
		HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_SET);
		break;
	case Right:
		HAL_GPIO_WritePin(A2_IN_GPIO_Port, A2_IN_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(B2_IN_GPIO_Port, B2_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(A1_IN_GPIO_Port, A1_IN_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B1_IN_GPIO_Port, B1_IN_Pin, GPIO_PIN_SET);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, PWMVal);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, PWMVal);
		HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_SET);
		break;
	}

	return HAL_OK;
}

