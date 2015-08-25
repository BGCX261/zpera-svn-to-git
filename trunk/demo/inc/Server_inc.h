#ifndef _SEVER_INC_H_
#define _SEVER_INC_H_

#include "Socket.h"
#include "neerr.h"
#include "neweravalue.h"
#include "connectvalue.h"

#define MAXTRY_TIME		40

typedef struct{
	HANDLE				hThread;   
	DWORD				dwThreadId; 
	SOCKET				SockClient;
}SUBTHREAD;

typedef struct{
	short				Lock;
	short				MemLock;
	int					CurPosi;
	int					DataPosi; 
	int					ListLong;
	int					*pList;
}MYLIST;

typedef struct{
	long				PlayerID;
	long				isendID;
	short				DataLock;
	short				MsgLock;
	DWORD				CurClientCom;
	DWORD				CurClientSent;
	LUInt64				SEED;
	DISPLAYDATA			ClinetData;
	MSGDATA				ClinetMsg;
}SEVERDATA;

typedef struct{
	
	CServer					*pServer;

	long					*pClientMemLock;
	long					*pDataLock;
	long					*pMsgLock;
	SEVERDATA				*pClientList;
	long					*pListSum;	

	///LOGIN REGISTER THREAD HANDLE/////////////////////////////////
	SUBTHREAD				*pThread_L_R;	
	MYLIST					*pList_L_R;
	////////////////////////////////////////////////////////////////

	///SEND THREAD HANDLE////////////////////////////////////////
	SUBTHREAD				*pThread_Send;	
	MYLIST					*pList_NeedSend;
	////////////////////////////////////////////////////////////////

}SERVERHANDLE;
#endif