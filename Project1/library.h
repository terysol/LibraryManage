#pragma once

#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <string>
#include <winsock.h>

#include <cstdlib>
#include <time.h>
#include <ctime>
#include <sstream>
#include <cstring>
#include "DB.h"


using namespace std;
#define UP 0
#define DOWN 1
#define SUBMIT 2
#define LEFT 3

void gotoxy(int x, int y);
void cursor(int n);
int keyControl();
void connectDB();

int query_state;
int fields;

void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void cursor(int n) {  // Ŀ�� ���̱� & �����
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor; //����ü ���� 
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = n; //Ŀ�� ���⿩�� 1:����, 0:�Ⱥ��� 
	ConsoleCursor.dwSize = 1; //Ŀ�� ������ 
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

int keyControl() {
	int temp = _getch();
	if (temp == 72) {
		return UP;
	}
	else if (temp == 80) {
		return DOWN;
	}
	else if (temp == 75) {
		return LEFT;
	}
	else if (temp == 13) {
		return SUBMIT;
	}
}



class Time {
	int year=0;
	int month=0;  // 1 ���� 12 ����.
	int day=0;    // 1 ���� 31 ����.
	stringstream str1;
	stringstream str2;
	stringstream str3;
	string result;
	time_t rawtime;
	tm* timeinfo;
	char buffer[80];

public:
	void SetDate();

	int GetCurrentMonthTotalDays(int year, int month);

	void AddMonth(int inc);

	void AddYear(int inc) { year += inc; }

	void AddDay(int inc);

	string getDate();

	string getToday();

};