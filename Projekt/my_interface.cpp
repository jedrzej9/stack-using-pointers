#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "my_data.h"
#include "my_stack.h"
#include "my_interface.h"

#pragma warning (disable : 4996)

#define NUMBER_OF_STRING 8
#define NUMBER_OF_COURSES 3
#define MAX_STRING_SIZE 127

static char strtab[NUMBER_OF_STRING][MAX_STRING_SIZE] =
{
	"0 - push",		     //INTERF_PUSH
	"1 - pop",			 //INTERF_POP
	"2 - clear",		 //INTERF_CLEAR
	"3 - print stack",   //INTERF_PRINT
	"4 - save to file",  //INTERF_SAVE
	"5 - read from file",//INTERF_READ
	"6 - search stack",  //INTERF_SEARCH
	"7 - finish"         //INTERF_STOP
};

static char coursesTab[NUMBER_OF_COURSES][MAX_STRING_SIZE] =		
{
	"0 - Informatyka",		     
	"1 - Matematyka",			 
	"2 - Fizyka",		 
};

void menu()
{
	size_t it;
	for (it = 0; it < INTERF_TOT; ++it)
	{
		printf("%s\n", strtab[it]);
	}
}

void push()
{
	static int rv1, rv2, rv3;
	char lastname[MAX_STRING_SIZE];
	size_t year, it;
	int course = 0;
	printf("Course numbers: \n");
	
	for (it = 0; it < NUMBER_OF_COURSES; ++it)
	{
		printf("%s\n", coursesTab[it]);
	}

	printf("lastname, year, course\n");
	rv1 = scanf("%s", lastname);
	rv2 = scanf("%zu", &year);
	rv3 = scanf("%d", &course);
	
	if (rv1 == 1 && rv2 == 1 && rv3 == 1)
	{
		if (course != 0 && course != 1 && course != 2)
			printf("You entered wrong course number!\n");

		void* pdat = MY_DATA_Push(lastname, year, course);
		if (!MY_STACK_Push(pdat))
			printf("push error\n");
	}
	else
	{
		exit(EXIT_FAILURE);
	}
}

void pop()
{
	printf("Poping from stack:\n");
	MY_STACK tmp = MY_STACK_Pop();
	MY_DATA_Print(tmp.pData);
	MY_DATA_Free(tmp.pData);
}

void print()
{
	printf("Printing Stack:\n");
	void* pPrint = MY_STACK_Print(MY_DATA_Print, 1);

	while (pPrint)
	{
		pPrint = MY_STACK_Print(MY_DATA_Print, 0);
	}
}

void save()
{
	printf("Saving Stack to file\n");

	void* pSave = MY_STACK_Write(MY_DATA_Write, 1);

	while (pSave)
	{
		pSave = MY_STACK_Write(MY_DATA_Write, 0);
	}
}

void read()
{
	printf("Reading stack from file\n");
	MY_STACK_Read(MY_DATA_Read);
}

void search()
{
	char str[MAX_STRING_SIZE];
	printf("Input lastname you search for:\n");
	scanf("%s", str);

	MY_STUDENT searchDat;
	searchDat.lastname = (char*)malloc(strlen(str) + 1);

	searchDat.lastname = str;

	void* pDat = MY_STACK_Search(&searchDat, MY_DATA_Search, 1);

	if (pDat)
	{
		printf("Found : \n");
		MY_DATA_Print(pDat);
	}

	while (pDat)
	{
		pDat = MY_STACK_Search(&searchDat, MY_DATA_Search, 0);
		MY_DATA_Print(pDat);
		if (pDat)
		{
			printf("Found : \n");
			MY_DATA_Print(pDat);
		}
	}
}


void clear()
{
	MY_STACK_Free();
}