// Codigo desenvolvido usando como referência o código do professor Eduardo Bezerra.
// http://gse.ufsc.br/bezerra/disciplinas/cpp/material/EstruturasDados/LinkedList/ListaInteiros_Nodo_em_ClasseSeparada/List.h

#ifndef LISTA
#define LISTA

#include "Node.cpp"


template<typename NODETYPE>
class Lista{ 

  Node<NODETYPE> * head;
  //Node<NODETYPE> * listNextNode;

public:
  Lista();
  ~Lista();
  void insertBeforeFirst(NODETYPE newData);
  void insertAfterLast(NODETYPE newData);
  NODETYPE readFirst();
  NODETYPE removeFirst();
  bool isEmpty();
  //void insertionSort(int value);
  //int removeNode(int dat);
  void listAll();
  //NODETYPE getProxNode(Node<NODETYPE> * currentNode); 
};

#endif		// LISTA