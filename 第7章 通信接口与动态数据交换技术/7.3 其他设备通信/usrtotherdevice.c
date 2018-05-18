#include <utility.h>
#include <ansi_c.h>
#include <formatio.h>
#include <rs232.h>
#include <cvirte.h>		
#include <userint.h>
#include "usrtotherdevice.h"

static int panelHandle;
static void *callbackdata;

void ComCallback(int COMport,int eventMask,void *callbackdata);
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "usrtotherdevice.uir", PANEL)) < 0)
		return -1;
	OpenComConfig (1, "", 1200, 1, 7, 1, 512, 512);   //打开并配置串口
	
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

//将接受到的数据储存在指定文件中
int CVICALLBACK timerweight (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	char *time;
	char *date;
	char filename[260];
	char weight[20];
	double weightvalue;
	switch(event)
	{
		case EVENT_TIMER_TICK:
		date="\0";
		time='\0';	//初始化指针
		time = TimeStr ();
		date = DateStr (); //获得系统当前时间和日期
		//以下为出创建一个文件存储路径
		GetProjectDir (filename);
		strcat(filename,"\\");
		strcat(filename,date);
		strcat(filename,"-");
		strcat(filename,"wei.txt");				   
		GetCtrlVal (panelHandle, PANEL_NUMERICGAUGE, &weightvalue);   //获得天平重量值
		Fmt (weight, "%s<%f", weightvalue);
		strcat(date,time);
		strcat(date," ");
		strcat(date,weight);
		//将文本内容加上换行和回车
		strcat(date,"\n");
		strcat(date,"\r");
		//将数组写到文件中
		ArrayToFile (filename, date, VAL_DOUBLE, strlen(date), 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, VAL_CONST_WIDTH, 10, VAL_BINARY, VAL_APPEND);
		
		break;
	}
	return 0;
}

int CVICALLBACK rs232quit (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);
			CloseCom (1);
			
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK rs232receive (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			InstallComCallback (1, LWRS_RECEIVE, 16, 0, ComCallback, callbackdata);  //给串口1安装指定回调函数 当输入队列满50个字符产生中断
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 1);	//定时器使能 开始计时

			break;
	}
	return 0;
}

//串口1端口中断回调函数
void ComCallback(int COMport,int eventMask,void *callbackdata)
{
	int inputqueuelength;
	int bytesread;
	char buffer[512];
	char *matchedchar=0;
	double value;
	int i;
	
	inputqueuelength= GetInQLen (1);  //获得指定端口输入队列字符数
	bytesread = ComRd (1, buffer, inputqueuelength);  //读取输入队列中的字符串
	for(i=0;i<=bytesread;i++)
	{
		//当字符为“+”ox2b 时 执行以下代码
		if(buffer[i]==0x2B)
		{
			matchedchar=buffer+1+i;//将matchedchar指针对准字符+的下一位 即指向接受的数据
			Fmt (&value, "%f<%s", matchedchar);  //将字符串格式数据转换成为双精度格式
			SetCtrlVal (panelHandle, PANEL_NUMERICGAUGE, value);  
			FlushInQ (1);   //清空指定端口的输入队列
		}
	}
	
}
