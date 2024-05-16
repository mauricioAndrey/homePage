#define _XOPEN_SOURCE 600

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//contador.c
/*
long contador = 0; 
void *inc(void *threadid){
    int i = 0; 
    for(; i < 9000000; i++) { 
        contador++; 
    }
}
void *dec(void *threadid){   
    int i = 0;
    for(; i < 9000000; i++) { 
        contador--; 
    }
}
int main (int argc, char *argv[]){   
    pthread_t thread1, thread2;   
    pthread_create(&thread1, NULL, inc, NULL); 
    pthread_create(&thread2, NULL, dec, NULL); 
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL); 
    printf("Valor final do contador: %ld\n", contador);
    pthread_exit(NULL);
}
*/

//mutex é para exclusão mútua
//uso mutex.c
/*
long contador = 0; 
pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;
//lock eh bloqueante

void *inc(void *threadid){
    int i = 0; 
    for(; i < 9000000; i++) { 
        pthread_mutex_lock(&mymutex); 
        contador++; 
        pthread_mutex_unlock(&mymutex); 
    }
}
void *dec(void *threadid){   
    int i = 0;
    for(; i < 9000000; i++) { 
        pthread_mutex_lock(&mymutex); 
        contador--; 
        pthread_mutex_unlock(&mymutex); 
    }
}
int main (int argc, char *argv[]){   
    pthread_t thread1, thread2;   
    pthread_create(&thread1, NULL, inc, NULL); 
    pthread_create(&thread2, NULL, dec, NULL); 
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL); 
    printf("Valor final do contador: %ld\n", contador);
    pthread_exit(NULL);
}
*/

//uso do trylock do mutex
/*
long contador = 0; 
pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;

//alternativa pthread_mutex_trylock();
//não bloqueante //0 -> travar
//é muito mais lento do que apenas o lock

void *inc(void *threadid){
    int i = 0; 
    for(; i < 9000000; i++) { 
        while(pthread_mutex_trylock(&mymutex) != 0) {;} 
        contador++; 
        pthread_mutex_unlock(&mymutex); 
    }
}
void *dec(void *threadid){   
    int i = 0;
    for(; i < 9000000; i++) { 
        while(pthread_mutex_trylock(&mymutex) != 0) {;} 
        contador--; 
        pthread_mutex_unlock(&mymutex); 
    }
}
int main (int argc, char *argv[]){   
    pthread_t thread1, thread2;   
    pthread_create(&thread1, NULL, inc, NULL); 
    pthread_create(&thread2, NULL, dec, NULL); 
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL); 
    printf("Valor final do contador: %ld\n", contador);
    pthread_exit(NULL);
}
*/

//produtor e consumidor //prod_cons.c
//variáveis de condição sempre precisam ser usadas com o mutex //SEMPRE
/*
#define BUFFER_SIZE 10
#define NUM_ITEMS 100

int buff[BUFFER_SIZE];  // buffer size = 10; 
int items = 0; // number of items in the buffer.
int first = 0;
int last = 0; 

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//variavel para produtor
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
//variavel para consumidor
pthread_cond_t fill = PTHREAD_COND_INITIALIZER;
 
void *producer();
void *consumer();

int main() {
    pthread_t consumer_thread; 
    pthread_t producer_thread; 
    pthread_create(&consumer_thread,NULL,consumer,NULL);
    pthread_create(&producer_thread,NULL,producer,NULL);
    pthread_join(producer_thread,NULL);  
    pthread_join(consumer_thread,NULL);
}

void put(int i){
    pthread_mutex_lock(&mutex);
    while(items == BUFFER_SIZE) {
        pthread_cond_wait(&empty, &mutex);
    }
    buff[last] = i;
    printf("pos %d: ", last);
    items++; last++;
    if(last==BUFFER_SIZE) { last = 0; } 
    if(items == 1) { 
        pthread_cond_signal(&fill); }
    pthread_mutex_unlock(&mutex); 
}
void *producer() {
    int i = 0;
    printf("Produtor\n");
    for(i=0;i<NUM_ITEMS; i++) {
        put(i);
        printf("Produzi %d \n",i);
    }
    pthread_exit(NULL);
}

int get(){
    int result;
    pthread_mutex_lock(&mutex);
    while(items == 0){
        pthread_cond_wait(&fill, &mutex);
    }
    result = buff[first];
    printf("pos %d: ", first);
    items--; first++;
    if(first==BUFFER_SIZE) { first = 0; }
    if(items == BUFFER_SIZE - 1){
        pthread_cond_signal(&empty);}
    pthread_mutex_unlock(&mutex);
    return result;
}
void *consumer() {
    int i,v;
    printf("Consumidor\n");
    for (i=0;i<NUM_ITEMS;i++) {
        v = get();
        printf("Consumi %d  \n",v);
    }
    pthread_exit(NULL);
}

*/

//barreira
//sincronizacao das threads
/*
#define THREADS 3
#define ITERACOES 20

pthread_barrier_t barrier;
 
void *codigo_thread(void *threadid);

int main() {
	
	pthread_t threads[THREADS]; 
    int *ids[THREADS];   
    int i;
	
	pthread_barrier_init(&barrier, NULL, 3);

	for(i = 0; i < THREADS; i++) {
		ids[i] =(int *) malloc(sizeof(int)); 
		*ids[i] = i;
  	    pthread_create(&threads[i],NULL,codigo_thread,(void *) ids[i]);  
    }
  
    for(i = 0; i < THREADS; i++) { pthread_join(threads[i],NULL); }
  
    pthread_barrier_destroy(&barrier);
    
    pthread_exit(NULL);
  
    return 0;
  
}


void *codigo_thread(void *threadid) {
    int i;

    printf("Thread %d iniciou \n", *((int*) threadid));

    for (i=0; i < ITERACOES; i++) {
        printf("Thread %d iteracao %d \n", *((int*) threadid),i);
        pthread_barrier_wait(&barrier);
    }
    
    printf("Thread %d terminou \n", *((int*) threadid));
    pthread_exit(NULL);

}
*/

//exercício
//um produtor e três consumidores
//no lugar de signal, usa um broadcast
//mudar isso//mudei
//*
#define BUFFER_SIZE 10
#define NUM_ITEMS 100
#define THREADS 3

int buff[BUFFER_SIZE];  // buffer size = 10; 
int items = 0; // number of items in the buffer.
int first = 0;
int last = 0; 

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//variavel para produtor 
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
//variavel para consumidor 
pthread_cond_t fill = PTHREAD_COND_INITIALIZER;

void *producer();
void *consumer(void *arg);

int main() {

    pthread_t consumer_thread[THREADS];
    pthread_t producer_thread; 
    int *ids[THREADS]; 
    
    for(int i=0; i<THREADS; i++){
        ids[i] = (int *) malloc(sizeof(int));
        *ids[i] = i;
        pthread_create(&consumer_thread[i],NULL,consumer,(void*)ids[i]);
    }
    pthread_create(&producer_thread,NULL,producer,NULL);
    
    pthread_exit(NULL);

    return 0;
}

void put(int i){
    pthread_mutex_lock(&mutex);
    while(items == BUFFER_SIZE) {
        pthread_cond_wait(&empty, &mutex);
    }
    buff[last] = i;
    printf("pos %d: ", last);
    items++; last++;
    if(last==BUFFER_SIZE) { last = 0; } 
    if(items == 1) { pthread_cond_broadcast(&fill); }
    pthread_mutex_unlock(&mutex); 
}
void *producer() {
    int i = 0;
    printf("Produtor\n");
    int amount = NUM_ITEMS * THREADS;
    printf("Produtor iniciou\n");
    for(i=0;i<amount; i++) {
        put(i);
        printf("Produzi %d \n",i);
    }
    printf("Produtor terminou\n");
    pthread_exit(NULL);
}

int get(){
    int result;
    pthread_mutex_lock(&mutex);
    while(items == 0){ pthread_cond_wait(&fill, &mutex); }
    result = buff[first];
    printf("pos %d: ", first);
    items--; first++;
    if(first==BUFFER_SIZE) { first = 0; }
    if(items == BUFFER_SIZE - 1){ pthread_cond_signal(&empty); }
    pthread_mutex_unlock(&mutex);
    return result;
}
void *consumer(void *arg) {
    int i,v;
    int *id = ((int*) arg);
    printf("Consumidor %d iniciou\n", *id);
    for (i=0;i<NUM_ITEMS;i++) {
        v = get();
        printf("Consumidor %d consumiu %d  \n", *id, v);
    }
    printf("Consumidor %d terminou\n", *id);
    pthread_exit(NULL);
}

//*/