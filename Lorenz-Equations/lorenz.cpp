// Lorenz equation solver
// Copyright (C) 2017 Brenton Horne
#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <utility>
#include <unistd.h>
#include <algorithm>

// Standard template library
using namespace std;

double N     = 100000.0;                  // Number of domain elements we're integrating over

// Integration interval
double t0    = 0.0;                       // Starting time
double t1    = 100;                       // End time

// Initial conditions
double X0    = 1.0;
double Y0    = 1.0;
double Z0    = 1.0;

// Parameters, a copy of this equation is in this directory
double rho   = 28;
double sigma = 10;
double beta  = 8/3.0;

// Step size
double h     = (t1 - t0) / double(N);

// dx is a function that returns a 3-tuple; first entry is dx/dt, second is dy/dt and third is dz/dt.
std::tuple<double, double, double> dx(double h, double sigma, double rho, double beta, double t, double x, double y, double z)
{
    return {h * sigma * (y - x), h * x * (rho - z) - h * y, h * x * y - h * beta * z};
}

// RK4 is a function that returns a 3-tuple; first entry is the diff in x, second is diff in y and third is diff in z. 
std::tuple<double, double, double> RK4(double t, double x, double y, double z, double h)
{
    // kn values are diffs in x.
    // ln values are diffs in y.
    // mn values are diffs in z.
    // diff1
    std::tuple<double, double, double> diff1 = dx(h, sigma, rho, beta, t,       x,        y,       z);
    double k1    = std::get<0>(diff1);
    double l1    = std::get<1>(diff1);
    double m1    = std::get<2>(diff1);

    // diff2
    std::tuple<double, double, double> diff2 = dx(h, sigma, rho, beta, t + h/2, x + k1/2, y + l1/2, z + m1/2);
    double k2    = std::get<0>(diff2);
    double l2    = std::get<1>(diff2);
    double m2    = std::get<2>(diff2);

    // diff3
    std::tuple<double, double, double> diff3 = dx(h, sigma, rho, beta, t + h/2, x + k2/2, y + l2/2, z + m2/2);
    double k3    = std::get<0>(diff3);
    double l3    = std::get<1>(diff3);
    double m3    = std::get<2>(diff3);

    // diff4
    std::tuple<double, double, double> diff4 = dx(h, sigma, rho, beta, t + h,   x + k3,   y + l3,   z + m3);
    double k4    = std::get<0>(diff4);
    double l4    = std::get<1>(diff4);
    double m4    = std::get<2>(diff4);

    // diff in x, y, z
    double diffx = (k1 + 2 * k2 + 2 * k3 + k4)/float(6);  // diff in x.
    double diffy = (l1 + 2 * l2 + 2 * l3 + l4)/float(6);  // diff in y.
    double diffz = (m1 + 2 * m2 + 2 * m3 + m4)/float(6);  // diff in z.

    return {diffx, diffy, diffz};
}

int main()
{
    // t vector
    std::vector<double> t;
    t.push_back(t0);

    // x vector
    std::vector<double> x;
    x.push_back(X0); // add X0 to vector

    // y vector
    std::vector<double> y;
    y.push_back(Y0); // add Y0 to vector

    // z vector
    std::vector<double> z;
    z.push_back(Z0); // add Z0 to vector

    // open myfilex ofstream
    ofstream myfilex;
    myfilex.open("lorenz-x.txt");

    // open myfiley ofstream
    ofstream myfiley;
    myfiley.open("lorenz-y.txt");

    // open myfilez ofstream
    ofstream myfilez;
    myfilez.open("lorenz-z.txt");

    // open myfilexy ofstream
    ofstream myfilexy;
    myfilexy.open("lorenz-xy.txt");

    // open myfilexz ofstream
    ofstream myfilexz;
    myfilexz.open("lorenz-xz.txt");

    // open myfileyz ofstream
    ofstream myfileyz;
    myfileyz.open("lorenz-yz.txt");

    // open myfilephase ofstream
    ofstream myfilephase;
    myfilephase.open("lorenz-phase.txt");

    // Loop over elements in t
    for(int i = 1; i<=N; i++)
    {
        std::tuple<double, double, double> diff = RK4(t[i-1], x[i-1], y[i-1], z[i-1], h);

	// add an ith element to t
        t.push_back( t[i-1] + h                 );
        // add an ith element to x
        x.push_back( x[i-1] + std::get<0>(diff) );
        // add an ith element to y
        y.push_back( y[i-1] + std::get<1>(diff) );
	// add an ith element to z
	z.push_back( z[i-1] + std::get<2>(diff) );

	// myfilex (i-1)th entry
        myfilex     << t[i-1];
        myfilex     << " "     << x[i-1]   << "\n";
	myfilex.precision(15);

	// myfiley (i-1)th entry
        myfiley     << t[i-1];
        myfiley     << " "     << y[i-1]  << "\n";
	myfiley.precision(15);

	// myfilez (i-1)th entry
        myfilez     << t[i-1];
        myfilez     << " "     << z[i-1]  << "\n";
	myfilez.precision(15);

	// myfilexy (i-1)th entry
	myfilexy    << x[i-1];
        myfilexy    << " "     << y[i-1]  << "\n";
	myfilexy.precision(15);

	// myfilexz (i-1)th entry
	myfilexz    << x[i-1];
        myfilexz    << " "     << z[i-1]  << "\n";
	myfilexz.precision(15);

	// myfileyz (i-1)th entry
	myfileyz    << y[i-1];
        myfileyz    << " "     << z[i-1]  << "\n";
	myfileyz.precision(15);

	// myfilephase (i-1)th entry
	myfilephase << x[i-1];
	myfilephase << " "     << y[i-1];
	myfilephase << " "     << z[i-1]  << "\n";
	myfilephase.precision(15);

        usleep(1000);
    }

    // myfilex Nth entry
    myfilex  << t[N];
    myfilex  << " "   << x[N];

    // myfiley Nth entry
    myfiley  << t[N];
    myfiley  << " "   << y[N];

    // myfilez Nth entry
    myfilez  << t[N];
    myfilez  << " "   << z[N];

    // myfilexy Nth entry
    myfilexy << x[N];
    myfilexy << " "   << y[N];

    // myfilexz Nth entry
    myfilexz << x[N];
    myfilexz << " "   << z[N];

    // myfileyz Nth entry
    myfileyz << y[N];
    myfileyz << " "   << z[N];

    // myfilephase Nth entry
    myfilephase << x[N]; 
    myfilephase << " " << y[N];
    myfilephase << " " << z[N];

    // close myfile streams
    myfilex.close();
    myfiley.close();
    myfilez.close();
    myfilexy.close();
    myfilexz.close();
    myfileyz.close();
    myfilephase.close();

    // Generate svg plots
    system("gnuplot -p lorenz.gp");

    // convert svg plots to png format
    system("rsvg-convert -w 2000 -o lorenz-x.png lorenz-x.svg");
    system("rsvg-convert -w 2000 -o lorenz-y.png lorenz-y.svg");
    system("rsvg-convert -w 2000 -o lorenz-z.png lorenz-z.svg");
    system("rsvg-convert -w 2000 -o lorenz-xy.png lorenz-xy.svg");
    system("rsvg-convert -w 2000 -o lorenz-xz.png lorenz-xz.svg");
    system("rsvg-convert -w 2000 -o lorenz-yz.png lorenz-yz.svg");
    system("rsvg-convert -w 2000 -o lorenz-phase.png lorenz-phase.svg");

    // exit
    return 0;
}
