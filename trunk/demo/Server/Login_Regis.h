#ifndef _LOGIN_REGIS_H_
#define _LOGIN_REGIS_H_

LRESULT StartL_R(SERVERHANDLE *pHandle);

LRESULT CloseL_R(SERVERHANDLE *pHandle);

LRESULT InitL_R(SERVERHANDLE *pHandle);

LRESULT ProcessLogin(SERVERHANDLE *pHandle, long CliID);

LRESULT ProcessRegister(SERVERHANDLE *pHandle, long CliID);

LRESULT ProcessInit(SERVERHANDLE *pHandle, long CliID);

LRESULT SendSeed(SERVERHANDLE *pHandle, long CliID);

#endif