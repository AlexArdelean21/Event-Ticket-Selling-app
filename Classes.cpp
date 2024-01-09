#include <iostream>
#include <string>
#include <cstring>
#include "Classes.h"

using namespace std;


//------------------------------------------------------------------- UTIL CLASS -------------------------------------------------------------------
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
    this->locationName =  Util::copyArray(" ");
}

EventLocation::EventLocation(const char* _name, int _maxSeats, int _rows) : maxSeats(_maxSeats), rows(_rows){
    this->locationName = Util::copyArray(_name);
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

//---------------------------------------------------------------------- EVENT CLASS ---------------------------------------------------------------------------
int Event::eventsNo = 0;

// Ctors
Event::Event() : type("None"), duration(0) {
    this->setDate("00/00/0000");
    this->eventName = Util::copyArray("");
    this->setStartingHour("00:00");
}

Event::Event(const char* _eventName, const string _type, const char* _date, const char* _startingHour) : type(_type) {
    this->eventName = Util::copyArray(_eventName);
    this->setDate(_date);
    this->setStartingHour(_startingHour);
    this->duration = 120;
    Event::eventsNo++;
}

Event::Event(const char* _eventName, string _type, const char* _date, const char* _startingHour, int _duration) :
     type(_type), duration(_duration) {
    this->eventName = Util::copyArray(_eventName);
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
    char* copy = Util::copyArray(eventName);  //mai era nevoie de copy? sau face functia din util o copie
    return copy; }
const string Event::getType() { return this->type; }
char* Event::getDate() { return Util::copyArray(this->date); }
char* Event::getStartingHour() { return Util::copyArray(this->startingHour); }
int Event::getDuration() { return this->duration; } 
int Event::getEventsNo() { return Event::eventsNo; }

// D.ctor and C.ctor
// Do i need a D.ctor

Event::~Event() {
    if (this->eventName != nullptr) {
        delete[] this->eventName;
    }
        
}
           // should i add const here?
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
    if (eventName != nullptr) { delete[] eventName; }

    if (this == &e){ return *this; }

    this->eventName = Util::copyArray(e.eventName);
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

