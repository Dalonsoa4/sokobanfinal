#ifndef Affichage_selection_hpp
#define Affichage_selection_hpp

#include "../Partie.hpp"

using namespace std;

/*
  Classe qui affiche la selection de niveau
*/

class Affichage_selection : public Fl_Window {

  private:
  
        Bouton *plateau1;
        Bouton *plateau2;
        Bouton *plateau3;
  public:

        Affichage_selection();

        void draw() override;

        int handle(int event);

        static void Timer_CB(void *userdata);

        void selectionne(Point p);

        int partie(int num_plateau);
};

#endif