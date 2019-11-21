#ifndef TELAATLYS
#define TELAATLYS

#include "InterfaceOut.h"

class TelaAtlys : public InterfaceOut {
		
	public:
		TelaAtlys();
		~TelaAtlys();
		void impMensa(string);
		void menu();
		void setOutput(int);
		void resetOutput();
};

#endif		// TELAATLYS