#ifndef INTERFACEIN
#define INTERFACEIN

// Clase-base

class InterfaceIn{
		
	public:
		virtual ~InterfaceIn();
		virtual int getInput() { cout << "asdsadsad";};// = 0;
		virtual int getOperatorPassword() { };// = 0;
		virtual int getInputOperator() { };// = 0;
};

#endif		// INTERFACEIN