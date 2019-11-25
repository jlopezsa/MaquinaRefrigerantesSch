// Codigo desenvolvido usando como referência o código do professor Eduardo Bezerra.
// http://gse.ufsc.br/bezerra/disciplinas/cpp/material/EstruturasDados/LinkedLista/ListaaInteiros_Nodo_em_ClasseSeparada/Lista.cpp

/*
   File Lista.cpp

   Class Lista stores Nodes (class Node) in a linked Lista.
   
   This file has the implementation for class Lista

   Class Lista is definition for a linked Lista, having the following operations:

   1. Initialize the Lista to an empty Lista.
   2. Free the nodes of a Lista.
   3. Determine whether a Lista is empty.
   4. Add a node with a given value into the Lista following
      the first node with another given value.
   5. Add a node with a given value to the front of the Lista.
   6. Add a node with a given value to the end of the Lista.
   7. Delete the first node from the Lista.

   Eduardo Augusto Bezerra <eduardo.bezerra@ufsc.br>
   Departamento de Engenharia Eletrica

   Data da criacao: Abril de 2006.
   Data da ultima alteracao: 8 de outubro de 2015.

*/

#include "Lista.h"

template <typename NODETYPE>
Lista<NODETYPE>::Lista()
{
   head = 0;
   last = 0;
}

template <typename NODETYPE>
Lista<NODETYPE>::~Lista()
{
   Node<NODETYPE> *cursor = head;
   while (head)
   {
      cursor = cursor->getProx();
      delete head;
      head = cursor;
   }
   head = 0; // Officially empty
}

template <typename NODETYPE>
void Lista<NODETYPE>::insertBeforeFirst(NODETYPE newData)
{
   head = new Node<NODETYPE>(newData, head);
}

template <typename NODETYPE>
void Lista<NODETYPE>::insertAfterLast(NODETYPE newData)
{
   Node<NODETYPE> *p = head;
   Node<NODETYPE> *q = head;

   if (head == 0)
      head = new Node<NODETYPE>(newData, head);
   else
   {
      while (q != 0)
      { // procurando o último nodo
         p = q;
         q = p->getProx();
      }
      p->setProx(new Node<NODETYPE>(newData, 0));
   }
}

template <typename NODETYPE>
NODETYPE Lista<NODETYPE>::readFirst()
{
   return head->getData();
}

template <typename NODETYPE>
NODETYPE Lista<NODETYPE>::removeFirst()
{
   NODETYPE retval = {0};
   if (head != 0)
   {
      //cout << "Removendo: " << head << endl;
      //cout << "e fica:" << head->getData() << endl;
      retval = head->getData();
      Node<NODETYPE> *oldHead = head;
      head = head->getProx();
      delete oldHead;
   }
   return retval;
}

template <typename NODETYPE>
bool Lista<NODETYPE>::isEmpty()
{
   return head == 0; // TRUE: if vazia, else FALSE
}

template <typename NODETYPE>
void Lista<NODETYPE>::insertionSort(NODETYPE value)
{
   Node<NODETYPE> *p = head; // head: ponteiro
   Node<NODETYPE> *q = head;

   if (head == 0) // Insere primeiro nodo
   {
      head = new Node<NODETYPE>(value, head);
      NODETYPE i;
      i = head->getData();
   }
   else
   {
      NODETYPE pint;
      NODETYPE auxint;
      pint = q->getData();
      auxint = pint;
      while ((q != 0) && (auxint.priorityID < value.priorityID))
      {
         p = q;
         q = p->getProx();
         if (q != 0)
         {
            pint = q->getData();
            auxint = pint;
         }
      }
      if (p == q)
         head = new Node<NODETYPE>(value, head);
      else
         p->setProx(new Node<NODETYPE>(value, q));
   }
}

template <typename NODETYPE>
int Lista<NODETYPE>::removeNode(NODETYPE dat)
{
   Node<NODETYPE> *p = head;
   Node<NODETYPE> *q = head;
   Node<NODETYPE> result;

   if (head == 0)
      result = 0;
   else
   {
      while ((q != 0) && (q->getVal() != dat))
      { // Error!! the addresses will always be different!
         p = q;
         q = p->getNext();
      }
      if (q != 0)
      {
         if (q == head)
         { // it is the first node
            result = q->getVal();
            head = q->getNext();
            delete q;
         }
         else
         { // the node is in the middle
            result = q->getVal();
            p->setNext(q->getNext());
            delete q;
         }
      }
      else
         result = 0; // node not found!
   }

   return result;
}

template <typename NODETYPE> // Ainda não utilizada
void Lista<NODETYPE>::listAll()
{
   Node<NODETYPE> *aux = head;
   //Node<NODETYPE> outStructure;
   while (aux != 0)
   {
      //cout << aux->getData() << endl; // >>> Problema quando desejo imprimir uma estrutura
      cout << "CodRef: "<< aux->getData().codigoRefri <<"\tRefri: " << aux->getData().nomeRefri <<"\tValor: "<<aux->getData().valorRefri<< 
		"\tHora (h:m:s): "<<aux->getData().h <<":"<<aux->getData().mi<<":"<<aux->getData().s <<"-"<<(aux->getData().ampm ? " pm" : " am") <<
      "\tData (a/m/d): "<<aux->getData().a <<"/"<<aux->getData().me<<"/"<<aux->getData().d << endl;

      aux = aux->getProx();
   }
}

/*
template <typename NODETYPE>
NODETYPE Lista<NODETYPE>::getProxNode(Node<NODETYPE> * currentNode) //Pasando argumentos por referência
{  
   listNextNode = currentNode;
   //listNextNode->getProx();
   return listNextNode;//->getData();
}
*/
/* 
   if(isEmpty()){
      cout << "Vazio" << endl;
      return;
   }
   Node<NODETYPE> * auxProx = head;
   Node<NODETYPE> * auxReturn = head;

   //while (aux != 0)
   //{
      
      //cout << aux->getData() << endl;
      auxProx = aux->getProx();

   //}
};
*/