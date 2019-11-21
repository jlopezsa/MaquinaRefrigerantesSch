#include<iostream>
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
CadastroVenda::CadastroVenda() { 
	numeroVendas = 0;
    numeroMEET = 0;
    numeroETIRPS = 0;
};
// Destrutor
//CadastroVenda::~CadastroVenda() { };

// Configura o valor inicial de data e hora. Usado para setar as variáveis de ClockCalendar
void CadastroVenda::setDataHora(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int min, unsigned int sec, bool isPM){
	dataHora = new ClockCalendar(year,month,day,hour,min,sec,isPM); // falta localizar o delete, onde??
}

// Armazena em filfa Fifo as informações de cada venda de refrigerante.
void CadastroVenda::cadastraNovaVenda(int tipoRefri, int newHora){
	unsigned int year, month, day, hour, min, sec;
	bool isPM;
	if (tipoRefri == 5){ // cadastra venda do refri MEET
		std::cout << "\tTranscurrieron : " << newHora  << " segundos" << std::endl;
		atualizaDataHora(newHora);
		cout << "\tVenda de MEET as :" ;
		visualizaDataHora();
		novaVenda.nomeRefri = "MEET";
		novaVenda.codigoRefri = 1;
		novaVenda.valorRefri = 150;
		dataHora->readClock(hour, min, sec, isPM);
		novaVenda.h = hour;	novaVenda.mi = min; novaVenda.s = sec; novaVenda.ampm = isPM;
		dataHora->readCalendar(year, month, day);
		novaVenda.a = year; novaVenda.me = month; novaVenda.d = day;
		filaVendas.enqueue(novaVenda); // novaVenda é uma estrutura do tipo dadosVenda
	}
	else if (tipoRefri == 6){ // cadastra venda do refri ETIRPS
		std::cout << "\tTranscurrieron : " << newHora  << " segundos" << std::endl;
		atualizaDataHora(newHora);
		cout << "\tVenda de ETIRPS as :" ;
		visualizaDataHora();
		novaVenda.nomeRefri = "ETIRPS";
		novaVenda.codigoRefri = 2;
		novaVenda.valorRefri = 150;
		dataHora->readClock(hour, min, sec, isPM);
		novaVenda.h = hour;	novaVenda.mi = min; novaVenda.s = sec; novaVenda.ampm = isPM;
		dataHora->readCalendar(year, month, day);
		novaVenda.a = year; novaVenda.me = month; novaVenda.d = day;
		filaVendas.enqueue(novaVenda); // novaVenda é uma estrutura do tipo dadosVenda
	}
}


dadosVenda CadastroVenda::getNovaVenda(){
	return novaVenda;
};

void CadastroVenda::visualizaDataHora(){
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

void CadastroVenda::atualizaDataHora(int segundos){
	while(segundos > 0){
		dataHora->advance();
		segundos--;
	}
};

// Passa o conteudo da FiFo para uma Lista
void CadastroVenda::fifoToList(){
    dadosVenda salva; // salva: armazena as ultimas vendas contidas na FiFo
	cout << "---------- vendas registradas desde o ultimo log -----------" <<endl;
    while(!filaVendas.isQueueEmpty()){
		salva = filaVendas.dequeue();   // retira elemento da FiFo
        listaVendas.insertAfterLast(salva); // pasando dado retirado da Fifo para uma lista
		numeroVendas = numeroVendas + 1; // contador do número de vendas em total        
        if(salva.codigoRefri==1){ // refrigerante MEET vendido
            numeroMEET = numeroMEET + 1; // contador do número de vendas de MEET
        }
        else{   // refrigerante ETIRPS vendido
            numeroETIRPS = numeroETIRPS + 1; // contador do número de vendas de ETIRPS
        }		
		cout << "CodRef: "<< salva.codigoRefri <<"\tRefri: " << salva.nomeRefri <<"\tValor: "<<salva.valorRefri<< 
		"\tHora (h:m:s): "<<salva.h <<":"<<salva.mi<<":"<<salva.s <<"-"<<
		(salva.ampm ? " pm" : " am") << endl;        
	}
	cout << "------------------------------------------------------------" <<endl;
};

int CadastroVenda::getNumeroVendas(){
    return numeroVendas;
};

int CadastroVenda::getNumeroMEET(){
    return numeroMEET;
};

int CadastroVenda::getNumeroETIRPS(){
    return numeroETIRPS;
};

void CadastroVenda::listarHistorico(){
	/*
	dadosVenda onlyNode;
	Lista<dadosVenda> * ptrOnlyNode;
	onlyNode = listaVendas.readFirst(); // readFirst devolve os dados do primeiro nodo
	//*ptrOnlyNode = &onlyNode;
	while(!listaVendas.isEmpty()){
		cout << "CodRef: "<< onlyNode.codigoRefri <<"Refri: " << onlyNode.nomeRefri <<", Valor: "<<onlyNode.valorRefri<< 
		", Hora (h:m:s): "<<onlyNode.h <<":"<<onlyNode.mi<<":"<<onlyNode.s <<"-"<<
		(onlyNode.ampm ? " pm" : " am") << endl;
		onlyNode = listaVendas.getProxNode(&onlyNode);
	}
	*/
};

//definindo o metodo de Sobrecarga de operador.
//ostream &operator<< (ostream &c, CadastroVenda * teste){	
	//dadosVenda salva;
	//salva = novaVenda.getNovaVenda();
	//cout << "\n\t\t\t\t\t\t testando sobrecarga";
	//c << teste.novaVenda.codigoRefri; 
	//c << "NomeRefri: " << salva.nomeRefri; 
	//c << "Valor: " << salva.valorRefri;
	//c << "HoraVenda (h:m:s): "<< salva.h << ":" << salva.mi << ":" << salva.s << "-" <<	(salva.ampm ? " pm" : " am");
	//c << endl;
	//c << "julian";
	//return c;
//}

