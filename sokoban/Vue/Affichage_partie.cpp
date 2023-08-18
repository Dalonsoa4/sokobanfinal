#include "Affichage_partie.hpp"

Affichage_partie::Affichage_partie(shared_ptr<Plateau> plateau) : Fl_Window(500, 500, 1600, 1000, "Partie") {

    plateau_affichage = plateau;                                      // on sauvegarde le pointeur du plateau pour pouvoir le draw
    controller = make_shared<Controller_partie>(plateau_affichage) ;  // on le passe au controller

    reset_plateau = new Bouton({1000, 800}, 500, 100, "Recommencer la partie");
    reset_meilleur_score = new Bouton({1000, 650}, 500, 100, "Reinitialiser le score du plateau");

    Fl::add_timeout(1.0 / 60, Timer_CB, this);
    resizable(this);
    this->show();

    //
}


void Affichage_partie::draw(){

    Fl_Window::draw();

    // dessine toutes les cellules du plateau
    // auto pour déclarer une variable dont le type est automatiquement déduit. utile car on draw des objets different
    for (auto &c:plateau_affichage->grille){c->draw();};

    draw_information("Compteur de pas : " + to_string(controller->get_compteur_pas()), 100, FL_BLACK);
  
    draw_information("Meilleur score : " + to_string(controller->get_meilleur_score()), 200, FL_BLACK);

    draw_information("Pas restant : " + to_string(controller->get_limite_pas() - controller->get_compteur_pas()), 300, FL_BLACK);

    if(controller->get_end_game()){message_fin(controller->get_gagne());}
}

void Affichage_partie::Timer_CB(void *userdata) {
    /* code provenant des labos, fonction qui raffraichit périodiquement la fenetre */
    Affichage_partie *o = static_cast<Affichage_partie *>(userdata);
    o->redraw();
    Fl::repeat_timeout(1.0 / 60, Timer_CB, userdata);
}

int Affichage_partie::handle(int event){
    // event sur la fenetre , click ou clavier
    controller->processEvent(event, reset_plateau, reset_meilleur_score); 
    return 0;
}


void Affichage_partie::draw_information(string info, int position_y, Fl_Color couleur){
    /* Dessine les informations de la partie*/

    fl_color(couleur);
    fl_font(FL_HELVETICA, 50);
    fl_draw(info.c_str(), info.size(), 1000, position_y); // c_str est pour donner un pointeur vers un string
}

void Affichage_partie::message_fin(bool gagne){
    /* Affiche le message de fin de partie*/
    
    if (gagne){draw_information("Gagné en " + to_string(controller->get_compteur_pas_gagnant()) + " pas !", 500, FL_RED);}
    else{draw_information("Perdu !", 500, FL_RED);}
}