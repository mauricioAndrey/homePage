#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
//#include <unistd.h>


struct matriz{
    int **mat1;
    int **mat2;
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
            info->mat->mat1[i][k]*info->mat->mat2[k][j];
    }
}

int main(int argc, char *argv[]){
    struct matriz mat;
    
    FILE *arq = fopen("arqTeste.txt", "r");
    if(arq == NULL) { return 1; }

    fscanf(arq, "%d %d", &mat.LINHAS, &mat.COLUNAS);
    ///
    mat.mat1 = (int **) malloc (sizeof(int*));
    mat.res = (int **) malloc(sizeof(int*));
    for(int i=0; i<mat.LINHAS; i++){
        mat.mat1[i] = (int *) malloc(sizeof(int));
        mat.res[i] = (int*) malloc(sizeof(int));
        for(int j=0; j<mat.COLUNAS; j++){
            fscanf(arq, " %d", &mat.mat1[i][j]);
            printf("AAA\n");
        } //%*c
    }
    //
    mat.mat2 = (int **) malloc (sizeof(int*));
    for(int i=0; i<mat.LINHAS; i++){
        mat.mat2[i] = (int *) malloc(sizeof(int));
        for(int j=0; j<mat.COLUNAS; j++){
            fscanf(arq, " %d", &mat.mat2[i][j]);
            printf("bbb\n");
        }
    }
    ///
    int NUM_THREADS = mat.LINHAS * mat.COLUNAS;
    struct threadThings **threads = (struct threadThings **) 
        malloc(sizeof(struct threadThings*)*NUM_THREADS);
    
    int t=0,i=0,j=0;
    for(t=0;t<NUM_THREADS; t++){
        threads[t] = (struct threadThings*) malloc(sizeof(struct threadThings));
        (*threads)[t].mat = &mat; 
        (*threads)[t].id = t; 
        (*threads)[t].NUM_THREADS = &NUM_THREADS;
        (*threads)[t].linha = i;
        if(i==mat.LINHAS) i=0;
        else if(i<mat.LINHAS) i++;
        (*threads)[t].coluna = j;
        if(j==mat.COLUNAS) j=0;
        else if(j<mat.COLUNAS && t%mat.COLUNAS == 0) j++;
        printf("Na main: criando thread %d\n", t);
        pthread_create(&threads[t]->thread, NULL, celulaThread, (void *) threads[t]);
    }
    for(t=0;t<NUM_THREADS; t++){
        //int *res; 
        pthread_join((*threads)[t].thread, NULL);
    }
    for(i=0; i<mat.LINHAS; i++){
        for(j=0; j<mat.COLUNAS; j++) 
            printf("%d ", mat.res[i][j]);
        printf("\n");
    }
    pthread_exit(NULL);
    fclose(arq);
}