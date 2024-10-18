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
#include "stm32g4xx_hal.h"

#include "stm32g4xx_ll_spi.h"
#include "stm32g4xx_ll_tim.h"
#include "stm32g4xx_ll_system.h"
#include "stm32g4xx_ll_gpio.h"
#include "stm32g4xx_ll_exti.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_cortex.h"
#include "stm32g4xx_ll_rcc.h"
#include "stm32g4xx_ll_utils.h"
#include "stm32g4xx_ll_pwr.h"
#include "stm32g4xx_ll_dma.h"

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
#define RT_Pin LL_GPIO_PIN_0
#define RT_GPIO_Port GPIOC
#define RB_Pin LL_GPIO_PIN_1
#define RB_GPIO_Port GPIOC
#define Y_Pin LL_GPIO_PIN_2
#define Y_GPIO_Port GPIOC
#define X_Pin LL_GPIO_PIN_3
#define X_GPIO_Port GPIOC
#define B_Pin LL_GPIO_PIN_0
#define B_GPIO_Port GPIOA
#define A_Pin LL_GPIO_PIN_1
#define A_GPIO_Port GPIOA
#define VR_Pin LL_GPIO_PIN_2
#define VR_GPIO_Port GPIOA
#define START_Pin LL_GPIO_PIN_3
#define START_GPIO_Port GPIOA
#define THRBO_Pin LL_GPIO_PIN_4
#define THRBO_GPIO_Port GPIOA
#define HOME_Pin LL_GPIO_PIN_5
#define HOME_GPIO_Port GPIOA
#define BACK_Pin LL_GPIO_PIN_6
#define BACK_GPIO_Port GPIOA
#define CLEAR_Pin LL_GPIO_PIN_7
#define CLEAR_GPIO_Port GPIOA
#define BAT_CHECK_Pin LL_GPIO_PIN_0
#define BAT_CHECK_GPIO_Port GPIOB
#define LED_Pin LL_GPIO_PIN_2
#define LED_GPIO_Port GPIOB
#define HL_Pin LL_GPIO_PIN_11
#define HL_GPIO_Port GPIOB
#define VL_Pin LL_GPIO_PIN_12
#define VL_GPIO_Port GPIOB
#define RS_Pin LL_GPIO_PIN_13
#define RS_GPIO_Port GPIOB
#define HR_Pin LL_GPIO_PIN_14
#define HR_GPIO_Port GPIOB
#define LS_Pin LL_GPIO_PIN_15
#define LS_GPIO_Port GPIOB
#define LB_Pin LL_GPIO_PIN_6
#define LB_GPIO_Port GPIOC
#define LT_Pin LL_GPIO_PIN_7
#define LT_GPIO_Port GPIOC
#define UP_Pin LL_GPIO_PIN_8
#define UP_GPIO_Port GPIOC
#define LEFT_Pin LL_GPIO_PIN_9
#define LEFT_GPIO_Port GPIOC
#define DOWM_Pin LL_GPIO_PIN_8
#define DOWM_GPIO_Port GPIOA
#define RIGHT_Pin LL_GPIO_PIN_9
#define RIGHT_GPIO_Port GPIOA
#define BUZZER_Pin LL_GPIO_PIN_10
#define BUZZER_GPIO_Port GPIOA
#define TFT_RS_Pin LL_GPIO_PIN_11
#define TFT_RS_GPIO_Port GPIOC
#define TFT_RES_Pin LL_GPIO_PIN_2
#define TFT_RES_GPIO_Port GPIOD
#define SPI1_CS_Pin LL_GPIO_PIN_6
#define SPI1_CS_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
void SystemClock_Config(void);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
