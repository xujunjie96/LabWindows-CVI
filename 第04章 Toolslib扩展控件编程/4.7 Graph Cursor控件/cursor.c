#include <analysis.h>
#include "graphcursors.h"
#include <cvirte.h>		
#include <userint.h>
#include "cursor.h"

//Graph Cursor句柄
static int graphhandle;

static int panelHandle;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "cursor.uir", PANEL)) < 0)
		return -1;
	//向Graph控件添加Graoph Cursor控件
	graphhandle=GCC_New (panelHandle, PANEL_GRAPHCURSOR, 10, GCC_VAL_POS_BELOW_LEFT, 2);
	SetCtrlAttribute (panelHandle, PANEL_GRAPHCURSOR, ATTR_ENABLE_ZOOM_AND_PAN, 1);
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK index (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	int value;
	switch (event)
	{
		case EVENT_COMMIT:
			//将游标控制框内所有控件1取相同的回掉函数名 可以响应同一事件
			//区分是哪个响应事件是通过常量名传递
			switch(control)
			{
				case PANEL_CHECKBOX_INDEX :
				GetCtrlVal (panelHandle, PANEL_CHECKBOX_INDEX, &value);
				GCC_SetAttribute (graphhandle, GCC_ATTR_INDEX_VISIBLE, value);
				break;
				case PANEL_CHECKBOX_ZOOM :
				GetCtrlVal (panelHandle, PANEL_CHECKBOX_ZOOM, &value);
				GCC_SetAttribute (graphhandle, GCC_ATTR_ZOOM_VISIBLE, value);		
				break;
				case PANEL_CHECKBOX_CLOLR :
				GetCtrlVal (panelHandle, PANEL_CHECKBOX_CLOLR, &value);
				GCC_SetAttribute (graphhandle, GCC_ATTR_COLOR_VISIBLE, value);
				break;
				case PANEL_CHECKBOX_NAME :
				GetCtrlVal (panelHandle, PANEL_CHECKBOX_NAME, &value);
				GCC_SetAttribute (graphhandle, GCC_ATTR_NAME_VISIBLE, value);
				break;
				case PANEL_CHECKBOX_COORDINMTE :
				GetCtrlVal (panelHandle, PANEL_CHECKBOX_COORDINMTE, &value);
				GCC_SetAttribute (graphhandle, GCC_ATTR_COORDINATES_VISIBLE, value);
				break;
				case PANEL_CHECKBOX_SELECTION :
				GetCtrlVal (panelHandle, PANEL_CHECKBOX_SELECTION, &value);
				GCC_SetAttribute (graphhandle, GCC_ATTR_SELECT_VISIBLE, value);
				break;
				case PANEL_CHECKBOX_OPTION :
				GetCtrlVal (panelHandle, PANEL_CHECKBOX_OPTION, &value);
				GCC_SetAttribute (graphhandle, GCC_ATTR_SETTINGS_VISIBLE, value);
				break;
				case PANEL_CHECKBOX_COMPASS :
				GetCtrlVal (panelHandle, PANEL_CHECKBOX_COMPASS, &value);
				GCC_SetAttribute (graphhandle, GCC_ATTR_COMPASS_VISIBLE, value);
				break;
				
			}
			break;
	}
	return 0;
}

int CVICALLBACK pos (int panel, int control, int event,
					 void *callbackData, int eventData1, int eventData2)
{
	int value; 
	switch (event)
	{
		case EVENT_COMMIT:
			switch(control)
			{
				case PANEL_NUMERIC_POS :
				GetCtrlVal (panelHandle, PANEL_NUMERIC_POS, &value);
				GCC_SetAttribute (graphhandle, GCC_ATTR_GAP_TO_ANCHOR, value);
				break;
				case PANEL_RING_ALIGN:
				GetCtrlVal (panelHandle, PANEL_RING_ALIGN, &value);
				GCC_SetAttribute (graphhandle, GCC_ATTR_REL_POS, value-1);
				break;
				case PANEL_NUMERIC_NUMBER :
				GetCtrlVal (panelHandle, PANEL_NUMERIC_NUMBER, &value);	
				GCC_SetAttribute (graphhandle, GCC_ATTR_NUM_ROWS, value);
				break;
			}

			break;
	}
	return 0;
}

int CVICALLBACK quitsys (int panel, int control, int event,
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
			DeleteGraphPlot (panelHandle, PANEL_GRAPHCURSOR, -1, VAL_IMMEDIATE_DRAW); 
			break;
	}
	return 0;
}

int CVICALLBACK drawnoise (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	double whitenoise[512];
	double sinx[512];
	switch (event)
	{
		case EVENT_COMMIT:
			DeleteGraphPlot (panelHandle, PANEL_GRAPHCURSOR, -1, VAL_IMMEDIATE_DRAW);
			WhiteNoise (512, 1.0, 2, whitenoise);//产生白噪声信号 
			GammaNoise (512, 1, 2, ANALYSIS_TRUE,sinx );		   
			PlotY (panelHandle, PANEL_GRAPHCURSOR, whitenoise, 512, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_BLUE);//绘图
			PlotY (panelHandle, PANEL_GRAPHCURSOR, sinx, 512, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_RED);//绘图
			break;
	}
	return 0;
}
