#include <iostream>
#include <sstream>
#include <vector>

#include "Command.hpp"

#include "Ticket.hpp"
#include "TicketManager.hpp"
#include "TicketTypes.hpp"
#include "TicketVip.hpp"

#include "UserManager.hpp"
#include "User.hpp"


const std::string prompt = ">> ";
bool quitCalled = false;

UserManager gUserManager;
TicketManager gTicketManager;


inline void print_usage(std::string command)
{
    std::cerr << "[ERROR] Invalid usage of command '"
        << command << "'" << std::endl;
    std::cout << "[INFO]  Type 'help " + command + "' to find out more!"
        << std::endl;
}


void cmd_quit(std::vector<std::string> args)
{
    quitCalled = true;
}

void cmd_login(std::vector<std::string> args)
{
    if (args.size() == 3)
    {
        gUserManager.Login(args[1], args[2]);
        return;
    }

    if (args.size() == 1) {
        std::string name, password;

        std::cout << "User: ";
        std::cin >> name;
        std::cout << "Password: ";
        std::cin >> password;

        gUserManager.Login(name, password);
        return;
    }

    print_usage(args[0]);
}

void cmd_register(std::vector<std::string> args)
{
    if (args.size() == 3)
    {
        gUserManager.Register(args[1], args[2]);
        return;
    }

    if (args.size() == 1) {
        std::string name, password;

        std::cout << "User: ";
        std::cin >> name;
        std::cout << "Password: ";
        std::cin >> password;

        gUserManager.Register(name, password);
        return;
    }

    print_usage(args[0]);
}

void cmd_logout(std::vector<std::string> args)
{
    gUserManager.Logout();
}


void cmd_topup(std::vector<std::string> args)
{
    if (args.size() != 2)
    {
        print_usage(args[0]);
        return;
    }

    gUserManager.TopUp(std::stoi(args[1]));
}

void cmd_balance(std::vector<std::string> args)
{
    if (args.size() != 1)
    {
        print_usage(args[0]);
        return;
    }

    double balance = gUserManager.GetBalance();

    if (balance == -1.0f)
    {
        return;
    }

    std::cout << "Balance: $" << balance << std::endl;
}

void cmd_buy(std::vector<std::string> args)
{
    if (args.size() != 3)
    {
        print_usage(args[0]);
        return;
    }

    TicketType type = args[2] == "standard" ? TicketType::STANDARD
        : args[2] == "vip" ? TicketType::VIP
        : TicketType::STANDARD; // Default

    gUserManager.BuyTicket(gTicketManager, args[1], type);
}

void cmd_list(std::vector<std::string> args)
{
    if (args.size() != 2)
    {
        print_usage(args[0]);
        return;
    }

    if (args[1] == "events")
    {
        gTicketManager.ListAvailableEvents();
    }
    else if (args[1] == "tickets")
    {
        gUserManager.ListTickets();
    }
    else
    {
        std::cerr << "Could not list '" << args[1] << "': Unknown token"
            << std::endl;
    }
}


int main(int argc, const char* argv[])
{
    const std::vector<Command> commands
    {
        Command("quit", "exits the program", cmd_quit),
        Command("exit", "exits the program", cmd_quit),
        Command("login", "either starts the login prompt by simply typing 'login', "
                            "or you can type 'login [name] [password]'", cmd_login),
        Command("register", "either starts the register prompt by simply typing 'register', "
                         "or you can type 'register [name] [password]'", cmd_register),
        Command("logout", "logout the current user, will fail if not currently logged in!", cmd_logout),
        Command("topup", "Tops up the current balance by given amount. Usage: 'topup [amount]'", cmd_topup),
        Command("balance", "Prints the current balance", cmd_balance),
        Command("buy", "Try to buy a ticket at an event. Usage: 'buy [event name] [standard/vip]", cmd_buy),
        Command("list", "Lists all available events. Usage: 'list [events/tickets]'", cmd_list)
    };

    gTicketManager.InitFromFile(argv[1]);

    std::string line;

    while (!quitCalled)
    {
        std::cout << prompt;
        std::getline(std::cin, line);

        std::vector<std::string> tokens;
        {
            std::stringstream sline(line);
            std::string aux;

            while (std::getline(sline, aux, ' '))
            {
                tokens.push_back(aux);
            }
        }

        if (tokens.empty())
        {
            continue;
        }

        if (tokens[0] == "help")
        {
            for (auto const& command : commands)
            {
                if (tokens.size() != 1 && tokens[1] != command.GetName())
                    continue;

                std::cout << command.GetName()
                    << " -> "
                    << command.GetDescription()
                    << std::endl;
            }

            continue;
        }

        bool foundCommand = false;

        for (auto const& command : commands)
        {
            if (tokens[0] == command.GetName())
            {
                command.Run(tokens);
                foundCommand = true;
                break;
            }
        }

        if (!foundCommand)
        {
            std::cerr << "Unknown command: " << tokens[0] << std::endl;
            std::cout << "Type 'help' for available commands, or "
                << "'help [subcommand]' to print info about a specific command"
                << std::endl;
        }
    }

    return 0;
}

