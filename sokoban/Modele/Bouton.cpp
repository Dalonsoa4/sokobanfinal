#include "Bouton.hpp"

    Bouton::Bouton(Point center, int w, int h, const char* nom) : center{center}, w{w}, h{h} {
        bouton = new Fl_Button(center.x, center.y, w, h, nom);
    }

    bool Bouton::bouton_contains(Point p){ // code repris des labos
    return p.x >= (center.x + w / 2) - w / 2 && p.x < (center.x + w / 2) + w / 2 && p.y >= (center.y + h / 2) - h / 2 && p.y < (center.y + h / 2) + h / 2;
    } 