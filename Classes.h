#pragma once
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class Util {
public:
    static char* copyArray(const char* source);
};

class EventLocation {

    const char* locationName = nullptr;
    int maxSeats = 0;
    int rows = 0;
    static int locationsNo;

public:
    EventLocation();  // Ctors
    EventLocation(const char* _locationName, int _maxSeats, int _rows);

    // Setters
    void setMaxSeats(int _maxSeats);
    void setRows(int _rows);

    // Gettrs
    const char* getLocationName() const;
    int getMaxSeats();
    int getRows();
    static int getLocationsNo();

    // D.ctor and C.ctor
    ~EventLocation(); 
    EventLocation(const EventLocation& e);

    // Overloaded operators
    EventLocation& operator=(const EventLocation& el);

    EventLocation operator++(int);

    EventLocation operator++();
};
// Will this work for all the classes?
void operator<<(ostream& output, EventLocation& el);

class Event {
    const char* eventName = nullptr;
    const string type = "";
    char date[11] = ""; // dd/mm/yyyy   // sa pun si aici const?
    char startingHour[6] = "";
    int duration = 0;
    static int eventsNo;

public:

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
    Event operator++(int);
    Event operator++();
};
void operator<<(ostream& output, Event& e);


class Tickets {
    char id[16] = "";
    char vipId[4] = "";  //idk if i should implement this
    const char* category = nullptr;
    const int maxTickets;
    static int ticketsSold[2]; // 0 => normal tickets sold, 1 => vip tickets sold

public:
    // Ctors
    Tickets();
    Tickets(const char* _id, const char* _category, const int _maxTickets);
    Tickets(const char* _vipId, const char* _category, const int _maxTickets);

    // Settrs
    void setId(const char* _id);
    void setVipId(const char* _vipId);

    // Getters
    char* getId();
    char* getVipId();
    const char* getCategory();
    const int getMaxTickets();

    // C.ctor and dtor
    ~Tickets();
    Tickets(Tickets& t);

    // Overloaded operators
    Tickets& operator=(const Tickets& t);
    
};

void operator<<(ostream& output, Tickets& t);