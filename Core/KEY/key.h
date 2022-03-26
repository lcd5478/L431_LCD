#ifndef __KEY_H
#define __KEY_H

#include "main.h"

//按键键值定义
#define LongPress				10
#define LongPressTime		800

#define Keyboard_MAIN		1			//主键
#define Keyboard_Release	5		//释放
#define Keyboard_MAIN_LongPress		Keyboard_MAIN + LongPress


//按键端口定义
#define PORT_MAIN		GPIOA
#define PIN_MAIN		GPIO_PIN_0

#define PORT1_MAIN		KEY2_R_GPIO_Port
#define PIN1_MAIN		KEY2_R_Pin

#define PORT2_MAIN		KEY3_L_GPIO_Port
#define PIN2_MAIN		KEY3_L_Pin


//按键读取定义
#define KEY_MAIN			HAL_GPIO_ReadPin(PORT_MAIN,PIN_MAIN)


//API
void Keyboard_Init(void);		



#endif	//__KEY_H

