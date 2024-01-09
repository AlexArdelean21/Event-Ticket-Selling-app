#pragma once

#include <iostream>
#include <string>
#include <vector>

class User
{
public:
    User(std::string const& name, std::string const& password)
        : mName(name)
        , mPasswordHash(std::hash<std::string>()(name + password))
    {}

    bool CheckCredentials(std::string const& name, std::string const& password) const
    {
        return mName == name
            && mPasswordHash == std::hash<std::string>()(name + password);
    }

    std::string const& GetName() const { return mName; }
    double GetBalance() const { return mBalance; }

    bool Pay(double amount)
    {
        if (amount > mBalance)
        {
            std::cerr << "[ERROR] Insufficient balance! Missing "
                << amount - mBalance << std::endl;
            return false;
        }

        mBalance -= amount;
        return true;
    }


    void TopUp(double amount) { mBalance += amount; }

private:
    std::string const mName;
    const size_t      mPasswordHash;

    double mBalance = 0.0f;

};

