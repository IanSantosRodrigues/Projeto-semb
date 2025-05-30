/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f4xx_hal.h"

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
#define HSE_IN_Pin GPIO_PIN_0
#define HSE_IN_GPIO_Port GPIOH
#define HSE_OUT_Pin GPIO_PIN_1
#define HSE_OUT_GPIO_Port GPIOH
#define LOAD_DATA_Pin GPIO_PIN_0
#define LOAD_DATA_GPIO_Port GPIOC
#define LOAD_CLK_Pin GPIO_PIN_1
#define LOAD_CLK_GPIO_Port GPIOC
#define RESET_DSP_Pin GPIO_PIN_4
#define RESET_DSP_GPIO_Port GPIOA
#define DC_DSP_Pin GPIO_PIN_5
#define DC_DSP_GPIO_Port GPIOA
#define BLK_DSP_Pin GPIO_PIN_6
#define BLK_DSP_GPIO_Port GPIOA
#define FAULT_Pin GPIO_PIN_5
#define FAULT_GPIO_Port GPIOC
#define DC1_IN2_Pin GPIO_PIN_12
#define DC1_IN2_GPIO_Port GPIOB
#define DC1_IN1_Pin GPIO_PIN_12
#define DC1_IN1_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define SCL_DSP_Pin GPIO_PIN_3
#define SCL_DSP_GPIO_Port GPIOB
#define SDA_DSP_Pin GPIO_PIN_5
#define SDA_DSP_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
