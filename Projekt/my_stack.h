#pragma once

#ifndef MY_STACK__H
#define MY_STACK__H

struct MY_STACK
{
	void* pData;					//wskaznik do danych typu void
	MY_STACK* previous;				//wskaznik do poprzedniego elementu stosu
};

//Wskaüniki do funkcji z kontenera my_data
typedef void (*FreeData)(void* pdat);						//MY_DATA_Free
typedef int (CompData)(void* pcurData, void* pSearchData);	//MY_DATA_Search
typedef void (PrintData)(void* ptr);						//MY_DATA_Print
typedef void (WriteData)(FILE* fp, void* ptr);				//MY_DATA_Write
typedef void* (*ReadData)(FILE* fp);						//MY_DATA_Read

void MY_STACK_Init(FreeData pFreeDat);
void MY_STACK_Free();
MY_STACK* MY_STACK_Push(void* pdat);
MY_STACK MY_STACK_Pop();
void* MY_STACK_Write(WriteData funPtr, int FirstEntry);
void MY_STACK_Read(ReadData funPtr);
void* MY_STACK_Print(PrintData funPtr, int FirstEntry);
void* MY_STACK_Search(void* pSearchDat, CompData ptr_comp_fun, int FirstEntry);

#endif // !MY_STACK__H