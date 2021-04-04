#include <iostream>
#include <winsock.h>
#include <mysql.h>
#include <string>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
void gotoxy(int x, int y);
#pragma comment(lib, "libmysql.lib")

void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
int main() {
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;
	MYSQL* Connptr = NULL;
	int fields;
	int query_state;
	int x = 20;
	int y = 8;

	mysql_init(&mysql); //mysql 초기화
	Connptr =mysql_real_connect(&mysql, "localhost", "root", "mirim2", "library", 3306, NULL, 0);
	// mysql_real_connect(&mysql, host, user, passwd, dbname, unix_socket, unit client_flag);

	mysql_query(Connptr, "set session character_set_connection=euckr;");
	mysql_query(Connptr, "set session character_set_results=euckr;");
	mysql_query(Connptr, "set session character_set_client=euckr;");

	string name = "booklist";
	string Query = "select * from" + name;
	mysql_query(&mysql, "select * from" + name);
	

	res = mysql_store_result(&mysql);  // 모든 출력 결과를 서버에서 한번에 다 받아옴.
	fields = mysql_num_fields(res);   // 필드 갯수 구함

	while (row = mysql_fetch_row(res)) {   // 한 행을 구함
		for (int i = 0; i < fields; i++) {
			gotoxy(x, y);
			cout << row[i] << '|';
			x += 5;
			if (i == 2)  y += 2;
		}
		cout << endl;
	}

	mysql_free_result(res);
	mysql_close(&mysql);

}
