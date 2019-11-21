#include<iostream>
#include <string>
using namespace std;

#include "InterfaceIn.cpp"
#include "TecladoPc.h"

int TecladoPc::getInput(){
	//cout << "FLAG TEST: into getInput" << endl;
		do{
			try{
				cin >> optionUser;
				if(optionUser < 0 || optionUser > 10)
					throw 1;
			}
			catch(int i){
				cout << "Erro, opção inválida"<<endl;
			}
			catch(...){
				cout << "Opção imprevista."<<endl;
			}
		}while(optionUser < 0 && optionUser >8);	
	
	return optionUser;
};


int TecladoPc::getInputOperator(){

		do{
			try{
				cin >> optionOperator;
				if(optionOperator < 0 || optionOperator > 5)
					throw 1;
			}
			catch(int i){
				cout << "Erro, opção inválida"<<endl;
			}
			catch(...){
				cout << "Opção imprevista."<<endl;
			}
		}while(optionOperator < 0 && optionOperator >5);	
	
	return optionOperator;
};

int TecladoPc::getOperatorPassword(){
	//cout << "FLAG TEST: into getOperatorPassword" << endl;
	cin >> operatorPassword;
	return operatorPassword;
};