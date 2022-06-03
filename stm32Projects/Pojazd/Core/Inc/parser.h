#ifndef INC_PARSER_H_
#define INC_PARSER_H_

#include "main.h"

typedef struct angles_t
{
	double x;
	double y;
} Angles;

typedef struct accel_t
{
	double x;
	double y;
	double z;
} Acceleration;

typedef struct meas_t
{
	Angles angles;
	Acceleration accel;
} Measurment;

HAL_StatusTypeDef ParseAccelAngles(uint8_t *data, uint16_t size, Measurment *m);

HAL_StatusTypeDef ParseData(uint8_t *data, uint16_t* pos, Measurment *m);

#endif /* INC_PARSER_H_ */
