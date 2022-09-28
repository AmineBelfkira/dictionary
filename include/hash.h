#ifndef HASH_H
#define HASH_H
#define TAILLE 350000

#include "../src/hash.c"

int hash(char* str);
table_hachage* intialisation();
bool identiques(char* mots1, char* mots2);
bool est_present(char* mots, table_hachage* ht);
void inserer_sans_redimensionner(char mots[], table_hachage* ht);
void affiche(liste l);
void afficher_table(table_hachage* ht);
void supprimer_liste(liste *l);
void supprime(table_hachage* ht);



#endif