#include <iostream>
#include <winsock.h>
#include <mysql.h>


using namespace std;

#pragma comment(lib, "libmysql.lib")
int main()
{
	//MYSQL mysql;
	//MYSQL Conn;             // MySQL 정보를 담을 구조체
	//MYSQL* ConnPtr = NULL;  // MySQL 핸들
	//MYSQL_RES* Result;      // 쿼리성공시 결과를 담는 구조체 포인터
	//MYSQL_ROW Row;          // 쿼리성공시 결과로 나온 행의 정보를 담는 구조체
	//int Stat;               // 쿼리요청 후 결과(성공, 실패)
	//mysql_init(&mysql);

	//// 데이터베이스와 연결
	//ConnPtr = mysql_real_connect(&Conn, "localhost", "root", "mirim2", "library", 3306, NULL, 0);

	//if (ConnPtr == NULL) // 연결 결과 확인. NULL일 경우 연결 실패한것.
	//{
	//	cout << "error : " << mysql_error(&Conn);
	//}
	//else {
	//	cout << "연동성공~~" << endl;
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
		cout << "성공~!!";

	mysql_close(&mysql);

	return 0;

}



