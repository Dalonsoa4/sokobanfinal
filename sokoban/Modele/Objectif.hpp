#ifndef Objectif_hpp
#define Objectif_hpp

#include "Cell.hpp"

using namespace std;

class Objectif : public Cell
{
private:

    int position_sous_boite;
    Fl_Color couleur_contour = fl_rgb_color(205,92,92); 

public:

    Objectif(Point centre, int longueur, int largeur, int position);

    virtual ~Objectif(){};

    void set_positions_objectif_valide(int p_boite, int p_initiale) {position_sous_boite = p_boite; position_initiale = p_initiale;}
    // quand une partie commence avec une boite sur un objectif (valide donc)

    int get_position_sous_boite() {return position_sous_boite;}

    void draw() override;

    void reset_objet() override;
};

#endif