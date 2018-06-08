#include "toolbox.h"
#include <cvirte.h>		
#include <userint.h>
#include "index.h"

static int panelHandle;
static int iconhandle;//系统托盘句柄
static int itemindex;
int CVICALLBACK iconCB (int iconHandle, int event, int eventData);//系统托盘响应鼠标事件的回调函数

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "index.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	//设置程序运行时的属性，使其不在任务栏显示按钮 
	SetPanelAttribute (panelHandle, ATTR_HAS_TASKBAR_BUTTON, 0);
	SetSystemAttribute (ATTR_TASKBAR_BUTTON_VISIBLE, 0);  //不显示在任务栏
	//装在一个灰色图标 并装载系统托盘回调函数
	InstallSysTrayIcon ("hide.ico", "系统托盘", iconCB, &iconhandle);
	
	RunUserInterface ();
	DiscardPanel (panelHandle);
	//系统退出时，卸载系统托盘 释放占用的资源
	DetachTrayIconMenu (iconhandle);
	RemoveSysTrayIcon (iconhandle);
	return 0;
}

int CVICALLBACK timer (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
		double xarray[7];
	unsigned long availablevirtual,availablepagefile,availablephysical,totalvirtual,totalpagefile,totalphysical,percentload;
	switch (event)
	{
		case EVENT_TIMER_TICK:
			GetMemoryInfo (&percentload, &totalphysical, &totalpagefile, &totalvirtual, &availablephysical, &availablepagefile, &availablevirtual);//得到电脑信息
			xarray[0]=percentload;
			xarray[1]=totalphysical;
			xarray[2]=totalpagefile;
			xarray[3]=totalvirtual;
			xarray[4]=availablephysical;
			xarray[5]=availablepagefile;
			xarray[6]=availablevirtual;
			PlotStripChart (panelHandle, PANEL_STRIPCHART, xarray, 7, 0, 0, VAL_DOUBLE);
			break;
	}
	return 0;
}

int CVICALLBACK OkCallback (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetPanelAttribute (panelHandle, ATTR_HAS_TASKBAR_BUTTON, 0);
			SetSystemAttribute (ATTR_TASKBAR_BUTTON_VISIBLE, 0);
			//卸载系统托盘
			DetachTrayIconMenu (iconhandle);
			RemoveSysTrayIcon (iconhandle);
			//重新装载彩色色图标 并装载系统托盘回调函数
			InstallSysTrayIcon ("show.ico", "系统托盘", iconCB, &iconhandle);
			AttachTrayIconMenu (iconhandle);//使系统响应鼠标右击事件
			//插入系统托盘右键菜单 从1开始 按先后累加
			InsertTrayIconMenuItem (iconhandle, "显示", &itemindex); // 显示菜单项   itemindex=1
			InsertTrayIconMenuItem (iconhandle, NULL, &itemindex);//NULL表示分隔符  itemindex=2
			InsertTrayIconMenuItem (iconhandle, "待显示状态", &itemindex);
			InsertTrayIconMenuItem (iconhandle, 0, &itemindex);//0表示分隔符  itemindex=4
			InsertTrayIconMenuItem (iconhandle, "退出", &itemindex);
			SetTrayIconMenuAttr (iconhandle, ATTR_POPUP_DEFAULT_ITEM, 3);//设置待显示状态属性 其字体加粗
			SetTrayIconMenuItemAttr (iconhandle, 3, ATTR_CHECKED, 1);//设置待显示状态菜单为选中状态
			SetPanelAttribute (panelHandle, ATTR_VISIBLE, 0);//隐藏面板
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
			//系统退出时，卸载系统托盘 释放占用的资源
			DetachTrayIconMenu (iconhandle);
			RemoveSysTrayIcon (iconhandle);
			QuitUserInterface (0);
			break;
	}
	return 0;
}

//系统托盘响应鼠标事件的回调函数
int CVICALLBACK iconCB (int iconHandle, int event, int eventData)
{
	int check;
	switch(event)
	{
		case EVENT_MENU_ITEM:
			if(eventData==1) //显示菜单
			{
				DetachTrayIconMenu (iconhandle);
				RemoveSysTrayIcon (iconhandle);	
				InstallSysTrayIcon ("hide.ico", "系统托盘", iconCB, &iconhandle); 
				SetPanelAttribute (panelHandle, ATTR_HAS_TASKBAR_BUTTON, 0);
				SetSystemAttribute (ATTR_TASKBAR_BUTTON_VISIBLE, 0);
				DisplayPanel (panelHandle); 
			}
			if(eventData==3) //待显示状态
			{
				GetTrayIconMenuItemAttr (iconhandle, 3, ATTR_CHECKED, &check);
				SetTrayIconMenuItemAttr (iconhandle, 3, ATTR_CHECKED, !check);		//
			}
			if(eventData==5)//退出
			{
				QuitUserInterface (0);   	
			}
			break;
	}
	return 0;
}
