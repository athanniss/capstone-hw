/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32h7xx_hal.h"

#include "stm32h7xx_ll_adc.h"
#include "stm32h7xx_ll_i2c.h"
#include "stm32h7xx_ll_rcc.h"
#include "stm32h7xx_ll_crs.h"
#include "stm32h7xx_ll_bus.h"
#include "stm32h7xx_ll_system.h"
#include "stm32h7xx_ll_exti.h"
#include "stm32h7xx_ll_cortex.h"
#include "stm32h7xx_ll_utils.h"
#include "stm32h7xx_ll_pwr.h"
#include "stm32h7xx_ll_dma.h"
#include "stm32h7xx_ll_usart.h"
#include "stm32h7xx_ll_gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
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
#define USR_OUT_COIL_Pin LL_GPIO_PIN_1
#define USR_OUT_COIL_GPIO_Port GPIOB
#define LED_USR_3_Pin LL_GPIO_PIN_15
#define LED_USR_3_GPIO_Port GPIOB
#define LED_USR_1_Pin LL_GPIO_PIN_6
#define LED_USR_1_GPIO_Port GPIOC
#define USR_ENC1_B_Pin LL_GPIO_PIN_8
#define USR_ENC1_B_GPIO_Port GPIOC
#define USR_ENC1_A_Pin LL_GPIO_PIN_9
#define USR_ENC1_A_GPIO_Port GPIOC
#define USR_SW_ENC_Pin LL_GPIO_PIN_2
#define USR_SW_ENC_GPIO_Port GPIOD
#define USR_SW_1_Pin LL_GPIO_PIN_3
#define USR_SW_1_GPIO_Port GPIOB
#define USR_SW_2_Pin LL_GPIO_PIN_5
#define USR_SW_2_GPIO_Port GPIOB
#define USR_SW_2_EXTI_IRQn EXTI9_5_IRQn
#define LED_USR_2_Pin LL_GPIO_PIN_8
#define LED_USR_2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
