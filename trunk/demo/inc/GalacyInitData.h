#include "neerr.h"
#include "NewEraValue.h"


RANGE				NS_Pla_Num		= {4, 6};//Nation System Planet NumRange
RANGE				CT_Pla_Num		= {5, 8};//Center System Planet NumRange

RANGE				NS_Ast_Num		= {2, 6};//Nation System Asteroid NumRange
RANGE				CT_Ast_Num		= {5, 19};//Center System Asteroid NumRange

RANGE				NS_Pla_Size		= {9, 11};//Nation System Planet SizeRange
RANGE				CT_Pla_Size		= {12, 14};//Center System Planet SizeRange

RANGE				NS_Ast_Size		= {5, 7};//Nation System Asteroid SizeRange
RANGE				CT_Ast_Size		= {6, 8};//Center System Asteroid SizeRange

RESOURCEGROUP16		NS_Pla_Pro		={//Nation System Planet Resource Probability
	100,	100,	100,	15,		4,		4,		0,		0
};
RESOURCEGROUP16		CT_Pla_Pro		={//Center System Planet Resource Probability
	100,	100,	100,	30,		8,		8,		0,		0
};
RESOURCEGROUP16		NS_Ast_Pro		={//Nation System Asteroid Resource Probability
	100,	100,	100,	45,		5,		5,		0,		0
};
RESOURCEGROUP16		CT_Ast_Pro		={//Center System Asteroid Resource Probability
	100,	100,	100,	50,		10,		10,		0,		0
};

RESOURCEGROUP_RANGE		NS_Pla_Area		={//Nation System Planet Resource Area
	3,	5,
	3,	5,
	2,	4,
	1,	2,
	1,	1,
	1,	1,
	0,	0,
	0,	0
};
RESOURCEGROUP_RANGE		CT_Pla_Area		={//Center System Planet Resource Area
	6,	10,
	6,	10,
	4,	8,
	2,	4,
	1,	2,
	1,	2,
	0,	0,
	0,	0
};
RESOURCEGROUP_RANGE		NS_Ast_Area		={//Nation System Asteroid Resource Area
	1,	3,
	1,	3,
	1,	1,
	1,	1,
	1,	1,
	1,	1,
	0,	0,
	0,	0}
;
RESOURCEGROUP_RANGE		CT_Ast_Area		={//Center System Asteroid Resource Area
	2,	4,
	2,	4,
	1,	2,
	1,	1,
	1,	1,
	1,	1,
	0,	0,
	0,	0
};

RESOURCEGROUP_RANGE		NS_Pla_Value	={//Nation System Planet Resource Value
	6,	8,
	10,	14,
	6,	8,
	3,	6,
	1,	2,
	1,	2,
	0,	0,
	0,	0
};
RESOURCEGROUP_RANGE		CT_Pla_Value	={//Center System Planet Resource Value
	8,	14,
	14,	22,
	8,	14,
	6,	10,
	3,	6,
	3,	6,
	0,	0,
	0,	0
};
RESOURCEGROUP_RANGE		NS_Ast_Value	={//Nation System Asteroid Resource Value
	6,	8,
	6,	8,
	6,	8,
	3,	4,
	3,	4,
	1,	2,
	0,	0,
	0,	0}
;
RESOURCEGROUP_RANGE		CT_Ast_Value	={//Center System Asteroid Resource Value
	8,	14,
	8,	14,
	8,	14,
	6,	10,
	3,	6,
	3,	6,
	0,	0,
	0,	0
};


WCHAR	*Group1=L"五六八九百千追艾宝参迪底灭地飞纷黑群安皆国甲卷结卡丽雷昆莱行矛念张火破左燃齐乾韧白伯仲素太统光水诺猛勾星恒闪东西南北中炎";
WCHAR	*Group2=L"蝶盾琴蚕豹界缥楼子约盘屏普沛境鹿龙皇琼躯聂河珠魂海兽幽冥祖词贡瑟座松尊器琴河人让容港莲格妃伞塔廷陀同祭林山花月晓芙蓉曼罗";