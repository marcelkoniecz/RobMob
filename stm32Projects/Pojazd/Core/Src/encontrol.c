#include "tim.h"
#include <stdlib.h>
#include "encontrol.h"
#include <string.h>

uint16_t calculateSpeed(double angle) {
    angle = abs(angle);

    if (angle > MAX_DEGREE)
        angle = MAX_DEGREE;

    angle *= PWM_MAX_VAL / MAX_DEGREE;

    if (angle < PWM_MIN_VAL)
        angle = PWM_MIN_VAL;

    return (uint16_t)angle;
}

Move calculateDirection(Measurment* m) {
    if ((abs(m->angles.x) < NO_ACCTBL_VALUE)
        && (abs(m->angles.y) < NO_ACCTBL_VALUE))
        return None;

    //	if (abs(m->angles.x) < abs(m->angles.y) && m->angles.y > NO_ACCTBL_VALUE)
    //		return Left;
    //
    //	if (abs(m->angles.x) < abs(m->angles.y) && m->angles.y < -(NO_ACCTBL_VALUE))
    //		return Right;
    //
    //	if (abs(m->angles.x) > abs(m->angles.y) && m->angles.x > NO_ACCTBL_VALUE)
    //		return Forward;
    //
    //	if (abs(m->angles.x) > abs(m->angles.y) && m->angles.x < -(NO_ACCTBL_VALUE))
    //		return Backwards;
    //return None;
    //}
    if (m->angles.y > NO_ACCTBL_VALUE && abs(m->angles.x) < NO_ACCTBL_VALUE)
        return Left;
    if (m->angles.y < -(NO_ACCTBL_VALUE) && abs(m->angles.x) < NO_ACCTBL_VALUE)
        return Right;
    if (m->angles.x > NO_ACCTBL_VALUE)
        return Forward;
    if (m->angles.x < -(NO_ACCTBL_VALUE))
        return Backwards;

    return None;
}
double calculateSpeedS(double angle) {
    angle = abs(angle);

    if (angle > MAX_DEGREE)
        angle = MAX_DEGREE;

    angle *= PWM_MAX_VAL / MAX_DEGREE;

    if (angle < PWM_MIN_VAL)
        angle = PWM_MIN_VAL;

    return (uint16_t)angle;


}

double calculateSpeedL(double angle) {
    angle = abs(angle);

    if (angle > MAX_DEGREE)
        angle = MAX_DEGREE;

    angle *= PWM_MAX_VAL / MAX_DEGREE;

    if (angle < PWM_MIN_VAL)
        angle = PWM_MIN_VAL;

    return (uint16_t)angle;
}


HAL_StatusTypeDef moveRobot(Measurment* m) {
    uint16_t PWMValR = 0;
    uint16_t PWMValL = 0;
    Move curr_move = None;

    curr_move = calculateDirection(m);

    if (curr_move == Left || curr_move == Right)
    {
        PWMValR = calculateSpeed(m->angles.y);
        PWMValL = PWMValR;
    }
    else if((abs(m->angles.y) < NO_ACCTBL_VALUE) || (abs(m->angles.x) > NO_TURN_VALUE))
	{
		PWMValR = PWMValL = calculateSpeed(m->angles.x);
	}
    else if (curr_move == Forward)
    {
		if (m->angles.y < 0)
		{
			PWMValL = calculateSpeed(m->angles.x);
			PWMValR = PWMValL - (calculateSpeed(m->angles.y) * PWMValL) / PWM_MAX_VAL;
		}
		else
		{
			PWMValR = calculateSpeed(m->angles.x);
			PWMValL = PWMValR - (calculateSpeed(m->angles.y) * PWMValR) / PWM_MAX_VAL;
		}
    }
    else if (curr_move == Backwards)
    {
    	if (m->angles.y < 0)
    	{
			PWMValL = calculateSpeed(m->angles.x);
			PWMValR = PWMValL - (calculateSpeed(m->angles.y) * PWMValL) / PWM_MAX_VAL;
		}
		else
		{
			PWMValR = calculateSpeedS(m->angles.x);
			PWMValL = PWMValR - (calculateSpeed(m->angles.y) * PWMValR) / PWM_MAX_VAL;
		}
    }

    switch (curr_move)
    {
    case None:
        HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(A1_IN_GPIO_Port, A1_IN_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(B1_IN_GPIO_Port, B1_IN_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(A2_IN_GPIO_Port, A2_IN_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(B2_IN_GPIO_Port, B2_IN_Pin, GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, PWM_MAX_VAL);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, PWM_MAX_VAL);
        break;
    case Forward:
        HAL_GPIO_WritePin(A2_IN_GPIO_Port, A2_IN_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(B2_IN_GPIO_Port, B2_IN_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(A1_IN_GPIO_Port, A1_IN_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(B1_IN_GPIO_Port, B1_IN_Pin, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, PWMValL);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, PWMValR);
        HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_SET);
        break;
    case Backwards:
        HAL_GPIO_WritePin(A1_IN_GPIO_Port, A1_IN_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(B1_IN_GPIO_Port, B1_IN_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(A2_IN_GPIO_Port, A2_IN_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(B2_IN_GPIO_Port, B2_IN_Pin, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, PWMValR);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, PWMValL);
        HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_SET);
        break;
    case Left:
        HAL_GPIO_WritePin(A2_IN_GPIO_Port, A2_IN_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(B2_IN_GPIO_Port, B2_IN_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(A1_IN_GPIO_Port, A1_IN_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(B1_IN_GPIO_Port, B1_IN_Pin, GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, PWMValR);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, PWMValL);
        HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_SET);
        break;
    case Right:
        HAL_GPIO_WritePin(A2_IN_GPIO_Port, A2_IN_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(B2_IN_GPIO_Port, B2_IN_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(A1_IN_GPIO_Port, A1_IN_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(B1_IN_GPIO_Port, B1_IN_Pin, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, PWMValR);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, PWMValL);
        HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_SET);
        break;
    }

    return HAL_OK;
}
