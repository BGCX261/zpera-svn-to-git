
#include "Socket.h"
#include "Server_inc.h"
#include "Mylist.h"

#include "Login_Regis.h"
#include "senddata.h"

long					ListSum = 0;	
long					ClientMemLock = 0;
long					DataLock = 0;
long					MsgLock = 0;

SUBTHREAD				Thread_L_R = {0};	
MYLIST					List_L_R = {0};
SUBTHREAD				Thread_Send = {0};	
MYLIST					List_NeedSend = {0};
SERVERHANDLE				Handle={0};



LRESULT ClientListMemroy();
void ClientListRelease();

LRESULT AssortCom(SEVERDATA *pClientList, int isendID,  char* buffer, int ireceivesize);



void OnReceive(int isendID, char* buffer, int ireceivesize, int imaxsize);


int main(int argc, char** argv)
{
	LRESULT res;
	CServer server(8888, OnReceive, SZBUFF);
	Handle.pServer = &server;

	Handle.pListSum = &ListSum;
	Handle.pClientMemLock = &ClientMemLock;
	Handle.pDataLock = &DataLock;
	Handle.pMsgLock = &MsgLock;
	
	Handle.pThread_L_R = &Thread_L_R;
	Handle.pList_L_R = &List_L_R;
	Handle.pThread_Send = &Thread_Send;
	Handle.pList_NeedSend = &List_NeedSend;

	SOCKCOMUNLOCK(*Handle.pClientMemLock);
	SOCKCOMUNLOCK(*Handle.pDataLock);
	SOCKCOMUNLOCK(*Handle.pMsgLock);
	char buf[255];
	ClientListMemroy();
	cout << endl << "Input Command (list, info, send, port, show, quit/exit)" << endl;
	cout << endl << "Server Command (lrstart, lrstop)" << endl;
	cout << endl << "Server Command (sentstart, sentstop)" << endl;

	res = LOK;
	res = InitL_R(&Handle);
	res = StartL_R(&Handle);
	res = LOK;
	res = InitConnect(&Handle);
	res = StartConnect(&Handle);

	while (1)
	{

		scanf("%s", buf);
		if(!strcmp(buf, "show"))
		{
			cout << endl << "Input Command (list, info, send, port, show, quit/exit)" << endl;
			cout << endl << "Server Command (lrstart, lrstop)" << endl;
			cout << endl << "Server Command (sentstart, sentstop)" << endl;
		}
		else if(!strcmp(buf, "lrstart"))
		{
			res = LOK;
			res = InitL_R(&Handle);
			res = StartL_R(&Handle);
			if(LOK == res)	cout << endl << "Login_Register Module launch succeeded" << endl;
		}
		else if(!strcmp(buf, "lrstop"))
		{
			res = LOK;
			res = CloseL_R(&Handle);
			if(LOK == res)	cout << endl << "Login_Register Module stop succeeded" << endl;
		}
		else if(!strcmp(buf, "sentstart"))
		{
			res = LOK;
			res = InitConnect(&Handle);
			res = StartConnect(&Handle);
			if(LOK == res)	cout << endl << "Msgsend Module launch succeeded" << endl;
		}
		else if(!strcmp(buf, "sentstop"))
		{
			res = LOK;
			res = CloseConnect(&Handle);
			if(LOK == res)	cout << endl << "Msgsend Module stop succeeded" << endl;
		}
		else if (!strcmp(buf, "list"))
		{
			cout << "There are "<< server.client_number() << " clients connected.";
			
		}
		else if (!strcmp(buf, "info"))
		{
			cout << "input client UID (0 for all): ";
			int uid;
			scanf("%d", &uid);
			cout << server.client_info(uid) << endl;
		} 
		else if (!strcmp(buf, "port"))
		{
			cout << "Current listening port is " << server.localport() << endl ;
		} 
		else if (!strcmp(buf, "send"))
		{
			cout<< "input client UID (0 for all): " << endl ;
			int uid;
			scanf("%d", &uid);
			cout<< "input Message: ";
			scanf("%s", buf);
			server.send_message(uid, buf, sizeof(buf));
		} 
		else if (!strcmp(buf, "quit") || !strcmp(buf, "exit"))
		{
			break;
		} 
	}

	ClientListRelease();
	return 0;
}

LRESULT ClientListMemroy()
{
	LRESULT res = LOK;
	SEVERDATA		*pClientTemp = NULL;
	int		*pListTemp = NULL;
	long CurrNum = Handle.pServer->client_number();
	if(CurrNum > *Handle.pListSum-256)
	{
		ListSum += 256;

		pClientTemp = (SEVERDATA*)malloc(ListSum*sizeof(SEVERDATA));
		if (NULL == pClientTemp)
		{
			return NO_MEMORY;
		}
		memset(pClientTemp, 0, ListSum*sizeof(SEVERDATA));

		SOCKCOMLOCK(*Handle.pClientMemLock);
		while(!CHECKUNLOCK(*Handle.pDataLock)||!CHECKUNLOCK(*Handle.pMsgLock))
		{
			Sleep(2);	
		}
		memcpy(pClientTemp, Handle.pClientList, CurrNum*sizeof(SEVERDATA));
		free(Handle.pClientList);
		Handle.pClientList = pClientTemp;
		SOCKCOMUNLOCK(*Handle.pClientMemLock);
		//////////////////////////////////////////////////////////////////////////
		pListTemp = (int*)malloc(ListSum*sizeof(int));
		if (NULL == pListTemp)
		{
			return NO_MEMORY;
		}
		memset(pListTemp, 0, ListSum*sizeof(int));
		SOCKCOMLOCK(Handle.pList_L_R->MemLock);
		while(!CHECKUNLOCK(Handle.pList_L_R->Lock))
		{
			Sleep(2);	
		}
		memcpy(pListTemp, Handle.pList_L_R->pList, Handle.pList_L_R->ListLong*sizeof(int));
		free(Handle.pList_L_R->pList);
		Handle.pList_L_R->ListLong = ListSum;
		Handle.pList_L_R->pList = pListTemp;
		SOCKCOMUNLOCK(Handle.pList_L_R->MemLock);
		//////////////////////////////////////////////////////////////////////////
		pListTemp = NULL;
		pListTemp = (int*)malloc(ListSum*sizeof(int));
		if (NULL == pListTemp)
		{
			return NO_MEMORY;
		}
		memset(pListTemp, 0, ListSum*sizeof(int));
		SOCKCOMLOCK(Handle.pList_NeedSend->MemLock);
		while(!CHECKUNLOCK(Handle.pList_NeedSend->Lock))
		{
			Sleep(2);	
		}
		memcpy(pListTemp, Handle.pList_NeedSend->pList, Handle.pList_NeedSend->ListLong*sizeof(int));
		free(Handle.pList_NeedSend->pList);
		Handle.pList_NeedSend->ListLong = ListSum;
		Handle.pList_NeedSend->pList = pListTemp;
		SOCKCOMUNLOCK(Handle.pList_NeedSend->MemLock);	
	}

	return res;

}

void ClientListRelease()
{
	if(NULL != Handle.pClientList)
		free(Handle.pClientList);
	Handle.pClientList = NULL;
}
static void GenerateSeed(SERVERHANDLE *pHandle, long CliID)
{
	LRESULT res=LOK;
	int temran, i;
	LUInt64 Seed=0, temp64;
	srand(GetTickCount()); 
	temran = rand();	temp64 = temran;	Seed = (temp64 & 0xff);
	temran = rand();	temp64 = temran;	Seed += (temp64 & 0xff)<<8;
	temran = rand();	temp64 = temran;	Seed += (temp64 & 0xff)<<16;
	temran = rand();	temp64 = temran;	Seed += (temp64 & 0xff)<<24;
	temran = rand();	temp64 = temran;	Seed += (temp64 & 0xff)<<32;
	temran = rand();	temp64 = temran;	Seed += (temp64 & 0xff)<<40;
	temran = rand();	temp64 = temran;	Seed += (temp64 & 0xff)<<48;
	temran = rand();	temp64 = temran;	Seed += (temp64 & 0xff)<<56;

	pHandle->pClientList[CliID].SEED = Seed;
	
}

void OnReceive(int isendID, char* buffer, int ireceivesize, int imaxsize)
{
//	cout << "\tMsg from " << isendID << " : " << buffer << endl;
	DWORD ControlWord;
	SIMPLECONNECTCOM Resp;
	Resp.Sign = MSG_ID_RES;
//	if (ireceivesize == sizeof(DWORD))
	if(MSG_ID_ASK == *( (DWORD*)buffer )  || MSG_ID_RES == *( (DWORD*)buffer ))
	{

cout << "MSG_ID_ASK |  MSG_ID_RES" << endl;

		ControlWord = *((DWORD*)buffer+1);
		if(ControlWord == MSG_ID_ASK_SEED)
		{
			GenerateSeed(&Handle, isendID);
			struct {DWORD Sign; LUInt64 Seed;}RespSeed;
			RespSeed.Sign = MSG_ID_SEND_SEED;
			RespSeed.Seed = Handle.pClientList[isendID].SEED;
			Handle.pServer->send_message(isendID, (char*)(&RespSeed), sizeof(LUInt64)+sizeof(DWORD));
		}
		else if(Handle.pClientList[isendID].CurClientCom == MSG_ID_NONE || Handle.pClientList[isendID].CurClientCom == ControlWord)
		{
			Handle.pClientList[isendID].CurClientCom = ControlWord;

			Resp.Command = MSG_ID_YES;
			if( ControlWord == MSG_ID_ASK_SEED)
			{
				long CurrNum = Handle.pServer->client_number();
				LRESULT temres=LOK;
				int cunt=0;
				if(CurrNum>ListSum)
				{
					Resp.Command = MSG_ID_WAIT;
					Handle.pServer->send_message(isendID, (char*)&(Resp), sizeof(SIMPLECONNECTCOM));
					ClientListMemroy();
				}
				else
				{
					do 
					{
						temres = AddListMember(Handle.pList_L_R, isendID);
						cunt++;
						Sleep(2);	
					} while (cunt<20 && (temres==LIST_NEEDWAIT|| temres==LIST_FULL));
					if(temres == LOK){
						Resp.Command = MSG_ID_YES;
cout << " SEND MSG_ID_YES " << endl;
					}
					else if(cunt==20){
						Resp.Command = MSG_ID_WAIT; //MSG_ID_OVERTIME
cout << " SEND MSG_ID_OVERTIME " << endl;
					}
					else{
						Resp.Command = MSG_ID_WAIT;// MSG_ID_NO
cout << " SEND MSG_ID_NO " << endl;
					}
					Handle.pServer->send_message(isendID, (char*)&(Resp), sizeof(SIMPLECONNECTCOM));
				}
			}
			else
				Handle.pServer->send_message(isendID, (char*)&(Resp), sizeof(SIMPLECONNECTCOM));
		}
		else
		{
			Resp.Command = MSG_ID_WAIT;
			Handle.pServer->send_message(isendID, (char*)&(Resp), sizeof(SIMPLECONNECTCOM));
		}
	}
	else
	{
		LRESULT temres=LOK;
		if(CHECKUNLOCK(Handle.pClientList->MsgLock))
		{
			temres = AssortCom(Handle.pClientList, isendID, buffer, ireceivesize);//所有传输数据头4字节都是口令:MSG_ID_ASK / MSG_ID_RES / MSG_ID_TRAN
			if(temres == LOK)
				Resp.Command = MSG_ID_YES;
			else if(temres == LIST_ADD_OVERTIME)
				Resp.Command = MSG_ID_OVERTIME;
			else
				Resp.Command = MSG_ID_NO;
			Handle.pServer->send_message(isendID, (char*)&(Resp), sizeof(SIMPLECONNECTCOM));
		}
		else
		{
			Resp.Command = MSG_ID_WAIT;
			Handle.pServer->send_message(isendID, (char*)&(Resp), sizeof(SIMPLECONNECTCOM));
		}
	}



}

LRESULT AssortCom(SEVERDATA *pClientList, int isendID, char* buffer, int ireceivesize)
{
	SEVERDATA *pCurCli = pClientList+isendID;
	long Datasize;
	LRESULT res = LOK, temres=LOK, cunt=0;
	switch(pCurCli->CurClientCom)
	{
//////////////////////////////////////////////////////////////////////////
	case MSG_ID_ASK_SEED:
		break;
//////////////////////////////////////////////////////////////////////////
	case MSG_ID_ASK_LOGIN:
		{
			Datasize = sizeof(LOGINMESSANG);
			LOGINMESSANG *pb = (LOGINMESSANG*)buffer;

			if(pb->CurClientCom != MSG_ID_ASK_LOGIN)
				return COMMAND_ERR;
			if(Datasize != ireceivesize)
				return BUFFSIZE_ERR;
			for (cunt=0; cunt<MAXTRY_TIME; cunt++)
			{
				if(CHECKUNLOCK(*Handle.pClientMemLock) && CHECKUNLOCK(pCurCli->MsgLock))
				{
					SOCKCOMLOCK(*Handle.pMsgLock);
					SOCKCOMLOCK(pCurCli->MsgLock);
					memcpy(&pCurCli->ClinetMsg.loginMsg, pb, Datasize);
					SOCKCOMUNLOCK(pCurCli->MsgLock);
					SOCKCOMUNLOCK(*Handle.pMsgLock);
				}
				else
					Sleep(2);
			}
			if(cunt==MAXTRY_TIME)
				return LIST_ADD_OVERTIME;
			cunt = 0;
			do 
			{
				temres = AddListMember(Handle.pList_L_R, isendID);
				cunt++;
				Sleep(2);	
			} while (cunt<MAXTRY_TIME && (temres==LIST_NEEDWAIT|| temres==LIST_FULL));
			if(cunt==MAXTRY_TIME)
				return LIST_ADD_OVERTIME;
		}
		break;
//////////////////////////////////////////////////////////////////////////
	case MSG_ID_ASK_REGISTER:
		{
			Datasize = sizeof(REGISTERMESSANG);
			REGISTERMESSANG *pb = (REGISTERMESSANG*)buffer;
			if(pb->CurClientCom != MSG_ID_ASK_REGISTER)
				return COMMAND_ERR;
			if(Datasize != ireceivesize)
				return BUFFSIZE_ERR;
			for (cunt=0; cunt<MAXTRY_TIME; cunt++)
			{
				if(CHECKUNLOCK(*Handle.pClientMemLock) && CHECKUNLOCK(pCurCli->MsgLock))
				{
					SOCKCOMLOCK(*Handle.pMsgLock);
					SOCKCOMLOCK(pCurCli->MsgLock);
					memcpy(&pCurCli->ClinetMsg.RegisterMsg, pb, Datasize);
					SOCKCOMUNLOCK(pCurCli->MsgLock);
					SOCKCOMUNLOCK(*Handle.pMsgLock);
				}
				else
					Sleep(2);
			}
			if(cunt==MAXTRY_TIME)
				return LIST_ADD_OVERTIME;
			cunt = 0;
			do 
			{
				temres = AddListMember(Handle.pList_L_R, isendID);
				cunt++;
				Sleep(2);	
			} while (cunt<20 && (temres==LIST_NEEDWAIT|| temres==LIST_FULL));
			if(cunt==20)
				return LIST_ADD_OVERTIME;
		}
		break;
//////////////////////////////////////////////////////////////////////////
	case MSG_ID_SEND_INIT:
		{
			Datasize = sizeof(PLAYERINITMESSANG);
			PLAYERINITMESSANG *pb = (PLAYERINITMESSANG*)buffer;
			if(pb->CurClientCom != MSG_ID_SEND_INIT)
				return COMMAND_ERR;
			if(Datasize != ireceivesize)
				return BUFFSIZE_ERR;
			for (cunt=0; cunt<MAXTRY_TIME; cunt++)
			{
				if(CHECKUNLOCK(*Handle.pClientMemLock) && CHECKUNLOCK(pCurCli->MsgLock))
				{
					SOCKCOMLOCK(*Handle.pMsgLock);
					SOCKCOMLOCK(pCurCli->MsgLock);
					memcpy(&pCurCli->ClinetMsg.MyPlayerInitMsg, pb, Datasize);
					SOCKCOMUNLOCK(pCurCli->MsgLock);
					SOCKCOMUNLOCK(*Handle.pMsgLock);
				}
				else
					Sleep(2);
			}
			if(cunt==MAXTRY_TIME)
				return LIST_ADD_OVERTIME;
			cunt = 0;
			do 
			{
				temres = AddListMember(Handle.pList_L_R, isendID);
				cunt++;
				Sleep(2);	
			} while (cunt<20 && (temres==LIST_NEEDWAIT|| temres==LIST_FULL));
			if(cunt==20)
				return LIST_ADD_OVERTIME;
		}
		break;
//////////////////////////////////////////////////////////////////////////
	case MSG_ID_ASK_ENTER_GALACY:
		{
			Datasize = sizeof(ENTERINFO);
			ENTERINFO *pb = (ENTERINFO*)buffer;
			if(pb->CurClientCom != MSG_ID_ASK_ENTER_GALACY)
				return COMMAND_ERR;
			if(Datasize != ireceivesize)
				return BUFFSIZE_ERR;
//			memcpy(&pCurCli->ClinetMsg.EnterGalacy, pb, Datasize);
		}
		break;
//////////////////////////////////////////////////////////////////////////
	case MSG_ID_ASK_ENTER_SYSTEM:
		{
			Datasize = sizeof(ENTERINFO);
			ENTERINFO *pb = (ENTERINFO*)buffer;
			if(pb->CurClientCom != MSG_ID_ASK_ENTER_SYSTEM)
				return COMMAND_ERR;
			if(Datasize != ireceivesize)
				return BUFFSIZE_ERR;
//			memcpy(&pCurCli->ClinetMsg.EnterSystem, pb, Datasize);
		}
		break;
//////////////////////////////////////////////////////////////////////////
	case MSG_ID_ASK_ENTER_PLANET:
		{
			Datasize = sizeof(ENTERINFO);
			ENTERINFO *pb = (ENTERINFO*)buffer;
			if(pb->CurClientCom != MSG_ID_ASK_ENTER_PLANET)
				return COMMAND_ERR;
			if(Datasize != ireceivesize)
				return BUFFSIZE_ERR;
//			memcpy(&pCurCli->ClinetMsg.EnterPlanet, pb, Datasize);
		}
		break;
//////////////////////////////////////////////////////////////////////////
	case MSG_ID_ASK_ENTER_ASTEROID:
		{
			Datasize = sizeof(ENTERINFO);
			ENTERINFO *pb = (ENTERINFO*)buffer;
			if(pb->CurClientCom != MSG_ID_ASK_ENTER_ASTEROID)
				return COMMAND_ERR;
			if(Datasize != ireceivesize)
				return BUFFSIZE_ERR;
//			memcpy(&pCurCli->ClinetMsg.EnterAsteroid, pb, Datasize);
		}
		break;
//////////////////////////////////////////////////////////////////////////
	case MSG_ID_ASK_BUILDACT:
		{
			Datasize = sizeof(BUILDINFO);
			BUILDINFO *pb = (BUILDINFO*)buffer;
			if(pb->CurClientCom != MSG_ID_ASK_BUILDACT)
				return COMMAND_ERR;
			if(Datasize != ireceivesize)
				return BUFFSIZE_ERR;
//			memcpy(&pCurCli->ClinetMsg.BuildAction, pb, Datasize);
		}
		break;
//////////////////////////////////////////////////////////////////////////
	case MSG_ID_ASK_EXIT:
		break;
	};
	
	return res;
}

