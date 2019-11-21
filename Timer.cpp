#include <time.h>

#include "Timer.h"

Timer::Timer(void)
{
    static int bInitialized = 0;
    // Initialize the new software timer.
    length = 0;
    count = 0;
    pNext = NULL;
    if (!bInitialized)
    {
        bInitialized = 1;
    }
} /* Timer() */

Timer::~Timer(){};

// -------------------------------------------------------------------------

int Timer::start(unsigned long int nMilliseconds)
{
// Initialize the software timer.
#if INTERFACE == 1 // Using PC
    static long int length = nMilliseconds / MS_PER_TICK;
#elif INTERFACE == 2 // Using Atlys
    static long int length = 1000000;
#else                // Using WINDOWS
    static long int length = nMilliseconds / MS_PER_TICK;
#endif
    //
    // Add this timer to the active timer list.
    //
    clock_t time_ini, time_fim;
    double elapsedTicks;
    time_ini = clock();

    while (count < length)
    {
        count++;
    }

    time_fim = clock();
    //elapsedTicks = (double)(time_fim - time_ini) / CLOCKS_PER_SEC; ///CLOCKS_PER_SEC ;
    //cout << "Ticks: " << (time_fim - time_ini) << "| seg: " << elapsedTicks << endl;

    count = 0;
    return (0);
} /* start() */

int Timer::waitfor()
{
}