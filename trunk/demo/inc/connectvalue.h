#if !defined(_CONNECTVALUE_H_)
#define _CONNECTVALUE_H_

/////////////////////////	Msg Control Word	//////////////////////////
#define MSG_ID_NONE					0x00

#define MSG_ID_ASK					MSG_ID_NONE						+1//表明是请求
#define MSG_ID_RES					MSG_ID_ASK						+1//表明是回应
#define MSG_ID_TRAN					MSG_ID_RES						+1//表明是发送

#define MSG_ID_YES					MSG_ID_TRAN						+1
#define MSG_ID_NO					MSG_ID_YES						+1
#define MSG_ID_WAIT					MSG_ID_NO						+1
#define MSG_ID_OVERTIME				MSG_ID_WAIT						+1

#define MSG_ID_CLIENT_COM			(0x01<<30)
#define MSG_ID_ASK_SEED				MSG_ID_CLIENT_COM				+1//login  register
#define MSG_ID_ASK_LOGIN			MSG_ID_ASK_SEED					+1
#define MSG_ID_ASK_EXIT				MSG_ID_ASK_LOGIN				+1
#define MSG_ID_ASK_REGISTER			MSG_ID_ASK_EXIT					+1
#define MSG_ID_SEND_INIT			MSG_ID_ASK_REGISTER				+1
#define MSG_ID_ASK_ENTER_GALACY		MSG_ID_SEND_INIT				+1
#define MSG_ID_ASK_ENTER_SYSTEM		MSG_ID_ASK_ENTER_GALACY			+1
#define MSG_ID_ASK_ENTER_PLANET		MSG_ID_ASK_ENTER_SYSTEM			+1
#define MSG_ID_ASK_ENTER_ASTEROID	MSG_ID_ASK_ENTER_PLANET			+1
#define MSG_ID_ASK_BUILDACT			MSG_ID_ASK_ENTER_ASTEROID		+1



#define MSG_ID_SEVER_COM			(0x10<<30)
#define MSG_ID_ENTER_PRO			MSG_ID_SEVER_COM				+1//approve enter
#define MSG_ID_ENTER_DEN			MSG_ID_ENTER_PRO				+1//deny	enter
#define MSG_ID_PLAYER_NEEDINIT		MSG_ID_ENTER_DEN				+1
#define MSG_ID_NOPLAYER				MSG_ID_PLAYER_NEEDINIT			+1
#define MSG_ID_PLAYER_HASREGIS		MSG_ID_NOPLAYER					+1
#define MSG_ID_LORDNAME_HASBEEN		MSG_ID_PLAYER_HASREGIS			+1
#define MSG_ID_SEND_SEED			MSG_ID_LORDNAME_HASBEEN				+1//login  register

//////////////////////////////////////////////////////////////////////////

typedef struct{
	DWORD		Sign;					//MSG_ID_ASK / MSG_ID_RES
	DWORD		Command;				//>MSG_ID_TRAN, if( Sign == MSG_ID_ASK || Sign == MSG_ID_RES)
}SIMPLECONNECTCOM;
#endif