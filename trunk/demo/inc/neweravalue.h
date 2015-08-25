#if !defined(_NEWERAVALUE_H_)
#define _NEWERAVALUE_H_
#include "neerr.h"


#define MAINWINDOW_WIDTH    1024  // size of screen
#define MAINWINDOW_HEIGHT   768

#define SYSTEMRANGE			100

#define SYSTEMWIDTH			4000

#define MAXGROUNDWID		16//GroundInfo Line

#define MAXCONNECTCOM		64

#define MAXFRAMENUM			40

#define FRAMETIME			1000/MAXFRAMENUM

#define	DESIGNSTYLE_HEAVYMATEL		0x01
#define DESIGNSTYLE_STREAMLINE		0x02
#define DESIGNSTYLE_CLASSICAL		0x03
#define PROFESSION_MERCHANT			0x01
#define PROFESSION_SMUGGLER			0x02
#define PROFESSION_COMMANDO			0x03
#define PROFESSION_GUARD			0x04
#define NATION_WATCHER				0x01
#define NATION_FREEUNION			0x02
#define NATION_RUBY					0x03
#define NATION_REBIRTHER			0x04
#define NATION_BELIEVER				0x05
#define NATION_TRAVELER				0x06

#define	TERRAIN_SAND_HILL			0x01
#define	TERRAIN_GRASS_FOREST		0x02
#define	TERRAIN_LAND_OCEAN			0x03

#define	RESOURCE_NONE				0x00
#define	RESOURCE_HEAVYMETAL			0x01
#define	RESOURCE_NONMETAL			0x02
#define	RESOURCE_NUCLEAR			0x03
#define	RESOURCE_RAREMETAL			0x04
#define	RESOURCE_SUPERCONDUCTOR		0x05
#define	RESOURCE_PRECIOUS			0x06
#define	RESOURCE_LIFECRISTAL		0x07
#define	RESOURCE_UNBUILD			0x08


#define SYS_STATE_NORMAL			0x01
#define SYS_STATE_CAPITAL			(0x01<<1)
#define SYS_STATE_PROTECTED			(0x01<<2)
#define SYS_STATE_SS				(0x01<<3)
#define SYS_STATE_DANGER			(0x01<<4)
#define SYS_STATE_CURRENTTAR		(0x01<<5)//Target Positon

#define BUI_ACT_BUILD				0x01
#define	BUI_ACT_UPGRADE				0x02
#define	BUI_ACT_DOWNGRADE			0x03
#define	BUI_ACT_DESTORY				0x04

#define BUILDING_ID_NONE			0x00
#define BUILDING_ID_CONSTRUCTION	BUILDING_ID_NONE				+1
#define BUILDING_ID_BASE			BUILDING_ID_CONSTRUCTION		+1
#define BUILDING_ID_MINE			BUILDING_ID_BASE				+1
#define BUILDING_ID_HINDUSTRY		BUILDING_ID_MINE				+1//Heavy Industry
#define BUILDING_ID_LINDUSTRY		BUILDING_ID_HINDUSTRY			+1//Light Industry
#define BUILDING_ID_POWERSTATION	BUILDING_ID_LINDUSTRY			+1
#define BUILDING_ID_SUPPLYSTATION	BUILDING_ID_POWERSTATION		+1
#define BUILDING_ID_USTC			BUILDING_ID_SUPPLYSTATION		+1
#define BUILDING_ID_WAREHOUSE		BUILDING_ID_USTC				+1
#define BUILDING_ID_REFINESTATION	BUILDING_ID_WAREHOUSE			+1
#define BUILDING_ID_ASSEMBLEPLANT	BUILDING_ID_REFINESTATION		+1
#define BUILDING_ID_CITYHALL		BUILDING_ID_ASSEMBLEPLANT		+1
#define BUILDING_ID_RESIDENTIAL		BUILDING_ID_CITYHALL			+1
#define BUILDING_ID_ENTERTAINMENT	BUILDING_ID_RESIDENTIAL			+1
#define BUILDING_ID_COMMERCIAL		BUILDING_ID_ENTERTAINMENT		+1
#define BUILDING_ID_SERVICE			BUILDING_ID_COMMERCIAL			+1
#define BUILDING_ID_EDUCATION		BUILDING_ID_SERVICE				+1

//////////////////////////////////////////////////////////////////////////

typedef	struct{
	short			MinValue;
	short			MaxValue;
}RANGE;
typedef	struct{
	short			sWidth;
	short			sHeight;
}LHSIZE;
typedef struct{
	short			HeavyMetal;
	short			NonMetal;
	short			Nuclear;
	short			RareMetal;
	short			Superconductor;
	short			Precious;
	short			LifeCristal;
	short			EnergyCristal;
}RESOURCEGROUP16;

typedef struct{
	long			HeavyMetal;
	long			NonMetal;
	long			Nuclear;
	long			RareMetal;
	long			Superconductor;
	long			Precious;
	long			LifeCristal;
	long			EnergyCristal;
}RESOURCEGROUP32;

typedef struct{
	LInt64			HeavyMetal;
	LInt64			NonMetal;
	LInt64			Nuclear;
	LInt64			RareMetal;
	LInt64			Superconductor;
	LInt64			Precious;
	LInt64			LifeCristal;
	LInt64			EnergyCristal;
}RESOURCEGROUP64;

typedef struct{
	RANGE			HeavyMetal;
	RANGE			NonMetal;
	RANGE			Nuclear;
	RANGE			RareMetal;
	RANGE			Superconductor;
	RANGE			Precious;
	RANGE			LifeCristal;
	RANGE			EnergyCristal;
}RESOURCEGROUP_RANGE;
//////////////////////////////////////////////////////////////////////////

//���ݿ⡪���ʺŵ�¼��Ϣ
typedef struct{
	WCHAR			PlayerName[20];
	WCHAR			LordName[20];
	WCHAR			PlayerCode[64];
	WCHAR			PlayerEmail[64];
	LONG			PlayerID;
	LONG			PlayerAge;
}CLIENTINFO;

//ͨ�ü���Ϣ
typedef struct  
{
	long			MsgType;
	WCHAR			Name[20];
	byte			ExpLV;
	byte			LesLV;
	short			Gender;			
}SIMPLEMANINFO;

//������ϸ��Ϣ
typedef struct  
{
	long			MsgType;
	WCHAR			LordName[20];
	short			Gender;			
	LInt64			ExpValue;			//����ֵ
	LInt64			LesValue;			//��ѵֵ
	LInt64			ExpValueNeed;		//��һ�����辭��ֵ
	LInt64			LesValueNeed;		//��һ�������ѵֵ

	byte			ExpLV;				//���鼶��
	byte			LesLV;				//��ѵ����
	byte			ExpPoint;			//�������Ե�ʣ��
	byte			LesPoint;			//��ѵ���Ե�ʣ��
	byte			Exp_Energy;			//��������_����
	byte			Exp_Intelligence;	//��������_����
	byte			Exp_Insignt;		//��ѵ����_����
	byte			Exp_Manipulation;	//��ѵ����_�ٿ�

	long			FleetID;			//ͳ�콢�Ӽ���ID

	byte			CitizenLV;			//���񼶱�
	byte			Profession;			//����ְҵ

}LORDINFO;

//������ϸ��Ϣ
typedef struct  
{
	long			MsgType;
	WCHAR			AdjutantName[20];
	short			Gender;			
	LInt64			ExpValue;
	LInt64			LesValue;
	LInt64			ExpValueNeed;
	LInt64			LesValueNeed;

	byte			ExpLV;
	byte			LesLV;
	byte			ExpPoint;
	byte			LesPoint;
	byte			Exp_Energy;
	byte			Exp_Intelligence;
	byte			Exp_Insignt;
	byte			Exp_Manipulation;
	
}ADJUTANTINFO;

//���ݿ⡪��������Ϣ
typedef struct  
{
	long			MsgType;
	long			PlayerID;			//�������ID
	byte			Nation;				//����
	byte			DesignStyle;		//ս�����
	LInt64			Money;				//�����ʲ�
	long			HonorPoint;			//������
	long			TradeCapacity;			//ó���޶�
	long			Population;			//���˿�
	long			TechnologyPoint;		//�Ƽ���
	
	SIMPLEMANINFO	LordSimple;
	LORDINFO		Lord;
	SIMPLEMANINFO	AdjutantSimple[4];
	ADJUTANTINFO	Adjutant[4];

	long			PlanetID[5];		//���Ǽ���ID
	long			AsteroidID[10];		//С���Ǽ���ID
}PLAYERINFO;

//��Ҫ��ϵ��Ϣ
typedef struct  
{
	long			MsgType;
	WCHAR			SystemName[8];
	long			SystemID;			//��ϵ����ID
	byte			GalacyID;			//�������Ӽ���ID
	byte			Nation;				//��������
	byte			ShowStyle;			//�ͻ�����ʾ����
	byte			BeFighting;			//�Ƿ���ս��				
	DWORD			State;				//Σ��/�ռ�վ/�׶�/�������ȵ�SYS_STATE_
	long			PosiZ;				//1��100
	long			PosiX;
	long			PosiY;
}SIMPLESYSTEM;

typedef struct  
{
	long			MsgType;
	short			Nation;				//��������
	short			BeFighting;			//�Ƿ���ս��				
	DWORD			State;				//Σ��/�ռ�վ/�׶�/�������ȵ�SYS_STATE_
}SYSTEMCHANGE;

typedef struct  
{
	long			MsgType;
	long			SystemNum;			//��ϵ����ID
	byte			GalacyID;			//�������Ӽ���ID
	byte			Exbuff[3];
	SIMPLESYSTEM	*pSystemSimple;
}GALACYINFO;

//������ϵ��Ϣ
typedef struct  
{
	long			MsgType;
	WCHAR			SystemName[8];
	long			SystemID;			//��ϵ����ID
	byte			GalacyID;			//�������Ӽ���ID
	byte			Nation;				//��������
	byte			ShowStyle;			//�ͻ�����ʾ����
	byte			BeFighting;			//�Ƿ���ս��
	DWORD			State;				//Σ��/�ռ�վ/�׶�/�������ȵ�SYS_STATE_
	long			PosiZ;				//1��100
	long			PosiX;
	long			PosiY;
	
	byte			BackgroundStyle;
	byte			StarStyle;
	byte			PlanetNum;
	byte			AsteroidNum;
	long			PlanetID;
	long			AsteroidID;

//	long			**ppFleetStack;

}SYSTEMINFO;

//��Ҫ������Ϣ
typedef struct  
{
	long			MsgType;
	WCHAR			PlanetName[4];
	long			PlanetID;			//�������ID
	long			SystemID;			//������ϵ����ID
	byte			GalacyID;			//�������Ӽ���ID
	byte			Nation;				//��������
	byte			ShowStyle;			//�ͻ�����ʾ����
	byte			BeFighting;			//�Ƿ���ս��
	long			PosiX;
	long			PosiY;
	byte			Width;
	byte			Height;
	long			Area;
	RESOURCEGROUP32	SourceReserve;
}SIMPLEPLANET;

//��ҪС������Ϣ
typedef struct  
{
	WCHAR			AsteroidName[4];
	long			PlanetID;			//�������ID
	long			SystemID;			//������ϵ����ID
	byte			GalacyID;			//�������Ӽ���ID
	byte			Nation;				//��������
	byte			ShowStyle;			//�ͻ�����ʾ����
	byte			BeFighting;			//�Ƿ���ս��
	long			PosiX;
	long			PosiY;
	byte			Width;
	byte			Height;
	long			Area;
	RESOURCEGROUP32	SourceReserve;
}SIMPLEASTEROID;

typedef struct  
{
	byte			SourceType;			//������Դ���ͣ�0Ϊ����Դ
	byte			SourceValue;		//��Դ������0Ϊ����Դ
	byte			BuildingType;		//�������ͣ�0Ϊ�޽���
	byte			BuildingLV;			//��������0Ϊ�޽���
}GROUNDINFO;

typedef struct  
{
	long			CargoType;			//��Ʒ���
	long			CargoNum;			//��Ʒ�����
}CARGOINFO;

typedef struct  
{
	byte			PosiX;				//����λ�ú����� 256��ʾ������װ�ռ�վ
	byte			PosiY;				//����λ��������
	byte			BuildingType;		//��������
	byte			BuildingAct;		//1 ����  ��1 ��һ���� 0ը��
	long			TimeNeed;			//����ʱ��
	__time64_t		StartTime;			//��ʼ�����ʱ��
}BUILDINGINFO;
//����������ÿ�����˷�������ʱ�������������¼�ʱ������ÿ6����Ҫˢ��Դ���ݣ��ٲ鿴�Ƿ�����ϣ����н�չ����

//����������Ϣ
typedef struct  
{
	long			MsgType;
	WCHAR			PlanetName[4];
	long			PlanetID;			//�������ID
	long			SystemID;			//������ϵ����ID
	byte			GalacyID;			//�������Ӽ���ID
	byte			Nation;				//��������
	byte			ShowStyle;			//�ͻ�����ʾ����
	byte			BeFighting;			//�Ƿ���ս��
	long			PosiX;
	long			PosiY;
	
	byte			Terrain;			//�����ò
	byte			SkyStyle;			//�����ʾ����
	byte			Width;
	byte			Height;
	long			Area;
	GROUNDINFO		GroundInfo[MAXGROUNDWID*MAXGROUNDWID];	//������Ϣ  WIdth��Height		
	
	byte			BaceLV;				//������ؼ���
	byte			BuildLimit;			//�����������
	byte			AssemblyPlantLV;	//��װ�ռ�վ����
	byte			IndustryNum;		//���ع�ҵ������<20
	long			HeavyIndsProduct;	//�Ṥҵ����
	long			LightIndsProduct;	//�ع�ҵ����
	long			TechnologyProducting;//��ǰ�Ƽ���������
	long			TechnologyProductMax;//�Ƽ�����������
	long			SupplyProducting;	//��ǰ����Ʒ������
	long			SupplyProductMax;	//�Ƽ�����Ʒ����������
	long			WareHouseCap;		//�մ�����

	__time64_t		LastSettleMentTime;	//�ϴν���ʱ��


	long			HeavyMetal;			//�ؽ�����Դ����
	long			NonMetal;			//�ǽ�����Դ����
	long			RareMetal;			//ϡ�н�����Դ����
	long			Nuclear;			//��ȼ����Դ����
	long			EnergyCristal;		//����������Դ����
	long			Superconductor;		//��������Դ����
	long			Precious;			//���ؽ�����Դ����
	long			LifeCristal;		//����������Դ����
	long			Supply;				//����Ʒ��Դ����
	long			EnergySupply;		//����֧��
	long			EnergyNeed;			//��������

	long			Garrison;			//פ������
	long			BuildPoint;			//������
	long			MaxBuildPoint;		//����������
	//BUILDINGINFO	CurrentBuilding;
	//BUILDINGINFO	pBuildingNeed[32];
	CARGOINFO		HeavyPruducting;
	CARGOINFO		LightPruducting;

//	CARGOINFO		**Cargo;//��Ʒ����ֻ������Ʋմ�	
//	CARGOINFO		**Hull;//���ǣ����Ʋմ�	

	short			CityType;			//��ҵ ��ҵ ���� ֳ���
	long			Population;			//�����˿�
	long			BusinessPopulation;	//��ҵ�˿�
	long			ServecedPopulation;	//�����˿�
	long			joyfulPopulation;	//�����˿�
	long			EducatedPopulation;	//�����˿�
	long			PopulationGrow;		//�˿�����ֵ
	
}PLANETINFO;

//����С������Ϣ
typedef struct  
{
	long			MsgType;
	WCHAR			AsteroidName[4];
	long			AsteroidID;			//�������ID
	long			SystemID;			//������ϵ����ID
	byte			GalacyID;			//�������Ӽ���ID
	byte			Nation;				//��������
	byte			ShowStyle;			//�ͻ�����ʾ����
	byte			BeFighting;			//�Ƿ���ս��
	long			PosiX;
	long			PosiY;
	
	byte			Terrain;			
	byte			SkyStyle;
	byte			Width;
	byte			Height;
	long			Area;
	GROUNDINFO		GroundInfo[MAXGROUNDWID*MAXGROUNDWID];
	
	byte			BaceLV;
	byte			BuildLimit;
	byte			AssemblyPlantLV;
	byte			IndustryNum;
	long			HeavyIndsProduct;
	long			LightIndsProduct;
	long			TechnologyProducting;
	long			TechnologyProductMax;
	long			WareHouseCap;

	__time64_t		LastSettleMentTime;	//�ϴν���ʱ��

	long			HeavyMetal;
	long			NonMetal;
	long			RareMetal;
	long			Nuclear;
	long			EnergyCristal;
	long			Superconductor;
	long			Precious;
	long			LifeCristal;

	long			Garrison;
	long			BuildPoint;			//������
	long			MaxBuildPoint;		//����������
//	BUILDINGINFO	CurrentBuilding;
//	BUILDINGINFO	pBuildingNeed[32];
	CARGOINFO		HeavyPruducting;
	CARGOINFO		LightPruducting;

//	CARGOINFO		**Cargo;	

}ASTEROIDINFO;



//���ݿ�������Ϣ
typedef struct  
{
	long			SystemNum;
	long			PlanetNum;
	long			AsteroidNum;
	SIMPLESYSTEM	*pSystemSimple;//��ʾ��Ӧ�����ݿ� ��������ָ���ʾָ��
	SYSTEMINFO		*pSystemInfo;

	ASTEROIDINFO	*pAsteroidSimple;
	SIMPLEASTEROID	*pAsteroidInfo;
	SIMPLEPLANET	*pPlanetSimple;
	PLANETINFO		*pPlanetInfo;
}GALACYINITINFO;

typedef struct  
{
	long			SystemNum;
	long			PlanetNum;
	long			AsteroidNum;
	short			GalacyWid;
	short			SystemWid;
	short			SystemRange;

	WCHAR			GalacyInfoName[256];

	WCHAR			SystemSimpleName[256];
	WCHAR			SystemInfoName[256];

	WCHAR			AsteroidSimpleName[256];
	WCHAR			AsteroidInfoName[256];
	WCHAR			PlanetSimpleName[256];
	WCHAR			PlanetInfoName[256];
}GALACYHEADER;

typedef struct{
	PLAYERINFO			MyPlayreInfo;
	SIMPLEMANINFO		MyManSimpleInfo;
	SIMPLEMANINFO		TargetManSimpleInfo;
	GALACYINFO			CurrentGalacy;
	SIMPLESYSTEM		TargetSystemSimple;
	SYSTEMINFO			CurrentSystem;
	SIMPLEPLANET		TargetPlanetSimple;
	PLANETINFO			CurrentPlanet;
	SIMPLEASTEROID		TargetAsteroidSimple;
	ASTEROIDINFO		CurrentAsteroid;	
}DISPLAYDATA;
//////////////////////////////////////////////////////////////////////////


typedef struct{
	DWORD			CurClientCom;
	WCHAR			PlayerName[20];
	WCHAR			PlayerCode[64];
}LOGINMESSANG;


typedef struct{
	DWORD			CurClientCom;
	WCHAR			PlayerName[20];
	WCHAR			PlayerCode[64];
	WCHAR			PlayerCode2[64];
	WCHAR			PlayerEmail[64];
	short			PlayerAge;
}REGISTERMESSANG;

typedef struct{
	DWORD			CurClientCom;
	WCHAR			LordName[10];
	WCHAR			Adjutant1[10];
	WCHAR			Adjutant2[10];
	WCHAR			Adjutant3[10];
	WCHAR			Adjutant4[10];
	byte			Gender;//1=male 2=female
	byte			DesignStyle;
	byte			Profession;
	byte			Nation;
}PLAYERINITMESSANG;

typedef struct{
	DWORD			CurClientCom;
	byte			PosiX;
	byte			PosiY;
	byte			ActionInfo;//BUI_ACT_
	byte			BuildingID;//BUILDING_ID_
}BUILDINFO;

typedef struct{
	DWORD			CurClientCom;
	long			RegionID;
}ENTERINFO;


typedef struct{
	LOGINMESSANG		loginMsg;
	REGISTERMESSANG		RegisterMsg;
	PLAYERINITMESSANG	MyPlayerInitMsg;
	ENTERINFO			EnterGalacy;
	ENTERINFO			EnterSystem;
	ENTERINFO			EnterPlanet;
	ENTERINFO			EnterAsteroid;

	BUILDINFO			BuildAction;

}MSGDATA;

#endif