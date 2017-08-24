// Exp(x) calculator using Maclaurin series
// Determines exp(x) with N+1 terms of the Maclaurin series
// Copyright (C) 2017 Brenton Horne 
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <utility>
#include <unistd.h>
#include <algorithm>

using namespace std;

int N    = 30;
double x = 1.0;

int fact(int n)
{
    if(n<=1) 
    {
         return 1;
    } else
    {
         return n*fact(n - 1);
    }
}

int main()
{
    double f = 0;
    double X = 1;
    for(int i = 0; i<=N; i++)
    {
         f = f + X/fact(i);
         X = X * x;
    }

    std::cout << "Exp(";
    //<< std::scientific;
    std::cout.precision(15);
    std::cout << x << ")=";
    std::cout << f;
    return 0;
}
