#ifndef MAQUINAREFRI
#define MAQUINAREFRI

#include "InterfaceIn.h"
#include "InterfaceOut.h"
#include "CadastroVenda.h"

class MaquinaRefri
{
	InterfaceIn *pEntrada; // pEntrada aponta para diversas formas (polimorfismo)
	InterfaceOut *pSaida;
	CadastroVenda cadVenda;
	int estAtual;
	int passwordOperator;
	int passwordInserido;
	int option;
	//MaquinaRefri * pTh;
public:
	MaquinaRefri();
	void inicia();
	void setEstAtual(int);
	void modoOperador();
	bool verificaPassword();
	void logicaEstados();
	void inputOption();
	void inputPassword();
	void showMenu();
	static void* exemploThread(void *);
#if INTERFACE == 1 || INTERFACE == 3// Using PC (diretivas de compilação para processdor)
	time_t timer, timerFim; // contabiliza segundos no PC
	pthread_t threadExemploThread;
#else						// Using Atlys
	clock_t inicio, fim; // contabiliza segundo no LEON3
#endif
};

#endif // MAQUINAREFRI