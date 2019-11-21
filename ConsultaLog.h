#ifndef CONSULTALOG
#define CONSULTALOG

#include "CadastroVenda.h"
#include "Lista.h"
#include "FilaFifo.h"

/*
typedef struct{
    unsigned int horaVenda = 0;
    unsigned int dataVenda = 0;
    int tipoRefri; // 1: MEET, 2: ETIRPS
}totalVendas;
*/

class ConsultaLog{
		int login;
		int password;
        Lista<dadosVenda> todasVendas; //ok
        FilaFifo<dadosVenda> ultimaFifo; 
		CadastroVenda ultimoCadastro;
        int numeroVendas;
        int numeroMEET;
        int numeroETIRPS;
	public:
		ConsultaLog();
		bool verificaUsuario(int newLogin, int newPassword);
        

};

#endif		// CONSULTALOG