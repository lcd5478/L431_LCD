#include "gui.h"

GuiWindow guiWin[winNumMax];	//��������
static int winNumCur;					//��ǰ��������
PMsgQueue pMsgQueue;					//��Ϣ����
PMsg pMsg[msgNumMax];					//��Ϣ����
HWin focusWin = GUI_NULL;

/*******************************************
	������������Ϣ���к���
	���ã�����һ��GUI��Ϣ����
	PMsgQueue *pQueue�����ʼ�����е�ָ��
	PMsg *pBuf�����л����ڴ��ָ��
	unsigned int bufSize�����д�С
********************************************/
void MsgQueueCreate(PMsgQueue *pQueue, PMsg *pBuf, unsigned int bufSize)
{
    pQueue->bufSize = bufSize;
    pQueue->pBuf = pBuf;
    pQueue->pStart = pBuf;
    pQueue->pEnd = pBuf;
}

/*******************************************
	��������Ϣ��Ӻ���
	���ã�����Ϣ�������
	PMsgQueue *pQueue��������Ŀ����Ϣ����
	PMsg *pBuf��Ҫ�������Ϣ�׵�ַָ��
	unsigned int bufSize���������Ϣ����
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
	��������Ϣ���Ӻ���
	���ã��Ӷ�����ȡ����Ϣ
	PMsgQueue *pQueue��������Ŀ����Ϣ����
	PMsg *pBuf��ȡ����Ϣ����ڴ���׵�ַָ��
	unsigned int bufSize��ȡ������Ϣ����
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
	������������Ϣ����
	���ã���Ŀ�괰�ڷ�����Ϣ
	HWin hWinSrc��Դ���ڵľ��
	HWin hWin��Ŀ�괰�ڵľ��
	int id����ϢID
	int val����Ϣֵ
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
	���������Ͱ�����Ϣ����
	���ã���۽����ڷ��Ͱ�����Ϣ
	unsigned int key_val��������ֵ
********************************************/
void GUI_SendKeyMsg(unsigned int key_val)
{
	GUI_SendMsg(GUI_NULL, GUI_NULL, KeyMsg, key_val);
}

/*******************************************
	�����������û���Ϣ����
	���ã���Ŀ�괰�ڷ����û���Ϣ
	HWin hWin��Ŀ�괰�ڵľ��
	unsigned int val���û���Ϣֵ
	unsigned char msgType���û���Ϣ���� 0��ֱ�ӷ���	1����Ŀ�괰����ʾʱ����
********************************************/
void GUI_SendUserMsg(HWin hWin, unsigned int val, unsigned char msgType)
{
	if(msgType) GUI_SendMsg(GUI_NULL, hWin, UserSMsg, val);
	else GUI_SendMsg(GUI_NULL, hWin, UserMsg, val);
}

/*******************************************
	��������ȡ����ָ�뺯��
	���ã��Ӵ��ھ����ȡ����ָ��
	HWin hWin�����ȡ���ڵľ��
********************************************/
GuiWindow* GUI_GetWindow(HWin hWin)
{
	return &guiWin[hWin-1];
}

/*******************************************
	���������þ۽�����
	���ã����ô���Ϊ�۽�����
	HWin hWin����۽����ڵľ��
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
	��������ȡ�۽�����
	���ã���ȡ��ǰ�۽�����
	���أ��۽����ڵľ��
********************************************/
HWin GUI_GetFocus(void)
{
	return focusWin;
}

/*******************************************
	��������ʾ���ں���
	���ã���ʾһ���ѳ�ʼ���Ĵ���
	HWin hWin������ʾ���ڵľ��
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
	���������ش��ں���
	���ã�����һ���ѳ�ʼ���Ĵ���
	HWin hWin�������ش��ڵľ��
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
	�������½����ں���
	���ã��½���һ������
	void (*_cbWindow)(PMsg *msg)�����ڻص�����
	HWin fWin�������ھ��
********************************************/
HWin GUI_CreatWindow(void (*_cbWindow)(PMsg*), HWin fWin)
{
	HWin hWin;
	GuiWindow* pWin;
	PMsg msg;
	
	//������
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
	
	//��䴰��
	pWin = GUI_GetWindow(hWin);
	pWin->hWin = hWin;
	pWin->_cbWindow = _cbWindow;
	pWin->showFlag = GUI_FALSE;
	if(fWin > GUI_NULL) pWin->father = fWin;	//���ø�����
	else pWin->father = GUI_NULL;
	if(winNumCur < winNumMax) winNumCur++;
	else return -1;
	
	//���ͳ�ʼ����Ϣ
	msg.msgID = InitMsg;
	msg.Data.v = GUI_NULL;
	msg.hWin = hWin;
	msg.hWinSrc = GUI_NULL;
	MsgQueuePacketIn(&pMsgQueue, &msg, 1);
	
	return hWin;
}

/*******************************************
	������GUI���ô��ں���
	���ã�����һ������
********************************************/
void GUI_RstWindow(HWin hWin)
{
	GuiWindow* pWin;
	
	pWin = GUI_GetWindow(hWin);					//��ȡ�����Ӧ����ָ��
	if(focusWin == hWin) focusWin = GUI_NULL;	//�����ô��ھ۽������þ۽�
	
	//���ô���
	pWin->hWin = GUI_NULL;
	pWin->showFlag = GUI_FALSE;
	pWin->_cbWindow = GUI_NULL;
	pWin->father = GUI_NULL;
}	

/*******************************************
	������GUI�ͷŴ��ں���
	���ã��ͷ�һ������
********************************************/
void GUI_FreeWindow(HWin hWin)
{
	PMsg msg;
	
	//�����ͷ��ź�
	msg.msgID = FreeMsg;
	msg.Data.v = GUI_NULL;
	msg.hWin = hWin;
	msg.hWinSrc = GUI_NULL;
	MsgQueuePacketIn(&pMsgQueue, &msg, 1);
}

/*******************************************
	������GUI��ʼ������
	���ã���ʼ��GUI��������
********************************************/
void GUI_Init(void)
{
	HWin hWin;
	
	//�ͷ����д���
	for(hWin=1; hWin<=winNumMax; hWin++)
	{
		GUI_RstWindow(hWin);
	}
	winNumCur = 0;		//���ô���ͳ��
	
	//������Ϣ����
	MsgQueueCreate(&pMsgQueue, pMsg, msgNumMax);
}

/*******************************************
	������GUIִ�к���
	���ã�ִ������GUI�������ִ��
********************************************/
void GUI_Exec(void)
{
	PMsg msg;
	GuiWindow *win;
	
	while(MsgQueuePacketOut(&pMsgQueue, &msg, 1))		//�������д�����Ϣ��ִ��
	{	
		if(msg.msgID == KeyMsg) msg.hWin = focusWin;	//�������͵��۽�����
		
		//������Ϣ
		if(msg.hWin > GUI_NULL)
		{
			win = GUI_GetWindow(msg.hWin);	//��ȡĿ�괰��
			
			//Ԥ����
			switch(msg.msgID)
			{
				//�۽�����
				case FocusMsg:
					if(win->showFlag) focusWin = msg.hWin;	//���ܾ۽���ʾ�Ĵ���
					break;
			}
			
			if(win->showFlag || msg.msgID < 0x5000) win->_cbWindow(&msg);	//ִ��Ŀ��ص�����
			
			//��������
			switch(msg.msgID)
			{
				//��ʾ����
				case ShowMsg: 
					win->showFlag = GUI_TRUE; 
					break;	
				
				//���ش���
				case HideMsg: 
					win->showFlag = GUI_FALSE; 
					if(focusWin == msg.hWin) focusWin = GUI_NULL;		//���۽����ڱ����������þ۽�
					break;	
				
				//�ͷŴ���
				case FreeMsg:
					GUI_RstWindow(msg.hWin);
					break;
			}
		}
		else
		{
			//ȫ����Ϣ�ݲ�����
		}
	}
}
