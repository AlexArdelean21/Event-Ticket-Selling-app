#include <iostream>
#include <string>
#include <cstring>
#include "Classes.h"

using namespace std;


// UTIL CLASS
char* Util::copyArray(const char* source) {
	char* copy = new char[strlen(source) + 1];
	strcpy_s(copy, strlen(source) + 1, source);
	return copy;
}

// EVENTLOCATION CLASS
int EventLocation::locationsNo = 0;

// Ctors
EventLocation::EventLocation() : maxSeats(0), rows(0) {
    this->locationName = "No name";
    EventLocation::locationsNo++;
}

EventLocation::EventLocation(const char* _name, int _maxSeats, int _rows) : maxSeats(_maxSeats), rows(_rows){
    this->locationName = _name;
    EventLocation::locationsNo++;
}

// Setters
void EventLocation::setMaxSeats(int _maxSeats) {
    this->maxSeats = _maxSeats;
}

void EventLocation::setRows(int _rows) {
    this->rows = _rows;
}

// Getters
const char* EventLocation::getLocationName() const { return this->locationName; }

int EventLocation::getMaxSeats() { return this->maxSeats; }

int EventLocation::getRows() { return this->rows; }

int EventLocation::getLocationsNo() { return locationsNo; }

// destructor
EventLocation::~EventLocation() {
    delete[] this->locationName;
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
    if (this == &el) {
        return *this;
    }

    this->setMaxSeats(el.maxSeats);
    this->setRows(el.rows);
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

void operator<<(ostream& output, EventLocation& el) {
    cout << endl << "The event will take place at " << el.getLocationName() << ".";
    cout << endl << "The revenu will provide " << el.getMaxSeats() << " seats, spread across " << el.getRows() << " rows.";
}

// EVENT CLASS
int Event::eventsNo = 0;

// Ctors
Event::Event() : eventName("No name"), type("None"), duration(0) {
    this->setDate("00/00/0000");
    this->setStartingHour("00:00");
    Event::eventsNo++;
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
const char* Event::getEventName() { return this->eventName; }
string Event::getType() { return this->type; }
char* Event::getDate() { return this->date; }
char* Event::getStartingHour() { return this->startingHour; }
int Event::getDuration() { return this->duration; }
int Event::getEventsNo() { return eventsNo; } // is this ok?

// D.ctor and C.ctor
// Do i need a D.ctor

Event::~Event() {
    delete[] this->eventName;
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
    if (this == &e)
        return *this;

    this->setDate(e.date);
    this->setDuration(e.duration);
    this->setStartingHour(e.startingHour); // fara variabilele constante

    return *this;
}

Event Event::operator++(int) {
    Event copy = *this;
    this->duration += 1;
    return copy;
}

Event Event::operator++() {
    this->duration += 1;
    return *this;
}

void operator<<(ostream& output, Event& e) {
    cout << endl << e.getEventName() << " is a " << e.getType();
    cout << endl << "It will start at " << e.getStartingHour() << " on ";
    cout << endl << e.getEventName() << " is " << e.getDuration() << " long.";
}