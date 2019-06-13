#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock;

void *incrementer(void *x)
{
    int *val = (int *) x;
    int i;
    pthread_mutex_lock(&lock);
    for (i = 0; i < 1000000; i ++) {
        (*val) ++;
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

#define THREADS 4

int main(int argc, char *argv[])
{
    int x = 0;
    int i;
    pthread_t threads[THREADS];
    printf("starting example 5-----------------------------------\n");
    if(pthread_mutex_init(&lock, NULL)) {
        printf("pthread init error\n");
        return -1;
    }

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
