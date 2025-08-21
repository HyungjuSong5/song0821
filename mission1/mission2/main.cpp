#include "attendance.h"
#include "IUserFactory.h"
#include "userFactory.h"


int main() {
    UserFactory factory;
    AttendanceProcessor processor(&factory);
    processor.input();
}