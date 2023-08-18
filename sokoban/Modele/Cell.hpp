#ifndef Cell_hpp
#define Cell_hpp

#include "Point.hpp"
#include <FL/Fl.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/fl_draw.H>
#include <string>

using namespace std;

/* Classe qui definit une cellule , vide par defintion*/

class Cell
{

protected:

    Point centre;
    int longueur;
    int largeur;
    int position;
    int position_initiale;
    bool is_marked = false; 
    char type = '-';    // cellule vide

    Fl_Color couleur;

public:


    Cell(Point centre, int longueur, int largeur, int position);

    virtual ~Cell(){}; // destructeur par défaut, il faut le déclarer dans toutes les sous-classes (permet le dynamic_cast)

    virtual void reset_objet(){}; // override dans les sous-classes pour utilite differente

    virtual void draw(){}; // override dans les sous-classes pour affichage different

    bool contains(Point p);

    // getters
    int get_position() {return position;}

    char get_type() {return type;}

    virtual bool get_marked() {return is_marked;} // override dans téléporteur pour la recherche de chemin

    int get_position_initiale(){return position_initiale;}

    Fl_Color get_couleur(){return couleur;}

    Point get_centre(){return centre;}

    //setters
    void set_type(char new_type) { type = new_type; }

    void set_position(int new_position) { position = new_position; }

    virtual void set_marked(bool marked) { is_marked = marked; } // override dans téléporteur pour la recherche de chemin

    void set_position(Point nouvelle_position){centre = nouvelle_position;}

    void set_couleur(Fl_Color new_couleur){couleur = new_couleur;}


    
        
};

#endif