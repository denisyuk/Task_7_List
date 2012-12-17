#ifndef LIST_H
#define LIST_H

#include "defines.h"

class CList
{
public:
	CList();
	~CList();

	void Add(void);			//add new element
	void Delete(void);		//delete element by index
	void Show(void);		//show whole list
	void Neat();			//transformation to neat list
	void Rand();
	void Run();
	void GrByBrand();		//grouped by Brand

private:	//useful methods
	void EnterSurName(CCar* car);	
	void EnterBrand(CCar* car);
	void EnterYear(CCar* car);
	void EnterCol(CCar* car);
	void EnterDist(CCar* car);

	void ShowCarData(CCar* car);
	void PrintBrand(UINT i);
	bool DelNode(CCar* node);

	void DelNeatNode(UINT id);
	void DelRandNode(UINT id);

	void AddNeatNode();

	UINT GetCount();	//get count of element in list
private:
	CCar*	pFirst;
	bool	bNeat;
};

#endif /*LIST_H*/