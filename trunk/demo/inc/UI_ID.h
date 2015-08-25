#if !defined(_UI_ID_H_)
#define _UI_ID_H_

#include "DXUT.h"
#include "DXUTgui.h"
#include "DXUTguiIME.h"
#include "DXUTcamera.h"
#include "DXUTsettingsdlg.h"
#include "SDKmesh.h"
#include "SDKmisc.h"
#include "resource.h"
#include "neerr.h"
#include "Action_ID.h"
#include "NewEraValue.h"
#include "DXUTGUI2.h"

typedef struct{
	HANDLE					hThread;   
	DWORD					dwThreadId; 
	SOCKET					SockClient;
}SUBTHREAD;
typedef struct{
	short					Lock;
	short					CommandNum;   
	DWORD					ConnectCommand[MAXCONNECTCOM];
}CONNECTCOM;


typedef struct{
///WINDOWS & SYSTEM & DEVICE HANDLE/////////////////////////////
	CDXUTDialog				*plh_UD; 
	CDXUTDialog				*plh_UI;
	CDXUTDialog2			*plh_MButton;
	CDXUTDialog2			*plh_PlayerInitButton;
	CDXUTControl*			pControl;
	HINSTANCE				*pHinstance;
	UINT					nEvent;
	int						nControlID;
	void*					pUserContext;
////////////////////////////////////////////////////////////////

///WINDOWS & SYSTEM & DEVICE PARAMETER//////////////////////////
	long					WinWidth;
	long					WinHeight;
	void					*pMemory;
	long					MemorySize;
////////////////////////////////////////////////////////////////

///MAIN THREAD CONTROL COMMAND//////////////////////////////////
	long					*pNewUI;
	long					*pAskforUI;
	long					*pCurrentUI;
	long					*pLastUI;
	LUInt64					*pNewSubUI;
	LUInt64					*pCurrentSubUI;
	LUInt64					*pLastSubUI;

//	DWORD					*pNewBaseFace;
//	DWORD					*pCurrentBaseFace;
//	DWORD					*pLastBaseFace;

	LPWSTR					pOutText;
	int						*pCUrrentUI_ErrDis;
////////////////////////////////////////////////////////////////

///MAIN THREAD DISPLAYDATA WRITE BY CONNECT THREAD//////////////
	DISPLAYDATA				*pGameData;
////////////////////////////////////////////////////////////////

///CONNECT THREAD MSGDATA WRITE BY MAIN THREAD//////////////////
	MSGDATA					*pMsgData;
////////////////////////////////////////////////////////////////

///CONNECT THREAD HANDLE////////////////////////////////////////
	SUBTHREAD				*pConnectThread;	
	SUBTHREAD				*pRecieveThread;	
////////////////////////////////////////////////////////////////

///CONNECT COMMAND STACK WRITE BY TWO THREAD WIDH LOCK METHOD///
	CONNECTCOM				*pConnectCom;
////////////////////////////////////////////////////////////////
	LRESULT					ConnectState;
	long					SeverCom;
	long					SentState;
	long					BeLogin;// 0 = not login, >0 login = PlayerID
	LUInt64					SEED;
}WINHANDLE;

//////////////////////////////////////////////////////////////////////////
#define SENTSTATE_NONE						0x00
#define SENTSTATE_ASK_SENT					SENTSTATE_NONE				+1
#define SENTSTATE_MSG_SENT					SENTSTATE_ASK_SENT			+1
#define SENTSTATE_SEED_ASKED				SENTSTATE_MSG_SENT			+1



#define UIFORNID_HEAVY						0x01
#define UIFORNID_STREAM						0x02
#define UIFORNID_NORMAL						0x03

//////////////////////////////////////////////////////////////////////////

// #define UI_CURRENTFACE_GROUP_START			(0x04<<16)
// #define UI_CURRENTFACE_GROUP_LOADING			(0x05<<16)
// #define UI_CURRENTFACE_GROUP_GALAXY			(0x06<<16)
// #define UI_CURRENTFACE_GROUP_SYSTEM			(0x07<<16)
// #define UI_CURRENTFACE_GROUP_SURFACE			(0x08<<16)


#define UI_MAINUI_GROUP_LOGIN				(0x01)
#define UI_MAINUI_GROUP_REGISTER			(0x02)
#define UI_MAINUI_GROUP_PLAYERINIT			(0x03)
#define UI_MAINUI_GROUP_WAIT				(0x04)
#define UI_MAINUI_GROUP_LOADING				(0x05)//小于UI_MAINUI_GROUP_GALAXY的mainUI改变，会隐藏掉所有子界面
#define UI_MAINUI_GROUP_GALAXY				(0x06)//大于等于UI_MAINUI_GROUP_GALAXY的mainUI改变，会隐藏掉其他子界面，重新显示UI_SUBUI_GROUP_MAIN——属于主界面的子界面
#define UI_MAINUI_GROUP_SYSTEM				(0x07)
#define UI_MAINUI_GROUP_SURFACE				(0x08)

#define UI_SUBUI_STEP						16

#define UI_SUBUI_GROUP						(0xff<<UI_SUBUI_STEP)
#define UI_SUBUI_GROUP_SUB					((0x1<<UI_SUBUI_STEP)-1)

#define UI_SUBUI_GROUP_MAIN					(0x01<<UI_SUBUI_STEP)//属于主界面的子界面，可共存
#define UI_SUBUI_GROUP_MAIN_MAP				(0x01)				//缩微地图和一些主按钮（系统 人物 科技 舰队设计 所属星球 舰队等），这组实际上永远显示
#define UI_SUBUI_GROUP_MAIN_MYCHOSE			((0x01<<1))			//选择己方目标详细窗口
#define UI_SUBUI_GROUP_MAIN_TARGET			((0x01<<2))			//选择对方目标详细窗口
#define UI_SUBUI_GROUP_MAIN_CHACK			((0x01<<3))			//聊天界面

#define UI_SUBUI_GROUP_SYSTEM				(0x02<<UI_SUBUI_STEP)					//子界面组——系统界面

#define UI_SUBUI_GROUP_PLAYER				(0x03<<UI_SUBUI_STEP)					//子界面组——人物界面

#define UI_SUBUI_GROUP_TECHNOLOGY			(0x04<<UI_SUBUI_STEP)					//子界面组——科技界面

#define UI_SUBUI_GROUP_TRADING				(0x05<<UI_SUBUI_STEP)					//子界面组——交易界面



////////////////////////////////////////////////////////////////////////// Login UI


#define UI_LOGIN_STA_FORN					UIFORNID_NORMAL
#define UI_LOGIN_STA_COLOR					D3DCOLOR_ARGB( 255, 200, 200, 0 )

#define UI_LOGIN_EDIT_FORN					UIFORNID_NORMAL
#define UI_LOGIN_EDIT_BACKCOLOR				D3DCOLOR_ARGB( 128, 0, 0, 0 )
#define UI_LOGIN_EDIT_TEXTCOLOR				D3DCOLOR_ARGB( 255, 200, 200, 220 )
#define UI_LOGIN_EDIT_COLOR					0
#define UI_LOGIN_EDIT_BW					5

#define UI_LOGIN_BUTTON_FORN				UIFORNID_NORMAL
#define UI_LOGIN_BUTTON_BACKCOLOR			D3DCOLOR_ARGB( 255, 83, 74, 68 )
#define UI_LOGIN_BUTTON_TEXTCOLOR			D3DCOLOR_ARGB( 255, 20, 231, 225 )
#define UI_LOGIN_BUTTON_COLOR				0


#define UIID_LOGIN_EDIT_PLAYERNAME			0x0001
#define UIID_LOGIN_EDIT_PLAYERCODE			0x0002
#define UIID_LOGIN_BUTTON_ENTER				0x0003
#define UIID_LOGIN_BUTTON_EXIT				0x0004
#define UIID_LOGIN_BUTTON_REGISTER			0x0005
#define UIID_LOGIN_STATIC_ID				0x0006
#define UIID_LOGIN_STATIC_CODE				0x0007
#define UIID_LOGIN_STATIC_ERR				0x0008
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// Register UI


#define UI_REGISTER_STA_FORN				UIFORNID_NORMAL
#define UI_REGISTER_STA_COLOR				D3DCOLOR_ARGB( 255, 200, 200, 0 )

#define UI_REGISTER_EDIT_FORN				UIFORNID_NORMAL
#define UI_REGISTER_EDIT_BACKCOLOR			D3DCOLOR_ARGB( 128, 0, 0, 0 )
#define UI_REGISTER_EDIT_TEXTCOLOR			D3DCOLOR_ARGB( 255, 220, 200, 200 )
#define UI_REGISTER_EDIT_COLOR				0
#define UI_REGISTER_EDIT_BW					5

#define UI_REGISTER_BUTTON_FORN				UIFORNID_NORMAL
#define UI_REGISTER_BUTTON_BACKCOLOR		D3DCOLOR_ARGB( 128, 255, 255, 255 )
#define UI_REGISTER_BUTTON_TEXTCOLOR		D3DCOLOR_ARGB( 255, 64, 64, 64 )
#define UI_REGISTER_BUTTON_COLOR			0

#define UIID_REGISTER_EDIT_PLAYERNAME		0x1001
#define UIID_REGISTER_EDIT_PLAYERCODE		0x1002
#define UIID_REGISTER_EDIT_PLAYERCODE2		0x1003
#define UIID_REGISTER_EDIT_PLAYEREMAIL		0x1004
#define UIID_REGISTER_EDIT_PLAYERAGE		0x1005
#define UIID_REGISTER_BUTTON_ENTER			0x1006
#define UIID_REGISTER_BUTTON_EXIT			0x1007
#define UIID_REGISTER_STATIC_ID				0x1008
#define UIID_REGISTER_STATIC_CODE			0x1009
#define UIID_REGISTER_STATIC_CODE2			0x100a
#define UIID_REGISTER_STATIC_EMAIL			0x100b
#define UIID_REGISTER_STATIC_AGE			0x100c
#define UIID_REGISTER_STATIC_ERR			0x100d
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// PlayerInit UI


#define UI_PLAYERINIT_STA_FORN					UIFORNID_NORMAL
#define UI_PLAYERINIT_STA_COLOR					D3DCOLOR_ARGB( 255, 200, 200, 0 )

#define UI_PLAYERINIT_EDIT_FORN					UIFORNID_NORMAL
#define UI_PLAYERINIT_EDIT_BACKCOLOR				D3DCOLOR_ARGB( 128, 0, 0, 0 )
#define UI_PLAYERINIT_EDIT_TEXTCOLOR				D3DCOLOR_ARGB( 255, 200, 200, 200 )
#define UI_PLAYERINIT_EDIT_COLOR					0
#define UI_PLAYERINIT_EDIT_BW					5


#define UIID_PLAYERINIT_BUTTON_FORN_ENTER			0x00
#define UIID_PLAYERINIT_BUTTON_FORN_EXIT			0x00
#define UIID_PLAYERINIT_BUTTON_FORN_MALE			0x01
#define UIID_PLAYERINIT_BUTTON_FORN_FEMALE			0x02
#define UIID_PLAYERINIT_BUTTON_FORN_HEAVYMETAL		0x03
#define UIID_PLAYERINIT_BUTTON_FORN_STREAMLINE		0x04
#define UIID_PLAYERINIT_BUTTON_FORN_CLASSICAL		0x05
#define UIID_PLAYERINIT_BUTTON_FORN_MERCHANT		0x06
#define UIID_PLAYERINIT_BUTTON_FORN_SMUGGLER		0x07
#define UIID_PLAYERINIT_BUTTON_FORN_GUARD			0x08
#define UIID_PLAYERINIT_BUTTON_FORN_COMMANDO		0x09
#define UIID_PLAYERINIT_BUTTON_FORN_NATION1			0x0a
#define UIID_PLAYERINIT_BUTTON_FORN_NATION2			0x0b
#define UIID_PLAYERINIT_BUTTON_FORN_NATION3			0x0c
#define UIID_PLAYERINIT_BUTTON_FORN_NATION4			0x0d
#define UIID_PLAYERINIT_BUTTON_FORN_NATION5			0x0e
#define UIID_PLAYERINIT_BUTTON_FORN_NATION6			0x0f


//#define UIID_PLAYERINIT_BUTTON_FORN_ENTER			0x00
//#define UIID_PLAYERINIT_BUTTON_FORN_EXIT			0x00
//#define UIID_PLAYERINIT_BUTTON_FORN_MALE			0x00
//#define UIID_PLAYERINIT_BUTTON_FORN_FEMALE			0x00
//#define UIID_PLAYERINIT_BUTTON_FORN_HEAVYMETAL		0x00
//#define UIID_PLAYERINIT_BUTTON_FORN_STREAMLINE		0x00
//#define UIID_PLAYERINIT_BUTTON_FORN_CLASSICAL		0x00
//#define UIID_PLAYERINIT_BUTTON_FORN_MERCHANT		0x00
//#define UIID_PLAYERINIT_BUTTON_FORN_SMUGGLER		0x00
//#define UIID_PLAYERINIT_BUTTON_FORN_GUARD			0x00
//#define UIID_PLAYERINIT_BUTTON_FORN_COMMANDO		0x00
//#define UIID_PLAYERINIT_BUTTON_FORN_NATION1			0x00
//#define UIID_PLAYERINIT_BUTTON_FORN_NATION2			0x00
//#define UIID_PLAYERINIT_BUTTON_FORN_NATION3			0x00
//#define UIID_PLAYERINIT_BUTTON_FORN_NATION4			0x00
//#define UIID_PLAYERINIT_BUTTON_FORN_NATION5			0x00
//#define UIID_PLAYERINIT_BUTTON_FORN_NATION6			0x00
#define UI_PLAYERINIT_BUTTON_BACKCOLOR			D3DCOLOR_ARGB( 255, 83, 74, 68 )
#define UI_PLAYERINIT_BUTTON_TEXTCOLOR			D3DCOLOR_ARGB( 255, 20, 231, 225 )
#define UI_PLAYERINIT_BUTTON_COLOR				0

#define UIID_PLAYERINIT							0x2000

#define UIID_PLAYERINIT_STATIC_NAMEANDGENDER	0x2001
#define UIID_PLAYERINIT_STATIC_ADJUTANTNAME		0x2002
#define UIID_PLAYERINIT_STATIC_DESIGNSTYLE		0x2003
#define UIID_PLAYERINIT_STATIC_PROFESSION		0x2004
#define UIID_PLAYERINIT_STATIC_NATION			0x2005
#define UIID_PLAYERINIT_STATIC_DESCRIPTION		0x2006
#define UIID_PLAYERINIT_STATIC_DESCRIPTION2		0x2007



#define UIID_PLAYERINIT_EDIT_LORDNAME			0x2101
#define UIID_PLAYERINIT_EDIT_ADJUTANT1NAME		0x2102
#define UIID_PLAYERINIT_EDIT_ADJUTANT2NAME		0x2103
#define UIID_PLAYERINIT_EDIT_ADJUTANT3NAME		0x2104
#define UIID_PLAYERINIT_EDIT_ADJUTANT4NAME		0x2105

#define UIID_PLAYERINIT_BUTTON_ENTER			0x2201
#define UIID_PLAYERINIT_BUTTON_EXIT				0x2202
#define UIID_PLAYERINIT_BUTTON_MALE				0x2203
#define UIID_PLAYERINIT_BUTTON_FEMALE			0x2204
#define UIID_PLAYERINIT_BUTTON_HEAVYMETAL		0x2205
#define UIID_PLAYERINIT_BUTTON_STREAMLINE		0x2206
#define UIID_PLAYERINIT_BUTTON_CLASSICAL		0x2207
#define UIID_PLAYERINIT_BUTTON_MERCHANT			0x2208
#define UIID_PLAYERINIT_BUTTON_SMUGGLER			0x2209
#define UIID_PLAYERINIT_BUTTON_COMMANDO			0x220a
#define UIID_PLAYERINIT_BUTTON_GUARD			0x220b
#define UIID_PLAYERINIT_BUTTON_NATION1			0x220c
#define UIID_PLAYERINIT_BUTTON_NATION2			0x220d
#define UIID_PLAYERINIT_BUTTON_NATION3			0x220e
#define UIID_PLAYERINIT_BUTTON_NATION4			0x220f
#define UIID_PLAYERINIT_BUTTON_NATION5			0x2210
#define UIID_PLAYERINIT_BUTTON_NATION6			0x2211


//////////////////////////////////////////////////////////////////////////


#endif