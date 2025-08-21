#include "attendance.h"
#include "IUserFactory.h"
#include "userFactory.h"

#ifdef _DEBUG
#include <gmock/gmock.h>

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#else
int main() {
    UserFactory factory;
    AttendanceProcessor processor(&factory);
    processor.input();
}

#endif