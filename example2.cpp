#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

double dx2(int t, int x, int dx)
{
    return (-9.8*cos(x));
}

int square(int x) 
{
    return (x*x);
}

std::pair<double, double> RK4(float t, float x, float dx, float h)
{
    double k1, k2, k3, k4, l1, l2, l3, l4, diff1, diff2;
    k1 = h*dx2(t,x,dx);
    l1 = h*k1;
    k2 = h*dx2(t+h/2,x+l1/2,dx+k1/2);
    l2 = h*k2;
    k3 = h*dx2(t+h/2,x+l2/2,dx+k2/2);
    l3 = h*k3;
    k4 = h*dx2(t+h,x+l3,dx+k3);
    l4 = h*k4;
    diff1 = (l1+2*l2+2*l3+l4)/float(6);
    diff2 = (k1+2*k2+2*k3+k4)/float(6);
    return {diff1, diff2};
}

int main()
{
    double t, t0, t1, x, x0, dx, dx0, h, N;
    N   = 1000.0;
    t0  = 0.0;
    t   = t0;
    t1  = 10.0;
    x0  = 0.0;
    x   = x0;
    dx0 = 0.0;
    dx  = dx0;
    h   = (t1 - t0) / float(N);

    for(int i = 1; i<=N; i++) {
        auto diff = RK4(t,x,dx,h);
        x = x + diff.first;
        dx = dx + diff.second;
        t = t + h;
    }
    cout << x << " " << dx << "\n" ;
    return 0;
}
