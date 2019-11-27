#ifndef TECLADOPC
#define TECLADOPC

#include <iostream>
#include <string>
using namespace std;

#include "InterfaceIn.h"

class TecladoPc : public InterfaceIn
{
	string userInputString;
	string operatorPasswordString;
	int optionUser;
	int optionOperator;
	int operatorPassword; // deve ser definida como private...
public:
	int getInput(); // override. testando isso para criar punteiro de função virtual
	int getOperatorPassword();
	int getInputOperator();
};

#endif // TECLADOPC