#pragma once
#include <string>

enum WeekdayIndex {
    MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY, DAYCONT, INVALID = DAYCONT
};

enum Grade {
    NORMAL, GOLD, SILVER, GRADECONT
};

struct weekdayInfo {
    std::string name;
    WeekdayIndex idx;
};

struct gradeInfo {
    std::string name;
    Grade seq;
};

static const weekdayInfo weekdayList[DAYCONT] = {
    {"monday", MONDAY},
    {"tuesday", TUESDAY},
    {"wednesday", WEDNESDAY},
    {"thursday", THURSDAY},
    {"friday", FRIDAY},
    {"saturday", SATURDAY},
    {"sunday", SUNDAY}
};

static const gradeInfo gradeList[GRADECONT] = {
    {"NORMAL", NORMAL},
    {"GOLD", GOLD},
    {"SILVER", SILVER}
};