// TestGalacyInit.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WTypes.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std; 

#include "neerr.h"
#include "NewEraValue.h"
#include "GalacyInitData.h"

#define GALACYWI	20
#define MYMAXCHAR	60
#define	GALACYRA	SYSTEMRANGE*GALACYWI/2
#define CENTERRA	GALACYRA*0.7
#define RAND_MAXF	double(RAND_MAX)

LHSIZE			Galacy_Size		= {SYSTEMRANGE*GALACYWI, SYSTEMRANGE*GALACYWI};
LHSIZE			System_Size		= {SYSTEMWIDTH, SYSTEMWIDTH};

SIMPLESYSTEM	*pTestSy_SimpleData=NULL;			//Test System
SYSTEMINFO		*pTestSy_InfoData=NULL;
SIMPLEPLANET	*pTestPl_SimpleData=NULL;			//Test Planet
SIMPLEASTEROID	*pTestAs_SimpleData=NULL;			//Test Asteroid
PLANETINFO		*pTestPl_InfoData=NULL;
ASTEROIDINFO	*pTestAs_InfoData=NULL;
GALACYINFO		GalacyInfo;
GALACYHEADER	GalacyHeader;
byte			*GroupSign=NULL;

//WCHAR			Group1[128]={0};			
//WCHAR			Group2[128]={0};		

long			SystemSum = GALACYWI * GALACYWI;
long			PlanetSum = 0;
long			AsteroidSum = 0;
long			PlanetArea = 0;
long			AsteroidArea = 0;
POINT			GalacyCenter = {System_Size.sWidth/2, System_Size.sHeight/2};

LRESULT	GenerateGalacy();
LRESULT	LoadGalacy();
void ReleaseGalacy();







int _tmain(int argc, _TCHAR* argv[])
{
	LRESULT res=LOK;
	char buf[256];
//	WCHAR tt[24]={0};
//	wcscpy(tt,L"0");

	srand(GetTickCount()); 

	wcscpy(GalacyHeader.GalacyInfoName, L"TestGalacy.zpd");
	wcscpy(GalacyHeader.SystemSimpleName, L"TestSySi.zpd");
	wcscpy(GalacyHeader.SystemInfoName, L"TestSyIn.zpd");
	wcscpy(GalacyHeader.PlanetSimpleName, L"TestPlSi.zpd");
	wcscpy(GalacyHeader.PlanetInfoName, L"TestPlIn.zpd");
	wcscpy(GalacyHeader.AsteroidSimpleName, L"TestAsySi.zpd");
	wcscpy(GalacyHeader.AsteroidInfoName, L"TestAsIn.zpd");

	while (1)
	{
		cout << endl << "Input 'generate' to Generate a new Galacy" << endl;
		scanf("%s", buf);
		if (!strcmp(buf, "Generate") || !strcmp(buf, "generate"))
		{
			res = GenerateGalacy();
			if(LOK == res)
				cout << "Generation succeeded";
			else
				cout << "Error "<< res;
		}
		else if (!strcmp(buf, "Load") || !strcmp(buf, "load"))
		{
			res = LoadGalacy();
			if(LOK == res)
				cout << "Load succeeded";
			else
				cout << "Error "<< res;
		}
		else if (!strcmp(buf, "quit") || !strcmp(buf, "exit"))
		{
			break;
		} 
	}

	ReleaseGalacy();
	return 0;
}
void ReleaseGalacy()
{
	if(pTestSy_SimpleData)	free(pTestSy_SimpleData);
	if(pTestSy_InfoData)	free(pTestSy_InfoData);
	if(pTestPl_SimpleData)	free(pTestPl_SimpleData);
	if(pTestAs_SimpleData)	free(pTestAs_SimpleData);
	if(pTestPl_InfoData)	free(pTestPl_InfoData);
	if(pTestAs_InfoData)	free(pTestAs_InfoData);
	if(GroupSign)			free(GroupSign);
}

LRESULT	LoadGalacy()
{
	LRESULT res = LOK;
	FILE *pTestGFile;
	WCHAR Path[256]={0}, FinalPath[256]={0};
	wcscpy(Path, L"../../../Data/");

//////////////////////////////////////////////////////////////////////////

	pTestGFile = NULL;
	wcscpy(FinalPath, Path);
	wcscat(FinalPath, GalacyHeader.GalacyInfoName);
	pTestGFile = _wfopen(FinalPath, L"r+");
	fread(&GalacyHeader, 1, sizeof(GALACYHEADER), pTestGFile);
	fclose(pTestGFile);

//////////////////////////////////////////////////////////////////////////

	pTestSy_SimpleData	= (SIMPLESYSTEM*)malloc(GalacyHeader.SystemNum*sizeof(SIMPLESYSTEM));	
	pTestSy_InfoData	= (SYSTEMINFO*)malloc(GalacyHeader.SystemNum*sizeof(SYSTEMINFO));
	pTestPl_SimpleData	= (SIMPLEPLANET*)malloc(GalacyHeader.PlanetNum*sizeof(SIMPLEPLANET));	
	pTestPl_InfoData	= (PLANETINFO*)malloc(GalacyHeader.PlanetNum*sizeof(PLANETINFO));
	pTestAs_SimpleData	= (SIMPLEASTEROID*)malloc(GalacyHeader.AsteroidNum*sizeof(SIMPLEASTEROID));	
	pTestAs_InfoData	= (ASTEROIDINFO*)malloc(GalacyHeader.AsteroidNum*sizeof(ASTEROIDINFO));
//////////////////////////////////////////////////////////////////////////

	pTestGFile = NULL;
	wcscpy(FinalPath, Path);
	wcscat(FinalPath, GalacyHeader.SystemSimpleName);
	pTestGFile = _wfopen(FinalPath, L"rb+");
	fread(pTestSy_SimpleData, SystemSum, sizeof(SIMPLESYSTEM), pTestGFile);
	fclose(pTestGFile);

	pTestGFile = NULL;
	wcscpy(FinalPath, Path);
	wcscat(FinalPath, GalacyHeader.SystemInfoName);
	pTestGFile = _wfopen(FinalPath, L"rb+");
	fread(pTestSy_InfoData, SystemSum, sizeof(SYSTEMINFO), pTestGFile);
	fclose(pTestGFile);

	pTestGFile = NULL;
	wcscpy(FinalPath, Path);
	wcscat(FinalPath, GalacyHeader.PlanetSimpleName);
	pTestGFile = _wfopen(FinalPath, L"rb+");
	fread(pTestPl_SimpleData, PlanetSum, sizeof(SIMPLEPLANET), pTestGFile);
	fclose(pTestGFile);

	pTestGFile = NULL;
	wcscpy(FinalPath, Path);
	wcscat(FinalPath, GalacyHeader.PlanetInfoName);
	pTestGFile = _wfopen(FinalPath, L"rb+");
	fread(pTestPl_InfoData, PlanetSum, sizeof(PLANETINFO), pTestGFile);
	fclose(pTestGFile);

	pTestGFile = NULL;
	wcscpy(FinalPath, Path);
	wcscat(FinalPath, GalacyHeader.AsteroidSimpleName);
	pTestGFile = _wfopen(FinalPath, L"rb+");
	fread(pTestAs_SimpleData, AsteroidSum, sizeof(SIMPLEASTEROID), pTestGFile);
	fclose(pTestGFile);

	pTestGFile = NULL;
	wcscpy(FinalPath, Path);
	wcscat(FinalPath, GalacyHeader.AsteroidInfoName);
	pTestGFile = _wfopen(FinalPath, L"rb+");
	fread(pTestAs_InfoData, AsteroidSum, sizeof(ASTEROIDINFO), pTestGFile);
	fclose(pTestGFile);

//////////////////////////////////////////////////////////////////////////
	return res;
}



static LRESULT	InitSysInfo();
static LRESULT	SysSet();
static LRESULT	InitPlaInfo();
static LRESULT	InitAstInfo();
static LRESULT	InitGroundInfo(long *pWid, GROUNDINFO *pGround, RESOURCEGROUP16 Pro, RESOURCEGROUP_RANGE Area, RESOURCEGROUP_RANGE Value,
							   RESOURCEGROUP32 *pSourceReserve, long *pTrueArea);

LRESULT	GenerateGalacy()
{
	LRESULT res=LOK;
	FILE *pTestGFile;
//////////////////////////////////////////////////////////////////////////

	pTestSy_SimpleData	= (SIMPLESYSTEM*)malloc(SystemSum*sizeof(SIMPLESYSTEM));	
	memset(pTestSy_SimpleData, 0, SystemSum*sizeof(SIMPLESYSTEM));
	pTestSy_InfoData	= (SYSTEMINFO*)malloc(SystemSum*sizeof(SYSTEMINFO));
	memset(pTestSy_InfoData, 0, SystemSum*sizeof(SYSTEMINFO));
	GroupSign			= (byte*)malloc(MYMAXCHAR*MYMAXCHAR);
	memset(GroupSign, 0, MYMAXCHAR*MYMAXCHAR);
//////////////////////////////////////////////////////////////////////////
	
	res = InitSysInfo();
	res = SysSet();
	res = InitPlaInfo();
	res = InitAstInfo();

//////////////////////////////////////////////////////////////////////////

	WCHAR Path[256]={0}, FinalPath[256]={0};
	wcscpy(Path, L"../../../Data/");
	GalacyHeader.SystemNum = SystemSum;
	GalacyHeader.PlanetNum = PlanetSum;
	GalacyHeader.AsteroidNum = AsteroidSum;
	GalacyHeader.GalacyWid = GALACYWI;
	GalacyHeader.SystemWid = SYSTEMWIDTH;
	GalacyHeader.SystemRange = SYSTEMRANGE;

//////////////////////////////////////////////////////////////////////////

	pTestGFile = NULL;
	wcscpy(FinalPath, Path);
	wcscat(FinalPath, GalacyHeader.GalacyInfoName);
	pTestGFile = _wfopen(FinalPath, L"wb+");
	fwrite(&GalacyHeader, 1, sizeof(GALACYHEADER), pTestGFile);
	fclose(pTestGFile);

	pTestGFile = NULL;
	wcscpy(FinalPath, Path);
	wcscat(FinalPath, GalacyHeader.SystemSimpleName);
	pTestGFile = _wfopen(FinalPath, L"wb+");
	fwrite(pTestSy_SimpleData, SystemSum, sizeof(SIMPLESYSTEM), pTestGFile);
	fclose(pTestGFile);

	pTestGFile = NULL;
	wcscpy(FinalPath, Path);
	wcscat(FinalPath, GalacyHeader.SystemInfoName);
	pTestGFile = _wfopen(FinalPath, L"wb+");
	fwrite(pTestSy_InfoData, SystemSum, sizeof(SYSTEMINFO), pTestGFile);
	fclose(pTestGFile);

	pTestGFile = NULL;
	wcscpy(FinalPath, Path);
	wcscat(FinalPath, GalacyHeader.PlanetSimpleName);
	pTestGFile = _wfopen(FinalPath, L"wb+");
	fwrite(pTestPl_SimpleData, PlanetSum, sizeof(SIMPLEPLANET), pTestGFile);
	fclose(pTestGFile);

	pTestGFile = NULL;
	wcscpy(FinalPath, Path);
	wcscat(FinalPath, GalacyHeader.PlanetInfoName);
	pTestGFile = _wfopen(FinalPath, L"wb+");
	fwrite(pTestPl_InfoData, PlanetSum, sizeof(PLANETINFO), pTestGFile);
	fclose(pTestGFile);

	pTestGFile = NULL;
	wcscpy(FinalPath, Path);
	wcscat(FinalPath, GalacyHeader.AsteroidSimpleName);
	pTestGFile = _wfopen(FinalPath, L"wb+");
	fwrite(pTestAs_SimpleData, AsteroidSum, sizeof(SIMPLEASTEROID), pTestGFile);
	fclose(pTestGFile);

	pTestGFile = NULL;
	wcscpy(FinalPath, Path);
	wcscat(FinalPath, GalacyHeader.AsteroidInfoName);
	pTestGFile = _wfopen(FinalPath, L"wb+");
	fwrite(pTestAs_InfoData, AsteroidSum, sizeof(ASTEROIDINFO), pTestGFile);
	fclose(pTestGFile);

//////////////////////////////////////////////////////////////////////////

	return res;
}

static void	RandomSystemName(WCHAR *pName)
{
	long MaxNum = 60;
	long i, j;
	do
	{
		i = MaxNum*rand()/RAND_MAX;
		j = MaxNum*rand()/RAND_MAX;
		if(GroupSign[i*MYMAXCHAR+j]==0)
		{
			pName[0] = Group1[i];	pName[1] = Group2[j];
			GroupSign[i*MYMAXCHAR+j] = 1;
			break;
		}
//		else if(GroupSign[i*MYMAXCHAR+j]==1)
//		{
//			pName[0] = Group1[i];	pName[1] = Group2[j];	wcscpy(pName+2, L"二");
//			GroupSign[i*MYMAXCHAR+j] = 2;
//			break;
//		}
	}
	while(1);



}
static LRESULT	InitSysInfo()
{
	LRESULT res=LOK;
	long i, j, offsetX, offsetY=0, Gara2 = GALACYWI*GALACYWI/4, CenRa2 = Gara2*0.5, SystemNum=0, PlanetNum=0, Asteroid=0;
	short PosiX, PosiY, PosiZ;
	SIMPLESYSTEM	*pSy_Simple	= pTestSy_SimpleData;			//Test System
	SYSTEMINFO		*pSy_Info	= pTestSy_InfoData;
	
	for (i=0; i<GALACYWI; i++, offsetY+=SYSTEMRANGE)
	{
		offsetX = 0;		
		for (j=0; j<GALACYWI; j++, pSy_Simple++, pSy_Info++, offsetX+=SYSTEMRANGE, SystemNum++)
		{
			long dd, Pln, Asn, dx0, dy0;

			dx0 = j - GALACYWI/2;
			dy0 = i - GALACYWI/2;
			PosiX = LH_ROUND(SYSTEMRANGE * rand()/RAND_MAXF);	
			PosiY = LH_ROUND(SYSTEMRANGE * rand()/RAND_MAXF);
			PosiX += offsetX;
			PosiY += offsetY;
			dd = dx0*dx0 + dy0*dy0;
			if (dd<=CenRa2)
			{
				RandomSystemName(pSy_Info->SystemName);
				PosiZ = LH_ROUND(SYSTEMRANGE * rand()/RAND_MAXF);
				pSy_Simple->PosiX = PosiX;	pSy_Simple->PosiY = PosiY;	pSy_Simple->PosiZ = PosiZ;
				pSy_Simple->SystemID = SystemNum;
				pSy_Info->PosiX = PosiX;	pSy_Info->PosiY = PosiY;	pSy_Info->PosiZ = PosiZ;
				pSy_Info->SystemID = SystemNum;
				Pln = CT_Pla_Num.MinValue + LH_ROUND((CT_Pla_Num.MaxValue - CT_Pla_Num.MinValue) * rand()/RAND_MAXF);
				pSy_Info->PlanetNum = Pln;
				pSy_Info->PlanetID = PlanetSum;
				PlanetSum += Pln;
				Asn = CT_Ast_Num.MinValue + LH_ROUND((CT_Ast_Num.MaxValue - CT_Ast_Num.MinValue) * rand()/RAND_MAXF);
				pSy_Info->AsteroidNum = Asn;
				pSy_Info->AsteroidID = AsteroidSum;
				AsteroidSum += Asn;		
				wcscpy(pSy_Simple->SystemName, pSy_Info->SystemName);
			}
			else if(dd<=Gara2)
			{
				RandomSystemName(pSy_Info->SystemName);
				PosiZ = LH_ROUND(SYSTEMRANGE * rand()/RAND_MAXF);
				pSy_Simple->PosiX = PosiX;	pSy_Simple->PosiY = PosiY;	pSy_Simple->PosiZ = PosiZ;
				pSy_Simple->SystemID = SystemNum;
				pSy_Info->PosiX = PosiX;	pSy_Info->PosiY = PosiY;	pSy_Info->PosiZ = PosiZ;
				pSy_Info->SystemID = SystemNum;
				Pln = NS_Pla_Num.MinValue + LH_ROUND((NS_Pla_Num.MaxValue - NS_Pla_Num.MinValue) * rand()/RAND_MAXF);
				pSy_Info->PlanetNum = Pln;
				pSy_Info->PlanetID = PlanetSum;
				PlanetSum += Pln;
				Asn = NS_Ast_Num.MinValue + LH_ROUND((NS_Ast_Num.MaxValue - NS_Ast_Num.MinValue) * rand()/RAND_MAXF);
				pSy_Info->AsteroidNum = Asn;
				pSy_Info->AsteroidID = AsteroidSum;
				AsteroidSum += Asn;	
				wcscpy(pSy_Simple->SystemName, pSy_Info->SystemName);
				if(dx0 == 0)
				{
					if(dy0>0)
						pSy_Simple->Nation = NATION_WATCHER;
					else
						pSy_Simple->Nation = NATION_REBIRTHER;
				}
				else
				{
					if(dx0<0 && dy0>(dx0*-0.57735))
						pSy_Simple->Nation = NATION_WATCHER;
					else if(dx0<0 && dy0<=(dx0*-0.57735) && dy0>(dx0*0.57735))
						pSy_Simple->Nation = NATION_FREEUNION;
					else if(dx0<0 && dy0<(dx0*0.57735))
						pSy_Simple->Nation = NATION_REBIRTHER;
					else if(dx0>0 && dy0<(dx0*-0.57735))
						pSy_Simple->Nation = NATION_BELIEVER;
					else if(dx0>0 && dy0>=(dx0*-0.57735) && dy0<(dx0*0.57735))
						pSy_Simple->Nation = NATION_RUBY;
					else
						pSy_Simple->Nation = NATION_TRAVELER;
				}
				pSy_Info->Nation = pSy_Simple->Nation;
			}
		}
	}

	return res;
}

static  LRESULT SysSet()
{
	LRESULT res=LOK;
	long i, j, offsetX, offsetY, Off, Gara2 = GALACYWI*GALACYWI, CenRa2 = Gara2*0.5, SystemNum=0, PlanetNum=0, Asteroid=0;
	short PosiX, PosiY, PosiZ, Ra;
	SIMPLESYSTEM	*pSy_Simple	= pTestSy_SimpleData;			//Test System
	SYSTEMINFO		*pSy_Info	= pTestSy_InfoData;
	double PIpa = 3.1415626535/180;
	CenRa2 = sqrt((double)CenRa2);
	Ra = LH_ROUND((CenRa2+(GALACYWI-CenRa2)*0.5)*0.5);
	offsetX = LH_ROUND(Ra*sin(-30*PIpa));		offsetY = LH_ROUND(Ra*cos(-30*PIpa));
	offsetX += GALACYWI/2;			offsetY += GALACYWI/2;
	Off = offsetY*GALACYWI + offsetX;
	pSy_Simple = pTestSy_SimpleData + Off;
	pSy_Info = pTestSy_InfoData + Off;
	if(pSy_Simple->Nation != NATION_WATCHER)
		return 301;
	else
	{
		pSy_Simple->State |= SYS_STATE_CAPITAL;
		pSy_Info->State |= SYS_STATE_CAPITAL;
		wcscpy(pSy_Info->SystemName,L"太阳系");
		wcscpy(pSy_Simple->SystemName, pSy_Info->SystemName);
	}

	offsetX = LH_ROUND(Ra*sin(-90*PIpa));		offsetY = LH_ROUND(Ra*cos(-90*PIpa));
	offsetX += GALACYWI/2;			offsetY += GALACYWI/2;
	Off = offsetY*GALACYWI + offsetX;
	pSy_Simple = pTestSy_SimpleData + Off;
	pSy_Info = pTestSy_InfoData + Off;
	if(pSy_Simple->Nation != NATION_FREEUNION)
		return 302;
	else
	{
		pSy_Simple->State |= SYS_STATE_CAPITAL;
		pSy_Info->State |= SYS_STATE_CAPITAL;
		wcscpy(pSy_Info->SystemName,L"普罗米修斯");
		wcscpy(pSy_Simple->SystemName, pSy_Info->SystemName);
	}

	offsetX = LH_ROUND(Ra*sin(-150*PIpa));		offsetY = LH_ROUND(Ra*cos(-150*PIpa));
	offsetX += GALACYWI/2;			offsetY += GALACYWI/2;
	Off = offsetY*GALACYWI + offsetX;
	pSy_Simple = pTestSy_SimpleData + Off;
	pSy_Info = pTestSy_InfoData + Off;
	if(pSy_Simple->Nation != NATION_REBIRTHER)
		return 303;
	else
	{
		pSy_Simple->State |= SYS_STATE_CAPITAL;
		pSy_Info->State |= SYS_STATE_CAPITAL;
		wcscpy(pSy_Info->SystemName,L"伊甸");
		wcscpy(pSy_Simple->SystemName, pSy_Info->SystemName);
	}

	offsetX = LH_ROUND(Ra*sin(-210*PIpa));		offsetY = LH_ROUND(Ra*cos(-210*PIpa));
	offsetX += GALACYWI/2;			offsetY += GALACYWI/2;
	Off = offsetY*GALACYWI + offsetX;
	pSy_Simple = pTestSy_SimpleData + Off;
	pSy_Info = pTestSy_InfoData + Off;
	if(pSy_Simple->Nation != NATION_BELIEVER)
		return 304;
	else
	{
		pSy_Simple->State |= SYS_STATE_CAPITAL;
		pSy_Info->State |= SYS_STATE_CAPITAL;
		wcscpy(pSy_Info->SystemName,L"雅西里");
		wcscpy(pSy_Simple->SystemName, pSy_Info->SystemName);
	}

	offsetX = LH_ROUND(Ra*sin(-270*PIpa));		offsetY = LH_ROUND(Ra*cos(-270*PIpa));
	offsetX += GALACYWI/2;			offsetY += GALACYWI/2;
	Off = offsetY*GALACYWI + offsetX;
	pSy_Simple = pTestSy_SimpleData + Off;
	pSy_Info = pTestSy_InfoData + Off;
	if(pSy_Simple->Nation != NATION_RUBY)
		return 305;
	else
	{
		pSy_Simple->State |= SYS_STATE_CAPITAL;
		pSy_Info->State |= SYS_STATE_CAPITAL;
		wcscpy(pSy_Info->SystemName,L"拉贾拉那星光");
		wcscpy(pSy_Simple->SystemName, pSy_Info->SystemName);
	}

	offsetX = LH_ROUND(Ra*sin(-330*PIpa));		offsetY = LH_ROUND(Ra*cos(-330*PIpa));
	offsetX += GALACYWI/2;			offsetY += GALACYWI/2;
	Off = offsetY*GALACYWI + offsetX;
	pSy_Simple = pTestSy_SimpleData + Off;
	pSy_Info = pTestSy_InfoData + Off;
	if(pSy_Simple->Nation != NATION_TRAVELER)
		return 306;
	else
	{
		pSy_Simple->State |= SYS_STATE_CAPITAL;
		pSy_Info->State |= SYS_STATE_CAPITAL;
		wcscpy(pSy_Info->SystemName,L"赫耳墨斯");
		wcscpy(pSy_Simple->SystemName, pSy_Info->SystemName);
	}

	return res;
}


#define ADDNAME(Name, j, p)								\
{														\
	wcscpy(Name, p);									\
	Name[1]	= 48+j/10;									\
	Name[2] = 48+j-j/10;								\
}
static LRESULT	InitPlaInfo()
{
	LRESULT res=LOK;
	long i, j, Ra1 = SYSTEMWIDTH/2, PlanetNum=0;
	short PosiX, PosiY;
	//////////////////////////////////////////////////////////////////////////
	pTestPl_SimpleData	= (SIMPLEPLANET*)malloc(PlanetSum*sizeof(SIMPLEPLANET));	
	memset(pTestPl_SimpleData, 0, PlanetSum*sizeof(SIMPLEPLANET));
	pTestPl_InfoData	= (PLANETINFO*)malloc(PlanetSum*sizeof(PLANETINFO));
	memset(pTestPl_InfoData, 0, PlanetSum*sizeof(PLANETINFO));
	//////////////////////////////////////////////////////////////////////////
	SIMPLEPLANET	*pPl_Simple	= pTestPl_SimpleData;			//Test System
	PLANETINFO		*pPl_Info	= pTestPl_InfoData;
	SYSTEMINFO		*pSy_Info	= pTestSy_InfoData;
	for (i=0; i<SystemSum; i++, pSy_Info++)
	{
		if(pSy_Info->PosiX>0 || pSy_Info->PosiY>0)
		{
			for (j=0; j<pSy_Info->PlanetNum; j++, pPl_Simple++, pPl_Info++, PlanetNum++)
			{
				ADDNAME(pPl_Info->PlanetName, j, L"P");
				long Ra = 300 + 100*j + LH_ROUND(50 * rand()/RAND_MAXF), angle = LH_ROUND(360 * rand()/RAND_MAXF);
				PosiX = Ra * cos(angle*C2PI) + Ra1;
				PosiY = Ra * sin(angle*C2PI) + Ra1;

				pPl_Info->PosiX = PosiX;	pPl_Info->PosiY = PosiY;
				pPl_Info->SystemID = i;		pPl_Info->PlanetID = PlanetNum;
				Ra = LH_ROUND(300 * rand()/RAND_MAXF);
				if(Ra<100)
					pPl_Info->Terrain = TERRAIN_SAND_HILL;
				else if(Ra<200)
					pPl_Info->Terrain = TERRAIN_GRASS_FOREST;
				else
					pPl_Info->Terrain = TERRAIN_LAND_OCEAN;
				
				if(0 == pSy_Info->Nation)
				{
					long PlanetSize = CT_Pla_Size.MinValue + LH_ROUND((CT_Pla_Size.MaxValue - CT_Pla_Size.MinValue) * rand()/RAND_MAXF);
					InitGroundInfo(&PlanetSize, pPl_Info->GroundInfo, CT_Pla_Pro, CT_Pla_Area, CT_Pla_Value, 
						&(pPl_Simple->SourceReserve), &(pPl_Info->Area));
					pPl_Info->Width = PlanetSize;
					pPl_Info->Height = PlanetSize;					
				}
				else
				{
					long PlanetSize = NS_Pla_Size.MinValue + LH_ROUND((NS_Pla_Size.MaxValue - NS_Pla_Size.MinValue) * rand()/RAND_MAXF);
					InitGroundInfo(&PlanetSize, pPl_Info->GroundInfo, NS_Pla_Pro, NS_Pla_Area, NS_Pla_Value, 
						&(pPl_Simple->SourceReserve), &(pPl_Info->Area));
					pPl_Info->Width = PlanetSize;
					pPl_Info->Height = PlanetSize;					
				}
				pPl_Simple->PosiX = pPl_Info->PosiX;
				pPl_Simple->PosiY = pPl_Info->PosiY;
				pPl_Simple->Width = pPl_Info->Width;
				pPl_Simple->Height = pPl_Info->Height;
				pPl_Simple->Area = pPl_Info->Area;
				pPl_Simple->PlanetID = pPl_Info->PlanetID;
				pPl_Simple->SystemID = pPl_Info->SystemID;
				wcscpy(pPl_Simple->PlanetName, pPl_Info->PlanetName);
			}

		}
	}
	return res;
}

static LRESULT	InitAstInfo()
{
	LRESULT res=LOK;
	long i, j, Ra1 = SYSTEMWIDTH/2, AsteroidNum=0;
	short PosiX, PosiY;
	//////////////////////////////////////////////////////////////////////////
	pTestAs_SimpleData	= (SIMPLEASTEROID*)malloc(AsteroidSum*sizeof(SIMPLEASTEROID));	
	memset(pTestAs_SimpleData, 0, AsteroidSum*sizeof(SIMPLEASTEROID));
	pTestAs_InfoData	= (ASTEROIDINFO*)malloc(AsteroidSum*sizeof(ASTEROIDINFO));
	memset(pTestAs_InfoData, 0, AsteroidSum*sizeof(ASTEROIDINFO));
	//////////////////////////////////////////////////////////////////////////
	SIMPLEASTEROID	*pAs_Simple	= pTestAs_SimpleData;			//Test System
	ASTEROIDINFO	*pAs_Info	= pTestAs_InfoData;
	SYSTEMINFO		*pSy_Info	= pTestSy_InfoData;
	for (i=0; i<SystemSum; i++, pSy_Info++)
	{
		if(pSy_Info->PosiX>0 || pSy_Info->PosiY>0)
		{
			for (j=0; j<pSy_Info->AsteroidNum; j++, pAs_Simple++, pAs_Info++, AsteroidNum++)
			{
				ADDNAME(pAs_Info->AsteroidName, j, L"A");
				long Ra = 350 + 100*j + LH_ROUND(50 * rand()/RAND_MAXF), angle = LH_ROUND(360 * rand()/RAND_MAXF);
				PosiX = Ra * cos(angle*C2PI) + Ra1;
				PosiY = Ra * sin(angle*C2PI) + Ra1;

				pAs_Info->PosiX = PosiX;	pAs_Info->PosiY = PosiY;
				pAs_Info->SystemID = i;		pAs_Info->AsteroidID = AsteroidNum;
				pAs_Info->Terrain = TERRAIN_SAND_HILL;
								
				if(0 == pSy_Info->Nation)
				{
					long AsteroidSize = CT_Ast_Size.MinValue + LH_ROUND((CT_Ast_Size.MaxValue - CT_Ast_Size.MinValue) * rand()/RAND_MAXF);
					InitGroundInfo(&AsteroidSize, pAs_Info->GroundInfo, CT_Ast_Pro, CT_Ast_Area, CT_Ast_Value, 
						&(pAs_Simple->SourceReserve), &(pAs_Info->Area));
					pAs_Info->Width = AsteroidSize;
					pAs_Info->Height = AsteroidSize;			
				}
				else
				{
					long AsteroidSize = NS_Ast_Size.MinValue + LH_ROUND((NS_Ast_Size.MaxValue - NS_Ast_Size.MinValue) * rand()/RAND_MAXF);
					InitGroundInfo(&AsteroidSize, pAs_Info->GroundInfo, NS_Ast_Pro, NS_Ast_Area, NS_Ast_Value, 
						&(pAs_Simple->SourceReserve), &(pAs_Info->Area));
					pAs_Info->Width = AsteroidSize;
					pAs_Info->Height = AsteroidSize;					
				}
				pAs_Simple->PosiX = pAs_Info->PosiX;
				pAs_Simple->PosiY = pAs_Info->PosiY;
				pAs_Simple->Width = pAs_Info->Width;
				pAs_Simple->Height = pAs_Info->Height;
				pAs_Simple->Area = pAs_Info->Area;
				pAs_Simple->PlanetID = pAs_Info->AsteroidID;
				pAs_Simple->SystemID = pAs_Info->SystemID;
				wcscpy(pAs_Simple->AsteroidName, pAs_Info->AsteroidName);
			}
		}
	}
	return res;
}

static void RandSide(short Wid, short *px, short *py)
{
	short Side;// left, right, top, bottom
	Side = rand()%4;
	switch(Side)
	{
	case 0:
		*px = 0;
		*py = Wid * rand()/RAND_MAX;
		break;
	case 1:
		*px = Wid - 1;
		*py = Wid * rand()/RAND_MAX;
		break;
	case 2:
		*px = Wid * rand()/RAND_MAX;
		*py = 0;
		break;
	case 3:
		*px = Wid * rand()/RAND_MAX;
		*py = Wid - 1;
		break;
	}
}
				
static LRESULT	InitResourceInfo(short Wid, short startx, short starty, GROUNDINFO *pGround, RESOURCEGROUP16 Pro, RESOURCEGROUP_RANGE Area, RESOURCEGROUP_RANGE Value, RESOURCEGROUP32 *pSourceReserve)
{
	LRESULT res = LOK;
	short Num, existence, i, x, y;
	RANGE *pCurRan;
	GROUNDINFO *pCurG;
	memset(pSourceReserve, 0, sizeof(RESOURCEGROUP32));
	///////////////////////////////Heavy Metal//////////////////////////////
	pCurRan = &Area.HeavyMetal;
	Num = pCurRan->MinValue + LH_ROUND((pCurRan->MaxValue - pCurRan->MinValue) * rand()/RAND_MAXF);
	pCurRan = &Value.HeavyMetal;
	for(i=0; i<Num; i++)
	{
		RandSide(Wid, &x, &y);
		pCurG = pGround + (y+starty)*MAXGROUNDWID+x+startx;
		while(pCurG->SourceType != RESOURCE_NONE)
		{
			RandSide(Wid, &x, &y);
			pCurG = pGround + (y+starty)*MAXGROUNDWID+x+startx;
		}
		pCurG->SourceType = RESOURCE_HEAVYMETAL;
		pCurG->SourceValue = pCurRan->MinValue + LH_ROUND((pCurRan->MaxValue - pCurRan->MinValue) * rand()/RAND_MAXF);
		pSourceReserve->HeavyMetal += pCurG->SourceValue;
	}
	///////////////////////////////Nonmetal//////////////////////////////
	pCurRan = &Area.NonMetal;
	Num = pCurRan->MinValue + LH_ROUND((pCurRan->MaxValue - pCurRan->MinValue) * rand()/RAND_MAXF);
	pCurRan = &Value.NonMetal;
	for(i=0; i<Num; i++)
	{
		RandSide(Wid, &x, &y);
		pCurG = pGround + (y+starty)*MAXGROUNDWID+x+startx;
		while(pCurG->SourceType != RESOURCE_NONE)
		{
			RandSide(Wid, &x, &y);
			pCurG = pGround + (y+starty)*MAXGROUNDWID+x+startx;
		}
		pCurG->SourceType = RESOURCE_NONMETAL;
		pCurG->SourceValue = pCurRan->MinValue + LH_ROUND((pCurRan->MaxValue - pCurRan->MinValue) * rand()/RAND_MAXF);
		pSourceReserve->NonMetal += pCurG->SourceValue;
	}
	///////////////////////////////Nuclear//////////////////////////////
	existence = rand()/RAND_MAXF;
	if(existence<Pro.Nuclear)
	{
		pCurRan = &Area.Nuclear;
		Num = pCurRan->MinValue + LH_ROUND((pCurRan->MaxValue - pCurRan->MinValue) * rand()/RAND_MAXF);
		pCurRan = &Value.Nuclear;
		RandSide(Wid, &x, &y);
		pCurG = pGround + (y+starty)*MAXGROUNDWID+x+startx;
		for(i=0; i<Num; i++)
		{
			while(pCurG->SourceType != RESOURCE_NONE)
			{
				RandSide(Wid, &x, &y);
				pCurG = pGround + (y+starty)*MAXGROUNDWID+x+startx;
			}
			pCurG->SourceType = RESOURCE_NONMETAL;
			pCurG->SourceValue = pCurRan->MinValue + LH_ROUND((pCurRan->MaxValue - pCurRan->MinValue) * rand()/RAND_MAXF);
			pSourceReserve->Nuclear += pCurG->SourceValue;
		}
	}
	///////////////////////////////Raremetal//////////////////////////////
	existence = rand()/RAND_MAXF;
	if(existence<Pro.RareMetal)
	{
		pCurRan = &Area.RareMetal;
		Num = pCurRan->MinValue + LH_ROUND((pCurRan->MaxValue - pCurRan->MinValue) * rand()/RAND_MAXF);
		pCurRan = &Value.RareMetal;
		RandSide(Wid, &x, &y);
		pCurG = pGround + (y+starty)*MAXGROUNDWID+x+startx;
		for(i=0; i<Num; i++)
		{
			while(pCurG->SourceType != RESOURCE_NONE)
			{
				RandSide(Wid, &x, &y);
				pCurG = pGround + (y+starty)*MAXGROUNDWID+x+startx;
			}
			pCurG->SourceType = RESOURCE_NONMETAL;
			pCurG->SourceValue = pCurRan->MinValue + LH_ROUND((pCurRan->MaxValue - pCurRan->MinValue) * rand()/RAND_MAXF);
			pSourceReserve->RareMetal += pCurG->SourceValue;
		}
	}
	///////////////////////////////Superconductor//////////////////////////////
	existence = rand()/RAND_MAXF;
	if(existence<Pro.Superconductor)
	{
		pCurRan = &Area.Superconductor;
		Num = pCurRan->MinValue + LH_ROUND((pCurRan->MaxValue - pCurRan->MinValue) * rand()/RAND_MAXF);
		pCurRan = &Value.Superconductor;
		RandSide(Wid, &x, &y);
		pCurG = pGround + (y+starty)*MAXGROUNDWID+x+startx;
		for(i=0; i<Num; i++)
		{
			while(pCurG->SourceType != RESOURCE_NONE)
			{
				RandSide(Wid, &x, &y);
				pCurG = pGround + (y+starty)*MAXGROUNDWID+x+startx;
			}
			pCurG->SourceType = RESOURCE_NONMETAL;
			pCurG->SourceValue = pCurRan->MinValue + LH_ROUND((pCurRan->MaxValue - pCurRan->MinValue) * rand()/RAND_MAXF);
			pSourceReserve->Superconductor += pCurG->SourceValue;
		}
	}
	///////////////////////////////Precious//////////////////////////////
	existence = rand()/RAND_MAXF;
	if(existence<Pro.Precious)
	{
		pCurRan = &Area.Precious;
		Num = pCurRan->MinValue + LH_ROUND((pCurRan->MaxValue - pCurRan->MinValue) * rand()/RAND_MAXF);
		pCurRan = &Value.Precious;
		RandSide(Wid, &x, &y);
		pCurG = pGround + (y+starty)*MAXGROUNDWID+x+startx;
		for(i=0; i<Num; i++)
		{
			while(pCurG->SourceType != RESOURCE_NONE)
			{
				RandSide(Wid, &x, &y);
				pCurG = pGround + (y+starty)*MAXGROUNDWID+x+startx;
			}
			pCurG->SourceType = RESOURCE_NONMETAL;
			pCurG->SourceValue = pCurRan->MinValue + LH_ROUND((pCurRan->MaxValue - pCurRan->MinValue) * rand()/RAND_MAXF);
			pSourceReserve->Precious += pCurG->SourceValue;
		}
	}
	///////////////////////////////LifeCristal//////////////////////////////
	existence = rand()/RAND_MAXF;
	if(existence<Pro.LifeCristal)
	{
		pCurRan = &Area.LifeCristal;
		Num = pCurRan->MinValue + LH_ROUND((pCurRan->MaxValue - pCurRan->MinValue) * rand()/RAND_MAXF);
		pCurRan = &Value.LifeCristal;
		RandSide(Wid, &x, &y);
		pCurG = pGround + (y+starty)*MAXGROUNDWID+x+startx;
		for(i=0; i<Num; i++)
		{
			while(pCurG->SourceType != RESOURCE_NONE)
			{
				RandSide(Wid, &x, &y);
				pCurG = pGround + (y+starty)*MAXGROUNDWID+x+startx;
			}
			pCurG->SourceType = RESOURCE_NONMETAL;
			pCurG->SourceValue = pCurRan->MinValue + LH_ROUND((pCurRan->MaxValue - pCurRan->MinValue) * rand()/RAND_MAXF);
			pSourceReserve->LifeCristal += pCurG->SourceValue;
		}
	}
	return res;
}

static LRESULT	InitGroundInfo(long *pWid, GROUNDINFO *pGround, RESOURCEGROUP16 rPro, RESOURCEGROUP_RANGE rArea, RESOURCEGROUP_RANGE rValue, 
							   RESOURCEGROUP32 *pSourceReserve, long *pTrueArea)
{
	LRESULT res = LOK;
	short Area, Area0, Areadif;
	short i, j, x, y, Wid0;
	GROUNDINFO *pCurG;
	Wid0 = *pWid;
	Area = Wid0*Wid0;
	Wid0 = Wid0+1;	
//	Wid0 = (Wid0+1)>>1<<1;
	Wid0 = min(MAXGROUNDWID-2, Wid0);
	Area0 = Wid0*Wid0;
	*pWid = Wid0+2;

	Area += (Area0-Area)*rand()/RAND_MAX;
	*pTrueArea = Area;
	for (i=0; i<MAXGROUNDWID; i++)
	{
		pCurG = pGround + i*MAXGROUNDWID;
		for (j=0; j<MAXGROUNDWID; j++, pCurG++)
		{
			pCurG->SourceType = RESOURCE_UNBUILD;
		}
	}

	for (i=0; i<Wid0; i++)
	{
		pCurG = pGround + i*MAXGROUNDWID;
		for (j=0; j<Wid0; j++, pCurG++)
		{
			pCurG->SourceType = RESOURCE_NONE;
		}
	}	
	InitResourceInfo(Wid0, 0, 0, pGround, rPro, rArea, rValue, pSourceReserve);
	Areadif = Area0 - Area;
	for (i=0; i<Areadif; i++)
	{
		do 
		{
			x = Wid0*rand()/RAND_MAX;
			y = Wid0*rand()/RAND_MAX;
			pCurG = pGround + y*MAXGROUNDWID+x;
		} 
		while(pCurG->SourceType != RESOURCE_NONE);
		pCurG->SourceType = RESOURCE_UNBUILD;
	}
	
	return res;
}





// 	MByte *ptt = (MByte*)MMemAlloc(MNull, 300*1000);
// 	MLong GALACYWI = 200;
// 	for (MLong i=0; i<GALACYWI; i++)
// 	{
// 		MByte *p =ptt + i*600;
// 		for (MLong j=0; j<GALACYWI; j++, p+=3)
// 		{
// 			long angle, dx, dy, dd, Pln, Asn, dx0, dy0;
// 
// 			dx0 = j - GALACYWI/2;
// 			dy0 = i - GALACYWI/2;
// 			{
// 				if(dx0 == 0)
// 				{
// 					if(dy0>0)
// 					{p[0]=0; p[1]=0; p[2]=255;}
// 					else
// 					{p[0]=0; p[1]=255; p[2]=255;}
// 				}
// 				else
// 				{
// 					if(dx0<0 && dy0>(dx0*-0.57735))
// 					{p[0]=0; p[1]=0; p[2]=255;}
// 					else if(dx0<0 && dy0<=(dx0*-0.57735) && dy0>(dx0*0.57735))
// 					{p[0]=255; p[1]=0; p[2]=255;}
// 					else if(dx0<0 && dy0<(dx0*0.57735))
// 					{p[0]=0; p[1]=255; p[2]=255;}
// 					else if(dx0>0 && dy0<(dx0*-0.57735))
// 					{p[0]=0; p[1]=255; p[2]=0;}
// 					else if(dx0>0 && dy0>=(dx0*-0.57735) && dy0<(dx0*0.57735))
// 					{p[0]=255; p[1]=0; p[2]=0;}
// 					else
// 					{p[0]=255; p[1]=255; p[2]=0;}
// 				}
// 			}
// 		}
// 	}
// 	SaveBMP("D:/tttt.bmp", ptt, GALACYWI, GALACYWI, 24);
//	MMemFree(MNull, ptt);