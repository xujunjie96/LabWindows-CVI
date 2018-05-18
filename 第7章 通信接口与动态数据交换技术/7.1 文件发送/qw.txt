#include <rs232.h>
#include <ansi_c.h>
#include "toolbox.h"
#include <cvirte.h>		
#include <userint.h>
#include "uartfilereceive.h"

static int panelHandle;
static int bytesread;
static char filename[MAX_FILENAME_LEN];
static char pathname[MAX_PATHNAME_LEN];

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "uartfilereceive.uir", PANEL)) < 0)
		return -1;
	
	OpenComConfig (2, "", 57600, 0, 8, 1, 32767, 32767);  //打开并配置串口2 
	SetComTime (2, 5.0);   //设置通信超时时限
	SetXMode (2, 0);   //禁止串口软件握手
	SetCTSMode (2, LWRS_HWHANDSHAKE_OFF);  //禁止串口硬件握手
	
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK filesel (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	int selstatus;
	switch (event)
	{
		case EVENT_COMMIT:
			selstatus = DirSelectPopup ("", "保存文件", 1, 1, pathname);
			if (selstatus)
			{
				strcat(pathname,"\\");
				strcat(pathname,filename);
				SetCtrlVal (panelHandle, PANEL_STRING_2, pathname);
				}
			break;
	}
	return 0;
}

int CVICALLBACK Quitcallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			CloseCom (2);//关闭串口2
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK receivefilename (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			filename[0]='\0';
			SetCtrlVal (panelHandle, PANEL_STRING, "");
			bytesread = ComRdTerm (2, filename, 256, 13);  //读取字符串直到回车出现
			filename[bytesread]='\0';	//当出现回车符后 在其后面加上结束符
			SetCtrlVal (panelHandle, PANEL_STRING, filename);
			break;
	}
	return 0;
}

int CVICALLBACK receivefile (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	int result;
	int filesize;
	int intputqueuelen;
	FILE *stream;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_STRING_2, pathname);
			result=FileExists (pathname, &filesize);  //判断文件是否存在
			if(!result)
			{
				stream = fopen (pathname, "wb+");
				fclose (stream);
			}
			XModemConfig (2, 10.0, 10, 5.0, 1024);   //设置串口2调制解调器参数
			XModemReceive (2, pathname);	//设置串口2接收文件数据
			intputqueuelen=GetInQLen (2);
			if(intputqueuelen==0)
			{
				MessagePopup ("文件保存", "文件保存完毕！");

			}

			break;
	}
	return 0;
}
