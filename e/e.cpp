#include <stdlib.h>
#include <cmath>
#include <cstdio>

int factorial(int n)
{
    float ret = 1.0;
    if(n==0) {
         float ret = 1.0;
    } else {
         for(int i = 1; i <= n; ++i)
              ret *= i;
    }
    return ret;
}

int main() {
    float e = 0;

    for(int n = 0; n<=10; ++n)
         e = e + 1.0/factorial(n);

    printf("%.6f", e);
}
