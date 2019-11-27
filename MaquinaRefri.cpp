#include <iostream>
#include <stdio.h>
#include <time.h>
#include <typeinfo>
using namespace std;

#include "MaquinaRefri.h"
#include "CadastroVenda.cpp"
#include "EscalonadorEstruct.cpp"
#include "TelaPc.cpp"
#include "TelaAtlys.cpp"

#if INTERFACE == 1  // Using PC (diretivas de compilação para processador)	
#include "TecladoPc.cpp"
#else // Using Atlys
#include "TecladoAtlys.cpp"
#endif

MaquinaRefri::MaquinaRefri()
{
	passwordOperator = 33;
	setEstAtual(0); // Configura estado inicial da Maquina de Estados
#if INTERFACE == 1  // Using PC (diretivas de compilação para processdor)
	time(&timer);
	//pthread_create(&threadExemploThread, NULL, &MaquinaRefri::exemploThread, NULL); // for static method
#else // Using Atlys
	inicio = clock();
#endif
};
//
//
//
EscalonadorEstruct projectEscVoid;
//
//
//
void *MaquinaRefri::exemploThread(void *)
{
	int testeIn;
	cout << "====== Testeando funcao com ponteiro ======" << endl;
	while (1)
	{
		cin >> testeIn;
		if (testeIn == 0)
		{
			cout << "....... THREAD executando: Insere 0................" << endl;
			//break;
		}
		else
		{
			cout << "....... THREAD executando: Outra coisa ................" << endl;
		}
	}
}
//
//
//
void MaquinaRefri::inicia()
{
	// padrão para configurar hora (year, month, day, hora, min, sec, true is Pm)
	cadVenda.setDataHora(2019, 11, 25, 11, 59, 40, true); // Configuração inicial da DataHora

	std::cout << "************************************************************" << std::endl;
	std::cout << "*           Maquina de venda de refrigerantes               " << std::endl;
	std::cout << "* Data/hora inicial: ";
	cadVenda.visualizaDataHora();
	std::cout << " 		    " << endl;
	std::cout << "*                                                           " << std::endl;
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

	MaquinaRefri *ptrMaquina;

	void (MaquinaRefri::*pShowMenu)() = &MaquinaRefri::showMenu;		   // Deitel pg 972
	void (MaquinaRefri::*pLogicaEstados)() = &MaquinaRefri::logicaEstados; // Deitel pg 972

	//projectEscVoid.addTaskReadyEstruct(pShowMenu, ptrMaquina, 5, 0);

	projectEscVoid.init_Task_TimersStruct();
	

	//(this->exemploThread);

	while (1)
	{
		//projectEscVoid.addTaskReadyEstruct(pLogicaEstados, ptrMaquina, 5, 0);
		//projectEscVoid.schedulerStatesLogic();
		showMenu();
		logicaEstados();
	}
}
//
//
//
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
//
//
void MaquinaRefri::logicaEstados()
{

	//MaquinaRefri *ptrMaquina;
	//void (MaquinaRefri::*pShowMenu)() = &MaquinaRefri::showMenu;
	//projectEscVoid.addTaskReadyEstruct(pShowMenu, ptrMaquina, 5, 0);

	//---- Variaveis
	bool saida = false;
	int segundos = 0;				 // usado para contar os segundos transcurridos
#if INTERFACE == 1 || INTERFACE == 3 // Using PC (diretivas de compilação para processdor)
	pSaida = new TelaPc();
#else // Using Atlys
	pSaida = new TelaAtlys();
#endif
	pSaida->resetOutput();
	//cout << "<------ FLAG ------>" << endl;
	//cout << estAtual << endl;
	switch (estAtual)
	{
	case 0: // ------------------------------------------ Estado S000
		pSaida->impMensa("\tSaldo 0");
		inputOption(); //@@@@@@@@@ ISR
		if (option == 1)
			setEstAtual(1);
		else if (option == 2)
			setEstAtual(2);
		else if (option == 3)
			setEstAtual(4);
		else if (6 < option && option < 11) // else if (pEntrada->getInputOperator() == 7,8,9,10)
		{									// Operator Mode
			modoOperador();					//@@@@@@@@@ ISR
		}
		else
			setEstAtual(0);
		break;
	case 1: // ------------------------------------------ Estado S025
		pSaida->impMensa("\tSaldo 25");
		inputOption(); //@@@@@@@@@ ISR
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
		{					// Operator Mode
			modoOperador(); //@@@@@@@@@ ISR
			saida = false;
		}
		else
			setEstAtual(1);

		break;
	case 2: // ------------------------------------------ Estado S050
		pSaida->impMensa("\tSaldo 50");
		inputOption(); //@@@@@@@@@ ISR
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
		{					// Operator Mode
			modoOperador(); //@@@@@@@@@ ISR
			saida = false;
		}
		else
			setEstAtual(2);
		break;
	case 3: // ------------------------------------------ Estado S075
		pSaida->impMensa("\tSaldo 75");
		inputOption(); //@@@@@@@@@ ISR
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
		{					// Operator Mode
			modoOperador(); //@@@@@@@@@ ISR
			saida = false;
		}
		else
			setEstAtual(3);
		break;
	case 4: // ------------------------------------------ Estado S100
		pSaida->impMensa("\tSaldo 100");
		inputOption(); //@@@@@@@@@ ISR
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
		{					// Operator Mode
			modoOperador(); //@@@@@@@@@ ISR
			saida = false;
		}
		else
			setEstAtual(4);
		break;
	case 5: // ------------------------------------------ Estado S125
		pSaida->impMensa("\tSaldo 125");
		inputOption(); //@@@@@@@@@ ISR
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
		{					// Operator Mode
			modoOperador(); //@@@@@@@@@ ISR
			saida = false;
		}
		else
			setEstAtual(5);
		break;
	case 6: // ------------------------------------------ Estado S150
		pSaida->impMensa("\tSaldo 150");
		inputOption(); //@@@@@@@@@ ISR
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
		{					// Operator Mode
			modoOperador(); //@@@@@@@@@ ISR
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
//
//
//
void MaquinaRefri::setEstAtual(int estado)
{
	estAtual = estado;
};
//
//
//
void MaquinaRefri::modoOperador()
{
	int login;
	bool logSolicitado = false;
	bool validez;

	// Verifica password do Operador. Si válido o requisitado é apresentado.
	pSaida->impMensa("\t\tIngresse password para consultar: ");
	inputPassword();			  // inserir password //@@@@@@@@@ ISR
	validez = verificaPassword(); // true: valido, false: invalido

	if (validez)
	{
		pSaida->impMensa("\t\t<<<Operador de Log valido>>>\n");

		cadVenda.fifoToList();

		switch (option)
		{
		case 7: // Listar total valor de vendas
			cout << "Total vendas:\t\t" << cadVenda.getNumeroVendas() << " refrigerantes" << endl;
			cout << "Valor total vendido:\t" << cadVenda.getNumeroVendas()*150 << endl;
			break;
		case 8: // Listar quantidade vendida de cada refrigerante
			cout << "Total de MEET:   " << cadVenda.getNumeroMEET() << endl;
			cout << "Total de ETIRPS: " << cadVenda.getNumeroETIRPS() << endl;
			break;
		case 9: // Listar periodo de dia com mais vendas
			cadVenda.getNumeroVendasDia();
			break;
		case 10: // Listar historico de vendas
			cadVenda.listarHistorico();
			break;
		default:
			cout << "\n\tIndefined FLAG\n";
			break;
		}
	}
	else
	{
		pSaida->impMensa("\tOperador nao valido");
	}
}
//
//
//
void MaquinaRefri::inputPassword()
{
#if INTERFACE == 1 || INTERFACE == 3 // Using PC (diretivas de compilação para processdor)
	pEntrada = new TecladoPc();
#else // Using Atlys
	pEntrada = new TecladoAtlys();
#endif
	//
	passwordInserido = pEntrada->getOperatorPassword();
}
//
//
// Verifica se o password usado pelo Operador corresponde com o cadastrado
bool MaquinaRefri::verificaPassword()
{
	if (passwordInserido == passwordOperator)
		return true;
	else
		return false;
};
//
//
//
void MaquinaRefri::showMenu()
{
	//MaquinaRefri *ptrMaquina;
	//void (MaquinaRefri::*pLogicaEstados)() = &MaquinaRefri::logicaEstados;
	//projectEscVoid.addTaskReadyEstruct(pLogicaEstados, ptrMaquina, 5, 1);
#if INTERFACE == 1 || INTERFACE == 3 // Using PC (diretivas de compilação para processdor)
	pSaida = new TelaPc();
#else // Using Atlys
	pSaida = new TelaAtlys();
#endif
	pSaida->menu();
}
//
//
//