#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
//#include <unistd.h>


struct matriz{
    int **matA;
    int **matB;
    int **res;
    int LINHAS,COLUNAS;
}; 
struct threadThings{
    struct matriz *mat;
    pthread_t thread;
    int *NUM_THREADS;
    int id;
    int linha, coluna;
};

void *celulaThread(void *arg){
    struct threadThings* info = (struct threadThings*) arg;
    int i=info->linha;
    int j=info->coluna;
    int k;
    for(k=0; k<info->mat->COLUNAS; k++){
        info->mat->res[i][j] = info->mat->res[i][j] + 
            info->mat->matA[i][k]*info->mat->matB[k][j];
    }
}

int main(int argc, char *argv[]){
    struct matriz mat;
    
    //if(arq == NULL) { return 1; }

    scanf("%d %d", &mat.LINHAS, &mat.COLUNAS);
    ///
    mat.matA = (int **) malloc(sizeof(int*) * mat.LINHAS);
    mat.matB = (int **) malloc(sizeof(int*) * mat.LINHAS);
    mat.res = (int **) malloc(sizeof(int*) * mat.LINHAS);
    for (int i = 0; i < mat.LINHAS; i++) {
        mat.matA[i] = (int *) malloc(sizeof(int) * mat.COLUNAS);
        mat.matB[i] = (int *) malloc(sizeof(int) * mat.COLUNAS);
        mat.res[i] = (int *) malloc(sizeof(int) * mat.COLUNAS);

        for(int j=0; j<mat.COLUNAS; j++){
            scanf("%d", &mat.matA[i][j]);
            //printf("AAA\n");
        } //%*c
    }
    //
    for(int i=0; i<mat.LINHAS; i++){
        for(int j=0; j<mat.COLUNAS; j++){
            scanf("%d", &mat.matB[i][j]);
            //printf("bbb\n");
        }
    }
    ///
    int NUM_THREADS = mat.LINHAS * mat.COLUNAS;
    struct threadThings *threads = (struct threadThings *) malloc(sizeof(struct threadThings)*NUM_THREADS);

    int t=0;
    for(int i=0; i<mat.LINHAS; i++)
        for(int j=0; j<mat.COLUNAS; j++){
            //threads[t] = (struct threadThings*) malloc(sizeof(struct threadThings));
            threads[t].mat = &mat; 
            threads[t].id = t; 
            threads[t].NUM_THREADS = &NUM_THREADS;
            threads[t].linha = i;
            threads[t].coluna = j;
            printf("Na main: criando thread %d\n", t);
            pthread_create(&threads[t].thread, NULL, celulaThread, (void *) &threads[t]);
            t++;
        }

    for(int u=0; u<NUM_THREADS; u++){
        //int *res; 
        pthread_join(threads[u].thread, NULL);
    }
    //print
    for(int i=0; i<mat.LINHAS; i++){
        for(int j=0; j<mat.COLUNAS; j++) 
            printf("%d ", mat.res[i][j]);
        printf("\n");
    }
    pthread_exit(NULL);
    //free
    free(threads);
    for (int i = 0; i < mat.LINHAS; i++) {
        free(mat.matA[i]);
        free(mat.matB[i]);
        free(mat.res[i]);
    }
    free(mat.matA);
    free(mat.matB);
    free(mat.res);

}