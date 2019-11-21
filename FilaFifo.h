// Codigo usando como referência o livro [Deitel, C++ how to program] capítulo 21 "Estruturas de dados"
#ifndef FILAFIFO
#define FILAFIFO

#include "Lista.h"

// Derivada de forma privada para que os objetos não consigam accessar os outros métodos, não usados, da classe Lista [Deitel pg.818]
template<typename QUEUETYPE>
class FilaFifo : private Lista<QUEUETYPE> {

    public:
        void enqueue(QUEUETYPE newData);
        //bool dequeue(QUEUETYPE &actualData);
        QUEUETYPE dequeue();
        bool isQueueEmpty();
        void printQueue();
};

#endif		// FILAFIFO