#ifndef ESCALONADOR
#define ESCALONADOR

#include <string>
using namespace std;

#include "InterfaceIn.h"
#include "MaquinaRefri.h"
#include "FilaFifo.h"
#include "Timer.h"

#define MAX_TASKS 3 // nr. máximo de tarefas

// Define estrutura com as informações da Task Control Block (TCB)
typedef struct
{
    string state;          // ready, running, waiting. Opcional
    MaquinaRefri *ptrObject; // ponteiro do objeto onde encontra-se o metodo que vai ser escalonado
    void (MaquinaRefri::*task)(void);    // ponteiro para uma função
    int ready; // se 1: pronto para executar, se 0: não pronto para executar
    int delay;
    int period;
    int enabled; // se 1: tarefa ativa, se 0: não ativa
}task_t;
//
//
//
// Define a classe
class EscalonadorEstruct
{
private:
    task_t GBL_task_table[MAX_TASKS]; // tabela global de tarefas
    task_t taskToSchedule;
    FilaFifo<task_t> fifoReady;
    int schedulerStates;
public:
    EscalonadorEstruct();
    ~EscalonadorEstruct();
    void init_Task_Timers(void); // inicializa todas as tarefas em 0
    //template <typename TASKTYPE, typename OBJECTTYPE>
    int addTask(void (MaquinaRefri::*task)(void), MaquinaRefri *newObject, int time, int priority);
    int addTaskFifoReady(void (MaquinaRefri::*task)(void), MaquinaRefri *newObject, int time, int priority);
    //void removeTask(void (*task)(void));
    void Enable_Task(int task_number);
    void Disable_Task(int task_number);
    void Run_RTC_Scheduler();
    //void Run_RTC_SchedulerEstruct();
    void tick_timer_intr(void);
    void Request_Task_Run(int task_number);
    void schedulerStatesLogic();
    Timer objTimer;
};

#endif // ESCALONADOR