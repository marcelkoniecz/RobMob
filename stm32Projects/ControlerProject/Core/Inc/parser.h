#ifndef INC_PARSER_H_
#define INC_PARSER_H_

#include "main.h"
#include "mpu6050.h"

HAL_StatusTypeDef ParseAccel(uint8_t *data, uint16_t size, MPU6050_t *mpu);


#endif /* INC_PARSER_H_ */
