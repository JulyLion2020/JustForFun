#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include "resource.h"
#include "MainDlg.h"

BOOL WINAPI Main_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, Main_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, Main_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, Main_OnClose);
    }

    return FALSE;
}

int timeCnt = 30;

void CALLBACK MyTimerProc(HWND hwnd,UINT message,UINT iTimerID,DWORD dwTime)
{
	TCHAR str[256];

	itoa(timeCnt,str,10);
	SetDlgItemText(hwnd,IDC_EDITJISHI,str);	

	timeCnt  = timeCnt - 1;

	if(timeCnt <=-1)
	{  
	    KillTimer(hwnd,0);
	    MessageBox(hwnd,TEXT("开始自动关机!!!"),TEXT("警告"),MB_OK);
	  
		TOKEN_PRIVILEGES tp;
		HANDLE hToken; 
		LUID luid; 
		LPTSTR MachineName=NULL; 

		if(!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&hToken ))
		{
		   // PERR("OpenProcessToken",GetLastError());
			return ;
		}

		if(!LookupPrivilegeValue(MachineName, SE_SHUTDOWN_NAME, &luid))
		{
		  //  PERR("LookupPrivilegeValue", GetLastError());
			return ; 
		}

		tp.PrivilegeCount = 1; 
		tp.Privileges[0].Luid = luid; 
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
		AdjustTokenPrivileges(hToken,FALSE,&tp,sizeof(TOKEN_PRIVILEGES),NULL, NULL ); //到这里,是取得权限///

		ExitWindowsEx(EWX_POWEROFF,EWX_FORCE);
	}
}

BOOL Main_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    SetTimer(hwnd,0,1000,MyTimerProc);
	return TRUE;
}

void Main_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{   
    switch(id)
    {
        
	 case IDC_OK:
		{
			 TCHAR str1[256];
		     GetDlgItemText(hwnd,IDC_EDIT1,str1,sizeof(str1));
			 
			 TCHAR str2[256]="哥";

			 if(strcmp(str1,str2)==0)
			 {  
				 KillTimer(hwnd,0);
				 MessageBox(hwnd,"好吧，我认了，嘿嘿","回答",MB_OK|MB_ICONEXCLAMATION);	
			 } 
		
		}
        break;

		case IDC_CLOSE:
		{	
			TCHAR str1[256];
		    GetDlgItemText(hwnd,IDC_EDIT1,str1,sizeof(str1));
			 
			TCHAR str2[256]="哥";
			if(strcmp(str1,str2)==0)
			{   KillTimer(hwnd,0);
				MessageBox(hwnd,TEXT("你受惊了，现在开始关闭窗口"),TEXT("问候"),MB_OK|MB_ICONEXCLAMATION);
				DestroyWindow(hwnd);
			}
		}
		break;

        default:
		break;
    }
}

void Main_OnClose(HWND hwnd)
{
    //EndDialog(hwnd, 0);
}