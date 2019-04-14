
 /**
 * @file hw1.c
 * @author your name (you@domain.com)
 * @brief Fahrenheit to Clesius conversion program.
 * @version 0.1
 * @date 2019-04-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "hw1.h"
#define N   256
#define A   32


int main(void){
    float temp = 5.0/9.0;
    float F = 0.0;
    float C = 0.0;
    char buf[N] = {0};
    float *Fp = &F;

    printf("Enter degrees in Fahrenheit \"ff.f\": ");
    scanf("%f", Fp);
    getchar();
    printf("\n");

    //Operations
    temp = ((F-A)*temp);

    printf("Result: %2f\n", temp);
    
    return 1;
}