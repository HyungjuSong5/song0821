#pragma once
#include "IUserFactory.h"
#include "User.h"

class UserFactory : public IUserFactory {
public:
    std::unique_ptr<IUser> CreateUser(const std::string& name, int id) override {
        return std::make_unique<User>(name, id);
    }
};
