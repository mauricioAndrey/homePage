#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>

/*
Rodar os códigos no linux

//http:/www.cin.ufpe.br/~eagt/if677/
//hpc-tutorials.llnl.gov/posix/
//https://computing.llnl.gov/tutorials/pthreads/

Livro: Programming with POSIX Threads

Compilar:   gcc -lpthread prog.c -o prog
            gcc -pthread prog.c -o prog
*/

//usando_fork.c
/*
int main(){
    int p = fork();
    int count = 0;
    bool condicao = true;
    while(condicao){
        count++;
        if(p!=0)
            printf("Proc. Pai\n");
        else
            printf("Proc. Filho\n");
        
        if(count == 1000) condicao = false;
    }
    return 0;
}
*/

//criacao.c
/*
void *PrintHello(void *threadid){
    printf("Ola, mundo\n");
    pthread_exit(NULL);
}
int main(int argc, char*argv[]){
    pthread_t thread;
    int rc;
    rc = pthread_create(&thread, NULL, PrintHello, NULL);
    if(rc){
        printf("ERRO; código de retorno é %d\n", rc);
        exit(-1);
    }
    printf("Main\n");
    pthread_exit(NULL);
}
*/

//cincoThreads.c
/*
#define NUM_THREADS 5
void *PrintHello(void *threadid){   
  int tid = *((int *)threadid);   
  printf("Ola, mundo! Sou eu, a thread #%d!\n", tid); 
  pthread_exit(NULL);
}
int main (int argc, char *argv[]){   
  pthread_t threads[NUM_THREADS];
  int *taskids[NUM_THREADS];

  int rc;   int t;   
  for(t=0; t<NUM_THREADS; t++){      
   taskids[t] = (int *) malloc(sizeof(int)); *taskids[t] = t;
	 printf("No main: criando thread %d\n", t);      
    rc = pthread_create(&threads[t], NULL, PrintHello, (void *) taskids[t]);      
    if (rc){         
      printf("ERRO; código de retorno é %d\n", rc);         
      exit(-1);      
    }   
  }   
  pthread_exit(NULL);
}
*/

//join.c
/*
void *print_msg( void *ptr);

main() {
  pthread_t thread1, thread2;
  char *msg1 = "Thread 1"; char *msg2 = "Thread 2";
  int ret1 = pthread_create( &thread1, NULL, print_msg, (void*)msg1);
  int ret2 = pthread_create( &thread2, NULL, print_msg, (void*)msg2);
  pthread_join( thread1, NULL);
  printf("Thread 1 voltou: %d\n",ret1); 
  pthread_join( thread2, NULL);
  printf("Thread 2 voltou: %d\n",ret2);
  exit(0);
}
void *print_msg ( void *ptr ) {
  char *message;
  message = (char *) ptr;
  printf("%s \n", message);
  pthread_exit(NULL);
}
*/


//joinTodos.c
///*
#define NUM_THREADS 5     

void *PrintHello(void *threadid){   
  int *tid = (int *)threadid; 
  char *ret = (char *)malloc(100);
  sprintf(ret, "Ola, mundo! Sou eu, a thread %d", *tid);
  pthread_exit((void *) tid);
}

int main (int argc, char *argv[]){   
  pthread_t threads[NUM_THREADS]; int *taskids[NUM_THREADS];
   int rc; int t; int u;   
  for(t=0; t<NUM_THREADS; t++){
    printf("No main: criando thread %d\n", t);    
    taskids[t] = (int *) malloc(sizeof(int)); *taskids[t] = t;
	 pthread_create(&threads[t],NULL,PrintHello, (void *)taskids[t]);         
  }
  for(u=0; u<NUM_THREADS;u++) {
    int *res;
    pthread_join(threads[u], (void **) &res);
    printf("%d\n",*res);
  }   
  pthread_exit(NULL);
}
//*/

//Multiplicação de matrizes


