#include <iostream>
#include <iostream>
#include <winsock.h>
#include <mysql.h>
#include <string>
#include <sstream>
#include <time.h>
#include <ctime>
using namespace std;

#pragma comment(lib, "libmysql.lib")


class Date {
	int year_;
	int month_;  // 1 ���� 12 ����.
	int day_;    // 1 ���� 31 ����.
	

public:
	void SetDate(int year, int month, int date);
	void AddDay(int inc);
	void AddMonth(int inc);
	void AddYear(int inc);

	// �ش� ���� �� �� ���� ���Ѵ�.
	int GetCurrentMonthTotalDays(int year, int month);

	void ShowDate();
	string getDate();
};

void Date::SetDate(int year, int month, int day) {
	year_ = year;
	month_ = month;
	day_ = day;
}

int Date::GetCurrentMonthTotalDays(int year, int month) {
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

void Date::AddDay(int inc) {
	while (true) {
		// ���� ���� �� �� ��
		int current_month_total_days = GetCurrentMonthTotalDays(year_, month_);

		// ���� �� �ȿ� ���´ٸ�;
		if (day_ + inc <= current_month_total_days) {
			day_ += inc;
			return;
		}
		else {
			// �����޷� �Ѿ�� �Ѵ�.
			inc -= (current_month_total_days - day_ + 1);
			day_ = 1;
			AddMonth(1);
		}
	}
}


void Date::AddMonth(int inc) {
	AddYear((inc + month_ - 1) / 12);
	month_ = month_ + inc % 12;
	month_ = (month_ == 12 ? 12 : month_ % 12);
}

void Date::AddYear(int inc) { year_ += inc; }

void Date::ShowDate() {
	cout << "������ " << year_ << " �� " << month_ << " �� " << day_
		<< " �� �Դϴ� " << std::endl;
}

string Date::getDate() {
	AddDay(7);
	stringstream str1;
	stringstream str2;
	stringstream str3;
	string result;

	str1 << year_;
	str2 << month_;
	str3 << day_;


	result = str1.str() + "-" + str2.str();
	result.append("-" + str3.str());

	return result;
}

int main() {
	Date day;
	day.SetDate(2020,12,07);
	day.ShowDate();
	

	day.AddDay(7);
	day.ShowDate();
	//cout << day.getDate() << endl;

	struct tm *curr_tm;
	time_t curr_time = time(nullptr);

	
	curr_tm=localtime(&curr_time);
	int curr_year = curr_tm->tm_year + 1900;
	int curr_month = curr_tm->tm_mon + 1;
	int curr_day = curr_tm->tm_mday;
	day.SetDate(curr_year, curr_month, curr_day);
	day.AddDay(7);
	day.ShowDate();
	//cout << curr_year << "-" << curr_month << "-" << curr_day;

	return 0;
}