#include "Partie.hpp"

Partie::Partie(int num_plateau){

   modele = make_shared<Plateau>(num_plateau);
   vue = new Affichage_partie(modele);
}