#include<iostream>
using namespace std;

//#include "InterfaceOut.cpp"
#include "TelaAtlys.h"

volatile unsigned int *output = (volatile unsigned int *)0x80000a04;	// 1000 ... 0000 1010 0000 0100
volatile unsigned int *direction = (volatile unsigned int *)0x80000a08; // 1000 ... 0000 1010 0000 1000

TelaAtlys::TelaAtlys(){};
TelaAtlys::~TelaAtlys(){};

void TelaAtlys::impMensa(string mensagem){
	cout << mensagem << endl;
};

void TelaAtlys::menu(){
	cout << "\tPlataforma: dispensador de refrigerantes em Atlys\n";
	cout << "\t\t(BTNL)\t\t- USUARIO: Inserir moeda M025" << endl;
	cout << "\t\t(BTNC)\t\t- USUARIO: Inserir moeda M050" << endl;
	cout << "\t\t(BTNR)\t\t- USUARIO: Inserir moeda M100" << endl;
	cout << "\t\t(SW0 & BTNU)\t- USUARIO: Solicitar devolucao" << endl;
	cout << "\t\t(BTNU)\t\t- USUARIO: Escolher refrigerante MEETS" << endl;
	cout << "\t\t(BTND)\t\t- USUARIO: Escolher refrigerante ETIRPS" << endl;
	cout << "\t\t(SW1 & BTNL)\t - OPERADOR: Visualizar Valor total de vendas" << endl;
	cout << "\t\t(SW1 & BTNC)\t - OPERADOR: Qauntidade vendida de cada refrigerante" << endl;
	cout << "\t\t(SW1 & BTNR)\t - OPERADOR: Periodo do dia com mais vendas" << endl;
	cout << "\t\t(SW1 & BTNU)\t - OPERADOR: Historico de vendas" << endl;
};

void TelaAtlys::setOutput(int outOption){

    // Enable all Outputs
    *direction = 0xffffffff;
    *output = 0x00000000;
	switch (outOption){
		case 25:
            cout << "\tD025" << endl;
			// Assign value to output registers ("escreve" 0000 0001 nos LEDs)            
            *output = 0x00000001;
			break;
		case 50:
            cout << "\tD050" << endl;
			// Assign value to output registers ("escreve" 0000 0010 nos LEDs)
            *output = 0x00000002;
			break;
        case 75:
            cout << "\tD025" << endl;
			cout << "\tD050" << endl;
			// Assign value to output registers ("escreve" 0000 0010 nos LEDs)
            *output = 0x00000003;
			break;
		case 100:
            cout << "\tD100" << endl;
			// Assign value to output registers ("escreve" 0000 0100 nos LEDs)
            *output = 0x00000004;
			break;
        case 125:
            cout << "\tD025" << endl;
			cout << "\tD100" << endl;
			// Assign value to output registers ("escreve" 0000 0010 nos LEDs)
            *output = 0x00000005;
			break;
        case 150:
            cout << "\tD050" << endl;
			cout << "\tD100" << endl;
			// Assign value to output registers ("escreve" 0000 0110 nos LEDs)
            *output = 0x00000006;
			break;
		case 1:
            cout << "\tLMEET" << endl;
			// Assign value to output registers ("escreve" 0000 1000 nos LEDs)
            *output = 0x00000008;
			break;
		case 2:
            cout << "\tLETIRPS" << endl;
			// Assign value to output registers ("escreve" 0001 0000 nos LEDs)
            *output = 0x00000010;
			break;
		default:
			cout << "\tERRO: saida nao definida" << endl;
	}
	
};

void TelaAtlys::resetOutput(){
    // Enable all Outputs
    *direction = 0xffffffff;
    *output = 0x00000000;
};