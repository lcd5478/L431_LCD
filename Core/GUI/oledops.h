/************************************************************************************************
 $ @Descripttion: ͷ��ע��
 $ @version: 
 $ @Author: wws
 $ @Date: 2022-03-26 15:25:10
 $ @LastEditors: wws
 $ @LastEditTime: 2022-03-26 17:09:26
 $ @FilePath: \lcde\Core\GUI\oledops.h
************************************************************************************************/
#ifndef __OLEDOPS_H
#define __OLEDOPS_H

#include "main.h"

//DISPALY API
void oled_show_welcome(void);	//OLED��ʾ��ӭ
void oled_show_Init(void);		//OLED��ʾ������ʼ��
void oled_show_self_check(void);	//OLED��ʾ�����Լ�

void oled_show_low_power(void);				//OLED�Ե͵���
void oled_clear_all(void);				//OLED����
void oled_clear_window(void);			//OLED�崰������
void oled_clear_notitle(void);		//��������֮�������
void oled_show_mainwindow(void);	//OLED��ʾ������
void oled_set_power(enum POWER_CAP cap);	//���õ������
void oled_set_time(RTC_TimeTypeDef time);		//����ʱ��


void oled_set_wlstate(bool State);	//��������״̬

void oled_show_menu(void);					//��ʾ������Ϣ

		

#endif	//__OLEDOPS_H

