#include "Objectif.hpp"

Objectif::Objectif(Point centre, int longueur, int largeur, int position): Cell(centre,longueur,largeur, position) {
    type = 'O';
    position_initiale = position;
    position_sous_boite = position;         // est modifie si une boite commence la partie sur un objectif
    couleur = fl_rgb_color(240,128,128);
}

void Objectif::draw(){
    //image->draw(centre.x-longueur/2,centre.y-largeur/2,longueur,largeur);
    if(type != '-'){
        fl_color(couleur);
        fl_begin_polygon();
        fl_circle(centre.x, centre.y, 18);
        fl_color(couleur_contour);
        fl_circle(centre.x, centre.y, 9);
    }

    //fl_draw_box(fl_circle(centre.x-longueur/2,centre.y-largeur/2,longueur));  
    //fl_draw_box(FL_FLAT_BOX,centre.x-longueur/2+10,centre.y-largeur/2+10,longueur-20,largeur-20,fl_rgb_color(218,165,32));
}

void Objectif::reset_objet(){
    if (position_initiale == position_sous_boite){type = 'O';}
    else{type = '-';}
}