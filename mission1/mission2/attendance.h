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
};

