/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "epaper.h"
#include "picture.h"
typedef enum {FALSE = 0,TRUE = !FALSE} bool;
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

//鐢垫睜鐢甸噺鏋氫妇
enum POWER_CAP
{
  POWER_NULL = 0, //绌虹數閲?
  POWER_LOW,      //浣庣數閲?
  POWER_MID,      //涓?鐢甸??
  POWER_HIGH,     //楂樼數閲?
};
//鍏呯數鐘舵?佹灇涓?
enum CHRG_ST
{
  CHRG_NULL = 0, //鏃犲厖鐢靛櫒
  CHRG_ING,      //鍏呯數涓?
  CHRG_FIN,      //鍏呮弧鍟?
};
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
//一般状态值定义
#define WlStateVal			0x1200	//无线状态值

#define PowerVal				0x1210	//电量状态值
#define ChargeVal				0x1220	//充电状态值
#define RtcUpdateVal		0x1230	//RTC更新状态值

#define DormancyVal		  0x1240	//RTC更新状态值
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CHRG_Pin GPIO_PIN_2
#define CHRG_GPIO_Port GPIOA
#define STDBY_Pin GPIO_PIN_3
#define STDBY_GPIO_Port GPIOA
#define SPI1_CS_Pin GPIO_PIN_4
#define SPI1_CS_GPIO_Port GPIOA
#define KEY2_R_Pin GPIO_PIN_0
#define KEY2_R_GPIO_Port GPIOB
#define KEY3_L_Pin GPIO_PIN_1
#define KEY3_L_GPIO_Port GPIOB
#define PWR_ESP_EN_Pin GPIO_PIN_8
#define PWR_ESP_EN_GPIO_Port GPIOA
#define LCD_MOSI_Pin GPIO_PIN_11
#define LCD_MOSI_GPIO_Port GPIOA
#define LCD_SCK_Pin GPIO_PIN_12
#define LCD_SCK_GPIO_Port GPIOA
#define LCD_CS_Pin GPIO_PIN_15
#define LCD_CS_GPIO_Port GPIOA
#define LCD_DC_Pin GPIO_PIN_3
#define LCD_DC_GPIO_Port GPIOB
#define LCD_RES_Pin GPIO_PIN_4
#define LCD_RES_GPIO_Port GPIOB
#define LCD_BUSY_Pin GPIO_PIN_5
#define LCD_BUSY_GPIO_Port GPIOB
#define PWR_EN_Pin GPIO_PIN_3
#define PWR_EN_GPIO_Port GPIOH
/* USER CODE BEGIN Private defines */






/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
