#include <stdlib.h>
#include <stdio.h>
#include "my_interface.h"
#include "my_stack.h"
#include "my_data.h"

//SF Pan kompletnie ignoruje diagnostyke kompilatora!

#pragma warning (disable : 4996)

int main()
{
	MY_STACK_Init(MY_DATA_Free);
	size_t op = 0;
	while (op >= INTERF_PUSH && op <= INTERF_STOP)
	{
		menu();
		if (scanf("%zu", &op) == 1)
		{
			switch (op)
			{
			case INTERF_PUSH: push();
				break;
			case INTERF_POP: pop();
				break;
			case INTERF_CLEAR: clear();
				break;
			case INTERF_PRINT: print();
				break;
			case INTERF_SAVE: save();
				break;
			case INTERF_READ: read();
				break;
			case INTERF_SEARCH: search();
				break;
			case INTERF_STOP: clear();
				return 0;
			default:
				printf("nieuznawany kod operacji\n");
			};
		}
		else
		{
			exit(EXIT_FAILURE);		//scanf zakończone niepowodzeniem
		}
	}
	system("pause");
	return 0;
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
