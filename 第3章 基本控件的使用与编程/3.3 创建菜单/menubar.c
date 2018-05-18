#include <cvirte.h>		
#include <userint.h>
#include "menubar.h"

static int panelHandle;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "menubar.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK panelcb (int panel, int event, void *callbackData,
						 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			break;
	}
	return 0;
}

void CVICALLBACK editcopy (int menuBar, int menuItem, void *callbackData,
						   int panel)
{
}

void CVICALLBACK editalwaystop (int menuBar, int menuItem, void *callbackData,
								int panel)
{
}

void CVICALLBACK editexit (int menuBar, int menuItem, void *callbackData,
						   int panel)
{
	QuitUserInterface (0);
}

void CVICALLBACK helpabout (int menuBar, int menuItem, void *callbackData,
							int panel)
{
}
