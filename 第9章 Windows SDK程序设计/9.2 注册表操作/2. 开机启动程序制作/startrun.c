#include "windows.h"
#include "toolbox.h"
#include "winreg.h" 
#include <cvirte.h>		
#include <userint.h>
#include "startrun.h"

static int panelHandle;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "startrun.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK run (int panel, int control, int event,
					 void *callbackData, int eventData1, int eventData2)
{
	unsigned int realstringsize;
	unsigned int buffersize=300;
	unsigned char stringbuffer[300];
	
	switch (event)
	{
		case EVENT_COMMIT:
			RegReadString (REGKEY_HKLM, "Software\\National INstruments\\CVI\\8.0\\User Info", "Directory", stringbuffer, buffersize, &realstringsize);//读取cvi的存储路径
			strcat(stringbuffer,"\\");
			strcat(stringbuffer,"cvi.exe"); 
			RegWriteString (REGKEY_HKLM, "SOFTWARE\Microsoft\Windows\CurrentVersion\Run", "CVI", stringbuffer);//开机启动cvi
			break;
	}
	return 0;
}

int CVICALLBACK unrun (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	HKEY hkey;
	switch (event)
	{
		case EVENT_COMMIT:
			//注销开机启动cvi
			RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\Microsoft\Windows\CurrentVersion\Run",0,KEY_ALL_ACCESS,&hkey);
			RegDeleteValue(hkey,"CVI");
			RegCloseKey(hkey);
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
