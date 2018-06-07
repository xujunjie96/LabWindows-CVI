<<<<<<< HEAD:ç¬¬07ç«  é€šä¿¡æ¥å£ä¸åŠ¨æ€æ•°æ®äº¤æ¢æŠ€æœ¯/7.4 DDEåŠ¨æ€é“¾æ•°æ®äº¤æ¢æŠ€æœ¯/ddesample.c
#include <analysis.h>
#include <ddesupp.h>
#include <utility.h>
#include <ansi_c.h>
#include "toolbox.h"
#include <formatio.h>
#include <cvirte.h>		
#include <userint.h>
#include "ddesample.h"

static int panelHandle;
static int ddelinkstatus=-1;//³õÊ¼»¯DDEÁ¬½Ó×´Ì¬ ´óÓÚµÈÓÚ0Îª³É¹¦Á¬½Ó
static unsigned int datalink;
static int panelHandle;

int clientCB(unsigned handle,char *topicName, char *itemName,int xType,int dataFmt,int dataSize,void *dataPtr,void *callbackData);   //ÉùÃ÷DDE»Øµ÷º¯Êı
void ddewave(char databuf[],char testbuf[],double wavw[]);  //×Ô¶¨Òåº¯Êı ÏòexcelĞ´Êı¾İ

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "ddesample.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK panelCB (int panel, int event, void *callbackData,
						 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_CLOSE:
			//Èç¹û½¨Á¢DDEÁ´½Ó ÔòÖ´ĞĞÒÔÏÂ´úÂë
			if(ddelinkstatus>=0)
			{
				 ClientDDEExecute (datalink, "[SAVE()]", 0); //±£´æexcelÎÄ¼ş
				 ClientDDEExecute (datalink, "[QUIT()]", 0); //ÍË³öexcel
				 DisconnectFromDDEServer (datalink);	 //¶Ï¿ªDDEÁ¬½Ó
			}
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK startexcel (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	char prjdir[MAX_PATHNAME_LEN];
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetDir (prjdir);
			strcat(prjdir,"\\wjx.xls");
			OpenDocumentInDefaultViewer (prjdir, VAL_NO_ZOOM);
			SetInputMode (panelHandle, PANEL_CMD_START, 0);   //°´Å¥±ä°µ ²»¿Éµã»÷
			break;
	}
		  
	return 0;
}

int CVICALLBACK linkexcel (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	char prjdir[MAX_PATHNAME_LEN];  
	char testbuf[50];
	double value;
	char databuf[100];
	char lineitem[20];
	char line[10];
	int i,j;
	switch (event)
	{
		case EVENT_COMMIT:
			GetDir (prjdir);
			strcat(prjdir,"\\wjx.xls");
			if((ddelinkstatus=ConnectToDDEServer (&datalink, "excel", prjdir, clientCB, 0))>=0)
				  SetInputMode (panelHandle, PANEL_CMD_LINK, 0);   //°´Å¥±ä°µ ²»¿Éµã»÷
			SetUpDDEHotLink (datalink, "R1C1:R10C10", CF_TEXT, 0);//Óë·şÎñÆ÷½¨Á¢ÈÈÁ´½Ó  R1C1:R10C10Ö¸excelµÚÒ»ĞĞµÚÒ»ÁĞµ½10ĞĞ10ÁĞ
			//½«excelÇ°10ĞĞ10ÁĞĞ´Èëtable±í¸ñÖĞ
			for(i=1;i<=10;i++)
			{
				for(j=1;j<=10;j++)
				{
					lineitem[0]='\0';
					line[0]='\0';
					value=0.0;
					strcat(lineitem,"R");
					Fmt(line,"%s<%d",i);
					strcat(lineitem,line);
					strcat(lineitem,"C");
					line[0]='\0';
					Fmt(line,"%s<%d",j);
					strcat(lineitem,line);
					ClientDDERead (datalink, lineitem, CF_TEXT, databuf, sizeof(databuf), 0);   //´ÓDDE·şÎñÆ÷¶ÁÈ¡Êı¾İ
					Fmt(&value,"%f<%s",databuf);
					SetTableCellVal (panelHandle, PANEL_TABLE, MakePoint(j,i), value);	  //½«Êı¾İĞ´Èë±í¸ñÖĞ
					
				}
			}
			break;
	}																	  
	
	return 0;
}

//ÉùÃ÷DDE»Øµ÷º¯Êı
int clientCB(unsigned handle,char *topicName, char *itemName,int xType,int dataFmt,int dataSize,void *dataPtr,void *callbackData)   
{
	double value;
	switch (xType)
	{
		case DDE_DISCONNECT:
			DisableBreakOnLibraryErrors();//µ±²úÉú¿âº¯Êı´íÎóÊ±£¬½ûÖ¹µ¯³öÔËĞĞÊ±´íÎó¶Ô»°¿ò
			DisconnectFromDDEServer (datalink);
			break;
		case DDE_DATAREADY:
			Fmt(&value,"%f<%s",(char*)dataPtr);//»ñµÃDDEÁ¬½ÓµÚÒ»ĞĞµÚÒ»ÁĞµÄÊı¾İ
			SetCtrlVal (panelHandle, PANEL_CELLVALUE, value);
			break;
	}
	return 0;
}

int CVICALLBACK wavesignal (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	char databuf[10000];
	char testbuf[100];
	double wave[100];
	double sinephase=0;
	double cosphase=90.0;
	double squarephase=90.0;
	int wavemode;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_RINGSLIDE, &wavemode);	
			switch(wavemode)
			{
				case 1:
					SineWave (100, 1.0, 0.01, &sinephase, wave);
					ddewave(databuf,testbuf,wave);
					break;
				case 2:
					SineWave (100, 1.0, 0.01, &cosphase, wave);
					ddewave(databuf,testbuf,wave);
					break;
				case 3:
					Triangle (100, 1.0, wave);
					ddewave(databuf,testbuf,wave);
					break;
				case 4:
					SquareWave (100, 1.0, 0.01, &squarephase, 50.0, wave);
					ddewave(databuf,testbuf,wave);
					break;
				case 5:
					Pulse (100, 1.0, 0, 1, wave);
					
					ddewave(databuf,testbuf,wave);
					break;
			}
			

			break;
	}
	return 0;
}

//×Ô¶¨Òåº¯Êı ÏòexcelĞ´Êı¾İ     											   
void ddewave(char databuf[],char testbuf[],double wave[])
{
	int i;
	
	databuf[0]='\0';
	testbuf[0]='\0';
	for(i=0;i<100;i++)
	{
		Fmt(testbuf,"%s<%f",wave[i]);
		strcat(databuf,testbuf);
		strcat(databuf,"\n");
	}
	ClientDDEWrite (datalink, "R1C1:R100C1", CF_TEXT, databuf, strlen(databuf), 0); //Ïòdde·şÎñÆ÷Ğ´Êı¾İ
	linkexcel(panelHandle,PANEL_CMD_LINK,EVENT_COMMIT,NULL,0,0);  //Ë¢ĞÂÊı¾İ
}
=======
#include <analysis.h>
#include <ddesupp.h>
#include <utility.h>
#include <ansi_c.h>
#include "toolbox.h"
#include <formatio.h>
#include <cvirte.h>		
#include <userint.h>
#include "ddesample.h"

static int panelHandle;
static int ddelinkstatus=-1;//³õÊ¼»¯DDEÁ¬½Ó×´Ì¬ ´óÓÚµÈÓÚ0Îª³É¹¦Á¬½Ó
static unsigned int datalink;
static int panelHandle;

int clientCB(unsigned handle,char *topicName, char *itemName,int xType,int dataFmt,int dataSize,void *dataPtr,void *callbackData);   //ÉùÃ÷DDE»Øµ÷º¯Êı
void ddewave(char databuf[],char testbuf[],double wavw[]);  //×Ô¶¨Òåº¯Êı ÏòexcelĞ´Êı¾İ

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "ddesample.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK panelCB (int panel, int event, void *callbackData,
						 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_CLOSE:
			//Èç¹û½¨Á¢DDEÁ´½Ó ÔòÖ´ĞĞÒÔÏÂ´úÂë
			if(ddelinkstatus>=0)
			{
				 ClientDDEExecute (datalink, "[SAVE()]", 0); //±£´æexcelÎÄ¼ş
				 ClientDDEExecute (datalink, "[QUIT()]", 0); //ÍË³öexcel
				 DisconnectFromDDEServer (datalink);	 //¶Ï¿ªDDEÁ¬½Ó
			}
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK startexcel (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	char prjdir[MAX_PATHNAME_LEN];
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetDir (prjdir);
			strcat(prjdir,"\\wjx.xls");
			OpenDocumentInDefaultViewer (prjdir, VAL_NO_ZOOM);
			SetInputMode (panelHandle, PANEL_CMD_START, 0);   //°´Å¥±ä°µ ²»¿Éµã»÷
			break;
	}
		  
	return 0;
}

int CVICALLBACK linkexcel (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	char prjdir[MAX_PATHNAME_LEN];  
	char testbuf[50];
	double value;
	char databuf[100];
	char lineitem[20];
	char line[10];
	int i,j;
	switch (event)
	{
		case EVENT_COMMIT:
			GetDir (prjdir);
			strcat(prjdir,"\\wjx.xls");
			if((ddelinkstatus=ConnectToDDEServer (&datalink, "excel", prjdir, clientCB, 0))>=0)
				  SetInputMode (panelHandle, PANEL_CMD_LINK, 0);   //°´Å¥±ä°µ ²»¿Éµã»÷
			SetUpDDEHotLink (datalink, "R1C1:R10C10", CF_TEXT, 0);//Óë·şÎñÆ÷½¨Á¢ÈÈÁ´½Ó  R1C1:R10C10Ö¸excelµÚÒ»ĞĞµÚÒ»ÁĞµ½10ĞĞ10ÁĞ
			//½«excelÇ°10ĞĞ10ÁĞĞ´Èëtable±í¸ñÖĞ
			for(i=1;i<=10;i++)
			{
				for(j=1;j<=10;j++)
				{
					lineitem[0]='\0';
					line[0]='\0';
					value=0.0;
					strcat(lineitem,"R");
					Fmt(line,"%s<%d",i);
					strcat(lineitem,line);
					strcat(lineitem,"C");
					line[0]='\0';
					Fmt(line,"%s<%d",j);
					strcat(lineitem,line);
					ClientDDERead (datalink, lineitem, CF_TEXT, databuf, sizeof(databuf), 0);   //´ÓDDE·şÎñÆ÷¶ÁÈ¡Êı¾İ
					Fmt(&value,"%f<%s",databuf);
					SetTableCellVal (panelHandle, PANEL_TABLE, MakePoint(j,i), value);	  //½«Êı¾İĞ´Èë±í¸ñÖĞ
					
				}
			}
			break;
	}																	  
	
	return 0;
}

//ÉùÃ÷DDE»Øµ÷º¯Êı
int clientCB(unsigned handle,char *topicName, char *itemName,int xType,int dataFmt,int dataSize,void *dataPtr,void *callbackData)   
{
	double value;
	switch (xType)
	{
		case DDE_DISCONNECT:
			DisableBreakOnLibraryErrors();
			DisconnectFromDDEServer (datalink);
			break;
		case DDE_DATAREADY:
			Fmt(&value,"%f<%s",(char*)dataPtr);//»ñµÃDDEÁ¬½ÓµÚÒ»ĞĞµÚÒ»ÁĞµÄÊı¾İ
			SetCtrlVal (panelHandle, PANEL_CELLVALUE, value);
			break;
	}
	return 0;
}

int CVICALLBACK wavesignal (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	char databuf[10000];
	char testbuf[100];
	double wave[100];
	double sinephase=0;
	double cosphase=90.0;
	double squarephase=90.0;
	int wavemode;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_RINGSLIDE, &wavemode);	
			switch(wavemode)
			{
				case 1:
					SineWave (100, 1.0, 0.01, &sinephase, wave);
					ddewave(databuf,testbuf,wave);
					break;
				case 2:
					SineWave (100, 1.0, 0.01, &cosphase, wave);
					ddewave(databuf,testbuf,wave);
					break;
				case 3:
					Triangle (100, 1.0, wave);
					ddewave(databuf,testbuf,wave);
					break;
				case 4:
					SquareWave (100, 1.0, 0.01, &squarephase, 50.0, wave);
					ddewave(databuf,testbuf,wave);
					break;
				case 5:
					Pulse (100, 1.0, 0, 1, wave);
					
					ddewave(databuf,testbuf,wave);
					break;
			}
			

			break;
	}
	return 0;
}

//×Ô¶¨Òåº¯Êı ÏòexcelĞ´Êı¾İ     											   
void ddewave(char databuf[],char testbuf[],double wave[])
{
	int i;
	
	databuf[0]='\0';
	testbuf[0]='\0';
	for(i=0;i<100;i++)
	{
		Fmt(testbuf,"%s<%f",wave[i]);
		strcat(databuf,testbuf);
		strcat(databuf,"\n");
	}
	ClientDDEWrite (datalink, "R1C1:R100C1", CF_TEXT, databuf, strlen(databuf), 0); //Ïòdde·şÎñÆ÷Ğ´Êı¾İ
	linkexcel(panelHandle,PANEL_CMD_LINK,EVENT_COMMIT,NULL,0,0);  //Ë¢ĞÂÊı¾İ
}
>>>>>>> 6cb5d42fc5d5a1f945cc808ffbde2a6f84a8e888:ç¬¬7ç«  é€šä¿¡æ¥å£ä¸åŠ¨æ€æ•°æ®äº¤æ¢æŠ€æœ¯/7.4 DDEåŠ¨æ€é“¾æ•°æ®äº¤æ¢æŠ€æœ¯/ddesample.c
