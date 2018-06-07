#include <utility.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "game.h"

static int i=0;
static char *data;
static int hh=9;
static int vv=-8;

struct porperty{	//定义 ball,bar,panel为结构体类型变量
	int left;
	int top;
	int width;
	int height;
}ball,bar,panel1;

static int setpanelHandle; 
static int panelHandle;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "game.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	
	GetPanelAttribute(panelHandle,ATTR_HEIGHT,&panel1.height);	//获得面板的高，并将其值传给panel1.height
	SetCtrlAttribute(panelHandle,PANEL_BAR,ATTR_TOP,panel1.height-20);	//设置bar的高为panel高减去20
	
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

//定时器回调函数
int CVICALLBACK timer (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK: 
			i++;
			GetCtrlAttribute(panelHandle,PANEL_BAR,ATTR_LEFT,&bar.left);
			GetCtrlAttribute(panelHandle,PANEL_BAR,ATTR_TOP,&bar.top);  
			GetCtrlAttribute(panelHandle,PANEL_BAR,ATTR_HEIGHT,&bar.height);  
			GetCtrlAttribute(panelHandle,PANEL_BAR,ATTR_WIDTH,&bar.width);  
			GetCtrlAttribute(panelHandle,PANEL_BALL,ATTR_LEFT,&ball.left);  
			GetCtrlAttribute(panelHandle,PANEL_BALL,ATTR_TOP,&ball.top);  
			GetCtrlAttribute(panelHandle,PANEL_BALL,ATTR_HEIGHT,&ball.height);  
			GetCtrlAttribute(panelHandle,PANEL_BALL,ATTR_WIDTH,&ball.width);  
			GetPanelAttribute(panelHandle,ATTR_HEIGHT,&panel1.height);  
			GetPanelAttribute(panelHandle,ATTR_WIDTH,&panel1.width); //每隔设定时间 对bar ball panel重新获得位置属性 
			
			if((ball.left<=0)||((ball.left+ball.width)>=panel1.width))	//如果ball弹到面板左右两侧则反方向弹回
			{
				hh=-1*hh; //左右方向改变
				Beep();//响声
			}
			if((ball.top<=0)||((ball.top>=bar.top-10)&&(ball.left>=bar.left)&&(ball.left<=bar.left+bar.width)))	//如果ball弹到面板上或者bar上则反方向弹回
			{
				vv=-1*vv; //上下方向改变
				Beep();//响声
			}
			
			ball.left+=hh;
			ball.top+=vv;
			SetCtrlAttribute(panelHandle,PANEL_BALL,ATTR_TOP,ball.top);
			SetCtrlAttribute(panelHandle,PANEL_BALL,ATTR_LEFT,ball.left);
			if(ball.top>=bar.top+40) //未被挡住 弹出面板PANEL_SET
			{
				SetCtrlAttribute(panelHandle, PANEL_TIMER,ATTR_ENABLED,0);
				setpanelHandle=LoadPanel(0,"game.uir",PANEL_SET);	//载入panel_set面板
				InstallPopup(setpanelHandle);
				SetCtrlVal(setpanelHandle,PANEL_SET_NUMERIC,(int)(i/20));	//时间作为分数
				data=DateStr();	//获得当前的日期
				SetCtrlVal(setpanelHandle,PANEL_SET_STRING,data);
			}
			break;
	}
	return 0;
}

//确定按钮 重新开始游戏
int CVICALLBACK ok (int panel, int control, int event,
					void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			hh=9;
			vv=-8;
			 SetCtrlAttribute(panelHandle,PANEL_BALL,ATTR_TOP,50);
			 SetCtrlAttribute(panelHandle,PANEL_BALL,ATTR_LEFT,50); 
			 SetCtrlAttribute(panelHandle, PANEL_TIMER,ATTR_ENABLED,1);
			 DiscardPanel (setpanelHandle);
			break;
	}
	return 0;
}

//退出游戏
int CVICALLBACK exitsys (int panel, int control, int event,
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

//panel面板回调函数  
int CVICALLBACK panelcb (int panel, int event, void *callbackData,
						 int eventData1, int eventData2)
{	   
	int lowerasc;
	int vk;
	int asc;
	int barleft;
	switch (event)
	{
		case EVENT_KEYPRESS: //相应键盘事件

			vk=eventData1&VAL_VKEY_MASK;	//按键ASCLL码值
			asc=eventData1&VAL_ASCII_KEY_MASK; //虚拟键键值
			lowerasc=tolower(asc);	//按键为大写则转换为小写
			switch(vk)
			{
				case VAL_RIGHT_ARROW_VKEY:  //如果按键为右方向键，则bar向右移40
					GetCtrlAttribute(panelHandle,PANEL_BAR,ATTR_LEFT,&barleft);
					SetCtrlAttribute(panelHandle,PANEL_BAR,ATTR_LEFT,barleft+40); 
					break;
				case VAL_LEFT_ARROW_VKEY:  //如果按键为左方向键，则bar向左移40
					GetCtrlAttribute(panelHandle,PANEL_BAR,ATTR_LEFT,&barleft);
					SetCtrlAttribute(panelHandle,PANEL_BAR,ATTR_LEFT,barleft-40);
					break;
				default:
				break;
			}
			switch(lowerasc)
			{
				case 'd':  //如果按键为d，则bar向右移40
					GetCtrlAttribute(panelHandle,PANEL_BAR,ATTR_LEFT,&barleft);
					SetCtrlAttribute(panelHandle,PANEL_BAR,ATTR_LEFT,barleft+40); 
					break;
				case 'a':  //如果按键为a，则bar向左移40
					GetCtrlAttribute(panelHandle,PANEL_BAR,ATTR_LEFT,&barleft);
					SetCtrlAttribute(panelHandle,PANEL_BAR,ATTR_LEFT,barleft-40);
					break;
				default:
				break;
			}
			break;
		case EVENT_CLOSE:

			break;
		case EVENT_PANEL_SIZE:	  //面板尺寸改变 重新获取
			GetPanelAttribute(panelHandle,ATTR_HEIGHT,&panel1.height);	//获得面板的高，并将其值传给panel1.height
			SetCtrlAttribute(panelHandle,PANEL_BAR,ATTR_TOP,panel1.height-20);	//设置bar的高为panel高减去20
			break;
	}
	return 0;
}
