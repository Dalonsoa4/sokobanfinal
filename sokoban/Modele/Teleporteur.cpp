#include "Teleporteur.hpp"

Teleporteur::Teleporteur(Point centre, int longueur, int largeur, int position): Cell(centre,longueur,largeur, position) {
    type = 'T';
    position_initiale = position;
    couleur = FL_BLACK;
    is_marked = false;
}

void Teleporteur::draw(){
    if(type != '-'){
        fl_color(couleur);
        fl_begin_polygon();
        fl_circle(centre.x, centre.y, 36);
    }
}

void Teleporteur::set_marked(bool marked){
// utile pour la recherche de chemin
    if(marked){compteur_marked++;}
    else{compteur_marked--;}
}

bool Teleporteur::get_marked(){
    // utile pour la recherche de chemin
    if (compteur_marked > 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Teleporteur::reset_objet(){
    type = 'T';
    compteur_marked = 0;
    is_marked = false;
}