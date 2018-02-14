// This program is inspired by the program shown in the question at
// https://stackoverflow.com/questions/12524316/for-loop-for-counting-approximation-of-pi-in-c
#include <stdio.h>

int main() {
    int N = 10000000;
    double pi = 0;
    int i = 0;

    for(i = 1; i <= N; i++)
    {
        float denom = 2.0 * i - 1.0;
        if((i % 2) == 1) { 
              pi = pi + (1.0/denom);
        } else {
              pi = pi - (1.0/denom);
        }
    }

    pi = 4 * pi;

    printf("The approximation of pi is: %lf", pi);

    return 0;    
}
