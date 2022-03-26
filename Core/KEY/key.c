#include "key.h"
#include "common.h"
#include "gpio.h"
#include "tim.h"
#include <stdbool.h>
bool KeyboardIsProcess = FALSE;		//按键处理标志
bool LongPressFlag = FALSE;
int keyValue;		//键值
uint32_t waitTime,waitTime1;		//按键计时值


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
		
	if(GPIO_Pin==GPIO_PIN_0)
	{
			if(KeyboardIsProcess == FALSE)		//防反复触发
		{
			KeyboardIsProcess = TRUE;				//置位处理标志
			keyValue = Keyboard_MAIN;				//设置键值
			waitTime = 0;										//清空计数
			HAL_TIM_Base_Start_IT(&htim16);
		}  
	}
	if(GPIO_Pin==GPIO_PIN_1)
	{
			if(KeyboardIsProcess == FALSE)		//防反复触发
		{
			KeyboardIsProcess = TRUE;				//置位处理标志
			keyValue = Keyboard_MAIN;				//设置键值
			waitTime1 = 0;										//清空计数
			HAL_TIM_Base_Start_IT(&htim16);
		}  
	}
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM16)
	{
		//按键处理
		if(KeyboardIsProcess)
		{
			//按键状态判断
			if(!KEY_MAIN)
			{
				waitTime++;			//按下时间累计
				
				if(waitTime == LongPressTime) 
				{
					GUI_SendKeyMsg(keyValue + LongPress);		//发送长按信号
				}
			}
			else
			{
				if(waitTime > 50)		//按键防抖动
				{
					if(waitTime >= LongPressTime)
					{
						GUI_SendKeyMsg(Keyboard_Release);		//发送长按释放信号
						LongPressFlag = FALSE;
					}
					else 
					{
						GUI_SendKeyMsg(keyValue);		//发送按键按下信号
					}
					waitTime = 0;
				}
				HAL_TIM_Base_Stop_IT(&htim16);
				KeyboardIsProcess = FALSE;	//恢复标志位
			}
		}	
	}
	else if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
	
}


//键盘初始化
void Keyboard_Init(void)
{
	
}



