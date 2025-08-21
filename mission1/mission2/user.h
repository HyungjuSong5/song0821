#pragma once
#include "IUser.h"
#include <string>
#include <array>

class User : public IUser {
    std::string name;
    int id;
    int points;
    int grade;
    std::array<int, 7> attendance;
public:
    User(const std::string& name, int id)
        : name(name), id(id), points(0), grade(0), attendance{ 0 } {
    }

    std::string GetName() const override { return name; }
    int GetId() const override { return id; }
    int GetPoints() const override { return points; }
    int GetGrade() const override { return grade; }
    void AddPoints(int pts) override { points += pts; }
    void AddAttendance(int weekday) override { attendance[weekday] += 1; }
    int GetAttendance(int weekday) const { return attendance[weekday]; }
    void SetGrade(int g) { grade = g; }
}; 
