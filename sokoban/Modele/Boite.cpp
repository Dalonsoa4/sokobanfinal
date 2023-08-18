#include "Boite.hpp"

Boite::Boite(Point centre, int longueur, int largeur, int position): Cell(centre,longueur,largeur, position) {
    type = 'B';
    position_initiale = position;
    is_valide = false; 
    couleur = fl_rgb_color(184,134,11);
}

void Boite::draw(){
    if(is_valide)
    {
        fl_draw_box(FL_FLAT_BOX,centre.x-longueur/2,centre.y-largeur/2,longueur,largeur,FL_GREEN);    
        fl_draw_box(FL_FLAT_BOX,centre.x-longueur/2+10,centre.y-largeur/2+10,longueur-20,largeur-20,FL_GREEN);
    }
    else
    {
        fl_draw_box(FL_FLAT_BOX,centre.x-longueur/2,centre.y-largeur/2,longueur,largeur,couleur);    
        fl_draw_box(FL_FLAT_BOX,centre.x-longueur/2+10,centre.y-largeur/2+10,longueur-20,largeur-20,couleur_contour);
    }
}

void Boite::reset_objet(){
    is_bloquee = false;
    is_valide = is_valide_de_base;
}