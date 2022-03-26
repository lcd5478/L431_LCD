#include "statusBar.h"
#include "display.h"
#include "main.h"
#include "gpio.h"


HWin hWin_status;					//״̬�����ھ��
#if BATTERY_EN		==0	    	//0:�������е�� 1:����û�е��
enum POWER_CAP batCap = POWER_NULL;		//����������
enum CHRG_ST chargeState;	//������״̬
#endif
bool secTwinkleSt = FALSE;	//����˸״̬

//״̬���ص�����
void _cbStatusBar(PMsg *msg)
{
	switch(msg->msgID)
	{
		//��ʾ��Ϣ
		case ShowMsg:
//			RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);
//			RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
		
		#if BATTERY_EN		==0	    	//0:�������е�� 1:����û�е��
			display_ops.set_power(batCap);
		#endif
//			display_ops.set_time(RTC_TimeStruct);

		
			#if SHOW_WIRESS_LINK
				display_ops.set_wlstate(WL_IsLink);
			#endif

			break;
		
		//������Ϣ
		case HideMsg:
		
			break;
		
		//�û���Ϣ
		case UserMsg:
		
			break;
		
		//�û���Ϣ ��������ʾʱ���յ�
		case UserSMsg:
			switch(msg->Data.v)
			{
			#if BATTERY_EN		==0	    	//0:�������е�� 1:����û�е��
				//���������û���Ϣ
				case PowerVal:
					display_ops.set_power(batCap);
					break;
				
				//����û���Ϣ
				case ChargeVal:
					if(batCap < POWER_HIGH) batCap++;
					else
					{
						batCap = POWER_NULL;
					}
					display_ops.set_power(batCap);
					break;
					#endif
				//RTCˢ����Ϣ	
				case RtcUpdateVal:
					
					//setDateTime(&calendar);
					break;
				
					
				//����״̬����
				case WlStateVal:
					#if SHOW_WIRESS_LINK
						display_ops.set_wlstate(WL_IsLink);
					#endif
					break;
					
			}
			break;
	}
}

//���ڳ�ʼ��
void StatusBarInit(void)
{
	hWin_status = GUI_CreatWindow(_cbStatusBar, 0);		//��ʼ��״̬��
}


