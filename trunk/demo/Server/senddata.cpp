
#include "Server_inc.h"
#include "Senddata.h"
#include "Mylist.h"

static DWORD WINAPI Connect(LPVOID lpParam);  

LRESULT StartConnect(SERVERHANDLE *pHandle)
{
	LRESULT res = LOK;
	pHandle->pThread_Send->hThread = CreateThread(NULL, NULL, Connect, pHandle,  
		0, &(pHandle->pThread_Send->dwThreadId));   

	return res;
}

LRESULT CloseConnect(SERVERHANDLE *pHandle)
{
	//release socket class
	if(NULL != pHandle->pThread_Send->hThread)
		CloseHandle(pHandle->pThread_Send->hThread); 
	return 0;
}

LRESULT InitConnect(SERVERHANDLE *pHandle)
{
	LRESULT res = LOK;

	return res;
}


static DWORD WINAPI Connect(LPVOID lpParam)   
{   
	SERVERHANDLE *pHandle = (SERVERHANDLE*)lpParam;

	//	char recvBuf[50];
	//	recv(sockClient,recvBuf,50,0);
	//	printf("%s\n",recvBuf);
	SOCKET CurSock = pHandle->pThread_Send->SockClient;
	while(1)   
	{   
		long CurPosi = pHandle->pList_NeedSend->CurPosi, DataPosi = pHandle->pList_NeedSend->DataPosi;
		if(CurPosi == DataPosi-1)
			Sleep(5);
		else
		{
			LRESULT temres=LOK;
			int curClient = pHandle->pList_NeedSend->pList[CurPosi];
			do 
			{
				temres = MoveListMember(pHandle->pList_NeedSend);				
				Sleep(1);	
			} while ((temres==LIST_NEEDWAIT|| temres==LIST_FULL));
			DWORD SentCom = pHandle->pClientList[curClient].CurClientSent;
			switch(SentCom)
			{
			case MSG_ID_ENTER_PRO:
			case MSG_ID_ENTER_DEN:
			case MSG_ID_PLAYER_NEEDINIT:
			case MSG_ID_NOPLAYER:
			case MSG_ID_PLAYER_HASREGIS:
			case MSG_ID_LORDNAME_HASBEEN:
				SIMPLECONNECTCOM Resp;
				Resp.Sign = MSG_ID_RES;
				Resp.Command = SentCom;
				pHandle->pServer->send_message(curClient, (char*)(&Resp), sizeof(DWORD));
				break;
			case MSG_ID_SEND_SEED:
				struct {DWORD Sign; LUInt64 Seed;}RespSeed;
				RespSeed.Sign = MSG_ID_SEND_SEED;
				RespSeed.Seed = pHandle->pClientList[curClient].SEED;
				pHandle->pServer->send_message(curClient, (char*)(&RespSeed), sizeof(LUInt64)+sizeof(DWORD));
				break;
			}//if	
		}
	}//while
	return 0;   
} 