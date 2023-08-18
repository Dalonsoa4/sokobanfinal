CFLAGS = -std=c++20 -Wall -Wextra -Wpedantic 
CC= g++-11

OBJECTS := Partie.o Plateau.o Cell.o Boite.o Joueur.o Objectif.o Affichage_partie.o Controller_partie.o Mur.o Controller_plateau.o Bouton.o Teleporteur.o Boite_legere.o Affichage_menu.o Affichage_selection.o
all: build

clean:
	rm -f $(OBJECTS)
mrproper: clean
	rm build
run: all
	./build
build: $(OBJECTS)
	$(CC) projet.cpp $^ -o $@ -lfltk -lfltk_images
%.o: Modele/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
%.o: Vue/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
%.o: Controller/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@	
.PHONY: all clean