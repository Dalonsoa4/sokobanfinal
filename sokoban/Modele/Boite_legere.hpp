#ifndef Boite_legere_hpp
#define Boite_legere_hpp

#include "Boite.hpp"

using namespace std;

class Boite_legere : public Boite
{

private:

    Fl_Color couleur_contour = fl_rgb_color(218,165,32); 

public:

    Boite_legere(Point centre, int longueur, int largeur, int position);

    virtual ~Boite_legere(){};

    void draw() override;
};

#endif