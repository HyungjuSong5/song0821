#pragma once
#include <string>
#include <map>

using namespace std;

const int BONUS_POINTS = 10;

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
	int dat[DAYCONT];
};

User users[100]; // Assuming a maximum of 100 users

struct Node {
	string w;
	string wk;
};

map<string, int> memberNameIdList;
int id_cnt = 0;
bool debug = false;

void getGrade(int id);
void printMemberInfo(int id);
int getId(const string& name);
bool isDebug(string name);
void removeMember();
int getBasicPoint(int id, WeekdayIndex index);
WeekdayIndex getWeekdayIndex(const string& weekday);
void input();
void setTheBasicInfo(string name, string weekday);
void addBonousePoint(int id);