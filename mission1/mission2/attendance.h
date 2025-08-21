#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "IUser.h"
#include "user.h"
#include "IUserFactory.h"
#include "userFactory.h"
#include "type.h"

using namespace std;

class AttendanceProcessor {
    map<string, int> memberNameIdList;
    vector<std::unique_ptr<IUser>> users;
    IUserFactory* userFactory;
    int id_cnt = 0;
    bool debug = false;
	const int MAX_USERS = 100;
	const int GOLDGRADE_THRESHOLD = 50;
	const int SILVERGRADE_THRESHOLD = 30;
	const int BONUS_POINTS = 10;
	const int BONUS_THRESHOLD = 9;
public:
    AttendanceProcessor(IUserFactory* factory) : userFactory(factory) {}

    int getId(const string& name);
    WeekdayIndex getWeekdayIndex(const string& weekday); 
    bool isDebug(const string& name);
    int getBasicPoint(int id, WeekdayIndex index);
    void setTheBasicInfo(const string& name, const string& weekday); 
    void addBonousePoint(int id);
    void getGrade(int id);
    void printMemberInfo(int id);
    void removeMember(); 
    void input();
    IUser& getUser(int id) const {
        if (id < 0 || id >= users.size()) {
            throw std::out_of_range("Invalid user ID");
        }
        return *(users[id]);
	}
};

