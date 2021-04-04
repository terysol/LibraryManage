#include <iostream>
#include <winsock.h>
#include <mysql.h>
#include <string>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

#pragma comment(lib, "libmysql.lib")

int main() {
	MYSQL mysql;
	MYSQL_ROW row;
	MYSQL* Connection = NULL;
	int fields;
	int query_state;
	string bookName;
	cout << "책 이름 : ";
	cin >> bookName;

	mysql_init(&mysql); //mysql 초기화
	Connection = mysql_real_connect(&mysql, "localhost", "root", "mirim2", "library", 3306, NULL, 0);
	// mysql_real_connect(&mysql, host, user, passwd, dbname, unix_socket, unit client_flag);

	mysql_query(Connection, "set session character_set_connection=euckr;");
	mysql_query(Connection, "set session character_set_results=euckr;");
	mysql_query(Connection, "set session character_set_client=euckr;");


	//mysql_query(&mysql, "delete from bookList where BookName=");


	string Query = "";     // 세미콜론을 제외하고 쿼리문 작성
	Query += "delete from bookList where BookName='";
	Query += bookName;
	Query += "';";
	query_state = mysql_query(Connection, Query.c_str());

	if (query_state != 0) {
		fprintf(stderr, "Mysql query error :%s", mysql_error(&mysql));
		return 1;
	}
	else {
		cout << "성공";
	}

	mysql_close(&mysql);

}
