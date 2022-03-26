/************************************************************************************************
 $ @Descripttion: ͷ��ע��
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


HWin hWin_menu;				//�˵����ھ��


//�˵����ڻص�����
void _cbMenuWindow(PMsg *msg)
{
	static uint8_t selState = 0;
	
	switch(msg->msgID)
	{		
		//��ʾ��Ϣ
		case ShowMsg:

			selState = 2;
			display_ops.show_menu();

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
			
					if(selState < 2) selState++;
					else selState = 0;
				
					break;
				
				case Keyboard_MAIN_LongPress:
	
					
					if(selState == 0)				//��������
					{

					}
					else if(selState == 1)	//����ӫ�����
					{

					}
					else	//�˳�����������
					{
						GUI_HideWindow(hWin_menu);			//���ز˵�����
						GUI_ShowWindow(hWin_main);			//��ʾ������
						GUI_SetFocus(hWin_main);				//�۽�������
					}
					break;
			}
			break;
	}
}

//��ʷ���ڳ�ʼ��
void menuWindowInit(void)
{
	hWin_menu = GUI_CreatWindow(_cbMenuWindow, hWin_main);		//��ʼ���˵�����Ϊ�����ڵ��Ӵ���
}






