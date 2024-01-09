#pragma once

#include <iostream>
#include <vector>

#include "User.hpp"


class UserManager
{
public:
    ~UserManager()
    {
        if (mUserCurrent)
        {
            Logout();
        }
    }

    bool Register(std::string const& name, std::string const& password)
    {
        if (password.size() == 0)
        {
            std::cerr << "[ERROR] Cannot use empty password!" << std::endl;
            return false;
        }

        for (auto const& user : mUsers)
        {
            if (name == user->GetName())
            {
                std::cerr << "[ERROR] Name already taken!" << std::endl;
                return false;
            }
        }

        std::cout << "[INFO]  Succesfully registered user '" << name << "'"
            << std::endl;

        mUsers.push_back(new User(name, password));
        return true;
    }

    bool Login(std::string const& name, std::string const& password)
    {
        if (mUserCurrent)
        {
            std::cerr << "[ERROR] Already logged in as '"
                + mUserCurrent->GetName() << "'" << std::endl;
            return false;
        }

        for (auto const& user : mUsers)
        {
            if (name == user->GetName())
            {
                if (!user->CheckCredentials(name, password))
                {
                    std::cerr << "[ERROR] Invalid password!" << std::endl;
                    return false;
                }

                std::cout << "[INFO]  Logged in succesfully as '" + name << "'"
                    << std::endl;

                mUserCurrent = user;
                return true;
            }
        }

        std::cerr << "[ERROR] Username not existent in database!" << std::endl;

        return false;
    }

    bool Logout()
    {
        if (!mUserCurrent)
        {
            std::cerr << "[ERROR] Not logged in!" << std::endl;
            return false;
        }

        mUserCurrent = nullptr;

        std::cout << "[INFO]  Logout succesful!" << std::endl;
        return true;
    }
 

    bool TopUp(double amount)
    {
        if (!mUserCurrent)
        {
            std::cerr << "[ERROR] Not logged in!" << std::endl;
            return false;
        }

        mUserCurrent->TopUp(amount);
        return true;
    }

    /*
     * Returns -1.0f in case of errors
     */
    double GetBalance()
    {
        if (!mUserCurrent)
        {
            std::cerr << "[ERROR] Not logged in!" << std::endl;
            return -1.0f;
        }

        return mUserCurrent->GetBalance();
    }



private:
    std::vector<User*> mUsers;
    User* mUserCurrent = nullptr;
};

