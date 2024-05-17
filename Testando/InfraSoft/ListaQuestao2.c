#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*
Nthreads é o N, a quantidade de threads e a quantidade que vai particionar o array.
*/

pthread_barrier_t barreira;

struct ArrayInfo{
    int *array;
    int tam;
};
struct threadThings{
    struct ArrayInfo *vetorInfo;
    int *Subarray;
    int *nThreads;
    int tamSub;
    int threadId;
    int begin;
    int end;
};

void *funcaoThread(void *arg){
    struct threadThings info = (*(struct threadThings *) arg);
    for(int i=info.begin; i<info.end; i++){
        for(int j=i; j<info.end-1; j++){
            if(info.Subarray[j] > info.Subarray[j+1]){
                printf("Thread %d trocou\n", info.threadId);
                int temp = info.Subarray[j];
                info.Subarray[j] = info.Subarray[j+1];
                info.Subarray[j+1] = temp;
            }
        }
    }
    pthread_barrier_wait(&barreira);
    pthread_exit(NULL);
}

void *sortThread(void *arg){
    //todas as threads e seus subarrays
    struct threadThings *info = (struct threadThings*) arg;
    //comparar qual o menor valor em determinada posição de cada subArray
    //colocá-los no "novo" array de maneira crescente
    //fazer isso com cada posicão

    int k=1;
    int ultimo=__INT_MAX__;
    for(int j=0; j<info[0].tamSub && k<info[0].vetorInfo->tam; j++){
        for(int i=0; i<info[0].nThreads[0]; i++){
            int subI=info[i].begin+j;
            //int subF=info[i].end;
            //o ultimo adicionado eh maior do que o atual //trocam de pos
            if(ultimo > info[i].Subarray[subI]){
                //a pos anterior recebe o atual
                info[i].vetorInfo->array[k-1] = info[i].Subarray[subI];
                //a pos atual recebe o ultimo
                info[i].vetorInfo->array[k] = ultimo;
                //o atual vira o novo ultimo
                ultimo = info[i].Subarray[subI];
                k++;
            }
            //o ultimo nao é maior ent só adiciona o valor atual na pos atual
            else {
                info[i].vetorInfo->array[k] = info[i].Subarray[subI];
                k++;
            }
        }
    }
}

int main(){
    //struct para as informações do array
    struct ArrayInfo vetorCoisas;
    int Nthreads;

    //únicas entradas do código
    printf("Qual o tamanho do array e a quantidade de particoes?\n");
    scanf("%d %d", &vetorCoisas.tam, &Nthreads);
    printf("Quais os elementos do array?\n");
    vetorCoisas.array = (int*) malloc(sizeof(int)*vetorCoisas.tam);
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
        thread[t].Subarray = (int*)calloc(0,sizeof(int)*vetorCoisas.tam);
        thread[t].vetorInfo = &vetorCoisas;
        thread[t].Subarray = vetorCoisas.array;
        thread[t].threadId = t;
        thread[t].tamSub = quant;
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
    pthread_t threadSort;
    pthread_create(&threadSort, NULL, sortThread, (void*) &thread);
    pthread_join(threadSort, NULL);

    //array ordenado
    for(int i=0; i<vetorCoisas.tam; i++){
        printf("%d ", vetorCoisas.array[i]);
    }
    printf("\n");

    free(vetorCoisas.array);
    for(int i=0; i<Nthreads; i++)
        free(thread[i].Subarray);
    free(thread);
    pthread_exit(NULL);
}