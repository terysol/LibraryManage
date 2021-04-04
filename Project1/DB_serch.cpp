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
	MYSQL_RES* res;
	int fields;
	int query_state;
	string keyword;
	cout << "책 이름 : ";
	cin >> keyword;

	mysql_init(&mysql); //mysql 초기화
	Connection = mysql_real_connect(&mysql, "localhost", "root", "mirim2", "library", 3306, NULL, 0);
	// mysql_real_connect(&mysql, host, user, passwd, dbname, unix_socket, unit client_flag);

	mysql_query(Connection, "set session character_set_connection=euckr;");
	mysql_query(Connection, "set session character_set_results=euckr;");
	mysql_query(Connection, "set session character_set_client=euckr;");


	//mysql_query(&mysql, "delete from bookList where BookName=");


	string Query = "";     // 세미콜론을 제외하고 쿼리문 작성
	Query += "SELECT * FROM booklist WHERE title LIKE '%";
	Query += keyword;
	Query += "%';";

	query_state = mysql_query(Connection, Query.c_str());

	if (query_state != 0) {
		fprintf(stderr, "Mysql query error :%s", mysql_error(&mysql));
		return 1;
	}
	else {
		cout << "성공"<<endl;
	}
	res = mysql_store_result(&mysql);  // 모든 출력 결과를 서버에서 한번에 다 받아옴.
	fields = mysql_num_fields(res);   // 필드 갯수 구함

	while (row = mysql_fetch_row(res)) {   // 한 행을 구함
		for (int i = 0; i < fields; i++) {
			cout << row[i] << '|';
		}
		cout << endl;
	}

	mysql_close(&mysql);

}
