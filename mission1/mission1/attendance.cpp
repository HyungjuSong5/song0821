#if 1
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "attendance.h"

using namespace std;


int main() {
	input();
}

void input() {
	ifstream fin{ "attendance_weekday_500.txt" }; //500개 데이터 입력
	for (int i = 0; i < 500; i++) {
		string name, weekday;
		fin >> name >> weekday;
		setTheBasicInfo(name, weekday);
	}

	for (int id = 1; id <= id_cnt; id++) {
		addBonousePoint(id);

		getGrade(id);

		printMemberInfo(id);
	}

	removeMember();
}

void setTheBasicInfo(string name, string weekday) {
	int id = getId(name);
	WeekdayIndex dayIndex = getWeekdayIndex(weekday);

	debug = isDebug(name);

	users[id].points += getBasicPoint(id, dayIndex);
}

void addBonousePoint(int id) {
	if (users[id].dat[WEDNESDAY] > 9) {
		users[id].points += BONUS_POINTS;
	}

	if (users[id].dat[SATURDAY] + users[id].dat[SUNDAY] > 9) {
		users[id].points += BONUS_POINTS;
	}
}

int getId(const string& name) {
	if (memberNameIdList.count(name) == 0) {
		memberNameIdList[name] = ++id_cnt;

		users[id_cnt].name = name;
		users[id_cnt].id = id_cnt;
	}
	return memberNameIdList[name];
}

bool isDebug(string name) {
	return name == "Daisy";
}

WeekdayIndex getWeekdayIndex(const string& weekday) {
	for (int i = 0; i < DAYCONT; i++) {
		if (weekdayList[i].name == weekday) {
			return weekdayList[i].idx;
		}
	}
	return INVALID;
}

int getBasicPoint(int id, WeekdayIndex index) {
	int add_point = 0;

	switch (index) {
	case MONDAY:
	case TUESDAY:
	case THURSDAY:
	case FRIDAY:
		add_point = 1;
		break;
	case WEDNESDAY:
		add_point = 3;
		break;
	case SATURDAY:
	case SUNDAY:
		add_point = 2;
		break;
	}

	users[id].dat[index] += 1;
	return add_point;
}

void removeMember()
{
	std::cout << "\n";
	std::cout << "Removed player\n";
	std::cout << "==============\n";
	for (int id = 1; id <= id_cnt; id++) {
		if (users[id].grade != GOLD && users[id].grade != SILVER && users[id].dat[WEDNESDAY] == 0 && (users[id].dat[SATURDAY] + users[id].dat[SUNDAY]) == 0) {
			std::cout << users[id].name << "\n";
		}
	}
}

void printMemberInfo(int id)
{
	cout << "NAME : " << users[id].name << ", ";
	cout << "POINT : " << users[id].points << ", ";
	cout << "GRADE : " << gradeList[users[id].grade].name << "\n";
}

void getGrade(int id)
{
	if (users[id].points >= 50) {
		users[id].grade = GOLD;
	}
	else if (users[id].points >= 30) {
		users[id].grade = SILVER;
	}
	else {
		users[id].grade = NORMAL;
	}
}

#endif