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

//电池电量枚举
enum POWER_CAP
{
  POWER_NULL = 0, //空电�?
  POWER_LOW,      //低电�?
  POWER_MID,      //�?电�??
  POWER_HIGH,     //高电�?
};
//充电状�?�枚�?
enum CHRG_ST
{
  CHRG_NULL = 0, //无充电器
  CHRG_ING,      //充电�?
  CHRG_FIN,      //充满�?
};
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
//һ��״ֵ̬����
#define WlStateVal			0x1200	//����״ֵ̬

#define PowerVal				0x1210	//����״ֵ̬
#define ChargeVal				0x1220	//���״ֵ̬
#define RtcUpdateVal		0x1230	//RTC����״ֵ̬

#define DormancyVal		  0x1240	//RTC����״ֵ̬
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
