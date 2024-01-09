#pragma once

#include <string>

#include "TicketTypes.hpp"

using TicketId = size_t;

class Ticket
{
public:
    Ticket(std::string const& owner,
        std::string const& event,
        size_t cost,
        size_t ticketNumber)
        : mOwner(owner)
        , mEvent(event)
        , mCost(cost)
        , mId(std::hash<std::string>()(event + std::to_string(ticketNumber)))
    {}

    TicketId GetId() const { return mId; }
    double GetCost() const { return mCost; }
    std::string const& GetOwner() { return mOwner; }

private:
    const TicketType mType = TicketType::STANDARD;
    const TicketId mId;

    std::string mOwner = "";
    std::string const mEvent;
    double const mCost;
};

