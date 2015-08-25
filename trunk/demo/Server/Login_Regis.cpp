
#include "Server_inc.h"
#include "Login_Regis.h"
#include "Mylist.h"


void ChangeCodebySeed(WCHAR *pCode, LUInt64 Seed, long ByteSize);

//数据库——帐号登录信息

CLIENTINFO			ClientTest[32]	= {0};
long				ClientNum = 0;
//数据库——人物信息
PLAYERINFO			PlayerTest[32]	= {0};

static DWORD WINAPI L_R_Process(LPVOID lpParam);  

LRESULT StartL_R(SERVERHANDLE *pHandle)
{
	LRESULT res = LOK;
	pHandle->pThread_L_R->hThread = CreateThread(NULL, NULL, L_R_Process, pHandle,  
		0, &(pHandle->pThread_L_R->dwThreadId));   

	return res;
}

LRESULT CloseL_R(SERVERHANDLE *pHandle)
{
	//release socket class
	if(NULL != pHandle->pThread_L_R->hThread)
		CloseHandle(pHandle->pThread_L_R->hThread); 
	return 0;
}

LRESULT InitL_R(SERVERHANDLE *pHandle)
{
	LRESULT res = LOK;

	return res;
}



static DWORD WINAPI L_R_Process(LPVOID lpParam)   
{   
	SERVERHANDLE *pHandle = (SERVERHANDLE*)lpParam;

	while(1)   
	{   
		long CurPosi = pHandle->pList_L_R->CurPosi, DataPosi = pHandle->pList_L_R->DataPosi;
		if(CurPosi == DataPosi-1)
			Sleep(5);
		else
		{
			LRESULT temres=LOK;
			int curClient = pHandle->pList_L_R->pList[CurPosi];
			do 
			{
				temres = MoveListMember(pHandle->pList_L_R);				
				Sleep(1);	
			} while ((temres==LIST_NEEDWAIT|| temres==LIST_FULL));

			switch(pHandle->pClientList[curClient].CurClientCom)
			{
			case MSG_ID_ASK_SEED:
				SendSeed(pHandle, curClient);
				break;
			case MSG_ID_ASK_LOGIN:
				ProcessLogin(pHandle, curClient);
				break;
			case MSG_ID_ASK_REGISTER:
				ProcessRegister(pHandle, curClient);
				break;
			case MSG_ID_SEND_INIT:
				ProcessInit(pHandle, curClient);
				break;
			}//if	
		}

	}//while

	return 0;   
}   

LRESULT ProcessLogin(SERVERHANDLE *pHandle, long CliID)
{
	LRESULT res = LOK;
	LOGINMESSANG *pL = &(pHandle->pClientList[CliID].ClinetMsg.loginMsg);
	BOOL beFound = false;
	int i;
////////////////	Fine Client		//////////////////////////////////////
	
	for (i=0; i<ClientNum; i++)
	{
		if(0 == wcscmp(ClientTest[i].PlayerName, pL->PlayerName))
			beFound = true;
	}	
	if(!beFound)
		res =  MSG_ID_NOPLAYER;
//////////////////////////////////////////////////////////////////////////
	
////////////////	Check Client	//////////////////////////////////////
	else
	{
		i--;
		WCHAR TemCode[64]={0};
		memcpy(TemCode, ClientTest[i].PlayerCode, 64);
		ChangeCodebySeed(TemCode, pHandle->pClientList[CliID].SEED, 40);
//		if(0 != wcscmp(ClientTest[i].PlayerCode, pL->PlayerCode))
		if(0 != wcscmp(TemCode, pL->PlayerCode))
			res = MSG_ID_ENTER_DEN;
		else
		{
////////////////	Check PlayerInit	//////////////////////////////////
			pHandle->pClientList[CliID].PlayerID = i;
			i = ClientTest[i].PlayerID;
			if(0==wcslen(PlayerTest[i].LordSimple.Name))
				res = MSG_ID_PLAYER_NEEDINIT;
			else
				res = MSG_ID_ENTER_PRO;
//////////////////////////////////////////////////////////////////////////
		}
	}
	pHandle->pClientList[CliID].CurClientCom = MSG_ID_NONE;
	pHandle->pClientList[CliID].CurClientSent = res;
//////////////////////////////////////////////////////////////////////////

////////////////	Respond			//////////////////////////////////////
	i = 0;
	do 
	{
		res = AddListMember(pHandle->pList_NeedSend, CliID);
		i++;
		Sleep(2);	
	} while (i<MAXTRY_TIME && (res==LIST_NEEDWAIT|| res==LIST_FULL));
	if(i==MAXTRY_TIME)
		return LIST_ADD_OVERTIME;
//////////////////////////////////////////////////////////////////////////
	return 0;
}
LRESULT ProcessRegister(SERVERHANDLE *pHandle, long CliID)
{
	LRESULT res = LOK;
	REGISTERMESSANG *pL = &(pHandle->pClientList[CliID].ClinetMsg.RegisterMsg);
	BOOL beFound = false;
	int i;
////////////////	Fine Client		//////////////////////////////////////

	for (i=0; i<ClientNum; i++)
	{
		if(0 == wcscmp(ClientTest[i].PlayerName, pL->PlayerName))
			beFound = true;
	}	
	if(beFound)
		res =  MSG_ID_PLAYER_HASREGIS;
//////////////////////////////////////////////////////////////////////////

////////////////	Check IP	Maybe need not	//////////////////////////

//////////////////////////////////////////////////////////////////////////

////////////////	Register Client	//////////////////////////////////////
	else
	{
		wcscpy(ClientTest[ClientNum].PlayerName, pL->PlayerName);


		wcscpy(ClientTest[ClientNum].PlayerName, pL->PlayerName);
		wcscpy(ClientTest[ClientNum].PlayerCode, pL->PlayerCode);
		wcscpy(ClientTest[ClientNum].PlayerEmail, pL->PlayerEmail);
		ClientTest[ClientNum].PlayerAge = pL->PlayerAge;
		ClientTest[ClientNum].PlayerID = ClientNum;
		pHandle->pClientList[CliID].PlayerID = ClientNum;
		ClientNum ++;
		res = MSG_ID_PLAYER_NEEDINIT;
	}
	pHandle->pClientList[CliID].CurClientCom = MSG_ID_NONE;
	pHandle->pClientList[CliID].CurClientSent = res;
//////////////////////////////////////////////////////////////////////////

////////////////	Respond			//////////////////////////////////////
	i = 0;
	do 
	{
		res = AddListMember(pHandle->pList_NeedSend, CliID);
		i++;
		Sleep(2);	
	} while (i<MAXTRY_TIME && (res==LIST_NEEDWAIT|| res==LIST_FULL));
	if(i==MAXTRY_TIME)
		return LIST_ADD_OVERTIME;
//////////////////////////////////////////////////////////////////////////
	return 0;
}

LRESULT ProcessInit(SERVERHANDLE *pHandle, long CliID)
{
	LRESULT res = LOK;
	PLAYERINITMESSANG *pL = &(pHandle->pClientList[CliID].ClinetMsg.MyPlayerInitMsg);
	BOOL beFound = false;
	int i;
////////////////	Fine Client		//////////////////////////////////////
	i = pHandle->pClientList[CliID].PlayerID;
	if(0!=wcslen(PlayerTest[i].LordSimple.Name))
		return PLAYER_LOGIN_ERR;
//////////////////////////////////////////////////////////////////////////

////////////////	Check LordName	//////////////////////////////////////
	else 
	{
		for (int j=0; j<ClientNum; j++)
		{
			if(0 == wcscmp(ClientTest[j].LordName, pL->LordName))
				beFound = true;
		}	
	}
	if(beFound)
		res =  MSG_ID_LORDNAME_HASBEEN;
////////////////	Init Player		//////////////////////////////////////
	else
	{
		wcscpy(PlayerTest[i].LordSimple.Name, pL->LordName);
		PlayerTest[i].LordSimple.Gender = pL->Gender;
		wcscpy(PlayerTest[i].Lord.LordName, pL->LordName);
		PlayerTest[i].Lord.Gender = pL->Gender;
		PlayerTest[i].Lord.Profession = pL->Profession;
		PlayerTest[i].DesignStyle = pL->DesignStyle;
		PlayerTest[i].Nation = pL->Nation;

		wcscpy(PlayerTest[i].AdjutantSimple[0].Name, pL->Adjutant1);
		wcscpy(PlayerTest[i].Adjutant[0].AdjutantName, pL->Adjutant1);
		wcscpy(PlayerTest[i].AdjutantSimple[1].Name, pL->Adjutant2);
		wcscpy(PlayerTest[i].Adjutant[1].AdjutantName, pL->Adjutant2);
		wcscpy(PlayerTest[i].AdjutantSimple[2].Name, pL->Adjutant3);
		wcscpy(PlayerTest[i].Adjutant[2].AdjutantName, pL->Adjutant3);
		wcscpy(PlayerTest[i].AdjutantSimple[3].Name, pL->Adjutant4);
		wcscpy(PlayerTest[i].Adjutant[3].AdjutantName, pL->Adjutant4);

		res = MSG_ID_ENTER_PRO;
	}
	pHandle->pClientList[CliID].CurClientCom = MSG_ID_NONE;
	pHandle->pClientList[CliID].CurClientSent = res;
//////////////////////////////////////////////////////////////////////////

////////////////	Respond			//////////////////////////////////////
	i = 0;
	do 
	{
		res = AddListMember(pHandle->pList_NeedSend, CliID);
		i++;
		Sleep(2);	
	} while (i<MAXTRY_TIME && (res==LIST_NEEDWAIT|| res==LIST_FULL));
	if(i==MAXTRY_TIME)
		return LIST_ADD_OVERTIME;
//////////////////////////////////////////////////////////////////////////
	return 0;
}
LRESULT SendSeed(SERVERHANDLE *pHandle, long CliID)
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
	pHandle->pClientList[CliID].CurClientSent = MSG_ID_SEND_SEED;

	////////////////	Respond			//////////////////////////////////////
	do 
	{
		res = AddListMember(pHandle->pList_NeedSend, CliID);
		i++;
		Sleep(2);	
	} while (i<MAXTRY_TIME && (res==LIST_NEEDWAIT|| res==LIST_FULL));
	if(i==MAXTRY_TIME)
		return LIST_ADD_OVERTIME;
	//////////////////////////////////////////////////////////////////////////
	return 0;
}

void ChangeCodebySeed(WCHAR *pCode, LUInt64 Seed, long ByteSize)
{
	long i, num=ByteSize/sizeof(LUInt64);
	LUInt64 *p = (LUInt64*)pCode;
	for (i=0; i<num; i++, p++)
	{
		LUInt64 tt = *p;
		tt = tt^Seed;
		*p = tt;
	}
}