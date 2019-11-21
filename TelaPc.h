#ifndef TELAPC
#define TELAPC

#include "InterfaceOut.h"

class TelaPc : public InterfaceOut {
	public:
		TelaPc();
		~TelaPc();
		void impMensa(string);
		void menu();
		void setOutput(int);
		void resetOutput();
};

#endif		// TECLADO