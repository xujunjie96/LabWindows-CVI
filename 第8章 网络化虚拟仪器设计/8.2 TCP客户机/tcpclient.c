#include <utility.h>
#include <tcpsupp.h>
#include <formatio.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "tcpclient.h"

static unsigned int conversationHandle;//TCP连接句柄
static int portnumber=0;
static int panelHandle, ctrlarray;

int TCPClientCB(unsigned handle,int xType,int errCode,void *callbackData);//自定义服务器端回调函数
void gethostinfo(unsigned int conversationHandle);//自定义函数 的到主机信息
void setmode(int connect,int disconnect,int send);//自定义函数 设置连接 断开以及发送按钮的互锁状态

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "tcpclient.uir", PANEL)) < 0)
		return -1;
	ctrlarray = GetCtrlArrayFromResourceID (panelHandle, CTRLARRAY);
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK disconnect (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//如果tcp连接句柄存在 则断开
			if (conversationHandle)	   //
			{
				DisableBreakOnLibraryErrors ();	   //当产生库函数错误时，禁止弹出运行时错误对话框
				DisconnectFromTCPServer (conversationHandle);
			}
			setmode(0,1,1);
			//设置客户机状态显示
			SetCtrlVal (panelHandle, PANEL_STRING_SERVERIP, "");
			SetCtrlVal (panelHandle, PANEL_STRING_SERVERNAME, "");
		//	SetCtrlVal (panelHandle, PANEL_LED_CLIENT, 0);
			SetCtrlVal (panelHandle, PANEL_LED_SERVER, 0); 
			break;
	}
	return 0;
}

int CVICALLBACK connect (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	char address[50];
	unsigned int conversationHandle;
	int status;
	char portnumberstring[10]; 
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_STRING_PORTNUMBER, portnumberstring);	 //获得tcp服务器端口号
			Fmt(&portnumber,"%i<%s",portnumberstring);
			GetCtrlVal (panelHandle, PANEL_STRING_ADDRESS, address);	 //获得tcp服务器地址
			status= ConnectToTCPServer (&conversationHandle, portnumber, address, TCPClientCB, 0, 0);
			if(status==0)
			{
				setmode(1,0,0);
				gethostinfo(conversationHandle);//自定义函数
			}
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
			 ClientTCPWrite (conversationHandle, datapointer, 1000, 0); //向服务器发送数据
			 ResetTextBox (panelHandle, PANEL_TEXTBOX, "");
			break;
	}
	return 0;
}

//自定义服务器端回调函数
int TCPClientCB(unsigned handle,int xType,int errCode,void *callbackData)
{
	char datapointer[1000];
	char buffer[50];
	int datamode;
	double datapointernumber[10];
	int result1,result2; 
	
	unsigned int add1,add2,i,j;
	int a;
	//a=strlen(datapointernumber);
	//add1=&datapointernumber;
	//add2=&datapointer;
	switch(xType)
	 {
		//TCP断开时产生的事件 
		case TCP_DISCONNECT :
		
			SetCtrlVal (panelHandle, PANEL_STRING_SERVERIP, "");
			SetCtrlVal (panelHandle, PANEL_STRING_SERVERNAME, "");
			SetCtrlVal (panelHandle, PANEL_LED_CLIENT, 0);
			SetTCPDisconnectMode (conversationHandle, TCP_DISCONNECT_AUTO);//设置tcp断开方式 
			break;
		//TCP数据准备好 读取数据事件 
		case TCP_DATAREADY :
			//如果是第二次连接或者更多次连接，从本函数获得句柄
			conversationHandle=handle;
			ClientTCPRead (conversationHandle, datapointer, 1000, 0); //从tcp服务器读取数据 
			//如果末尾包含回车和换行符 则认为是字符串 如果没有 则认为是数据 写入stripchart中
			result1=FindPattern (datapointer, 0, -1, "\r", 0, 0);
			result2=FindPattern (datapointer, 0, -1, "\n", 0, 0);
			if(result1>=0&&result2>=0)
			{
				SetCtrlVal (panelHandle, PANEL_TEXTBOX, datapointer);//将字符串数据写入Textbox内
			}
			else
			{
			//	ClientTCPRead (conversationHandle, datapointernumber, 10, 0); //从tcp服务器读取数据
				//	Fmt(&datapointernumber,"%i<%s",datapointer);
			/*	for(i=0;i<a;i++)
				{
					*(add1+i) = *(add2+i)	;
				}*/
			memcpy ( datapointernumber, datapointer, sizeof(datapointernumber) );
				PlotStripChart (panelHandle, PANEL_STRIPCHART, datapointernumber, 1, 0, 0, VAL_DOUBLE);
			}
			
			break; 
	 }
	 return 0;
}

//自定义函数 的到主机信息
void gethostinfo(unsigned int conversationHandle)
{
	char buffer[50]; 
	//获得远程主机信息
	GetTCPPeerAddr (conversationHandle, buffer, 50);   
	SetCtrlVal (panelHandle, PANEL_STRING_SERVERIP, buffer);
	GetTCPPeerName (conversationHandle, buffer, 50); 
	SetCtrlVal (panelHandle, PANEL_STRING_SERVERNAME, buffer);
	SetCtrlVal (panelHandle, PANEL_LED_SERVER, 1);
	GetTCPHostAddr (buffer, 50);	//获取本地计算机的IP地址
	SetCtrlVal (panelHandle, PANEL_STRING_CLIENTIP, buffer);
	GetTCPHostName (buffer, 50);
	SetCtrlVal (panelHandle, PANEL_STRING_CLIENTIPNAME, buffer);
	SetCtrlVal (panelHandle, PANEL_LED_CLIENT, 1); 
}

//自定义函数 设置连接 断开以及发送按钮的互锁状态 
void setmode(int connect,int disconnect,int send)
{
	SetCtrlAttribute (panelHandle, PANEL_CMD_CONNECT, ATTR_DIMMED, connect);
	SetCtrlAttribute (panelHandle, PANEL_CMD_DISCONNECT, ATTR_DIMMED, disconnect);
	SetCtrlAttribute (panelHandle, PANEL_CMD_SEND, ATTR_DIMMED, send);
}
