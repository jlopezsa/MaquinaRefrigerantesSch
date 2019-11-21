#ifndef TECLADO
#define TECLADO

#include "InterfaceIn.h"

class TecladoPc : public InterfaceIn {
		
	public:
		int getInput(); 					// override. testando isso para criar punteiro de função virtual
		int getOperatorPassword();
		int getInputOperator();
};

#endif		// TECLADO