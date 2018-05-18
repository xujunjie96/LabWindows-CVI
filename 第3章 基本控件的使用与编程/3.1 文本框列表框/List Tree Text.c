#include <formatio.h>
#include <cvirte.h>		
#include <userint.h>  
#include "List Tree Text.h"

static int panelHandle;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "List Tree Text.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

//清除已选目录按钮回调函数
int CVICALLBACK clear (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		 	ClearListCtrl(panelHandle,PANEL_TREE);	//清除文本内容
			InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"清除已选目录");	//向文本框末尾添加一行文本 	
			break;
	}
	return 0;
}

//转移按钮回调函数
int CVICALLBACK transfer (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	int maxitems;
	int i;
	char label[10];
	char Tag[32];
	int value;
	int checked;
	static int j=0,k;
	
	switch (event)
	{
		case EVENT_COMMIT:
			ClearListCtrl(panelHandle,PANEL_TREE);	//清除定制列表框 ？？
			InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"转移并显示目录");	//向文本框末尾添加一行文本
			j=0;
			GetNumListItems(panelHandle,PANEL_LISTBOX,&maxitems);	//获得列表框项目的数目
			for(i=0;i<maxitems;i++)
			{
				IsListItemChecked(panelHandle,PANEL_LISTBOX,i,&checked);	//获得列表框中指定项目的选中状态
				if(checked)
				{
					j++;
					GetValueFromIndex(panelHandle,PANEL_LISTBOX,i,&value);	//获得指定索引项目value值
					GetLabelFromIndex(panelHandle,PANEL_LISTBOX,i,label);	//获得指定索引项目的标题
					InsertTreeItem(panelHandle,PANEL_TREE,VAL_SIBLING,j-2,VAL_NEXT,label,"",Tag,value);//将选中的项目插入到指定的树控件
				}
			}
			break;
	}
	return 0;
}

//插入按钮回调函数
int CVICALLBACK insert (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	char newitem[10];
	
	switch (event)
	{
		case EVENT_COMMIT:
			InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"添加目录");	//向文本框末尾添加一行文本 
			GetCtrlVal(panel,PANEL_STRING_INSERT,newitem);		//得到指定String控件的值
			InsertListItem(panelHandle,PANEL_LISTBOX,-1,newitem,0);	//向列表框插入新的项目
			break;
	}
	return 0;
}

//移除按钮回调函数
int CVICALLBACK delete (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	int maxitems;
	char removeitem[10];
	int i;
	char label[10];
	
	switch (event)
	{
		case EVENT_COMMIT:
			InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"移除目录");	//向文本框末尾添加一行文本 	 
			GetCtrlVal(panel,PANEL_STRING_DELETE,removeitem);
			GetNumListItems(panelHandle,PANEL_LISTBOX,&maxitems);
			for(i=0;i<maxitems;i++)   
			{
				GetLabelFromIndex(panelHandle,PANEL_LISTBOX,i,label);	//获得指定索引项目的标题
				if(CompareStrings(label,0,removeitem,0,1)==0)   //判断该标题和指定内容是否相一致
				{
					DeleteListItem(panelHandle,PANEL_LISTBOX,i--,1);	//删除列表框指定项目
					maxitems--;
				}
			}
			  
			break;
	}
	return 0;
}

int CVICALLBACK quit (int panel, int control, int event,
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
