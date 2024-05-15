#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 3

pthread_barrier_t barrier;

struct Array {
    int *arr;
    int size;
};

struct ThreadInfo {
    struct Array *array;
    pthread_t thread;
    int id;
    int start;
    int end;
};

void *sortThread(void *arg) {
    struct ThreadInfo *info = (struct ThreadInfo *)arg;
    int *arr = info->array->arr;
    int size = info->array->size;
    
    for (int i = info->start; i < info->end; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        pthread_barrier_wait(&barrier);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    struct Array array;
    scanf("%d", &array.size);
    array.arr = (int *)malloc(sizeof(int) * array.size);
    
    for (int i = 0; i < array.size; i++) {
        scanf("%d", &array.arr[i]);
    }

    pthread_barrier_init(&barrier, NULL, N);

    struct ThreadInfo *threads = (struct ThreadInfo *)malloc(sizeof(struct ThreadInfo) * N);

    int partitionSize = array.size / N;
    for (int i = 0; i < N; i++) {
        threads[i].array = &array;
        threads[i].id = i;
        threads[i].start = i * partitionSize;
        threads[i].end = (i + 1) * partitionSize;
        pthread_create(&threads[i].thread, NULL, sortThread, (void *)&threads[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i].thread, NULL);
    }

    pthread_barrier_destroy(&barrier);

    for (int i = 0; i < array.size; i++) {
        printf("%d ", array.arr[i]);
    }
    printf("\n");

    free(array.arr);
    free(threads);

    return 0;
}
