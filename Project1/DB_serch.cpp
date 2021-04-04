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
	cout << "å �̸� : ";
	cin >> keyword;

	mysql_init(&mysql); //mysql �ʱ�ȭ
	Connection = mysql_real_connect(&mysql, "localhost", "root", "mirim2", "library", 3306, NULL, 0);
	// mysql_real_connect(&mysql, host, user, passwd, dbname, unix_socket, unit client_flag);

	mysql_query(Connection, "set session character_set_connection=euckr;");
	mysql_query(Connection, "set session character_set_results=euckr;");
	mysql_query(Connection, "set session character_set_client=euckr;");


	//mysql_query(&mysql, "delete from bookList where BookName=");


	string Query = "";     // �����ݷ��� �����ϰ� ������ �ۼ�
	Query += "SELECT * FROM booklist WHERE title LIKE '%";
	Query += keyword;
	Query += "%';";

	query_state = mysql_query(Connection, Query.c_str());

	if (query_state != 0) {
		fprintf(stderr, "Mysql query error :%s", mysql_error(&mysql));
		return 1;
	}
	else {
		cout << "����"<<endl;
	}
	res = mysql_store_result(&mysql);  // ��� ��� ����� �������� �ѹ��� �� �޾ƿ�.
	fields = mysql_num_fields(res);   // �ʵ� ���� ����

	while (row = mysql_fetch_row(res)) {   // �� ���� ����
		for (int i = 0; i < fields; i++) {
			cout << row[i] << '|';
		}
		cout << endl;
	}

	mysql_close(&mysql);

}
