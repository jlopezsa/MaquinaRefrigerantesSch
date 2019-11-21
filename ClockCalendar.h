#ifndef CLOCKCALENDAR
#define CLOCKCALENDAR

#include <iostream>
#include "Clock.h"
#include "Calendar.h"

using namespace std;

class ClockCalendar : public Clock, public Calendar {
	public:
		ClockCalendar(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int min, unsigned int sec, bool isPM);
		~ClockCalendar();
		void advance();
};

#endif		// CLOCKCALENDAR