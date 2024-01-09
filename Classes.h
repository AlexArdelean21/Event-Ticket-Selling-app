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

