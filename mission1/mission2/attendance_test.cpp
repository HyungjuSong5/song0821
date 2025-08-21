#include "gmock/gmock.h"
#include "attendance.h"
#include "IUser.h"
#include "IUserFactory.h"
#include "userFactory.h"
#include "type.h"
#include "user.h"

class AttendanceProcessorTest : public ::testing::Test {
protected:
    UserFactory factory;
    AttendanceProcessor attendpro;

    AttendanceProcessorTest() : attendpro(&factory) {}

    void SetUp() override {
    }
    void TearDown() override {
    }
};

// IUser
TEST(UserFactoryTest, CreateUserBasic) {
    UserFactory factory;
    auto user = factory.CreateUser("TestUser", 42);

    for (int idx = MONDAY; idx < DAYCONT; idx++) {
        user->AddAttendance(idx);
    }
	user->AddPoints(11);
    user->SetGrade(NORMAL);

    ASSERT_NE(user, nullptr);
    EXPECT_EQ(user->GetName(), "TestUser");
    EXPECT_EQ(user->GetId(), 42);
    EXPECT_EQ(user->GetPoints(), 11);
    EXPECT_EQ(user->GetGrade(), NORMAL);
    EXPECT_EQ(user->GetAttendance(WEDNESDAY), 1);
}

// AttendanceProcessor
TEST_F(AttendanceProcessorTest, TESTGetID) {
    for (int idx = 0; idx < 10; ++idx) {
        auto user = factory.CreateUser("TestUser" + std::to_string(idx), idx);
        attendpro.setTheBasicInfo(user->GetName(), "monday");
        EXPECT_EQ(attendpro.getId(user->GetName()), idx);
	}
}

TEST_F(AttendanceProcessorTest, TESTGetWEEKIDEXVALID) {
    EXPECT_EQ(attendpro.getWeekdayIndex("monday"), MONDAY);
    EXPECT_EQ(attendpro.getWeekdayIndex("tuesday"), TUESDAY);
    EXPECT_EQ(attendpro.getWeekdayIndex("wednesday"), WEDNESDAY);
    EXPECT_EQ(attendpro.getWeekdayIndex("thursday"), THURSDAY);
    EXPECT_EQ(attendpro.getWeekdayIndex("friday"), FRIDAY);
    EXPECT_EQ(attendpro.getWeekdayIndex("saturday"), SATURDAY);
	EXPECT_EQ(attendpro.getWeekdayIndex("sunday"), SUNDAY);
    EXPECT_EQ(attendpro.getWeekdayIndex("2022"), INVALID);
}

TEST_F(AttendanceProcessorTest, TESTISDEBUG) {
    string name = "Daisy";
    EXPECT_EQ(attendpro.isDebug(name), true);

    name = "Ryan";
    EXPECT_EQ(attendpro.isDebug(name), false);
}

TEST_F(AttendanceProcessorTest, TESTGETBASICPOINT) {
    for (int idx = 0; idx < 2; ++idx) {
        auto user = factory.CreateUser("TestUser" + std::to_string(idx), idx);
        attendpro.setTheBasicInfo(user->GetName(), "monday");
    }

    EXPECT_EQ(attendpro.getBasicPoint(1, MONDAY), 1);
    EXPECT_EQ(attendpro.getBasicPoint(1, TUESDAY), 1);
    EXPECT_EQ(attendpro.getBasicPoint(1, THURSDAY), 1);
    EXPECT_EQ(attendpro.getBasicPoint(1, FRIDAY), 1);
    EXPECT_EQ(attendpro.getBasicPoint(1, WEDNESDAY), 3);
    EXPECT_EQ(attendpro.getBasicPoint(1, SATURDAY), 2);
    EXPECT_EQ(attendpro.getBasicPoint(1, SUNDAY), 2);
}

TEST_F(AttendanceProcessorTest, TESTSETTHEBAISCINFOINVALID) {
    string name = "RYAN";
    string weekday = "2022";
    
    attendpro.setTheBasicInfo(name, weekday);
}

TEST_F(AttendanceProcessorTest, TESTSETTHEBAISCINFOVALID) {
    string name = "RYAN";
    string weekday = "wednesday";

    attendpro.setTheBasicInfo(name, weekday);
}

TEST_F(AttendanceProcessorTest, TESTADDBONOUSEPOINTWED) {
    attendpro.setTheBasicInfo("TestUser", "saturday");
    int id = attendpro.getId("TestUser");
    IUser& user = attendpro.getUser(id);

    user.AddPoints(0);
    for (int idx = 0; idx < 10; ++idx) {
        user.AddAttendance(WEDNESDAY);
        user.AddPoints(3);
    }
    
    cout << user.GetPoints() << "\n";

    attendpro.addBonousePoint(attendpro.getId(user.GetName()));
	EXPECT_EQ(user.GetPoints(), 42);

    attendpro.getGrade(attendpro.getId(user.GetName()));
    EXPECT_EQ(user.GetGrade(), SILVER);
}
TEST_F(AttendanceProcessorTest, TESTADDBONOUSEPOINTWEEKEN) {
    attendpro.setTheBasicInfo("TestUser", "saturday");
    int id = attendpro.getId("TestUser");
    IUser& user = attendpro.getUser(id);

    for (int idx = 0; idx < 10; ++idx) {
        attendpro.getBasicPoint(id, idx % 2 ? SUNDAY : SATURDAY);
        user.AddAttendance(idx % 2 ? SUNDAY : SATURDAY);
    }
    user.AddPoints(40);

    attendpro.addBonousePoint(id);

    EXPECT_EQ(user.GetPoints(), 52);

    attendpro.getGrade(id);
    EXPECT_EQ(user.GetGrade(), GOLD);
}

TEST_F(AttendanceProcessorTest, TESTGETGRADE) {
    attendpro.input();
}