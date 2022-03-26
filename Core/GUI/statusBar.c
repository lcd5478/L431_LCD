#include "statusBar.h"
#include "display.h"
#include "main.h"
#include "gpio.h"


HWin hWin_status;					//状态栏窗口句柄
#if BATTERY_EN		==0	    	//0:仪器带有电池 1:仪器没有电池
enum POWER_CAP batCap = POWER_NULL;		//定义电池容量
enum CHRG_ST chargeState;	//定义充电状态
#endif
bool secTwinkleSt = FALSE;	//秒闪烁状态

//状态栏回调函数
void _cbStatusBar(PMsg *msg)
{
	switch(msg->msgID)
	{
		//显示消息
		case ShowMsg:
//			RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);
//			RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
		
		#if BATTERY_EN		==0	    	//0:仪器带有电池 1:仪器没有电池
			display_ops.set_power(batCap);
		#endif
//			display_ops.set_time(RTC_TimeStruct);

		
			#if SHOW_WIRESS_LINK
				display_ops.set_wlstate(WL_IsLink);
			#endif

			break;
		
		//隐藏消息
		case HideMsg:
		
			break;
		
		//用户消息
		case UserMsg:
		
			break;
		
		//用户消息 仅界面显示时会收到
		case UserSMsg:
			switch(msg->Data.v)
			{
			#if BATTERY_EN		==0	    	//0:仪器带有电池 1:仪器没有电池
				//电量更新用户消息
				case PowerVal:
					display_ops.set_power(batCap);
					break;
				
				//充电用户消息
				case ChargeVal:
					if(batCap < POWER_HIGH) batCap++;
					else
					{
						batCap = POWER_NULL;
					}
					display_ops.set_power(batCap);
					break;
					#endif
				//RTC刷新消息	
				case RtcUpdateVal:
					
					//setDateTime(&calendar);
					break;
				
					
				//无线状态更新
				case WlStateVal:
					#if SHOW_WIRESS_LINK
						display_ops.set_wlstate(WL_IsLink);
					#endif
					break;
					
			}
			break;
	}
}

//窗口初始化
void StatusBarInit(void)
{
	hWin_status = GUI_CreatWindow(_cbStatusBar, 0);		//初始化状态栏
}


