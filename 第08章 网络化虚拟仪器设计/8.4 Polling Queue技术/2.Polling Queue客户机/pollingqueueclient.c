#include "dataskt.h"
#include <cvirte.h>		
#include <userint.h>
#include "pollingqueueclient.h"

static int panelHandle, ctrlarray;
static DSHandle dsHandle;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "pollingqueueclient.uir", PANEL)) < 0)
		return -1;
	ctrlarray = GetCtrlArrayFromResourceID (panelHandle, CTRLARRAY);
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
			QuitUserInterface (0);
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
			GetCtrlVal (panelHandle, PANEL_STRING, url);
			//以读方式打开datasocket对象 接收pollingqueue数据
			DS_OpenEx (url, DSConst_ReadAutoUpdate, NULL, NULL, DSConst_PollingModel, 5000, &dsHandle);
			break;
	}
	return 0;
}

int CVICALLBACK receive (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(dsHandle)
			{
				SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 1);
			}
			break;
	}
	return 0;
}

//通过定时器控件接收数据
int CVICALLBACK timer (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	double value[1];
	BOOL dataupdate;
	double packetfraction;
	double bytefraction;
	unsigned int type;
	char text[300];
	int packetsize;
	int bytesize;
	
	switch (event)
	{
		case EVENT_TIMER_TICK:
			DS_GetDataUpdated (dsHandle, &dataupdate);//获得polling queue数据更新信息
			if(dataupdate)//如果数据更新 则执行以下操作
			{
				DS_GetPollingQueueSizeInBytes (dsHandle, &bytesize);//获得polling queue字节数
				DS_GetPollingQueueSizeInPackets (dsHandle, &packetsize); //获得polling queue数据包数
				SetCtrlVal (panelHandle, PANEL_NUMERIC_BYTES, bytesize);
				SetCtrlVal (panelHandle, PANEL_NUMERIC_PACKETS, packetsize);
				DS_GetPollingQueueBytesUtilization (dsHandle, &bytefraction);//获得polling queue字节数占总字节数比例
				DS_GetPollingQueuePacketsUtilization (dsHandle, &packetfraction); //获得polling queue数据包数占总数据包数比例
				SetCtrlVal (panelHandle, PANEL_NUMERICSLIDE_BYTES, bytefraction);
				SetCtrlVal (panelHandle, PANEL_NUMERICSLIDE_PACKETS, packetfraction);
				
				DS_GetDataType (dsHandle, &type, NULL, NULL);//获得接收数据的数据类型
				switch(type)
				{
					case CAVT_DOUBLE://当为double型数据时 写入stripchart控件
						DS_GetDataValue (dsHandle, CAVT_DOUBLE, &value, 0, NULL, NULL);
						PlotStripChart (panelHandle, PANEL_STRIPCHART, value, 1, 0, 0, VAL_DOUBLE); 
						break;
					case CAVT_CSTRING: //当为字符串型数据 写入Textbox控件
						DS_GetDataValue (dsHandle, CAVT_CSTRING, text, 300, NULL, NULL);
						SetCtrlVal (panelHandle, PANEL_TEXTBOX, text);
						break;
				}
			}
			
			break;
	}
	return 0;
}
