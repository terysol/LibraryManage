#include <iostream>
#include <winsock.h>
#include <mysql.h>


using namespace std;

#pragma comment(lib, "libmysql.lib")
int main()
{
	//MYSQL mysql;
	//MYSQL Conn;             // MySQL ������ ���� ����ü
	//MYSQL* ConnPtr = NULL;  // MySQL �ڵ�
	//MYSQL_RES* Result;      // ���������� ����� ��� ����ü ������
	//MYSQL_ROW Row;          // ���������� ����� ���� ���� ������ ��� ����ü
	//int Stat;               // ������û �� ���(����, ����)
	//mysql_init(&mysql);

	//// �����ͺ��̽��� ����
	//ConnPtr = mysql_real_connect(&Conn, "localhost", "root", "mirim2", "library", 3306, NULL, 0);

	//if (ConnPtr == NULL) // ���� ��� Ȯ��. NULL�� ��� ���� �����Ѱ�.
	//{
	//	cout << "error : " << mysql_error(&Conn);
	//}
	//else {
	//	cout << "��������~~" << endl;
	//}
	//mysql_query(ConnPtr, "set session character_set_connection=euckr;");
	//mysql_query(ConnPtr, "set session character_set_results=euckr;");
	//mysql_query(ConnPtr, "set session character_set_client=euckr;");

	//mysql_close(&mysql);
	MYSQL mysql;
	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql, "localhost", "root", "mirim2", "library", 3306, NULL, 0))
		cout << "error";
	else
		cout << "����~!!";

	mysql_close(&mysql);

	return 0;

}



