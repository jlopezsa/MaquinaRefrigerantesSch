#ifndef CLOCK
#define CLOCK

class Clock {
	protected:
		unsigned int hour, min, sec;
		bool isPM;
	public:
		Clock (unsigned int hour, unsigned int min, unsigned int sec, bool isPM);
		~Clock();
		void setClock (unsigned int hour, unsigned int min, unsigned int sec, bool isPM);
		void readClock (unsigned int& hour, unsigned int& min, unsigned int& sec, bool& isPM);
		void advance ();
};

#endif		// CLOCK