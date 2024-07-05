#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
//=================================================================
//CLOSED HASHING COM INT
//=================================================================

class Item {
    public:
        int key;
        int element;
        bool full;
        bool deleted;

        Item(){
            full = false;
            deleted = false;
        }

        void insert(int e, int k){
            key = k;
            element = e;
            full = true;
            deleted = false;
        }
        void remove(){
            full = false;
            deleted = true;
        }
        void printDois(){
            cout << key << ", " << element << "; ";
        }
};

//template<typename E, typename T>
class hashTable{
    private: 
        //coisas
        int m;
        int cnt;
        Item* H;
        int* Perm;
        int hashFunc(int key) { 
            int temp = (int) floor((((double) key) / ((double) m))); 
            return (key - (m * temp)); 
        }
        int findChave(int k){
            int valor = -1; 
            int newPos = -1; 
            int i = hashFunc(k); 
            if(H[i].full && H[i].key == k) 
                valor = H[i].element; 
            else 
                for(int j=1; j<m && valor == -1; j++){ 
                    int set = Perm[j-1]; 
                    newPos = (i + set) % m; 
                    if(H[newPos].key == k && H[newPos].full){ 
                        valor = H[newPos].element; 
                    } 
                } 
            return newPos; 
        } 
        void inserirDireto(int pos, int e, int k){ 
            H[pos].element = e; 
            H[pos].key = k; 
            H[pos].full = true; 
            H[pos].deleted = false; 
        } 
    public: 
        //constructor
        hashTable(int size): m(size) { 
            m = size; 
            cnt = 0; 
            H = new Item[size]; 
            for(int i=0; i<size; i++){ 
                H[i].key = 0; 
                H[i].element = 0; 
                H[i].deleted = false; 
                H[i].full = false; 
            } 
            Perm = new int[size]; 
        } 
        ~hashTable(){ 
            clear(); 
            delete[] H; 
            delete[] Perm; 
        }
        // 
        
        // 
        void perm(int* p){
            for(int i=1; i<m; i++)
                Perm[i] = p[i];
        }
        void printPerm(){
            for(int i=1; i<m; i++){
                cout << Perm[i] << " ";
            }
            cout << "\n";
        }

        void clear(){
            delete[] this->H;
            H = new Item[this->m];
        }

        int findElemento(int  k){ //tem algo de errado aqui
            int valor = -1;
            int i = hashFunc(k);
            
            //cout << endl << i << endl; 
            
            int newPos = -1; 
            if( H[i].key == k ){
                valor = H[i].element;
            }  
            else if( H[i].deleted ){ 
                int i=0; 
                do{ 
                    i++; 
                    int offset = this->Perm[i-1]; 
                    newPos = (i + offset) % m; 
                } while( H[newPos].full && i!=m ); 
                i = newPos; 

                //cout << endl << i << endl; 

                valor = H[i].element; 
            }
            else if( H[i].full ){
                valor = H[i].element;
            }
            return valor; 
        }
        void insert(int k, int e){ 
            if((size()<this->m) && (findElemento(k) == -1)){ 
                int hashpos = hashFunc(k); 
                int newPos; 
                //cout << endl << hashpos << endl; 
                if( H[hashpos].full ){ 
                    int i=0; 
                    do{ 
                        i++; 
                        int offset = this->Perm[i-1]; 
                        newPos = abs((hashpos + offset)) % m; 
                    } while(H[newPos].full && i!=m); 
                    hashpos = newPos; 
                } 
                //cout << endl << hashpos << endl; 
                this->inserirDireto(hashpos, e, k); 
                this->cnt++; 
            } 
        } 
        int remove(int k){ 
            if(cnt==0 || findChave(k) == -1){ return int(); }
            int pos = hashFunc(k);
            if(H[pos].full){
                H[pos].key = 444;
                H[pos].element = 404;
                H[pos].full = false;
                H[pos].deleted = true;
            }
        }
        int* getKeys(int* keys){
            for(int i=0; i<m; i++){
                keys[i] = H[i].key;
            }
            return keys;
        }
        int size(){
            return cnt;
        }

        //outros
        void printarDicionario(){
            for(int i=0; i<m; i++){
                H[i].printDois();
            }
            cout << endl;
            //cout << endl << size() << endl;
        }
};

//-----------------------------------------------------------------

void usarHash_INT(){ 
    string entrada; 
    int valor, chave; 

    int m; cin>>m; 
    if(m>0){ 
        hashTable Tabela(m); 
        int perm[m]; 
        for(int i=1; i<m; i++) 
            cin >> perm[i]; 
        Tabela.perm(perm); 
        Tabela.printPerm(); 

        int t; cin>>t; 
        while(t>0){ 
            cin >> entrada; 

            if(entrada == "add"){ 
                cin >> chave >> valor; 
                Tabela.insert(chave, valor); 
            } 
            else if(entrada == "find"){ 
                cin >> chave; 
                valor = Tabela.findElemento(chave); 
                cout << valor << endl; 
            } 
            Tabela.printarDicionario(); 
            t--; 
        } 
    } 
}

/* VALORES DE ENTRADA
7
3 4 1 6 2 5
19
add 10 5
add -7 -3
add 3 1
add -5 -2
add 5 2
add -8 -4
find 10
find -7
find 3
find -5
find 5
find -8
find 100
add 100 50
find 100
add 10 6
find 10
add 200 100
find 200
0

*/

//=================================================================
//CLOSED HASHING COM STRING
//=================================================================

#include<B1_Listas/list.cpp>

//template<typename E, typename T>
class DicionaryHashTable{
    public:
        //coisas
        int m;
        int cnt;
        linkedList<string>* H;
        int* Perm;
        string /*T ou E*/ deleted;

        //constructor
        DicionaryHashTable(int size): m(size) {
            m = size;
            cnt = 0;
            H = new linkedList<string>[size];
            for(int i=0; i<size; i++)
                H[i].insert_dois("nada", "*");
            Perm = new int[size];
            deleted = "**";
        }
        ~DicionaryHashTable(){
            clear();
            delete[] H;
            delete[] Perm;
        }
        //
        int hashFunc(string/*T*/ key){
            //soma dos valores da string
            int soma=0; 
            for(int i=0; i<=11; i++){
                const char p[] = {key[i]};
                soma += atoi(p);
            }
            return soma; 
        }
        //
        void perm(int* p){
            for(int i=0; i<m; i++)
                Perm[i] = p[i];
        }

        void clear(){
            for(int i=0; i<m; i++){
                H[i].clear();
                H[i].insert_dois("nada", "*");
            }
        }
        void insert(string/*T*/ k, string/*E*/ e){
            if(cnt < m && find(k) == "nao"){
                int pos = hashFunc(k);
                if(H[pos].getKey() != "*" && H[pos].getValue() != deleted){
                    int newPos=0;
                    int i=0;
                    do{
                        i++; 
                        int offset = Perm[i-1];
                        newPos = (pos + offset) % m; ////obsssss
                        if(newPos<0) newPos += m;
                    }while(!(H[newPos].getKey() == "*" || H[newPos].getValue() == deleted));
                }
                linkedList<string/*T ou E*/> entry; entry.insert_dois(e,k);
                H[pos] = entry;
                cnt++;
            }
        }
        string /*E*/ remove(string/*T*/ k){
            if(cnt==0 || find(k) == "nada"){
                cout << "Nothing here\n";
                return string() /*E()*/;
            }
            int pos = hashFunc(k);
            H[pos].clear();
            H[pos].insert_dois("nada", deleted);
        }
        string* /*T*/ getKeys(){
            string keys[m];
            for(int i=0; i<m; i++){
                keys[i] = H[i].getKey();
            }
            return keys;
        }
        string /*E*/ find(string /*T*/ k){
            string found = "nao";
            for(int i=0; i<m; i++){
                if(H[i].getKey() == k){
                    found = H[i].getValue();
                }
            }
            return found;
        }
        int size(){
            return cnt;
        }

        //outros
        void printarDicionario(){
            int i=0;
            cout << "Dicio\n" ;
            for(i=0; i<m; i++)
                H[i].printLista();
        }
};

//---------------------------------------------------------

void usarHash_STRING() {
    cout << "Quantidade: ";
    int n=0; cin >> n;
    DicionaryHashTable Tabela(n);
    int valor[n]; 
    cout << "Valores Perm: ";
    for(int i=0; i<n; i++){
        cin >> valor[i];
    }
    Tabela.perm(valor);
    string entrada;
    string nome, cpf;
    string check;

    cout << "Testes: ";
    int c; cin >> c;
    while(c>0){
        cout << "Escolha: ";
        cin >> entrada;
        if(entrada == "add"){
            cout << "Nome e CPF: ";
            cin >> nome >> cpf;
            check = Tabela.find(cpf);
            if(check == "nao"){
                Tabela.insert(cpf, nome);
                cout << "Inserido\n";
            }
        }
        else if(entrada == "find"){
            cout << "CPF: ";
            cin >> cpf;
            check = Tabela.find(cpf);
            if(check == "nao")
                cout << -1 << endl;
            else
                cout << check << endl;
        }
        else 
            cout << "Inválido\n";

        Tabela.printarDicionario();
        c--;
    }

    Tabela.clear();

}

//==================================================================
