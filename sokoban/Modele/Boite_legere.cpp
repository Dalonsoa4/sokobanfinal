#include "Boite_legere.hpp"

Boite_legere::Boite_legere(Point centre, int longueur, int largeur, int position): Boite(centre,longueur,largeur, position) {legere = true;}

void Boite_legere::draw(){

    if(is_valide)
    {
        fl_draw_box(FL_FLAT_BOX,centre.x-longueur/4,centre.y-largeur/4,(longueur/2),(largeur/2),FL_GREEN);    
        fl_draw_box(FL_FLAT_BOX,centre.x-longueur/4+10,centre.y-largeur/4+10,(longueur/2)-20,(largeur/2)-20,FL_GREEN);
    }
    else
    {
        fl_draw_box(FL_FLAT_BOX,centre.x-longueur/4,centre.y-largeur/4,(longueur/2),(largeur/2),couleur);    
        fl_draw_box(FL_FLAT_BOX,centre.x-longueur/4+10,centre.y-largeur/4+10,(longueur/2)-20,(largeur/2)-20,couleur_contour);
    }
}