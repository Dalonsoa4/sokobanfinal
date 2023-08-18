#ifndef Mur_hpp
#define Mur_hpp


#include "Point.hpp"
#include <FL/Fl.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/fl_draw.H>
#include "Cell.hpp"

using namespace std;

class Mur : public Cell
{

private:

    Fl_Color couleur_contour = fl_rgb_color(32,32,32);

public:

    Mur(Point centre, int longueur, int largeur, int position);

    virtual ~Mur(){};

    void draw() override;
};

#endif