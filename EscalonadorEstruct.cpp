#include <iostream>
#include <stdio.h>
#include <iomanip>
using namespace std;

#include "EscalonadorEstruct.h"
//#include "Lista.cpp"
#include "Timer.cpp"

//template<typename TYPEFUNC,typename TASKTYPE,typename OBJECTTYPE>
EscalonadorEstruct::EscalonadorEstruct()
{
    schedulerStates = 0;   
};
//
//template<typename TYPEFUNC,typename TASKTYPE,typename OBJECTTYPE>
EscalonadorEstruct::~EscalonadorEstruct(){};
//
// Inicializa as entradas de todas as tarefas com 0
//template<typename TYPEFUNC,typename TASKTYPE,typename OBJECTTYPE>
void EscalonadorEstruct::init_Task_TimersStruct()
{

    taskToSchedule.priorityID = 0;
    taskToSchedule.ptrObject = NULL;
    taskToSchedule.task = NULL;
    taskToSchedule.ready = 0;
    taskToSchedule.delay = 0;
    taskToSchedule.period = 0;
    taskToSchedule.enabled = 0;
    taskToSchedule.io_status = 0;
    //
    runningTask.priorityID = 0;
    runningTask.ptrObject = NULL;
    runningTask.task = NULL;
    runningTask.ready = 0;
    runningTask.delay = 0;
    runningTask.period = 0;
    runningTask.enabled = 0;
    runningTask.io_status = 0;
};
//
//
//
int EscalonadorEstruct::addTaskReadyEstruct(void (MaquinaRefri::*task)(void), MaquinaRefri *newObject, int time, int priority)
{
    /* Verifica se a prioridade é válida */
    /* Verifica se sobre-escreve uma tarefa escalonada */

    /* Escalona a tarefa */
    taskToSchedule.priorityID = priority;
    taskToSchedule.ptrObject = newObject;
    taskToSchedule.task = task;
    taskToSchedule.ready = 0;
    taskToSchedule.delay = time;
    taskToSchedule.period = time;
    taskToSchedule.enabled = 1;

    readyEstruct.insertionSort(taskToSchedule);
    return 1;
}
//
//
//
int EscalonadorEstruct::removeTask(void (MaquinaRefri::*task)(void), MaquinaRefri *newObject)
{
    readyEstruct.removeFirst();
    return 1;
}
//
//
//
void EscalonadorEstruct::Run_RTC_SchedulerEstruct()
{ // Sempre executando
    int i;
    //GBL_run_scheduler = 1;
    while (1)
    { // Laço infinito; verifica cada tarefa
        if ((runningTask.task != NULL) &&
            // Verifica se habilitada
            (runningTask.enabled == 1) &&
            // Verifica se está pronta para executar
            (runningTask.ready == 1))
        { // se (task!=NULL & enable==1 & ready==1)
            cout << "\n\n\t\tFLAG TEST: into RUN Scheduler <" << setfill('-') << setw(50) << "Execut function" << endl;
            //(pT->*GBL_task_table[i].task)();       // Executa a tarefa
            (runningTask.ptrObject->*runningTask.task)(); // <<<<<<<< Executa a tarefa
            runningTask.ready = 0;
            break;
        } // if
        tick_timer_intrStruct();
        objTimer.start(1);
    } // while 1
}
//
//
//
#pragma INTERRUPT tick_timer_intr
void EscalonadorEstruct::tick_timer_intrStruct(void)
{
    //cout << "FLAG TEST: into tick_timer_intr  0000000" << endl;
    //static char i;
    int i;
    //cout << "\t\tDelay task 0: " << setfill(' ') << setw(2) << runningTask.delay << endl;

    //cout << "FLAG TEST: into tick_timer_intr for " << i << endl;
    if ((runningTask.task != NULL) && //Se for escalonada
        (runningTask.enabled == 1) &&
        (runningTask.delay != 0))
    { // se (task!=NULL & enable==1 & delay!=0)
        //cout << "FLAG TEST: into tick_timer_intr if  1 delay: " << GBL_task_table[i].delay << endl;
        runningTask.delay--; // delay Decrementa
        if (runningTask.delay == 0)
        {
            //cout << "FLAG TEST: into tick_timer_intr  2" << endl;
            runningTask.ready = 1; // ready = 1
            runningTask.delay = runningTask.period;
        } // if delay == 0
    }     // if
}
//
//
//

void EscalonadorEstruct::schedulerStatesLogic()
{
    int toStart;
    switch (schedulerStates)
    {
    case 0: // created
        //cout << "CREATED: Aperte tecla para iniciar: ";
        //cin >> toStart;
        
        schedulerStates = 2;
        break;
    case 1: // ready
        //cout << "READY: aperte tecla para continuar: ";
        //if (readyEstruct.readFirst().priorityID >= runningTask.priorityID) // if priReady > priRunning
            schedulerStates = 2;
        //cin >> toStart;
        break;
    case 2: // running
        //cout << "RUNNING 1: state\n";
        runningTask = readyEstruct.readFirst();
        readyEstruct.removeFirst();
        //printf("\e[H\e[2J");
        Run_RTC_SchedulerEstruct();
        if (runningTask.ready == 0)// && runningTask.io_status == 0)
            schedulerStates = 4;
        // executing task
        // while priRunning > priReady || delay > 0
        //      delay --
        // if priRunning < pryReady && delay > 0
        //      schedulerStates = 1
        // if delay == 0
        //      schedulerStates = 4
        // if ???? para ir no waiting
        break;
    case 3: // waiting
        break;
    case 4: // terminated
        cout << "TERMINATED: \n";
        terminatedTask = runningTask;        
        schedulerStates = 2;
        break;
    default:
        break;
    }
}
/*
void EscalonadorEstruct::Run_RTC_Scheduler()
{ // Sempre executando
    int i;
    //GBL_run_scheduler = 1;
    while (1)
    { // Laço infinito; verifica cada tarefa
        for (i = 0; i < MAX_TASKS; i++)
        { // Se essa for uma tarefa escalonada valida
            if ((GBL_task_table[i].task != NULL) &&
                // Verifica se habilitada
                (GBL_task_table[i].enabled == 1) &&
                // Verifica se está pronta para executar
                (GBL_task_table[i].ready == 1))
            { // se (task!=NULL & enable==1 & ready==1)
                cout << "\n\n\t\tFLAG TEST: into RUN Scheduler <" << setfill('-') << setw(50) << "Execut function" << endl;
                //(pT->*GBL_task_table[i].task)();       // Executa a tarefa
                (GBL_task_table[i].ptrObject->*GBL_task_table[i].task)(); // Executa a tarefa
                GBL_task_table[i].ready = 0;
                break;
            } // if
        }     // for i
        tick_timer_intr();
        objTimer.start(1);
    } // while 1
}
*/
//
/*
void Escalonador::addTask(void (*task)(void), int time, int priority)
int EscalonadorEstruct::addTask(void (MaquinaRefri::*task)(void), MaquinaRefri *newObject, int time, int priority)
{
}
*/
//
//
//
//
//
//template<typename TYPEFUNC,typename TASKTYPE,typename OBJECTTYPE>
/*
void EscalonadorEstruct::Enable_Task(int task_number)
{
    GBL_task_table[task_number].enabled = 1;
}
*/
//
//
//
//template<typename TYPEFUNC,typename TASKTYPE,typename OBJECTTYPE>
/*
void EscalonadorEstruct::Disable_Task(int task_number)
{
    GBL_task_table[task_number].enabled = 0;
}
*/
//

//
/*declara uma função que será uma rotina de serviço
de interrupção (ISR - Interrupt Service Routine) de prioridade alta*/
//template<typename TYPEFUNC,typename TASKTYPE,typename OBJECTTYPE>
/*
#pragma INTERRUPT tick_timer_intr
void EscalonadorEstruct::tick_timer_intr(void)
{
    //cout << "FLAG TEST: into tick_timer_intr  0000000" << endl;
    //static char i;
    int i;
    cout << "\t\tDelay task 0: " << setfill(' ') << setw(2) << GBL_task_table[0].delay;
    cout << "\tDelay task 1: " << setfill(' ') << setw(2) << GBL_task_table[1].delay;
    cout << "\tDelay task 2: " << GBL_task_table[2].delay << endl;
    //cout << endl;
    for (i = 0; i < MAX_TASKS; i++)
    {
        //cout << "FLAG TEST: into tick_timer_intr for " << i << endl;
        if ((GBL_task_table[i].task != NULL) && //Se for escalonada
            (GBL_task_table[i].enabled == 1) &&
            (GBL_task_table[i].delay != 0))
        { // se (task!=NULL & enable==1 & delay!=0)
            //cout << "FLAG TEST: into tick_timer_intr if  1 delay: " << GBL_task_table[i].delay << endl;
            GBL_task_table[i].delay--; // delay Decrementa
            if (GBL_task_table[i].delay == 0)
            {
                //cout << "FLAG TEST: into tick_timer_intr  2" << endl;
                GBL_task_table[i].ready = 1; // ready = 1
                GBL_task_table[i].delay = GBL_task_table[i].period;
            } // if delay == 0
        }     // if
    }         // for
}
*/
//
//
//
//template<typename TYPEFUNC,typename TASKTYPE,typename OBJECTTYPE>


void EscalonadorEstruct::Request_Task_Run()
{
    taskToSchedule.ready = 1;
}

//
//
//
//