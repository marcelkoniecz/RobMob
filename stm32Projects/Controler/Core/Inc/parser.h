#ifndef INC_PARSER_H_
#define INC_PARSER_H_

#include "mpu6050.h"

HAL_StatusTypeDef ParseAccelAngles(uint8_t *data, uint16_t size, MPU6050_t *mpu);


#endif /* INC_PARSER_H_ */
