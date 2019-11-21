// Codigo usando como referência o livro [Deitel, C++ how to program] capítulo 21 "Estruturas de dados"

#include "FilaFifo.h"
#include "Lista.cpp"

template<typename QUEUETYPE>
void FilaFifo<QUEUETYPE>::enqueue(QUEUETYPE newData){
    //this->insertBeforeFirst(newData);
    this->insertAfterLast(newData);
};

template<typename QUEUETYPE>
QUEUETYPE FilaFifo<QUEUETYPE>::dequeue(){
//bool FilaFifo<QUEUETYPE>::dequeue(QUEUETYPE &actualData){
    QUEUETYPE retorno;
    retorno = this->removeFirst();
    return  retorno;
};


template<typename QUEUETYPE>
bool FilaFifo<QUEUETYPE>::isQueueEmpty(){
    return this->isEmpty();   
};

template<typename QUEUETYPE>
void FilaFifo<QUEUETYPE>::printQueue(){
    this->listAll();
};
