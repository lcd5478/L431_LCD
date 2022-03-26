/************************************************************************************************
 $ @Descripttion: 头部注释
 $ @version: 
 $ @Author: wws
 $ @Date: 2022-03-26 13:49:01
 $ @LastEditors: wws
 $ @LastEditTime: 2022-03-26 16:28:17
 $ @FilePath: \lcde\Core\GUI\menuWindow.c
************************************************************************************************/
#include "menuWindow.h"
#include "mainWindow.h"
#include "key.h"
#include "main.h"
#include "display.h"
#include "gpio.h"


HWin hWin_menu;				//菜单窗口句柄


//菜单窗口回调函数
void _cbMenuWindow(PMsg *msg)
{
	static uint8_t selState = 0;
	
	switch(msg->msgID)
	{		
		//显示消息
		case ShowMsg:

			selState = 2;
			display_ops.show_menu();

			break;
		
		//隐藏消息
		case HideMsg:
			display_ops.clear_window();
			break;
		
		//按键消息
		case KeyMsg:
			switch(msg->Data.v)
			{
				case Keyboard_MAIN:
			
					if(selState < 2) selState++;
					else selState = 0;
				
					break;
				
				case Keyboard_MAIN_LongPress:
	
					
					if(selState == 0)				//胶体金测试
					{

					}
					else if(selState == 1)	//免疫荧光测试
					{

					}
					else	//退出返回主界面
					{
						GUI_HideWindow(hWin_menu);			//隐藏菜单窗口
						GUI_ShowWindow(hWin_main);			//显示主窗口
						GUI_SetFocus(hWin_main);				//聚焦主窗口
					}
					break;
			}
			break;
	}
}

//历史窗口初始化
void menuWindowInit(void)
{
	hWin_menu = GUI_CreatWindow(_cbMenuWindow, hWin_main);		//初始化菜单窗口为主窗口的子窗口
}






