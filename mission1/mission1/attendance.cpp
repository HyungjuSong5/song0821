#if 1
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

enum WeekdayIndex {
	MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY, DAYCONT, INVALID = DAYCONT
};

enum Grade {
	NORMAL, GOLD, SILVER, GRADECONT
};

struct weekdayInfo {
	string name;
	WeekdayIndex idx;
};

weekdayInfo weekdayList[DAYCONT] = {
	{"monday", MONDAY},
	{"tuesday", TUESDAY},
	{"wednesday", WEDNESDAY},
	{"thursday", THURSDAY},
	{"friday", FRIDAY},
	{"saturday", SATURDAY},
	{"sunday", SUNDAY}
};

struct gradeInfo {
	string name;
	Grade seq;
};

gradeInfo gradeList[GRADECONT] = {
	{"NORMAL", NORMAL},
	{"GOLD", GOLD},
	{"SILVER", SILVER}
};

struct User {
	string name;
	int id;
	int points;
	int grade;
	int dat[7]; // 0: Monday, 1: Tuesday, 2: Wednesday, 3: Thursday, 4: Friday, 5: Saturday, 6: Sunday
};

User users[100]; // Assuming a maximum of 100 users

struct Node {
	string w;
	string wk;
};

map<string, int> memberNameIdList;
int id_cnt = 0;

//dat[사용자ID][요일]
int dat[100][100];
int points[100];
int grade[100];
string names[100];

int wed[100];
int weeken[100];

bool debug = false;

void getGrade(int id);
void printMemberInfo(int id);
int getId(const string& name);
bool isDebug(string name);
void removeMember();
int getBasicPoint(int id, WeekdayIndex index);
WeekdayIndex getWeekdayIndex(const string& weekday);


void setTheBasicInfo(string name, string weekday) {
	int id = getId(name);
	WeekdayIndex dayIndex = getWeekdayIndex(weekday);

	debug = isDebug(name);
	points[id] += getBasicPoint(id, dayIndex);
}

void addBonousePoint(int id) {
	if (dat[id][2] > 9) { // 수요일
		points[id] += 10;
	}

	if (dat[id][5] + dat[id][6] > 9) { // 주말
		points[id] += 10;
	}
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

int getId(const string& name) {
	if (memberNameIdList.count(name) == 0) {
		memberNameIdList[name] = ++id_cnt;
		names[id_cnt] = name;
	}
	return memberNameIdList[name];
}

bool isDebug(string name) {
	if (name == "Daisy") {
		return true;
	}
	return false;
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
		wed[id] += 1;
		break;
	case SATURDAY:
	case SUNDAY:
		add_point = 2;
		weeken[id] += 1;
		break;
	}

	//사용자ID별 요일 데이터에 1씩 증가
	dat[id][index] += 1;
	return add_point;
}
void removeMember()
{
	std::cout << "\n";
	std::cout << "Removed player\n";
	std::cout << "==============\n";
	for (int id = 1; id <= id_cnt; id++) {

		if (grade[id] != GOLD && grade[id] != SILVER && wed[id] == 0 && weeken[id] == 0) {
			std::cout << names[id] << "\n";
		}
	}
}

void printMemberInfo(int id)
{
	cout << "NAME : " << names[id] << ", ";
	cout << "POINT : " << points[id] << ", ";
	cout << "GRADE : " << gradeList[grade[id]].name << "\n";
}

void getGrade(int id)
{
	if (points[id] >= 50) {
		grade[id] = GOLD;
	}
	else if (points[id] >= 30) {
		grade[id] = SILVER;
	}
	else {
		grade[id] = NORMAL;
	}
}

int main() {
	input();
}

#endif