#ifndef Affichage_menu_hpp
#define Affichage_menu_hpp

#include <FL/Fl_PNG_Image.H>
#include <FL/fl_draw.H>
#include "Affichage_selection.hpp"

using namespace std;

/*
  Classe qui affiche le menu
*/

class Affichage_menu : public Fl_Window {

  private:
    Bouton *quitter;
    Bouton *jouer;
    Fl_PNG_Image* image_accueil = new Fl_PNG_Image("Vue/accueil.png");
    
  public:

    Affichage_menu();

    void draw() override;
    int handle(int event) override;

    static void Timer_CB(void *userdata);

    void push(Point p);

    int selection_niveau();
};

#endif