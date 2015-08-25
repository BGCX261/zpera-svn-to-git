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

//数据库——帐号登录信息
typedef struct{
	WCHAR			PlayerName[20];
	WCHAR			LordName[20];
	WCHAR			PlayerCode[64];
	WCHAR			PlayerEmail[64];
	LONG			PlayerID;
	LONG			PlayerAge;
}CLIENTINFO;

//通用简单信息
typedef struct  
{
	long			MsgType;
	WCHAR			Name[20];
	byte			ExpLV;
	byte			LesLV;
	short			Gender;			
}SIMPLEMANINFO;

//领主详细信息
typedef struct  
{
	long			MsgType;
	WCHAR			LordName[20];
	short			Gender;			
	LInt64			ExpValue;			//经验值
	LInt64			LesValue;			//教训值
	LInt64			ExpValueNeed;		//下一级所需经验值
	LInt64			LesValueNeed;		//下一级所需教训值

	byte			ExpLV;				//经验级别
	byte			LesLV;				//教训级别
	byte			ExpPoint;			//经验属性点剩余
	byte			LesPoint;			//教训属性点剩余
	byte			Exp_Energy;			//经验属性_精力
	byte			Exp_Intelligence;	//经验属性_智力
	byte			Exp_Insignt;		//教训属性_洞察
	byte			Exp_Manipulation;	//教训属性_操控

	long			FleetID;			//统领舰队检索ID

	byte			CitizenLV;			//公民级别
	byte			Profession;			//领主职业

}LORDINFO;

//副官详细信息
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

//数据库——人物信息
typedef struct  
{
	long			MsgType;
	long			PlayerID;			//人物检索ID
	byte			Nation;				//种族
	byte			DesignStyle;		//战舰风格
	LInt64			Money;				//人物资产
	long			HonorPoint;			//荣誉点
	long			TradeCapacity;			//贸易限额
	long			Population;			//总人口
	long			TechnologyPoint;		//科技点
	
	SIMPLEMANINFO	LordSimple;
	LORDINFO		Lord;
	SIMPLEMANINFO	AdjutantSimple[4];
	ADJUTANTINFO	Adjutant[4];

	long			PlanetID[5];		//行星检索ID
	long			AsteroidID[10];		//小行星检索ID
}PLAYERINFO;

//简要星系信息
typedef struct  
{
	long			MsgType;
	WCHAR			SystemName[8];
	long			SystemID;			//星系检索ID
	byte			GalacyID;			//隶属银河检索ID
	byte			Nation;				//所属种族
	byte			ShowStyle;			//客户端显示特征
	byte			BeFighting;			//是否发生战斗				
	DWORD			State;				//危险/空间站/首都/保护区等等SYS_STATE_
	long			PosiZ;				//1～100
	long			PosiX;
	long			PosiY;
}SIMPLESYSTEM;

typedef struct  
{
	long			MsgType;
	short			Nation;				//所属种族
	short			BeFighting;			//是否发生战斗				
	DWORD			State;				//危险/空间站/首都/保护区等等SYS_STATE_
}SYSTEMCHANGE;

typedef struct  
{
	long			MsgType;
	long			SystemNum;			//星系检索ID
	byte			GalacyID;			//隶属银河检索ID
	byte			Exbuff[3];
	SIMPLESYSTEM	*pSystemSimple;
}GALACYINFO;

//具体星系信息
typedef struct  
{
	long			MsgType;
	WCHAR			SystemName[8];
	long			SystemID;			//星系检索ID
	byte			GalacyID;			//隶属银河检索ID
	byte			Nation;				//所属种族
	byte			ShowStyle;			//客户端显示特征
	byte			BeFighting;			//是否发生战斗
	DWORD			State;				//危险/空间站/首都/保护区等等SYS_STATE_
	long			PosiZ;				//1～100
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

//简要行星信息
typedef struct  
{
	long			MsgType;
	WCHAR			PlanetName[4];
	long			PlanetID;			//星球检索ID
	long			SystemID;			//隶属星系检索ID
	byte			GalacyID;			//隶属银河检索ID
	byte			Nation;				//所属种族
	byte			ShowStyle;			//客户端显示特征
	byte			BeFighting;			//是否发生战斗
	long			PosiX;
	long			PosiY;
	byte			Width;
	byte			Height;
	long			Area;
	RESOURCEGROUP32	SourceReserve;
}SIMPLEPLANET;

//简要小行星信息
typedef struct  
{
	WCHAR			AsteroidName[4];
	long			PlanetID;			//星球检索ID
	long			SystemID;			//隶属星系检索ID
	byte			GalacyID;			//隶属银河检索ID
	byte			Nation;				//所属种族
	byte			ShowStyle;			//客户端显示特征
	byte			BeFighting;			//是否发生战斗
	long			PosiX;
	long			PosiY;
	byte			Width;
	byte			Height;
	long			Area;
	RESOURCEGROUP32	SourceReserve;
}SIMPLEASTEROID;

typedef struct  
{
	byte			SourceType;			//区域资源类型，0为无资源
	byte			SourceValue;		//资源含量，0为无资源
	byte			BuildingType;		//建筑类型，0为无建筑
	byte			BuildingLV;			//建筑级别，0为无建筑
}GROUNDINFO;

typedef struct  
{
	long			CargoType;			//产品类别
	long			CargoNum;			//产品库存量
}CARGOINFO;

typedef struct  
{
	byte			PosiX;				//建筑位置横坐标 256表示建造组装空间站
	byte			PosiY;				//建筑位置纵坐标
	byte			BuildingType;		//建筑类型
	byte			BuildingAct;		//1 升级  －1 拆一级， 0炸毁
	long			TimeNeed;			//所需时间
	__time64_t		StartTime;			//开始建造的时间
}BUILDINGINFO;
//建筑升级在每次有人访问星球时，或者星球发生事件时（比如每6分钟要刷资源数据）再查看是否建设完毕，队列进展到哪

//具体行星信息
typedef struct  
{
	long			MsgType;
	WCHAR			PlanetName[4];
	long			PlanetID;			//星球检索ID
	long			SystemID;			//隶属星系检索ID
	byte			GalacyID;			//隶属银河检索ID
	byte			Nation;				//所属种族
	byte			ShowStyle;			//客户端显示特征
	byte			BeFighting;			//是否发生战斗
	long			PosiX;
	long			PosiY;
	
	byte			Terrain;			//星球地貌
	byte			SkyStyle;			//天空显示类型
	byte			Width;
	byte			Height;
	long			Area;
	GROUNDINFO		GroundInfo[MAXGROUNDWID*MAXGROUNDWID];	//地面信息  WIdth×Height		
	
	byte			BaceLV;				//星球基地级别
	byte			BuildLimit;			//建造队列上限
	byte			AssemblyPlantLV;	//组装空间站级别
	byte			IndustryNum;		//轻重工业区总数<20
	long			HeavyIndsProduct;	//轻工业产能
	long			LightIndsProduct;	//重工业产能
	long			TechnologyProducting;//当前科技点生产率
	long			TechnologyProductMax;//科技点生产上限
	long			SupplyProducting;	//当前生活品生产率
	long			SupplyProductMax;	//科技生活品点生产上限
	long			WareHouseCap;		//舱储容量

	__time64_t		LastSettleMentTime;	//上次结算时间


	long			HeavyMetal;			//重金属资源储量
	long			NonMetal;			//非金属资源储量
	long			RareMetal;			//稀有金属资源储量
	long			Nuclear;			//核燃料资源储量
	long			EnergyCristal;		//能量晶体资源储量
	long			Superconductor;		//超导矿资源储量
	long			Precious;			//贵重金属资源储量
	long			LifeCristal;		//生命晶体资源储量
	long			Supply;				//生活品资源储量
	long			EnergySupply;		//能量支持
	long			EnergyNeed;			//能量需求

	long			Garrison;			//驻军数量
	long			BuildPoint;			//建筑点
	long			MaxBuildPoint;		//建筑点上限
	//BUILDINGINFO	CurrentBuilding;
	//BUILDINGINFO	pBuildingNeed[32];
	CARGOINFO		HeavyPruducting;
	CARGOINFO		LightPruducting;

//	CARGOINFO		**Cargo;//商品、船只配件，计舱储	
//	CARGOINFO		**Hull;//船壳，不计舱储	

	short			CityType;			//工业 商业 旅游 殖民地
	long			Population;			//城市人口
	long			BusinessPopulation;	//商业人口
	long			ServecedPopulation;	//服务人口
	long			joyfulPopulation;	//娱乐人口
	long			EducatedPopulation;	//教育人口
	long			PopulationGrow;		//人口增长值
	
}PLANETINFO;

//具体小行星信息
typedef struct  
{
	long			MsgType;
	WCHAR			AsteroidName[4];
	long			AsteroidID;			//星球检索ID
	long			SystemID;			//隶属星系检索ID
	byte			GalacyID;			//隶属银河检索ID
	byte			Nation;				//所属种族
	byte			ShowStyle;			//客户端显示特征
	byte			BeFighting;			//是否发生战斗
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

	__time64_t		LastSettleMentTime;	//上次结算时间

	long			HeavyMetal;
	long			NonMetal;
	long			RareMetal;
	long			Nuclear;
	long			EnergyCristal;
	long			Superconductor;
	long			Precious;
	long			LifeCristal;

	long			Garrison;
	long			BuildPoint;			//建筑点
	long			MaxBuildPoint;		//建筑点上限
//	BUILDINGINFO	CurrentBuilding;
//	BUILDINGINFO	pBuildingNeed[32];
	CARGOINFO		HeavyPruducting;
	CARGOINFO		LightPruducting;

//	CARGOINFO		**Cargo;	

}ASTEROIDINFO;



//数据库银河信息
typedef struct  
{
	long			SystemNum;
	long			PlanetNum;
	long			AsteroidNum;
	SIMPLESYSTEM	*pSystemSimple;//表示相应的数据库 这里先用指针表示指针
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