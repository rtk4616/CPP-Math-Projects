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

using namespace std;

double N     = 100000.0;                  // Number of domain elements we're integrating over
double t0    = 0.0;                       // Starting time
double t1    = 100;                       // End time
double X0    = 1.0;
double Y0    = 1.0;
double Z0    = 1.0;
double rho   = 28;
double sigma = 10;
double beta  = 8/3.0;
double h     = (t1 - t0) / double(N);     // step size

std::tuple<double, double, double> dx(double h, double sigma, double rho, double beta, double t, double x, double y, double z)
{
    return {h * sigma * (y - x), h * x * (rho - z) - h * y, h * x * y - h* beta * z};
}

std::tuple<double, double, double> RK4(double t, double x, double y, double z, double h)
{
    // kn values are diffs in x.
    // ln values are diffs in y.
    // mn values are diffs in z.
    std::tuple<double, double, double> diff1 = dx(h, sigma, rho, beta, t,       x,        y,       z);
    double k1    = std::get<0>(diff1);
    double l1    = std::get<1>(diff1);
    double m1    = std::get<2>(diff1);

    std::tuple<double, double, double> diff2 = dx(h, sigma, rho, beta, t + h/2, x + k1/2, y + l1/2, z + m1/2);

    double k2    = std::get<0>(diff2);
    double l2    = std::get<1>(diff2);
    double m2    = std::get<2>(diff2);

    std::tuple<double, double, double> diff3 = dx(h, sigma, rho, beta, t + h/2, x + k2/2, y + l2/2, z + m2/2);

    double k3    = std::get<0>(diff3);
    double l3    = std::get<1>(diff3);
    double m3    = std::get<2>(diff3);

    std::tuple<double, double, double> diff4 = dx(h, sigma, rho, beta, t + h,   x + k3,   y + l3,   z + m3);

    double k4    = std::get<0>(diff4);
    double l4    = std::get<1>(diff4);
    double m4    = std::get<2>(diff4);

    double diffx = (k1 + 2 * k2 + 2 * k3 + k4)/float(6);  // diff in x.
    double diffy = (l1 + 2 * l2 + 2 * l3 + l4)/float(6);  // diff in y.
    double diffz = (m1 + 2 * m2 + 2 * m3 + m4)/float(6);  // diff in z.

    return {diffx, diffy, diffz};
}

int main()
{
    std::vector<double> t;
    t.push_back(t0);

    std::vector<double> x;
    x.push_back(X0);

    std::vector<double> y;
    y.push_back(Y0);

    std::vector<double> z;
    z.push_back(Z0);

    ofstream myfilex;
    myfilex.open("lorenz-x.txt");

    ofstream myfiley;
    myfiley.open("lorenz-y.txt");

    ofstream myfilez;
    myfilez.open("lorenz-z.txt");

    ofstream myfilexy;
    myfilexy.open("lorenz-xy.txt");

    ofstream myfilexz;
    myfilexz.open("lorenz-xz.txt");

    ofstream myfileyz;
    myfileyz.open("lorenz-yz.txt");

    ofstream myfilephase;
    myfilephase.open("lorenz-phase.txt");

    double minx = x[0];

    for(int i = 1; i<=N; i++)
    {
        std::tuple<double, double, double> diff = RK4(t[i-1], x[i-1], y[i-1], z[i-1], h);

        t.push_back( t[i-1] + h                 );
        x.push_back( x[i-1] + std::get<0>(diff) );
        y.push_back( y[i-1] + std::get<1>(diff) );
	z.push_back( z[i-1] + std::get<2>(diff) );

        myfilex     << t[i-1];
        myfilex     << " "     << x[i-1]   << "\n";

        myfiley     << t[i-1];
        myfiley     << " "     << y[i-1]  << "\n";

        myfilez     << t[i-1];
        myfilez     << " "     << z[i-1]  << "\n";

	myfilexy    << x[i-1];
        myfilexy    << " "     << y[i-1]  << "\n";

	myfilexz    << x[i-1];
        myfilexz    << " "     << z[i-1]  << "\n";

	myfileyz    << y[i-1];
        myfileyz    << " "     << z[i-1]  << "\n";

	myfilephase << x[i-1];
	myfilephase << " "     << y[i-1];
	myfilephase << " "     << z[i-1]  << "\n";

        if(x[i]<minx)
        minx=x[i];

        usleep(1000);
    }

    myfilex  << t[N];
    myfilex  << " "   << x[N];

    myfiley  << t[N];
    myfiley  << " "   << y[N];

    myfilez  << t[N];
    myfilez  << " "   << z[N];

    myfilexy << x[N];
    myfilexy << " "   << y[N];

    myfilexz << x[N];
    myfilexz << " "   << z[N];

    myfileyz << y[N];
    myfileyz << " "   << z[N];

    myfilephase << x[N]; 
    myfilephase << " " << y[N];
    myfilephase << " " << z[N];

    myfilex.close();
    myfiley.close();
    myfilez.close();
    myfilexy.close();
    myfilexz.close();
    myfileyz.close();
    myfilephase.close();

    system("gnuplot -p lorenz.gp");
    system("rsvg-convert -w 2000 -o lorenz-x.png lorenz-x.svg");
    system("rsvg-convert -w 2000 -o lorenz-y.png lorenz-y.svg");
    system("rsvg-convert -w 2000 -o lorenz-z.png lorenz-z.svg");
    system("rsvg-convert -w 2000 -o lorenz-xy.png lorenz-xy.svg");
    system("rsvg-convert -w 2000 -o lorenz-xz.png lorenz-xz.svg");
    system("rsvg-convert -w 2000 -o lorenz-yz.png lorenz-yz.svg");
   /* system("rsvg-convert -w 2000 -o lorenz-phase.png lorenz-phase.svg");*/

    std::cout << "x[N] is: " << x[N] << ".\n";

    return 0;
}
