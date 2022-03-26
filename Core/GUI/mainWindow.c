#include "mainWindow.h"
#include "statusBar.h"
#include "display.h"
#include "menuWindow.h"
#include "gui.h"
#include "main.h"
#include "key.h"
#include "gpio.h"


HWin hWin_main;		//主窗口句柄

extern bool WL_IsLink;		//无线连接状态

//主窗口回调函数
void _cbMainWindow(PMsg *msg)
{
	switch(msg->msgID)
	{
		//显示消息
		case ShowMsg:

			display_ops.show_mainwindow();
		
			#if DEVICE_TYPE == 2
			display_ops.show_contip(WL_IsLink);
			#endif
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
					
					#if ENABLE_KEY_OPT
					CODEIIC_Init(); 
					delay_ms(10);
					if(CodeCard_Check() == 0)
					{
						codeState = CODE_WAIT_READ;		//设置为等待读卡状态
						GUI_HideWindow(hWin_main);		//隐藏主窗口
						GUI_ShowWindow(hWin_code);		//显示CODE更新窗口
						GUI_SetFocus(hWin_code);			//聚焦CODE更新窗口
					}
					else
					{
						PortA_Init();			//端口A初始化
						GUI_HideWindow(hWin_main);			//隐藏主窗口
						GUI_ShowWindow(hWin_menu);			//显示菜单窗口
						GUI_SetFocus(hWin_menu);				//聚焦菜单窗口
					}
					#endif
					break;
				
				case Keyboard_MAIN_LongPress:
				
					#if ENABLE_KEY_OPT
					GUI_HideWindow(hWin_main);		//隐藏主窗口
					GUI_ShowWindow(hWin_his);			//显示历史窗口
					GUI_SetFocus(hWin_his);				//聚焦历史窗口
					#endif
					break;
			}
			break;
			
		//用户消息 仅界面显示时会收到
		case UserSMsg:
			switch(msg->Data.v)
			{
				case WlStateVal:		//无线状态更新消息
					#if DEVICE_TYPE == 2
					display_ops.show_contip(WL_IsLink);
					#endif
					break;
			}
			break;
			
		//用户消息 任意状态响应
		case UserMsg:
			switch(msg->Data.v)
			{
				case DormancyVal:		//无线状态更新消息
					HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN1);
					/* Clear the related wakeup pin flag */
						__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
					/* Re-enable all used wakeup sources: Pin1(PA.0) */
					HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);
					/* Request to enter STANDBY mode  */
					HAL_PWR_EnterSTANDBYMode();
					break;
				
			}
			break;
	}
}

//主窗口初始化
void mainWindowInit(void)
{
	hWin_main = GUI_CreatWindow(_cbMainWindow, 0);		//初始化主窗口
}

//窗口初始化
void WinInit(void)
{
	mainWindowInit();		//主窗口初始化
	StatusBarInit();		//状态栏初始化
	menuWindowInit();		//菜单窗口初始化
	GUI_ShowWindow(hWin_main);		//显示主窗口
	GUI_ShowWindow(hWin_status);	//显示状态栏
	GUI_SetFocus(hWin_main);			//聚焦主窗口
}

