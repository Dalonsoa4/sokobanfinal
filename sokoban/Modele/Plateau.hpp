#ifndef Plateau_hpp
#define Plateau_hpp

#include "Cell.hpp"
#include "Point.hpp"
#include "Mur.hpp"
#include "Boite.hpp"
#include "Objectif.hpp"
#include "Joueur.hpp"
#include "Teleporteur.hpp"
#include "Boite_legere.hpp"
#include <vector>
#include <unistd.h>  
#include <iostream>
#include <fstream>
#include <math.h>


using namespace std;

/* Liste caractères : types | couleurs defaut 

        M : mur  
        - : case vide
        B : boite                   | brun |   
        J : joueur                  | bleu |  
        L : boite legere            | brun |   
        O : objectif                | rouge| 
        T : Teleporteur             | noir |

*/

/* classe qui modelise le plateau de jeu */

class Plateau
{
    private:

    int nombre_objet; // le nombre d'objet dans le plateau  
    int nombre_boite = 0;
    int nombre_boite_valide = 0;
    int nombre_boite_valide_de_base = 0;
    int nombre_boite_bloquee = 0;
    int nombre_objectif = 0;
    int numero_plateau;
    int taille_plateau;

    bool avec_couleur = false;

    Joueur *j1;

    vector<int> mouvement_possible;
    vector<string> terrain;

    public:

    vector<Cell*> grille;
    vector<Objectif*> objectif_perdu;
    vector<Objectif*> objectif_deja_valide;
    vector<Teleporteur*> liste_teleporteur;

    Plateau(int numero);

    void analyse_fichier_terrain();

    void creation_terrain();

    Fl_Color couleur_associee(char couleur);

    void swap(int position1, int position2);
    
    Teleporteur* teleporteur_correspondant(Cell* teleporteur);

    bool chemin_possible(int position_joueur, int destination, int profondeur_max);

    bool boite_bloquee(Cell *b);

    void boite_deja_valide(Boite *b, Objectif *objectif_correspondant);

    int valeur_mouvement(string direction);

    void reset_compteur();

    // getters
    char get_type_initial(int position){return terrain[position][0];}

    int get_numero(){return numero_plateau;}

    bool partie_avec_couleur(){return avec_couleur;}

    int get_taille(){return nombre_objet;}

    int get_nombre_boite_valide(){return nombre_boite_valide;}

    int get_nombre_boite(){return nombre_boite;}

    int get_nombre_objectif(){return nombre_objectif;}

    int get_nombre_boite_bloquee(){return nombre_boite_bloquee;}

    int get_position_joueur(){return j1->get_position();}

    //setters

    void set_nombre_boite_valide(int i){nombre_boite_valide += i;}
};

#endif