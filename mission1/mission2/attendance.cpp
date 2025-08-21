#include "attendance.h"

int AttendanceProcessor::getId(const string& name) {
    if (memberNameIdList.count(name) == 0) {
        memberNameIdList[name] = ++id_cnt;
        users.push_back(userFactory->CreateUser(name, id_cnt));
    }
    return memberNameIdList[name] - 1; // vector index
}

WeekdayIndex AttendanceProcessor::getWeekdayIndex(const string& weekday) {
    for (int i = 0; i < DAYCONT; i++) {
        if (weekdayList[i].name == weekday) {
            return weekdayList[i].idx;
        }
    }
    return INVALID;
}

bool AttendanceProcessor::isDebug(const string& name) {
    return name == "Daisy";
}

int AttendanceProcessor::getBasicPoint(int id, WeekdayIndex index) {
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

void AttendanceProcessor::setTheBasicInfo(const string& name, const string& weekday) {
    int id = getId(name);
    WeekdayIndex dayIndex = getWeekdayIndex(weekday);
    if (dayIndex == INVALID) {
        std::cerr << "Invalid weekday: " << weekday << " for user: " << name << std::endl;
        return;
    }
    debug = isDebug(name);
    users[id]->AddPoints(getBasicPoint(id, dayIndex));
}

void AttendanceProcessor::addBonousePoint(int id) {
    if (users[id]->GetAttendance(WEDNESDAY) > BONUS_THRESHOLD) {
        users[id]->AddPoints(BONUS_POINTS);
    }
    if (users[id]->GetAttendance(SATURDAY) + users[id]->GetAttendance(SUNDAY) > BONUS_THRESHOLD) {
        users[id]->AddPoints(BONUS_POINTS);
    }
}

void AttendanceProcessor::getGrade(int id) {
    int pts = users[id]->GetPoints();
    if (pts >= GOLDGRADE_THRESHOLD) {
        users[id]->SetGrade(GOLD);
    }
    else if (pts >= SILVERGRADE_THRESHOLD) {
        users[id]->SetGrade(SILVER);
    }
    else {
        users[id]->SetGrade(NORMAL);
    }
}

void AttendanceProcessor::printMemberInfo(int id) {
    cout << "NAME : " << users[id]->GetName() << ", ";
    cout << "POINT : " << users[id]->GetPoints() << ", ";
    cout << "GRADE : " << gradeList[users[id]->GetGrade()].name << "\n";
}

void AttendanceProcessor::removeMember() {
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

void AttendanceProcessor::input() {
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

