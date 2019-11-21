#include "Clock.h"

Clock::Clock(unsigned int hour, unsigned int min, unsigned int sec, bool isPM) {
	this->hour = hour;
	this->min = min;
	this->sec = sec;
	this->isPM = isPM;
}

Clock::~Clock() { }

void Clock::setClock (unsigned int hour, unsigned int min, unsigned int sec, bool isPM) {
	this->hour = hour;
	this->min = min;
	this->sec = sec;
	this->isPM = isPM;
}

void Clock::readClock (unsigned int& hour, unsigned int& min, unsigned int& sec, bool& isPM) {
	hour = this->hour;
	min = this->min;
	sec = this->sec;
	isPM = this->isPM;
}

void Clock::advance () {
	sec++;
	if (sec >= 60) {
		sec = 0;
		min++;
		if (min >= 60) {
			min = 0;
			hour++;
			if (hour > 12) 
				hour = 1;
			else
				if (hour == 12 && isPM) {
					hour = 0;
					isPM = !isPM;
				} else {
					if (hour == 12 && !isPM) {
						isPM = !isPM;
					}
				}
		}
	}
}
