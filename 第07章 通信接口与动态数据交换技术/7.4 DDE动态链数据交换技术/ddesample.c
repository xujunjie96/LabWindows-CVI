#include <analysis.h>
#include <ddesupp.h>
#include <utility.h>
#include <ansi_c.h>
#include "toolbox.h"
#include <formatio.h>
#include <cvirte.h>		
#include <userint.h>
#include "ddesample.h"

static int panelHandle;
static int ddelinkstatus=-1;//初始化DDE连接状态 大于等于0为成功连接
static unsigned int datalink;
static int panelHandle;

int clientCB(unsigned handle,char *topicName, char *itemName,int xType,int dataFmt,int dataSize,void *dataPtr,void *callbackData);   //声明DDE回调函数
void ddewave(char databuf[],char testbuf[],double wavw[]);  //自定义函数 向excel写数据

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "ddesample.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK panelCB (int panel, int event, void *callbackData,
						 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_CLOSE:
			//如果建立DDE链接 则执行以下代码
			if(ddelinkstatus>=0)
			{
				 ClientDDEExecute (datalink, "[SAVE()]", 0); //保存excel文件
				 ClientDDEExecute (datalink, "[QUIT()]", 0); //退出excel
				 DisconnectFromDDEServer (datalink);	 //断开DDE连接
			}
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK startexcel (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	char prjdir[MAX_PATHNAME_LEN];
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetDir (prjdir);
			strcat(prjdir,"\\wjx.xls");
			OpenDocumentInDefaultViewer (prjdir, VAL_NO_ZOOM);
			SetInputMode (panelHandle, PANEL_CMD_START, 0);   //按钮变暗 不可点击
			break;
	}
		  
	return 0;
}

int CVICALLBACK linkexcel (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	char prjdir[MAX_PATHNAME_LEN];  
	char testbuf[50];
	double value;
	char databuf[100];
	char lineitem[20];
	char line[10];
	int i,j;
	switch (event)
	{
		case EVENT_COMMIT:
			GetDir (prjdir);
			strcat(prjdir,"\\wjx.xls");
			if((ddelinkstatus=ConnectToDDEServer (&datalink, "excel", prjdir, clientCB, 0))>=0)
				  SetInputMode (panelHandle, PANEL_CMD_LINK, 0);   //按钮变暗 不可点击
			SetUpDDEHotLink (datalink, "R1C1:R10C10", CF_TEXT, 0);//与服务器建立热链接  R1C1:R10C10指excel第一行第一列到10行10列
			//将excel前10行10列写入table表格中
			for(i=1;i<=10;i++)
			{
				for(j=1;j<=10;j++)
				{
					lineitem[0]='\0';
					line[0]='\0';
					value=0.0;
					strcat(lineitem,"R");
					Fmt(line,"%s<%d",i);
					strcat(lineitem,line);
					strcat(lineitem,"C");
					line[0]='\0';
					Fmt(line,"%s<%d",j);
					strcat(lineitem,line);
					ClientDDERead (datalink, lineitem, CF_TEXT, databuf, sizeof(databuf), 0);   //从DDE服务器读取数据
					Fmt(&value,"%f<%s",databuf);
					SetTableCellVal (panelHandle, PANEL_TABLE, MakePoint(j,i), value);	  //将数据写入表格中
					
				}
			}
			break;
	}																	  
	
	return 0;
}

//声明DDE回调函数
int clientCB(unsigned handle,char *topicName, char *itemName,int xType,int dataFmt,int dataSize,void *dataPtr,void *callbackData)   
{
	double value;
	switch (xType)
	{
		case DDE_DISCONNECT:
			DisableBreakOnLibraryErrors();//当产生库函数错误时，禁止弹出运行时错误对话框
			DisconnectFromDDEServer (datalink);
			break;
		case DDE_DATAREADY:
			Fmt(&value,"%f<%s",(char*)dataPtr);//获得DDE连接第一行第一列的数据
			SetCtrlVal (panelHandle, PANEL_CELLVALUE, value);
			break;
	}
	return 0;
}

int CVICALLBACK wavesignal (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	char databuf[10000];
	char testbuf[100];
	double wave[100];
	double sinephase=0;
	double cosphase=90.0;
	double squarephase=90.0;
	int wavemode;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_RINGSLIDE, &wavemode);	
			switch(wavemode)
			{
				case 1:
					SineWave (100, 1.0, 0.01, &sinephase, wave);
					ddewave(databuf,testbuf,wave);
					break;
				case 2:
					SineWave (100, 1.0, 0.01, &cosphase, wave);
					ddewave(databuf,testbuf,wave);
					break;
				case 3:
					Triangle (100, 1.0, wave);
					ddewave(databuf,testbuf,wave);
					break;
				case 4:
					SquareWave (100, 1.0, 0.01, &squarephase, 50.0, wave);
					ddewave(databuf,testbuf,wave);
					break;
				case 5:
					Pulse (100, 1.0, 0, 1, wave);
					
					ddewave(databuf,testbuf,wave);
					break;
			}
			

			break;
	}
	return 0;
}

//自定义函数 向excel写数据     											   
void ddewave(char databuf[],char testbuf[],double wave[])
{
	int i;
	
	databuf[0]='\0';
	testbuf[0]='\0';
	for(i=0;i<100;i++)
	{
		Fmt(testbuf,"%s<%f",wave[i]);
		strcat(databuf,testbuf);
		strcat(databuf,"\n");
	}
	ClientDDEWrite (datalink, "R1C1:R100C1", CF_TEXT, databuf, strlen(databuf), 0); //向dde服务器写数据
	linkexcel(panelHandle,PANEL_CMD_LINK,EVENT_COMMIT,NULL,0,0);  //刷新数据
}
