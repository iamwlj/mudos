// testmud.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
SOCKET sockets[1024];
char   sockbuf[1024][256];

SOCKET ConnectSocket(char * host,char *port)
{
	SOCKADDR_IN sin;
	SOCKET cs;
	cs=socket(AF_INET,SOCK_STREAM,0);
	if(cs==INVALID_SOCKET)return 0;

	sin.sin_family=AF_INET;
	sin.sin_addr.s_addr=inet_addr(host);
	sin.sin_port=htons(atoi(port));
	if(connect(cs,(SOCKADDR *)&sin,sizeof(sin))){
		closesocket(cs);
		return 0;
	}
	return cs;
}

void DoLine(const char * line)
{
	printf("%s\n",line);
}

void DoReceive(SOCKET cs,char *pbuf)
{
	char buf[512];
	int  size,i,k;

	size=(BYTE)pbuf[0];
	memcpy(buf,&pbuf[1],size);

	i=recv(cs,&buf[size],sizeof(buf)-size,0);
	if(i<=0)return;
	size+=i;

	do {
		for(i=0;i<size;i++)if(buf[i]=='\n')break;
		if(i>=size){
			if(size>255)size=255;
			memcpy(&pbuf[1],buf,size);
			pbuf[0]=size;
			break;
		}
		buf[i]=0;
		DoLine(buf);

		for(k=0;k<size-i-1;k++)buf[k]=buf[k+i+1];
		size-=i+1;
	} while(1);
}

int main(int argc, char* argv[])
{
	WSADATA ws;
	int i,j,size,max;
	FD_SET fd;
	struct timeval tm;

	if(argc<3){
		printf("testmud connection_number host port\n");
		return 0;
	}

	WSAStartup(0x101,&ws);
	for(i=0;i<1024;i++){
		sockets[i]=0;
		sockbuf[i][0]=0;
	}

	max=atoi(argv[1]);
	if(max<=0)max=1;
	if(max>1024)max=1024;

	for(i=0;i<max;i++){
		sockets[i]=ConnectSocket(argv[2],argv[3]);
		if(!sockets[i]){
			printf("ConnectSocket %d failed.\n",i);
			return 0;
		}
	}
	printf("Connect %d connections ok.\n",max);
	while(1){
		tm.tv_sec=0;
		tm.tv_usec=0;
		for(i=0;i<max;i+=16){  // every time, we check 16 socket
			size=max-i;
			if(size>16)size=16;
			FD_ZERO(&fd);
			for(j=0;j<size;j++)FD_SET(sockets[i+j],&fd);
			if(select(0,&fd,NULL,NULL,&tm)>0){
				for(j=0;j<size;j++)if(FD_ISSET(sockets[i+j],&fd)){
					DoReceive(sockets[i+j],sockbuf[i+j]);
				}
			}
		}
	}
	for(i=0;i<1024;i++)closesocket(sockets[i]);
	WSACleanup();
	return 0;
}

