#include <utility.h>
#include <cvirte.h>		
#include <userint.h>
#include "dll.h"
 //编译时勾选上build/target setting/embed porject uirs ,将会将uir文件嵌入dll文件内，调用时uir文件可以不在文件夹内，但是dll文件大小会变大
int InitUIForDLL (void);
void DiscardUIObjectsForDLL (void);

static int panelHandle;
static int exehandle;
static char pathname[MAX_PATHNAME_LEN];


int __stdcall DllMain (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:
			if (InitCVIRTE (hinstDLL, 0, 0) == 0)
				return 0;	/* out of memory */
			break;
		case DLL_PROCESS_DETACH:
			//如果cvirte.dll (cvi运行库)已经被释放 则不能调用cvi函数
			if (!CVIRTEHasBeenDetached())		/* Do not call CVI functions if cvirte.dll has already been detached. */
			{
				DiscardUIObjectsForDLL();//释放用户界面资源
				CloseCVIRTE ();
			}
			break;
	}

	return 1;
}

//int __stdcall DllEntryPoint (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
//{
//	/* Included for compatibility with Borland */
//	//borland c++ builder的dll定义的入口点
//	return DllMain (hinstDLL, fdwReason, lpvReserved);
//}


int InitUIForDLL (void)
{
	/* Call this function from the appropriate place in your code */
	/* to load and display startup panels.                        */
	//含有界面的dll调用入口点
	if ((panelHandle = LoadPanelEx (0, "dll.uir", PANEL, __CVIUserHInst)) < 0)
		return -1;
	DisplayPanel (panelHandle);  //加载用户界面
	 RunUserInterface ();	 //不加入这个函数 界面将会一闪而过
	/* Uncomment this call to RunUserInterface or call it from elsewhere */
	/* in your code to begin issuing user interface events to panels     */
	/* RunUserInterface (); */
	return 0;
}

void DiscardUIObjectsForDLL (void)
{
	/* Discard the panels loaded in InitUIForDLL */
	/* Call this function from the appropriate place in your code */
	/* to discard UI objects.                                     */
	 //释放inituifordll函数入口点处装载的界面函数
	if (panelHandle > 0)
	{
		DiscardPanel (panelHandle);
		panelHandle = 0;
	}
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

int CVICALLBACK terminate (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			TerminateExecutable (exehandle);   //终止exe文件的运行 释放exe程序句柄
			break;
	}
	return 0;
}

int CVICALLBACK lanch (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		    GetCtrlVal (panelHandle, PANEL_STRING, pathname);
			LaunchExecutableEx (pathname, LE_SHOWNORMAL, &exehandle);//得到exe程序句柄
			
			break;
	}
	return 0;
}

int CVICALLBACK openfile (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(FileSelectPopup ("", "*.exe", "*.exe", "打开", VAL_OK_BUTTON, 0, 0, 1, 1, pathname))
		   {
		   	SetCtrlVal (panelHandle, PANEL_STRING, pathname);
		   }
			break;
	}
	return 0;
}
