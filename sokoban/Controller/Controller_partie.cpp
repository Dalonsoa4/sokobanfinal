#include "Controller_partie.hpp"

Controller_partie::Controller_partie(shared_ptr<Plateau> p_plateau){

    controller_plateau = new Controller_plateau(p_plateau);

    plateau = p_plateau; // on sauvegarde le pointeur pour qu'il aie aussi accès aux attributs du plateau

    string nom_fichier = "Plateaux/statplateau"+to_string(plateau->get_numero())+".txt";

    ifstream fichier(nom_fichier);  // ouvert en lecture uniquement

    string ligne;

    getline(fichier, ligne); // ligne 1 : meilleur score

    meilleur_score = stoi(ligne);   // converti le string en int

    getline(fichier, ligne); // ligne 1 : meilleur score

    limite_pas = stoi(ligne);   // converti le string en int

    fichier.close();
}


void Controller_partie::bouge_joueur(string direction){

    int position_joueur = plateau->get_position_joueur();

    controller_plateau->bouge_joueur(plateau->get_position_joueur(),plateau->valeur_mouvement(direction));

    if (position_joueur != plateau->get_position_joueur()){compteur_pas++;} // gère le cas où l'input ne bouge pas le joueur

    if(end_game()){reset_partie();} // si le jeu est fini , on réinitialise tout
}

void Controller_partie::reset_partie(){
    /* recommence la partie */

    if (gagne && compteur_pas < meilleur_score){ maj_meilleur_score(compteur_pas);} 

    plateau->reset_compteur();
    compteur_pas = 0;
    controller_plateau->reset_plateau();    
}

bool Controller_partie::end_game(){
    /* regarde si la partie est finie*/ 

    end = false;
    gagne = false;

    if (plateau->get_nombre_objectif() == plateau->get_nombre_boite_valide()){end = true; gagne = true;}
    if ((plateau->get_nombre_boite() - plateau->get_nombre_boite_bloquee()) == 0){end = true;} 
    if ((limite_pas - compteur_pas) == 0){end = true;}   
    if (gagne){compteur_pas_gagnant = compteur_pas;} 

    return end;
}

void Controller_partie::event_click(Point p){

    int destination = destination_click(p); // trouve l'index dans la grille du click
        
    int profondeur = longueur_chemin(destination); // trouve la distance entre la position du joueur et la destination

    if (profondeur > 0 && ((limite_pas - compteur_pas) - profondeur) >= 0)
    {
        controller_plateau->mouvement_click(plateau->grille[destination]);  
        compteur_pas += profondeur;    
    }

    if(end_game()){reset_partie();} // si le jeu est fini , on réinitialise tout et on maj le score
}

int Controller_partie::destination_click(Point p){

    /* Inteprete le Point liée au click afin de retourner la destination souhaitée */

    int destination = 0;

    for (auto &c:plateau->grille)
    {
        if (c->contains(p)){destination = c->get_position();}
    }

    // gère le cas où le joueur est sur un tp , et que sa destination est son téléporteur correspondant
    if (plateau->grille[destination]->get_type() == 'T')
    {
        // Si le teleporteur est bloqué par quelque chose alors il ne se passe rien
        if (plateau->teleporteur_correspondant(plateau->grille[destination])->get_type() != 'T'){destination = plateau->get_position_joueur();}
        
        else{destination = plateau->teleporteur_correspondant(plateau->grille[destination])->get_position();}
    }
    
    return destination;
}

int Controller_partie::longueur_chemin(int destination){

    /* Calcule la longeur du chemin possible entre la position du joueur et la destination demandée */

    int profondeur = 0;
    int limite = plateau->get_taille(); // limite de taille du chemin pourrait etre + petite pour + performant

    if (plateau->grille[destination]->get_type() != 'B' && plateau->grille[destination]->get_type() != 'M' && plateau->grille[destination]->get_type() != 'L')
    {
        while (plateau->chemin_possible(plateau->get_position_joueur(), destination, profondeur) == false && profondeur != limite) //Backtracking avec profondeur limitee incrementale 
        {
            profondeur++;
        }
    }

    // on supprime la trace du chemin de notre backtracking
    // Si plateau enorme ça serait + performant de placer le chemin dans un vecteur plutot que parcourir le plateau
    for (auto &c:plateau->grille)
    {
        if (c->get_type() != 'B' && c->get_type() != 'M' && c->get_type() != 'L'){c->set_marked(false);}        
    }
    if(profondeur == limite){profondeur = 0;} // prondeur = limite -> pas de chemin possible
    
    return profondeur;
}

void Controller_partie::maj_meilleur_score(int score){

    string nom_fichier = "Plateaux/statplateau"+to_string(plateau->get_numero())+".txt"; // ouvre le fichier en mode écriture (formate le contenu existant)

    ofstream fichier(nom_fichier);

    fichier << score << "\n";  // écrit le meilleur score dans le fichier

    fichier << limite_pas;  // réecrit la limite de pas pour ce niveau

    fichier.close();

    meilleur_score = score;
}

bool Controller_partie::processEvent(int event, Bouton *reset_plateau, Bouton *reset_meilleur_score){
    /* Recoit l'event ainsi que les boutons de la part de la vue*/
    
    int key = Fl::event_key();
    switch (event) { // code a moitie repris des labos
        case FL_PUSH:

        if (reset_plateau->bouton_contains(Point{Fl::event_x(),Fl::event_y()})){reset_partie();} // Click sur le bouton reset

        else if (reset_meilleur_score->bouton_contains(Point{Fl::event_x(),Fl::event_y()})){maj_meilleur_score(10000);} // score tres grand pour reinitialiser

        else{event_click(Point{Fl::event_x(),Fl::event_y()});} // clique sur le plateau pour se déplacer

        break;
        case FL_KEYDOWN:

        if (key == FL_Up) {bouge_joueur("haut");} 
        else if (key == FL_Down) {bouge_joueur("bas");} 
        else if (key == FL_Left) {bouge_joueur("gauche");} 
        else if (key == FL_Right) {bouge_joueur("droite");}

        break;

        default:
        return 0;
    }
return 0;
}