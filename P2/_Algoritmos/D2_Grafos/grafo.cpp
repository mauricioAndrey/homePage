#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define INT_MAX 2147483647 
#define INFINY 2147483647
#define UNVISITED false
#define VISITED true

//========================================================================

class graphMatrix{
private:
    int** matrix;
    int numEdge;
    bool* mark;
    int numVertices;
    stack<int> order;

    //info------------------------------------------------------------
    int n(){ return numVertices; }
    int e() { return numEdge; }
    //as edge---------------------------------------------------------
    int first(int v) {
        for(int i=0; i<n(); i++)
            if(matrix[v][i] != 0) return i;
        return n();
    }
    int next(int v, int w) {
        for(int i=w+1; i< n(); i++)
            if(matrix[v][i] != 0) return i;
        return n();
    }
    //vetor mark------------------------------------------------------
    void setMark(int v, bool val) {
        mark[v] = val;
    }
    bool getMark(int v) {
        return mark[v];
    }
    //travessias------------------------------------------------------
    void DFS(int v){
        preVisit(v);
        setMark(v, VISITED);
        int w = first(v);
        while(w < n()){
            if(getMark(w) == UNVISITED)
                DFS(w);
            w = next(v, w);
        }
        posVisit(v);
    }
    void toposort_DFS(int v){
        setMark(v, VISITED);
        int w = first(v);
        while(w<n()){
            if(getMark(w) == UNVISITED)
                toposort_DFS(w);
            w = next(v, w);
        }
        order.push(v);
    }
    void BFS(int start){
        queue<int> q;
        q.push(start);
        setMark(start, VISITED);
        while(q.size() > 0){
            int v = q.front(); q.pop();
            preVisit(v);
            int w = first(v);
            while(w<n()){
                if(getMark(w) == UNVISITED){
                    setMark(w, VISITED);
                    q.push(w);
                }
                w = next(v, w);
            }
            posVisit(v);
        }
    }
    //visitas---------------------------------------------------------
    void preVisit(int v) {
        cout << v << " ";
    }
    void posVisit(int v) {
        //cout << endl;
    }

public:
    graphMatrix(int size){
        numVertices = size;
        numEdge = 0;
        matrix = new int*[numVertices];
        mark = new bool[size];
        for(int i=0; i<numVertices; i++) {
            matrix[i] = new int[numVertices];
            for (int j = 0; j < numVertices; j++)
                matrix[i][j] = 0;
        }
    }
    ~graphMatrix(){
        for(int i=0; i<numVertices; i++) delete[] matrix[i];
        delete[] matrix;
        delete[] mark;
    }

    //arestas---------------------------------------------------------
    void setEdge(int i, int j, int wt){
        if(wt == 0) { return; }
        if(matrix[i][j] == 0) numEdge+=2;
        //grafo nao dirigido e nao ponderado
        matrix[j][i] = wt;
        matrix[i][j] = wt;
    }
    void delEdge(int i, int j) {
        if(matrix[i][j] != 0) numEdge-=2;
        matrix[j][i] = 0;
        matrix[i][j] = 0;
    }
    bool isEdge(int i, int j){
        if(matrix[i][j] == 1) return true;
        return false;
    }
    int weight(int i, int j) {
        //if(i<n() && i>=0 && j<n() && j>=0)
        return matrix[i][j];
        //return 0;
    }
    //visitar---------------------------------------------------------
    void traverseDFS(int start){
        //if(start >= n() || start < 0) return;
        for(int v = 0; v < n(); v++)
            setMark(v, UNVISITED);
        for(int v = start; v < n(); v++)
            DFS(v);
    }
    void traverseBFS(int start){
        //if(start >= n() || start < 0) return;
        for(int v = 0; v < n(); v++)
            setMark(v, UNVISITED);
        for(int v = start; v < n(); v++)
            if(!getMark(v))
                BFS(v);
    }
    //outros----------------------------------------------------------
    void graphPrint(){
        cout << "G = \n(\n    ";
        cout << "V = { ";
        for(int i=0; i < n() - 1 ; i++)
            cout << i << ", ";
        cout << n() - 1 << " ";

        cout << "}\n     E = { ";
        for(int i=0; i < n(); i++)
            for(int j=0; j < n(); j++)
                if(matrix[i][j])
                    cout << "(" << i << ", " << j << ") " <<
                         matrix[i][j];
        cout << "}\n)\n";
    }
    void printStack(){
        for(int v = 0; v < n(); v++)
            setMark(v, UNVISITED);
        for(int v = 0; v < n(); v++)
            toposort_DFS(v);
        while (!order.empty()) {
            cout << order.top() + 1 << " ";
            order.pop();
        }
    }

};

//========================================================================

struct priority{
    int v, w, peso;

    priority(){ v=0; w=0; peso=INFINY; }
    priority(int v1, int w1, int p){ v=v1; w=w1; peso=p; }

    //ver como se comporta
    bool operator<(const priority& other) const {
        return peso > other.peso;
    }
};
struct node {
    int cone;
    int wt;
    node(){
        cone=0;
        wt=0;
    }
    node(int c, int w){
        cone = c;
        wt = w;
    }
};

class graphLista{
private:
    vector<node> *lista;
    node* predecessores;
    int* distancias;
    bool* mark;
    int numEdge;
    int numVertices;
    stack<int> order;

    //info
    int n(){ return numVertices; }
    int e() { return numEdge; }
    //vetor mark
    void setMark(int v, bool val) {
        mark[v] = val;
    }
    bool getMark(int v) {
        return mark[v];
    }
    //travessias
    void DFS(int v){
        preVisit(v);
        setMark(v, VISITED);
        for(auto it = lista[v].begin(); it!=lista[v].end(); it++) {
            int w = it->cone;
            if (getMark(w) == UNVISITED)
                DFS(w);
        }
        posVisit(v);
    }
    void toposort(int v){
        setMark(v,VISITED);
        for(auto it = lista[v].begin(); it!=lista[v].end(); it++) {
            int w = it->cone;
            if (getMark(w) == UNVISITED)
                toposort(w);
        }
        order.push(v);
    }
    void BFS(int start){
        queue<int> q;
        q.push(start);
        setMark(start, VISITED);
        while(q.size() > 0){
            int v = q.front(); q.pop();
            preVisit(v);
            for(auto it = lista[v].begin(); it != lista[v].end(); it++){
                int w = it->cone;
                if(getMark(w) == UNVISITED){
                    setMark(w, VISITED);
                    q.push(w);
                }
            }
            posVisit(v);
        }
    }
    void EncontrarPredecessores(int start){
        predecessores[start].cone = start;
        predecessores[start].wt = 0;
        setMark(start, VISITED);
        queue<int> q;
        q.push(start);
        while(!q.empty()){
            int& v = q.front(); q.pop();
            for(auto it = lista[v].begin() + 1; it!= lista[v].end(); it++){
                int& w = it->wt;
                if(getMark(w) == UNVISITED){
                    predecessores[w].cone = v; //predecessor
                    predecessores[w].wt = predecessores[v].wt + 1; //distancia
                    setMark(w, VISITED);
                    q.push(w);
                }
            }
        }
    }
    //visitas
    void preVisit(int v) {
        //cout << "Iniciando Visita no vertice " << v << "\n";
    }
    void posVisit(int v) {
        //cout << "\tFinalizada a Visita no vertice " << v << "\n";
    }
    //outros
    void printStack(){
        while (!order.empty()) {
            cout << order.top() + 1 << " ";
            order.pop();
        }
    }

public:
    graphLista(int size){
        numVertices = size;
        numEdge = 0;
        lista = new vector<node>[numVertices];
        predecessores = new node[numVertices];
        distancias = new int[numVertices];
        mark = new bool[size];
        for(int i=0; i<numVertices; i++) {
            mark[i] = false;
        }
    }
    ~graphLista(){
        delete[] lista;
        delete[] predecessores;
        delete[] distancias;
        delete[] mark;
    }

    //"inserir"---------------------------------------------------------
    void setEdge(int i, int j, int wt){
        //if(i>=n() || i<0 || j>=n() || j<0) return;
        if(wt == 0) { /*cout << "error\n"; */ return; }
        bool encontrado = false;
        node temp(j,1);
        for(auto it = lista[i].begin(); it!=lista[i].end() && !encontrado; it++)
            if((*it).cone == temp.cone)
                encontrado = true;
        if(!encontrado){
            lista[i].insert(lista[i].end(), temp);
            numEdge++;
        }

    }
    void delEdge(int i, int j) {
        bool encontrado = false;
        node temp(j,1);
        for(auto it = lista[i].begin(); it!=lista[i].end() && !encontrado; it++)
            if((*it).cone == temp.cone){
                encontrado = true;
                lista[i].erase(it);
                numEdge--;
            }
    }
    bool isEdge(int i, int j){
        for(auto it = lista[i].begin(); it != lista[i].end(); it++)
            if((*it).cone == j) return true;
        return false;
    }
    int weight(int v, int w){
        for(auto it = lista[v].begin(); it != lista[v].end(); it++)
            if((*it).cone == w) return it->wt;
        return 0;
    }
    //visitar-----------------------------------------------------------
    void traversia(string tal){
        for(int v = 0; v < n(); v++)
            setMark(v, false);
        if(tal == "BFS")
            for(int v = 0; v < n(); v++)
                if(!getMark(v))
                    BFS(v);
        if(tal == "DFS")
            for(int v = 0; v < n(); v++)
                if(!getMark(v))
                    DFS(v);
    }
    //------------------------------------------------------------------
    //fazer para matriz também
    void Dijkstra(int s){
        for(int i=0; i<n(); i++){
            distancias[i] = INFINY;
            predecessores[i].cone = -1;
            setMark(i, UNVISITED);
        }
        priority_queue<priority> H;
        H.push(priority(s,s,0));
        distancias[s] = 0;
        for(int i=0; i<n(); i++){
            priority temp;
            do{
                //pode dar problema
                if(!H.empty()) {
                    temp = H.top();
                    H.pop();
                }
                if(temp.v == 0 && temp.w == 0 && temp.peso == INFINY && H.empty()) return;
            } while(getMark(temp.v) != UNVISITED);
            setMark(temp.v, VISITED); predecessores[temp.v].cone = temp.w;
            for(auto it = lista[temp.v].begin(); it!=lista[temp.v].end(); it++){
                int w = it->cone;
                if(getMark(w) != VISITED && distancias[w] > distancias[temp.v] + weight(temp.v,w)) {
                    distancias[w] = distancias[temp.v] + weight(temp.v, w);
                    H.push(priority(temp.v, w, distancias[w]));
                }
            }
        }
    }
    void Floyd_Warshall(int** D){
        for(int i=0; i< n(); i++)
            for(int j=0; j<n(); j++){
                if(i=j) D[i][j] = 0;
                else if(weight(i, j) != 0) D[i][j] = weight(i, j);
                else D[i][j] = INFINY;
            }

        for(int k=0; k<n(); k++)
            for(int i=0; i<n(); i++)
                for(int j=0; j<n(); j++)
                    if(D[i][k] != INFINY && D[k][j] != INFINY && D[i][j] > D[i][k] + D[k][j])
                        D[i][j] = D[i][k] + D[k][j];
    }
    void BellmanFord(int s, int* D){
        for(int i=0; i<n(); i++) D[i] = INFINY;
        D[s] = 0;
        bool negativeCycle = false;
        for(int k=0; k<n()-1; k++)
            for(int i=0; i<n(); i++)
                for(auto it = lista[i].begin(); it!=lista[i].end(); it++){
                    int& j = it->cone;
                    if(D[j] > D[i] + weight(i, j))
                        D[j] = D[i] + weight(i, j);
                }
        for(int i=0; i<n(); i++)
            for(auto it = lista[i].begin(); it != lista[i].end(); it++){
                int j = it->cone;
                if(D[j] > D[i] + weight(i, j))
                    negativeCycle = true;
            }
    }
    void Prim(){
        for(int i=0; i<numVertices; i++){
            distancias[i] = INT_MAX;
            predecessores[i].cone = -1;
            setMark(i, UNVISITED);
        }
        priority_queue<priority> heap;
        heap.push(priority(0,0,0));
        distancias[0] = 0;
        for(int i=0; i<n(); i++){
            priority temp;
            do{
                if(heap.empty()) return;
                temp = heap.top();
                heap.pop();
            }while(getMark(temp.w) == VISITED);
            setMark(temp.w, VISITED);
            predecessores[temp.w].cone = temp.v;
            for(auto it = lista[temp.w].begin(); it!=lista[temp.w].end(); it++){
                node& w = (*it);
                if(getMark(w.cone) == UNVISITED)
                    if(distancias[w.cone] > w.wt) {
                        distancias[w.cone] = w.wt;
                        heap.push(priority(temp.w, w.cone, distancias[w.cone]));
                    }
            }
        }
    }
    //nao entendi isso
    //nem como fazer o disjoint subsets
    void Kruskal(){
        priority_queue<priority> heap;
        int edgecnt = 1;
        for(int i=0; i<n(); i++)
            for(auto it = lista[i].begin(); it!=lista[i].end(); it++){
                int& w = it->cone;
                heap.push(priority(i, w, weight(i, w)));
            }
        //HeapBottonUp(heap);
        //ds = create_disjointSubset(n(G));
        int numMST = n();
        while (numMST > 1){
            priority temp = heap.top(); heap.pop();
            if(temp.v != temp.w){//find(ds, temp.v) != find(ds, temp.w)
                //union(ds, temp.v, temp.u);
                //setEdge(G', temp.v, temp.w, temp.peso);
                numMST--;
            }
        }
    }
    //outros-------------------------------------------------------------
    void print_toposort(){
        for(int v = 0; v < n(); v++)
            setMark(v, false);
        for(int v = 0; v < n(); v++)
            if(!getMark(v))
                toposort(v);

        printStack();
    }
    void graphPrint(){
        cout << "G = \n(\n    ";
        cout << "V = { ";
        for(int i=0; i < n() - 1 ; i++)
            cout << i << ", ";
        cout << n() - 1 << " ";

        cout << "}\n     E = { ";
        for(int i=0; i < n(); i++)
            for(auto it = lista[i].begin(); it != lista[i].end(); it++)
                if((*it).cone)
                    cout << "(" << i << ", " << (*it).cone << ") "; //<< matrix[i][j]
        cout << "}\n)\n";
    }

};

//========================================================================
