
#include "Server_inc.h"
#include "Mylist.h"


LRESULT AddListMember(MYLIST *pMyList, int CliID)
{
	LRESULT res = LOK;
	if(!CHECKUNLOCK(pMyList->MemLock) || !CHECKUNLOCK(pMyList->Lock))
		return LIST_NEEDWAIT;
	if(pMyList->DataPosi == pMyList->CurPosi-1)
		return LIST_FULL;

	SOCKCOMLOCK(pMyList->Lock);
	int curr = pMyList->DataPosi;
	pMyList->pList[curr] = CliID;
	curr++;
	pMyList->DataPosi = curr==pMyList->ListLong ? 0 : curr;

	SOCKCOMUNLOCK(pMyList->MemLock);
	return res;
}

LRESULT MoveListMember(MYLIST *pMyList)
{
	LRESULT res = LOK;	
	if(!CHECKUNLOCK(pMyList->MemLock) || !CHECKUNLOCK(pMyList->Lock))
		return LIST_NEEDWAIT;

	SOCKCOMLOCK(pMyList->Lock);
	int curr = pMyList->CurPosi;
	if (0!=pMyList->pList[curr])
	{
		pMyList->pList[curr] = 0;
		curr++;
		pMyList->CurPosi = curr==pMyList->ListLong ? 0 : curr;
	}
	SOCKCOMUNLOCK(pMyList->MemLock);
	return res;
}