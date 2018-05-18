#include "toolbox.h"
#include "pwctrl.h"
#include "combobox.h"
#include <cvirte.h>		
#include <userint.h>
#include "password.h"

static int panelHandle;
static int panelpassword;
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "password.uir", PANEL)) < 0)
		return -1;
	PasswordCtrl_ConvertFromString (panelHandle, PANEL_PASSWORD);	//string控件转换成password控件
	Combo_NewComboBox (panelHandle, PANEL_COMBO);   //string控件转换成combo控件
	//向combo控件插入内容
	Combo_InsertComboItem (panelHandle, PANEL_COMBO, -1, "2b");
	Combo_InsertComboItem (panelHandle, PANEL_COMBO, -1, "a2");
	Combo_InsertComboItem (panelHandle, PANEL_COMBO, -1, "9s");
	Combo_InsertComboItem (panelHandle, PANEL_COMBO, -1, "lem");
	SetCtrlToolTipAttribute (panelHandle, PANEL_CMD_OK, CTRL_TOOLTIP_ATTR_ENABLE, 1);//用于控制是否显示提示内容 默认显示
	//当鼠标悬停时 设置每个控件应提示的内容
	SetCtrlToolTipAttribute (panelHandle, PANEL_CMD_OK, CTRL_TOOLTIP_ATTR_TEXT, "这是确定按钮");
	SetCtrlToolTipAttribute (panelHandle, PANEL_CMD_CLEAR, CTRL_TOOLTIP_ATTR_TEXT, "这是取消按钮");
	SetCtrlToolTipAttribute (panelHandle, PANEL_CMD_VIEW, CTRL_TOOLTIP_ATTR_TEXT, "这是查看密码按钮");
	SetCtrlToolTipAttribute (panelHandle, PANEL_COMBO, CTRL_TOOLTIP_ATTR_TEXT, "请输入用户名");
	SetCtrlToolTipAttribute (panelHandle, PANEL_PASSWORD, CTRL_TOOLTIP_ATTR_TEXT, "请输入密码");

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
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK hidepanel (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			DiscardPanel (panelpassword);
			break;
	}
	return 0;
}

int CVICALLBACK passwoedview (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			panelpassword=LoadPanel (0, "password.uir", PANEL_2);
			InstallPopup(panelpassword);  //采用模式对话框  InstallPopup函数的功能是显示并激活一个弹出面板
			break;
	}
	return 0;
}

int CVICALLBACK cancel (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			PasswordCtrl_SetAttribute (panelHandle, PANEL_PASSWORD, ATTR_PASSWORD_VAL, "");  //清除密码

			break;
	}
	return 0;
}


//确认时候输入正确
int CVICALLBACK ok (int panel, int control, int event,
					void *callbackData, int eventData1, int eventData2)
{
	int len;
	int plen;
	
	char *username;
	char *passwordstring;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlAttribute (panelHandle, PANEL_COMBO, ATTR_STRING_TEXT_LENGTH,&len );		//获得combo box中字符串长度
			username=(char*)malloc(len*sizeof(char)+1);   //动态分配字符串长度加1的空间 最后一个字节存储结束符 \0 值
			username[0]='\0';	//清空用户名中内容
			GetCtrlVal (panelHandle, PANEL_COMBO, username); //将用户名存储到usrname
			PasswordCtrl_GetAttribute (panelHandle, PANEL_PASSWORD, ATTR_PASSWORD_MAX_LENGTH,&plen );		//获得password box中字符串长度 
			passwordstring=(char*)malloc(plen*sizeof(char)+1);   //动态分配字符串长度加1的空间 最后一个字节存储结束符 \0 值
		   	passwordstring[0]='\0';	//清空password中内容	
			PasswordCtrl_GetAttribute (panelHandle, PANEL_PASSWORD, ATTR_PASSWORD_VAL, passwordstring);//取得password中存储的内容
			//判断密码是否正确
			if( ((strcmp(username,"2b")==0)&&(strcmp(passwordstring,"2b")==0)) || ((strcmp(username,"a2")==0)&&(strcmp(passwordstring,"a2")==0)) || ((strcmp(username,"9s")==0)&&(strcmp(passwordstring,"9s")==0))   || ((strcmp(username,"ezio")==0)&&(strcmp(passwordstring,"ezio")==0))  )
			{
				MessagePopup("密码","密码正确！");
			}
			else
			{
				MessagePopup("密码","密码错误！");
			}
			//释放动态分配内存
			free(username);
			free(passwordstring);
			break;
	}
	return 0;
}

int CVICALLBACK timer (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	int  keymodifiers;
	int rightdown=0;
	int leftdown=0;
	int y,x;
	int len;
	char *passwordstring;
	char message[100];
	switch (event)
	{
		case EVENT_TIMER_TICK:
			GetGlobalMouseState (&panelHandle, &x, &y, &leftdown, &rightdown, &keymodifiers);
			if(leftdown==1 && rightdown==1 && keymodifiers==VAL_MENUKEY_MODIFIER)
			{
			PasswordCtrl_GetAttribute (panelHandle, PANEL_PASSWORD, ATTR_PASSWORD_MAX_LENGTH,&len );		//获得password box中字符串长度 
			passwordstring=(char*)malloc(len*sizeof(char)+1);   //动态分配字符串长度加1的空间 最后一个字节存储结束符 \0 值
		   	message[0]='\0';	//清空password中内容	
			PasswordCtrl_GetAttribute (panelHandle, PANEL_PASSWORD, ATTR_PASSWORD_VAL, passwordstring);//取得password中存储的内容	
			strcat(message,"输入的密码是:\n");
			strcat(message,passwordstring);
			MessagePopup("密码",message); 
			}
			break;
	}
	return 0;
}
