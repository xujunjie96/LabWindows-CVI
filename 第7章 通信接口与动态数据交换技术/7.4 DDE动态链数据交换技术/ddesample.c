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
			OpenDocumentInDefaultViewer (prjdie, VAL_NO_ZOOM);
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
					lineitem='\0';
					line[0]='\0';
					value=0.0;
					strcat(lineitem,"R");
					Fmt(line,"%s<%d",i);
					strcat(lineitem,line);
					strcat(lineitem,"C");
					line[0]='\0';
					Fmt(line,"%s<%d",j);
					strcat(lineitem,line);
					ClientDDERead (datalink, lineitem, CF_TEXT, databuf, sizeof(databuf), 0);
				}
			}
			break;
	}																	  .
	
	return 0;
}

int CVICALLBACK wavesignal (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
		case EVENT_VAL_CHANGED:

			break;
	}
	return 0;
}
