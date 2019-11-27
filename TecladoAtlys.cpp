#include <iostream>
#include <string>
using namespace std;

#include "InterfaceIn.cpp"
#include "TecladoAtlys.h"

volatile unsigned int *data = (volatile unsigned int *)0x80000a00; // 1000 ... 0000 1010 0000 0000

int TecladoAtlys::getInput()
{
    //std::cout << "Current value of gpio lines: 0x" << *data << std::endl;

    do
    {
    } while (*data != 131072 && *data != 1048576 && *data != 524288 && *data != 65792 && *data != 65536 && *data != 262144 && *data !=131584  && *data != 1049088 && *data != 524800 && *data != 66048);

    if (*data == 131072) // BTNL
        optionUser = 1;
    else if (*data == 1048576) // BTNC
        optionUser = 2;
    else if (*data == 524288) // BTNR
        optionUser = 3;
    else if (*data == 65792) // SW0 & BTNU
        optionUser = 4;
    else if (*data == 65536) // BTNU
        optionUser = 5;
    else if (*data == 262144) // BTND
        optionUser = 6;
    else if (*data == 131584) // SW1 & BTNL
        optionUser = 7;
    else if (*data == 1049088) // SW1 & BTNC
        optionUser = 8;
    else if (*data == 524800) // SW1 & BTNR
        optionUser = 9;
    else if (*data == 66048) // SW1 & BTNU
        optionUser = 10;

    return optionUser;
};

int TecladoAtlys::getInputOperator()
{
    //std::cout << "Current value of gpio lines: 0x" << *data << std::endl;

    do
    {
    } while (*data != 131584 && *data != 1049088 && *data != 524800 && *data != 66048 && *data != 262656);

    if (*data == 131584)
        optionOperator = 1;
    else if (*data == 1049088)
        optionOperator = 2;
    else if (*data == 524800)
        optionOperator = 3;
    else if (*data == 66048)
        optionOperator = 4;
    else if (*data == 262656)
        optionOperator = 5;

    return optionOperator;
};

int TecladoAtlys::getOperatorPassword()
{
    do
    {
    } while (*data != 655360);

    if (*data == 655360)
        optionOperator = 33;
    else
        optionOperator = 0;
        
    return optionOperator;
};

//*********************
// Enable all Outputs

// Realiza a leitura dos valores indicados nos pinos de entrada (Switches e Buttons)
