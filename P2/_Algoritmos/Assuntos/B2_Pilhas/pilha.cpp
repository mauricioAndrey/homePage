#include <iostream>
using namespace std;

//==================================================================

//linkedStack
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

template<typename E> class Stack {
private:
    Node<E>* head;
    int size;
public:
    Stack(){
        head = new Node<E>;
        head->next = nullptr;
        size=0;
    }
    ~Stack() {
        clear();
        delete head;
    }

    void clear(){
        Node<E>* temp = head->next;
        while(temp != nullptr){
            Node<E>* removed = temp;
            temp = temp->next;
            delete removed;
        }
        head->next = nullptr;
        size=0;
    }
    void push(E item){
        Node<E>* newNode = new Node<E>(item);
        //newNode->element = item;
        newNode->next = head;
        head = newNode;
        size++;
    }
    void pop() {
        if(head == nullptr) return;
        Node<E>* temp = head;
        head = head->next;
        delete temp;
        size--;
    }
    E top() {
        if(head != nullptr)
            return head->element;
        return E();
    }
    int length() { return size; }

    void printStack() {
        cout << "Stack Linkada\n<";
        Node<E>* temp = head;
        for(int i=0; i < length()-1 ; i++, temp = temp->next){
            cout << temp->element << ", ";
        }
        cout << temp->element << ">\n";
    }
};

//--------------------------------------------------------------------

void usarPilhaLinkada(){
    int escolha = 0;
    Stack<int> pilha;
    int elemento;
    cout << "Pilha\n";
    cout << "1.Limpar\n2.Inserir\n3.Remover\n4.Tamanho\n5.Topo\n6.Printar Tudo\n7.Sair\n";
    do{
        cout << "Escolha:";
        cin >> escolha;
        switch (escolha) {
            case 1:
                pilha.clear();
                break;
            case 2:
                cout << "Digite um elemento:";
                cin >> elemento;
                pilha.push(elemento);
                break;
            case 3:
                pilha.pop();
                break;
            case 4:
                cout << pilha.length() << "\n";
                break;
            case 5:
                cout << pilha.top() << "\n";
                break;
            case 6:
                pilha.printStack();
                break;
            case 7:
                cout << "Saindo...\n";
                break;
        }
    }while(escolha != 7);
}

//==================================================================
