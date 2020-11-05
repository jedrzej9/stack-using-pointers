#ifndef MY_INTERFACE___H
#define MY_INTERFACE___H

enum MY_INTERF_EN
{
	INTERF_PUSH,
	INTERF_POP,
	INTERF_CLEAR,
	INTERF_PRINT,
	INTERF_SAVE,
	INTERF_READ,
	INTERF_SEARCH,
	INTERF_STOP,
	INTERF_TOT
};

void push();
void pop();
void clear();
void menu();
void print();
void save();
void read();
void search();

#endif