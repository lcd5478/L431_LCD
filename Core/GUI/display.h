/************************************************************************************************
 $ @Descripttion: 头部注释
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


//显示函数操作集
typedef struct
{
	void (*init)(void);							//初始化
	void (*show_welcome)(void);			//清屏并显示欢迎
	void (*show_Init)(void);				//清屏并显示初始化
	void (*show_self_check)(void);	//清屏并显示仪器自检中


	void (*show_low_power)(void);		//显示电量过低
	void (*clear_all)(void);				//清屏
	void (*clear_window)(void);			//清窗口区域
	void (*clear_notitle)(void);		//清除标题外的窗口区域
	void (*show_mainwindow)(void);	//显示主界面

	void (*set_power)(enum POWER_CAP);	//设置电池容量显示
	void (*set_time)(RTC_TimeTypeDef);	//设置时间显示


	void (*set_wlstate)(bool);					//设置无线状态


	void (*show_menu)(void);						//显示主菜单
	
	
}DISPLSY_OPS;

extern DISPLSY_OPS display_ops;

void Display_Init(void);



#endif	//__DISPLAY_H

