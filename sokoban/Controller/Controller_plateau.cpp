#include "Controller_plateau.hpp"

Controller_plateau::Controller_plateau(shared_ptr<Plateau> p_plateau){plateau = p_plateau;}  // On sauvegarde le pointeur


void Controller_plateau::bouge_joueur(int position_joueur, int mouvement){
    /*     
    int position_joueur : la position du joueur sur le plateau
    int mouvement : valeur calculée en fonction du plateau , pour savoir quel sera le décalage dans la grille
   */
   
    Cell *case_destination = plateau->grille[position_joueur + mouvement];

    // si la case destination est une boite. Le joueur marche pas sur la case de destination car c'était la boite (qui n'est donc plus la case adjacente)
    if (case_destination->get_type() == 'B'){

        Boite* boite = dynamic_cast<Boite*>(case_destination);

        if (boite->get_legere()){pousse_boite_legere(boite, mouvement);}

        else{pousse_boite(boite, mouvement);}

        joueur_marche(plateau->grille[position_joueur + mouvement]);
    } 

    else {joueur_marche(case_destination);}

    restaure_objectif(); // on vérifie après chaque mouvement

    restaure_teleporteur();       
}

void Controller_plateau::joueur_marche(Cell *case_destination){

    // si la case destination est vide, alors le joueur bouge
    if (case_destination->get_type() == '-'){plateau->swap(plateau->get_position_joueur(), case_destination->get_position());} 

    // si la case destination est un objectif
    if (case_destination->get_type() == 'O'){Objectif* destination = dynamic_cast<Objectif*>(case_destination); marche_sur_objectif(destination);} 

    // si la case destination est un teleporteur
    if (case_destination->get_type() == 'T'){Teleporteur* destination = dynamic_cast<Teleporteur*>(case_destination); marche_sur_teleporteur(destination);}
}

void Controller_plateau::pousse_boite(Boite *boite, int mouvement){

    /* Quand la case de destination est une boite , on la pousse en fonction de la destination de la boite */

    // facilité de lecture et ecriture
    int position_boite = boite->get_position();
    Cell *case_apres_boite = plateau->grille[boite->get_position() + mouvement];

    if (case_apres_boite->get_type() == '-'){ // si la case est vide

        if (boite->get_valide()){boite->set_valide(false); plateau->set_nombre_boite_valide(-1);} // si on bouge une boite validée

        plateau->swap(position_boite, case_apres_boite->get_position()); // on switch la case vide , avec la boite 

        if (plateau->get_type_initial(position_boite) == 'T'){restaure_teleporteur();} // Si jamais la boite était sur un téléporteur

        if (plateau->get_type_initial(position_boite) == 'O'){restaure_objectif();} // Si jamais la boite était sur un objectif
    }

    
    if (case_apres_boite->get_type() == 'O'){ // si la case est un objectif

        if (boite->get_valide()){boite->set_valide(false); plateau->set_nombre_boite_valide(-1);} // si on bouge une boite validée

        Objectif* objectif = dynamic_cast<Objectif*>(case_apres_boite);

        pousse_sur_objectif(boite, objectif);
    }    

    if (case_apres_boite->get_type() == 'T'){ // si la case est un teleporteur

        if (boite->get_valide()){boite->set_valide(false); plateau->set_nombre_boite_valide(-1);} // si on bouge une boite validée

        plateau->grille[case_apres_boite->get_position()]->set_type('-'); // on rend le teleporteur invisible (il devient une case vide)

        plateau->swap(position_boite, case_apres_boite->get_position()); // on switch le teleporteur , avec la boite 
    }

    plateau->boite_bloquee(boite); // regarde si le mouvement de la boite la rend bloquee ou bloque d'autres boites
}

void Controller_plateau::pousse_boite_legere(Boite *boite, int mouvement){

    /* Action lorsqu'on pousse une boite ou plusieurs boite legere */

    int nb_boite_legere = 1; // il y en a une au départ
    Boite* legere;
    bool breaking = false;

    while (plateau->grille[boite->get_position() + nb_boite_legere * mouvement]->get_type() == 'B' && !breaking){ // trouve le nombre de boite legere qui se suit

        Boite* legere = dynamic_cast<Boite*>(plateau->grille[boite->get_position() + nb_boite_legere * mouvement]);

        if (legere->get_legere()){nb_boite_legere++;}      
        else{breaking = true;} // quitter la boucle si c'est une boite non legere
    } 

    // pour chaque boite , on la pousse
    for (int i = 1; i <= nb_boite_legere; i++){

        legere = dynamic_cast<Boite*>(plateau->grille[boite->get_position() + (nb_boite_legere-i) * mouvement]);
        pousse_boite(legere, mouvement);
    }
}


void Controller_plateau::pousse_sur_objectif(Boite *boite , Objectif *objectif){

    /* Action lorsqu'on pousse une boite sur un objectif */

    if (objectif->get_couleur() == boite->get_couleur() || !plateau->partie_avec_couleur()) // si la partie est avec couleur , on vérifie
    {
        boite->set_valide(true);// la boite devient verte        

        plateau->set_nombre_boite_valide(1); // on incrémente le nombre de boite valide
    }

    objectif->set_type('-'); // on rend l'objectif invisible (il devient une case vide)

    plateau->objectif_perdu.push_back(objectif);    
    
    plateau->swap(boite->get_position(), objectif->get_position()); // on switch l'objectif , avec la boite 

    // gere le cas où un joueur pousse une boite qui était sur un tp , ou deux boites legeres qu'on pousse sur deux objectifs adjacents
    if (plateau->get_type_initial(objectif->get_position()) == 'T'){restaure_teleporteur();}
    if (plateau->get_type_initial(objectif->get_position()) == 'O'){restaure_objectif();}
}


void Controller_plateau::marche_sur_objectif(Objectif *objectif){

    /* Action quand le joueur marche sur l'objectif */

    objectif->set_type('-'); // on rend l'objectif invisible (il devient une case vide)

    plateau->objectif_perdu.push_back(objectif);
    
    plateau->swap(plateau->get_position_joueur(), objectif->get_position()); // on switch le joueur, avec l'objectif

}


void Controller_plateau::marche_sur_teleporteur(Teleporteur *teleporteur){

    /* Action quand le joueur marche sur un teleporteur */

    Teleporteur *teleporteur2 = plateau->teleporteur_correspondant(teleporteur);

    if (teleporteur2->get_type() != '-') // si il n'y a pas de boite dessus
    {
        plateau->grille[teleporteur2->get_position()]->set_type('-'); // on rend le teleporteur de destination invisible (il devient une case vide)
        
        plateau->swap(plateau->get_position_joueur(), teleporteur2->get_position()); // on switch le joueur, avec le teleporteur de destination
    }

    else // si jamais il y a une boite sur le teleporteur de destination
    {       
        teleporteur->set_type('-'); // on rend le teleporteur invisible (il devient une case vide)
        
        plateau->swap(plateau->get_position_joueur(), teleporteur->get_position()); // on switch le joueur, avec le teleporteur
    }
}



void Controller_plateau::restaure_objectif(){

    /*     
    Restaure les objectifs qui doivent se trouver en dessous d'une boite valide , si la case est libre
   */

    for (size_t i = 0; i < plateau->objectif_perdu.size(); i++)
    {           
        Objectif *objectif = plateau->objectif_perdu[i];

        if (plateau->grille[objectif->get_position_sous_boite()]->get_type() == '-') // si la case à la position initiale de l'objectif est vide
        {
            plateau->swap(objectif->get_position(), objectif->get_position_sous_boite());  // on swap les deux
            objectif->set_type('O');
            plateau->objectif_perdu.erase(plateau->objectif_perdu.begin() + i); // on retire l'objectif des perdus
        }        
    }   
}

void Controller_plateau::restaure_teleporteur(){

    /*     
    Restaure les teleporteurs qui ne sont pas à leur position initiale
   */

    for (size_t i = 0; i < plateau->liste_teleporteur.size(); i++)
    {   
        if (plateau->liste_teleporteur[i]->get_type() == '-') // si il est perdu
        {
            Cell *teleporteur = plateau->liste_teleporteur[i];

            if (plateau->grille[teleporteur->get_position_initiale()]->get_type() == '-') // si la case à la position initiale du teleporteur est vide
            {
                plateau->swap(teleporteur->get_position(), teleporteur->get_position_initiale());  // on swap les deux
                teleporteur->set_type('T');
            }
        }        
    }
}

void Controller_plateau::reset_plateau(){
  
    /* Remet tous les objets du plateau à leur place initiale */ 

    plateau->objectif_perdu.clear();

    for (size_t i = 0; i < plateau->grille.size(); i++)
    {
        // facilité de lecture
        Cell *objet_choisi = plateau->grille[i]; 

        if (objet_choisi->get_position() != objet_choisi->get_position_initiale()) // si la position de l'objet n'est pas la meme qu'initiale, on swap.
        {   
            Cell *objet_a_swap = plateau->grille[objet_choisi->get_position_initiale()];

            plateau->swap(objet_choisi->get_position(), objet_a_swap->get_position());

            i = i - 1; // on recommence sur la même case au cas où l'objet à swap n'est pas à son endroit initial            
        }

        objet_choisi->reset_objet();
    }

    for (size_t i = 0; i < plateau->objectif_deja_valide.size(); i++)
    {
        plateau->objectif_perdu.push_back(plateau->objectif_deja_valide[i]);
    }
       
}

void Controller_plateau::mouvement_click(Cell *destination){

    /* Déplace le joueur en fonction de la destination liée à un click */

    if (destination->get_type() == 'T'){joueur_marche(plateau->teleporteur_correspondant(destination));}
    else{joueur_marche(destination);}

    restaure_objectif(); // on vérifie après chaque mouvement
    restaure_teleporteur();            
}