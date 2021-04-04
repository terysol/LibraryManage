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
		return 29;  // ����
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
		// ���� ���� �� �� ��
		int current_month_total_days = GetCurrentMonthTotalDays(year, month);

		// ���� �� �ȿ� ���´ٸ�;
		if (day + inc <= current_month_total_days) {
			day += inc;
			return;
		}
		else {
			// �����޷� �Ѿ�� �Ѵ�.
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
		cout << setw(35) << "������" << endl;
		cout << endl;
		cout << setw(50) << "====================================" << endl;
		cout << endl;
		gotoxy(x-2,y);   // (����, ����)
		cout << "> 1. �α����ϱ�";
		gotoxy(x, y+2);
		cout << "2. ȸ�������ϱ�" ;

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
		cout << setw(35) << "�α���"<< endl;
		cout << endl;
		cout << setw(50) << "====================================" << endl;
		cout << endl;
		gotoxy(x,y-2);
		cout << "���̵� : ";
		cin >> id;
		gotoxy(x, y);
		cout  << "��й�ȣ : ";
		cin >> password;
		gotoxy(x-5, y+2);
		cout << "Ȯ�� �ϼ����� y�� �Է����ּ���>> ";
		cin >> check;

		
	}

	void SignUp() {
		int x = 23;
		int y = 5;
		cursor(0);
		system("cls");
		cout << endl;
		cout << setw(35) << "ȸ������" << endl;
		cout << endl;
		cout << setw(50) << "====================================" << endl;
		gotoxy(x, y);
		cout << "���̵� : ";
		cin >> id;
		gotoxy(x, y + 2);
		cout << "��й�ȣ : ";
		cin >> password;
		gotoxy(x - 5, y + 4);
		cout << "Ȯ�� �ϼ����� y�� �Է����ּ���>> ";
		cin >> check;
		if (check == "y") {
			SignUpDB();
		}

		login();
	}

	void SignUpDB() {
		connectDB();

		string Query = "";     // �����ݷ��� �����ϰ� ������ �ۼ�
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
		cout << setw(30) << "������" << endl;
		cout << endl;
		cout << setw(48) << "====================================" << endl;

		gotoxy(x - 2, y);
		cout << "> 1. �ݳ��ϱ� ";
		gotoxy(x, y + 2);
		cout << "2. �����ϱ�";
		gotoxy(x, y + 4);
		cout << "3. å �˻��ϱ�";
		gotoxy(x, y + 6);
		cout << "4. �ڽ� ������ ����";
		gotoxy(x, y + 8);
		cout << "5. å ����Ʈ ����";
		gotoxy(x, y + 10);
		cout << "6. ����";
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
		cout << "������" << endl;
		cout << setw(48) << "====================================" << endl;
		cout << endl;
		cout << setw(33) << "<�ݳ�>" << endl;
		gotoxy(10, 7);
		cout << "�ݳ��� å�� �Է��ϼ��� >> ";
		cin >> bookName;
		//updateDB();
		ReturnDB();
		gotoxy(10, 10);
		cout << "�ݳ��Ǽ̽��ϴ�.";
		
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

		
		Query2 += "UPDATE booklist SET borrow ='���Ⱑ��' WHERE title='";
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
		cout << setw(35) << "������" << endl;
		cout << endl;
		cout << setw(48) << "====================================" << endl;
		cout << endl;
		cout << setw(35) << "<����>" << endl;
		gotoxy(10, 7);
		cout << "������ å�� �Է��ϼ��� >> ";
		cin >> bookName;
		borrowDB();
		gotoxy(10, 10);
		cout << "����Ǽ̽��ϴ�." << endl;
		
		gotoxy(10, 12);
		cout << "�ݳ����� " << date << "�Դϴ�. ";

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

		Query2 += "UPDATE booklist SET borrow ='������' WHERE title='";
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
		cout << setw(35) << "������" << endl;
		cout << endl;
		cout << setw(48) << "====================================" << endl;
		cout << endl;
		cout << setw(35) << "<�˻�>" << endl;
		gotoxy(10, 7);
		cout << "�˻��� å�� �Է��ϼ���(Ű���� ����) >> ";
		cin >> bookName;
		gotoxy(10, 8);
		cout << "------------------------------------------";
		searchDB();  /* ����Ʈ ������ �ϱ�*/
		gotoxy(10, 15);
		cout << "------------------------------------------";
		gotoxy(10, 16);
		cout << "�� å�� �� �����ϰ� ������ å�� �ֳ���?(y/n) ";
		cin >> select;
		if (select == 'y') {
			gotoxy(10, 18);
			cout << "� å�� �����ϰ� ������ ����?(���� �Է�)>>";
			cin >> bookName;
			borrowDB();
			gotoxy(10, 20);
			cout << "����Ǽ̽��ϴ�." << endl;
			gotoxy(10, 22);
			cout << "�ݳ����� " << date<<"���� �Դϴ�. ";
		}
		else {
			gotoxy(10, 20);
			cout << "�������� ���ư��ϴ�.";
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
		res = mysql_store_result(&mysql);  // ��� ��� ����� �������� �ѹ��� �� �޾ƿ�.
		fields = mysql_num_fields(res);   // �ʵ� ���� ����

		int y = 10;
		while (row = mysql_fetch_row(res)) {   // �� ���� ����
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
		cout << setw(35) << "������" << endl;
		cout << endl;
		cout << setw(48) << "====================================" << endl;
		cout << endl;
		cout << setw(35) << "<ȸ��>" << endl;
		gotoxy(12, 8);
		cout << "���� å               ������                 �ݳ��� " << endl;
		gotoxy(12, 9);
		cout << "-----------------------------------------------------" << endl;
		/* å ����Ʈ �����ֱ�*/
		memberDB();

		Sleep(10000);
		//list();
	}

	void memberDB() {
		connectDB();

		mysql_query(&mysql, "select * from borrowbook");

		res = mysql_store_result(&mysql);  // ��� ��� ����� �������� �ѹ��� �� �޾ƿ�.
		fields = mysql_num_fields(res);   // �ʵ� ���� ����

		int y = 10;
		while (row = mysql_fetch_row(res)) {   // �� ���� ����
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
		cout << setw(35) << "������" << endl;
		cout << endl;
		cout << setw(48) << "====================================" << endl;
		cout << endl;
		cout << setw(35) << "<å ����Ʈ>" << endl << endl;

		selectDB();
		gotoxy(10, 18);
		cout << "-----------------------------------------------";
		
		
		gotoxy(10, 20);
		cout << "10�� �Ŀ� �������� ���ư��ڽ��ϴ�";
		
		Sleep(10000);
		//list();
	}

	void selectDB() {
		connectDB();

		mysql_query(&mysql, "select * from booklist");

		res = mysql_store_result(&mysql);  // ��� ��� ����� �������� �ѹ��� �� �޾ƿ�.
		fields = mysql_num_fields(res);   // �ʵ� ���� ����

		int y = 8;
		while (row = mysql_fetch_row(res)) {   // �� ���� ����
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