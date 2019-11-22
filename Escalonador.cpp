#include "Escalonador.h"
#include "Timer.cpp"

//template<typename TYPEFUNC,typename TASKTYPE,typename OBJECTTYPE>
Escalonador::Escalonador(){};

//template<typename TYPEFUNC,typename TASKTYPE,typename OBJECTTYPE>
Escalonador::~Escalonador(){};

// Inicializa as entradas de todas as tarefas com 0
//template<typename TYPEFUNC,typename TASKTYPE,typename OBJECTTYPE>
void Escalonador::init_Task_Timers()
{
    int i;
    for (i = 0; i < MAX_TASKS; i++)
    {
        GBL_task_table[i].ptrObject = NULL;
        GBL_task_table[i].task = NULL;
        GBL_task_table[i].ready = 0;
        GBL_task_table[i].delay = 0;
        GBL_task_table[i].period = 0;
        GBL_task_table[i].enabled = 0;
    }
};




//template<typename TYPEFUNC,typename TASKTYPE,typename OBJECTTYPE>
int Escalonador::addTask(void (MaquinaRefri::*task)(void), MaquinaRefri* newObject, int time, int priority)
//void Escalonador::addTask(void (*task)(void), int time, int priority)
{
    unsigned int t_time;
    /* Verifica se a prioridade é válida */
    if (priority >= MAX_TASKS || priority < 0)
        return 0;
    /* Verifica se sobre-escreve uma tarefa escalonada */
    if (GBL_task_table[priority].task != NULL)
        return 0;
    /* Escalona a tarefa */
    GBL_task_table[priority].ptrObject = newObject;
    GBL_task_table[priority].task = task;
    GBL_task_table[priority].ready = 0;
    GBL_task_table[priority].delay = time;
    GBL_task_table[priority].period = time;
    GBL_task_table[priority].enabled = 1;
    return 1;
}
/*
void Escalonador::removeTask(void (*task)(void))
{
    int i;
    for (i = 0; i < MAX_TASKS; i++)
    {
        if (GBL_task_list[i].task == task)
        {
            GBL_task_list[i].task = NULL;
            GBL_task_list[i].ready = 0; // era run. verificar isso
            GBL_task_list[i].delay = 0;
            GBL_task_list[i].period = 0;
            GBL_task_list[i].enabled = 0;
            return;
        }
    }
};
*/

//template<typename TYPEFUNC,typename TASKTYPE,typename OBJECTTYPE>
void Escalonador::Enable_Task(int task_number)
{
    GBL_task_table[task_number].enabled = 1;
}

//template<typename TYPEFUNC,typename TASKTYPE,typename OBJECTTYPE>
void Escalonador::Disable_Task(int task_number)
{
    GBL_task_table[task_number].enabled = 0;
}

//template<typename TYPEFUNC,typename TASKTYPE,typename OBJECTTYPE>
void Escalonador::Run_RTC_Scheduler()
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
            {                                       // se (task!=NULL & enable==1 & ready==1)
                cout << "\n\n\t\tFLAG TEST: into RUN Scheduler <" << setfill('-') << setw(50) << "Execut function" << endl;
                //(pT->*GBL_task_table[i].task)();       // Executa a tarefa
                (GBL_task_table[i].ptrObject->*GBL_task_table[i].task)();       // Executa a tarefa
                GBL_task_table[i].ready = 0;
                break;
            } // if
        }// for i
        tick_timer_intr();
        objTimer.start(1);
    }// while 1
}

/*declara uma função que será uma rotina de serviço
de interrupção (ISR - Interrupt Service Routine) de prioridade alta*/
#pragma INTERRUPT tick_timer_intr
//template<typename TYPEFUNC,typename TASKTYPE,typename OBJECTTYPE>
void Escalonador::tick_timer_intr(void)
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
        if ((GBL_task_table[i].task != NULL) &&     //Se for escalonada
            (GBL_task_table[i].enabled == 1) &&
            (GBL_task_table[i].delay != 0))
        {                                           // se (task!=NULL & enable==1 & delay!=0)
            //cout << "FLAG TEST: into tick_timer_intr if  1 delay: " << GBL_task_table[i].delay << endl;
            GBL_task_table[i].delay--;                                  // delay Decrementa
            if (GBL_task_table[i].delay == 0)
            {
                //cout << "FLAG TEST: into tick_timer_intr  2" << endl;
                GBL_task_table[i].ready = 1;                            // ready = 1
                GBL_task_table[i].delay = GBL_task_table[i].period;
            } // if delay == 0
        } // if
    } // for
}

//template<typename TYPEFUNC,typename TASKTYPE,typename OBJECTTYPE>
void Escalonador::Request_Task_Run(int task_number)
{
    GBL_task_table[task_number].ready = 1;
}