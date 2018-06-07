#include "windows.h" 
#include <cvirte.h>		
#include <userint.h>
#include "specialdisplay.h"

static int panelHandle;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "specialdisplay.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	CloseCVIRTE ();
	return 0;
}

int CVICALLBACK panelCB (int panel, int event, void *callbackData,
						 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_DOUBLE_CLICK:
			QuitUserInterface(0);  //双击面板时退出程序
			break;
		case EVENT_CLOSE:
			QuitUserInterface(0);
			break;
	}
	return 0;
}

int CVICALLBACK color (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	int color;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_COLORNUM, &color); 
			SetPanelAttribute (panelHandle, ATTR_BACKCOLOR, color);//设置面板颜色
			break;		
		case EVENT_VAL_CHANGED:

			break;
	}
	return 0;
}

int CVICALLBACK shape (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	int shapevalue,titlebar;
	int titlebarheight=0;
	HWND hwnd;
	RECT windowrect,clientrect,shaperect;//对于RECT cvi中为Rect windows中为RECT 注意区分大小写
	int fullheight,fullwidth,verticalborderwidth,horizentalborderwidth;
	HRGN winrgn,inner;
	int arcvalue=0;
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetPanelAttribute (panelHandle, ATTR_SYSTEM_WINDOW_HANDLE, (int*)&hwnd); //获得窗口句柄
			GetPanelAttribute (panelHandle, ATTR_TITLEBAR_VISIBLE, &titlebar);//获得标题栏的可见性
			if(titlebar)
			{
				titlebarheight=GetSystemMetrics(SM_CYCAPTION);	 //WINDOWS SDK函数 获得窗口标题的高度
			}
			//获得整个窗口的矩形范围 窗口的边框 标题栏 滚动条以及菜单都在这个矩形内
			//hwnd 想获得矩形范围的那个窗口句柄
			//windowrect 屏幕坐标中随同窗口装载的那个矩形
			GetWindowRect(hwnd,&windowrect);
			GetClientRect(hwnd,&clientrect);//返回指定窗口客户区矩形的大小
			fullheight=windowrect.bottom-windowrect.top;//获得面板总体高度
			fullwidth=windowrect.right-windowrect.left;//获得面板总体宽度
			verticalborderwidth=(fullheight-clientrect.bottom-titlebarheight)/2; //获得上下两个边框中任一边框的高度
			horizentalborderwidth=(fullwidth-clientrect.right);//获得左右两个边框中任一边框的高度 
			//得到绘制图形的区域
			shaperect.left= horizentalborderwidth;
			shaperect.top=titlebarheight+ verticalborderwidth;
			shaperect.right=clientrect.right+horizentalborderwidth;
			shaperect.bottom=clientrect.bottom+ verticalborderwidth+ titlebarheight;
			//获得绘图形状
			GetCtrlVal (panelHandle, PANEL_RING, &shapevalue);
			
			switch(shapevalue)
			{
				case 0:
					winrgn=CreateEllipticRgn(shaperect.left,shaperect.top,shaperect.right,shaperect.bottom);//创建一个椭圆
					SetWindowRgn(hwnd,winrgn,1); //改变窗口的区域
					break;
				case 1:
					GetCtrlVal (panelHandle, PANEL_NUMERICGAUGE, &arcvalue);
					winrgn=CreateRoundRectRgn(shaperect.left,shaperect.top,shaperect.right,shaperect.bottom,arcvalue,arcvalue);//创建一个圆角矩形 
					SetWindowRgn(hwnd,winrgn,1); //改变窗口的区域 
					break;
				case 2:
					GetCtrlVal (panelHandle, PANEL_NUMERICGAUGE, &arcvalue);
					winrgn=CreateEllipticRgn(shaperect.left,shaperect.top,shaperect.right,shaperect.bottom);//创建一个椭圆
					inner=CreateEllipticRgn(shaperect.left+arcvalue,shaperect.top+arcvalue,shaperect.right-arcvalue,shaperect.bottom-arcvalue);//创建一个椭圆
					CombineRgn(winrgn,winrgn,inner,RGN_DIFF);//将两个不相交的而部分组合为一个新的区域
					DeleteObject(inner); //删除gdi对象
					SetWindowRgn(hwnd,winrgn,1); //改变窗口的区域  
					break;
			}
			break;
			
		case EVENT_VAL_CHANGED:

			break;
	}
	return 0;
}
