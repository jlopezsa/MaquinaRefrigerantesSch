#include<iostream>
using namespace std;

#include "InterfaceOut.cpp"
#include "TelaPc.h"

TelaPc::TelaPc(){};
TelaPc::~TelaPc(){};

void TelaPc::impMensa(string mensagem){
	cout << mensagem << endl;
};

void TelaPc::menu(){
	cout << endl;
	cout << "\tPlataforma: dispensador de refrigerantes em PC\n";
	cout << "\tIngrese opcao desejada: " << endl;
	cout << "\t\t 1 - USUARIO: Inserir moeda M025" << endl;
	cout << "\t\t 2 - USUARIO: Inserir moeda M050" << endl;
	cout << "\t\t 3 - USUARIO: Inserir moeda M100" << endl;
	cout << "\t\t 4 - USUARIO: Solicitar devolucao" << endl;
	cout << "\t\t 5 - USUARIO: Escolher refrigerante MEETS" << endl;
	cout << "\t\t 6 - USUARIO: Escolher refrigerante ETIRPS" << endl;
	cout << "\t\t 7 - OPERADOR: Visualizar Valor total de vendas" << endl;
	cout << "\t\t 8 - OPERADOR: Quantidade vendida de cada refrigerante" << endl;
	cout << "\t\t 9 - OPERADOR: Periodo do dia com mais vendas" << endl;
	cout << "\t\t10 - OPERADOR: Historico total de vendas" << endl;
};

void TelaPc::setOutput(int outOption){
	switch (outOption){
		case 25:
			cout << "\tD025" << endl;
			break;
		case 50:
			cout << "\tD050" << endl;
			break;
		case 75:
			cout << "\tD025" << endl;
			cout << "\tD050" << endl;
			break;
		case 100:
			cout << "\tD100" << endl;
			break;
		case 125:
			cout << "\tD025" << endl;
			cout << "\tD100" << endl;
			break;
		case 150:
			cout << "\tD050" << endl;
			cout << "\tD100" << endl;
			break;
		case 1:
			cout << "\tMEET" << endl;
			break;
		case 2:
			cout << "\tLETIRPS" << endl;
			break;
		default:
			cout << "\tERRO: saida nao definida" << endl;
	}
	
};

void TelaPc::resetOutput(){
    
};