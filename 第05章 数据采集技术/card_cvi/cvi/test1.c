#include <cvirte.h>		
#include <userint.h>
#include "test1.h"
#include "NIDAQmx.h"
//手工添加NI-DAQmx任务的头文件
#include "DAQTasktest.h"

static int panelHandle;
 //NI-DAQmx任务句柄
static TaskHandle taskHandle = 0;
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "test1.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK stop (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);
			DAQmxClearTask(taskHandle);
			taskHandle = 0; 
			break;
	}
	return 0;
}

int CVICALLBACK sample (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//如果NI-DAQmx任务不存在，则执行以下代码
		//	if (taskHandle <= 0)
	//		{
				//在工程中创建一个NI-DAQmx任务句柄
				CreateDAQTasktest(&taskHandle);
				
				//打开定时器
				SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 1);
		//	}
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
			//清除NI-DAQmx任务句柄
			DAQmxClearTask(taskHandle);
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK timer (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int32 samplesread = 100;
	float64 readarray[1000];
	switch (event)
	{
		case EVENT_TIMER_TICK:
			
			//进行数据采集
			DAQmxReadAnalogF64 (taskHandle, DAQmx_Val_Auto, 10.0, DAQmx_Val_GroupByChannel, readarray, 1000, &samplesread, 0);
			
			//将采集到的数据绘制在Strip Chart控件上
			PlotStripChart (panelHandle, PANEL_STRIPCHART, readarray, 1, 0, 0, VAL_DOUBLE);
			break;
	}
	return 0;
}
