#ifndef Partie_hpp
#define Partie_hpp

#include "Modele/Plateau.hpp"
#include "Vue/Affichage_partie.hpp"
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <iostream>
#include <memory>

using namespace std;

class Partie
{
    public:
    shared_ptr<Plateau> modele; // plateau           
    Affichage_partie *vue;                    

    Partie(int mum_plateau);
};

#endif