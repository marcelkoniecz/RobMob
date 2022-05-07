#include "parser.h"
#include "stdio.h"
#include "string.h"

HAL_StatusTypeDef ParseAccelAngles(uint8_t *data, uint16_t size, MPU6050_t *mpu)
{
	uint8_t end[2] = {'\r', '\n'};

	if(size < (sizeof(mpu->Accel_X_RAW)
				+ sizeof(mpu->Accel_Y_RAW)
				+ sizeof(mpu->Accel_Z_RAW)
				+ sizeof(mpu->KalmanAngleX)
				+ sizeof(mpu->KalmanAngleY)
				+ sizeof(end)))
	{
		return HAL_ERROR;
	}


	memcpy(data, (uint8_t *)&(mpu->Accel_X_RAW), sizeof(mpu->Accel_X_RAW));
	data += sizeof(mpu->Accel_X_RAW);
	memcpy(data, (uint8_t *)&(mpu->Accel_Y_RAW), sizeof(mpu->Accel_Y_RAW));
	data += sizeof(mpu->Accel_Y_RAW);
	memcpy(data, (uint8_t *)&(mpu->Accel_Z_RAW), sizeof(mpu->Accel_Z_RAW));
	data += sizeof(mpu->Accel_Z_RAW);
	memcpy(data, (uint8_t *)&(mpu->KalmanAngleX), sizeof(mpu->KalmanAngleX));
	data += sizeof(mpu->KalmanAngleX);
	memcpy(data, (uint8_t *)&(mpu->KalmanAngleY), sizeof(mpu->KalmanAngleY));
	data += sizeof(mpu->KalmanAngleY);
	memcpy(data, end, sizeof(end));

	return HAL_OK;
}

