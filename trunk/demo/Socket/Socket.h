#ifndef _SOCKET_H_DOGXUAN_
#define _SOCKET_H_DOGXUAN_

#include <afxsock.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <process.h>
using namespace std;

#define SZBUFF 1024
#define LOG_FILE "log.txt"

#define MAX_CONNECT 100

typedef void (*OnReceivePtr)(int isendID, char* buffer, int ireceivesize, int imaxsize);

class CServer;

typedef struct _tagSocketInfo{

	SOCKET Socket;

	sockaddr_in Sockaddr;

	bool bConnected;

	HANDLE hrecvthread;

	OnReceivePtr ponreceive;

	int iUID;

	int irevsize;

	char* czrevbuff;

	CServer* caller;
}ConnectInfo;

class CAsyncSock{

public:

	CAsyncSock()
	{
		WORD wVersionRequested;
		WSADATA wsaData;
		int err;
		
		wVersionRequested = MAKEWORD( 2, 2 );
		
		err = WSAStartup( wVersionRequested, &wsaData );
		if ( err != 0 ) {
			_error("Could not initial WinSock dll");
			return ;
		}
		
		if ( LOBYTE( wsaData.wVersion ) != 2 ||
			HIBYTE( wsaData.wVersion ) != 2 ) {
			WSACleanup( );
			_error("Error WinSock dll version");
			return; 
		}
	}

	~CAsyncSock()
	{
		WSACleanup();
	}

protected:
	
	string m_strRet;
	
	static void _write_log(const string& strMsg);
	
	static void _error(const string& strMsg);

	virtual void close(SOCKET& sock);
};

class CClient : CAsyncSock
{

public:

	CClient(int ilocalport = 1234, const char m_szIP[] = "127.0.0.1", int iremoteport = 2345, OnReceivePtr onreceive = NULL, int imaxbuf = SZBUFF);

	~CClient();

	void connectserver(const char m_szIP[] = "127.0.0.1", int iport = 1234, OnReceivePtr callfun = NULL, int imaxbuf = SZBUFF);

	void send_message(char* buffer, int isize);
	
	int localport(){return ntohs(m_ilocalport);}

private:

	static void receive_message(PVOID pvoid);

	int m_ilocalport;

	ConnectInfo m_connectinfo;

	OnReceivePtr m_ponreceive;

	HANDLE m_hreceive;

	int m_irevsize;

	char* m_czrevbuff;
};

class CServer : CAsyncSock
{
	
public:
	CServer(int ilocalport = 1234, OnReceivePtr onreceive = NULL, int imaxbuf = SZBUFF);
	
	~CServer();

	bool send_message(unsigned iUID, char* buffer, int isize);

	string client_info(unsigned iUID);

	int client_number(){return m_connectinfo.size();}
	
	int localport(){return ntohs(m_serverinfo.Sockaddr.sin_port);}

	void RemoveClinet(int iUID);

private:
	
	static void listenandwait(PVOID pvoid);
	
	static void wait_for_receive_from_client(PVOID pvoid);
	
	OnReceivePtr m_ponreceive;
	
	bool m_bListening;

	HANDLE m_hlistenthread;

	ConnectInfo m_serverinfo;

	typedef vector<ConnectInfo *> SocketVector;

	SocketVector m_connectinfo;

	int m_iUID;

	bool m_bConnectPool[MAX_CONNECT];

	int m_irevsize;
};

#endif //_SOCKET_H_DOGXUAN_