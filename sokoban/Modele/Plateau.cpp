#include "Plateau.hpp"

Plateau::Plateau(int numero){

    numero_plateau = numero;
    
    analyse_fichier_terrain();
    creation_terrain();
}


void Plateau::creation_terrain(){

    int x;
    int y;
    int taille_objet = 90;
    int n = int(sqrt(nombre_objet)); // nombre d'élément dans une ligne ou colonne 

    for (int position = 0; position < nombre_objet; position++)
    {
        // Position dessiné dans la fenetre
        x  = taille_objet * (position % n) + 81; 
        y  = taille_objet * (position / n) + 81;

        // Murs
        if(terrain[position][0] == 'M'){grille.push_back(new Mur{Point{x, y}, taille_objet, taille_objet, position});}

        // Joueurs
        if(terrain[position][0] == 'J'){j1 = new Joueur{Point{x, y}, taille_objet, taille_objet, position}; grille.push_back(j1);}

        // Objectif
        if(terrain[position][0] == 'O'){
            Objectif *objectif = new Objectif{Point{x, y}, taille_objet, taille_objet, position};
            if(terrain[position].size() > 1){objectif->set_couleur(couleur_associee(terrain[position][1]));}
            grille.push_back(objectif);
            nombre_objectif++;
        }

        // Boite
        if(terrain[position][0] == 'B'){
            Boite *boite = new Boite{Point{x, y}, taille_objet, taille_objet, position};
            if(terrain[position].size() > 1 && terrain[position][1] != ' '){boite->set_couleur(couleur_associee(terrain[position][1]));}
            if(terrain[position].size() > 2){Objectif *objectif = new Objectif{Point{x, y}, taille_objet, taille_objet, position};boite_deja_valide(boite, objectif);}
            grille.push_back(boite);
            nombre_boite ++;            
        }

        // Boite legere
        if(terrain[position][0] == 'L'){
            Boite_legere *boite_legere = new Boite_legere{Point{x, y}, taille_objet, taille_objet, position};
            if(terrain[position].size() > 1 && terrain[position][1] != ' '){boite_legere->set_couleur(couleur_associee(terrain[position][1]));}
            if(terrain[position].size() > 2){Objectif *objectif = new Objectif{Point{x, y}, taille_objet, taille_objet, position};boite_deja_valide(boite_legere, objectif);}
            grille.push_back(boite_legere);
            nombre_boite ++;            
        }

        // Teleporteur
        if(terrain[position][0] == 'T'){
            Teleporteur *teleporteur = new Teleporteur{Point{x, y}, taille_objet, taille_objet, position};
            if(terrain[position].size() > 1){teleporteur->set_couleur(couleur_associee(terrain[position][1]));}
            grille.push_back(teleporteur);
            liste_teleporteur.push_back(teleporteur);       
        }

        // Vide
        if(terrain[position][0] == '-'){grille.push_back(new Cell{Point{x, y}, taille_objet, taille_objet, position});}
    };

    mouvement_possible = {1,-1,int(sqrt(nombre_objet)),-int(sqrt(nombre_objet))}; // respectivement droite,gauche,bas,haut
}


void Plateau::swap(int position1, int position2){

    /* Echange deux éléments dans la grille en fonction de leur position */
        Point new_centre;
        int new_position;
        std::swap(grille[position1], grille[position2]);

        new_centre = grille[position2]->get_centre();
        new_position = grille[position2]->get_position();
        // switch positions 
        grille[position2]->set_position(grille[position1]->get_centre());
        grille[position1]->set_position(new_centre);
        // switch position dans la grille
        grille[position2]->set_position(grille[position1]->get_position());
        grille[position1]->set_position(new_position);
}


Teleporteur* Plateau::teleporteur_correspondant(Cell* teleporteur){

    /* Regarde le teleporteur donné en paramètre , et renvoie le teleporteur correspondant (de même couleur)*/

    Teleporteur* teleporteur_correspondant;

    for (size_t i = 0; i < liste_teleporteur.size(); i++)
    {
        // si ils ont la meme couleur et une position differente
        if (liste_teleporteur[i]->get_couleur() == teleporteur->get_couleur() && liste_teleporteur[i]->get_position() != teleporteur->get_position())
        {
            teleporteur_correspondant = liste_teleporteur[i];
            i = liste_teleporteur.size(); // on arrête la boucle
        }
        
    }

    return teleporteur_correspondant;   
}

Fl_Color Plateau::couleur_associee(char couleur){
    /* retourne la couleur associée a un char donné*/
    Fl_Color couleur_associee;
    if (couleur == 'w'){couleur_associee = FL_WHITE;}
    if (couleur == 'y'){couleur_associee = FL_YELLOW;}
    if (couleur == 'r'){couleur_associee = FL_RED;}
    if (couleur == 'b'){couleur_associee = FL_BLACK;}

    return couleur_associee;
}

bool Plateau::chemin_possible(int position_joueur, int destination, int distance_max){

    /* Backtracking récursif qui renvoie vrai si il existe un chemin d'une distance maximum donnée 
       entre la position du joueur et la destination. */

    if (grille[position_joueur]->get_marked() || distance_max < 0){return false;}

    else if (position_joueur == destination){return true;}

    grille[position_joueur]->set_marked(true); // pour éviter de reprendre un meme chemin

    distance_max-- ;

    for (size_t i = 0; i < 4; i++)
    {
        int voisin = position_joueur + mouvement_possible[i];
        
        // si la case voisine est accessible
        if (grille[voisin]->get_marked() == false && grille[voisin]->get_type() != 'B' && grille[voisin]->get_type() != 'M' && grille[voisin]->get_type() != 'L')
        {
            if (grille[voisin]->get_type() == 'T'){voisin = teleporteur_correspondant(grille[voisin])->get_position();}
            
            if (chemin_possible(voisin,destination, distance_max)){return true;}   // plonge dans la récursion
        }    
    }

    distance_max++ ;

    grille[position_joueur]->set_marked(false);      

    return false;
}

bool Plateau::boite_bloquee(Cell *b){

    /* verifie si le mouvement d'une boite entraine un blocage d'une ou plusieurs boite */

    Boite* boite = dynamic_cast<Boite*>(b); 
    bool bloquee = false;
    
    if (!boite->get_bloquee())
    {
        int bloque_vertical = 0;
        int bloque_horizontal = 0;
        char type = boite->get_type();

        int position_boite = boite->get_position();

        Cell *haut_voisin = grille[position_boite + valeur_mouvement("haut")];
        Cell *bas_voisin = grille[position_boite + valeur_mouvement("bas")];
        Cell *gauche_voisin = grille[position_boite + valeur_mouvement("gauche")];
        Cell *droite_voisin = grille[position_boite + valeur_mouvement("droite")];

        boite->set_type('M'); // elle devient un mur du point de vue d'une possible autre boite (pour la recursion)

        if (droite_voisin->get_type() == 'M' || (droite_voisin->get_type() == 'B' && boite_bloquee(droite_voisin))){bloque_horizontal++;}
        if (gauche_voisin->get_type() == 'M' || (gauche_voisin->get_type() == 'B' && boite_bloquee(gauche_voisin))){bloque_horizontal++;}
        if (haut_voisin->get_type() == 'M' || (haut_voisin->get_type() == 'B' && boite_bloquee(haut_voisin))){bloque_vertical++;}
        if (bas_voisin->get_type() == 'M' || (bas_voisin->get_type() == 'B' && boite_bloquee(bas_voisin))){bloque_vertical++;}

        if (bloque_horizontal * bloque_vertical > 0){bloquee = true; this->nombre_boite_bloquee++; boite->set_bloquee(true);}

        boite->set_type(type); // elle "redevient" une boite pas bloquee
    }

    else{bloquee = true;}
       
    return bloquee;
}

int Plateau::valeur_mouvement(string direction){
    /* retourne la valeur entiere sur le plateau d'un mouvement */
    int valeur;
    
    if(direction == "haut"){valeur = -int(sqrt(nombre_objet));}
    if(direction == "bas"){valeur = int(sqrt(nombre_objet));}
    if(direction == "droite"){valeur = 1;}
    if(direction == "gauche"){valeur = -1;}

    return valeur;
}


void Plateau::boite_deja_valide(Boite *b, Objectif *objectif_correspondant){
    /* gère le cas où on commence une partie avec une boite deja valide */

    b->set_valide(true);
    b->set_valide_de_base(true);
    nombre_boite_valide_de_base++;

    int index_case_libre;
    int pas = objectif_perdu.size(); // Evite de selectionner une case libre qui contient déjà un objectif perdu (cas où plusieurs boites valide au demarrage)

    for (int i = 0; i < nombre_objet; i++)
    {
        if (grille[i]->get_type() == '-')
        {
            if (pas == 0){index_case_libre = i; i = nombre_objet;}  // trouve l'index et arrete la boucle
            else{pas--;}           
        }     
    }

    if(partie_avec_couleur()){objectif_correspondant->set_couleur(b->get_couleur());}
    objectif_correspondant->set_type('-');
    objectif_correspondant->set_positions_objectif_valide(b->get_position(), index_case_libre);

    objectif_perdu.push_back(objectif_correspondant);
    objectif_deja_valide.push_back(objectif_correspondant);
    grille.push_back(objectif_correspondant); // on l'ajoute à la fin du vecteur
    swap(index_case_libre, grille.size()-1); // on swap avec la case libre

    delete(grille[grille.size()]);
    grille.pop_back();

    nombre_boite_valide ++;
    nombre_objectif++;
}


void Plateau::analyse_fichier_terrain(){
    /* analyse le fichier texte comprenant les infos pour faire le plateau */

    //if (fichier.is_open()) {std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;}

    string nom_fichier = "Plateaux/plateau"+to_string(numero_plateau)+".txt";

    ifstream fichier(nom_fichier);  // ouvert en lecture uniquement

    string ligne;

    string objet;

    getline(fichier, ligne); // ligne 1 : taille du plateau

    nombre_objet = stoi(ligne); // converti le string en int

    getline(fichier, ligne);  // ligne 2 : couleur ou non

    if (ligne == "oui"){avec_couleur = true;}

    getline(fichier, ligne); // ligne 3 : plateau

    for (long unsigned int i = 0; i < ligne.size(); i++)
    {
        if (ligne[i] == '|')
        {
            terrain.push_back(objet);
            objet.clear();
        }
        else{objet.push_back(ligne[i]);}
    }

    fichier.close();
}

void Plateau::reset_compteur(){
    nombre_boite_bloquee = 0;
    nombre_boite_valide = 0; 
    nombre_boite_valide += nombre_boite_valide_de_base;
}