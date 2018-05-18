#include <ansi_c.h>
#include "toolbox.h"
#include <utility.h>
#include <formatio.h>
#include "FileBrowser.h"
#include "pathctrl.h"
#include <cvirte.h>		
#include <userint.h>
#include "filebrowsetest.h"
#include "userint.h"
static int panelHandle;
static int j=0;
static int flag=0;

//自定义函数 获得驱动器的盘符及数目
void drivevolume();

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "filebrowsetest.uir", PANEL)) < 0)
		return -1;
	FileBrowser_Create (panelHandle, PANEL_FILEBROWSER, ROOT_LEVEL_STRING);   //创建一个新的FileBrowser控件
    NewPathCtrl (panelHandle, PANEL_PATH, 8, 1);   //创建一个新的PathCtrl控件 
	DisplayPanel (panelHandle);
	drivevolume(); //显示驱动器盘符
	//设置文件系统绝对路径
	FileBrowser_SetAttribute (panelHandle, PANEL_FILEBROWSER, ATTR_PATH_RELATIVE, 0);
	
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK panelcb (int panel, int event, void *callbackData,
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

int CVICALLBACK drivevol (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	int value;
	char drive2[10];
	switch (event)
	{
		//Ring的响应事件为 EVENT_COMMIT   EVENT_VAL_CHANGED
		case EVENT_COMMIT || EVENT_VAL_CHANGED:
			drivevolume(); //显示驱动器盘符 
			GetCtrlAttribute (panelHandle, PANEL_RING, ATTR_CTRL_VAL, &value);
			Fmt(drive2,"%2c<%i",value);		//数据格式化函数
			drive2[1]='\0';
			strcat(drive2,":\\");
			SetCtrlVal (panelHandle, PANEL_PATH, drive2);
			SetActiveCtrl (panelHandle, PANEL_PATH);
			SetCtrlAttribute (panelHandle, PANEL_PATH, ATTR_TEXT_SELECTION_START, 10);
			FileBrowser_SetAttribute (panelHandle, PANEL_FILEBROWSER, ATTR_START_PATH, drive2);
			break;
	}
	return 0;
}

int CVICALLBACK path (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	char drive2[MAX_PATHNAME_LEN];
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_PATH, &drive2);//当输入盘符和冒号后 在输入 \ 则会显示i本目录下所有的文件以及目录
			FileBrowser_SetAttribute (panelHandle, PANEL_FILEBROWSER, ATTR_START_PATH, drive2);	//设置file browser开始路径 
			break;
	}
	return 0;
}

int CVICALLBACK fileopen (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	char **files;
	switch (event)
	{
		case EVENT_COMMIT:
			FileBrowser_GetSelectedFiles (panelHandle, PANEL_FILEBROWSER, &files); //获得filebrowers中被选中的文件
			OpenDocumentInDefaultViewer(*files,VAL_NO_ZOOM); //以windows默认方式打开选择的文件
			free(files);//释放文件指针
			break;
	}
	return 0;
}


void drivevolume()
{
	 int  numberofdrives;
	 int currentdrivenumber;
	 int i;
	 int drive1=0;
	 char drive2[10];
	 unsigned int messagenumber=0;
	 
	 if(flag==0)
	 {
	 	GetDrive (&currentdrivenumber,&numberofdrives);	 //获得系统驱动器个数
		j=numberofdrives;
		//计数 从硬盘盘符C开始 一直到驱动器盘符数减二为止
		for(i=0;i<numberofdrives-2;i++)
		{
			drive1='c'+i;
			Fmt(drive2,"%2c<%i",drive1);
			drive2[1]='\0';
			strcat(drive2,":");
			InsertListItem (panelHandle, PANEL_RING, -1, drive2, drive1);
			drive2[0]='\0';
		}
		flag=1;
		
	 }
	 GetDrive (&currentdrivenumber,&numberofdrives);	 //获得系统驱动器个数  
	 
	 if (j!=numberofdrives)
	 {
	 	  DeleteListItem (panelHandle, PANEL_RING, 0, -1);
		  	//计数 从硬盘盘符C开始 一直到驱动器盘符数减二为止
		for(i=0;i<numberofdrives-2;i++)
		{
			drive1='c'+i;
			Fmt(drive2,"%2c<%i",drive1);
			drive2[1]='\0';
			strcat(drive2,":");
			InsertListItem (panelHandle, PANEL_RING, -1, drive2, drive1);
			drive2[0]='\0';
		}
		flag=1;
	 }
}
