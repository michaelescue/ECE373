#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>

void *incrementer(void *x)
{
    atomic_int *val = (atomic_int *) x;
    int i;
    for (i = 0; i < 1000000; i ++) {
        (*val) ++;
    }
    return NULL;
}

#define THREADS 4

int main(int argc, char *argv[])
{
    atomic_int x = 0;
    int i;
    pthread_t threads[THREADS];
    printf("starting example 4-----------------------------------\n");
    
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
