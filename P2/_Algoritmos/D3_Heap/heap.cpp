#include <iostream>

//=======================================================================
//heap maxima
void heapBottonUp(int H[], int n){
    for(int i = n/2; i>=1; i--){
        int k = i; 
        int v = H[k];
        bool heap = false;
        while(!heap && 2*k<=n){
            int j = 2*k;
            if(j<n)
                if(H[j] < H[j+1]) 
                    j = j+1;
            if(v>=H[j])
                heap = true;
            else{
                H[k] = H[j]; 
                k = j;
            }
            H[k] = v;
        }
    }
}
//heap maxima
void heapTopDown(int H[], int n) {
    if(n/2 >= 1){
        int k = 1;
        long int v = H[k];
        bool heap = false;
        while(!heap && 2*k <= n){
            int j = 2*k;
            if(j < n)
                if(H[j] < H[j+1])
                    j = j+1;
            if(v >= H[j])
                heap = true;
            else{
                H[k] = H[j];
                k = j;
            }
            H[k] = v;
        }
    }
}

//=======================================================================
//heap minima botton up
class heap{
private:
    int size, cnt;
    long int* vetor;
    //heapfyUm-----------------------------------------------------
    void heapfyTopDown() {
        if(this->cnt/2 >= 1){
            int k = 1;
            long int v = vetor[k];
            bool heap = false;
            while(!heap && 2*k <= this->cnt){
                int j = 2*k;
                if(j < this->cnt)
                    if(vetor[j] > vetor[j+1])
                        j = j+1;
                if(v <= vetor[j])
                    heap = true;
                else{
                    vetor[k] = vetor[j];
                    k = j;
                }
                vetor[k] = v;
            }
        }
    }
public:
    heap(int tam){
        size = tam;
        vetor = new long int[tam+1];
        cnt = 0;
    }
    ~heap(){
        delete[] vetor;
    }
    //operacoes------------------------------------------------------
    void inserir(int value){
        if(size == cnt) return;

        cnt++;
        vetor[cnt] = value;
    }
    long int remover(){
        if(cnt == 0) return 0;

        long int sub = vetor[1];
        vetor[1] = vetor[cnt];
        vetor[cnt] = sub;

//        printarTudo();

        cnt--;
        heapfyTopDown();

        return sub;
    }
    //heapfyDois-----------------------------------------------------
    void heapfyBottonUp(){
        for(int i = cnt/2; i >= 1; i--){
            int k = i;
            long int v = vetor[k];
            bool heap = false;
            while(!heap && 2*k <= cnt){
                int j = 2*k;
                if(j<cnt)
                    if(vetor[j] > vetor[j+1])
                        j = j+1;
                if(v <= vetor[j])
                    heap = true;
                else{
                    vetor[k] = vetor[j];
                    k = j;
                }
                vetor[k] = v;
            }
        }
    }
    //print----------------------------------------------------------
   void printarTudo(){
       for(int i=1; i<=cnt; i++){
           std::cout << vetor[i] << "\n";
       }
       std::cout << std::endl;
   }
    
};
