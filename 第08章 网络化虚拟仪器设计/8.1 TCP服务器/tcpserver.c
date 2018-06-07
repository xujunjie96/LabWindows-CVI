#include <tcpsupp.h>
#include <formatio.h>
#include "toolbox.h"
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "tcpserver.h"

static unsigned int conversationHandle;//TCP连接句柄
static int portnumber=0;
static int panelHandle;

int TCPServerCB(unsigned handle,int xType,int errCode,void *callbackData);//自定义服务器端回调函数
void gethostinfo(void);//自定义函数 的到主机信息
void setmode(int connect,int disconnect,int send);//自定义函数 设置连接 断开以及发送按钮的互锁状态

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "tcpserver.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	//在退出时 如果tcp连接句柄存在 则删除句柄 并注销TCP服务器
	if (conversationHandle)
	{
		DisconnectTCPClient (conversationHandle);
		UnregisterTCPServer (portnumber);
	}
	return 0;
}

int CVICALLBACK connect (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	int status;
	char portnumberstring[10];
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_STRING_PORTNUMBER, portnumberstring);	 //获得tcp服务器端口号
			Fmt(&portnumber,"%i<%s",portnumberstring);
			status=RegisterTCPServer (portnumber, TCPServerCB, 1);//注册tcp服务器
			if(status==0)
			{
				SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 1);
				setmode(1,0,0);
				gethostinfo();//自定义函数
			}
			
			break;
	}
	return 0;
}

int CVICALLBACK disconnect (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);
			//如果tcp连接句柄存在 则断开
			if (conversationHandle)
			{
				DisconnectTCPClient (conversationHandle);
			}
			conversationHandle=0;
			UnregisterTCPServer (portnumber);   //注销服务器
			setmode(0,1,1);
			//设置客户机状态显示
			SetCtrlVal (panelHandle, PANEL_STRING_CLIENTIP, "");
			SetCtrlVal (panelHandle, PANEL_STRING_CLIENTIPNAME, "");
			SetCtrlVal (panelHandle, PANEL_LED_CLIENT, 0);
			SetCtrlVal (panelHandle, PANEL_LED_SERVER, 0); 
			break;
	}
	return 0;
}

int CVICALLBACK timer (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	double datapointernumber[10];
	double value[1];
	double result;
	
	switch (event)
	{
		case EVENT_TIMER_TICK:
			result=Random (0, 100);		//产生0-100的随机数
			value[0]=result;
			PlotStripChart (panelHandle, PANEL_STRIPCHART, value, 1, 0, 0, VAL_DOUBLE);
			
			//如果存在tcp连接 则将数据发送到tcp服务器
			if(conversationHandle)
			{
				 datapointernumber[0]=result;
				 ServerTCPWrite (conversationHandle, datapointernumber, 10, 0);
			}
			break;
	}
	return 0;
}

int CVICALLBACK clear (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_COMMIT:
			ResetTextBox (panelHandle, PANEL_TEXTBOX, "");
			break;
	}
	return 0;
}

int CVICALLBACK QuitCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK send (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	char datapointer[1000];
	switch (event)
	{
		case EVENT_COMMIT:
			 GetCtrlVal (panelHandle, PANEL_TEXTBOX, &datapointer[0]);		  //
			 //在所获字符串中加上回车换行以及结束标识符
			 strcat(datapointer,"\r");
			 strcat(datapointer,"\n");
			 strcat(datapointer,"\0");
			 ServerTCPWrite (conversationHandle, datapointer, 1000, 0); //向tcp客户机发送数据
			 ResetTextBox (panelHandle, PANEL_TEXTBOX, "");
			break;
	}
	return 0;
}

//自定义服务器端回调函数 
int TCPServerCB(unsigned handle,int xType,int errCode,void *callbackData)
{
	 char datapointer[1000];
	 char buffer[50];
	 
	 switch(xType)
	 {
	 	//TCP连接时产生的事件
		 case TCP_CONNECT :
			 conversationHandle=handle; //当有客户机连接时，获得tcp连接句柄
			 //获得客户机信息
			 GetTCPPeerAddr (conversationHandle, buffer, 50);   
			 SetCtrlVal (panelHandle, PANEL_STRING_CLIENTIP, buffer);
			 GetTCPPeerName (conversationHandle, buffer, 50); 
	 		 SetCtrlVal (panelHandle, PANEL_STRING_CLIENTIPNAME, buffer);
			 SetCtrlVal (panelHandle, PANEL_LED_CLIENT, 1);
			 SetTCPDisconnectMode (conversationHandle, TCP_DISCONNECT_AUTO);//设置tcp断开方式
			 break;
		//TCP断开时产生的事件 
		case TCP_DISCONNECT :
			if(conversationHandle==handle)
			{
				 conversationHandle=0;
				 //设置客户机状态显示
				SetCtrlVal (panelHandle, PANEL_STRING_CLIENTIP, "");
				SetCtrlVal (panelHandle, PANEL_STRING_CLIENTIPNAME, "");
				SetCtrlVal (panelHandle, PANEL_LED_CLIENT, 0);
			}
			break;
		//TCP数据准备好 读取数据事件 
		case TCP_DATAREADY :
			ServerTCPRead (conversationHandle, datapointer, 1000, 0); //从tcp客户机读取数据
			SetCtrlVal (panelHandle, PANEL_TEXTBOX, datapointer);
			break; 
	 }
	 return 0;
}

//自定义函数 的到主机信息 
void gethostinfo(void) 
{
	char buffer[50];
	GetTCPHostAddr (buffer, 50);
	SetCtrlVal (panelHandle, PANEL_STRING_SERVERIP, buffer);
	SetCtrlVal (panelHandle, PANEL_STRING_ADDRESS, buffer);
	GetTCPHostName (buffer, 50);
	SetCtrlVal (panelHandle, PANEL_STRING_SERVERNAME, buffer);
	SetCtrlVal (panelHandle, PANEL_LED_SERVER, 1); 
}

//自定义函数 设置连接 断开以及发送按钮的互锁状态 
void setmode(int connect,int disconnect,int send)
{
	SetCtrlAttribute (panelHandle, PANEL_CMD_CONNECT, ATTR_DIMMED, connect);
	SetCtrlAttribute (panelHandle, PANEL_CMD_DISCONNECT, ATTR_DIMMED, disconnect);
	SetCtrlAttribute (panelHandle, PANEL_CMD_SEND, ATTR_DIMMED, send);
}



