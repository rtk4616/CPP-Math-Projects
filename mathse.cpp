#include <iostream>
#include <math.h>       /* sin */
#include <GL/glut.h>
#include <fstream>
#include <SDL/SDL.h>
const int g=30;
const double l = 1.5;
double u = 4;
double theta = 1;
const double h = 0.01;
double translatex=0;
double translatey=0;
GLuint texture_background;
using namespace std;

//simplified equations 1
double thetadot(double u)
{
    return u;
}

//simplified equations 2
double udot(double theta)
{
    return (-g / l) * sin(theta);
}


int main(int argc, char *argv[])
{
    double theta, thetanext, u, unext, ku1, ku2, ku3, ku4, kt1, kt2, kt3, kt4;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return 1;

    atexit(SDL_Quit);
    SDL_Surface *screen = SDL_SetVideoMode(width, height, 0, SDL_DOUBLEBUF);
    if (screen == NULL)
        return 2;
    //putting inital values to the function
    u = u0;
    theta = theta0;

    while(true)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                return 0;
        }

        double x = xoffset + l * sin(theta);
        double y = yoffset + l * cos(theta);

        SDL_LockSurface(screen);

        //string hanging position
        draw_circle(screen, xoffset, yoffset, 10, 0x0000ff00);
        fill_circle(screen, xoffset, yoffset, 10, 0x0000ff00);

        //draw string
        draw_line(screen, xoffset, yoffset, x, y, 0xff3366ff);

        //draw bob's current position
        fill_circle(screen, (int)x, (int)y, r, 0xff004400);
        draw_circle(screen, (int)x, (int)y, r, 0xff3366ff);

        SDL_Delay(300);
        //SDL_FreeSurface(screen);
        SDL_Flip(screen);

        //Numerical integration of equation 1
        kt1 = thetadot(u);
        kt2 = thetadot(u) + 0.5 * h * kt1;
        kt3 = thetadot(u) + 0.5 * h * kt2;
        kt4 = thetadot(u) + h * kt3;
        thetanext = thetadot(u) + (h / 6) * (kt1 + 2 * kt2 + 2 * kt3 + kt4);

        //Numerical integration of equation 2
        ku1 = udot(theta);
        ku2 = udot(theta) + 0.5 * h * ku1;
        ku3 = udot(theta) + 0.5 * h * ku2;
        ku4 = udot(theta) + h * ku3;
        unext = udot(theta) + (h / 6) * (ku1 + 2 * ku2 + 2 * ku3 + ku4);

        //updating values
        u = unext;
        theta = thetanext;
    }
    return 0;
}
