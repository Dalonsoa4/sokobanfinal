#include "Cell.hpp"

Cell::Cell(Point centre, int longueur, int largeur, int position):
centre{centre}, longueur{longueur}, largeur{largeur}, position{position}{position_initiale = position;}

bool Cell::contains(Point p){ // code provenant des labos , pour determiner si click sur une cell
    return p.x>=centre.x-largeur/2 &&
        p.x<centre.x+largeur/2 &&
        p.y>=centre.y-longueur/2 &&
        p.y<centre.y+longueur/2;
}