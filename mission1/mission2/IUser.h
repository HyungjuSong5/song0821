#pragma once
#include <string>

class IUser {
public:
    virtual ~IUser() = default;
    virtual std::string GetName() const = 0;
    virtual int GetId() const = 0;
    virtual int GetPoints() const = 0;
    virtual int GetGrade() const = 0;
    virtual void AddPoints(int points) = 0;
    virtual void AddAttendance(int weekday) = 0;
	virtual int GetAttendance(int weekday) const = 0;
	virtual void SetGrade(int grade) = 0;
};