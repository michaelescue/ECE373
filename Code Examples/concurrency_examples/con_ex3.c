#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

void *incrementer(void *x)
{
    int *val = (int *) x;
    int i;
    sem_wait(&sem);
    for (i = 0; i < 10000; i ++) {
        (*val) ++;
    }
    sem_post(&sem);
    return NULL;
}

#define THREADS 4

int main(int argc, char *argv[])
{
    int x = 0;
    int i;
    pthread_t threads[THREADS];
    printf("starting example 3-----------------------------------\n");
    
    // 0 - used to indicate sharing between threads, not processes
    // 1 - initial semaphore value (ie, number of things that can use this at once)
    sem_init(&sem, 0, 1);

    for (i = 0; i < THREADS; i ++) {
        printf("creating thread number %d\n", i);
        if(pthread_create(&threads[i], NULL, incrementer, &x)) {
            printf("thread creation error\n");
            return -1;
        }
    }

    for (i = 0; i < THREADS; i ++) {
        if(pthread_join(threads[i], NULL))
            printf("thread join error\n");
    }
    printf("final value of x is %d\n", x);
}
