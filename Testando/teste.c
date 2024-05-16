#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define N 4 // Número de threads
#define ARRAY_SIZE 8 // Tamanho do array

pthread_barrier_t barrier;

struct mergeInfo{
    int *arr;
    int l;
    int m;
    int r;
};

struct ThreadInfo {
    int *arr;
    int start;
    int end;
};

void *bubbleSort(void *arg) {
    struct ThreadInfo *info = (struct ThreadInfo *)arg;
    int *arr = info->arr;
    int start = info->start;
    int end = info->end;

    for (int i = start; i < end; i++) {
        for (int j = start; j < end - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    pthread_barrier_wait(&barrier);

    pthread_exit(NULL);
}

void merge(struct mergeInfo *dados) {
    int *temp = (int *)malloc((dados->r - dados->l + 1) * sizeof(int));
    int i = dados->l, j = dados->m + 1, k = 0;

    while (i <= dados->m && j <= dados->r) {
        if (dados->arr[i] <= dados->arr[j]) {
            temp[k++] = dados->arr[i++];
        } else {
            temp[k++] = dados->arr[j++];
        }
    }

    while (i <= dados->m) {
        temp[k++] = dados->arr[i++];
    }

    while (j <= dados->r) {
        temp[k++] = dados->arr[j++];
    }

    for (i = dados->l, k = 0; i <= dados->r; i++, k++) {
        dados->arr[i] = temp[k];
    }

    free(temp);
}

void *mergeSort(void *arg) {
    struct mergeInfo *dados = (struct mergeInfo *) arg;
    if(dados->l < dados->r){
        dados->m = floor((dados->l+(double)dados->r)/2);
        merge(dados);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_barrier_init(&barrier, NULL, N);

    int arr[ARRAY_SIZE] = {4, 1, 7, 3, 2, 6, 8, 5};
    pthread_t threads[N];
    struct ThreadInfo threadInfo[N];

    int segmentSize = ARRAY_SIZE / N;
    for (int i = 0; i < N; i++) {
        threadInfo[i].arr = arr;
        threadInfo[i].start = i * segmentSize;
        threadInfo[i].end = (i + 1) * segmentSize;
        pthread_create(&threads[i], NULL, bubbleSort, (void *)&threadInfo[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_barrier_destroy(&barrier);

    pthread_t mergeThread;
    struct mergeInfo dados;
    dados.arr = arr;
    dados.l = 0;
    dados.r = ARRAY_SIZE;
    pthread_create(&mergeThread, NULL, mergeSort, (void *)&dados);
    pthread_join(mergeThread, NULL);

    printf("Array ordenado: ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");


    return 0;
}
