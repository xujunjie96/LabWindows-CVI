#include "scroll.h"
#include <cvirte.h>		
#include <userint.h>
#include "scrollbar.h"
static int panelHandle;
   void getvalue(void) ;
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Scrollbar.uir", PANEL)) < 0)
		return -1;
	//将绘图控件转换成滚动条
	ScrollBar_ConvertFromGraph (panelHandle, PANEL_GRAPH_VERTICAL, scrollbarCB, &panelHandle);
	
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

//退出回调函数
int CVICALLBACK QuitCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		   QuitUserInterface(0);
			break;
	}
	return 0;
}


//滚动条回调函数
int CVICALLBACK scrollbarCB (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_SB_UP_BUTTON:
			 getvalue();
			break;
		case EVENT_SB_DOWN_BUTTON:
			 getvalue();
			break;
		case EVENT_SB_PAGE_UP:
			 getvalue();
			break;
		case EVENT_SB_PAGE_DOWN:
			 getvalue();
			break;
		case EVENT_SB_THUMB_CHANGE:
			 getvalue();
			break;
		case EVENT_SB_COMMIT:
			 getvalue();
			break;
		
	}
	return 0;
}

//所有numeric回调函数都是这个
int CVICALLBACK adjustvalue (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	int value;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, control, &value);
			switch(control)
			{
				case PANEL_NUMERIC_VERTICAL_MIN:
					ScrollBar_SetAttribute (panelHandle, PANEL_GRAPH_VERTICAL, ATTR_SB_DOC_MIN, value);
					break;
				case PANEL_NUMERIC_VERTICAL_VAL:
					ScrollBar_SetAttribute (panelHandle, PANEL_GRAPH_VERTICAL, ATTR_SB_VALUE, value);
					break;
				case PANEL_NUMERIC_VERTICAL_MAX:
					ScrollBar_SetAttribute (panelHandle, PANEL_GRAPH_VERTICAL, ATTR_SB_DOC_MAX, value);
					break;
				case PANEL_NUMERIC_VERTICAL_HEI:
					ScrollBar_SetAttribute (panelHandle, PANEL_GRAPH_VERTICAL, ATTR_SB_HEIGHT, value);
					break;
				case PANEL_NUMERIC_VERTICAL_WID:
					ScrollBar_SetAttribute (panelHandle, PANEL_GRAPH_VERTICAL, ATTR_SB_WIDTH, value);
					break;
				case PANEL_COLORNUM_COLOR:
					ScrollBar_SetAttribute (panelHandle, PANEL_GRAPH_VERTICAL, ATTR_SB_COLOR, value);
					break;
				case PANEL_TOGGLEBUTTON_MODE:
					ScrollBar_SetAttribute (panelHandle, PANEL_GRAPH_VERTICAL, ATTR_SB_VERTICAL, value);
					break;
				case PANEL_NUMERIC_VERTICAL_VIEW:
					ScrollBar_SetAttribute (panelHandle, PANEL_GRAPH_VERTICAL, ATTR_SB_VIEW_SIZE, value);
					break;
				
			}
			break;
	}
	return 0;
}


void getvalue(void)
{
	int value;
	ScrollBar_GetAttribute (panelHandle, PANEL_GRAPH_VERTICAL, ATTR_SB_VALUE, &value);
	SetCtrlVal (panelHandle, PANEL_NUMERIC_VERTICAL_VAL, value);

}
