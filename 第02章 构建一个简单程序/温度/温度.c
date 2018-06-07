#include <ansi_c.h>
#include <utility.h>
#include <analysis.h>
#include <cvirte.h>		
#include <userint.h>
#include "温度.h"

static int panelHandle;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "温度.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK Acquire (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	static double max,min;
	static int max_index,min_index;
	int i,j,value;
	double datapoints[100];
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panelHandle,PANEL_BINARYSWITCH,&value);		  //获取开关状态
			if(value==1)
			{
				SetCtrlVal(panelHandle,PANEL_LED,1);	//点亮LED
				SetCtrlAttribute(panelHandle,PANEL_LED,ATTR_LABEL_TEXT,"开"); //LED标题设置为开
				for(i=0;i<100;i++)
				{
					datapoints[i]=100*rand()/32767.0;	//生成随机数
					Delay(0.01);	//延时0.01秒 单位s
					SetCtrlVal(panelHandle,PANEL_NUMERICTHERM,datapoints[i]);	//设置温度计控件值
					PlotStripChartPoint(panelHandle,PANEL_STRIPCHART,datapoints[i]);	//折线图中滚动显示数据
				}
				MaxMin1D(datapoints,100,&max,&max_index,&min,&min_index);	//找出随机数中的最大值最小值
				SetCtrlVal(panelHandle,PANEL_NUMERIC,max);	// 
				SetCtrlVal(panelHandle,PANEL_NUMERIC_2,min);	//最大最小值设置到控件
				SetCtrlVal(panelHandle,PANEL_BINARYSWITCH,0);		  //关闭采样开关 
				SetCtrlVal(panelHandle,PANEL_LED,0);	//关闭LED  
				SetCtrlVal(panelHandle,PANEL_NUMERICTHERM,0.00);	//温度计归零
				SetCtrlAttribute(panelHandle,PANEL_LED,ATTR_LABEL_TEXT,"关"); //LED标题设置为关
			}
			else
			{
				SetCtrlVal(panelHandle,PANEL_LED,0);	//关闭LED  
				SetCtrlVal(panelHandle,PANEL_NUMERICTHERM,0.00);	//温度计归零
				SetCtrlAttribute(panelHandle,PANEL_LED,ATTR_LABEL_TEXT,"关"); //LED标题设置为关	
			}					    
			break;
	}
	return 0;
}

int CVICALLBACK Quit (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{

	
	switch (event)
	{
		case EVENT_COMMIT:
			 QuitUserInterface(0);
			break;
	}
	return 0;
}
