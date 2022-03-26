#include "mainWindow.h"
#include "statusBar.h"
#include "display.h"
#include "menuWindow.h"
#include "gui.h"
#include "main.h"
#include "key.h"
#include "gpio.h"


HWin hWin_main;		//�����ھ��

extern bool WL_IsLink;		//��������״̬

//�����ڻص�����
void _cbMainWindow(PMsg *msg)
{
	switch(msg->msgID)
	{
		//��ʾ��Ϣ
		case ShowMsg:

			display_ops.show_mainwindow();
		
			#if DEVICE_TYPE == 2
			display_ops.show_contip(WL_IsLink);
			#endif
			break;
		
		//������Ϣ
		case HideMsg:
			display_ops.clear_window();
			break;
		
		//������Ϣ
		case KeyMsg:
			switch(msg->Data.v)
			{
				case Keyboard_MAIN:
					
					#if ENABLE_KEY_OPT
					CODEIIC_Init(); 
					delay_ms(10);
					if(CodeCard_Check() == 0)
					{
						codeState = CODE_WAIT_READ;		//����Ϊ�ȴ�����״̬
						GUI_HideWindow(hWin_main);		//����������
						GUI_ShowWindow(hWin_code);		//��ʾCODE���´���
						GUI_SetFocus(hWin_code);			//�۽�CODE���´���
					}
					else
					{
						PortA_Init();			//�˿�A��ʼ��
						GUI_HideWindow(hWin_main);			//����������
						GUI_ShowWindow(hWin_menu);			//��ʾ�˵�����
						GUI_SetFocus(hWin_menu);				//�۽��˵�����
					}
					#endif
					break;
				
				case Keyboard_MAIN_LongPress:
				
					#if ENABLE_KEY_OPT
					GUI_HideWindow(hWin_main);		//����������
					GUI_ShowWindow(hWin_his);			//��ʾ��ʷ����
					GUI_SetFocus(hWin_his);				//�۽���ʷ����
					#endif
					break;
			}
			break;
			
		//�û���Ϣ ��������ʾʱ���յ�
		case UserSMsg:
			switch(msg->Data.v)
			{
				case WlStateVal:		//����״̬������Ϣ
					#if DEVICE_TYPE == 2
					display_ops.show_contip(WL_IsLink);
					#endif
					break;
			}
			break;
			
		//�û���Ϣ ����״̬��Ӧ
		case UserMsg:
			switch(msg->Data.v)
			{
				case DormancyVal:		//����״̬������Ϣ
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

//�����ڳ�ʼ��
void mainWindowInit(void)
{
	hWin_main = GUI_CreatWindow(_cbMainWindow, 0);		//��ʼ��������
}

//���ڳ�ʼ��
void WinInit(void)
{
	mainWindowInit();		//�����ڳ�ʼ��
	StatusBarInit();		//״̬����ʼ��
	menuWindowInit();		//�˵����ڳ�ʼ��
	GUI_ShowWindow(hWin_main);		//��ʾ������
	GUI_ShowWindow(hWin_status);	//��ʾ״̬��
	GUI_SetFocus(hWin_main);			//�۽�������
}

