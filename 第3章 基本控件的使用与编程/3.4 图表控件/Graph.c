#include <analysis.h>
#include "toolbox.h"
#include <cvirte.h>		
#include <userint.h>
#include "Graph.h"

static int panelHandle;
int CVICALLBACK EventFunction (int panelOrMenuBarHandle, int controlOrMenuItemID, int event, void *callbackData, int eventData1, int eventData2);
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Graph.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK graph (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	double sin[10];
	switch (event)
	{	 // double sin[1];
		case EVENT_COMMIT:
			SinePattern(10,1.0,0.0,1.0,sin);		//产生一个正弦波函数数组
			PlotY (panelHandle, PANEL_GRAPH, sin, 10, VAL_DOUBLE, VAL_CONNECTED_POINTS, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_RED);//绘制GRAPH图
		
			SetCtrlAttribute (panelHandle, PANEL_GRAPH, ATTR_ENABLE_ZOOM_AND_PAN, 1);
			break;
	}
	return 0;
}

int CVICALLBACK stripchart (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		   //为面板、控件和菜单安装主回调函数
			InstallMainCallback (EventFunction, 0, 1);
			
			//设置主回调函数的响应时间
			SetIdleEventRate (100);
			break;
	}
	return 0;
}

int CVICALLBACK digitalgraph (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{	
	int array[12]={0,5,8,6,0,4,1,8,3,6,4,0};
	switch (event)
	{
		case EVENT_COMMIT:
			ClearDigitalGraph (panelHandle, PANEL_DIGGRAPH); //清除DG
			PlotDigitalLines (panelHandle, PANEL_DIGGRAPH, array, 12, VAL_INTEGER, 3);  //绘图
			

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
			InstallMainCallback(NULL,0,0);	//关闭主回调函数
			QuitUserInterface(0);
			break;
	}
	return 0;
}
int CVICALLBACK EventFunction (int panelOrMenuBarHandle, int controlOrMenuItemID, int event, void *callbackData, int eventData1, int eventData2)
{
	double value;
	
	//产生一个0到100之间的随机数
	value = Random (0, 100);
	
	//绘图
	PlotStripChartPoint (panelHandle, PANEL_STRIPCHART, value);
	return 0;
}
