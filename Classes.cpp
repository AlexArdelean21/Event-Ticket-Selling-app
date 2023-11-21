#include <iostream>
#include <string>
#include <cstring>
#include "Classes.h"

using namespace std;


// UTIL CLASS
char* Util::copyArray(const char* source) {
    if (source == nullptr) {
        return nullptr;
    }
	char* copy = new char[strlen(source) + 1];
	strcpy_s(copy, strlen(source) + 1, source);
	return copy;
}

// EVENTLOCATION CLASS
// Ctors
EventLocation::EventLocation() : maxSeats(0), rows(0) {
    this->locationName = "No name";
}

EventLocation::EventLocation(const char* _name, int _maxSeats, int _rows) : maxSeats(_maxSeats), rows(_rows){
    this->locationName = _name;
}

// Setters
void EventLocation::setMaxSeats(int _maxSeats) {
    this->maxSeats = _maxSeats;
}

void EventLocation::setRows(int _rows) {
    this->rows = _rows;
}

// Getters
const char* EventLocation::getLocationName() {
    char* copy = Util::copyArray(this->locationName);
    return copy;
}
int EventLocation::getMaxSeats() { return this->maxSeats; }
int EventLocation::getRows() { return this->rows; }

// destructor
EventLocation::~EventLocation() {
    if (this->locationName != nullptr) {
        delete[] this->locationName;
    }
    
}

// cpy ctor
EventLocation::EventLocation(const EventLocation& e) {
    if (e.locationName) {
        this->locationName = Util::copyArray(e.locationName);
    }
    else {
        this->locationName = nullptr;
    }
    maxSeats = e.maxSeats;
    rows = e.rows;
}

// Overloaded operators
EventLocation& EventLocation::operator=(const EventLocation& el) {
    if (locationName != nullptr) {
        delete[] locationName;
    }
    
    if (this == &el) {
        return *this;
    }

    this->setMaxSeats(el.maxSeats);
    this->setRows(el.rows);
    return *this;
}

EventLocation EventLocation::operator++(int) {// Postfix
    EventLocation copy = *this;
    this->maxSeats += 1;
    return copy;
}

EventLocation EventLocation::operator++() {// Prefix
    this->maxSeats += 1;
    return *this;
}

EventLocation::operator int() {
    return EventLocation::getMaxSeats();  
}

// sa modific din void in class 
ostream& operator<<(ostream& output, EventLocation& el) {
    output << endl << "The event will take place at " << el.getLocationName() << ".";
    output << endl << "The revenu will provide " << el.getMaxSeats() << " seats, spread across " << el.getRows() << " rows.";
    return output;
}

istream& operator>>(istream& input, EventLocation& el) {
    string buffer;
    cout << endl << "Set a name for your location: ";
    input >> buffer;
    if (el.locationName != nullptr) {
        delete[] el.locationName;
    }
    el.locationName = Util::copyArray(buffer.c_str());
    
    cout << endl << "The maximum number of seats will be: ";
    input >> el.maxSeats;

    cout << endl << "The number of rows: ";
    input >> el.rows;
    return input;
}

// EVENT CLASS
int Event::eventsNo = 0;

// Ctors
Event::Event() : eventName("No name"), type("None"), duration(0) {
    this->setDate("00/00/0000");
    this->setStartingHour("00:00");
}

Event::Event(const char* _eventName, const string _type, const char* _date, const char* _startingHour) : type(_type) {
    this->eventName = _eventName;
    this->setDate(_date);
    this->setStartingHour(_startingHour);
    this->duration = 120;
    Event::eventsNo++;
}

Event::Event(const char* _eventName, string _type, const char* _date, const char* _startingHour, int _duration) :
     type(_type), duration(_duration) {
    this->eventName = _eventName;
    this->setDate(_date);
    this->setStartingHour(_startingHour);
    Event::eventsNo++;
}

// Setters
void Event::setDate(const char* _date) {
    if (strlen(_date) != 10)
        throw exception("Wrong date");
    if (_date[2] != '/' || _date[5] != '/')
        throw exception("Wrong date format");

    strcpy_s(this->date, _date);
}

void Event::setStartingHour(const char* _startingHour) {
    if (strlen(_startingHour) != 5)
        throw exception("Wrong hour");
    if (_startingHour[2] != ':')
        throw exception("Wrong format");

    strcpy_s(this->startingHour, _startingHour);
}

void Event::setDuration(int _duration) {
    this->duration = _duration;

}

// Getters
const char* Event::getEventName() { 
    char* copy = Util::copyArray(eventName);
    return copy; }
const string Event::getType() { return this->type; }
char* Event::getDate() { return Util::copyArray(this->date); }
char* Event::getStartingHour() { return Util::copyArray(this->startingHour); }
int Event::getDuration() { return this->duration; }

// D.ctor and C.ctor
// Do i need a D.ctor

Event::~Event() {
    if (this->eventName != nullptr) {
        delete[] this->eventName;
    }
        
}

Event::Event(Event& e) : type(e.type) {
    if (e.eventName) {
        this->eventName = Util::copyArray(e.eventName);
    }
   
    else {
        this->eventName = nullptr;
    }

    this->setDate(e.getDate());
    this->setStartingHour(e.getStartingHour());
    this->duration = e.duration;
}

// Overloaded operators
Event& Event::operator=(const Event& e) {
    if (eventName != nullptr) {
        delete[] eventName;
    }

    if (this == &e)
        return *this;

    this->setDate(e.date);
    this->setDuration(e.duration);
    this->setStartingHour(e.startingHour); // fara variabilele constante

    return *this;
}

Event Event::operator+(int value) {
    Event copy = *this;
    copy.duration += value;   // or copy.setDuration(getDuration() + value)
    return copy;
}

char& Event::operator[](int index) {
    if (index >= 0 && index < 6) {
        return getStartingHour()[index];
    }
    throw exception("Invalid index");
}


istream& operator>>(istream& input, Event& e) {
    string buffer;
    cout << endl << "Name your event: ";
    input >> buffer;
    if (e.eventName != nullptr) {
        delete[] e.eventName;
    }
    e.eventName = Util::copyArray(buffer.c_str());

    cout << "What type of event will it be? ";
    input >> e.type;   
    
    cout << "What is the date of the event?";
    input >> e.date;

    cout << "What is the starting hour of the event?";
    input >> e.startingHour;

    cout << "What is the duration, in minutes, of the event?";
    input >> e.duration;

    return input;
}

// sa modific din void in class type
ostream& operator<<(ostream& output, Event& e) {
    output << endl << e.getEventName() << " is a " << e.getType();
    output << endl << "It will start at " << e.getStartingHour() << " on " << e.getDate();
    output << endl << "The " << e.getEventName() << " is " << e.getDuration() << " minutes long.";
    return output;
}

// TICKETS CLASS
int Tickets::ticketsSold[] = {0, 0};

// Other methods
bool Tickets::isVip(const char* _category) {
    if (_category != "Vip" && _category != "Normal") {
        throw exception("Choose between Normal and Vip!");
    }
    if (_category == "Vip") return true;    
    else return false;
}

// Ctors
Tickets::Tickets() : category("No category"), maxTickets(0) {
    this->setId("000000000000000");
}

Tickets::Tickets(const char* _id, const char* _category, const int _maxTickets, int _ticketsSoldIndex) :  category(_category), maxTickets(300){
    if (_ticketsSoldIndex == 0) { this->setId(_id); }
    else if (_ticketsSoldIndex == 1) { this->setVipId(_id); }
    else throw exception("There is no such ticket");
    
    Tickets::ticketsSold[_ticketsSoldIndex]++;
}

// Setters
void Tickets::setId(const char* _id) {
    if (strlen(_id) != 9)
        throw exception("Wrong id");
    strcpy_s(this->id, _id);

}void Tickets::setVipId(const char* _vipId) {
    if (strlen(_vipId) != 3)
        throw exception("Wrong id");
    strcpy_s(this->id, _vipId);
}

// Getters

char* Tickets::getId() { return this->id; }
char* Tickets::getVipId() { return this->vipId; }
const char* Tickets::getCategory() { return this->category; }
const int Tickets::getMaxTickets() { return this->maxTickets; }
int* Tickets::getTicketsSold() { return Tickets::ticketsSold; }

// Dtor and C.ctor
Tickets::~Tickets() {
    if (this->category != nullptr) {
        delete[] this->category;
    }
}

Tickets::Tickets(Tickets& t) : maxTickets(t.maxTickets){

    if (this == &t) return;
    if (t.category) {
        this->category = Util::copyArray(t.category);
    }
    else {
        this->category = nullptr;
    }

    this->setId(t.getId());
    this->setVipId(t.getVipId());
}


// Overloaded operators
Tickets& Tickets::operator=(const Tickets& t) {
    if (category != nullptr) {
        delete[] category;
    }
    if (this == &t) {
        return *this;
    }

    this->setId(t.id);
    this->setVipId(t.vipId);
    return *this;
}

bool Tickets::operator==(Tickets t) {
    if (!strcmp(t.category, "Vip")) {
        if (!strcmp(t.vipId, this->vipId)) { return true; }
        else { return false; }
    }
    else if (!strcmp(t.category, "Normal")) {
        if (!strcmp(t.id, this->id)) { return true; }
        else { return false; }
    }
    else {
        throw exception("Wrong category");
    }
}

istream& operator>>(istream& input, Tickets& t) {
    cout << "What type of ticket would you like?" << endl << "Vip or Normal ?";
    string buffer;
    while (buffer != "Vip" || buffer != "Normal") {
        input >> buffer;
    }

    if (t.category != nullptr) {
        delete[] t.category;
    }
    t.category = Util::copyArray(buffer.c_str());

    if (!strcmp(t.category, "Vip")) {
        cout << "Enter the Vip id, it should loook like this \"###\" :";
        input >> t.vipId;
    }
    else if (!strcmp(t.category, "Normal")) {
        cout << "Enter the Vip id, it should loook like this \"#########\" :";
        input >> t.id;
    }

    cout << "What is the maximum ammount of tickets? ";
    input >> t.maxTickets;
    
    return input;
}


ostream& operator<<(ostream& output, Tickets& t) {
    if (t.isVip(t.getCategory())) {
        output << endl<< "You bought a Vip ticket, this is your ticket's id: " << t.getVipId();
        output << "Thre are a number of " << t.getMaxTickets() << "tickets in total";
        output << "So far " << Tickets::getTicketsSold()[0] + Tickets::getTicketsSold()[1] << " tickets have been sold.";
    }
    else {
        output << endl << "You bought a ticket, this is your ticket's id: " << t.getId();
        output << endl << "Thre are " << t.getMaxTickets() - (Tickets::getTicketsSold()[0] + Tickets::getTicketsSold()[1]);
        output<< " tickets remaining";
   
        
    }
    return output;
}