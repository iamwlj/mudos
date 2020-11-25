#include "std.h"
#include "windows.h"
#include "pdebug.h"

char i_ARCH[256];
int initmud_ok=0;
int fatal();


#define MUDOS_EXCEPTION 0xe0ff1234

typedef struct{
    char *buf;
    void *ip;
}ECB,*PECB;
ECB ecb;

HandleException(LPEXCEPTION_POINTERS lpExp)
{
    static char buf[256];
    int i;
    
    DWORD code=lpExp->ExceptionRecord->ExceptionCode;
    switch(code){
    case EXCEPTION_ACCESS_VIOLATION:
        strcpy(buf,"access violation");
        if(lpExp->ExceptionRecord->ExceptionInformation[0])strcat(buf," write at");
        else strcat(buf," read at");
        i=(int)strlen(buf);
        wsprintf(&buf[i]," %08X",lpExp->ExceptionRecord->ExceptionInformation[1]);
        break;
    case EXCEPTION_PRIV_INSTRUCTION:        strcpy(buf,"priv instruction");break;
    case EXCEPTION_NONCONTINUABLE_EXCEPTION:strcpy(buf,"can not continue");break;
    case EXCEPTION_FLT_DIVIDE_BY_ZERO:      strcpy(buf,"divide by zero");break;
    case EXCEPTION_BREAKPOINT:              strcpy(buf,"breakpoint");break;
    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:   strcpy(buf,"exceeded arry");break;
    case EXCEPTION_FLT_INVALID_OPERATION:   strcpy(buf,"invalid operation");break;
    case EXCEPTION_FLT_STACK_CHECK:         strcpy(buf,"stack overflow");break;
	case MUDOS_EXCEPTION:
		ecb.buf=NULL;
		ecb.ip=(void *)lpExp->ExceptionRecord->ExceptionInformation[0];
		return EXCEPTION_EXECUTE_HANDLER;
    default: strcpy(buf,"unknown");
    }
    ecb.buf=buf;
    ecb.ip=lpExp->ExceptionRecord->ExceptionAddress;
#ifndef _DEBUG
    return EXCEPTION_EXECUTE_HANDLER;
#else
    return EXCEPTION_CONTINUE_SEARCH;
#endif
}

#ifndef _PROFILE
void mudos_exit(int code)
{
	static DWORD ret;
	ret=code;
	RaiseException(MUDOS_EXCEPTION,0,1,(const ULONG_PTR *)&ret);
}
#endif

extern char log_file[];
int main(int argc,char **argv);
int  WINAPI mudos_runmudos(int argc,char **argv)
{
	FILE *rptr,*owptr,*wptr=NULL;
	int ret;

    owptr=freopen(log_file,"a",stdout);
	if(!owptr)return -1;
    wptr=freopen(log_file,"a",stderr);
    fseek(wptr,0,2);
	if(!wptr)return -1;
    rptr=freopen(log_file,"r",stdin);
    if(!rptr)return -1;

	ret=0;
    __try{
		CoInitialize(NULL);
		main(argc,argv);
    }
    __except(HandleException(GetExceptionInformation())){
		if(ecb.buf){
			fprintf(wptr,"error %s ,IP=%p trying to restart\n",
				ecb.buf,ecb.ip);
			ret=1;
		}
    }

	fflush(NULL);
	fclose(rptr);
	fclose(owptr);
	fclose(rptr);
	return ret;
}

int  WINAPI mudos_initmud_ok()
{
    return initmud_ok;
}

int  WINAPI mudos_fatal(char *msg)
{
    return fatal(msg);
}

int heartbeatinterval=1000000;
void WINAPI mudos_set_heartbeat(int h)
{
    heartbeatinterval=h;
}

int  WINAPI mudos_get_heartbeat()
{
    return heartbeatinterval;
}

static int dll_heart_beat_flag=0;

int  WINAPI mudos_heartbeat()
{
    return dll_heart_beat_flag++;
}

void WINAPI mudos_set_info(char *s1)
{
    strcpy(i_ARCH,s1);
}

