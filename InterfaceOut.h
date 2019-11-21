#ifndef INTERFACEOUT
#define INTERFACEOUT

#include <string>
using namespace std;

// Clase-base

class InterfaceOut{
	public:
		virtual ~InterfaceOut();
		virtual void menu() = 0;
		virtual void setOutput(int) = 0;
		virtual void impMensa(string) = 0; // verificar se 'e= 0?
		virtual void resetOutput() = 0;
};

#endif		// INTERFACEIN