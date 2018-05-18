#include <cvirte.h>		
#include <userint.h>
#include "Splitter.h"

static int panelHandle;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Splitter.uir", PANEL)) < 0)
		return -1;
	//设置Spliter的颜色属性为透明色
	SetCtrlAttribute (panelHandle, PANEL_SPLITTER_VER_LEFT, ATTR_FRAME_COLOR, VAL_TRANSPARENT);
	SetCtrlAttribute (panelHandle, PANEL_SPLITTER_HOR_TOP, ATTR_FRAME_COLOR, VAL_TRANSPARENT);
	SetCtrlAttribute (panelHandle, PANEL_SPLITTER_VER_RIGHT, ATTR_FRAME_COLOR, VAL_TRANSPARENT);
	SetCtrlAttribute (panelHandle, PANEL_SPLITTER_HOR_BOTTOM, ATTR_FRAME_COLOR, VAL_TRANSPARENT);
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
			QuitUserInterface (0);
			break;
	}
	return 0;
}
