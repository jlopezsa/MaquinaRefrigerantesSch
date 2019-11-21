#ifndef ESCALONADOR
#define ESCALONADOR

#include <string>
using namespace std;

#include "InterfaceIn.h"
#include "TecladoPc.h"
#include "Timer.h"

#define MAX_TASKS 2 // nr. máximo de tarefas

// Define estrutura com as informações da Task Control Block (TCB)
struct task_t
{
    string state; // ready, running, waiting. Opcional
    TecladoPc* ptrObject; // ponteiro do objeto onde encontra-se o metodo que vai ser escalonado
    int (InterfaceIn::*task)(void); // ponteiro para uma função
    int ready; // se 1: pronto para executar, se 0: não pronto para executar
    int delay;
    int period;
    int enabled; // se 1: tarefa ativa, se 0: não ativa

};

// Define a classe
class Escalonador
{
    private:
        task_t GBL_task_table[MAX_TASKS]; // tabela global de tarefas
    public:
        Escalonador();
        ~Escalonador();
        void init_Task_Timers(void); // inicializa todas as tarefas em 0
        template<typename TASKTYPE, typename OBJECTTYPE>
        int addTask(int (TASKTYPE::*task)(void), OBJECTTYPE* newObject, int time, int priority);
        //void removeTask(void (*task)(void));
        void Enable_Task(int task_number);
        void Disable_Task(int task_number);
        void Run_RTC_Scheduler(/*TecladoPc* pT*/);   
        void tick_timer_intr(void); 
        void Request_Task_Run(int task_number);
        Timer objTimer;   
};

#endif // ESCALONADOR