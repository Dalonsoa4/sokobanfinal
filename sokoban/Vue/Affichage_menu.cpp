#include "Affichage_menu.hpp"

Affichage_menu::Affichage_menu() : Fl_Window(500, 500, 1000, 1000, "Menu principal"){

    Fl_Box box(800,500,200,200);     // widget qui va contenir l'image
    Fl::add_timeout(1.0 / 60, Timer_CB, this);
    resizable(this);

    jouer = new Bouton({200, 650}, 600, 100, "Jouer");
    quitter = new Bouton({200, 800}, 600, 100, "Quitter le jeu");

    this->show();
}



void Affichage_menu::draw(){

    Fl_Window::draw();
    string s = "David Alonso";
    fl_color(FL_BLACK);
    fl_font(FL_HELVETICA, 50);
    
    fl_draw(s.c_str(), s.size(), 50, 50); // c_str est pour donner un pointeur vers un string
    image_accueil->draw(200, 50, 600, 600);
}

int Affichage_menu::handle(int event){
    /* regarde à chaque clic , si la zone du click est sur un bouton */
    switch (event) {
        case FL_PUSH:
            push(Point{Fl::event_x(),Fl::event_y()});
            return 1;                   
        }
    return 0;
}


 void Affichage_menu::Timer_CB(void *userdata){
    /* code provenant des labos, fonction qui raffraichit périodiquement la fenetre */
    Affichage_menu *o = (Affichage_menu*) userdata;
    o->redraw();
    Fl::repeat_timeout(60, Timer_CB, userdata);
}


void Affichage_menu::push(Point p){

    /* si click sur le bouton quitter, quitte le jeu */
    if (quitter->bouton_contains(p)){ exit(0);}
    else if (jouer->bouton_contains(p)){selection_niveau();}
}

int Affichage_menu::selection_niveau(){
    /* Passe à la page de séléction de niveau */

    Affichage_selection selection;
    this->hide(); // on ferme la fenetre
    return Fl::run();
}