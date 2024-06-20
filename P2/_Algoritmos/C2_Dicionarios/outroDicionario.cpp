#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Item {
public:
    int key;
    int element;
    bool full;
    bool deleted;

    Item(){
        key = 0;
        element = 0;
        full = false;
        deleted = false;
    }
    Item(int k, int e){
        key = k;
        element = e;
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

template<typename E, typename  Key> 
class Dicio {
private:
    int m;
    int cnt;
    vector<Item> H;
    vector<int> Perm;
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
    Dicio(int size){
        m = size;
        cnt = 0;
        H.resize(m);
        Perm.resize(m);
    }
    ~Dicio() { }
    void perm(vector<int> p){
        for(int i=1; i<m; i++)
            Perm[i] = p[i];
    }
    void clear(){
        H.resize(m, Item(0,0));
        Perm.resize(m, 0);
        m=0;
    }
    void insert(E item, Key k){
        if(find(k) != E()) return;
        int pos = hash(k);
        int l = lista[pos];
        lista.push_back(make_pair(item, k));
        m++;
    }
    E remove(Key k) {
        if(m == 0) { return E(); }
        E removedItem = E();
        bool finded = false;
        auto it = lista.begin();
        for (; it!=lista.end() && !finded; it++){
            if(it->second ==  k){
                removedItem = it->first;
                finded = true;
            }
        }
        lista.erase(it);
        m--;
        return removedItem;
    }
    E getKeys() {
        if(m == 0) return E();
        return E();
    }

    E find(Key k){
        if(m == 0) { return E(); }
        E findItem = E();
        bool finded = false;
        auto it = lista.begin();
        for (; it!=lista.end() && !finded; it++){
            if(it->second ==  k){
                findItem = it->first;
                finded = true;
            }
        }
        return findItem;
    }

    int length() { return m; }

    void printDicio() {
        cout << "Lista Linkada\n< ";
        int i=0;
        auto it = lista.begin();
        for(; it!= lista.end()-1; it++){
            cout << "(" << it.first << ", " << it.second << "), ";
            i++;
        }
        cout << "(" << it.first << ", " << it.second << ") >\n";
    }

};
