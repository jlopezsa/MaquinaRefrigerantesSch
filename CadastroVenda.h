#ifndef CADASTROVENDA
#define CADASTROVENDA

#include <iostream>
#include <time.h>
#include <string>

using namespace std;

#include "ClockCalendar.h"
//#include "Lista.h"
#include "FilaFifo.h"

// definicao da estrutura
typedef struct{
    unsigned int h,mi,s;
    bool ampm; // true: pm, false: am 
    unsigned int a,me,d;
    int valorRefri; 
    string nomeRefri; // MEET, ETIRPS
    int codigoRefri; // 1: MEET, 2: ETIRPS
}dadosVenda;

typedef struct{
    int madrugada;
    int manha;
    int tarde;
    int noite;
}periodoDia;

class CadastroVenda {
        FilaFifo<dadosVenda> filaVendas;
        Lista<dadosVenda> listaVendas;
        dadosVenda novaVenda;
        periodoDia vendasNoDia;
        int numeroVendas;
        int numeroMEET;
        int numeroETIRPS;
        int diaMaiVendas[2]; // [0]:dia com mais vendas | [1]: numero de vendas nesse dia     
    protected:
        ClockCalendar* dataHora; // *dataHora ponteiro do tipo ClockCalendar        
    public:
        CadastroVenda();
        //~CadastroVenda();
        void setDataHora(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int min, unsigned int sec, bool isPM);
        void cadastraNovaVenda(int newRefri, int newHora);
        dadosVenda getNovaVenda();
        void visualizaDataHora();        
        void atualizaDataHora(int segundos);
        void fifoToList();
        void periodoMaiVendas(dadosVenda newNodo);
        int getNumeroVendas();
		int getNumeroMEET();
        int getNumeroETIRPS();
        void getNumeroVendasDia();
        void listarHistorico();
        //friend ostream &operator<< (ostream& c, CadastroVenda * teste); // sobrecarga de operador
};

#endif		// CADASTROVENDA

