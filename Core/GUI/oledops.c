/************************************************************************************************
 $ @Descripttion: ͷ��ע��
 $ @version: 
 $ @Author: wws
 $ @Date: 2021-12-21 16:00:25
 $ @LastEditors: wws
 $ @LastEditTime: 2022-03-26 17:06:01
 $ @FilePath: \lcde\Core\GUI\oledops.c
************************************************************************************************/
#include "oledops.h"
#include "main.h"
#include "rtc.h"
#include "epaper.h"
#include "picture.h"



//OLED��ʾ��ӭ
void oled_show_welcome()
{
	// OLED_Clear(0, 0, 256, 64, 0x00);
	// OLED_ShowString(32, 24, (unsigned char*)"Welcome to use the device", 16);
}

//OLED��ʾ��ʼ��
void oled_show_Init()
{
	// OLED_Clear(0, 0, 256, 64, 0x00);
	// // OLED_DrawBMP(32, 20, 24, 24, preheat);
	// OLED_ShowChinese(64, 20, (unsigned char*)"������ʼ��",  24);//��ʼ����
	// OLED_ShowString(190, 10, (unsigned char*)"...", 32);
}

//OLED��ʾ�����Լ�
void oled_show_self_check()
{
	// OLED_Clear(0, 0, 256, 64, 0x00);
	// OLED_DrawBMP(32, 20, 24, 24, self_check);
	// OLED_ShowChinese(64, 20, (unsigned char*)"�����Լ���",  24);
	// OLED_ShowString(190, 10, (unsigned char*)"...", 32);
}

//OLED��ʾ�����Լ�ʧ��


//OLED�Ե͵���
void oled_show_low_power()
{
	// OLED_Clear(0, 0, 256, 64, 0x00);
	// OLED_ShowChinese(28, 20, (unsigned char*)"��������",  24);
	// OLED_ShowString(124, 16, (unsigned char*)"!", 32);
	// OLED_ShowChinese(140, 20, (unsigned char*)"����",  24);
	// OLED_ShowString(212, 16, (unsigned char*)"!", 32);
}

//OLED����
void oled_clear_all()
{
	// OLED_Clear(0, 0, 256, 64, 0x00);
}

//OLED�崰��
void oled_clear_window()
{
	// OLED_Clear(0, 0, 128, 16, 0x00);
	// OLED_Clear(0, 16, 256, 64, 0x00);
}

//��������֮�������
void oled_clear_notitle()
{
	// OLED_Clear(0, 17, 256, 64, 0x00);
}

//OLED��ʾ������
void oled_show_mainwindow()
{
	// OLED_DrawBMP(0, 0, 64, 64, gImage_TXYS);
	
	// #if DEVICE_TYPE != 2
	// OLED_ShowChinese(104, 24, (unsigned char*)"�ȴ���ȡ",  24);
	// #endif
}




//���õ������
void oled_set_power(enum POWER_CAP cap)
{
	// switch (cap)
	// {
	// 	case POWER_NULL:
	// 		OLED_DrawBMP(235, 1, 20, 16, NoPwr);
	// 		break;
	// 	case POWER_LOW:
	// 		OLED_DrawBMP(235, 1, 20, 16, LowPwr);
	// 		break;
	// 	case POWER_MID:
	// 		OLED_DrawBMP(235, 1, 20, 16, MidPwr);
	// 		break;
	// 	case POWER_HIGH:
	// 		OLED_DrawBMP(235, 1, 20, 16, HighPwr);
	// 		break;
	// 	default:
	// 		break;
	// }
}

//����ʱ��
void oled_set_time(RTC_TimeTypeDef time)
{
	// OLED_ShowNum(184, 0, time.RTC_Hours, 2, 16);
	// OLED_ShowNum(208, 0, time.RTC_Minutes, 2, 16);
}





//��������״̬
void oled_set_wlstate(bool State)
{
	// if (State) OLED_DrawBMP(130, 3, 12, 12, BtLink);
	// else OLED_DrawBMP(130, 3, 12, 12, BtUnlink);
}



//OLED��ʾ���˵�
void oled_show_menu()			
{
	// OLED_ShowChinese(0, 0, (unsigned char*)"��ѡ�����",  16);
	// OLED_ShowString(80, 0, (unsigned char*)":", 16);
	// OLED_ShowChinese(32, 20, (unsigned char*)"��������",  16);
	// OLED_ShowChinese(32, 40, (unsigned char*)"����ӫ�����",  16);
	// OLED_ShowChinese(172, 40, (unsigned char*)"�˳�",  16);
}


