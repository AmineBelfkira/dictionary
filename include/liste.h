#ifndef LISTE_H
#define LISTE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "../src/liste.c"



void affichage(liste l);

liste initialistion_liste(char* valeur);

void insere_tete(char* valeur, liste* pl);

bool recherche(char* valeur, liste l);

void supprimer(liste l);

#endif