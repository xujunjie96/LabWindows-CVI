<<<<<<< HEAD
#include <windows.h>  
#include <cvirte.h>
  //编译dll时要选择release模式才能生成静态到入库lib文件  1 configuration也是release模式  2 targetsetting也是release模式，change勾选上.h文件 
int __stdcall DllMain (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
		//初始化cvi的rte 装载d11
		case DLL_PROCESS_ATTACH:
			if (InitCVIRTE (hinstDLL, 0, 0) == 0)
				return 0;	  /* out of memory */
			break;
		//关闭cvi的rte 卸载dll 释放分配的资源
		case DLL_PROCESS_DETACH:
			CloseCVIRTE ();
			break;
	}
	
	return 1; //返回值1 说明dllmain函数初始化成功
}

int __stdcall DllEntryPoint (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	/* Included for compatibility with Borland */
	//borland c++ builder的dll定义的入口点
	return DllMain (hinstDLL, fdwReason, lpvReserved);
}

int __stdcall GetVirtualKey(int *Capslock,int *NumLock,int *ScrollLock,int *AsciiA)
{
	int asciiA=65;
	*Capslock=GetKeyState(VK_CAPITAL);//获得capslock锁定键值 1为按下状态
	*NumLock=GetKeyState(VK_NUMLOCK);//获得numlock锁定键值 1为按下状态
	*ScrollLock=GetKeyState(VK_SCROLL);//获得scrolllock锁定键值 1为按下状态 
	*AsciiA=GetKeyState(asciiA);//获得字母A键值键值 1为按下状态 
}
=======
#include <windows.h>  
#include <cvirte.h>
  //编译dll时要选择release模式才能生成静态到入库lib文件  1 configuration也是release模式  2 targetsetting也是release模式，change勾选上.h文件 
int __stdcall DllMain (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
		//初始化cvi的rte 装载d11
		case DLL_PROCESS_ATTACH:
			if (InitCVIRTE (hinstDLL, 0, 0) == 0)
				return 0;	  /* out of memory */
			break;
		//关闭cvi的rte 卸载dll 释放分配的资源
		case DLL_PROCESS_DETACH:
			CloseCVIRTE ();
			break;
	}
	
	return 1; //返回值1 说明dllmain函数初始化成功
}

int __stdcall DllEntryPoint (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	/* Included for compatibility with Borland */
	//borland c++ builder的dll定义的入口点
	return DllMain (hinstDLL, fdwReason, lpvReserved);
}

int __stdcall GetVirtualKey(int *Capslock,int *NumLock,int *ScrollLock,int *AsciiA)
{
	int asciiA=65;
	*Capslock=GetKeyState(VK_CAPITAL);//获得capslock锁定键值 1为按下状态
	*NumLock=GetKeyState(VK_NUMLOCK);//获得numlock锁定键值 1为按下状态
	*ScrollLock=GetKeyState(VK_SCROLL);//获得scrolllock锁定键值 1为按下状态 
	*AsciiA=GetKeyState(asciiA);//获得字母A键值键值 1为按下状态 
}
>>>>>>> 6cb5d42fc5d5a1f945cc808ffbde2a6f84a8e888
