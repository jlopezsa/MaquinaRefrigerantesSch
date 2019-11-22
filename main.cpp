// Controlador de máquina de venda de refrigerantes

#include<iostream>
using namespace std;

#define INTERFACE 1 // 1 = PC  || 2 = ATLYS



#include "MaquinaRefri.cpp"

int main(){

	
	MaquinaRefri maRefri;

	
	
	//objTecladoPc = new TecladoPc();
	//projectEsc.addTask(&objTecladoPc->getInput, 100, 0);

	maRefri.inicia();
	
	

	return 0;
}