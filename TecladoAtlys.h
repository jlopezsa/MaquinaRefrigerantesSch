#ifndef TECLADOATLYS
#define TECLADOATLYS

#include "InterfaceIn.h"

class TecladoAtlys : public InterfaceIn
{
	int optionUser;
	int optionOperator;
	int operatorPassword; // deve ser definida como private...
public:
	int getInput();
	int getOperatorPassword();
	int getInputOperator();
};

#endif // TECLADOATLYS