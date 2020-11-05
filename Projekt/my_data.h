#ifndef MY_DATA_ADFGRETW__H
#define MY_DATA_ADFGRETW__H

struct MY_STUDENT
{
	char* lastname;		//SF tu ma byc wskaznik czar, a pamiec powinna alokowac sie dynamicznie
	size_t stringSize;
	size_t year;
	enum{
		Informatyka,	//0
		Matematyka,		//1
		Fizyka,			//2
	}course;
};

void* MY_DATA_Init(char* llastname, size_t year, int course);
void MY_DATA_Free(void* ptr);
void* MY_DATA_Push(char* llastname, size_t year, int course);
void MY_DATA_Print(void* ptr);
void MY_DATA_PrintDat(MY_STUDENT* p, const char* course);
void MY_DATA_Write(FILE* file, void* ptr);
void* MY_DATA_Read(FILE* file);
int MY_DATA_Search(void* pCurData, void* pSearchData);
#endif