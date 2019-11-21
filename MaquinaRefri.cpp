#include <iostream>
#include <stdio.h>
#include <time.h>
#include <typeinfo>
using namespace std;

#include "MaquinaRefri.h"
#include "TelaPc.cpp"
#include "TelaAtlys.cpp"
#include "TecladoPc.cpp"
#include "TecladoAtlys.cpp"
#include "CadastroVenda.cpp"

#include "Escalonador.cpp"

MaquinaRefri::MaquinaRefri()
{
	passwordOperator = 33;

#if INTERFACE == 1 // Using PC (diretivas de compilação para processdor)
	time(&timer);
#else // Using Atlys
	inicio = clock();
#endif
};


void MaquinaRefri::inicia()
{

	//struct tm *timeinfo; // timeinfo é o ponteiro

	// padrão para configurar hora (year, month, day, hora, min, sec, true is Pm)
	cadVenda.setDataHora(2019, 12, 31, 11, 59, 40, true); // Configuração inicial da DataHora

	std::cout << "************************************************************" << std::endl;
	std::cout << "*           Maquina de venda de refrigerantes              *" << std::endl;
	std::cout << "* Data/hora inicial: ";
	cadVenda.visualizaDataHora();
	std::cout << " 		   *" << endl;
	std::cout << "*                                                          *" << std::endl;
	std::cout << "************************************************************" << std::endl;

	/*
	TecladoPc *pT;
	TecladoPc objTecladoPc;
	//
	int (InterfaceIn::*pGetInput)() = &InterfaceIn::getInput; // Deitel pg 972
	int (InterfaceIn::*pGetPassword)() = &InterfaceIn::getOperatorPassword;
	pT = &objTecladoPc;
	//(pT->*pGetInput)(); // forma de accessar à funçao atraves de ponteiro
	projectEsc.init_Task_Timers();
	//
	projectEsc.addTask(pGetInput, pT, 10, 0); // (ponteiro, time (delay), prioeity)
	projectEsc.addTask(pGetPassword, pT, 20, 1);
	//
	projectEsc.Run_RTC_Scheduler(); // Executa a tarefa
	*/
	
	Escalonador<void,MaquinaRefri,MaquinaRefri> projectEscVoid;
	MaquinaRefri objMaquina;
	MaquinaRefri *ptrMaquina;
	ptrMaquina = &objMaquina;
	void (MaquinaRefri::*pShowMenu)() = &MaquinaRefri::showMenu; // Deitel pg 972
	void (MaquinaRefri::*pLogicaEstados)() = &MaquinaRefri::logicaEstados; // Deitel pg 972
	void (MaquinaRefri::*pInputOption)() = &MaquinaRefri::inputOption; // Deitel pg 972
	projectEscVoid.init_Task_Timers();
	projectEscVoid.addTask(pShowMenu,ptrMaquina,10,0);
	projectEscVoid.addTask(pLogicaEstados,ptrMaquina,20,1);
	projectEscVoid.addTask(pInputOption,ptrMaquina,30,2);
	projectEscVoid.Run_RTC_Scheduler(); // Executa a tarefa
	
	setEstAtual(0); // Configura estado inicial da Maquina de Estados
	do
	{
		showMenu();
		logicaEstados();
	} while (1);
}

void MaquinaRefri::inputOption()
{
#if INTERFACE == 1 || INTERFACE == 3 // Using PC (diretivas de compilação para processdor)
	pEntrada = new TecladoPc();
#else // Using Atlys
	pEntrada = new TecladoAtlys();
#endif
	//
	option = pEntrada->getInput();
}
//
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//
void MaquinaRefri::logicaEstados()
{
	//---- Variaveis
	bool saida = false;
	int segundos = 0; // usado para contar os segundos transcurridos
#if INTERFACE == 1 || INTERFACE == 3 // Using PC (diretivas de compilação para processdor)
	pSaida = new TelaPc();
#else // Using Atlys
	pSaida = new TelaAtlys();
#endif
	pSaida->resetOutput();
	switch (estAtual)
	{
	case 0: // ------------------------------------------ Estado S000
		pSaida->impMensa("\tSaldo 0");
		inputOption();
		if (option == 1)
			setEstAtual(1);
		else if (option == 2)
			setEstAtual(2);
		else if (option == 3)
			setEstAtual(4);
		else if (6 < option && option < 11) // else if (pEntrada->getInputOperator() == 7,8,9,10)
		{									// Operator Mode
			cout << option;
			modoOperador(option);
		}
		else
			setEstAtual(0);
		break;
	case 1: // ------------------------------------------ Estado S025
		pSaida->impMensa("\tSaldo 25");
		inputOption();
		if (option == 1)
			setEstAtual(2);
		else if (option == 2)
			setEstAtual(3);
		else if (option == 3)
			setEstAtual(5);
		else if (option == 4)
		{
			setEstAtual(0);
			pSaida->setOutput(25); // D025
		}
		else if (6 < option && option < 11)
		{ // Operator Mode
			modoOperador(option);
			saida = false;
		}
		else
			setEstAtual(1);

		break;
	case 2: // ------------------------------------------ Estado S050
		pSaida->impMensa("\tSaldo 50");
		inputOption();
		if (option == 1)
			setEstAtual(3);
		else if (option == 2)
			setEstAtual(4);
		else if (option == 3)
			setEstAtual(6);
		else if (option == 4)
		{
			setEstAtual(0);
			pSaida->setOutput(50); // D050
		}
		else if (6 < option && option < 11)
		{ // Operator Mode
			modoOperador(option);
			saida = false;
		}
		else
			setEstAtual(2);
		break;
	case 3: // ------------------------------------------ Estado S075
		pSaida->impMensa("\tSaldo 75");
		inputOption();
		if (option == 1)
			setEstAtual(4);
		else if (option == 2)
			setEstAtual(5);
		else if (option == 3)
		{
			setEstAtual(6);
			pSaida->setOutput(25); // D025
		}
		else if (option == 4)
		{
			setEstAtual(0);
			pSaida->setOutput(75); // D075
		}
		else if (6 < option && option < 11)
		{ // Operator Mode
			modoOperador(option);
			saida = false;
		}
		else
			setEstAtual(3);
		break;
	case 4: // ------------------------------------------ Estado S100
		pSaida->impMensa("\tSaldo 100");
		inputOption();
		if (option == 1)
			setEstAtual(5);
		else if (option == 2)
			setEstAtual(6);
		else if (option == 3)
		{
			setEstAtual(6);
			pSaida->setOutput(50); // D050
		}
		else if (option == 4)
		{
			setEstAtual(0);
			pSaida->setOutput(100); // D100
		}
		else if (6 < option && option < 11)
		{ // Operator Mode
			modoOperador(option);
			saida = false;
		}
		else
			setEstAtual(4);
		break;
	case 5: // ------------------------------------------ Estado S125
		pSaida->impMensa("\tSaldo 125");
		inputOption();
		if (option == 1)
			setEstAtual(6);
		else if (option == 2)
		{
			setEstAtual(6);
			pSaida->setOutput(25); // D025
		}
		else if (option == 3)
		{
			setEstAtual(6);
			pSaida->setOutput(75); // D075
		}
		else if (option == 4)
		{
			setEstAtual(0);
			pSaida->setOutput(125); // D125
		}
		else if (6 < option && option < 11)
		{ // Operator Mode
			modoOperador(option);
			saida = false;
		}
		else
			setEstAtual(5);
		break;
	case 6: // ------------------------------------------ Estado S150
		pSaida->impMensa("\tSaldo 150");
		inputOption();
		if (option == 1)
		{
			setEstAtual(6);
			pSaida->setOutput(25); // D025
		}
		else if (option == 2)
		{
			setEstAtual(6);
			pSaida->setOutput(50); // D050
		}
		else if (option == 3)
		{
			setEstAtual(6);
			pSaida->setOutput(100); // D100
		}
		else if (option == 4)
		{
			setEstAtual(0);
			pSaida->setOutput(150); // D150
		}
		else if (option == 5)
		{ // -------------------------------------------------------------------- Venda do MEET
			setEstAtual(0);
			pSaida->setOutput(1);	// Entrega refri MEET
#if INTERFACE == 1 || INTERFACE == 3 // PC
			time(&timerFim);
			segundos = (timerFim - timer);
			time(&timer);
#else
			fim = clock();
			segundos = (fim - inicio) / CLOCKS_PER_SEC;
			inicio = clock();
#endif
			cadVenda.cadastraNovaVenda(option, segundos);
			std::cout << endl
					  << endl;
		}
		else if (option == 6)
		{ // ------------------------------------------------------------------ Venda do ETIRPS
			setEstAtual(0);
			pSaida->setOutput(2); // Entrega refri ETIRPS
#if INTERFACE == 1 || INTERFACE == 3
			time(&timerFim);
			segundos = (timerFim - timer);
			time(&timer);
#else
			fim = clock();
			segundos = (fim - inicio) / CLOCKS_PER_SEC;
			inicio = clock();
#endif
			cadVenda.cadastraNovaVenda(option, segundos);
			std::cout << endl
					  << endl;
		}
		else if (6 < option && option < 11)
		{ // Operator Mode
			modoOperador(option);
			saida = false;
		}
		else
			setEstAtual(6);
		break;
	default:
		break;
	};
	std::cout << "------------------------------------------------------------" << std::endl;

	//delete pSaida;
	//delete pEntrada;
}

void MaquinaRefri::setEstAtual(int estado)
{
	estAtual = estado;
};

void MaquinaRefri::modoOperador(int newOption)
{
	int login, password, optionLog;
	bool saidaOperador = false;
	bool logSolicitado = false;
	bool validez;

	// Verifica password do Operador. Si válido o requisitado é apresentado.
	pSaida->impMensa("\t\tIngresse password para consultar: ");
	password = pEntrada->getOperatorPassword(); // iserir password
	validez = verificaPassword(password);		// true: valido, false: invalido

	if (validez)
	{
		pSaida->impMensa("\tOperador de Log valido");

		optionLog = newOption; // pEntrada->getInputOperator();

		cadVenda.fifoToList();

		switch (optionLog)
		{
		case 7: // Listar total valor de vendas
			cout << "Total vendas: " << cadVenda.getNumeroVendas() << endl;
			break;
		case 8: // Listar quantidade vendida de cada refrigerante
			cout << "Total de MEET:   " << cadVenda.getNumeroMEET() << endl;
			cout << "Total de ETIRPS: " << cadVenda.getNumeroETIRPS() << endl;
			break;
		case 9: // Listar periodo de dia com mais vendas
			cout << "Nao implementado." << endl;
			break;
		case 10: // Listar historico de vendas
			cout << "Nao implementado." << endl;
			break;
		case 5: // saida modo operador
			saidaOperador = true;
			break;
		default:
			break;
		}
	}
	else
	{
		pSaida->impMensa("\tOperador nao valido");
	}
}

// Verifica se o password usado pelo Operador corresponde com o cadastrado
bool MaquinaRefri::verificaPassword(int newPassword)
{
	if (newPassword == passwordOperator)
		return true;
	else
		return false;
};

void MaquinaRefri::showMenu()
{
#if INTERFACE == 1 || INTERFACE == 3 // Using PC (diretivas de compilação para processdor)
	pSaida = new TelaPc();
#else // Using Atlys
	pSaida = new TelaAtlys();
#endif
	pSaida->menu();
}