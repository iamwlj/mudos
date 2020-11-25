#include "windows.h"
#define _VC_
#include "notify.h"
#include "stdio.h"
#include "direct.h"
#include "time.h"

static char *socket_err_str[]={
		"WSAEWOULDBLOCK",
		"WSAEINPROGRESS",
		"WSAEALREADY",
		"WSAENOTSOCK",
		"WSAEDESTADDRREQ",
		"WSAEMSGSIZE",
		"WSAEPROTOTYPE  ",
		"WSAENOPROTOOPT ",
		"WSAEPROTONOSUPPORT",
		"WSAESOCKTNOSUPPORT",
		"WSAEOPNOTSUPP  ",
		"WSAEPFNOSUPPORT",
		"WSAEAFNOSUPPORT",
		"WSAEADDRINUSE  ",
		"WSAEADDRNOTAVAIL  ",
		"WSAENETDOWN",
		"WSAENETUNREACH ",
		"WSAENETRESET   ",
		"WSAECONNABORTED",
		"WSAECONNRESET  ",
		"WSAENOBUFS ",
		"WSAEISCONN ",
		"WSAENOTCONN",
		"WSAESHUTDOWN   ",
		"WSAETOOMANYREFS",
		"WSAETIMEDOUT   ",
		"WSAECONNREFUSED",
		"WSAELOOP",
		"WSAENAMETOOLONG",
		"WSAEHOSTDOWN   ",
		"WSAEHOSTUNREACH",
		"WSAENOTEMPTY   ",
		"WSAEPROCLIM",
		"WSAEUSERS  ",
		"WSAEDQUOT  ",
		"WSAESTALE  ",
		"WSAEREMOTE ",
};

int debug_message(const char *,...);

void str_perror (char * s, char * what, char * file, long err)
{
    LPVOID lpMsgBuf;
	
    lpMsgBuf=NULL;
    if(!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,    err,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,    0,    NULL )){
		// try wsock32.dll
        HINSTANCE hinst;
		hinst=LoadLibrary("wsock32.dll");
		if(!hinst)hinst=LoadLibrary("ws2_32.dll");
		if(hinst){
			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE ,
				hinst,    err,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
				(LPTSTR) &lpMsgBuf,    0,    NULL );
		}
		if(!lpMsgBuf){
			static char buf[256];
			if((err>=WSAEWOULDBLOCK)&&(err<WSAEWOULDBLOCK+sizeof(socket_err_str)/sizeof(char *))){
				sprintf(buf,"%s",socket_err_str[err-WSAEWOULDBLOCK]);
			} else
				sprintf(buf,"unknown error %d",err);
			lpMsgBuf=buf;
		}
    }
    if (file)
		sprintf(s,"System Error: %s: %s: %s\n", what, file, (char *)lpMsgBuf);
    else
		sprintf(s,"System Error: %s: %s\n", what, (char*)lpMsgBuf);
    LocalFree( lpMsgBuf );
}

void debug_perror (char * what, char * file) 
{
	char str[256];
    str_perror(str,what,file,GetLastError());
	debug_message(str);
}
