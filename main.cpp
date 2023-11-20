
#include <iostream>
#include <string>
#include "Classes.h"
#include <cstring>

using namespace std;

int main() {

    cout << endl << endl;

    Tickets t1("123456789012345", "Normal", 300, NORMAL);
    Tickets t2("456", "Vip", 300,VIP);
    Tickets t3("789", "Vip", 300, VIP); 

    // Print some information about the tickets
    cout << "The category of t1 is " << t1.getCategory() << endl;
    cout << "The id of t2 is " << t2.getId() << endl;
    cout << "The max tickets for t3 is " << t3.getMaxTickets() << endl;

    // Check if some tickets are Vip
    cout << endl << "Is t1 Vip? " << t1.isVip(t1.getCategory()) << endl;
    cout << "Is t2 Vip? " << t2.isVip(t2.getCategory()) << endl;

    // Get the number of tickets sold for each category
    cout << endl << "The number of Normal tickets sold is " << t1.getTicketsSold()[0] << endl;
    cout << "The number of Vip tickets sold is " << t2.getTicketsSold()[1] << endl;

    // Display event details using overloaded operator<<
    cout << t1;   //does nothing

    //--------------------------------------------------------------------------------------------
    // WORKS IF I COMMENT THE DTOR  
    //Event event2("Birthday Party", "Celebration", "12/01/2023", "18:00"); // Parameterized constructor
    //Event event3("Conference", "Business", "05/15/2023", "09:30", 180); // Parameterized constructor with duration

    //// Display event details using overloaded operator<<
    //cout << endl << "Event 2:" << event2 << endl;
    //cout << endl << "Event 3:" << event3 << endl;

    //// Modify and display details of event2
    //event2.setDuration(120);
    //event2.setStartingHour("19:30");
    //cout << endl << "Modified Event 2:" << event2 << endl;

    //// Demonstrate copy constructor
    //Event event4 = event3;
    //cout << endl << "Copied Event 3 to Event 4:" << event4 << endl;  
    
    //--------------------------------------------------------------------------------------------

    //EventLocation location1; // Default constructor
    //EventLocation location2("Conference Hall", 100, 10); // Parameterized constructor

    //// Display location details using overloaded operator<<
    //cout << "Location 1:" << location1 << endl;
    //cout << "Location 2:" << location2 << endl;

    //// Modify and display details of location1
    //location1.setMaxSeats(50);
    //location1.setRows(5);
    //cout << "Modified Location 1:" << location1 << endl;

    //// Demonstrate copy constructor and copy assignment operator
    //EventLocation location3 = location2; // Copy constructor
    //EventLocation location4;
    //location4 = location1; // Copy assignment operator

    //cout << "Copied Location 2 to Location 3:" << location3 << endl;
    //cout << "Copied Location 1 to Location 4:" << location4 << endl;

    //// Demonstrate the increment operators
    //EventLocation location5 = location2++; // Postfix increment
    //EventLocation location6 = ++location1; // Prefix increment

    //cout << "Postfix Increment Location 2:" << location5 << endl;
    //cout << "Prefix Increment Location 1:" << location6 << endl;

    cout << endl << endl;
    return 0;

}