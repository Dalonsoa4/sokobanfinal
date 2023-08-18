#ifndef Affichage_partie_hpp
#define Affichage_partie_hpp

#include "../Modele/Plateau.hpp"
#include "../Controller/Controller_partie.hpp"
#include "../Modele/Bouton.hpp"
#include <FL/Fl_Double_Window.H>
#include <iostream>
#include <memory>

/*
  Classe qui affiche la partie
*/

class Affichage_partie : public Fl_Window {

  private:
    shared_ptr<Controller_partie> controller; 

    shared_ptr<Plateau> plateau_affichage;

    Bouton *reset_plateau;
    Bouton *reset_meilleur_score;

    bool resultat_affiche = false;

  public:

    Affichage_partie(shared_ptr<Plateau> plateau);

    void draw() override ;

    void draw_information(string info, int position_y, Fl_Color couleur);

    void message_fin(bool gagne);

    static void Timer_CB(void *userdata);

    int handle(int event) override;
};

#endif