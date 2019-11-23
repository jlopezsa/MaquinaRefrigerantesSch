#include <iostream>
#include <time.h>
#include <iomanip>
#include <string>
using namespace std;

#include "CadastroVenda.h"
#include "ClockCalendar.cpp"
#include "Clock.cpp"
#include "Calendar.cpp"
//#include "Lista.cpp" // declarada previamente em FilaFifo.cpp
#include "FilaFifo.cpp"

// Construtor
CadastroVenda::CadastroVenda()
{
	numeroVendas = 0;
	numeroMEET = 0;
	numeroETIRPS = 0;
	vendasNoDia.madrugada = 0;
	vendasNoDia.manha = 0;
	vendasNoDia.tarde = 0;
	vendasNoDia.noite = 0;
};
// Destrutor
//CadastroVenda::~CadastroVenda() { };

// Configura o valor inicial de data e hora. Usado para setar as variáveis de ClockCalendar
void CadastroVenda::setDataHora(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int min, unsigned int sec, bool isPM)
{
	dataHora = new ClockCalendar(year, month, day, hour, min, sec, isPM); // falta localizar o delete, onde??
}

// Armazena em filfa Fifo as informações de cada venda de refrigerante.
void CadastroVenda::cadastraNovaVenda(int tipoRefri, int newHora)
{
	unsigned int year, month, day, hour, min, sec;
	bool isPM;
	if (tipoRefri == 5)
	{ // cadastra venda do refri MEET
		std::cout << "\tTranscurrieron : " << newHora << " segundos" << std::endl;
		atualizaDataHora(newHora);
		cout << "\tVenda de MEET as :";
		visualizaDataHora();
		novaVenda.nomeRefri = "MEET";
		novaVenda.codigoRefri = 1;
		novaVenda.valorRefri = 150;
		dataHora->readClock(hour, min, sec, isPM);
		novaVenda.h = hour;
		novaVenda.mi = min;
		novaVenda.s = sec;
		novaVenda.ampm = isPM;
		dataHora->readCalendar(year, month, day);
		novaVenda.a = year;
		novaVenda.me = month;
		novaVenda.d = day;
		filaVendas.enqueue(novaVenda); // novaVenda é uma estrutura do tipo dadosVenda
	}
	else if (tipoRefri == 6)
	{ // cadastra venda do refri ETIRPS
		std::cout << "\tTranscurrieron : " << newHora << " segundos" << std::endl;
		atualizaDataHora(newHora);
		cout << "\tVenda de ETIRPS as :";
		visualizaDataHora();
		novaVenda.nomeRefri = "ETIRPS";
		novaVenda.codigoRefri = 2;
		novaVenda.valorRefri = 150;
		dataHora->readClock(hour, min, sec, isPM);
		novaVenda.h = hour;
		novaVenda.mi = min;
		novaVenda.s = sec;
		novaVenda.ampm = isPM;
		dataHora->readCalendar(year, month, day);
		novaVenda.a = year;
		novaVenda.me = month;
		novaVenda.d = day;
		filaVendas.enqueue(novaVenda); // novaVenda é uma estrutura do tipo dadosVenda
	}
}

void CadastroVenda::periodoMaiVendas(dadosVenda newNodo)
{
	if ((newNodo.h >= 0 && (newNodo.h <= 5 && newNodo.mi < 60)) && (newNodo.ampm == false)) //contabiliza vendas na madrugada
		vendasNoDia.madrugada = vendasNoDia.madrugada + 1;
	else if ((newNodo.h >= 6 && (newNodo.h <= 11 && newNodo.mi < 60)) && (newNodo.ampm == false)) //contabiliza vendas na manha
		vendasNoDia.manha = vendasNoDia.manha + 1;
	else if ((newNodo.h >= 0 && (newNodo.h <= 6 && newNodo.mi < 60)) && (newNodo.ampm == true)) //contabiliza vendas na tarde
		vendasNoDia.tarde = vendasNoDia.tarde + 1;
	else //contabiliza vendas na noite
		vendasNoDia.noite = vendasNoDia.noite + 1;

	// Calculando o periodo do dia com mais vendas;
	int vetorMaior[4];
	vetorMaior[0] = vendasNoDia.madrugada;
	vetorMaior[1] = vendasNoDia.manha;
	vetorMaior[2] = vendasNoDia.tarde;
	vetorMaior[3] = vendasNoDia.noite;

	int maior = vetorMaior[0];
	diaMaiVendas[0] = 0; // [0]:dia com mais vendas | [1]: numero de vendas nesse dia
	diaMaiVendas[1] = maior;
	for (int i = 1; i < 4; i++)
	{
		if (vetorMaior[i] > maior)
		{
			maior = vetorMaior[i];
			diaMaiVendas[0] = i;
			diaMaiVendas[1] = maior;
		}
	}
};

dadosVenda CadastroVenda::getNovaVenda()
{
	return novaVenda;
};

void CadastroVenda::visualizaDataHora()
{
	unsigned int year, month, day, hour, min, sec;
	bool isPM;

	dataHora->readClock(hour, min, sec, isPM);
	dataHora->readCalendar(year, month, day);

	cout << setw(2) << setfill('0') << year;
	cout << "/";
	cout << setw(2) << setfill('0') << month;
	cout << "/";
	cout << setw(2) << setfill('0') << day;
	cout << " | ";
	cout << setw(2) << setfill('0') << hour;
	cout << ":";
	cout << setw(2) << setfill('0') << min;
	cout << ":";
	cout << setw(2) << setfill('0') << sec;
	cout << (isPM ? " pm" : " am");
};

void CadastroVenda::atualizaDataHora(int segundos)
{
	while (segundos > 0)
	{
		dataHora->advance();
		segundos--;
	}
};

// Passa o conteudo da FiFo para uma Lista
void CadastroVenda::fifoToList()
{
	dadosVenda salva; // salva: armazena as ultimas vendas contidas na FiFo
	cout << "---------- vendas registradas desde o ultimo log -----------" << endl;
	while (!filaVendas.isQueueEmpty())
	{
		salva = filaVendas.dequeue();		// retira elemento da FiFo
		listaVendas.insertAfterLast(salva); // pasando dado retirado da Fifo para uma lista
		numeroVendas = numeroVendas + 1;	// contador do número de vendas em total
		if (salva.codigoRefri == 1)
		{								 // refrigerante MEET vendido
			numeroMEET = numeroMEET + 1; // contador do número de vendas de MEET
		}
		else
		{									 // refrigerante ETIRPS vendido
			numeroETIRPS = numeroETIRPS + 1; // contador do número de vendas de ETIRPS
		}
		periodoMaiVendas(salva);
		cout << "CodRef: " << salva.codigoRefri << "\tRefri: " << salva.nomeRefri << "\tValor: " << salva.valorRefri << "\tHora (h:m:s): " << salva.h << ":" << salva.mi << ":" << salva.s << "-" << (salva.ampm ? " pm" : " am") << "\tData (a/m/d): " << salva.a << "/" << salva.me << "/" << salva.d << endl;
	}
	cout << "------------------------------------------------------------" << endl;
};

int CadastroVenda::getNumeroVendas()
{
	return numeroVendas;
};

int CadastroVenda::getNumeroMEET()
{
	return numeroMEET;
};

int CadastroVenda::getNumeroETIRPS()
{
	return numeroETIRPS;
};

void CadastroVenda::getNumeroVendasDia()
{
	//int *ptrDiaMaiVendas;
	cout << "Madrugada: " << vendasNoDia.madrugada << "\tManha : " << vendasNoDia.manha << "\tTarde: " << vendasNoDia.tarde << "\tNoite: " << vendasNoDia.noite << endl;
	cout << "Periodo do dia com mais vendas:\t";
	if (diaMaiVendas[0] == 0)
		cout << " MADRUGADA "; // [0]:dia com mais vendas | [1]: numero de vendas nesse dia
	else if (diaMaiVendas[0] == 1)
		cout << "MANHA";
	else if (diaMaiVendas[0] == 2)
		cout << "TARDE";
	else
		cout << "NOITE";
	cout << endl << "Total de vendas no periodo e:\t" << diaMaiVendas[1] << " refrigerantes" << endl;
};

void CadastroVenda::listarHistorico()
{
	cout << "---------------- Registro de todas as vendas ---------------" << endl;
	listaVendas.listAll();
};
