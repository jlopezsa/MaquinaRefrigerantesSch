#include "Calendar.h"

Calendar::Calendar (unsigned int year, unsigned int month, unsigned int day) {
	this->year = year;
	this->month = month;
	this->day = day;
}

Calendar::~Calendar() { }

void Calendar::setCalendar (unsigned int year, unsigned int month, unsigned int day) {
	this->year = year;
	this->month = month;
	this->day = day;
}

void Calendar::readCalendar (unsigned int& year, unsigned int& month, unsigned int& day){
	year = this->year;
	month = this->month;
	day = this->day;
}

void Calendar::advance () {
	day++;
	switch (month) {
		case 1: 
		case 3: 
		case 5: 
		case 7:
		case 8: 
		case 10: 
		case 12: if (day > 31) {
                     day = 1;
		             month++;
		         }
                 break;
        case 2:            // Leap Year - To be implemented!!
        case 4: 
        case 6: 
        case 9: 
        case 11: if (day > 30) {
                     day = 1;
		             month++;
                 }
                 break;
    }
    if (month > 12) {
	    month = 1;
	    year++;
	}

}

