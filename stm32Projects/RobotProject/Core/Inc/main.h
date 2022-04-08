/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PWMA_Pin GPIO_PIN_0
#define PWMA_GPIO_Port GPIOC
#define PWMB_Pin GPIO_PIN_1
#define PWMB_GPIO_Port GPIOC
#define BLTTH_TX_Pin GPIO_PIN_4
#define BLTTH_TX_GPIO_Port GPIOC
#define STBY_Pin GPIO_PIN_6
#define STBY_GPIO_Port GPIOC
#define B2_Pin GPIO_PIN_8
#define B2_GPIO_Port GPIOC
#define B1_Pin GPIO_PIN_9
#define B1_GPIO_Port GPIOC
#define BLUTTH_RX_Pin GPIO_PIN_10
#define BLUTTH_RX_GPIO_Port GPIOA
#define A2_Pin GPIO_PIN_8
#define A2_GPIO_Port GPIOB
#define A1_Pin GPIO_PIN_9
#define A1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
