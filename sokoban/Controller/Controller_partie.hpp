#ifndef Controller_partie_hpp
#define Controller_partie_hpp

#include "Controller_plateau.hpp"
#include "../Modele/Bouton.hpp"
#include <iostream>

/*     
Classe qui gère la partie 
*/

using namespace std;

class Controller_partie{

 private:
 
  Controller_plateau *controller_plateau;

  shared_ptr<Plateau> plateau;

  int compteur_pas = 0;
  int compteur_pas_gagnant;
  int meilleur_score;
  int limite_pas;
  bool end = false;
  bool gagne = false;

 public:

  Controller_partie(shared_ptr<Plateau> p_plateau);

  bool processEvent(int event, Bouton *reset_plateau, Bouton *reset_meilleur_score);

  void bouge_joueur(string direction);

  void reset_partie();

  void event_click(Point p);

  int destination_click(Point p);

  int longueur_chemin(int destination);

  void maj_meilleur_score(int score);

  // getters

  int get_compteur_pas(){return compteur_pas;}

  int get_compteur_pas_gagnant(){return compteur_pas_gagnant;}

  int get_meilleur_score(){return meilleur_score;}

  int get_limite_pas(){return limite_pas;}

  bool get_end_game(){return end;}

  bool get_gagne(){return gagne;}

  bool end_game();
};

#endif
