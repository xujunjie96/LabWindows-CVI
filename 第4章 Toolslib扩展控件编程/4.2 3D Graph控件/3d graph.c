#include "3DGraphCtrl.h"
#include <analysis.h>
#include <cvirte.h>		
#include <userint.h>
#include "3d graph.h"

static CW3DGraphLibObj_CWPlot3D plotObjHandle;
static CW3DGraphLibObj_CWPlots3D plotsObjHandle;
static CAObjHandle graphObjHandle;
static int panelHandle;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "3d graph.uir", PANEL)) < 0)
		return -1;
/*=CHANGE:=============================================================*
To programmatically interact with the 3D graph, you will need to first obtain
the object handle. Use this handle to register event callback functions,
call methods, or get and set properties of the 3D graph.

Example Code:

	int							i, j;
	HRESULT						__result;
	CAObjHandle					graphObjHandle;
	CW3DGraphLibObj_CWPlots3D	plotObjHandle;
	CW3DGraphLibObj_CWPlot3D	plotObjHandle;
	double						zMatrix[10][10];
	VARIANT 					zMatrixV;

	GetObjHandleFromActiveXCtrl (panelHandle, PANEL_GRAPH3D,
											&graphObjHandle);

	__caErrChk(CW3DGraphLib__DCWGraph3DGetPlots (graphObjHandle, NULL,
											&plotObjHandle));
	__caErrChk(CW3DGraphLib_CWPlots3DItem (plotObjHandle, NULL,
										CA_VariantLong(1), &plotObjHandle));

	for (i=0; i<10; i++)
		for (j=0; j<10; j++)
			zMatrix[i][j] = (i*i) + (j*j);

	__caErrChk(CA_VariantSet2DArray (&zMatrixV, CAVT_DOUBLE, 10, 10,
							   zMatrix));

	__caErrChk(CW3DGraphLib_CWPlot3DPlot3DSimpleSurface (plotObjHandle, NULL, zMatrixV,
											  CA_DEFAULT_VAL));

Error:
	CA_VariantClear(&zMatrixV);
	CA_DiscardObjHandle(plotObjHandle);
	CA_DiscardObjHandle(plotObjHandle);
*==========================================================END=CHANGE=*/
	GetObjHandleFromActiveXCtrl (panelHandle, PANEL_GRAPH3D, &graphObjHandle);	  //获得graph3d控件的句柄
	CW3DGraphLib__DCWGraph3DGetPlots (graphObjHandle, NULL,  &plotObjHandle);	//获得graph3d控件绘图句柄
	CW3DGraphLib_CWPlots3DItem (plotObjHandle, NULL, CA_VariantLong(1), &plotObjHandle);  //获得graph3d控件绘图句柄 
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK projection (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	int type;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_RING_PROJECT, &type);
			//以下代码为清除投影
			 CW3DGraphLib_CWPlot3DSetProjectionXY (plotObjHandle, NULL, VFALSE);
			 CW3DGraphLib_CWPlot3DSetProjectionYZ (plotObjHandle, NULL, VFALSE);
			 CW3DGraphLib_CWPlot3DSetProjectionXZ (plotObjHandle, NULL, VFALSE);
			 //以下代码为设置投影方式 
			 switch (type)
			 {
				 case 0:
			 		CW3DGraphLib_CWPlot3DSetProjectionXY (plotObjHandle, NULL, VTRUE);
				break;
				case 1:
					CW3DGraphLib_CWPlot3DSetProjectionYZ (plotObjHandle, NULL, VTRUE);
				break;
				case 2:
					CW3DGraphLib_CWPlot3DSetProjectionXZ (plotObjHandle, NULL, VTRUE);
				break;
			 }
			break;
	}
	return 0;
}

int CVICALLBACK drawline (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	int line;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_RING_LINE, &line);
			// 以下代码为设置绘制图形的类型
		switch (line)
		{
			case 0:
			CW3DGraphLib_CWPlot3DSetStyle (plotObjHandle, NULL, CW3DGraphLibConst_cwLine);
			break;
			case 1:
			CW3DGraphLib_CWPlot3DSetStyle (plotObjHandle, NULL, CW3DGraphLibConst_cwPoint);	
			break;
			case 2:
			CW3DGraphLib_CWPlot3DSetStyle (plotObjHandle, NULL, CW3DGraphLibConst_cwLinePoint);	
			break;
			case 3:
			CW3DGraphLib_CWPlot3DSetStyle (plotObjHandle, NULL, CW3DGraphLibConst_cwHiddenLine);	
			break;
			case 4:
			CW3DGraphLib_CWPlot3DSetStyle (plotObjHandle, NULL, CW3DGraphLibConst_cwSurface);	
			break;
			case 5:
			CW3DGraphLib_CWPlot3DSetStyle (plotObjHandle, NULL, CW3DGraphLibConst_cwSurfaceLine);	
			break;
			case 6:
			CW3DGraphLib_CWPlot3DSetStyle (plotObjHandle, NULL, CW3DGraphLibConst_cwSurfaceNormal);	
			break;
			case 7:
			CW3DGraphLib_CWPlot3DSetStyle (plotObjHandle, NULL, CW3DGraphLibConst_cwContourLine);	
			break;
			case 8:
			CW3DGraphLib_CWPlot3DSetStyle (plotObjHandle, NULL, CW3DGraphLibConst_cwSurfaceContour);	
			break;
				
		}
			break;
	}
	return 0;
}

int CVICALLBACK generatewave (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	VARIANT GaussianNoiseV;
	double GaussianNoise[20][200];
	int i;
	
	switch (event)
	{
		case EVENT_COMMIT:
			for(i=0;i<20;i++)
			{
				GaussNoise(200,1.0,-2,GaussianNoise[i]);//产生二维高斯噪声
			}
			CA_VariantSet2DArray(&GaussianNoiseV,CAVT_DOUBLE,10,200,GaussianNoise);  //将double型数据转换成VARIANT型
			CW3DGraphLib_CWPlot3DPlot3DSimpleSurface (plotObjHandle, NULL, GaussianNoiseV, CA_DEFAULT_VAL); //绘制高斯噪声三维表面图
			CA_VariantClear(&GaussianNoiseV); //释放GaussianNoiseV型数据
			break;
	}
	return 0;
}

int CVICALLBACK clearwave (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			CW3DGraphLib_CWPlot3DClearData (plotObjHandle, NULL);
			break;
	}
	return 0;
}

int CVICALLBACK quitsys (int panel, int control, int event,
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

int CVICALLBACK trans (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	double transvalue;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_NUMERICSLIDE, &transvalue);
			CW3DGraphLib_CWPlot3DSetTransparency (plotObjHandle, NULL, transvalue); //设置图形的透明度

			break;
	}
	return 0;
}
