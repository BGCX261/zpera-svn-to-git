#if !defined(_NEERR_H_)
#define _NEERR_H_

#include <wtypes.h>

#define		PI		3.1415926535
#define		C2PI	PI*0.0055555555555555555555555555555556
#define		PI2C	57.295779513082320876798154814105

#define		LOK								0x00
#define		NO_MEMORY						0x01
#define		SOCKETINIT_ERR					NO_MEMORY					+1
#define		COMMAND_ERR						SOCKETINIT_ERR				+1
#define		BUFFSIZE_ERR					COMMAND_ERR					+1
#define		LIST_FULL						BUFFSIZE_ERR				+1
#define		LIST_NEEDWAIT					LIST_FULL					+1
#define		LIST_ADD_OVERTIME				LIST_NEEDWAIT				+1
#define		PLAYER_LOGIN_ERR				LIST_ADD_OVERTIME			+1


#define		LERR_LORDNAME_TOOLONG			0x101 
#define		LERR_LORDNAME_ERROR				0x102 
#define		LERR_ADJUTANTNAME_TOOLONG		0x103 
#define		LERR_ADJUTANTNAME_ERROR			0x104 
#define		LERR_GENDER_MISS				0x105 
#define		LERR_DESIGNSTYLE_MISS			0x106 
#define		LERR_PROFESSION_MISS			0x107 
#define		LERR_NATION_MISS				0x108 
#define		LERR_NAME_TOOLONG				0x109 
#define		LERR_MAME_ERROR					0x10a 
#define		LERR_CODE_TOOLONG				0x10b 
#define		LERR_CODE_ERROR					0x10c 
#define		LERR_CODE_DIFFERENT				0x10d 
#define		LERR_EMAIL_MISS					0x10e 
#define		LERR_CANNOTCONNECT_SERVER		LERR_EMAIL_MISS				+1
#define		LERR_SEVER_BUSY					LERR_CANNOTCONNECT_SERVER	+1

#define		LERR_WRONG_CODE					LERR_SEVER_BUSY				+1
#define		LERR_NO_PLAYER_FOR_LOGIN		LERR_WRONG_CODE				+1//没有此帐号
#define		LERR_DENY_ENTER					LERR_NO_PLAYER_FOR_LOGIN	+1
#define		LERR_PLAYER_HASREGIS			LERR_DENY_ENTER				+1//人物已被注册
#define		LERR_LORDNAME_HASBEEN			LERR_PLAYER_HASREGIS		+1//人物名已存在

#define		LERR_CONNECTCOM_STACKFULL		LERR_EMAIL_MISS			+1 
#define		BMPHEADSIZE						0x436

#ifndef		SAFE_FREE
#define		SAFE_FREE(p)					  { if (p) { free(p); (p)=NULL; } }
#endif

#define		SOCKCOMLOCK(lock)				{(lock)=1;}
#define		SOCKCOMUNLOCK(lock)				{(lock)=0;}
#define		CHECKUNLOCK(lock)				(0==(lock))

#define		LH_ROUND(x)						(long)(x+0.5)


typedef unsigned char			LByte;
typedef void					LVoid;
typedef void*					LHandle;


#if defined(_MSC_VER)
typedef signed		__int64		LInt64;
typedef unsigned	__int64		LUInt64;
#else
typedef signed		long long	LInt64;
typedef unsigned	long long	LUInt64;
#endif
#endif