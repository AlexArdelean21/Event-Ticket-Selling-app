#pragma once

#include <string>
#include <vector>
#include <functional>

class Command
{
public:
    Command(std::string const& name,
        std::string const& description,
        std::function<void(std::vector<std::string>)> const& function)
        : mName(name)
        , mDescription(description)
        , mFunction(function)
    {}

    std::string const& GetName() const { return mName; }
    std::string const& GetDescription() const { return mDescription; }

    void Run(std::vector<std::string> args) const
    {
        return mFunction(args);
    }

private:
    std::string const mName;
    std::string const mDescription;

    std::function<void(std::vector<std::string>)> const mFunction;

};

