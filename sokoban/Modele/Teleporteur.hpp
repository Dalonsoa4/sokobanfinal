#ifndef Teleporteur_hpp
#define Teleporteur_hpp

#include "Cell.hpp"

using namespace std;

class Teleporteur : public Cell
{

private:

    int compteur_marked = 0; // pour la recherche de chemin

    Fl_Color couleur_contour = FL_BLACK; 

    bool invisible = false;

public:

    Teleporteur(Point centre, int longueur, int largeur, int position);

    virtual ~Teleporteur(){};

    void draw() override;

    void set_marked(bool is_marked) override;

    bool get_marked() override;

    void reset_objet() override;
};

#endif