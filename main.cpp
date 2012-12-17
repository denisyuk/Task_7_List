#include "list.h"

void main(void)
{
	CList *pCar = new CList();

	pCar->Run();

	delete pCar;

	system("pause");
}