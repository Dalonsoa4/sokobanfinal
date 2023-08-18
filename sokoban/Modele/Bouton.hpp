#ifndef Bouton_hpp
#define Bouton_hpp

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <string>
#include <math.h>
#include <time.h>
#include <chrono>
#include <vector>
#include <iostream>
#include <random>
#include "Point.hpp"

using namespace std;

class Bouton{

private:
    Point center;
    int w;
    int h;
    Fl_Button *bouton;

public:
    Bouton(Point center, int w, int h, const char *nom);
    bool bouton_contains(Point p);
};

#endif