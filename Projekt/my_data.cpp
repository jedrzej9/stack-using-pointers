#include <stdlib.h>
#include <stdio.h>
#include "my_data.h"
#include "string.h"

#pragma warning (disable : 4996)

#define MAX_STRING_SIZE 127				//max dlugosc stringa lastname

void* MY_DATA_Init(char* llastname, size_t year, int cc)
{
	MY_STUDENT* pdat = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));

	pdat->stringSize = strlen(llastname);

	pdat->lastname = (char*)malloc(strlen(llastname) * sizeof(char) + 1);		//dynamiczna alokacja pamieci dla zmiennej lastname
																				//	+1 dla znaku \0
	switch (cc)
	{
	case 0:
		if (pdat->lastname) strcpy(pdat->lastname, llastname);
		pdat->year = (int)year;
		pdat->course = MY_STUDENT::Informatyka;
		break;
	case 1:
		if (pdat->lastname) strcpy(pdat->lastname, llastname);
		pdat->year = (int)year;
		pdat->course = MY_STUDENT::Matematyka;
		break;
	case 2:
		if (pdat->lastname) strcpy(pdat->lastname, llastname);
		pdat->year = (int)year;
		pdat->course = MY_STUDENT::Fizyka;
		break;
	default:
		break;
	}
	return (void*)(pdat);
}


void MY_DATA_Free(void* ptr)
{
	MY_STUDENT* pDat = (MY_STUDENT*)ptr;
	////SF Tu Pan gubi pamieć (leak of memory).
	if (pDat)
		free(pDat);
}

void* MY_DATA_Push(char* lastname, size_t year, int cc)
{
	return MY_DATA_Init(lastname, year, cc);
}

void MY_DATA_Print(void* ptr)
{
	MY_STUDENT* p = (MY_STUDENT*)ptr;
	if (p)
	{
		//SF Pan wielokrotnie powtarza podobne fragmenty kodu. Czy moze warto zrobic jakas funkcje?
		////SF nie widzę rozwiązania tego problemu
		const char* c = NULL;
		switch (p->course)
		{
		case MY_STUDENT::Informatyka:
			MY_DATA_PrintDat(p, c = "Informatyka");			//stworzylem funkcje MY_DATA_PrintDat zeby kod byl krotszy
			break;
		case MY_STUDENT::Matematyka:
			MY_DATA_PrintDat(p, c = "Matematyka");
			break;
		case MY_STUDENT::Fizyka:
			MY_DATA_PrintDat(p, c = "Fzyka");
			break;
		default:
			break;
		}
	}
}

void MY_DATA_PrintDat(MY_STUDENT* p, const char* course)
{
	printf("Lastname: %s\n", p->lastname);
	printf("Year    : %zu\n", p->year);
	printf("Course  : %s\n", course);
}

void MY_DATA_Write(FILE* file,void* ptr)
{
	//Struktura pliku:
	/*===============================================================================================
	*							|						|	
	*		 Object				|		lastname		|	... i tak dalej dla kazdego elementu stosu
	*		MY_STUDENT			|		 char[]			|
	*							|						|	
	*================================================================================================*/

	MY_STUDENT* object = (MY_STUDENT*)ptr;

	//SF Mowili my o to ze zapis-odczyt powinien byc binarnym, a nie tekstowym.
	////SF A jesli struktura zawiera 100 elementow, to Pan bedzie pisal 100 linij kodu?
	////Prosze zrealizowac w dwa zapisy. stringSize mozna dolaczyc do struktury
	if (object)
	{
		fwrite(object, sizeof(*object), 1, file);								
		fwrite(object->lastname, sizeof(char), object->stringSize + 1, file);
	}
}

void* MY_DATA_Read(FILE* file)
{
	MY_STUDENT* object = NULL;

	object = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));
	object->lastname = NULL;

	char str[MAX_STRING_SIZE];

	while (!feof(file))
	{
		////SF prosze zrealizowac w dwa odczyty
		if (object)
			fread(object, sizeof(*object), 1, file);
		
		object->lastname = (char*)malloc(sizeof(char) * object->stringSize + 1);

		if (object->lastname)
		{
			fread(object->lastname, sizeof(char), object->stringSize + 1, file);
			printf("Object readed: \n");
			MY_DATA_Print(object);
			printf("\n");
			return object;
		}
	}
	return NULL;
}

int MY_DATA_Search(void* pCurData, void* pSearchData)
{
	MY_STUDENT* pcur = (MY_STUDENT*)pCurData;
	MY_STUDENT* psearch = (MY_STUDENT*)pSearchData;

	if (strcmp(pcur->lastname, psearch->lastname) == 0)
		return 1;

	return 0;
}