#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
//#include <unistd.h>

#define NUM_THREADS 2
#define LINHAS 3
#define COLUNAS 3

int matriz1[LINHAS][COLUNAS] = {{1,2,5}, {3,4,2}, {5,6,1}};
int matriz2[LINHAS][COLUNAS] = {{1,2,4}, {3,4,2}, {5,6,1}};
int resultado[LINHAS][COLUNAS];

void *linhaThread(void *arg){
    int i,j,k;
    int *id = (int*) arg;
    for(i = (*id); i<LINHAS; i=i+NUM_THREADS) {
        for(j=0;j<COLUNAS; j++){
            resultado[i][j] = 0;
            for(k=0; k<COLUNAS; k++)
                resultado[i][j] = resultado[i][j] + matriz1[i][k]*matriz2[k][j];
        }
    }
}

int main(int argc, char *argv[]){
    pthread_t threads[NUM_THREADS];
    int *ids[NUM_THREADS];
    int i,j;
    for(i=0;i<NUM_THREADS; i++){
        printf("Na main: criando thread %d\n", i);
        ids[i]=(int*)malloc(sizeof(int));
        *ids[i] = i;
        pthread_create(&threads[i], NULL, linhaThread, (void *) ids[i]);
    }
    for(j=0; j<LINHAS; j++){
        //int *res;
        pthread_join(threads[i], NULL);
    }
    for(i=0; i<LINHAS; i++){
        for(j=0; j<COLUNAS; j++)
            printf("%d ", resultado[i][j]);
        printf("\n");
    }
    pthread_exit(NULL);
}