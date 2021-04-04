#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4

int keyControl();
void gotoxy(int x, int y);
int menuDraw();

int main() {
	int keyCode = menuDraw();
	cout << "�Է��� Ű ���� : " << keyCode << endl;
	return 0;
}
int keyControl() {
	int temp = _getch();
	if (temp ==72) {
		return UP;
	}
	else if (temp ==80) {
		return DOWN;
	}
	else if (temp == 13) {
		return SUBMIT;
	}
}
int menuDraw() {
	int x = 24;
	int y = 12;
	int y1 = 12;
	gotoxy(x - 2, y);
	cout << "> ���ӽ��� ";
	gotoxy(x, y + 2);
	cout << "��������";
	gotoxy(x, y + 4);
	cout << "��������";
	gotoxy(x, y + 6);
	cout << "��������";
	gotoxy(x, y + 8);
	cout << "��������";
	gotoxy(x, y + 10);
	cout << "��������";
	gotoxy(x, y + 12);
	cout << "��������";
	/*gotoxy(x, y + 2);
	cout << "����";*/
	
	while (true) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y1 > 12) {
				gotoxy(x - 2, y1);
				cout << " ";
				gotoxy(x - 2, y1-=2);
				cout << ">";
			}
			break;
		}
		case DOWN: {
			if (y1 <24) {
				gotoxy(x - 2, y1);
				cout << " ";
				gotoxy(x - 2, y1+=2);
				cout << ">";
			}
			break;
		}
		case SUBMIT: {
			system("cls");
			break;
		}
		}
	}
}
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
