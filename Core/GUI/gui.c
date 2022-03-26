#include "gui.h"

GuiWindow guiWin[winNumMax];	//窗口容器
static int winNumCur;					//当前窗口数量
PMsgQueue pMsgQueue;					//消息队列
PMsg pMsg[msgNumMax];					//消息容器
HWin focusWin = GUI_NULL;

/*******************************************
	函数：创建消息队列函数
	作用：创建一个GUI消息队列
	PMsgQueue *pQueue：需初始化队列的指针
	PMsg *pBuf：队列缓存内存的指针
	unsigned int bufSize：队列大小
********************************************/
void MsgQueueCreate(PMsgQueue *pQueue, PMsg *pBuf, unsigned int bufSize)
{
    pQueue->bufSize = bufSize;
    pQueue->pBuf = pBuf;
    pQueue->pStart = pBuf;
    pQueue->pEnd = pBuf;
}

/*******************************************
	函数：消息入队函数
	作用：将消息加入队列
	PMsgQueue *pQueue：操作的目标消息队列
	PMsg *pBuf：要插入的消息首地址指针
	unsigned int bufSize：插入的消息数量
********************************************/
unsigned int MsgQueuePacketIn(PMsgQueue *pQueue, PMsg *pData, unsigned int len)
{
    volatile PMsg *pEnd = GUI_NULL;
    unsigned int index = 0;

    pEnd = pQueue->pEnd;
    for (index=0; index<len; index++)
    {
        if(++pEnd >= pQueue->pBuf + pQueue->bufSize) 
				{
					pEnd = pQueue->pBuf;
				}
        if(pEnd == pQueue->pStart) break;
        *pQueue->pEnd = *pData++;
        pQueue->pEnd = pEnd;
    }
    
    return index;
}

/*******************************************
	函数：消息出队函数
	作用：从队列中取出消息
	PMsgQueue *pQueue：操作的目标消息队列
	PMsg *pBuf：取出消息存放内存的首地址指针
	unsigned int bufSize：取出的消息数量
********************************************/
unsigned int MsgQueuePacketOut(PMsgQueue *pQ8, PMsg *pData, unsigned int dataLen)
{
    unsigned int index = 0;

    while ((pQ8->pStart != pQ8->pEnd) && (index < dataLen) && (index < pQ8->bufSize))
    {
        pData[index++] = *pQ8->pStart++;
        if (pQ8->pStart >= pQ8->pBuf + pQ8->bufSize) 
        {
            pQ8->pStart = pQ8->pBuf;
        }
    }

    return index;
}

/*******************************************
	函数：发送消息函数
	作用：向目标窗口发送消息
	HWin hWinSrc：源窗口的句柄
	HWin hWin：目标窗口的句柄
	int id：消息ID
	int val：消息值
********************************************/
void GUI_SendMsg(HWin hWinSrc, HWin hWin, int id, int val)
{
	PMsg msg;
	
	msg.msgID = id;
	msg.Data.v = val;
	msg.hWin = hWin;
	msg.hWinSrc = hWinSrc;
	MsgQueuePacketIn(&pMsgQueue, &msg, 1);
}

/*******************************************
	函数：发送按键消息函数
	作用：向聚焦窗口发送按键消息
	unsigned int key_val：按键键值
********************************************/
void GUI_SendKeyMsg(unsigned int key_val)
{
	GUI_SendMsg(GUI_NULL, GUI_NULL, KeyMsg, key_val);
}

/*******************************************
	函数：发送用户消息函数
	作用：向目标窗口发送用户消息
	HWin hWin：目标窗口的句柄
	unsigned int val：用户消息值
	unsigned char msgType：用户消息类型 0：直接发送	1：仅目标窗口显示时发送
********************************************/
void GUI_SendUserMsg(HWin hWin, unsigned int val, unsigned char msgType)
{
	if(msgType) GUI_SendMsg(GUI_NULL, hWin, UserSMsg, val);
	else GUI_SendMsg(GUI_NULL, hWin, UserMsg, val);
}

/*******************************************
	函数：获取窗口指针函数
	作用：从窗口句柄获取窗口指针
	HWin hWin：需获取窗口的句柄
********************************************/
GuiWindow* GUI_GetWindow(HWin hWin)
{
	return &guiWin[hWin-1];
}

/*******************************************
	函数：设置聚焦函数
	作用：设置窗口为聚焦窗口
	HWin hWin：需聚焦窗口的句柄
********************************************/
void GUI_SetFocus(HWin hWin)
{
	PMsg msg;
	 
	msg.msgID = FocusMsg;
	msg.Data.v = GUI_NULL;
	msg.hWin = hWin;
	msg.hWinSrc = GUI_NULL;
	MsgQueuePacketIn(&pMsgQueue, &msg, 1);
}

/*******************************************
	函数：获取聚焦函数
	作用：获取当前聚焦窗口
	返回：聚焦窗口的句柄
********************************************/
HWin GUI_GetFocus(void)
{
	return focusWin;
}

/*******************************************
	函数：显示窗口函数
	作用：显示一个已初始化的窗口
	HWin hWin：需显示窗口的句柄
********************************************/
void GUI_ShowWindow(HWin hWin)
{
	PMsg msg;
	
	msg.msgID = ShowMsg;
	msg.Data.v = GUI_NULL;
	msg.hWin = hWin;
	msg.hWinSrc = GUI_NULL;
	MsgQueuePacketIn(&pMsgQueue, &msg, 1);
}

/*******************************************
	函数：隐藏窗口函数
	作用：隐藏一个已初始化的窗口
	HWin hWin：需隐藏窗口的句柄
********************************************/
void GUI_HideWindow(HWin hWin)
{
	PMsg msg;

	msg.msgID = HideMsg;
	msg.Data.v = GUI_NULL;
	msg.hWin = hWin;
	msg.hWinSrc = GUI_NULL;
	MsgQueuePacketIn(&pMsgQueue, &msg, 1);
}

/*******************************************
	函数：新建窗口函数
	作用：新建立一个窗口
	void (*_cbWindow)(PMsg *msg)：窗口回调函数
	HWin fWin：父窗口句柄
********************************************/
HWin GUI_CreatWindow(void (*_cbWindow)(PMsg*), HWin fWin)
{
	HWin hWin;
	GuiWindow* pWin;
	PMsg msg;
	
	//分配句柄
	if(winNumCur >= winNumMax) return -1;
	else
	{
		for(hWin=1; hWin<=winNumMax; hWin++)
		{
			if(guiWin[hWin-1].hWin == GUI_NULL) break;
			else
			{
				if(hWin == winNumMax) return -1;
			}
		}
	}
	
	//填充窗口
	pWin = GUI_GetWindow(hWin);
	pWin->hWin = hWin;
	pWin->_cbWindow = _cbWindow;
	pWin->showFlag = GUI_FALSE;
	if(fWin > GUI_NULL) pWin->father = fWin;	//配置父窗口
	else pWin->father = GUI_NULL;
	if(winNumCur < winNumMax) winNumCur++;
	else return -1;
	
	//发送初始化消息
	msg.msgID = InitMsg;
	msg.Data.v = GUI_NULL;
	msg.hWin = hWin;
	msg.hWinSrc = GUI_NULL;
	MsgQueuePacketIn(&pMsgQueue, &msg, 1);
	
	return hWin;
}

/*******************************************
	函数：GUI重置窗口函数
	作用：重置一个窗口
********************************************/
void GUI_RstWindow(HWin hWin)
{
	GuiWindow* pWin;
	
	pWin = GUI_GetWindow(hWin);					//获取句柄对应窗口指针
	if(focusWin == hWin) focusWin = GUI_NULL;	//若重置窗口聚焦则重置聚焦
	
	//重置窗口
	pWin->hWin = GUI_NULL;
	pWin->showFlag = GUI_FALSE;
	pWin->_cbWindow = GUI_NULL;
	pWin->father = GUI_NULL;
}	

/*******************************************
	函数：GUI释放窗口函数
	作用：释放一个窗口
********************************************/
void GUI_FreeWindow(HWin hWin)
{
	PMsg msg;
	
	//发送释放信号
	msg.msgID = FreeMsg;
	msg.Data.v = GUI_NULL;
	msg.hWin = hWin;
	msg.hWinSrc = GUI_NULL;
	MsgQueuePacketIn(&pMsgQueue, &msg, 1);
}

/*******************************************
	函数：GUI初始化函数
	作用：初始化GUI所需配置
********************************************/
void GUI_Init(void)
{
	HWin hWin;
	
	//释放所有窗口
	for(hWin=1; hWin<=winNumMax; hWin++)
	{
		GUI_RstWindow(hWin);
	}
	winNumCur = 0;		//重置窗口统计
	
	//创建消息队列
	MsgQueueCreate(&pMsgQueue, pMsg, msgNumMax);
}

/*******************************************
	函数：GUI执行函数
	作用：执行整个GUI、需持续执行
********************************************/
void GUI_Exec(void)
{
	PMsg msg;
	GuiWindow *win;
	
	while(MsgQueuePacketOut(&pMsgQueue, &msg, 1))		//若队列中存在消息则执行
	{	
		if(msg.msgID == KeyMsg) msg.hWin = focusWin;	//按键发送到聚焦窗口
		
		//定向消息
		if(msg.hWin > GUI_NULL)
		{
			win = GUI_GetWindow(msg.hWin);	//获取目标窗口
			
			//预配置
			switch(msg.msgID)
			{
				//聚焦窗口
				case FocusMsg:
					if(win->showFlag) focusWin = msg.hWin;	//仅能聚焦显示的窗口
					break;
			}
			
			if(win->showFlag || msg.msgID < 0x5000) win->_cbWindow(&msg);	//执行目标回调函数
			
			//后续配置
			switch(msg.msgID)
			{
				//显示窗口
				case ShowMsg: 
					win->showFlag = GUI_TRUE; 
					break;	
				
				//隐藏窗口
				case HideMsg: 
					win->showFlag = GUI_FALSE; 
					if(focusWin == msg.hWin) focusWin = GUI_NULL;		//若聚焦窗口被隐藏则重置聚焦
					break;	
				
				//释放窗口
				case FreeMsg:
					GUI_RstWindow(msg.hWin);
					break;
			}
		}
		else
		{
			//全局消息暂不处理
		}
	}
}
