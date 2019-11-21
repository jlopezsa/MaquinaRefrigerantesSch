//https://www.e-reading.club/chapter.php/129272/103/Barr_-_Programming_Embedded_Systems_in_C_and_C++.html
//http://www.pudn.com/Download/item/id/204952.html

#ifndef TIMER
#define TIMER

#define MS_PER_TICK 0.000000004//0.000000004

class Timer
{
public:
    Timer();
    ~Timer();
    int start(unsigned long int nMilliseconds);
    int waitfor();
    //void cancel();
    unsigned long int length;
    unsigned long int count;
    Timer *pNext;
};

#endif //TIMER