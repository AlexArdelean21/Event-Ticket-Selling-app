#pragma once

#include <cstddef>
#include <functional>

#include "Ticket.hpp"


class TicketVip : public Ticket
{
public:
    TicketVip(std::string const& owner,
        std::string const& event,
        size_t cost,
        size_t ticketNumber)
        : Ticket(owner, event, cost, ticketNumber)
    {}
private:
    const TicketType mType = TicketType::VIP;
};

