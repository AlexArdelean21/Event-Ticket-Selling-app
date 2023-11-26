
#include <iostream>
#include <string>
#include "Classes.h"
#include <cstring>

using namespace std;

int main() {

    //EventLocation location1; 
    //cin >> location1;   // erroare dupa ce introduc numarul de randuri
    //cout << location1;

    //EventLocation location2("Conference Hall", 100, 10); 
    //cout << location2;
    //int x = (int)location2;
    //cout << x;
    //
    //// Display location details using overloaded operator<<
    //cout <<endl << "Location 1:" << location1 << endl;
    //cout <<endl << "Location 2:" << location2 << endl;

    //// Modify and display details of location1
    //location1.setMaxSeats(50);
    //location1.setRows(5);
    //cout <<endl << "Modified Location 1:" << location1 << endl;

    //// Demonstrate copy constructor and copy assignment operator
    //EventLocation location3 = location2;
    //EventLocation location4;
    //location4 = location1;          

    //cout <<endl << "Copied Location 2 to Location 3:" << location3 << endl;
    //cout <<endl << "Copied Location 1 to Location 4:" << location4 << endl;

    //// Demonstrate the increment operators
    //EventLocation location5 = location2++;
    //EventLocation location6 = ++location1;

    //cout << endl << "Postfix Increment Location 2:" << location5 << endl;
    //cout << "Prefix Increment Location 1:" << location6 << endl;


    //--------------------------------------------------------------------------------------------
    // This works but also prints : on the first row, (idk why)
    //Event event2("Birthday Party", "Celebration", "12/01/2023", "18:00"); // Parameterized constructor
    //Event event3("Conference", "Business", "05/15/2023", "09:30", 180); // Parameterized constructor with duration
    //cout << event3[2];

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

    //Tickets t1("123456789", "Normal", 300, NORMAL);

    //cout << endl << t1.getSoldOut();
    //cout << endl << !t1.getSoldOut();

    //Tickets t2("456", "Vip", 300,VIP);
    //Tickets t3("789", "Vip", 300, VIP); 
   
    //Tickets t;
    //cin >> t;
    //// Print some information about the tickets
    //cout << "The category of t1 is " << t1.getCategory() << endl;
    //cout << "The id of t2 is " << t2.getId() << endl;
    //cout << "The max tickets for t3 is " << t3.getMaxTickets() << endl;

    //// Check if some tickets are Vip
    //cout << endl << "Is t1 Vip? " << t1.isVip(t1.getCategory()) << endl;
    //cout << "Is t2 Vip? " << t2.isVip(t2.getCategory()) << endl;

    //// Get the number of tickets sold for each category
    //cout << endl << "The number of Normal tickets sold is " << t1.getTicketsSold()[0] << endl;
    //cout << "The number of Vip tickets sold is " << t2.getTicketsSold()[1] << endl;

    //// Display event details using overloaded operator<<
    //cout << t1 << endl;   

    //cout << endl << endl;
    //return 0;
}