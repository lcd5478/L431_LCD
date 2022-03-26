/************************************************************************************************
 $ @Descripttion: ͷ��ע��
 $ @version: 
 $ @Author: wws
 $ @Date: 2021-05-19 18:12:54
 $ @LastEditors: wws
 $ @LastEditTime: 2022-01-10 11:22:07
 $ @FilePath: \MMYG_JTJ_v1.3.4\USER\gui.h
************************************************************************************************/
#ifndef _GUI_H_
#define _GUI_H_

//GUI��������
#define winNumMax	30	//��󴰿�����
#define msgNumMax	30	//�����Ϣ������

//GUI�ض���
#define GUI_TRUE	1
#define GUI_FALSE	0	
#define GUI_NULL	0

//msg���� 
#define InitMsg		0x1000	//���ڳ�ʼ����Ϣ
#define FreeMsg		0x1100	//�����ͷ���Ϣ
#define HideMsg		0x2000	//����������Ϣ
#define ShowMsg		0x2100	//����������Ϣ
#define UserMsg		0x3000	//�û���Ϣ

//��0x5000��msg�������ʾʱ��ִ��
#define FocusMsg	0x5000	//�۽���Ϣ
#define KeyMsg		0x5100	//������Ϣ
#define UserSMsg	0x6000	//�û���Ϣ ��������ʾʱ��Ч

typedef int HWin;					//���ھ��

//msg�ṹ��
typedef struct{
	int msgID;			//��Ϣ���
	HWin hWin;			//Ŀ����
	HWin hWinSrc;		//Դ���
	union {
    const void *p;
    int v;
  } Data;
}PMsg;

//��Ϣ���нṹ��
typedef volatile struct{
	unsigned int bufSize;			//�������ܴ�С
	volatile PMsg *pStart;    //��ʼ��ַ
	volatile PMsg *pEnd;      //������ַ
	volatile PMsg *pBuf;      //�������׵�ַ
}PMsgQueue;

//�������ڽṹ��
typedef struct WINDOW{
	HWin hWin;											//���ھ��	
	void (*_cbWindow)(PMsg *msg);		//���ڻص�����
	unsigned char showFlag;					//��ʾ��־λ
	HWin father;										//�����ھ��
}GuiWindow;

//API
void GUI_Init(void);	//GUI��ʼ������
void GUI_Exec(void);	//GUIִ�к���
HWin GUI_CreatWindow(void (*_cbWindow)(PMsg*), HWin fWin);	//�½����ں���
GuiWindow* GUI_GetWindow(HWin hWin);	//GUI�Ӿ����ȡ����ָ��
void GUI_SetFocus(HWin hWin);					//GUI�۽�����
HWin GUI_GetFocus(void);							//GUI��ȡ�۽�����
void GUI_ShowWindow(HWin hWin);				//GUI��ʾ����
void GUI_HideWindow(HWin hWin);				//GUI���ش���
void GUI_RstWindow(HWin hWin);				//GUI���ô���
void GUI_FreeWindow(HWin hWin);				//GUI�ͷŴ���	���ܵ�Ч�����ô��ڡ�������ǰ��ִ���ͷ���Ϣ
void GUI_SendMsg(HWin hWinSrc, HWin hWin, int id, int val);		//GUI������Ϣ
void GUI_SendKeyMsg(unsigned int key_val);										//GUI���Ͱ�����Ϣ
void GUI_SendUserMsg(HWin hWin, unsigned int val, unsigned char msgType);		//GUI�����û���Ϣ


#endif	//_GUI_H_

