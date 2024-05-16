#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Nthreads é o N, a quantidade de threads e a quantidade que vai particionar o array. 
*/

pthread_barrier_t barreira;

struct ArrayInfo{
    int *array;
    int *ordenado;
    int tam;
};
struct threadThings{
    struct ArrayInfo *vetorInfo;
    int *nThreads;
    int threadId;
    int begin;
    int end;
};

void *funcaoThread(void *arg){
    struct threadThings info = (*(struct threadThings *) arg);
    for(int k=info.begin; k<=info.end && k+1<info.vetorInfo->tam; k++){
        for(int m=k+1; m<=info.end; m++){
            if(info.vetorInfo->array[m] > info.vetorInfo->array[m+1]){ 
                printf("Thread %d trocou\n", info.threadId);
                info.vetorInfo->ordenado[m] = info.vetorInfo->array[m+1];
                info.vetorInfo->ordenado[m+1] = info.vetorInfo->array[m];
            }
        }
    }
    pthread_barrier_wait(&barreira);
    
    pthread_exit(NULL);
}

int main(int argc, char* argv[]){
    //struct para as informações do array
    struct ArrayInfo vetorCoisas;
    int Nthreads;

    //únicas entradas do código
    printf("Qual o tamanho do array e a quantidade de particoes?\n");
    scanf("%d %d", &vetorCoisas.tam, &Nthreads);
    printf("Quais os elementos do array?\n");
    vetorCoisas.array = (int*) malloc(sizeof(int)*vetorCoisas.tam);
    vetorCoisas.ordenado = (int*)malloc(sizeof(int)*vetorCoisas.tam); 
    for(int i=0; i<vetorCoisas.tam; i++){
        scanf("%d", &vetorCoisas.array[i]);
    }
    //a quantidade de threads deve ser menor que a quantidade de elementos do array
    if(vetorCoisas.tam < Nthreads) return 1;

    //barreira iniciada
    pthread_barrier_init(&barreira, NULL, Nthreads);

    //struct que vai ser mandada para cada thread
    struct threadThings *thread = (struct threadThings*) malloc(sizeof(struct threadThings)*Nthreads);
    pthread_t threadVar[Nthreads];

    //variavel para indicar os indices do array
    int cont=0;
    //quantidade de elementos do array colocado em cada thread
    int quant = vetorCoisas.tam / Nthreads;

    for(int t=0; t<Nthreads; t++){
        //todas as threads apontam para a posição em que as informações do array está
        thread[t].vetorInfo = &vetorCoisas; 
        thread[t].threadId = t; 
        //colocando as partes do array em cada thread 
        thread[t].begin = cont;
        cont += quant;
        thread[t].end = cont;
        pthread_create(&threadVar[t], NULL, funcaoThread, (void*) &thread[t]);
    }
    for(int t=0; t<Nthreads; t++){
        pthread_join(threadVar[t], NULL);
    }
    //barreira finalizada
    pthread_barrier_destroy(&barreira);

    //thread que junta tudo 

    //array ordenado 
    for(int i=0; i<vetorCoisas.tam; i++){
        printf("%d ", vetorCoisas.ordenado[i]); 
    }
    printf("\n");

    pthread_exit(NULL);
    free(thread);

}