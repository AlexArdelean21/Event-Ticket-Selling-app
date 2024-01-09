#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Event.hpp"

#include "Ticket.hpp"
#include "TicketTypes.hpp"
#include "TicketVip.hpp"




class TicketManager
{
public:
    TicketManager() {}

    TicketManager(std::string const& filepath)
    {
        InitFromFile(filepath);
    }

    void InitFromFile(std::string const& filepath)
    {
        std::ifstream in(filepath);
        std::string line;

        enum ParserState {
            OUTSIDE_EVENT_BLOCK,
            EVENT_BLOCK,
        } state = OUTSIDE_EVENT_BLOCK;

        std::string eventName{};
        size_t stdCount = 0, vipCount = 0;
        double stdCost = -1.0f, vipCost = -1.0f;

        while (std::getline(in, line))
        {
            std::vector<std::string> tokens;
            {
                std::stringstream sline(line);
                std::string aux;

                while (std::getline(sline, aux, ' '))
                {
                    tokens.push_back(aux);

                }
            }

            if (tokens.empty() || tokens[0].empty() || tokens[0][0] == '#')
            {
                continue;
            }

            /* File format
             *
            event Neversea
            ticket standard count 5000
            ticket standard price 500
            ticket vip count 200
            ticket vip price 800
            end
            */

            switch (state) {
            case OUTSIDE_EVENT_BLOCK:
                if (tokens[0] == "event" && tokens.size() == 2)
                {
                    state = EVENT_BLOCK;
                    eventName = tokens[1];
                }
                else
                {
                    std::cerr << "[ERROR] Bad file format: Expected event block"
                        << std::endl;
                    exit(1);
                }
                break;
            case EVENT_BLOCK:
                if (tokens[0] == "ticket" && tokens.size() == 4)
                {
                    if (tokens[1] == "standard")
                    {
                        if (tokens[2] == "count")
                        {
                            stdCount = std::stoi(tokens[3]);
                        }
                        else if (tokens[2] == "price")
                        {
                            stdCost = std::stof(tokens[3]);
                        }
                        else
                        {
                            std::cerr << "[ERROR] Bad file format: Expected count/price"
                                << std::endl;
                            exit(1);
                        }
                    }
                    else if (tokens[1] == "vip")
                    {
                        if (tokens[2] == "count")
                        {
                            vipCount = std::stoi(tokens[3]);
                        }
                        else if (tokens[2] == "price")
                        {
                            vipCost = std::stof(tokens[3]);
                        }
                        else
                        {
                            std::cerr << "[ERROR] Bad file format: Expected count/price"
                                << std::endl;
                            exit(1);
                        }
                    }
                    else
                    {
                        std::cerr << "[ERROR] Bad file format: Expected standard/vip"
                            << std::endl;
                        exit(1);
                    }
                }
                else if (tokens[0] == "end" && tokens.size() == 1)
                {
                    if (!eventName.empty()
                        && stdCount && vipCount
                        && stdCost >= 0 && vipCost >= 0)
                    {
                        mEvents.push_back(Event(stdCount, stdCost, vipCount, vipCost, eventName));
                        eventName = "";
                        stdCount = 0;
                        vipCount = 0;
                        stdCost = -1.0f;
                        vipCost = -1.0f;

                        state = OUTSIDE_EVENT_BLOCK;
                    }
                    else
                    {
                        std::cerr << "[ERROR] Bad file format: Incomplete event data"
                            << std::endl;

                        std::cerr << "Data dump:" << std::endl
                            << "\t" << "EvnName  = " << eventName << std::endl
                            << "\t" << "stdCount = " << stdCount << std::endl
                            << "\t" << "vipCount = " << vipCount << std::endl
                            << "\t" << "stdCost  = " << stdCost << std::endl
                            << "\t" << "vipCost  = " << vipCost << std::endl;
                        exit(1);
                    }
                }
                break;
            }
        }

        in.close();
    }

    void ListAvailableEvents()
    {
        for (auto const& event : mEvents)
        {
            std::cout << "Name: " << event.GetName() << " | Tickets:" << std::endl
                << "\tStandard - $" << event.GetStdCost()
                << ", remaining: " << event.GetStdLeft() << std::endl
                << "\tVIP      - $" << event.GetVipCost()
                << ", remaining: " << event.GetVipLeft() << std::endl;
        }
    }

    /*
     * Returns '-1.0f in case of non-existent eventName'
     */
    double GetEventPrice(std::string const& eventName, TicketType type)
    {
        for (auto const& event : mEvents)
        {
            if (eventName == event.GetName())
            {
                return type == TicketType::STANDARD ? event.GetStdCost()
                    : event.GetVipCost();
            }
        }

        return -1.0f;
    }
    /*
     * Returns '0' in case of failure
     */
    TicketId PrintTicket(std::string const& owner,
        std::string const& eventName,
        TicketType type)
    {
        for (auto& event : mEvents)
        {
            if (eventName == event.GetName())
            {
                size_t ticketsLeft;
                double ticketCost;

                switch (type)
                {
                case TicketType::STANDARD:
                    ticketsLeft = event.GetStdLeft();
                    ticketCost = event.GetStdCost();
                    break;
                case TicketType::VIP:
                    ticketsLeft = event.GetVipLeft();
                    ticketCost = event.GetVipCost();
                }


                if (ticketsLeft == 0)
                {
                    std::cerr << "[ERROR] Not enough tickets of this type left at '"
                        << eventName << "'" << std::endl;
                    return 0;
                }

                if (type == TicketType::VIP)
                {
                    event.SellTicketVip();
                }
                else if (type == TicketType::STANDARD)
                {
                    event.SellTicketStd();
                }

                Ticket ticket("", eventName, ticketCost, event.GetStdLeft() + event.GetVipLeft());
                mSoldTickets.push_back(ticket);
                return ticket.GetId();
            }
        }

        std::cerr << "[ERROR] Unknown event!" << std::endl;
        return 0;
    }

    Ticket const* GetTicketData(TicketId id)
    {
        for (auto const& ticket : mSoldTickets)
        {
            if (id == ticket.GetId())
            {
                return &ticket;
            }
        }

        return nullptr;
    }

private:
    std::vector<Event> mEvents;
    std::vector<Ticket> mSoldTickets;
    double mBalance;
};

