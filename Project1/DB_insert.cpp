#include <iostream>
#include <winsock.h>
#include <mysql.h>
#include <string>
#include <time.h>
using namespace std;

#pragma comment(lib, "libmysql.lib")
void updatedb();
MYSQL mysql;
MYSQL_RES* res;
MYSQL_ROW row;

MYSQL* Connection = NULL, conn;
int query_state;

char query[255];
char buffer[80];
string bookName;
string password;
string date = "2020-12-7";
string Query = "";

void updatedb() {
	mysql_init(&mysql); //mysql �ʱ�ȭ
	Connection = mysql_real_connect(&mysql, "localhost", "root", "mirim2", "library", 3306, NULL, 0);
	if (Connection == NULL) {
		cout << mysql_error(&mysql) << endl;
	}
	mysql_query(Connection, "set session character_set_connection=euckr;");
	mysql_query(Connection, "set session character_set_results=euckr;");
	mysql_query(Connection, "set session character_set_client=euckr;");

	Query += "UPDATE booklist SET borrow ='������' WHERE title='";
	Query += borrowBook;
	Query += "';";
	query_state = mysql_query(Connection, Query.c_str());

	if (query_state != 0) {
		fprintf(stderr, "Mysql query error :%s", mysql_error(&mysql));
	}
}

int main() {
	
	cout << "å�̸� �Է� : ";
	cin >> borrowBook;
	cout << endl;
	updatedb();

	mysql_init(&mysql); //mysql �ʱ�ȭ
	Connection = mysql_real_connect(&mysql, "localhost", "root", "mirim2", "library", 3306, NULL, 0);
	if (Connection == NULL){
		cout << mysql_error(&mysql) << endl;
	}
	else {
		cout << "db ���� ����";
	}

	mysql_query(Connection, "set session character_set_connection=euckr;");
	mysql_query(Connection, "set session character_set_results=euckr;");
	mysql_query(Connection, "set session character_set_client=euckr;");

	time_t rawtime;
	tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "%Y-%m-%d", timeinfo);

	  // �����ݷ��� �����ϰ� ������ �ۼ�
	Query += "insert into borrowbook(BookName,Date,borrowDate) values ('";
	Query += borrowBook;
	Query += "','";
	Query += buffer;
	Query += "','";
	Query += date;
	Query += "');";
	query_state = mysql_query(Connection, Query.c_str());

	if (query_state != 0) {
		fprintf(stderr, "Mysql query error :%s", mysql_error(&mysql));
		return 1;
	}
	else {
		cout << "����";
	}
	
	mysql_close(&mysql);
	

}
