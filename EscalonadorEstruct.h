#ifndef ESCALONADORESTRUCT
#define ESCALONADORESTRUCT

#include <string>
using namespace std;

//#include "Lista.h"
#include "Timer.h"
#include "MaquinaRefri.h"


// Define estrutura com as informações da Task Control Block (TCB)
typedef struct
{
    int priorityID;
    string state;          // ready, running, waiting. Opcional
    MaquinaRefri *ptrObject; // ponteiro do objeto onde encontra-se o metodo que vai ser escalonado
    void (MaquinaRefri::*task)(void);    // ponteiro para uma função
    int ready; // se 1: pronto para executar, se 0: não pronto para executar
    int delay;
    int period;
    int enabled; // se 1: tarefa ativa, se 0: não ativa
    int io_status; // 1: imput required
}task_t;
//
//
//
// Define a classe
class EscalonadorEstruct
{
private:
    task_t taskToSchedule; // task to be scheduler
    Lista<task_t> readyEstruct; // Task into FIFO
    task_t  runningTask; // Executing task
    task_t  terminatedTask; // Terminated task
    int schedulerStates;
public:
    EscalonadorEstruct();
    ~EscalonadorEstruct();
    void init_Task_TimersStruct(void); // inicializa todas as tarefas em 0
    int addTaskReadyEstruct(void (MaquinaRefri::*task)(void), MaquinaRefri *newObject, int time, int priority);
    int removeTask(void (MaquinaRefri::*task)(void), MaquinaRefri *newObject);
    //void removeTask(void (*task)(void));
    //void Enable_Task(int task_number);
    //void Disable_Task(int task_number);
    //void Run_RTC_Scheduler();
    void Run_RTC_SchedulerEstruct();
    void tick_timer_intr(void);
    void tick_timer_intrStruct(void);
    void Request_Task_Run();
    void schedulerStatesLogic();
    Timer objTimer;
};

#endif // ESCALONADORESTRUCT