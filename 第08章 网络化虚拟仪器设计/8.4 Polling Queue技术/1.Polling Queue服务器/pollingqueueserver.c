#include "dataskt.h"
#include "toolbox.h"
#include <cvirte.h>		
#include <userint.h>
#include "pollingqueueserver.h"

static int panelHandle, ctrlarray;
static DSHandle dsHandle;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "pollingqueueserver.uir", PANEL)) < 0)
		return -1;
	
	DS_ControlLocalServer(DSConst_ServerLaunch);	//启动DataSocket服务器界面
	DS_ControlLocalServer (DSConst_ServerHide);	// 隐藏DataSocket服务器界面 
	
	ctrlarray = GetCtrlArrayFromResourceID (panelHandle, CTRLARRAY);
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	DS_ControlLocalServer (DSConst_ServerClose);
	return 0;
}

int CVICALLBACK connect (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	char url[300];
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 1);
			GetCtrlVal (panelHandle, PANEL_STRING, url);
			//以polling queue方式打开datasocket对象 并连接到数据源
			//此方式不需要eventfunction函数
			DS_OpenEx (url, DSConst_ReadWriteAutoUpdate, 0, 0, DSConst_PollingModel, 5000, &dsHandle);
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
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);
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
	char text[300];
	switch (event)
	{
		case EVENT_COMMIT:
			//如果连接到datasocket服务器 则执行
			if(dsHandle)
			{
				GetCtrlVal (panelHandle, PANEL_TEXTBOX, text);
				DS_SetDataValue (dsHandle, CAVT_CSTRING, text, 0, 0);	 //向datasocket服务器写入数据 
				ResetTextBox (panelHandle, PANEL_TEXTBOX, ""); 
			}
			break;
	}
	return 0;
}

int CVICALLBACK timer (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	double value[1],result;
	switch (event)
	{
		case EVENT_TIMER_TICK:
			result = Random (0, 100);		//产生0-100的随机数
		 	value[0]=result; 
			PlotStripChart (panelHandle, PANEL_STRIPCHART, value, 1, 0, 0, VAL_DOUBLE);
			DS_SetDataValue (dsHandle, CAVT_DOUBLE, value, 0, 0);	//向datasocket服务器写入数据
			
			break;
	}
	return 0;
}
