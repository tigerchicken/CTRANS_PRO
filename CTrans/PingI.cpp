// PingI.cpp: implementation of the CPingI class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "PingI.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define MIN_ICMP_PACKET_SIZE 8
#define MAX_ICMP_PACKET_SIZE 1024
CPingI::CPingI()
{	//icmp.dll
	sm_pIcmpSendEcho=NULL;
	sm_pIcmpCreateFile=NULL;
	sm_pIcmpCloseHandle=NULL;
	icmphandle=LoadLibrary("ICMP.DLL");
	//printf("could not load up theicmp.dll" );
	if(icmphandle==NULL){
		//printf("could not load up theicmp.dll" );
		return;
	}
	sm_pIcmpCreateFile=(lpIcmpCreateFile)GetProcAddress(icmphandle,"IcmpCreateFile");
	sm_pIcmpSendEcho=(lpIcmpSendEcho)GetProcAddress(icmphandle,"IcmpSendEcho");
	sm_pIcmpCloseHandle=(lpIcmpCloseHandle)GetProcAddress(icmphandle,"IcmpCloseHandle");
	
	if(sm_pIcmpCreateFile==NULL||sm_pIcmpSendEcho==NULL||sm_pIcmpCloseHandle==NULL)
	{
		OutputDebugString("could not find function in icmp.dll");
	}

}

CPingI::~CPingI()
{//unload dll
	if(icmphandle){
		FreeLibrary(icmphandle);
		icmphandle=NULL;
	}

}


//function ping()
int CPingI::Ping(UINT nRetries ,LPCSTR pstrHost,HWND hWnd)
{
	if(sm_pIcmpSendEcho==NULL)
	{
		return 0;
	}
	DWORD dwTimeout=1000;  //timeout time
	UCHAR nPacketSize=32;
	unsigned long addr =inet_addr(pstrHost);

	if(addr==INADDR_NONE)
	{
		hostent* hp=gethostbyname(pstrHost);
		if(hp)
		{
			memcpy(&addr,hp->h_addr,hp->h_length);

		}else
		{
			//could not resolve the host name
			return FALSE;
		}
	
	}

	//get icmp jubing
	HANDLE hIP=sm_pIcmpCreateFile();
	if(hIP==INVALID_HANDLE_VALUE)
	{
		return FALSE;

	}

	IP_OPTION_INFORMATION OptionInfo;
	ZeroMemory(&OptionInfo,sizeof(IP_OPTION_INFORMATION));
	OptionInfo.Ttl=128;
	// fill the data to send
	unsigned char pBuf[36];
	memset(pBuf,'E',nPacketSize);

	//do the actual ping
	int nReplySize=sizeof(ICMP_ECHO_REPLY)+max(MIN_ICMP_PACKET_SIZE,nPacketSize);
	unsigned char pReply[100];
	ICMP_ECHO_REPLY* pEchoReply =(ICMP_ECHO_REPLY*) pReply;
	//DWORD nRecvPackets = sm_pIcmpSendEcho(hIP,addr,pBuf,nPacketSize,&OptionInfo,pReply,nReplySize,dwTimeout);
	DWORD nRecvPackets = sm_pIcmpSendEcho(hIP,addr,pBuf,nPacketSize,&OptionInfo,nReplySize,dwTimeout);
	BOOL bSuccess=(nRecvPackets==1);
	if(bSuccess&&(pEchoReply->Status!=0))
	{
		bSuccess=FALSE;
		SetLastError(pEchoReply->Status);

	}
	//close icmp jubing
	sm_pIcmpCloseHandle(hIP);
	return bSuccess;

}
int CPingI::Coo()
{
	printf("luo");
	return  0;
}
