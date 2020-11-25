/********************************************************
*              FORMAT C Version 1.0                     *
*                                                       *
*             CopyRight(c) 1996-1997                    *
*                  Wang Wenjun                          *
*              j32,Tsinghua University                  *
*                 Beijing,China                         *
*********************************************************/





#define MSGBASE        0x200
#define NM_MOUSEMOVE   MSGBASE
#define NM_LBUTTONDOWN (MSGBASE+1)
#define NM_LBUTTONUP   (MSGBASE+2)
#define NM_LDBLCLICK   (MSGBASE+3)
#define NM_RBUTTONDOWN (MSGBASE+4)
#define NM_RBUTTONUP   (MSGBASE+5)
#define NM_RDBLCLICK   (MSGBASE+6)

#ifndef _VC_

#define NIM_ADD         0x00000000
#define NIM_MODIFY      0x00000001
#define NIM_DELETE      0x00000002


typedef struct _NOTIFYICONDATAA {
    DWORD cbSize;
    HWND hWnd;
    UINT uID;
    UINT uFlags;
    UINT uCallbackMessage;
    HICON hIcon;
    CHAR   szTip[64];
} NOTIFYICONDATAA, *PNOTIFYICONDATAA;

typedef NOTIFYICONDATAA NOTIFYICONDATA;
typedef PNOTIFYICONDATAA PNOTIFYICONDATA;

extern "C" BOOL WINAPI Shell_NotifyIconA(DWORD dwMessage, PNOTIFYICONDATAA lpData);

#define Shell_NotifyIcon  Shell_NotifyIconA

#endif

typedef BOOL (WINAPI * SHELL_NOTIFY)(DWORD dwMessage, PNOTIFYICONDATAA lpData);
