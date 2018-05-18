#include <cvirte.h>		
#include <userint.h>
#include "温度.h"

static int panelHandle;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "温度.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK Acquire (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
								    
			break;
	}
	return 0;
}

int CVICALLBACK Quit (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	static double max,min;
	static int max_index,min_index;
	int i,j,value;
	double datapoints[100];
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panelHandle,PANEL_BINARYSWITCH,&value);		  //获取开关状态
			if(value==1)
			{
				SetCtrlVal(panelHandle,PANEL_LED,1);	//点亮LED
				SetCtrlAttribute(panelHandle,PANEL_LED,ATTR_LABEL_TEXT);
			}

			break;
	}
	return 0;
}
