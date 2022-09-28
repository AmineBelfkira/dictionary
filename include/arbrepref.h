#ifndef ARBREPREF_H
#define ARBREPREF_H
//structure du noeud
struct pref{
    char c;//caractere qu'on a creer
    int v;//marquage de fin de mot
    struct pref* fils[26];//pointeurs sur les caracteres suivants
};
typedef struct pref noeud;
typedef struct pref* arbre;

bool arbre_est_vide(arbre t);
void tosmall(char* mot);
arbre creer_noeud(char x);
int indice(char c);
void insertion(char* mot,arbre t1);
bool verification(char* mot,arbre t1);
void destruction(arbre t1);

#endif

