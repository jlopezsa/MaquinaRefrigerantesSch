// Controlador de máquina de venda de refrigerantes

#include <iostream>
using namespace std;

#define INTERFACE 1 // 1 = PC  || 2 = ATLYS
#define MAX_TASKS 3 // nr. máximo de tarefas

#include "MaquinaRefri.cpp"
#include "EscalonadorEstruct.cpp"

#if INTERFACE == 1 // Using PC (diretivas de compilação para processdor)
#include <pthread.h>
#else // Using Atlys

#endif

typedef struct
{
	int priority;
	float teste = 3.4;
} struTeste;

int main()
{

	EscalonadorEstruct projectEscVoid;
	MaquinaRefri objMaquina;
	MaquinaRefri *ptrMaquina;
	ptrMaquina = &objMaquina;

	objMaquina.inicia();

	//Escalonador<void,MaquinaRefri,MaquinaRefri> projectEscVoid;
	void (MaquinaRefri::*pShowMenu)() = &MaquinaRefri::showMenu;		   // Deitel pg 972
	void (MaquinaRefri::*pLogicaEstados)() = &MaquinaRefri::logicaEstados; // Deitel pg 972
	void (MaquinaRefri::*pInputOption)() = &MaquinaRefri::inputOption;	 // Deitel pg 972
	//void (MaquinaRefri::*pExemploThread)() = &MaquinaRefri::exemploThread;	 // Deitel pg 972

	projectEscVoid.init_Task_Timers();

	//projectEscVoid.addTaskReadyEstruct(pExemploThread, ptrMaquina, 5, 3);

	do
	{
		projectEscVoid.addTaskReadyEstruct(pShowMenu, ptrMaquina, 10, 0);
		projectEscVoid.addTaskReadyEstruct(pLogicaEstados, ptrMaquina, 10, 1);
		projectEscVoid.addTaskReadyEstruct(pInputOption, ptrMaquina, 10, 2);
		projectEscVoid.schedulerStatesLogic();
	} while (1);
	//projectEscVoid.Run_RTC_Scheduler(); // Executa a tarefa

	//----------------
	// testando lista
	/*
	struTeste listaDado;

	Lista<struTeste> sortList;
	float input;
	int counter=0;
	cout << "Prenchendo Lista:\n";
	do{
		cin >> listaDado.priority;
		sortList.insertionSort(listaDado);
		counter++;
	}while(counter<5);

	counter = 0;
	cout << "\nVisualizando Lista\n";
	do{
		cout << sortList.removeFirst().priority << endl;
	}while(!sortList.isEmpty());
	*/
	//----------------

	do
	{
		objMaquina.showMenu();
		objMaquina.logicaEstados();
	} while (1);

	return 0;
}