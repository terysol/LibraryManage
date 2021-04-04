#include <iostream>
#include <winsock.h>
#include <mysql.h>
#include <cstdio>
#include <ctime>

using namespace std;
#pragma comment(lib, "libmysql.lib")
void AddMonth(int year, int month, int day);
void AddYear(int year, int month, int day);

void AddMonth(int year,int month, int day) {
	AddYear((7 + month - 1) / 12);
	month = month + 7 % 12;
	month = (month == 12 ? 12 : month % 12);
}

void AddYear(int year, int month, int day) { year += 7; }

int main()
{
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;

	MYSQL* Connection = NULL, conn;
	int query_state;
	time_t rawtime;
	tm* timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);


	strftime(buffer, 80, "%Y-%m-%d", timeinfo);
	puts(buffer);
	cout << buffer << endl;

	mysql_init(&mysql); //mysql 초기화
	Connection = mysql_real_connect(&mysql, "localhost", "root", "mirim2", "library", 3306, NULL, 0);
	if (Connection == NULL) {
		cout << mysql_error(&mysql) << endl;
	}
	else {
		cout << "db 연결 성공";
	}

	
	mysql_query(Connection, "set session character_set_connection=euckr;");
	mysql_query(Connection, "set session character_set_results=euckr;");
	mysql_query(Connection, "set session character_set_client=euckr;");

	string Query = "";     // 세미콜론을 제외하고 쿼리문 작성
	Query += "insert into time(time) values ('";
	Query += buffer;
	Query += "');";
	query_state = mysql_query(Connection, Query.c_str());

	if (query_state != 0) {
		fprintf(stderr, "Mysql query error :%s", mysql_error(&mysql));
	}
	else {
		cout << "성공";
	}

	mysql_close(&mysql);

	return 0;
}