#ifndef TECLADOATLYS
#define TECLADOATLYS

#include "InterfaceIn.h"

class TecladoAtlys : public InterfaceIn {

	public:
		int getInput();
		int getOperatorPassword();
		int getInputOperator();
};

#endif		// TECLADOATLYS