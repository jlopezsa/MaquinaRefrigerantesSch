#ifndef MAQUINAREFRI
#define MAQUINAREFRI

#define INTERFACE 1 // 1 = PC  || 2 = ATLYS

#include "InterfaceIn.h"
#include "InterfaceOut.h"
#include "CadastroVenda.h"
#include "ConsultaLog.h"



class MaquinaRefri
{
	InterfaceIn *pEntrada; // pEntrada aponta para diversas formas (polimorfismo)
	InterfaceOut *pSaida;
	CadastroVenda cadVenda;
	int estAtual;
	int passwordOperator;
public:
	MaquinaRefri();
	void inicia();
	void setEstAtual(int);
	void modoOperador(int);
	bool verificaPassword(int);
	void logicaEstados();
	int inputOption();
	void showMenu();
#if INTERFACE == 1 || INTERFACE == 3			// Using PC (diretivas de compilação para processdor)
	time_t timer, timerFim; // contabiliza segundos no PC
#else						// Using Atlys
	clock_t inicio, fim; // contabiliza segundo no LEON3
#endif
};

#endif // MAQUINAREFRI