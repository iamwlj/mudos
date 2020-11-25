#include "windows.h"
#define _VC_
#include "notify.h"
#include "stdio.h"
#include "direct.h"
#include "time.h"
#include "arch.h"
#include "com/resource.h"


int addr_main(int argc, char **argv);

typedef void (_cdecl * FPFUNCTION) ();

int  WINAPI mudos_runmudos(int argc,char **argv);
int  WINAPI mudos_initmud_ok();
int  WINAPI mudos_fatal(char *);
void WINAPI mudos_set_heartbeat(int);
int  WINAPI mudos_get_heartbeat();
int  WINAPI mudos_heartbeat();
void WINAPI mudos_set_info(char *arch);
extern int init_addr_server_ok;

HINSTANCE hinstance;
HWND hwnd;
NOTIFYICONDATA ni;
int in_restart=1;
int isservice=0;
int is95;
int query_restart=0;
char config_file[256];
char log_file[256];
char svr_long[128];
char svr_short[128];
#define SVR_SHORT svr_short
#define SVR_LONG  svr_long


const char * loadstring(UINT idx,char * p)
{
	static char str[1024];
	if(!p)p=str;
	if(!LoadString(hinstance,idx,p,sizeof(str))){
		p[0]=0;
	}
	return p;
}

static long load1,load10,load15;  // in 10000

void UpdateLoad()
{
	static long loads[60],loads_s[15];
	static long count;
	long load,i;
	HKEY hk;

	count++;

	load=0;  // can not get cpu usage
	if(RegOpenKey(HKEY_DYN_DATA,"PerfStats\\StartStat",&hk)==ERROR_SUCCESS){
		DWORD sz;
		sz=sizeof(load);
		RegQueryValueEx(hk,"KERNEL\\CPUUsage",NULL,NULL,(BYTE *)&load,&sz);
		RegCloseKey(hk);
		RegOpenKey(HKEY_DYN_DATA,"PerfStats\\StatData",&hk);
		RegQueryValueEx(hk,"KERNEL\\CPUUsage",NULL,NULL,(BYTE *)&load,&sz);
		RegCloseKey(hk);
	} else {
		// should in nt, then GetProcessTimes can work
		static DWORD last_tickcount,last_time;
		FILETIME t1,t2,t3,t4;
		LONGLONG i;
		DWORD k;
		if(GetProcessTimes(GetCurrentProcess(),&t1,&t2,&t3,&t4)){
			i=*(LONGLONG *)&t4;
			k=(DWORD)(i/10000);
			i=*(LONGLONG *)&t3;
			k+=(DWORD)(i/10000);
			if(!last_tickcount){
				last_tickcount=GetTickCount();
				last_time=k;
			} else if(GetTickCount()!=last_tickcount){
				load=((k-last_time)*100)/(GetTickCount()-last_tickcount);
			}
			last_tickcount=GetTickCount();
			last_time=k;
		}
	}
	for(i=59;i>0;i--)loads[i]=loads[i-1];
	loads[0]=load;
	load1=0;
	for(i=0;i<60;i++)load1+=loads[i];
	load1=(load1*100)/60;
	if((count%60)==0){
		for(i=14;i>0;i--)loads_s[i]=loads_s[i-1];
		loads_s[0]=load1;
		load10=0;
		for(i=0;i<10;i++)load10+=loads_s[i];
		load10=load10/10;
		load15=0;
		for(i=0;i<15;i++)load15+=loads_s[i];
		load15=load15/15;
	}
}

void f_get_rusage(long * p)
{
	FILETIME t1,t2,t3,t4;
	LONGLONG  i;
	if(GetProcessTimes(GetCurrentProcess(),&t1,&t2,&t3,&t4)){
		i=*(LONGLONG *)&t4;
		p[0]=(long)(i/10000);
		i=*(LONGLONG *)&t3;
		p[1]=(long)(i/10000);
	} else {
		p[0]=GetTickCount();
		p[1]=0;
	}
	p[2]=load1;
	p[3]=load10;
	p[4]=load15;
#pragma warning(push)
#pragma warning(disable:4996)
	p[5]=GetVersion();
#pragma warning(pop)
}


static HKEY OpenIniSection(LPCTSTR lpAppName)
{
	char buf[512];
	HKEY hk;
	sprintf(buf,"SOFTWARE\\anders\\MudOS\\%s\\%s",svr_short,lpAppName);
	if(RegOpenKey(HKEY_LOCAL_MACHINE,buf,&hk)!=ERROR_SUCCESS){
		RegCreateKey(HKEY_LOCAL_MACHINE,"SOFTWARE\\anders",&hk);
		strcpy(buf,"mailto: xxx@163.com");
		RegSetValue(hk,NULL,REG_SZ,buf, (DWORD)strlen(buf));
		RegCloseKey(hk);
		RegCreateKey(HKEY_LOCAL_MACHINE,"SOFTWARE\\anders\\MudOS",&hk);
		RegCloseKey(hk);
		sprintf(buf,"SOFTWARE\\anders\\MudOS\\%s\\%s",svr_short,lpAppName);
		RegCreateKey(HKEY_LOCAL_MACHINE,buf,&hk);
		RegCloseKey(hk);
		sprintf(buf,"SOFTWARE\\anders\\MudOS\\%s\\%s",svr_short,lpAppName);
		RegCreateKey(HKEY_LOCAL_MACHINE,buf,&hk);
	}
	return hk;
}

DWORD GetIniString(LPCTSTR lpAppName,LPCTSTR lpKeyName,LPCTSTR lpDefault,LPTSTR lpReturnedString,DWORD nSize)
{
	HKEY hk;
	hk=OpenIniSection(lpAppName);
	if(RegQueryValueEx(hk,lpKeyName,NULL,NULL,lpReturnedString,&nSize)!=ERROR_SUCCESS){
		strcpy(lpReturnedString,lpDefault);
	}
	RegCloseKey(hk);
	return (DWORD)strlen(lpReturnedString);
}

int GetIniInt(LPCTSTR lpAppName,LPCTSTR lpKeyName,int iDefault)
{
	HKEY hk;
	DWORD cb;
	hk=OpenIniSection(lpAppName);
	cb=sizeof(iDefault);
	RegQueryValueEx(hk,lpKeyName,NULL,NULL,(BYTE *)&iDefault,&cb);
	RegCloseKey(hk);
	return iDefault;
}

BOOL SetIniString(LPCTSTR lpAppName,LPCTSTR lpKeyName,LPCTSTR lpString)
{
	HKEY hk;
	LONG ret;
	hk=OpenIniSection(lpAppName);
	ret=RegSetValueEx(hk,lpKeyName,0,REG_SZ,lpString, (DWORD)strlen(lpString));
	RegCloseKey(hk);
	return ret==ERROR_SUCCESS;
}

BOOL SetIniInt(LPCTSTR lpAppName,LPCTSTR lpKeyName,int abc)
{
	HKEY hk;
	LONG ret;
	hk=OpenIniSection(lpAppName);
	ret=RegSetValueEx(hk,lpKeyName,0,REG_DWORD,(BYTE *)&abc,sizeof(abc));
	RegCloseKey(hk);
	return ret==ERROR_SUCCESS;
}



#ifdef _PROFILE
void mudos_exit(int i)
{
	ExitThread(i);
}
#endif


#ifndef _PROFILE
int start_new(void)
{
	char buf[256];
	static int start_count=0;
    PROCESS_INFORMATION pinfo;
    STARTUPINFO sinfo;

	if(start_count)return 0;
	start_count++;

    if(!in_restart)return 0;
    
    GetModuleFileName(NULL,buf,256);
    strcat(buf,"  ");
    if(isservice)strcat(buf,"service");
    
    sinfo.cb=sizeof(sinfo);
    sinfo.lpReserved=NULL;
    sinfo.lpDesktop=NULL;
    sinfo.lpTitle=NULL;
    sinfo.dwFlags=0;
    sinfo.cbReserved2=0;
    sinfo.lpReserved2=NULL;
    
    if(!CreateProcess(NULL,buf,NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&sinfo,&pinfo))return -1;
    CloseHandle(pinfo.hThread);
    CloseHandle(pinfo.hProcess);
    return 0;
}


int WINAPI runservice()
{
    char *p[5];
    HFILE hf;
    long size;
	char buf[256];
	time_t tt;
    int i;
    
    p[0]="mudos";
    p[1]=config_file;
    p[2]=NULL;
    
    hf=_lopen(log_file,0);
    if(hf>0){
        size=_llseek(hf,0,FILE_END);
        _lclose(hf);
        if(size>1000000)DeleteFile(log_file);
    }
    hf=_lopen(log_file,1);
	if(hf<0){
		hf=_lcreat(log_file,0);
	}
    size=_llseek(hf,0,2);
	time(&tt);
    sprintf(buf,"\n<---%s startup on %s at %s\n",SVR_LONG,ARCH,ctime(&tt));
    _lwrite(hf,buf, (DWORD)strlen(buf));
    _lclose(hf);

	while(!init_addr_server_ok)Sleep(10);

    mudos_runmudos(2,p);

    GetModuleFileName(NULL,buf,256);
    i=(int)strlen(buf);
    while((i>0)&&(buf[i]!='\\'))i--;
    buf[i]=0;


    hf=_lopen(log_file,1);
    _llseek(hf,0,2);
	time(&tt);
    sprintf(buf,"\n<---%s shutdown at %s\n\n\n",SVR_LONG,ctime(&tt));
    _lwrite(hf,buf,(UINT)strlen(buf));
    _lclose(hf);

    if(!mudos_initmud_ok()){
		char estr[1024];
        int ret;
	    hf=_lopen(log_file,0);
		_llseek(hf,size,0);
		ret=_lread(hf,estr,sizeof(estr)-1);
        estr[ret]=0;
        MessageBox(NULL,estr,loadstring(IDS_MAIN_ERROR,NULL),MB_OK);
		in_restart=0;
		PostMessage(hwnd,WM_QUIT,0,0);
    } else {
        start_new();
    }
    Shell_NotifyIcon(NIM_DELETE,&ni);
	query_restart=1;
    return 0;
}


int WINAPI runservice2()
{
    char *p[5];
    char buf[50];
    
    p[0]="mudos";
    p[2]=NULL;
    
    sprintf(buf,"%d",GetIniInt("init","addr_port",0));
    p[1]=buf;
    
    if(p[1][0]!='0'){
		addr_main(2,p);
		query_restart=1;
	}
	init_addr_server_ok=1;
    return 0;
}

int PumpMessage(void)
{
	MSG msg;
	while(PeekMessage(&msg,0,0,0,PM_REMOVE)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
	}
	return 0;
}

BOOL CALLBACK DialogProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam);

long WINAPI WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	static DWORD start_time;
	static int in_showabout=0;
    HMENU hm;
    POINT p;
    
    switch(msg){
    case WM_CLOSE:
		if(wParam==123)in_restart=0;
        PostQuitMessage(0);
        return 0;
		
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
		
    case WM_TIMER:
		start_time++;
		if(start_time%100==0){
			Shell_NotifyIcon(NIM_ADD,&ni);
		}
		
		mudos_heartbeat();
		UpdateLoad();
		
		if(query_restart){
			PostQuitMessage(0);
			return 0;
		}
		return 0;
		
    case WM_COMMAND:
		if(wParam==1){
			in_restart=1;
			PostQuitMessage(0);
			return 0;
		}
		if(wParam==2){
			in_restart=0;
			PostQuitMessage(0);
		}
		if(wParam==3){
			DialogBox(hinstance,(LPCTSTR)IDD_SETUP_DLG,NULL,(DLGPROC)DialogProc);
		}
		if((wParam==555)&&(!in_showabout)){
			in_showabout=1;
			MessageBox(NULL,loadstring(IDS_MAIN_ABOUT,NULL),SVR_LONG,MB_OK);
			in_showabout=0;
		}
        return 0;
		
    case WM_USER+10:
        if((LOWORD(lParam)==NM_LBUTTONDOWN)||(LOWORD(lParam)==NM_RBUTTONUP)){
			SetFocus(hwnd);
            GetCursorPos(&p);
			hm=CreatePopupMenu();
			
			AppendMenu(hm,MF_STRING,555,loadstring(IDS_MAIN_MENU_ABOUT,NULL));

			AppendMenu(hm,MF_SEPARATOR,0,NULL);

			AppendMenu(hm,MF_STRING,3,loadstring(IDS_MAIN_MENU_SETUP,NULL));
			AppendMenu(hm,MF_STRING,1,loadstring(IDS_MAIN_MENU_RESTART,NULL));
			AppendMenu(hm,MF_STRING,2,loadstring(IDS_MAIN_MENU_SHUTDOWN,NULL));

			TrackPopupMenu(hm,TPM_LEFTALIGN,p.x,p.y,0,hwnd,NULL);
			DestroyMenu(hm);
            return 0;
        }
        return 0;
    }
    return (long)DefWindowProc(hwnd,msg,wParam,lParam);
}


typedef DWORD (WINAPI *RegisterServiceProcess)(DWORD pid,DWORD inst);

int ServiceStart(LPCTSTR cmd)
{
    UINT htimer;
    WNDCLASS wc;
    MSG msg;
    int isshutdown;
    DWORD p;
    int i;
    HINSTANCE hdll;
    RegisterServiceProcess rsp;
    
    isshutdown=0;

  
    if(!lstrcmpi(cmd,"shutdown"))isshutdown=1;
    wc.lpszClassName = SVR_LONG;
    wc.style         = 0;
    wc.lpfnWndProc   = (WNDPROC)WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hinstance;
    wc.hIcon         = LoadIcon(hinstance,(LPCTSTR)IDI_SVR);
    wc.hCursor       = LoadCursor(NULL,IDC_ARROW);
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wc.lpszMenuName  = NULL;
    
    i=0;
    do{
        hwnd=FindWindow(wc.lpszClassName,NULL);
		if(isshutdown){
			if(!hwnd){
				MessageBox(NULL,"server not found.\n","mudos",MB_OK);
				return 0;
			}
			PostMessage(hwnd,WM_CLOSE,123,0);
			return 0;
		}
        if(!hwnd)break;
        i++;
        PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
        Sleep(200);
    }while(i<50);
    if(i==50)return 0;
    
    
    i=GetIniInt("init","heartbeat",0);
    if(i>=100)mudos_set_heartbeat(i*1000);
    
    p=0;
    CloseHandle(CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)&runservice,0,0,&p));
    CloseHandle(CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)&runservice2,0,0,&p));
    if(p==0)return 0;
    
    
    if (!RegisterClass(&wc)){
        MessageBox(NULL,"Register class","Error",MB_OK);
        return 0;
    }
    
    hwnd= CreateWindow(wc.lpszClassName, "Server",
        WS_OVERLAPPEDWINDOW , CW_USEDEFAULT, 0,
        CW_USEDEFAULT, 0, NULL, NULL,
        hinstance, NULL );
    
    ShowWindow(hwnd,SW_HIDE);
    
    htimer=(UINT)SetTimer(hwnd,0,mudos_get_heartbeat() / 1000,NULL);
    
    ni.cbSize=sizeof(ni);
    ni.hWnd=hwnd;
    ni.uID=MSGBASE;
    ni.uFlags=7;
    ni.uCallbackMessage=WM_USER+10;
    ni.hIcon=wc.hIcon;
    strcpy(ni.szTip,SVR_LONG);
    
    hdll=LoadLibrary("kernel32");
    rsp=(RegisterServiceProcess)GetProcAddress(hdll,"RegisterServiceProcess");
    if(rsp)rsp(GetCurrentProcessId(),1);
    
    FreeLibrary(hdll);
    
    Shell_NotifyIcon(NIM_ADD,&ni);
    
    while (GetMessage(&msg, (HWND) NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    Shell_NotifyIcon(NIM_DELETE,&ni);
    start_new();
    return 0;
}


SERVICE_STATUS          ssStatus;
SERVICE_STATUS_HANDLE   sshStatusHandle;
DWORD dwErr=0;

BOOL ReportStatusToSCMgr(DWORD dwCurrentState,
			 DWORD dwWin32ExitCode,
			 DWORD dwWaitHint)
{
    static DWORD dwCheckPoint = 1;
    
    
    if (dwCurrentState == SERVICE_START_PENDING)
        ssStatus.dwControlsAccepted = 0;
    else
        ssStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    
    ssStatus.dwCurrentState = dwCurrentState;
    ssStatus.dwWin32ExitCode = dwWin32ExitCode;
    ssStatus.dwWaitHint = dwWaitHint;
    
    if ( ( dwCurrentState == SERVICE_RUNNING ) ||
        ( dwCurrentState == SERVICE_STOPPED ) )
        ssStatus.dwCheckPoint = 0;
    else
        ssStatus.dwCheckPoint = dwCheckPoint++;
    
    return SetServiceStatus( sshStatusHandle, &ssStatus);
    
}



VOID WINAPI service_ctrl(DWORD dwCtrlCode)
{
    // Handle the requested control code.
    //
    switch(dwCtrlCode)
    {
	// Stop the service.
	//
    case SERVICE_CONTROL_STOP:
        ssStatus.dwCurrentState = SERVICE_STOP_PENDING;
        ReportStatusToSCMgr(
            SERVICE_STOP_PENDING,       // service state
            NO_ERROR,              // exit code
            0);                    // wait hint
	
        PostMessage(hwnd,WM_CLOSE,123,0);
        break;
	
	// Update the service status.
	//
    case SERVICE_CONTROL_INTERROGATE:
        break;
	
	// invalid control code
	//
    default:
        break;
	
    }
    ReportStatusToSCMgr(ssStatus.dwCurrentState, NO_ERROR, 0);
    
}



void WINAPI service_main(DWORD t1,LPTSTR *t2)
{
    isservice=1;
    sshStatusHandle = RegisterServiceCtrlHandler(SVR_SHORT, service_ctrl);
    
    if (!sshStatusHandle)
        goto cleanup;
    
    ssStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    ssStatus.dwServiceSpecificExitCode = 0;
    if (!ReportStatusToSCMgr(
		SERVICE_RUNNING,       // service state
		NO_ERROR,              // exit code
		0))                    // wait hint
        goto cleanup;
    ServiceStart("");
    
cleanup:
    if (sshStatusHandle)
        ReportStatusToSCMgr(
		SERVICE_STOPPED,
		dwErr,
		0);
    return;
}



int ErrorMessage(char *str)
{
    MessageBox(NULL,str,"mudos error",MB_OK);
    return 0;
}

long GetLine(HFILE hf,char *str)
{
    int len,i,j;
    char s[260];
    
    len=_lread(hf,&s,256);
    if(len==0)return -1;
    for(i=0;i<len;i++)if(s[i]==0x0a)break;
    s[i]=0;j=1;
    while(i-j>=0)if(s[i-j]==0x0d)s[i-j++]=0;else break;
    lstrcpy(str,s);
    return _llseek(hf,i-len+1,1);
}




int Win95Main(LPCTSTR cmd)
{
	if(cmd[0]==0){
		return ServiceStart(cmd);
	} 
    MessageBox(NULL,loadstring(IDS_MAIN_USAGE,NULL),"MUDOS",MB_OK);
	return 0;
}

int WinNtMain(LPCTSTR cmd)
{
    SC_HANDLE   schService;
    SC_HANDLE   schSCManager;
	
    int i;
    
    
    if(cmd[0]==0){ // try to start service
        SERVICE_TABLE_ENTRY dispatchTable[] =
        {
            { SVR_SHORT, (LPSERVICE_MAIN_FUNCTION)service_main },
            { NULL, NULL }
        };
        if(StartServiceCtrlDispatcher(dispatchTable)==0){
			if(GetLastError()!=ERROR_FAILED_SERVICE_CONTROLLER_CONNECT){
				return 0;
			} else {
				return ServiceStart("");
			}
		} else 
			return 0;
    }
    
    if(!lstrcmpi(cmd,"start")){
		return ServiceStart("");
    }
    if(!lstrcmpi(cmd,"service")){
		i=100;
		do{
			schSCManager = OpenSCManager(
				NULL,                   // machine (NULL == local)
				NULL,                   // database (NULL == default)
				SC_MANAGER_ALL_ACCESS   // access required
				);
			if ( !schSCManager ){
				ErrorMessage("SCManager not found");
				return 0;
			}
			schService = OpenService(schSCManager,SVR_SHORT, SERVICE_START);
			i--;
			if(!schService){
				CloseServiceHandle(schSCManager);
				PumpMessage();
				Sleep(10);
			} else {
				i=-1;
			}
		} while(i>0);
        if(!schService){
			CloseServiceHandle(schService);
			CloseServiceHandle(schSCManager);
			return ServiceStart("");
        }
		StartService(schService,0,NULL);
        CloseServiceHandle(schService);
        CloseServiceHandle(schSCManager);
        return 0;
    }
    
    MessageBox(NULL,loadstring(IDS_MAIN_USAGE,NULL),"MUDOS",MB_OK);
	return 0;
}


BOOL ReadConfig()
{
	int i;
	HFILE hf;
	char buf[256];
	char str[256];

	GetIniString("init","config","",config_file,128);
    hf=_lopen(config_file,0);
    if(hf<0){
		sprintf(buf,loadstring(IDS_MAIN_NO_CFG,NULL),config_file);
		MessageBox(NULL,buf,loadstring(IDS_MAIN_ERROR,NULL),MB_OK);
		return 0;
    }
    while(GetLine(hf,buf)>0){
		if(buf[0]=='#')continue;
		str[0]=0;
		sscanf(buf,"%s",str);
		if(!lstrcmpi(str,"name")){
			int j;
			i=0;
			while(buf[i]&&(buf[i]!=':'))i++;
			if(buf[i]==':')i++;
			while((buf[i]==' ')||(buf[i]=='\t'))i++;
			j=(int)strlen(buf)-1;
			while((j>0)&&((buf[j]==' ')||(buf[j]=='\t'))){
				buf[j]=0;
				j--;
			}
			sprintf(svr_long,"%s: GameServer v1.0 (by Anders," __DATE__ ")",&buf[i]);
			_lclose(hf);
			hf=-1;
		}
    }
    if(hf>0){
		_lclose(hf);
		sprintf(buf,loadstring(IDS_MAIN_BAD_CFG,NULL),config_file);
		MessageBox(NULL,buf,loadstring(IDS_MAIN_ERROR,NULL),MB_OK);
		return 0;
    }
	return 1;
}

BOOL HaveService()
{
	if(!is95){
		SC_HANDLE   schService;
		SC_HANDLE   schSCManager;
		schSCManager = OpenSCManager(
			NULL,                   // machine (NULL == local)
			NULL,                   // database (NULL == default)
			SC_MANAGER_ALL_ACCESS   // access required
			);
		if ( !schSCManager ){
			return FALSE;
		}
		schService = OpenService(schSCManager,SVR_SHORT, SERVICE_ALL_ACCESS);
		if(!schService){
			CloseServiceHandle(schSCManager);
			return FALSE;
		}
		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		return TRUE;
	} else {
		HKEY hk;
		
		RegOpenKey(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServices",&hk);
		if(RegQueryValueEx(hk,svr_short,NULL,NULL,NULL,NULL)!=ERROR_SUCCESS){
			RegCloseKey(hk);
			return FALSE;
		} else {
			RegCloseKey(hk);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL SetupService(BOOL install)
{
    SC_HANDLE   schService;
    SC_HANDLE   schSCManager;
    char Sidbuf[64];
    char Domain[64];
    char Aclbuf[256];
    char username[64];
	
    SECURITY_DESCRIPTOR  security;
    DWORD cbSid,cbDomain;
    SID_NAME_USE snu;
    
    int i;
	char str[256];
	
	if(!is95){
		if(install){
			if(GetModuleFileName( NULL, str, 256 ) == 0 ){
				ErrorMessage("can not Get Exefilename");
				return 0;
			}
			
			schSCManager = OpenSCManager(
				NULL,                   // machine (NULL == local)
				NULL,                   // database (NULL == default)
				SC_MANAGER_ALL_ACCESS   // access required
				);
			if ( !schSCManager ){
				ErrorMessage("SCManager not found");
				return 0;
			}
			
			schService = CreateService(
				schSCManager,               // SCManager database
				SVR_SHORT,           // name of service
				SVR_LONG,      // name to display
				SERVICE_ALL_ACCESS,         // desired access
				SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS , // service type
				SERVICE_AUTO_START,         // start type
				SERVICE_ERROR_NORMAL,       // error control type
				str,                        // service's binary
				NULL,                       // no load ordering group
				NULL,                       // no tag identifier
				"Tcpip\0\0",                // dependencies
				NULL,                       // LocalSystem account
				NULL);                      // no password
			if(!schService){
				CloseServiceHandle(schSCManager);
				ErrorMessage("CreateService failed");
				return 0;
			}
			
			
			if(!InitializeAcl((PACL)Aclbuf,sizeof(Aclbuf),ACL_REVISION)){
				MessageBox(NULL,"InitalizeAcl","error",MB_OK);
				CloseServiceHandle(schService);
				CloseServiceHandle(schSCManager);
				return 0;
			}
			cbSid=sizeof(Sidbuf);
			cbDomain=sizeof(Domain);
			if(!LookupAccountName(NULL,"users",(PSID)Sidbuf,&cbSid,Domain,&cbDomain,&snu)){
				MessageBox(NULL,"lookupaccountname users","error",MB_OK);
				CloseServiceHandle(schService);
				CloseServiceHandle(schSCManager);
				return 0;
			}
			if(!AddAccessAllowedAce((PACL)Aclbuf,ACL_REVISION,SERVICE_ALL_ACCESS,(PSID)Sidbuf)){
				MessageBox(NULL,"AddAccessAllowedAce","error",MB_OK);
				CloseServiceHandle(schService);
				CloseServiceHandle(schSCManager);
				return 0;
			}
			cbSid=sizeof(username);
			GetUserName(username,&cbSid);
			cbSid=sizeof(Sidbuf);
			cbDomain=sizeof(Domain);
			if(!LookupAccountName(NULL,username,(PSID)Sidbuf,&cbSid,Domain,&cbDomain,&snu)){
				MessageBox(NULL,"lookupaccountname","error",MB_OK);
				CloseServiceHandle(schService);
				CloseServiceHandle(schSCManager);
				return 0;
			}
			
			if(!AddAccessAllowedAce((PACL)Aclbuf,ACL_REVISION,SERVICE_ALL_ACCESS,(PSID)Sidbuf)){
				MessageBox(NULL,"AddAccessAllowedAce","error",MB_OK);
				CloseServiceHandle(schService);
				CloseServiceHandle(schSCManager);
				return 0;
			}
			
			if(!InitializeSecurityDescriptor(&security,SECURITY_DESCRIPTOR_REVISION)){
				MessageBox(NULL,"InitializeSecurity","error",MB_OK);
				CloseServiceHandle(schService);
				CloseServiceHandle(schSCManager);
				return 0;
			}
			
			if(!SetSecurityDescriptorDacl(&security,TRUE,(PACL)Aclbuf,FALSE)){
				MessageBox(NULL,"SetSecurity","error",MB_OK);
				CloseServiceHandle(schService);
				CloseServiceHandle(schSCManager);
				return 0;
			}
			
			SetSecurityDescriptorSacl(&security,TRUE,NULL,FALSE);
			
			if(!SetServiceObjectSecurity(schService,DACL_SECURITY_INFORMATION,&security)){
				MessageBox(NULL,"SetService","error",MB_OK);
				CloseServiceHandle(schService);
				CloseServiceHandle(schSCManager);
				return 0;
			}
			
			CloseServiceHandle(schService);
			CloseServiceHandle(schSCManager);
			MessageBox(NULL,loadstring(IDS_MAIN_SUCCESS,str),loadstring(IDS_MAIN_REG_SERVICE,NULL),MB_OK);
			return 1;
		} else {
			
			schSCManager = OpenSCManager(
				NULL,                   // machine (NULL == local)
				NULL,                   // database (NULL == default)
				SC_MANAGER_ALL_ACCESS   // access required
				);
			if(!schSCManager){
				ErrorMessage("SCManager not found");
				return 0;
			}
			schService = OpenService(schSCManager,SVR_SHORT, SERVICE_ALL_ACCESS);
			if(!schService){
				CloseServiceHandle(schSCManager);
				ErrorMessage("Service not installed");
				return 0;
			}
			i=0;
			ControlService( schService, SERVICE_CONTROL_STOP, &ssStatus);
			while(QueryServiceStatus(schService, &ssStatus)){
				if(ssStatus.dwCurrentState != SERVICE_STOP_PENDING)break;
				Sleep(1000);
				if(i++>5)break;
			}
			if(ssStatus.dwCurrentState != SERVICE_STOPPED){
				CloseServiceHandle(schSCManager);
				CloseServiceHandle(schService);
				ErrorMessage("Can not shutdown Service");
				return 0;
			}
			if(DeleteService(schService)){
				MessageBox(NULL,loadstring(IDS_MAIN_SUCCESS,str),loadstring(IDS_MAIN_UNREG_SERVICE,NULL),MB_OK);
				CloseServiceHandle(schService);
				CloseServiceHandle(schSCManager);
				return 1;
			} else {
				MessageBox(NULL,loadstring(IDS_MAIN_ERROR,str),loadstring(IDS_MAIN_UNREG_SERVICE,NULL),MB_OK);
				CloseServiceHandle(schService);
				CloseServiceHandle(schSCManager);
				return 0;
			}
		}
	} else {  // 95
		if(install){
			HKEY hk;
			char str[256];
			DWORD ret;
			
			GetModuleFileName( NULL, str, 256 );
			RegOpenKey(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServices",&hk);
			ret=RegSetValueEx(hk,svr_short,0,REG_SZ,(BYTE *)str,(DWORD)strlen(str));
			RegCloseKey(hk);
			
			if(ret==ERROR_SUCCESS){
				MessageBox(NULL,loadstring(IDS_MAIN_SUCCESS,str),loadstring(IDS_MAIN_REG_SERVICE,NULL),MB_OK);
				return 1;
			} else {
				MessageBox(NULL,loadstring(IDS_MAIN_ERROR,str),loadstring(IDS_MAIN_REG_SERVICE,NULL),MB_OK);
				return 0;
			}
		} else {
			HKEY hk;
			DWORD ret;
			
			RegOpenKey(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServices",&hk);
			ret=RegDeleteValue(hk,svr_short);
			RegCloseKey(hk);
			
			if(ret==ERROR_SUCCESS){
				MessageBox(NULL,loadstring(IDS_MAIN_SUCCESS,str),loadstring(IDS_MAIN_UNREG_SERVICE,NULL),MB_OK);
				return 1;
			} else {
				MessageBox(NULL,loadstring(IDS_MAIN_ERROR,str),loadstring(IDS_MAIN_UNREG_SERVICE,NULL),MB_OK);
				return 0;
			}
		}
	}
	return FALSE;
}

BOOL CALLBACK DialogProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	static int firstshow=1;
	RECT r1,r2;
	char buf[256];
	switch(uMsg){
	case WM_INITDIALOG:
		if(GetIniString("init","config","",buf,sizeof(buf))){
			EnableWindow(GetDlgItem(hDlg,IDOK),TRUE);
		} else {
			EnableWindow(GetDlgItem(hDlg,IDOK),FALSE);
		}
		SetDlgItemText(hDlg,IDC_CFG_PATH,buf);
		SetDlgItemInt(hDlg,IDC_ADDR_PORT,GetIniInt("init","addr_port",0),FALSE);
		if(GetIniInt("init","heartbeat",0)==0){
			SetIniInt("init","heartbeat",mudos_get_heartbeat() / 1000);
		}
		SetDlgItemInt(hDlg,IDC_HEART_BEAT,GetIniInt("init","heartbeat",0),0);
		return 1;

	case WM_SHOWWINDOW:
		if(firstshow){
			GetWindowRect(GetDesktopWindow(),&r1);
			GetWindowRect(hDlg,&r2);
			r2.right-=r2.left; r2.left=0;
			r2.bottom-=r2.top; r2.top=0;
			MoveWindow(hDlg,
				r1.right/2-r2.right/2,
				r1.bottom/2-r2.bottom/2,
				r2.right,
				r2.bottom,
				FALSE);
			firstshow=0;
		}
		return 1;

	case WM_COMMAND:
		if(LOWORD(wParam)==IDCANCEL){
			PostMessage(hDlg,WM_CLOSE,0,0);
			return 1;
		}
		if(LOWORD(wParam)==IDC_BROWSER){
			OPENFILENAME of;
			memset(&of,0,sizeof(of));
			of.lStructSize=sizeof(of);
			of.hwndOwner=hDlg;
			of.hInstance=hinstance;
			GetIniString("init","config","",buf,sizeof(buf));
			of.lpstrFile=buf;
			of.nMaxFile=sizeof(buf);
			of.Flags=OFN_ENABLESIZING|OFN_EXPLORER|OFN_FILEMUSTEXIST;
			if(GetOpenFileName(&of)){
				SetDlgItemText(hDlg,IDC_CFG_PATH,of.lpstrFile);
			}
			return 1;
		}
		if(HIWORD(wParam)==EN_CHANGE){
			if(LOWORD(wParam)==IDC_CFG_PATH){
				if(GetDlgItemText(hDlg,IDC_CFG_PATH,buf,sizeof(buf))){
					EnableWindow(GetDlgItem(hDlg,IDOK),TRUE);
				} else {
					EnableWindow(GetDlgItem(hDlg,IDOK),FALSE);
				}
			}
			return 1;
		}
		if(LOWORD(wParam)==IDREG){
			buf[0]=0;
			GetDlgItemText(hDlg,IDC_CFG_PATH,buf,sizeof(buf));
			if(buf[0])SetIniString("init","config",buf);
			if(!ReadConfig())return 1;
			SetupService(TRUE);
		}
		if(LOWORD(wParam)==IDUNREG){
			SetupService(FALSE);
		}
		if(LOWORD(wParam)==IDOK){
			GetDlgItemText(hDlg,IDC_CFG_PATH,buf,sizeof(buf));
			SetIniString("init","config",buf);
			GetDlgItemText(hDlg,IDC_ADDR_PORT,buf,sizeof(buf));
			SetIniInt("init","addr_port",atoi(buf));
			GetDlgItemText(hDlg,IDC_HEART_BEAT,buf,sizeof(buf));
			SetIniInt("init","heartbeat",atoi(buf));
			EndDialog(hDlg,1234);
			return 1;
		}
		return 1;

	case WM_CLOSE:
		EndDialog(hDlg,0);
		return 1;
	}
	return 0;
}

extern int InitCom(HINSTANCE hInstance);
extern int ExitCom();
extern HRESULT _stdcall DllRegisterServer(void);
extern HRESULT _stdcall DllUnregisterServer(void);


int WINAPI WinMain(HINSTANCE hinst,HINSTANCE t1,LPSTR cmd,int t3)
{
	int i;
	char buf[256];
	DWORD p;
    WSADATA WSAData;


    hinstance=hinst;

    GetModuleFileName(NULL,buf,sizeof(buf));
	if(buf[1]!=':')return 0;
	for(i=3;buf[i]&&(i<=128);i++){
		svr_short[i-3]=buf[i];
		if((buf[i]>='0')&&(buf[i]<='9'))continue;
		if((buf[i]>='a')&&(buf[i]<='z'))continue;
		if((buf[i]>='A')&&(buf[i]<='Z'))continue;
		svr_short[i-3]='_';
	}
	svr_short[i-3]=0;

	strcpy(log_file,buf);
	i=(int)strlen(log_file);
	while((log_file[i]!='.')&&(i>0))i--;
	strcpy(&log_file[i],".log");

#pragma warning(push)
#pragma warning(disable:4996)
    p=GetVersion();
#pragma warning(pop)
	if((p&0xff)<4){
		sprintf(buf,loadstring(IDS_MAIN_WIN_VERSION,NULL),p&0xff,(p&0xff00)>>8);
		MessageBox(NULL,buf,loadstring(IDS_MAIN_CANNOT_RUN,NULL),MB_OK);
		return 0;
	}
    is95=p&0x80000000;
    if(is95){
		if( ((p&0xff00)>>8) < 10)
			mudos_set_info("Microsoft Windows 95");
		else
			mudos_set_info("Microsoft Windows 98");
    } else
		mudos_set_info("Microsoft Windows NT");

    i=GetIniInt("init","runcount",0);
	if(i==0){
		sprintf(buf,loadstring(IDS_MAIN_FIRST_RUN,NULL),SVR_SHORT);
		MessageBox(NULL,loadstring(IDS_MAIN_ABOUT,NULL),buf,MB_OK);
	}
	if((i==0)||(!lstrcmpi(cmd,"setup"))){
		if(DialogBox(hinstance,(LPCTSTR)IDD_SETUP_DLG,NULL,(DLGPROC)DialogProc)!=1234)return 0;
	}
	i++;
	SetIniInt("init","runcount",i);

	if(!lstrcmpi(cmd,"setup")){
		if(DialogBox(hinstance,(LPCTSTR)IDD_SETUP_DLG,NULL, (DLGPROC)DialogProc)!=1234)return 0;
	}
	
    if(WSAStartup(MAKEWORD(1,1), &WSAData)){
		MessageBox(NULL,loadstring(IDS_MAIN_NO_TCPIP,buf),loadstring(IDS_MAIN_CANNOT_RUN,NULL),MB_OK);
		return 0;
    }

	while(!ReadConfig()){
		if(DialogBox(hinstance,(LPCTSTR)IDD_SETUP_DLG,NULL, (DLGPROC)DialogProc)!=1234)return 0;
	}
    

#if 0
	InitCom(hinstance);
	if(!lstrcmpi(cmd,"register")){
		if(DllRegisterServer()==S_OK){
			MessageBox(NULL,"登记COM对象成功","MUDOS",MB_OK);
		} else {
			MessageBox(NULL,"登记COM对象失败","MUDOS",MB_OK);
		}
	} else	if(!lstrcmpi(cmd,"unregister")){
		if(DllUnregisterServer()==S_OK){
			MessageBox(NULL,"取消COM对象成功","MUDOS",MB_OK);
		} else {
			MessageBox(NULL,"取消COM对象失败","MUDOS",MB_OK);
		}
	} else
#endif
	if (is95) {
		Win95Main(cmd);
	} else {
		WinNtMain(cmd);
	}
#if 0
	ExitCom();
#endif
	return 0;
}
#endif

#ifdef _PROFILE
void time_thread(void *p)
{
	while(1){
		Sleep(300);
		mudos_heartbeat();
	}
}

int p_main (int argc, char ** argv);
int main(int argc,char ** argv)
{
    DWORD p;
	int i;
    char Aclbuf[256];
    WSADATA WSAData;

    if(WSAStartup(MAKEWORD(1,1), &WSAData)){
		MessageBox(NULL,"WSAStartup error","TCP/IP error",MB_OK);
		return 0;
    }
	_beginthread(time_thread,0,0);

    GetModuleFileName(NULL,Aclbuf,256);
    i=strlen(Aclbuf);
    while((i>0)&&(Aclbuf[i]!='\\'))i--;
    Aclbuf[i]=0;


#pragma warning(push)
#pragma warning(disable:4996)
    p=GetVersion();
#pragma warning(pop)
    is95=p&0x80000000;
    if(is95)
		mudos_set_info("Microsoft Windows 95",mudos_ini);
    else 
		mudos_set_info("Microsoft Windows NT",mudos_ini);
	return p_main(argc,argv);
}
#endif
