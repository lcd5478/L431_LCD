/************************************************************************************************
 $ @Descripttion: 头部注释
 $ @version: 
 $ @Author: wws
 $ @Date: 2022-03-26 13:49:31
 $ @LastEditors: wws
 $ @LastEditTime: 2022-03-26 15:37:51
 $ @FilePath: \lcde\Core\GUI\display.c
************************************************************************************************/
#include "display.h"
#include "oledops.h"

#include "main.h"





//显示函数操作集
DISPLSY_OPS display_ops = {
	.init = EPD_HW_Init,
	.show_welcome = oled_show_welcome,
	.show_Init = oled_show_Init,
	.show_self_check = oled_show_self_check,

	.show_low_power = oled_show_low_power,
	.clear_all = oled_clear_all,
	.clear_window = oled_clear_window,
	.clear_notitle = oled_clear_notitle,
	.show_mainwindow = oled_show_mainwindow,
	.set_power = oled_set_power,
	.set_time = oled_set_time,

	.set_wlstate = oled_set_wlstate,

	.show_menu = oled_show_menu,
};


void Display_Init(void)
{
	display_ops.init();
}	




