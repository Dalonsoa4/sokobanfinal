#ifndef Boite_hpp
#define Boite_hpp

#include "Cell.hpp"

using namespace std;

class Boite : public Cell
{

protected:

    bool legere = false;
    bool is_bloquee = false;
    bool is_valide = false; 
    bool is_valide_de_base = false;

    Fl_Color couleur_contour = fl_rgb_color(218,165,32); 
    
public:

    Boite(Point centre, int longueur, int largeur, int position);

    virtual ~Boite(){};

    void draw() override;

    void reset_objet() override;

    // getters
    bool get_valide() {return is_valide;}

    bool get_legere(){return legere;}

    bool get_bloquee(){return is_bloquee;}

    bool get_valide_de_base(){return is_valide_de_base;}

    // setters
    void set_bloquee(bool bloquee){is_bloquee = bloquee;}

    void set_valide(bool valide){ is_valide = valide; }

    void set_valide_de_base(bool valide_de_base){is_valide_de_base = valide_de_base;}
};

#endif