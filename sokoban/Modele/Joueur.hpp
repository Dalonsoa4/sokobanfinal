#ifndef Joueur_hpp
#define Joueur_hpp

#include "Cell.hpp"

using namespace std;

class Joueur : public Cell
{

private:

    Fl_Color couleur_contour = fl_rgb_color(0,0,255);

public:

    Joueur(Point centre, int longueur, int largeur, int position);

    virtual ~Joueur(){};

    void draw() override;
};

#endif