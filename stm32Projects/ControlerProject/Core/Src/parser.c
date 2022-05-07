#include "parser.h"
#include "stdio.h"
#include "string.h"

HAL_StatusTypeDef ParseAccel(uint8_t *data, uint16_t size, MPU6050_t *mpu)
{
	if(size < 8)
		return HAL_ERROR;

	char end[2] = {'\r', '\n'};

	memcpy(data, (uint8_t *)&(mpu->Accel_X_RAW), 2);
	memcpy(data + 2, (uint8_t *)&(mpu->Accel_Y_RAW), 2);
	memcpy(data + 4, (uint8_t *)&(mpu->Accel_Z_RAW), 2);
	memcpy(data + 6, end, 2);
}

