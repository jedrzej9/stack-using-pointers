#include <stdlib.h>
#include <stdio.h>
#include "my_stack.h"

#pragma warning (disable : 4996)
//SF Zapis i odczyt powinni byc tu, w kontenerze

////SF U mnie jest wielkie podejrzenie, ze u Pana powstaje inwersja. Mamy stos: 1  2  3 (3 - top).
////Piszemy do pliku:  3   2   1
////Odczytujemy z pliku: 3   2   1  (1 - top)
////Prosze poprawic

//MJ poprawione

////SF jesli po zapisie do pliku wykonac od razu drugi zapis - GP (General Page Fault).
////SF jesli po odczycie danych z pliku wykonac wydrukowanie stosu, to nic sie nie drukuje.
////SF jesli po odczycie danych z pliku i nieudanej sprobie wydrukowania wykonac pop - GP
////SF Pan nie testowal porzadnie tego programu. Jesli jeszcze raz Pan przeszlie projekt nietestowany, ja anuluje jego i wydam nowy, bardziej zlozony.

static MY_STACK* top = NULL;   //wskaznik do ostatniego elementu stosu
FreeData ptr_free_dat;         //Deklaracja wskaznika do funkcji typu FreeData

void MY_STACK_Init(FreeData pFreeDat)
{
	top = NULL;
	ptr_free_dat = pFreeDat;
}

void MY_STACK_Free()
{
	MY_STACK* p = top;
	MY_STACK* ptmp = NULL;

	while (p)
	{
		(*ptr_free_dat)(p->pData);

		ptmp = p;

		p = p->previous;

		free(ptmp);
	}

	top = NULL;
}

MY_STACK* MY_STACK_Push(void* pdat)
{
	//alokujemy pamiec dla nowego elementu stosu
	MY_STACK* current = (MY_STACK*)malloc(sizeof(MY_STACK));
	if (!current)
		return NULL;

	//Jeœli to jedyny element wtedy - previous = NULL
	current->previous = NULL;

	//ustawiamy pData
	current->pData = pdat;

	current->previous = top;

	//teraz bie¿¹cy element jest ostatni
	top = current;

	return current;
}

MY_STACK MY_STACK_Pop()
{
	MY_STACK rv;

	if (top == NULL)
	{
		//stos jest pusty
		rv.pData = NULL;
		rv.previous = NULL;
	}
	else
	{
		MY_STACK* tmp = NULL;

		rv.pData = top->pData;
		rv.previous = NULL;
		tmp = top;

		if (top->previous == NULL) top = NULL;
		else top = top->previous;
		
		free(tmp);
	}

	return rv;
}

void* MY_STACK_Print(PrintData funPtr, int FirstEntry)
{
	static MY_STACK* p = top;
	static MY_STACK* ptmp = NULL;

	if (FirstEntry) {
		p = top;
	}

	while (p)
	{
		ptmp = p;
		p = p->previous;

		//SF kontener powinien wywolac funkcje wydruku obiektu przez wskaznik
		(*funPtr)(ptmp->pData);		//wywolanie funkcji wydruku przez wskaznik

	}
	return NULL;
}

void* MY_STACK_Write(WriteData funPtr, int FirstEntry)
{
	static MY_STACK* p = top;
	static MY_STACK* ptmp = NULL;
	FILE* file = NULL;

	file = fopen("output.bin", "wb");			//otwarcie pliku binarnego do zapisu
	
	if (file == NULL)
	{
		printf("Cannot open file!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		if (FirstEntry) {
			p = top;
		}

		while (p)
		{
			ptmp = p;
			p = p->previous;
			(*funPtr)(file, ptmp->pData);
		}

		fclose(file);
	}

	return NULL;
}

void MY_STACK_Read(ReadData funPtr)
{
	MY_STACK_Free();						//przed wczytaniem z pliku czyszcze pamiec

	FILE* file = fopen("output.bin", "rb");	//otwarcie pliku binarnego do odczytu
	int it = 0;
	constexpr auto ARR_SIZE = 1000;			//tablica na wskazniki do obiektow odczytanych z pliku
											//potrzebna zeby nie bylo inwersji
	void* arr[ARR_SIZE];			
	
	if (file == NULL)
	{
		printf("Cannot open file!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		void* pDat = nullptr;

		do {
			pDat = (*funPtr)(file);

			arr[it] = pDat;
			it++;

		} while (pDat);

		it = it - 1;

		for (it; it > 0; it--)			
		{
			MY_STACK_Push(arr[it - 1]);	//dekrementacja i pusz obiektow w odwrotnej kolejnosci
		}

		fclose(file);
	}
}

void* MY_STACK_Search(void* pSearchDat, CompData ptr_comp_fun, int FirstEntry)
/*=================================================================
Wyszukuje dane umieszczone w stosie.
IN: ptr_comp_fun - wskaznik do funkcji porownawczej int FunkcjaPorownawcza(void * curDat, void *pSearchDat),
gdzie curDat     - wskaznik do danych biezacego elementu kolejki,
	  pSearchDat - wskaznik do danych, jakie trzeba odnalezc
	  Zwraca 0 w przypadku curDat != searcDat i 1 jesli curDat == searchDat.

	FirstEntry = 1, jesli to jest pierwsze wywolanie na poczatku poszukiwania, 0 - w przeciwnym przypadku.

	 RetVal: wskaznik do odnalezionych danych, NULL - poszukiwanie nie skonczylo sie sukcessem
===================================================================*/
{
	static MY_STACK* p;
	MY_STACK* ptmp = NULL;

	if (FirstEntry)
		p = top;

	//pobieramy po kolejce obiekty
	while (p != NULL)
	{
		if (!(*ptr_comp_fun)(p->pData, pSearchDat))
		{
			//nie odnaleziono
			//przestawiamy wskaznik p do poprzedniego elementu stosu
			p = p->previous;
		}
		else
		{
			//sukces
			ptmp = p;
			p = p->previous;		//reset to the previous element of stack
			return ptmp->pData;		//return the data of found element
		}
	}
	return NULL;
}