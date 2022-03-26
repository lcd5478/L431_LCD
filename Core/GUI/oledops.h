/************************************************************************************************
 $ @Descripttion: 头部注释
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
void oled_show_welcome(void);	//OLED显示欢迎
void oled_show_Init(void);		//OLED显示仪器初始化
void oled_show_self_check(void);	//OLED显示仪器自检

void oled_show_low_power(void);				//OLED显低电量
void oled_clear_all(void);				//OLED清屏
void oled_clear_window(void);			//OLED清窗口区域
void oled_clear_notitle(void);		//清屏标题之外的区域
void oled_show_mainwindow(void);	//OLED显示主界面
void oled_set_power(enum POWER_CAP cap);	//设置电池容量
void oled_set_time(RTC_TimeTypeDef time);		//设置时钟


void oled_set_wlstate(bool State);	//设置无线状态

void oled_show_menu(void);					//显示测量信息

		

#endif	//__OLEDOPS_H

