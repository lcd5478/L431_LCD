#include "key.h"
#include "common.h"
#include "gpio.h"
#include "tim.h"
#include <stdbool.h>
bool KeyboardIsProcess = FALSE;		//���������־
bool LongPressFlag = FALSE;
int keyValue;		//��ֵ
uint32_t waitTime,waitTime1;		//������ʱֵ


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
		
	if(GPIO_Pin==GPIO_PIN_0)
	{
			if(KeyboardIsProcess == FALSE)		//����������
		{
			KeyboardIsProcess = TRUE;				//��λ�����־
			keyValue = Keyboard_MAIN;				//���ü�ֵ
			waitTime = 0;										//��ռ���
			HAL_TIM_Base_Start_IT(&htim16);
		}  
	}
	if(GPIO_Pin==GPIO_PIN_1)
	{
			if(KeyboardIsProcess == FALSE)		//����������
		{
			KeyboardIsProcess = TRUE;				//��λ�����־
			keyValue = Keyboard_MAIN;				//���ü�ֵ
			waitTime1 = 0;										//��ռ���
			HAL_TIM_Base_Start_IT(&htim16);
		}  
	}
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM16)
	{
		//��������
		if(KeyboardIsProcess)
		{
			//����״̬�ж�
			if(!KEY_MAIN)
			{
				waitTime++;			//����ʱ���ۼ�
				
				if(waitTime == LongPressTime) 
				{
					GUI_SendKeyMsg(keyValue + LongPress);		//���ͳ����ź�
				}
			}
			else
			{
				if(waitTime > 50)		//����������
				{
					if(waitTime >= LongPressTime)
					{
						GUI_SendKeyMsg(Keyboard_Release);		//���ͳ����ͷ��ź�
						LongPressFlag = FALSE;
					}
					else 
					{
						GUI_SendKeyMsg(keyValue);		//���Ͱ��������ź�
					}
					waitTime = 0;
				}
				HAL_TIM_Base_Stop_IT(&htim16);
				KeyboardIsProcess = FALSE;	//�ָ���־λ
			}
		}	
	}
	else if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
	
}


//���̳�ʼ��
void Keyboard_Init(void)
{
	
}



