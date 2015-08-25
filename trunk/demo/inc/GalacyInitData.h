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


WCHAR	*Group1=L"�����˾Ű�ǧ׷�����εϵ���طɷ׺�Ⱥ���Թ��׾�Ῠ����������ì���Ż�����ȼ��Ǭ�Ͱײ�����̫ͳ��ˮŵ�͹��Ǻ��������ϱ�����";
WCHAR	*Group2=L"�����ٲϱ�����¥��Լ�������澳¹��������������꺣����ڤ��ʹ�ɪ���������ٺ������ݸ�������ɡ��͢��ͬ����ɽ������ܽ������";