#include <utility.h>
#include <ansi_c.h>
#include "toolbox.h"
#include "radioGroup.h"
#include <cvirte.h>		
#include <userint.h>
#include "ridio.h"

static int panelHandle, ctrlarray;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "ridio.uir", PANEL)) < 0)
		return -1;
	Radio_ConvertFromTree (panelHandle, PANEL_RADIOGROUP);	  //将tree控件转化为单选控件
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
	
		case EVENT_CLOSE:
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK help (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	char prjdir[MAX_PATHNAME_LEN];
	char filedir[MAX_PATHNAME_LEN];
	char filename[MAX_PATHNAME_LEN]; 
	int radiovalue;
	switch (event)
	{
		//事件发生条件是当前选项的值发生改变时
		case EVENT_VAL_CHANGED:
			GetCtrlVal (panelHandle, PANEL_RADIOGROUP, &radiovalue);	//获得radiogroup的索引值
			GetProjectDir (prjdir);  
			GetProjectDir (filedir);  
			strcat(prjdir,"\\input.hlp");
			switch(radiovalue)
			{
				case 0:
					//显示帮助内容
					SystemHelp ("prjdir", HELP_CONTENTS, 0, 0);
				break;
				case 1:
					//显示帮助主题
					SystemHelp ("prjdir", HELP_CONTEXT , 7, 0);
				break;
				case 2:
					 //显示帮助索引
					SystemHelp ("prjdir", HELP_PARTIALKEY,0,"");
				break;
				case 3:
					  //文本文件内容的显示方式
					  filename[0]='\0';
					  strcat(filename,"notepad.exe");
					  strcat(filename," ");
					  strcat(filename,filedir); 
					  strcat(filename,"\\input.txt");
					  LaunchExecutable (filename);
				break;
				case 4:
					 //显示html格式的帮助文件
					 filename[0]='\0';
					 strcat(filename,filedir); 
					 strcat(filename,"\\sounds.chm");
					 ShowHtmlHelp (filename, HH_DISPLAY_TOPIC, 0);
				break;
				case 5:
					//用windows默认方式打开浏览器
					filename[0]='\0';
					strcat(filename,filedir) ;
					strcat(filename,"\\input.txt");
					OpenDocumentInDefaultViewer (filename, VAL_NO_ZOOM);
				break;
			}
			break;
	}
	return 0;
}
	 
