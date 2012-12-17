#include "list.h"

CList::CList()
{
	pFirst = nullptr;
	bNeat = false;
}

CList::~CList()
{
	CCar* cur = pFirst;
	if(!bNeat)
	{
		while(cur)
		{
			pFirst = pFirst->pNext;
			DelNode(cur);
			cur = pFirst;
		}
	}
	else
	{
		CCar* pBegin = pFirst;
		while(cur)
		{
			pFirst = pFirst->pNext;
			if(cur->pSurName)
			{
				delete[] cur->pSurName;
			}
			cur = pFirst;
		}
		delete[] pBegin;
	}
}

void CList::Add(void)
{
	UINT size = sizeof(CCar);
	BYTE* tmp = new BYTE[size - 1];
		CCar* Next = new CCar;
	delete[] tmp;
	///enter data///
	EnterSurName(Next);
	//EnterBrand(Next);
	//EnterYear(Next);
	//EnterCol(Next);
	//EnterDist(Next);
	////////////////
	Next->pNext = pFirst;
	pFirst = Next;

	if(bNeat)
	{
		AddNeatNode();
		delete Next;
	}
}

void CList::Delete(void)
{
	if(!pFirst)
	{
		cout<<"\nNo available elements in list!\n";
		return;
	}
	cout<<"\nEnter index: ";
	UINT id;
	cin>>id;
	if(!cin.good() || id < 1)
	{
		cout<<"\nError!!! Bad index!\n";
		return;
	}
	if(GetCount() == 1 && id == 1)
	{
		DelNode(pFirst);
		pFirst = nullptr;
		cout<<"\nSuccessful delete!\n";
		bNeat = false;
		return;
	}

	if(bNeat)
	{
		this->DelNeatNode(id);
	}
	else
	{
		this->DelRandNode(id);
	}
}

void CList::Show(void)
{
	CCar* cur = pFirst;	//current
	cout<<"\nList of cars: \n";
	UINT n = 1;
	while(cur)
	{
		cout<<endl<<n++<<"):";
		ShowCarData(cur);
		cout<<"\n(Address: "<<cur<<")\n";
		cur = cur->pNext;
		
	}
}

void CList::Neat()
{
	
	UINT n = this->GetCount();
	UINT size = (UINT)sizeof(CCar);
	if(n == 0)
	{
		cout<<"\nNo available elements in list!\n";
		return;
	}
	BYTE* ptr = new BYTE[size * n];	//create a new region of memory

	CheckPtr(ptr);

	CCar* cur = pFirst;		//current - runs in old list
	CCar* prev = nullptr;

	pFirst = (CCar*)ptr;	//runs in new list

	for(UINT i = 0; i < n; i++)
	{
		pFirst->pNext = (CCar*)(ptr + i * size);
		pFirst = pFirst->pNext;

		memcpy(pFirst, cur, size); 

		prev = cur;
		if(i < n - 1)
		{
			cur = cur->pNext;
		}
		delete prev;
	}
	pFirst->pNext = nullptr;
	pFirst = (CCar*)ptr;

	bNeat = true;	//now it is neat list
}

void CList::Rand()
{
	if(!GetCount())
	{
		cout<<"\nNo available elements in list!\n";
		return;
	}
	UINT size = sizeof(CCar);
	CCar* pOld = pFirst;	//save pointer on old region
	CCar* pCur = pFirst;
	BYTE* tmp = nullptr;
	CCar* pTmp = new CCar();

	for(UINT i = 0; pCur; i++)
	{
		if(i == 0)
		{
			pFirst = new (pTmp)CCar();
		}
		else
		{
			tmp = new BYTE[size - 1];
			pFirst->pNext = new CCar();
			delete[] tmp;
			pFirst = pFirst->pNext;
		}
		memcpy(pFirst, pCur, size);
		pCur = pCur->pNext;
	}
	pFirst = pTmp;
	delete[] pOld;
	bNeat = false;
}
void CList::GrByBrand()
{
	UINT n = this->GetCount();
	UINT size = (UINT)sizeof(CCar);
	if(n == 0)
	{
		cout<<"\nNo available elements in list!\n";
		return;
	}
	BYTE* ptr = new BYTE[size * n];	//create a new region of memory

	CheckPtr(ptr);

	CCar* cur = pFirst;		//current - runs in old list

	pFirst = (CCar*)ptr;	//runs in new list

	CBrand tBrand = Br_EMPTY;

	for(UINT i = 0; i < n; i++)
	{
		tBrand = cur->vBrand;	//save current brand
		pFirst->pNext = (CCar*)(ptr + i * size);
		pFirst = pFirst->pNext;

		memcpy(pFirst, cur, size); 

		cur = cur->pNext;

		if(tBrand != cur->vBrand)
		{
			
		}
	}
	pFirst->pNext = nullptr;
	pFirst = (CCar*)ptr;

	bNeat = true;	//now it is neat list
}


void CList::Run()
{
	char ch;

	do
	{
		system("cls");
		cout<<"\n---MAIN menu---\n";
		cout<<"\n\'0\' - to EXIT";
		cout<<"\n\'1\' - to Add a new element";
		cout<<"\n\'2\' - to Delete an element by index";
		cout<<"\n\'3\' - to Show whole list";
		cout<<"\n\'4\' - to CONVERT list";
		cout<<"\n\'5\' - to DECONVERT list";

		cout<<"\n\nLet's enter your choice: ";
		cin>>ch;
		switch(ch)
		{
			case '0':
			{
				return;
			}break;

			case '1':
			{
				system("cls");
				this->Add();
			}break;

			case '2':
			{
				system("cls");
				this->Delete();
				system("pause");
			}break;

			case '3':
			{
				system("cls");
				this->Show();
				system("pause");
			}break;

			case '4':
			{
				system("cls");
				this->Neat();
				this->Show();
				system("pause");
			}break;

			case '5':
			{
				system("cls");
				this->Rand();
				this->Show();
				system("pause");
			}break;

			default:
			{
				cout<<"\nTry again!\n";
				system("pause");
			}

		}

	}while(ch != '0');
}
//////////////////////////////////////////////////
//private methods
//////////////////////////////////////////////////
void CList::EnterSurName(CCar* car)
{
	CheckPtr(car);
	char tmp;
	cout<<"\nEnter surname: ";
	cin>>tmp;

	car->pSurName = new char[(UINT) (cin.rdbuf()->in_avail() + 1)];
	car->pSurName[0] = tmp;
	cin>>(car->pSurName + 1 );

	system("cls");
	cout<<"\nEnter Surname - Good!\n";
	system("pause");
	system("cls");
}

void CList::EnterBrand(CCar* car)
{
	CheckPtr(car);
	int ch = 0;	//choice
	car->vBrand = Br_EMPTY;
	do
	{
		for(UINT i = 1; i < 12;	i++)
		{
			cout<<i<<": ";
			PrintBrand(i);	//print list of brands for choice
			cout<<"\n";
		}
		cout<<"\nLook at the brands, and enter your choice: ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin>>ch;
		if(cin.good() && ch >= Br_OPEL && ch <= Br_KIA)
		{
			car->vBrand = (CBrand)ch;
		}
		else
		{
			cout<<"\nError! Bad brand!!!\n";
			system("pause");
		}
		system("cls");
	}while(car->vBrand == Br_EMPTY);

	cout<<"\nEntering of brand - Good!\n";
	system("pause");
	system("cls");
}

void CList::EnterYear(CCar* car)
{
	CheckPtr(car);
	CYear y;
	bool bExit = false;
	do{
		cout<<"\nEnter year of car: ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin>>y;
		if(cin.good() && y >= 0 && y <= 2012)
		{
			car->vYear = y;
			bExit = true;
		}
		else
		{
			cout<<"\nError! Bad year!!!\n";
			system("pause");
		}
		system("cls");
	}while(!bExit);

	cout<<"\nEntering of year - Good!\n";
	system("pause");
	system("cls");
}

void CList::EnterCol(CCar* car)
{
	CheckPtr(car);
	short r = 0, b = 0, g = 0;
	bool bExit = false;
	do{
		system("cls");
		cout<<"\nEnter Color (0-255): Red ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin>>r;
		if(r < 0 || r > 255 || !cin.good())
		{
			cout<<"\nError! Bad value! Try again!\n";
			system("pause");
			continue;
		}

		cout<<"\nEnter Color (0-255): Green ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin>>g;
		if(g < 0 || g > 255 || !cin.good())
		{
			cout<<"\nError! Bad value! Try again!\n";
			system("pause");
			continue;
		}

		cout<<"\nEnter Color (0-255): Blue ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin>>b;
		if(b < 0 || b > 255 || !cin.good())
		{
			cout<<"\nError! Bad value! Try again!\n";
			system("pause");
			continue;
		}

		/////if entering is good
		car->vCol.vR = (BYTE)r;
		car->vCol.vG = (BYTE)g;
		car->vCol.vB = (BYTE)b;
		bExit = true;
		//////////
		system("cls");
	}while(!bExit);
	cout<<"\nEntering of Color - Good!\n";
	system("pause");
	system("cls");
}

void CList::EnterDist(CCar* car)
{
	CheckPtr(car);
	CDist tmp;
	bool bExit = false;
	do{
		cout<<"\nEnter kilometrage of car (km): ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin>>tmp;
		if(cin.good())
		{
			car->vKm = tmp;
			bExit = true;
		}
		else
		{
			cout<<"\nError! Bad kilometrage!!!\n";
			system("pause");
		}
		system("cls");
	}while(!bExit);
	cout<<"\nEntering of kilometrage - Good!\n";
	system("pause");
	system("cls");
}

void CList::ShowCarData(CCar* car)
{
	CheckPtr(car);
	cout<<"\nSurname: \t"		<<car->pSurName;
	//cout<<"\nBrand: \t\t";
	//PrintBrand(car->vBrand);
	//cout<<"\nColor: \t\t(R:"<<(UINT)car->vCol.vR<<", G:"<<(UINT)car->vCol.vG<<", B:"<<(UINT)car->vCol.vB<<")";
	//cout<<"\nYear: \t\t"		<<car->vYear;
	//cout<<"\nKilometrage: \t"	<<car->vKm;
}

void CList::PrintBrand(UINT i)
{
		switch(i)
		{
			case Br_OPEL:
			{
				cout<<" Opel";
			}break;

			case Br_NISSAN:
			{
				cout<<" Nissan";
			}break;

			case Br_RENAULT:
			{
				cout<<" Renault";
			}break;

			case Br_SKODA:
			{
				cout<<" Skoda";
			}break;

			case Br_FORD:
			{
				cout<<" Ford";
			}break;

			case Br_AUDI:
			{
				cout<<" Audi";
			}break;

			case Br_BMW:
			{
				cout<<" BMW";
			}break;

			case Br_CHEVROLET:
			{
				cout<<" Chevrolet";
			}break;

			case Br_HONDA:
			{
				cout<<" Honda";
			}break;

			case Br_JAGUAR:
			{
				cout<<" Jaguar";
			}break;

			case Br_KIA:
			{
				cout<<" KIA";
			}break;

			default:
			{
				cout<<"EMPTY";
			}
		}
}

UINT CList::GetCount()
{
	UINT n = 0;

	CCar* cur = pFirst;	//current
	while(cur)
	{
		n++;
		cur = cur->pNext;
	}
	return n;
}


bool CList::DelNode(CCar* node)
{
	CheckPtr(node);
	if(node->pSurName)
		{
			delete[] node->pSurName;
		}
	delete node;
	node = nullptr;
	return true;
}

void CList::DelNeatNode(UINT id)
{
	UINT n = GetCount();
	UINT size = sizeof(CCar);
	if(id > n)
	{
		cout<<"\nError!!! Bad index!\n";
		return;
	}
	
	//new region of memory
	BYTE* ptr = new BYTE[(n - 1) * size];
	BYTE* pOld = (BYTE*)pFirst;	//save pointer on old list

	pFirst = (CCar*)ptr;	//runs in new region of memory

	CCar* cur = (CCar*)pOld;

	for(UINT i = 0; i < n - 1; i++)
	{
		pFirst->pNext = (CCar*)(ptr + i * size);
		pFirst = pFirst->pNext;

		if((id - 1) == i)
		{
			if(cur->pSurName)
			{
				delete[] cur->pSurName;
			}
			cur = cur->pNext;
		}

		memcpy(pFirst, cur, size); 
		cur = cur->pNext;
	}
	pFirst->pNext = nullptr;
	pFirst = (CCar*)ptr;

	delete[] pOld;
	cout<<"\nSuccessful delete!\n";
}

void CList::DelRandNode(UINT id)
{
	CCar* cur = pFirst;
	if(id == 1)	//if we want delete first element
	{
		pFirst = pFirst->pNext;
		DelNode(cur);
		cout<<"\nSuccessful delete!\n";
		return;
	}

	CCar* prev = pFirst;
	UINT i = 1;
	do
	{
		if(id == (i + 1))
		{
			cur = cur->pNext;
			prev->pNext = cur->pNext;
			DelNode(cur);
			cout<<"\nSuccessful delete!\n";
			return;
		}

		cur = cur->pNext;
		prev = cur;
		i++;
	}while(cur);

	cout<<"\nError!!! Bad index!\n";
}

void CList::AddNeatNode()
{
	UINT n = GetCount();
	UINT size = sizeof(CCar);
	//new region of memory
	BYTE* ptr = new BYTE[n * size];
	CCar* cur = (CCar*)pFirst;
	BYTE* pOld = (BYTE*)pFirst->pNext;	//save pointer on old list

	pFirst = (CCar*)ptr;	//runs in new region of memory

	for(UINT i = 0; cur; i++)
	{
		pFirst->pNext = (CCar*)(ptr + i * size);
		pFirst = pFirst->pNext;

		memcpy(pFirst, cur, size); 
		cur = cur->pNext;
	}
	pFirst->pNext = nullptr;
	pFirst = (CCar*)ptr;
	delete[] pOld;
}