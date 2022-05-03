LDFLAGS = -L./lib -ldemineur
CFLAGS = -std=c99 -fpic -I./include -ggdb -O0



all : demineur test doc

test : TU_AfficherGrille TU_InitPartie TU_MarquerUneCellule

demineur : bin/controller.o lib/libdemineur.so
	gcc -o $@ $< $(LDFLAGS)


TU_MarquerUneCellule : bin/TU_MarquerUneCellule.o lib/libdemineur.so
	gcc -o test/$@ $< $(LDFLAGS)	

TU_AfficherGrille : bin/TU_AfficherGrille.o lib/libdemineur.so
	gcc -o test/$@ $< $(LDFLAGS)

TU_InitPartie : bin/TU_InitPartie.o lib/libdemineur.so
	gcc -o test/$@ $< $(LDFLAGS)

bin/TU_%.o : src/test/TU_%.c
	gcc -o $@ -c $(CFLAGS) $^ 

lib/libdemineur.so : bin/modele/modele_grille.o bin/view/view_grille.o bin/modele/modele_strategie.o bin/view/view_strategie.o bin/modele/modele_partie.o bin/view/view_menu.o 
	gcc -shared -o $@ $^

bin/view/%.o : src/view/%.c
	gcc -o $@ -c $(CFLAGS) $^ 

bin/modele/%.o : src/modele/%.c
	gcc -o $@ -c $(CFLAGS) $^ 

bin/controller.o : src/controller.c
	gcc -o $@ -c $(CFLAGS) $^ 

clean : 

	rm lib/*
	rm bin/modele/*
	rm bin/view/*
	rm bin/controller.o
	rm demineur
	rm test/*
	

doc :
	cd doc && doxygen 

.PHONY : doc clean test

