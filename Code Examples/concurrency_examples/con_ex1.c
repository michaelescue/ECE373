#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int x = 0;
    printf("starting example 1-----------------------------------\n");
    if (fork() == 0) {
        printf("child running now!!!!\n");
        for (int i = 0; i < 100000; i ++) {
            x ++;
        }
        printf("x at end of child is: %d\n", x);
        return 0;
    }
    else {
        printf("Parent running now!!!!\n");
        for (int i = 0; i < 100000; i ++) {
            x ++;
        }
        printf("x at end of parent is: %d\n", x);
        return 0;
    }
}
