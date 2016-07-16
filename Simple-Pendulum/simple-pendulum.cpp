#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <utility>
#include <unistd.h>
#include <algorithm>

#define M_PI 3.14159265358979323846  /* pi */
using namespace std;

double N     = 1000.0;                 // Number of domain elements we're integrating over
double t0    = 0.0;										 // Starting time
double t1    = 10;
double x0    = 0.0;
double dx0   = 0.0;
double h     = (t1 - t0) / double(N);  // step size

double dx2(double t, double x, double dx)
{
	return {-9.8*cos(x)};
}

std::pair<double, double> RK4(double t, double x, double dx, double h)
{
	// k values are diffs in dy/dx.
	// l values are diffs in x.
	double k1, k2, k3, k4, l1, l2, l3, l4, diff1, diff2;
	k1 = h*dx2(t,x,dx);
	l1 = h*dx;
	k2 = h*dx2(t+h/2,x+l1/2,dx+k1/2);
	l2 = h*(dx+k1/2);
	k3 = h*dx2(t+h/2,x+l2/2,dx+k2/2);
	l3 = h*(dx+k2/2);
	k4 = h*dx2(t+h,x+l3,dx+k3);
	l4 = h*(dx+k3);
  diff1 = (l1+2*l2+2*l3+l4)/float(6); // diff in x.
  diff2 = (k1+2*k2+2*k3+k4)/float(6); // diff in y.
  return {diff1, diff2};
}

int main()
{
    std::vector<double> t;
    t.push_back(t0);
    std::vector<double> x;
    x.push_back(x0);
    std::vector<double> dx;
    dx.push_back(dx0);

    ofstream myfile;
    myfile.open("simple-pendulum.txt");

    ofstream myfiledx;
    myfiledx.open("simple-pendulum-dx.txt");

    ofstream myfilephase;
    myfilephase.open("simple-pendulum-phase.txt");

    for(int i = 1; i<=N; i++)
		{
        auto diff = RK4(t[i-1],x[i-1],dx[i-1],h);
        t.push_back(  t[i-1] + h);
        x.push_back(  x[i-1] + diff.first  );
        dx.push_back(dx[i-1] + diff.second );
        myfile << t[i-1];
        myfile << " " << x[i-1] << "\n";
        myfiledx << t[i-1];
        myfiledx << " " << dx[i-1] << "\n";
        myfilephase << x[i-1];
        myfilephase << " " << dx[i-1] << "\n";
        usleep(1000);
    }
    myfile << t[N];
		myfile << " " << x[N];
    myfiledx << t[N];
    myfiledx << " " << dx[N];
		myfile.close();
    myfiledx.close();
		system("gnuplot -p simple-pendulum.gp");
    double minx = x[0];
    for(int i=0;i<N;i++)
    {
        if(x[i]<minx)
        minx=x[i];
    }
    std::cout << "Error: " << std::scientific;
    std::cout.precision(15);
    cout << minx + M_PI;
    std::cout << "X minimum: " << std::scientific;
    std::cout.precision(15);
    cout << minx;
		return 0;
}
