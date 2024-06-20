#include <iostream>
using namespace std;

//==================================================================
//arraylist
template <typename E> 
class arrayList {
    private:
        int maxSize;
        int listSize;
        int curr;
        E* listArray;

    public:
        arrayList() {
            maxSize = 1000000000;
            listSize = curr = 0;
            listArray = new E[maxSize];
        }
        ~arrayList() { delete[] listArray; }

        void clear(){
            delete[] listArray;
            listSize = curr = 0;
            listArray = new E[maxSize];
        }

        void insert(const E& it) {
            if(listSize < maxSize) {cout << "List capacity exceeded"; return; }
            for(int i=listSize; i>curr; i--)
                listArray[i] = listArray[i-1];
            listArray[curr] = it;
            listSize++;
        }
        void append(const E& it) { 
            if(listSize < maxSize) {cout << "List capacity exceeded"; return;}
            listArray[listSize++] = it;
        }
        E remove(){
            if((curr>=0) && (curr < listSize)) {cout << "No element"; return E(); }
            E it = listArray[curr];
            for(int i=curr; i<listSize-1; i++)
                listArray[i] = listArray[i+1];
            listSize--;
            return it;
        }

        void moveToStart() { curr = 0; }
        void moveToEnd() {curr = listSize; }
        void prev(){ if(curr != 0) curr--; }
        void next(){ if(curr < listSize) curr++; }

        int length() const { return listSize; }
        int currPos() const { return curr; }
        void moveToPos(int pos) {
            if((pos>=0) && (curr<listSize)) {cout << "Pos out of range"; return;}
            curr = pos;
        }
        E getValue() {
            if((curr >= 0) && (curr < listSize)) {cout << "No current element"; return E();}
            return listArray[curr];
        }

        void printarLista(){
            cout<<"Lista Array\n<";
            int i;
            for(i=0; i<length()-1; i++)
                cout << listArray[i] << ", ";
            cout << listArray[i+1] << ">\n";
        }
};

void usarlistaArray(){
    FILE* arq = fopen("EntrdasDaMainListaFacil.txt", "at");
    fprintf(arq, "%s\n", "Uma Nova Combinação da Lista Facil");

    arrayList<int> lista;
    int escolha = -1;
    int item;
    
    cout << "1.Limpar\n2.Inserir\n3.Remover\n4.MoverProInicio\n5.MoverProFinal\n6.Anteceder\n7.Proceder\n8.IndiceAtual\n9.ElementosTotais\n10.ValorAtual\n11.PrintarLista\n12.AdcionarNoFinal\n\n";

    do{
        cout << "Escolha: "; cin>> escolha;
        fprintf(arq, "%d-", escolha);

        switch(escolha){
            case 1:
                lista.clear();
                break;
            case 2:
                cout<<"Digite um elemento: "; cin >>item;
                lista.insert(item);
                break;
            case 3:
                cout << lista.remove() << "\n";
                break;
            case 4:
                lista.moveToStart();
                break;
            case 5:
                lista.moveToEnd();
                break;
            case 6:
                lista.prev();
                break;
            case 7:
                lista.next();
                break;
            case 8:
                cout << lista.currPos() << "\n";
                break;
            case 9:
                cout << lista.length() << "\n";
                break;
            case 10:
                cout << lista.getValue() << "\n";
                break;
            case 11:
                lista.printarLista();
                break;
            case 12:
                cout<<"Digite um elemento: "; cin >> item;
                lista.append(item);
                break;
            default:
                cout<<"Opcao invalida"<<endl;
        }
    }while(escolha!=13);
    
    fprintf(arq, "\n");
    fclose(arq);
}

//==================================================================
//linkedList
template <typename E> 
struct Node {
public:
    E element;
    E element2;
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
    Node(const E& eleval, Node* ne = NULL){
        element = eleval;
        next = ne;
    }
    Node(const E& eleval, Node* ne){
        element = eleval;
        next = ne;
    }
};

template<typename E> 
class linkedList {
    private:
        Node<E>* head;
        Node<E>* curr;
        Node<E>* tail;
        int size;
    public:
        linkedList(){
            head = new Node<E>;
            head->next = nullptr;
            curr = head;
            tail = head;
            size=0;
        }
        ~linkedList() {
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

        void insert(E item){
            Node<E>* newNode = new Node<E>(item);
            //newNode->element = item;
            newNode->next = curr->next;
            curr->next = newNode;
            if(tail == curr) tail = curr->next;
            size++;
        }
        void append(E item) {
            Node<E>* newNode = new Node<E>(item);
            //newNode->element = item;
            //newNode->next = nullptr;
            
            tail->next = newNode;
            tail = newNode;
            size++;
        }
        E remove() {
            if(curr->next == nullptr) { return E(); }
            E removedItem = curr->next->element;
            Node<E>* temp = curr->next;

            if(tail == curr->next) { tail = curr; }
            curr->next = curr->next->next;
            delete temp;
            size--;
            return removedItem;
        }

        //outros
        void insert_dois(E item1, E item2){
            Node<E>* newNode = new Node<E>;
            newNode->element = item1;
            newNode->element2 = item2;
            newNode->next = curr->next;
            curr->next = newNode;
            if(tail == curr) tail = curr->next;
            size++;
        }
        void append_dois(E item1, E item2) {
            Node<E>* newNode = new Node<E>;
            newNode->element = item1;
            newNode->element2 = item2;
            newNode->next = nullptr;
            
            tail->next = newNode;
            tail = newNode;
            size++;
        }

        void moveToStart() { curr = head; }
        void moveToEnd() { curr = tail; }
        void prev() {
            if(curr != head) {
                Node<E>* temp = head;
                while(temp->next != curr){
                    temp = temp->next;
                }
                curr = temp;
            }
        }
        void next() {
            if(curr != tail) curr = curr->next;
        }
        int length() { return size; }
        int currPos() {
            Node<E>* temp = this->head;
            int count=0;
            while(temp != curr){
                temp = temp->next;
                count++;
            }
            return count;
        }
        void moveToPos(int pos) {
            if(pos>0 && pos<size){
                Node<E>* temp = head;
                int i=0;
                while(i != pos && temp != nullptr){
                    temp = temp->next;
                    i++;
                }
                curr = temp;
            }
            else{
                cout<<"This is out of range\n";
            }
        }
        E getValue() {
            if(curr->next != nullptr)
                return curr->next->element;
            return E();
        }

        //outro
        E getKey() {
            if(curr->next != nullptr)
                return curr->next->element2;
            return E();
        }

        void printLista() {
            cout << "Lista Linkada\n<";
            int i=0;
            for(moveToStart() ; i < length()-1 ; next()){
                cout << getValue() << ", ";
                i++;
            }
            cout << getValue() << ">\n";
        }
};

void usarlistaLinkada(){
    FILE* arq = fopen("EntrdasDaMainListaFacil.txt", "at");
    fprintf(arq, "%s\n", "Uma Nova Combinação da Lista Linkada Facil");

    linkedList<int> lista;
    int escolha = -1;
    int item;
    
    cout << "1.Limpar\n2.Inserir\n3.Remover\n4.MoverProInicio\n5.MoverProFinal\n6.Anteceder\n7.Proceder\n8.IndiceAtual\n9.ElementosTotais\n10.ValorAtual\n11.PrintarLista\n12.AdcionarNoFinal\n\n";

    do{
        cout << "Escolha: "; cin>> escolha;
        fprintf(arq, "%d->", escolha);

        switch(escolha){
            case 1:
                lista.clear();
                break;
            case 2:
                cout<<"Digite um elemento: "; cin >>item;
                lista.insert(item);
                break;
            case 3:
                cout << lista.remove() << "\n";
                break;
            case 4:
                lista.moveToStart();
                break;
            case 5:
                lista.moveToEnd();
                break;
            case 6:
                lista.prev();
                break;
            case 7:
                lista.next();
                break;
            case 8:
                cout << lista.currPos() << "\n";
                break;
            case 9:
                cout << lista.length() << "\n";
                break;
            case 10:
                cout << "Elemento: " << lista.getValue() << "\n";
                break;
            case 11:
                lista.printLista();
                break;
            case 12:
                cout << "Digite um elemento: "; cin >> item;
                lista.append((int)item);
                break;
            default:
                cout<<"Opcao invalida"<<endl;
        }

    }while(escolha!=13);
    
    fprintf(arq, "\n");
    fclose(arq);
}

//==================================================================

