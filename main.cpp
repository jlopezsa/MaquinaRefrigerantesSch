// Controlador de máquina de venda de refrigerantes

#include<iostream>
using namespace std;

#define INTERFACE 1 // 1 = PC  || 2 = ATLYS
#define MAX_TASKS 3 // nr. máximo de tarefas

#include "MaquinaRefri.cpp"
#include "EscalonadorEstruct.cpp" 

int main(){

	EscalonadorEstruct projectEscVoid;
	MaquinaRefri objMaquina;
	MaquinaRefri *ptrMaquina;
	ptrMaquina = &objMaquina;
	
	objMaquina.inicia();
	
	//Escalonador<void,MaquinaRefri,MaquinaRefri> projectEscVoid;
	void (MaquinaRefri::*pShowMenu)() = &MaquinaRefri::showMenu; // Deitel pg 972
	void (MaquinaRefri::*pLogicaEstados)() = &MaquinaRefri::logicaEstados; // Deitel pg 972
	void (MaquinaRefri::*pInputOption)() = &MaquinaRefri::inputOption; // Deitel pg 972
	projectEscVoid.init_Task_Timers();
	//projectEscVoid.addTask(pShowMenu,ptrMaquina,10,0);
	//projectEscVoid.addTask(pLogicaEstados,ptrMaquina,10,1);
	//projectEscVoid.addTask(pInputOption,ptrMaquina,10,2);
	projectEscVoid.addTaskFifoReady(pShowMenu,ptrMaquina,10);
	projectEscVoid.addTaskFifoReady(pLogicaEstados,ptrMaquina,10);
	projectEscVoid.addTaskFifoReady(pInputOption,ptrMaquina,10);
	projectEscVoid.Run_RTC_Scheduler(); // Executa a tarefa

	do
	{
		objMaquina.showMenu();
		objMaquina.logicaEstados();
	}while (1);
	
	

	return 0;
}