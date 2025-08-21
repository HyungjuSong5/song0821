#pragma once
#include "IUser.h"
#include <string>
#include <memory>

class IUserFactory {
public:
    virtual ~IUserFactory() = default;
    virtual std::unique_ptr<IUser> CreateUser(const std::string& name, int id) = 0;
};
