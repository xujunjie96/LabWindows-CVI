#include "toolbox.h"
#include "popup.h"

static int panelHandle;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "popup.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

//Message按钮回调函数
int CVICALLBACK messagepop (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			MessagePopup ("MessagePopup", "这是一个Message Popup窗口");
			break;
	}
	return 0;
}

//confirmpop按钮回调函数
int CVICALLBACK confirmpop (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	int confirm;
	switch (event)
	{
		case EVENT_COMMIT:
			confirm=ConfirmPopup ("Confirm Popup", "这是一个Confirm Popup窗口");
			if(confirm==1)
			{
				QuitUserInterface (0);	
			}
			break;
	}
	return 0;
}

//genericpopup按钮回调函数
int CVICALLBACK genericpopup (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{   
	char responsebuffer[101];
	int selbutton;
	switch (event)
	{
		case EVENT_COMMIT:
			selbutton=GenericMessagePopup ("Generic Message Popup", "这是一个Generic Message Popup窗口", "按钮1", "按钮2", "按钮3",
										   responsebuffer, 100, 0, VAL_GENERIC_POPUP_BTN1, VAL_GENERIC_POPUP_BTN1, VAL_GENERIC_POPUP_BTN3);
			break;
	}
	return 0;
}

//promptpopup按钮回调函数
int CVICALLBACK promptpopup (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	char responsebuffer[101];  
	switch (event)
	{
		case EVENT_COMMIT:
			PromptPopup ("Prompt Popup", "这是一个Prompt Popup窗口", responsebuffer, 100);
			break;
	}
	return 0;
}

//font 按钮回调函数
int CVICALLBACK font (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{   
	int selectionstatus=0;
	int size,color,just,italic,strikeout,underline,bold;
	char typeface[1000]={"宋体"};
	switch (event)
	{
		case EVENT_COMMIT:
			selectionstatus=FontSelectPopup ("Font Select Popup", "Sample Text", 0,typeface, &bold ,&underline, &strikeout, &italic, &just, &color, &size,6, 48, 1, 0);

		if(selectionstatus>0)
			 {
			 	SetCtrlAttribute (panelHandle, PANEL_TEXTBOX, ATTR_TEXT_BOLD,bold );
				SetCtrlAttribute (panelHandle, PANEL_TEXTBOX, ATTR_TEXT_COLOR, color);
				SetCtrlAttribute (panelHandle, PANEL_TEXTBOX, ATTR_TEXT_FONT, typeface);
				SetCtrlAttribute (panelHandle, PANEL_TEXTBOX, ATTR_TEXT_ITALIC,italic);
				SetCtrlAttribute (panelHandle, PANEL_TEXTBOX, ATTR_TEXT_JUSTIFY, just);
				SetCtrlAttribute (panelHandle, PANEL_TEXTBOX, ATTR_TEXT_STRIKEOUT,strikeout );
				SetCtrlAttribute (panelHandle, PANEL_TEXTBOX, ATTR_TEXT_UNDERLINE,underline );
				SetCtrlAttribute (panelHandle, PANEL_TEXTBOX, ATTR_LABEL_BGCOLOR, color);
				SetCtrlAttribute (panelHandle, PANEL_TEXTBOX, ATTR_LABEL_POINT_SIZE, size);
				
			 }

			break;
	}
	return 0;
}




//fileselect按钮回调函数
int CVICALLBACK fileselectpopup (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	char pathname[MAX_PATHNAME_LEN];
	switch (event)
	{
		case EVENT_COMMIT:
			FileSelectPopup ("", "*.h", ".c;.h", "File Select Popup", VAL_LOAD_BUTTON, 0, 0, 1, 0, pathname);
			break;
	}
	return 0;
}

//ygraphpopup 按钮回调函数
int CVICALLBACK ygraphpopup (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	double value[100];
	int i;
	switch (event)
	{
		case EVENT_COMMIT:
		  for(i=0;i<100;i++)
		  {
		  	value[i]=Random(0,100);
		  }
		  YGraphPopup ("Y Graph Popup", value, 100, VAL_DOUBLE);
			break;
	}
	return 0;
}

//dirpopup 按钮回调函数
int CVICALLBACK dirpopup (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	char pathname[MAX_PATHNAME_LEN];
	switch (event)
	{
		case EVENT_COMMIT:
			DirSelectPopup ("", "Select Directory", 1, 1, pathname);
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
