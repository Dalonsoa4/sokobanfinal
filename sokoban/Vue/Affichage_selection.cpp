#include "Affichage_selection.hpp"

Affichage_selection::Affichage_selection() : Fl_Window(500, 500, 1000, 1000, "Selection niveaux"){

    Fl::add_timeout(1.0 / 60, Timer_CB, this);
    resizable(this);

    plateau1 = new Bouton({200, 700}, 600, 100, "Niveau 1");
    plateau2 = new Bouton({200, 500}, 600, 100, "Niveau 2");
    plateau3 = new Bouton({200, 300}, 600, 100, "Niveau 3");

    this->show();
}



void Affichage_selection::draw()  {
    Fl_Window::draw();
}


int Affichage_selection::handle(int event)  {
    /* regarde à chaque clic , si la zone du click est sur un bouton */
    switch (event) {
        case FL_PUSH:
            selectionne(Point{Fl::event_x(),Fl::event_y()});
            return 1;                   
        }
    return 0;
}

void Affichage_selection::Timer_CB(void *userdata) {
    /* code provenant des labos, fonction qui raffraichit périodiquement la fenetre */
    Affichage_selection *o = (Affichage_selection*) userdata;
    o->redraw();
    Fl::repeat_timeout(60, Timer_CB, userdata);
}


void Affichage_selection::selectionne(Point p){
    /* lance la partie correspondante au niveau séléctionné */    

    if (plateau1->bouton_contains(p)){partie(1);}
    else if (plateau2->bouton_contains(p)){partie(2);}
    else if (plateau3->bouton_contains(p)){partie(3);}
}

int Affichage_selection::partie(int num_plateau){
    /* Passe à la partie */
    
    Partie partie(num_plateau);
    return Fl::run();
}