#ifndef Controller_plateau_hpp
#define Controller_plateau_hpp

#include "../Modele/Plateau.hpp"
#include <memory>
/*     
Classe qui gère toutes les actions liées au plateau
*/

using namespace std;



class Controller_plateau{

 private:

  shared_ptr<Plateau> plateau;
  
 public:

  Controller_plateau(shared_ptr<Plateau> p_plateau);

  void bouge_joueur(int position_joueur, int mouvement);

  void joueur_marche(Cell *case_destination);

  void pousse_boite(Boite *boite, int mouvement);

  void pousse_boite_legere(Boite *boite, int mouvement);

  void marche_sur_objectif(Objectif *objectif);

  void pousse_sur_objectif(Boite *boite , Objectif *objectif);

  void marche_sur_teleporteur(Teleporteur *teleporteur);

  void restaure_objectif();

  void restaure_teleporteur();

  void reset_plateau();

  void mouvement_click(Cell *destination);
};

#endif