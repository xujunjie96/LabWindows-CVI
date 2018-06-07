#include <cvirte.h>		
#include <userint.h>
#include "dllexe.h"
#include "dllsample.h" 
static int panelHandle;
 //编译dll时要选择release模式才能生成静态到入库lib文件  1 configuration也是release模式  2 targetsetting也是release模式，change勾选上.h文件
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

int CVICALLBACK locktimer (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	int CapsLock=0;
	int Numlock=0;
	int ScrollLock=0;
	int AsciiA=0;
	
	switch (event)
	{
		case EVENT_TIMER_TICK:
			GetVirtualKey(&CapsLock,&Numlock,&ScrollLock,&AsciiA);  //调用自定义函数 判断键是否被按下    
			 SetCtrlVal(panelHandle, PANEL_LED_CAP, CapsLock); 
			 SetCtrlVal(panelHandle, PANEL_LED_NUM, Numlock);
			 SetCtrlVal(panelHandle, PANEL_LED_SCROLL, ScrollLock);
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
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK keypresstimer (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			//0.5s后led_a熄灭
			SetCtrlVal (panelHandle, PANEL_LED_A, 0);
			// 按键显示 定时器停止计时
			SetCtrlAttribute (panelHandle, PANEL_TIMER_2, ATTR_ENABLED, 0);
			break;
	}
	return 0;
}

int CVICALLBACK panelCB (int panel, int event, void *callbackData,
						 int eventData1, int eventData2)
{
	int CapsLock=0;
	int Numlock=0;
	int ScrollLock=0;
	int AsciiA=0;
	switch (event)
	{
		case EVENT_KEYPRESS:
			GetVirtualKey(&CapsLock,&Numlock,&ScrollLock,&AsciiA);  //调用自定义函数 判断键是否被按下
			//按下 则led发光 定时器开始计时
			 SetCtrlVal(panelHandle, PANEL_LED_A, AsciiA);
			SetCtrlAttribute (panelHandle, PANEL_TIMER_2, ATTR_ENABLED, 1);
			break;
	}
	return 0;
}
