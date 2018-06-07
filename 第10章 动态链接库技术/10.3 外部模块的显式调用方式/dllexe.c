#include <utility.h>
#include <cvirte.h>		
#include <userint.h>
#include "dllexe.h"
#include "dllsample.h"
static int panelHandle;
//要勾选上build/target setting/LoadExternalModule
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "dllexe.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK QuitCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
		case EVENT_KEYPRESS:

			break;
	}
	return 0;
}

int CVICALLBACK popup (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{   int (*address)(void);
	int mode,moduleid;
	int status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_BINARYSWITCH, &mode);//mode为0调用lib 为1调用obj
			if(mode)
			{
				moduleid=LoadExternalModule ("dllsample.obj");	 //装载一个外部模块
			}
			else
			{
				moduleid=LoadExternalModule ("dllsample.lib");
			}
			address=GetExternalModuleAddr (moduleid, "function1", &status);//得到function1首地址指针
			(*address)();//调用function1函数   不传入任何参数
			UnloadExternalModule (moduleid);//释放模块 
			break;
	}
	return 0;
}

int CVICALLBACK calc (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	int (*address)(int x,int y);
	int mode;
	int x,y,z;
	int status;
	int moduleid;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_NUMERIC_X, &x);
			GetCtrlVal (panelHandle, PANEL_NUMERIC_Y, &y);
			GetCtrlVal (panelHandle, PANEL_BINARYSWITCH, &mode);//mode为0调用lib 为1调用obj
			if(mode)
			{
				moduleid=LoadExternalModule ("dllsample.obj");	 //装载一个外部模块
			}
			else
			{
				moduleid=LoadExternalModule ("dllsample.lib");
			}
			address=GetExternalModuleAddr (moduleid, "function2", &status);//得到function2首地址指针
			z=(*address)(x,y);//调用function2函数
			SetCtrlVal (panelHandle, PANEL_NUMERIC_Z, z);
			UnloadExternalModule (moduleid);//释放模块
			break;
	}
	return 0;
}
