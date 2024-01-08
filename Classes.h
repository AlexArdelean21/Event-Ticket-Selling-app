#pragma once
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class Util { // I should add a variable (an array [rows][seats]) and a method that will take fill up the spots
public:
    static char* copyArray(const char* source);
};

//---------------------------------------------------------------------------------- Event Location -------------------------------------------------------------------------------------------------
class EventLocation {
    const char* locationName = nullptr;
    int maxSeats = 0; 
    int rows = 0;  
   
public:
    EventLocation();  // Ctors
    EventLocation(const char* _locationName, int _maxSeats, int _rows);

    // Setters
    void setMaxSeats(int _maxSeats);
    void setRows(int _rows);

    // Gettrs
    const char* getLocationName();
    int getMaxSeats();
    int getRows();

    // D.ctor and C.ctor
    ~EventLocation(); 
    EventLocation(const EventLocation& e);

    // Overloaded operators
    EventLocation& operator=(const EventLocation& el);
    EventLocation operator++(int);
    EventLocation operator++();
    friend istream& operator>>(istream& input, EventLocation& el);
    explicit operator int();
                                                // maybe i'll add ! operator here
};

istream& operator>>(istream& input, EventLocation& el);
ostream& operator<<(ostream& output, EventLocation& el);

//---------------------------------------------------------------------------------- Event -------------------------------------------------------------------------------------------------
class Event {
    const char* eventName = nullptr;
    string type = "";
    char date[11] = ""; // dd/mm/yyyy   
    char startingHour[6] = ""; // 21:30
    int duration = 0;
    static int eventsNo;

public:
    // Other methods

    // Ctors
    Event();
    Event(const char* _eventName, const string _type, const char* _date, const char* _startingHour);
    Event(const char* _eventName, const string _type, const char* _date, const char* _startingHour, int duration);
    

    // Setters
    void setDate(const char* _date);
    void setDuration(int _time);
    void setStartingHour(const char* _staritingHour);

    // Getters
    const char* getEventName();
    const string getType();
    char* getDate();
    char* getStartingHour();
    int getDuration();
    static int getEventsNo();
    // Dtor and C.ctor
    ~Event();
    Event(Event& e);

    // Overloaded operators
    Event& operator=(const Event& e);
    Event operator+(int value);
    friend istream& operator>>(istream& input, Event& e); 
    char& operator[](int index);

};
ostream& operator<<(ostream& output, Event& e);
istream& operator>>(istream& input, Event& e);

enum TicketType {
    NORMAL, VIP
};
//---------------------------------------------------------------------------------- Tickets -------------------------------------------------------------------------------------------------
class Tickets {
protected:
    char id[10] = ""; 
    int maxTickets = 0;
    float price = 0.0;
    static int ticketsSold; 
    bool SoldOut = false;

public:
    // Other methods
    bool isSoldOut(int _maxTickets, int _soldTickets);//???????????

    // Ctors
    Tickets();
    Tickets(const char* _id, float _price);

    // Settrs 
    void setId(const char* _id);
    void setPrice(float _price);
    void setMaxTickets(EventLocation el);
    void setSoldOut(bool _SolsOut);

    // Getters
    char* getId();
    const int getMaxTickets();
    static int getTicketsSold();
    bool getSoldOut();

    // Overloaded operators
    Tickets& operator=(const Tickets& t);
    friend istream& operator>>(istream& input, Tickets& t);
    bool operator!();
    
};

ostream& operator<<(ostream& output, Tickets& t);
istream& operator>>(istream& input, Tickets& t);

//---------------------------------------------------------------------------------- Vip Tickets -------------------------------------------------------------------------------------------------
class VipTickets : public Tickets {
    char VipId[4] = "";
    static int VipTicketsSold;
public:
    VipTickets();
    VipTickets(const char* VipId);    

    void setVipId(const char* _vipId);

    static int getVipTicketsSold();
    char* getVipId();
};

static int getVipTicketsSold();
ostream& operator<<(ostream& output, VipTickets& vt);