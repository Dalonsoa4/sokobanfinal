#include "Joueur.hpp"

Joueur::Joueur(Point centre, int longueur, int largeur, int position): Cell(centre,longueur,largeur, position) {
    type = 'J';
    position_initiale = position;
    couleur = fl_rgb_color(65,105,225);
}

void Joueur::draw(){
    fl_color(couleur_contour);
    fl_begin_polygon();
    fl_circle(centre.x, centre.y, 30);
    fl_color(couleur);
    fl_circle(centre.x, centre.y, 20);
}