// Codigo desenvolvido usando como referência o código do professor Eduardo Bezerra.
// http://gse.ufsc.br/bezerra/disciplinas/cpp/material/EstruturasDados/LinkedList/ListaInteiros_Nodo_em_ClasseSeparada/List.h

#ifndef LISTA
#define LISTA

#include "Node.cpp"


template<typename NODETYPE>
class Lista{ 

  Node<NODETYPE> * head;
  Node<NODETYPE> * last;

public:
  Lista();
  ~Lista();
  void insertBeforeFirst(NODETYPE newData);
  void insertAfterLast(NODETYPE newData);
  NODETYPE readFirst();
  NODETYPE removeFirst();
  bool isEmpty();
  void insertionSort(NODETYPE newData); // insere valor de forma ordenada
  int removeNode(NODETYPE newData);
  void listAll();
  //NODETYPE getProxNode(Node<NODETYPE> * currentNode); 
};

#endif		// LISTA