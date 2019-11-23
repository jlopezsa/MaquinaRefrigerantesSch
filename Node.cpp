// Codigo usando como referência o livro [Deitel, C++ how to program] capítulo 21 "Estruturas de dados"
// Codigo desenvolvido usando como referência o código do professor Eduardo Bezerra.
// <http://gse.ufsc.br/bezerra/disciplinas/cpp/material/EstruturasDados/LinkedList/ListaInteiros_Nodo_em_ClasseSeparada/Nodo.cpp> 

#include "Node.h"

// Constructor
template<typename NODETYPE> 
Node<NODETYPE>::Node(NODETYPE newData, Node<NODETYPE>* nxt){
       data = newData;
       nextNode = nxt;
}

// setData: Armazena os valores do tipo NODETYPE no nodo
template<typename NODETYPE>void 
Node<NODETYPE>::setData(NODETYPE newData){
     data = newData;
}

// getData
template<typename NODETYPE> 
NODETYPE Node<NODETYPE>::getData() const{
     return data;
}

// setProx
template<typename NODETYPE>
void Node<NODETYPE>::setProx(Node<NODETYPE> *nxt){
     nextNode = nxt;
}

// getProx
template<typename NODETYPE>
Node<NODETYPE> * Node<NODETYPE>::getProx(){
     return nextNode;
}

// setNext stores the pointer to the next Nodo in the list in the "next" field