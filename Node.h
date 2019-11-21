// Codigo usando como referência o livro [Deitel, C++ how to program] capítulo 21 "Estruturas de dados"
// Definição de "função membro const": https://docs.microsoft.com/pt-br/cpp/cpp/const-cpp?view=vs-2019
#ifndef NODE
#define NODE

// Declaração anticipada da classe Lista
template<typename NODETYPE> class Lista;

// Classe auto-referencial: Contem um membro ponteiro que aponta para um objeto de classe do mesmo tipo
template<typename NODETYPE>
class Node {

        friend class Lista<NODETYPE>;

        NODETYPE data; // valor que será armazenado. Valor do tipo NODETYPE
        Node<NODETYPE> *nextNode; // ponteiro para outro objeto do mesmo tipo        
    public:
        Node(NODETYPE data, Node<NODETYPE> *nxt);
        //-- manipula dados
        void setData(NODETYPE); // manipula dado do nodo
        NODETYPE getData() const; // retorna dados do nodo. const palavra-chave especifica que a função é uma função de "somente leitura" que não modifica o objeto para o qual ele é chamado.
        //-- manipula ponteiro
        void setProx(Node<NODETYPE> *nxt); // manipula o ponteiro
        Node<NODETYPE> *getProx(); // manipula o ponteiro
};

#endif		// NODO