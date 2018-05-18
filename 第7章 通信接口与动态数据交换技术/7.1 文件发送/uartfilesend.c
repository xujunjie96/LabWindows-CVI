#include <rs232.h>
#include <utility.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "uartfilesend.h"

static int panelHandle;
static int byteswritten;
static char filename[MAX_FILENAME_LEN];
static char pathname[MAX_PATHNAME_LEN];

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "uartfilesend.uir", PANEL)) < 0)
		return -1;
	OpenComConfig (1, "", 57600, 0, 8, 1, 32767, 32767); //打开并配置串口1
	SetComTime (1, 5.0);	//设置通信超时时限
	SetXMode (1, 0);   //禁止串口软件握手
	SetCTSMode (1, LWRS_HWHANDSHAKE_OFF); //禁止硬件握手
	
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
			filename[0]='\0';
			selstatus= FileSelectPopup ("", "*.*", "", "打开文件", VAL_LOAD_BUTTON, 0, 0, 1, 1, pathname);
			if (selstatus>=0)
			{
				SetCtrlVal (panelHandle, PANEL_STRING, pathname);
				SplitPath (pathname, NULL, NULL, filename);	//分解获得文件名
			}
			break;
	}
	return 0;
}

int CVICALLBACK sendfilename (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	int comstatus;
	int outputqueuelen;
	switch (event)
	{
		case EVENT_COMMIT:
			strcat(filename,"\r");
			byteswritten=ComWrt (1, filename, strlen(filename));//向com1写入文件名字符串
		//	byteswritten=ComWrt (1, "adsp", 4);//向com1写入文件名字符串 
			break;
	}
	return 0;
}

int CVICALLBACK sendfile (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	int outputqueuelen;
	switch (event)
	{
		case EVENT_COMMIT:
			XModemConfig (1, 10.0, 10, 5.0, 1024);//设置串口1调制解调器参数
			XModemSend (1, pathname);   //从串口1发送文件数据
			outputqueuelen = GetOutQLen (1);	//获得串口1输出队列的字符数目
			if(outputqueuelen==0)
			{
				MessagePopup ("文件传输", "文件传输完毕！");
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
			CloseCom (1);//关闭串口1
			
			QuitUserInterface (0);
			break;
	}
	return 0;
}
