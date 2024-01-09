#pragma once

#include <cstddef>
#include <string>

class Event
{
public:
    Event(size_t stdCount, double stdCost,
        size_t vipCount, double vipCost,
        std::string const& name)
        : mStdLeft(stdCount)
        , mStdCost(stdCost)
        , mVipLeft(vipCount)
        , mVipCost(vipCost)
        , mName(name)
    {}

    std::string const& GetName() const { return mName; }

    size_t GetStdLeft() const { return mStdLeft; }
    size_t GetVipLeft() const { return mVipLeft; }
    double GetStdCost() const { return mStdCost; }
    double GetVipCost() const { return mVipCost; }

    void SellTicketStd() { mStdLeft--; }
    void SellTicketVip() { mVipLeft--; }

private:
    size_t mStdLeft;
    double mStdCost;

    size_t mVipLeft;
    double mVipCost;

    std::string const mName;
};

