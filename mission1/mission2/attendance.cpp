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

    int getId(const string& name) {
        if (memberNameIdList.count(name) == 0) {
            memberNameIdList[name] = ++id_cnt;
            users.push_back(userFactory->CreateUser(name, id_cnt));
        }
        return memberNameIdList[name] - 1; // vector index
    }

    WeekdayIndex getWeekdayIndex(const string& weekday) {
        for (int i = 0; i < DAYCONT; i++) {
            if (weekdayList[i].name == weekday) {
                return weekdayList[i].idx;
            }
        }
        return INVALID;
    }

    bool isDebug(const string& name) {
        return name == "Daisy";
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
        users[id]->AddAttendance(index);
        return add_point;
    }

    void setTheBasicInfo(const string& name, const string& weekday) {
        int id = getId(name);
        WeekdayIndex dayIndex = getWeekdayIndex(weekday);
        if (dayIndex == INVALID) {
            // 잘못된 요일 입력은 무시
            std::cerr << "Invalid weekday: " << weekday << " for user: " << name << std::endl;
            return;
        }
        debug = isDebug(name);
        users[id]->AddPoints(getBasicPoint(id, dayIndex));
    }

    void addBonousePoint(int id) {
        // 수요일 출석 10회 이상
        if (users[id]->GetAttendance(WEDNESDAY) > 9) {
            users[id]->AddPoints(10);
        }
        // 주말 출석 합 10회 이상
        if (users[id]->GetAttendance(SATURDAY) + users[id]->GetAttendance(SUNDAY) > 9) {
            users[id]->AddPoints(10);
        }
    }

    void getGrade(int id) {
        int pts = users[id]->GetPoints();
        if (pts >= 50) {
            users[id]->SetGrade(GOLD);
        }
        else if (pts >= 30) {
            users[id]->SetGrade(SILVER);
        }
        else {
            users[id]->SetGrade(NORMAL);
        }
    }

    void printMemberInfo(int id) {
        cout << "NAME : " << users[id]->GetName() << ", ";
        cout << "POINT : " << users[id]->GetPoints() << ", ";
        cout << "GRADE : " << gradeList[users[id]->GetGrade()].name << "\n";
    }

    void removeMember() {
        cout << "\nRemoved player\n==============\n";
        for (size_t id = 0; id < users.size(); id++) {
            int grade = users[id]->GetGrade();
            if (grade != GOLD && grade != SILVER &&
                users[id]->GetAttendance(WEDNESDAY) == 0 &&
                users[id]->GetAttendance(SATURDAY) == 0 &&
                users[id]->GetAttendance(SUNDAY) == 0) {
                cout << users[id]->GetName() << "\n";
            }
        }
    }

    void input() {
        ifstream fin{ "attendance_weekday_500.txt" };
        for (int i = 0; i < 500; i++) {
            string name, weekday;
            fin >> name >> weekday;
            setTheBasicInfo(name, weekday);
        }
        for (size_t id = 0; id < users.size(); id++) {
            addBonousePoint(id);
            getGrade(id);
            printMemberInfo(id);
        }
        removeMember();
    }
};

int main() {
    UserFactory factory;
    AttendanceProcessor processor(&factory);
    processor.input();
}