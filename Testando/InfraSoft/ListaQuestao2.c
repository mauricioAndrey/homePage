#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 3

struct array{
    int *arr;
    int tam;
    bool sort;
};
struct threadThings{
    struct array *vetor;
    pthread_t thread;
    int id;
    int begun;
    int end;
};

void *funcaoThread(void *arg){
    struct threadThings dados = (*(struct threadThings *) arg);
    
    
}

int main(int argc, char* argv[]){
    struct array vetor;
    scanf("%d", &vetor.tam);
    vetor.arr = (int*) malloc(sizeof(int)*vetor.tam);
    for(int i=0; i<vetor.tam; i++){
        scanf("%d", &vetor.arr[i]);
    }

    struct threadThings *thread = (struct threadThings*) malloc(sizeof(struct threadThings)*N);
    int cont=0;
    for(int t=0; t<N; t++){
        thread[t].vetor = vetor;
        thread[t].id = t;
        thread[t].begin = cont; cont++;
        thread[t].end = cont; cont++;
        pthread_create(&thread[t].thread, NULL, funcaoThread, (void*) &thread[t]);
    }

}