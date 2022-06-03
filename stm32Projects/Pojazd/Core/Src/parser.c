#include "parser.h"
#include "stdio.h"
#include "string.h"

HAL_StatusTypeDef ParseAccelAngles(uint8_t *data, uint16_t size, Measurment *m)
{
	uint8_t end[2];
	int16_t temp;

	if(size < (2*sizeof(double) + 3*sizeof(int16_t) + sizeof(end)))
	{
		return HAL_ERROR;
	}

	memcpy((uint8_t *)&(temp), data, sizeof(temp));
	data += sizeof(temp);
	m->accel.x = temp / 16384.0;

	memcpy((uint8_t *)&(temp), data, sizeof(temp));
	data += sizeof(temp);
	m->accel.y = temp / 16384.0;

	memcpy((uint8_t *)&(temp), data, sizeof(temp));
	data += sizeof(temp);
	m->accel.z = temp / 14418.0;

	memcpy((double *)&(m->angles.x), data, sizeof(m->angles.x));
	data += sizeof(m->angles.x);

	memcpy((double *)&(m->angles.y), data, sizeof(m->angles.y));
	data += sizeof(m->angles.y);

	memcpy(end, data, sizeof(end));

	if(end[0] != '\r' || end[1] != '\n')
		return HAL_ERROR;

	return HAL_OK;
}

HAL_StatusTypeDef ParseData(uint8_t *data, uint16_t* pos, Measurment *m)
{
	HAL_StatusTypeDef status = HAL_ERROR;
	uint8_t size = (2*sizeof(double) + 4*sizeof(uint16_t));
	if(*pos >= 24)
	{
		if(data[size - 2] == '\r' && data[size - 1] == '\n')
		{
			status = ParseAccelAngles(data, *pos, m);

		}

		*pos = 0;
	}
	return status;
}
