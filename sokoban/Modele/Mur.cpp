#include "Mur.hpp"

Mur::Mur(Point centre, int longueur, int largeur, int position): Cell(centre,longueur,largeur,position) {
    type = 'M';
    position_initiale = position;
    couleur = fl_rgb_color(96,96,96);
}

void Mur::draw(){
    fl_draw_box(FL_FLAT_BOX,centre.x-longueur/2,centre.y-largeur/2,longueur,largeur,couleur_contour);    
    fl_draw_box(FL_FLAT_BOX,centre.x-longueur/2+10,centre.y-largeur/2+10,longueur-20,largeur-20,couleur);
}