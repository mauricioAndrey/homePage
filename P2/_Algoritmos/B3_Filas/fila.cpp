#include <iostream>
using namespace std;

//====================================================================

//linkedList
template <typename E>
struct Node {
public:
    E element;
    Node<E>*next;
    Node(){
        element = 0;
        next = nullptr;
    }
    Node(int eleval){
        element = eleval;
        next = nullptr;
    }
    Node(E& elemval, Node ne){
        element = elemval;
        next = ne;
    }
};

template<typename E> class queue_ {
private:
    Node<E>* front;
    Node<E>* rear;
    int size;
public:
    queue_(){
        front = new Node<E>;
        front->next = nullptr;
        rear = front;
        size=0;
    }
    ~queue_() {
        clear();
        delete front;
    }

    void clear(){
        Node<E>* temp = front->next;
        while(temp != nullptr){
            Node<E>* removed = temp;
            temp = temp->next;
            delete removed;
        }
        front->next = nullptr;
        size=0;
    }

    void enqueue(E item){
        Node<E>* newNode = new Node<E>(item);
        //newNode->element = item;
        newNode->next = rear->next;
        rear->next = newNode;
        rear = rear->next;
        size++;
    }
    E dequeue() {
        if(front->next == nullptr) { return E(); }
        E removedItem = front->next->element;
        Node<E>* temp = front->next;

        if(rear == front->next) { rear = front; }
        front->next = front->next->next;
        delete temp;
        size--;
        return removedItem;
    }
    E frontValue() {
        if(front->next != nullptr)
            return front->next->element;
        return E();
    }

    int length() { return size; }

    void printFila() {
        if(length() == 0) return;
        cout << "Fila Linkada\n<";
        Node<E>* temp = front->next;
        for(int i=0; i < length()-1 ; i++, temp = temp->next){
            cout << temp->element << ", ";
        }
        cout << temp->element << ">\n";
    }
};

//--------------------------------------------------------------------

void usarFilaLinkada(){
    int escolha = 0;
    queue_<int> fila;
    int elemento;
    cout << "Fila Linkada\n";
    cout << "1.Limpar\n2.Colocar\n3.Tirar\n4.PrimeiroValor\n5.Tamanho\n6.PrintarFila\n7.Sair\n";
    do{
        cout << "Escolha:";
        cin >> escolha;
        switch (escolha) {
            case 1:
                fila.clear();
                break;
            case 2:
                cout << "Digite um elemento:";
                cin >> elemento;
                fila.enqueue(elemento);
                break;
            case 3:
                elemento = fila.dequeue();
                cout << "Elemento Retirado: " << elemento << "\n";
                break;
            case 4:
                if(fila.length() != 0)
                    cout << fila.frontValue() << "\n";
                break;
            case 5:
                cout << fila.length() << "\n";
                break;
            case 6:
                fila.printFila();
                break;
            case 7:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Escolha Invalida\n";
        }
    }while(escolha != 7);

}

//====================================================================
