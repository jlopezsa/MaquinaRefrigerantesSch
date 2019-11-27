#include "TecladoPc.h"
#include "InterfaceIn.cpp"

int TecladoPc::getInput()
{
	//cout << "FLAG TEST: into getInput" << endl;
	do
	{
		try
		{
			cin >> userInputString;
			if (userInputString == "1")
				optionUser = 1;
			else if (userInputString == "2")
				optionUser = 2;
			else if (userInputString == "3")
				optionUser = 3;
			else if (userInputString == "4")
				optionUser = 4;
			else if (userInputString == "5")
				optionUser = 5;
			else if (userInputString == "6")
				optionUser = 6;
			else if (userInputString == "7")
				optionUser = 7;
			else if (userInputString == "8")
				optionUser = 8;
			else if (userInputString == "9")
				optionUser = 9;
			else if (userInputString == "10")
				optionUser = 10;
			else
				optionUser = 99;
			//
			if (optionUser < 0 || optionUser > 10)
				throw 1;
		}
		catch (int i)
		{
			cout << "Erro, opção inválida" << endl;
		}
		catch (...)
		{
			cout << "Opção imprevista." << endl;
		}
	} while (optionUser < 0 && optionUser > 8);

	return optionUser;
};

int TecladoPc::getInputOperator()
{

	do
	{
		try
		{
			cin >> optionOperator;
			if (optionOperator < 0 || optionOperator > 5)
				throw 1;
		}
		catch (int i)
		{
			cout << "Erro, opção inválida" << endl;
		}
		catch (...)
		{
			cout << "Opção imprevista." << endl;
		}
	} while (optionOperator < 0 && optionOperator > 5);

	return optionOperator;
};

//
//
// Codigo referencia: "Convertir de cadena a número"
//https://poesiabinaria.net/2017/01/operaciones-basicas-cadenas-c-capitalizacion-conversiones-recorte-recorrido-mas/
int TecladoPc::getOperatorPassword()
{
	//cout << "FLAG TEST: into getOperatorPassword" << endl;

	cin >> operatorPasswordString;

	try
	{
		// STOI funcionam para compiladores que soportam C++11 o maiores
		operatorPassword = std::stoi(operatorPasswordString);
		return operatorPassword;
	}
	catch (std::logic_error e)
	{
		std::cout << "\t\tERRO -> Password deve conter  somente numeros." << std::endl;
		return 0;
	}
	//cin >> operatorPassword;
};