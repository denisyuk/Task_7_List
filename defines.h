#ifndef DEFINES_H
#define DEFINES_H
#pragma pack(push, 1)	//alignment by 1 byte

#include <iostream>
using namespace std;

#define CheckPtr(ptr)					\
{										\
	if(ptr == NULL)						\
	{									\
		cout<<"\nBad Pointer!!!\n";		\
		system("pause");				\
		exit(EXIT_FAILURE);				\
	}									\
}								

enum CBrand{Br_EMPTY, Br_OPEL, Br_NISSAN, Br_RENAULT, Br_SKODA, Br_FORD, Br_AUDI, Br_BMW, Br_CHEVROLET, Br_HONDA, Br_JAGUAR, Br_KIA};

typedef unsigned short		CYear;	//year
typedef unsigned char		BYTE;	//8 bit
typedef unsigned long int	CDist;	//distance
typedef unsigned int		UINT;

union CColor
{
	struct
	{
		BYTE	vR;		//red color
		BYTE	vG;		//green color
		BYTE	vB;		//blue color
	};
	UINT uCol:24;
};

struct CCar
{
	char*	pSurName;		//surname of owner
	CBrand	vBrand;			//brand of car
	CYear	vYear;			//year
	CColor	vCol;			//color of car
	CDist	vKm;			//kilometrage

	CCar*	pNext;	//list
};

#pragma pack(pop)
#endif /*DEFINES_H*/