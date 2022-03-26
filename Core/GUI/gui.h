/************************************************************************************************
 $ @Descripttion: 头部注释
 $ @version: 
 $ @Author: wws
 $ @Date: 2021-05-19 18:12:54
 $ @LastEditors: wws
 $ @LastEditTime: 2022-01-10 11:22:07
 $ @FilePath: \MMYG_JTJ_v1.3.4\USER\gui.h
************************************************************************************************/
#ifndef _GUI_H_
#define _GUI_H_

//GUI参数定义
#define winNumMax	30	//最大窗口数量
#define msgNumMax	30	//最大消息缓存量

//GUI特定宏
#define GUI_TRUE	1
#define GUI_FALSE	0	
#define GUI_NULL	0

//msg定义 
#define InitMsg		0x1000	//窗口初始化消息
#define FreeMsg		0x1100	//窗口释放消息
#define HideMsg		0x2000	//窗口隐藏消息
#define ShowMsg		0x2100	//窗口隐藏消息
#define UserMsg		0x3000	//用户消息

//≥0x5000的msg需界面显示时才执行
#define FocusMsg	0x5000	//聚焦消息
#define KeyMsg		0x5100	//按键消息
#define UserSMsg	0x6000	//用户消息 仅界面显示时有效

typedef int HWin;					//窗口句柄

//msg结构体
typedef struct{
	int msgID;			//消息编号
	HWin hWin;			//目标句柄
	HWin hWinSrc;		//源句柄
	union {
    const void *p;
    int v;
  } Data;
}PMsg;

//消息队列结构体
typedef volatile struct{
	unsigned int bufSize;			//缓冲区总大小
	volatile PMsg *pStart;    //起始地址
	volatile PMsg *pEnd;      //结束地址
	volatile PMsg *pBuf;      //缓冲区首地址
}PMsgQueue;

//交互窗口结构体
typedef struct WINDOW{
	HWin hWin;											//窗口句柄	
	void (*_cbWindow)(PMsg *msg);		//窗口回调函数
	unsigned char showFlag;					//显示标志位
	HWin father;										//父窗口句柄
}GuiWindow;

//API
void GUI_Init(void);	//GUI初始化函数
void GUI_Exec(void);	//GUI执行函数
HWin GUI_CreatWindow(void (*_cbWindow)(PMsg*), HWin fWin);	//新建窗口函数
GuiWindow* GUI_GetWindow(HWin hWin);	//GUI从句柄获取窗口指针
void GUI_SetFocus(HWin hWin);					//GUI聚焦窗口
HWin GUI_GetFocus(void);							//GUI获取聚焦窗口
void GUI_ShowWindow(HWin hWin);				//GUI显示窗口
void GUI_HideWindow(HWin hWin);				//GUI隐藏窗口
void GUI_RstWindow(HWin hWin);				//GUI重置窗口
void GUI_FreeWindow(HWin hWin);				//GUI释放窗口	功能等效于重置窗口、但重置前会执行释放消息
void GUI_SendMsg(HWin hWinSrc, HWin hWin, int id, int val);		//GUI发送消息
void GUI_SendKeyMsg(unsigned int key_val);										//GUI发送按键消息
void GUI_SendUserMsg(HWin hWin, unsigned int val, unsigned char msgType);		//GUI发送用户消息


#endif	//_GUI_H_

