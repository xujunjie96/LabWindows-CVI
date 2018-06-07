#include "dataskt.h"
#include "toolbox.h"
#include "combobox.h"
#include <cvirte.h>		
#include <userint.h>
#include "datasocketdesidn.h"

static int CSmode;
static int panelHandle, ctrlarray;
static DSHandle dshandleread=0;//从DataSocket服务器读取数据的句柄
static DSHandle dshandlewrite=0;//向DataSocket服务器写数据的句柄

void geturl(int ReadOrWriteURL,char *url);   //自定义函数 获得DataSocket的地址
void insertcombo(void);//向combobox中插入项目
void CVICALLBACK dsfunctionread(DSHandle dsHandle,int event,void *callbackData);//从DataSocket服务器读取数据
void CVICALLBACK dsfunctionwrite(DSHandle dsHandle,int event,void *callbackData);//向DataSocket服务器写数据

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "datasocketdesidn.uir", PANEL)) < 0)
		return -1;
	
	Combo_NewComboBox (panelHandle, PANEL_COMBO);  //装载一个combo控件
	insertcombo();
	SetCtrlAttribute (panelHandle, PANEL_CMD_SEND, ATTR_DIMMED, 1);  //send按钮变灰
	DS_ControlLocalServer(DSConst_ServerLaunch);	//启动DataSocket服务器界面
	DS_ControlLocalServer (DSConst_ServerHide);	// 隐藏DataSocket服务器界面 
	ctrlarray = GetCtrlArrayFromResourceID (panelHandle, CTRLARRAY);
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);		// 关闭DataSocket服务器
	DS_ControlLocalServer (DSConst_ServerClose);
	return 0;
}

int CVICALLBACK disconnect (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panelHandle, PANEL_CMD_SEND, ATTR_DIMMED, 1);  //send按钮变灰 
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);   //关定时器
			if(dshandleread)
			{
				//释放datasocket服务器对象资源
				DS_DiscardObjHandle (dshandleread);
				dshandleread=0;
			}
			if(dshandlewrite)
			{
				//释放datasocket服务器对象资源
				DS_DiscardObjHandle (dshandlewrite);
				dshandlewrite=0;
			}
			break;
	}
	return 0;
}

int CVICALLBACK connect (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{   
	char url[300];
	
	switch (event)
	{
		case EVENT_COMMIT:
			//如果在打开前datasocket连接句柄存在  则先关闭
			if(dshandleread)
			{
				//释放datasocket服务器对象资源
				DS_DiscardObjHandle (dshandleread);
				dshandleread=0;
			}
			if(dshandlewrite)
			{
				//释放datasocket服务器对象资源
				DS_DiscardObjHandle (dshandlewrite);
				dshandlewrite=0;
			}
			
			SetCtrlAttribute (panelHandle, PANEL_CMD_SEND, ATTR_DIMMED, 0);
			GetCtrlVal (panelHandle, PANEL_BINARYSWITCH, &CSmode);	//获得服务器或者客户机模式
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, CSmode);
			geturl(CSmode,url);
			DS_OpenEx (url, DSConst_ReadAutoUpdate, dsfunctionread, NULL, DSConst_EventModel, DSConst_Asynchronous, &dshandleread);//打开datasocket读取操作服务器
			geturl(!CSmode,url);
			DS_OpenEx (url, DSConst_WriteAutoUpdate, dsfunctionwrite, NULL, DSConst_EventModel, DSConst_Asynchronous, &dshandlewrite);//打开datasocket写操作服务器
			
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
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0); 
			if(dshandleread)
			{
				//释放datasocket服务器对象资源
				DS_DiscardObjHandle (dshandleread);
				dshandleread=0;
			}
			if(dshandlewrite)
			{
				//释放datasocket服务器对象资源
				DS_DiscardObjHandle (dshandlewrite);
				dshandlewrite=0;
			}
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK clear (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			ResetTextBox (panelHandle, PANEL_TEXTBOX, "");
			break;
	}
	return 0;
}

int CVICALLBACK send (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	char text[300];
	char url[300];
	
	switch (event)
	{
		case EVENT_COMMIT:
			geturl(CSmode,url);
			GetCtrlVal (panelHandle, PANEL_TEXTBOX, text);
			DS_SetDataValue (dshandlewrite, CAVT_CSTRING, text, 0, 0);	//向datasocket服务器写入数据 
			ResetTextBox (panelHandle, PANEL_TEXTBOX, ""); 
			break;
	}
	return 0;
}

int CVICALLBACK timer (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	double value[1];
	switch (event)
	{
		case EVENT_TIMER_TICK:
			value[0] = Random (0, 100);		//产生0-100的随机数
			PlotStripChart (panelHandle, PANEL_STRIPCHART, value, 1, 0, 0, VAL_DOUBLE);
			DS_SetDataValue (dshandlewrite, CAVT_DOUBLE, value, 1, 0);	//向datasocket服务器写入数据
			break;
	}
	return 0;
}

//从DataSocket服务器读取数据
void CVICALLBACK dsfunctionread(DSHandle dsHandle,int event,void *callbackData)
{
	char text[300]; 
	unsigned int type;
	char buffer[1000];
	double value;
	switch(event)
	{
		//从datasocket服务器读取数据事件	
		case DS_EVENT_DATAUPDATED:
			DS_GetDataType (dshandleread, &type, NULL, NULL);
			switch(type)
			{
				case CAVT_DOUBLE://当为double型数据时 写入stripchart控件
					DS_GetDataValue (dshandleread, type, &value, 0, NULL, NULL);
					PlotStripChart (panelHandle, PANEL_STRIPCHART, &value, 1, 0, 0, VAL_DOUBLE); 
					break;
				case CAVT_CSTRING: //当为字符串型数据 写入Textbox控件
					DS_GetDataValue (dshandleread, type, text, 300, NULL, NULL);
					SetCtrlVal (panelHandle, PANEL_TEXTBOX, text);
					break;
			}
			break;
		//从datasocket服务器读取状态信息
		case DS_EVENT_STATUSUPDATED:
			DS_GetLastMessage (dshandleread, buffer, 1000);
			SetCtrlVal (panelHandle, PANEL_STRING, buffer);	
			break;
	}
}

//向DataSocket服务器写数据
void CVICALLBACK dsfunctionwrite(DSHandle dsHandle,int event,void *callbackData)
{
	char text[300]; 
	unsigned int type;
	char buffer[1000];
	double value;
	switch(event)
	{
		//从datasocket服务器读取状态信息
		case DS_EVENT_STATUSUPDATED:
			DS_GetLastMessage (dshandleread, buffer, 1000);
			SetCtrlVal (panelHandle, PANEL_STRING, buffer);	
			break;
	}	
}


//向combobox中插入项目 
void insertcombo(void)
{
	Combo_InsertComboItem (panelHandle, PANEL_COMBO, -1, "dstp://localhost/data");
	Combo_InsertComboItem (panelHandle, PANEL_COMBO, -1, "dstp://192.168.74.1/data");
}

//自定义函数 获得DataSocket的地址 
//ReadOrWriteURL为1是读取操作 为0是写操作
void geturl(int ReadOrWriteURL,char *url)
{
	url[0]='\0';
	GetCtrlVal (panelHandle, PANEL_COMBO, url);
	if(ReadOrWriteURL)
	{
		strcat(url,"/");
		strcat(url,"read");
	}
	else
	{
		strcat(url,"/");
		strcat(url,"write");	
	}
}
