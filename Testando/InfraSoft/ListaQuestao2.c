#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

pthread_barrier_t barreira;

#define N 3

struct array{
    int *arr;
    int tam;
};
struct threadThings{
    struct array *vetor;
    pthread_t thread;
    int id;
    int begin;
    int end;
};

void *funcaoThread(void *arg){
    struct threadThings info = (*(struct threadThings *) arg);
    int i=info.begin, j=info.end;
    for(int k=i; k<j && k+1<info.vetor->tam; k++){
        for(int m=k+1; m<j; m++)
            if(info.vetor->arr[m] < info.vetor->arr[m+1]){ 
                int temp = info.vetor->arr[m];
                info.vetor->arr[m] = info.vetor->arr[m+1];
                info.vetor->arr[m+1] = temp;
            }
        pthread_barrier_wait(&barreira);
    }
    
    pthread_exit(NULL);
}

int main(int argc, char* argv[]){
    //struct para as informações do array
    struct array vetor;

    scanf("%d", &vetor.tam);
    vetor.arr = (int*) malloc(sizeof(int)*vetor.tam);
    for(int i=0; i<vetor.tam; i++){
        scanf("%d", &vetor.arr[i]);
    }

    pthread_barrier_init(&barreira, NULL, vetor.tam);

    //struct que vai ser mandada para cada thread
    struct threadThings *thread = (struct threadThings*) malloc(sizeof(struct threadThings)*N);

    //variavel para indicar os indices do array
    int cont=0;
    //quantidade de elementos do array colocado em cada thread
    int quant = vetor.tam / N;

    for(int t=0; t<N; t++){
        //todas as threads apontam para a posição em que as informações do array está
        thread[t].vetor = &vetor; 
        thread[t].id = t; 
        //colocando as partes do array em cada thread
        thread[t].begin = cont;
        cont += quant;
        thread[t].end = cont;
        pthread_create(&thread[t].thread, NULL, funcaoThread, (void*) &thread[t]);
    }
    for(int t=0; t<N; t++){
        pthread_join(thread[t].thread, NULL);
    }
    pthread_barrier_destroy(&barreira);

    //thread que junta tudo

    //array ordenado
    for(int i=0; i<N; i++){
        printf("%d ", vetor.arr[i]); 
    }
    printf("\n");

    pthread_exit(NULL);
    free(thread);

}