#include "library.h"

// class Time
void Time:: SetDate() {
	time_t curr_time = time(nullptr);
	struct tm* curr_tm = localtime(&curr_time);
	int curr_year = curr_tm->tm_year + 1900;
	int curr_month = curr_tm->tm_mon + 1;
	int curr_day = curr_tm->tm_mday;
	this->year = curr_year;
	this->month = curr_month;
	this->day = curr_day;
}
int Time::GetCurrentMonthTotalDays(int year, int month) {
	static int month_day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (month != 2) {
		return month_day[month - 1];
	}
	else if (year % 4 == 0 && year % 100 != 0) {
		return 29;  // 윤년
	}
	else {
		return 28;
	}
}
void Time::AddMonth(int inc) {
	AddYear((inc + month - 1) / 12);
	month = month + inc % 12;
	month = (month == 12 ? 12 : month % 12);
}
void Time::AddDay(int inc) {
	while (true) {
		// 현재 달의 총 일 수
		int current_month_total_days = GetCurrentMonthTotalDays(year, month);

		// 같은 달 안에 들어온다면;
		if (day + inc <= current_month_total_days) {
			day += inc;
			return;
		}
		else {
			// 다음달로 넘어가야 한다.
			inc -= (current_month_total_days - day + 1);
			day = 1;
			AddMonth(1);
		}
	}
}
string Time::getDate() {
	SetDate();
	AddDay(7);
	str1 << year;
	str2 << month;
	str3 << day;

	result = str1.str() + "-" + str2.str();
	result.append("-" + str3.str());

	return result;
}
string Time::getToday() {
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "%Y-%m-%d", timeinfo);
	return buffer;
}

class Library :public Time{
public:
	string bookName;
	string date = getDate();
	string buffer = getToday();
};

class Front {
private:
	int select=0;
	string id;
	string password;
	string check;
public:
	int PrintFront() {
		int x = 23;
		int y = 5;
		cursor(0);
		system("cls");
		cout << endl;
		cout << setw(35) << "도서관" << endl;
		cout << endl;
		cout << setw(50) << "====================================" << endl;
		cout << endl;
		gotoxy(x-2,y);   // (가로, 세로)
		cout << "> 1. 로그인하기";
		gotoxy(x, y+2);
		cout << "2. 회원가입하기" ;

		while (true) {
			int n = keyControl();
			switch (n) {
			case UP: {
				if (y>=5) {
					gotoxy(x-2 , y);
					cout << " ";
					gotoxy(x-2, y-=2);
					cout << ">";
				}
				break;
			}
			case DOWN: {
				if (y <7) {
					gotoxy(x-2, y);
					cout << " ";
					gotoxy(x-2, y+=2);
					cout << ">";
				}
				break;
			}
			case SUBMIT: {
				return y - 5;
			}
			}
		}

	}

	void login() {
		int x = 23;
		int y = 7;
		cursor(0);
		system("cls");
		cout << endl;
		cout << setw(35) << "로그인"<< endl;
		cout << endl;
		cout << setw(50) << "====================================" << endl;
		cout << endl;
		gotoxy(x,y-2);
		cout << "아이디 : ";
		cin >> id;
		gotoxy(x, y);
		cout  << "비밀번호 : ";
		cin >> password;
		gotoxy(x-5, y+2);
		cout << "확인 하셨으면 y를 입력해주세요>> ";
		cin >> check;

		
	}

	void SignUp() {
		int x = 23;
		int y = 5;
		cursor(0);
		system("cls");
		cout << endl;
		cout << setw(35) << "회원가입" << endl;
		cout << endl;
		cout << setw(50) << "====================================" << endl;
		gotoxy(x, y);
		cout << "아이디 : ";
		cin >> id;
		gotoxy(x, y + 2);
		cout << "비밀번호 : ";
		cin >> password;
		gotoxy(x - 5, y + 4);
		cout << "확인 하셨으면 y를 입력해주세요>> ";
		cin >> check;
		if (check == "y") {
			SignUpDB();
		}

		login();
	}

	void SignUpDB() {
		connectDB();

		string Query = "";     // 세미콜론을 제외하고 쿼리문 작성
		Query += "insert into member(id,password) values ('";
		Query += id;
		Query += "','";
		Query += password;
		Query += "');";
		query_state = mysql_query(Connection, Query.c_str());

		if (query_state != 0) {
			fprintf(stderr, "Mysql query error :%s", mysql_error(&mysql));
		}

		mysql_close(&mysql);
	}

};


class Book : public Library {
private:
	char select = NULL;
	string Query = "";
	string Query2 = "";
	int x = 23;
	int y = 5;

public:
	
	int list() {
		
		system("cls");
		cout << endl;
		cout << setw(30) << "도서관" << endl;
		cout << endl;
		cout << setw(48) << "====================================" << endl;

		gotoxy(x - 2, y);
		cout << "> 1. 반납하기 ";
		gotoxy(x, y + 2);
		cout << "2. 대출하기";
		gotoxy(x, y + 4);
		cout << "3. 책 검색하기";
		gotoxy(x, y + 6);
		cout << "4. 자신 프로필 보기";
		gotoxy(x, y + 8);
		cout << "5. 책 리스트 보기";
		gotoxy(x, y + 10);
		cout << "6. 종료";
		int x1 = 23;
		int y1 = 5;
		while (true) {
			int n = keyControl();
			switch (n) {
			case UP: {
				if (y1 > 5) {
					gotoxy(x1 - 2, y1);
					cout << " ";
					gotoxy(x1 - 2, y1 -= 2);
					cout << ">";
				}
				break;
			}
			case DOWN: {
				if (y1 < 15) {
					gotoxy(x1 - 2, y1);
					cout << " ";
					gotoxy(x1 - 2, y1 += 2);
					cout << ">";
				}
				break;
			}
			case SUBMIT: {
				return y1 - 5;
			}
			}
		}
	}

	void Return() {
		system("cls");
		cout << endl;
		gotoxy(24, 1);
		cout << "도서관" << endl;
		cout << setw(48) << "====================================" << endl;
		cout << endl;
		cout << setw(33) << "<반납>" << endl;
		gotoxy(10, 7);
		cout << "반납할 책을 입력하세요 >> ";
		cin >> bookName;
		//updateDB();
		ReturnDB();
		gotoxy(10, 10);
		cout << "반납되셨습니다.";
		
		Sleep(3000);
		//list();
	}
	
	void ReturnDB() {
		connectDB();
		
		Query += "DELETE FROM borrowbook WHERE BookName='";
		Query += bookName;
		Query += "';";
		query_state = mysql_query(Connection, Query.c_str());

		if (query_state != 0) {
			gotoxy(10, 22);
			fprintf(stderr, "Mysql query error :%s", mysql_error(&mysql));
		}

		
		Query2 += "UPDATE booklist SET borrow ='대출가능' WHERE title='";
		Query2 += bookName;
		Query2 += "';";
		query_state = mysql_query(Connection, Query2.c_str());

		if (query_state != 0) {
			fprintf(stderr, "Mysql query error :%s", mysql_error(&mysql));
		}
		mysql_close(&mysql);
		mysql_close(&mysql);
	}

	void borrow() {
		system("cls");
		cout << endl;
		cout << setw(35) << "도서관" << endl;
		cout << endl;
		cout << setw(48) << "====================================" << endl;
		cout << endl;
		cout << setw(35) << "<대출>" << endl;
		gotoxy(10, 7);
		cout << "대출할 책을 입력하세요 >> ";
		cin >> bookName;
		borrowDB();
		gotoxy(10, 10);
		cout << "대출되셨습니다." << endl;
		
		gotoxy(10, 12);
		cout << "반납일은 " << date << "입니다. ";

		Sleep(5000);

	}

	void borrowDB() {
		connectDB();
		Query += "INSERT INTO borrowbook(BookName, Date, borrowDate) VALUES ('";
		Query += bookName;
		Query += "', '";
		Query += buffer;
		Query += "', '";
		Query += date;
		Query += "');";
		query_state = mysql_query(Connection, Query.c_str());

		if (query_state != 0) {
			gotoxy(10, 22);
			fprintf(stderr, "Mysql query error :%s", mysql_error(&mysql));
		}

		Query2 += "UPDATE booklist SET borrow ='대출중' WHERE title='";
		Query2 += bookName;
		Query2 += "';";
		query_state = mysql_query(Connection, Query2.c_str());

		if (query_state != 0) {
			fprintf(stderr, "Mysql query error :%s", mysql_error(&mysql));
		}
		mysql_close(&mysql);
	}

	void serch() {
		
		system("cls");
		cout << endl;
		cout << setw(35) << "도서관" << endl;
		cout << endl;
		cout << setw(48) << "====================================" << endl;
		cout << endl;
		cout << setw(35) << "<검색>" << endl;
		gotoxy(10, 7);
		cout << "검색할 책을 입력하세요(키워드 가능) >> ";
		cin >> bookName;
		gotoxy(10, 8);
		cout << "------------------------------------------";
		searchDB();  /* 리스트 나오게 하기*/
		gotoxy(10, 15);
		cout << "------------------------------------------";
		gotoxy(10, 16);
		cout << "위 책들 중 대출하고 싶으신 책이 있나요?(y/n) ";
		cin >> select;
		if (select == 'y') {
			gotoxy(10, 18);
			cout << "어떤 책을 대출하고 싶으신 가요?(제목 입력)>>";
			cin >> bookName;
			borrowDB();
			gotoxy(10, 20);
			cout << "대출되셨습니다." << endl;
			gotoxy(10, 22);
			cout << "반납일은 " << date<<"까지 입니다. ";
		}
		else {
			gotoxy(10, 20);
			cout << "메인으로 돌아갑니다.";
		}
		Sleep(10000);
		//list();
	}

	void searchDB() {
		connectDB();
		string Query = "";
		Query += "SELECT * FROM booklist WHERE title LIKE '%";
		Query += bookName;
		Query += "%';";

		query_state = mysql_query(Connection, Query.c_str());

		if (query_state != 0) {
			fprintf(stderr, "Mysql query error :%s", mysql_error(&mysql));
		}
		res = mysql_store_result(&mysql);  // 모든 출력 결과를 서버에서 한번에 다 받아옴.
		fields = mysql_num_fields(res);   // 필드 갯수 구함

		int y = 10;
		while (row = mysql_fetch_row(res)) {   // 한 행을 구함
			gotoxy(10, y);
			y += 2;
			for (int i = 0; i < fields; i++) {

				cout << row[i] << '|' << setw(5);
			}
			cout << endl;
		}

		mysql_close(&mysql);
	}

	void Member() {
		system("cls");
		cout << endl;
		cout << setw(35) << "도서관" << endl;
		cout << endl;
		cout << setw(48) << "====================================" << endl;
		cout << endl;
		cout << setw(35) << "<회원>" << endl;
		gotoxy(12, 8);
		cout << "빌린 책               대출일                 반납일 " << endl;
		gotoxy(12, 9);
		cout << "-----------------------------------------------------" << endl;
		/* 책 리스트 보여주기*/
		memberDB();

		Sleep(10000);
		//list();
	}

	void memberDB() {
		connectDB();

		mysql_query(&mysql, "select * from borrowbook");

		res = mysql_store_result(&mysql);  // 모든 출력 결과를 서버에서 한번에 다 받아옴.
		fields = mysql_num_fields(res);   // 필드 갯수 구함

		int y = 10;
		while (row = mysql_fetch_row(res)) {   // 한 행을 구함
			gotoxy(3, y);
			y += 2;
			for (int i = 0; i < fields; i++) {
				cout << setw(20) << row[i] << '|';
			}
			cout << endl;
		}

		mysql_free_result(res);
		mysql_close(&mysql);
	}

	void BookList() {
		
		system("cls");
		cout << endl;
		cout << setw(35) << "도서관" << endl;
		cout << endl;
		cout << setw(48) << "====================================" << endl;
		cout << endl;
		cout << setw(35) << "<책 리스트>" << endl << endl;

		selectDB();
		gotoxy(10, 18);
		cout << "-----------------------------------------------";
		
		
		gotoxy(10, 20);
		cout << "10초 후에 메인으로 돌아가겠습니다";
		
		Sleep(10000);
		//list();
	}

	void selectDB() {
		connectDB();

		mysql_query(&mysql, "select * from booklist");

		res = mysql_store_result(&mysql);  // 모든 출력 결과를 서버에서 한번에 다 받아옴.
		fields = mysql_num_fields(res);   // 필드 갯수 구함

		int y = 8;
		while (row = mysql_fetch_row(res)) {   // 한 행을 구함
			gotoxy(3, y);
			y += 2;
			for (int i = 0; i < fields; i++) {
				cout <<setw(25) << row[i] << '|';
			}
			cout << endl;
		}

		mysql_free_result(res);
		mysql_close(&mysql);
	}

	void finish() {
		system("cls");
		exit(0);
	}
};

int main() {
	int select;
	Front f;

	select=f.PrintFront();
	if (select == 0) {
		f.login();
	}
	else if (select == 2) {
		f.SignUp();
	}
	Book b;
	while (true) {
		select = b.list();
		switch (select) {
		case 0:
			b.Return();  break;
		case 2:
			b.borrow();  break;
		case 4:
			b.serch();  break;
		case 6:
			b.Member();  break;
		case 8:
			b.BookList();  break;
		case 10:
			b.finish();   break;
		default:
			continue;
		}
	}
}