/************************************************************************************************
 $ @Descripttion: ͷ��ע��
 $ @version: 
 $ @Author: wws
 $ @Date: 2022-03-26 13:49:31
 $ @LastEditors: wws
 $ @LastEditTime: 2022-03-26 17:10:00
 $ @FilePath: \lcde\Core\GUI\display.h
************************************************************************************************/
#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "main.h"


//��ʾ����������
typedef struct
{
	void (*init)(void);							//��ʼ��
	void (*show_welcome)(void);			//��������ʾ��ӭ
	void (*show_Init)(void);				//��������ʾ��ʼ��
	void (*show_self_check)(void);	//��������ʾ�����Լ���


	void (*show_low_power)(void);		//��ʾ��������
	void (*clear_all)(void);				//����
	void (*clear_window)(void);			//�崰������
	void (*clear_notitle)(void);		//���������Ĵ�������
	void (*show_mainwindow)(void);	//��ʾ������

	void (*set_power)(enum POWER_CAP);	//���õ��������ʾ
	void (*set_time)(RTC_TimeTypeDef);	//����ʱ����ʾ


	void (*set_wlstate)(bool);					//��������״̬


	void (*show_menu)(void);						//��ʾ���˵�
	
	
}DISPLSY_OPS;

extern DISPLSY_OPS display_ops;

void Display_Init(void);



#endif	//__DISPLAY_H

