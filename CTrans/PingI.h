// PingI.h: interface for the CPingI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PINGI_H__A792282D_6B69_4464_A5EC_6109D9D64CD4__INCLUDED_)
#define AFX_PINGI_H__A792282D_6B69_4464_A5EC_6109D9D64CD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
typedef unsigned long IPAddr;  //an ip addr

//set ip_option_infomation struct
typedef struct tagIP_OPTION_INFORMATION
{
	unsigned char Ttl;	//time to live
	unsigned char Tos;	//type of service 
	unsigned char Flags;	//ip header flags
	unsigned char OptionsSize;  //Size in byte of options data
	unsigned char FAR *OptionsData;  //pointer to option  data
}IP_OPTION_INFORMATION;


// set ICMP_ECHO_REPLY STRuct
typedef struct tagICMP_ECHO_REPLY
{
	IPAddr  Address;
	unsigned long Status;
	unsigned long RoundTripTime;
	unsigned short DtatSize;
	unsigned short Reserved;
	void FAR *Data;
	IP_OPTION_INFORMATION Options;
}ICMP_ECHO_REPLY;

// set bie name ;

typedef IP_OPTION_INFORMATION FAR* LPIP_OPTION_INFORMATION;
typedef ICMP_ECHO_REPLY FAR* LPICMP_ECHO_REPLY;


//dingyi zhizhen hanshu bianliang
typedef HANDLE (WINAPI IcmpCreateFile)(VOID);

typedef IcmpCreateFile* lpIcmpCreateFile;
typedef BOOL(WINAPI IcmpCloseHandle)(HANDLE IcmpHandle);
typedef IcmpCloseHandle* lpIcmpCloseHandle;
typedef DWORD (WINAPI IcmpSendEcho)(
HANDLE IcmpHandle,
IPAddr DestinationAddress,
LPVOID RequestData,
WORD RequestSize,
LPIP_OPTION_INFORMATION RequestOptions,
DWORD ReplySize,
DWORD Timeout
);
typedef IcmpSendEcho* lpIcmpSendEcho;

//set CPINGREPL
struct CPingReply
{
in_addr Address;
unsigned long RTT;
};
//set CPINGI class;
class CPingI{
public:
	HINSTANCE icmphandle;
	int Ping(UINT nRetries,LPCSTR pstrHost,HWND hWnd);
	lpIcmpCreateFile sm_pIcmpCreateFile;
	lpIcmpSendEcho sm_pIcmpSendEcho;
	lpIcmpCloseHandle sm_pIcmpCloseHandle;
	CPingI();
	Coo();
	virtual ~CPingI();
};		

#endif // !defined(AFX_PINGI_H__A792282D_6B69_4464_A5EC_6109D9D64CD4__INCLUDED_)
