#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

//#include "../include/arbreprefixe.h"

struct pref{
    char c;//caractere qu'on a creer
    int v;//marquage de fin de mot
    struct pref** fils;//pointeurs sur les caracteres suivants
    int nb_fils;
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
int exist(char x,arbre t);
 
bool arbre_est_vide(arbre t){
    return t==NULL;
}


//crée un noed d'arbre conenant un caractère x
arbre creer_noeud(char x){
    arbre t=calloc(1,sizeof(*t));
    if(t==NULL){
        perror("erreur d'allocation \n");
        exit(EXIT_FAILURE);
    }
    t->c=x;
    //t->nb_fils=0;
    return t;
}

//retourne l'indice d'un caractere [a,z]->[0,26]
int indice(char c){
    return (int)c-97;
} 

int exist(char x,arbre t){
    if(t->nb_fils==0) return -1;
    for(int i=0;i<t->nb_fils;i++){
        if((t->fils[i])->c==x) return i;
    }
    return -1;
}

//met tout les caracteres du mot en miniscules
void tosmall(char* mot){
    for(int i=0;i<(int)strlen(mot);i++){
        if((int)mot[i]>64 && (int)mot[i]<91) mot[i]=(char)((int)mot[i]+32);
    }
}

//insere un mot dans l'arbre
void insertion(char* mot,arbre t1){
    char c1;
    arbre t=t1;
    //on parcours les caractères du mot
    for(int i=0;i<(int)strlen(mot);i++){
        c1=mot[i];
        /*si on trouve caractère n'ayant pas de noeud je créé des noeuds 
        pour tous les autres restants dans le mot et on met l'entier du noeud du dernier 
        caractere à 1 pour marquer la fin du mot
        */
        if(exist(c1,t)<0){
            //printf("%c n'existe pas dans t\n",c1);
            t->fils=realloc(t->fils,(t->nb_fils+1)*sizeof(*(t->fils)));
            if(t->fils==NULL){
                perror("error realloc");
                exit(EXIT_FAILURE);
            }
            //printf("le nombre de fils de %c avant insertion est %d \n",c1,t->nb_fils);
            t->fils[t->nb_fils]=creer_noeud(c1);
            printf("%c inseré \n",c1);
            t->nb_fils++;
            //printf("le nombre de fils apres insertion de %c est %d \n",c1,t->nb_fils);
            t=t->fils[(t->nb_fils)-1];
            
            for(int j=i+1;j<(int)strlen(mot);j++){
                c1=mot[j];
                t->fils=realloc(t->fils,(t->nb_fils+1)*sizeof(*(t->fils)));
                if(t->fils==NULL){
                    perror("error realloc");
                    exit(EXIT_FAILURE);
                }
                printf("%c inseré \n",c1);
                t->fils[t->nb_fils]=creer_noeud(c1);
                t->nb_fils++;
                t=t->fils[(t->nb_fils)-1];
            }
            t->v=1;
            return;
        }
        /*si tous les noeuds existents deja il suffit alors de marquer
        la fin du mot*/
        else{
            //printf("%c existe dans t\n",c1);
            t=t->fils[exist(c1,t)];
            if (i==(int)strlen(mot)-1){
                t->v=1;
                return;
            }
        }
    }
}

/*verifie l'existence du mot au sein de l'arbre*/
bool verification(char* mot,arbre t1){
    arbre t=t1;
    char c1;
    //parcours simple des noeuds de l'arbre
    for(int i=0;i<(int)strlen(mot);i++){
        c1=mot[i];
        //si un noeud n'existe pas on return false
        if(exist(c1,t)<0){ 
            printf("%s n'existe pas \n",mot);
            return false;
        }
        //else je passe au caractere suivant et noeud suivant
        else{
            t=t->fils[exist(c1,t)];
        }
    }
    //si tous les noeuds existe on verifie l'existence du marquage
    if(t->v==0){
        printf("%s n'existe pas \n",mot);
        return false;
    }
    return true;
}


//on détruit tout l'arbre de manière récursive
void destruction(arbre t1){
    if(t1!=NULL){
        if(t1->nb_fils==0){
            free(t1);
        }else{
            for (int i=0; i<t1->nb_fils; i++){
                destruction(t1->fils[i]);
            }
            free(t1->fils);
            free(t1);
        }
    }
} 

#define MAXLENGTH 29


/* int main(){
    arbre t=creer_noeud(':');
    insertion("youssef",t);
    insertion("youzar",t);
    insertion("amine",t);
    insertion("lokman",t);
    insertion("ilyas",t);
    insertion("ilyasmzin",t); 
    verification("youssef",t);
    verification("youzar",t);
    verification("yous",t);
    verification("you",t);
    verification("amine",t);
    verification("ilyas",t);
    destruction(t);


    return 0;
}
 */

int main(int argc, char* argv[] ){
    //creation de de l'arbre
    arbre t1=creer_noeud(':');
    //ouverture du fichier dictionnaire
    FILE* dictionnaire=fopen("FR.txt","r");
    if(dictionnaire==NULL){
        perror("problem d'ouverture du fichier \n");
        exit(EXIT_FAILURE);
    }
    //lecture des mots du dictionnaire
    int r=0;
    while(r!=EOF){//tant qu_on est pas on fin du fichier
        char mot[MAXLENGTH]="";
        int n=0;
        r=getc(dictionnaire);
        while((r>64 && r<91) || (r>96 && r<123)){ //on lit les caractères minuscules ou maj 
        //jusqu'auu fin du mot (\n)
            mot[n]=r;
            n++;
            r=getc(dictionnaire);
        }
        //j'insere le caratere null en fin du mot
        if(n!=0)mot[n+1]='\0';
        //j'insere le mot dans le graphe
        insertion(mot,t1);
    }
    //fermeture dictionnaire
    fclose(dictionnaire);

    //ouverture du fichier à tester 
    FILE* texte=fopen("a_la_recherche_du_temps_perdu.txt","r");
    if(texte==NULL){
        perror("problem d'ouverture du fichier \n");
        exit(EXIT_FAILURE);
    }
    //lecture des mots de la même manière on s'arrête en rencontrant un 
    //caractere special autre qu'alphabet
    int t=0;
    while(t!=EOF){
        char mot2[MAXLENGTH]="";
        int i=0;
        t=getc(texte);
        while((t>64 && t<91) || (t>96 && t<123)){
            mot2[i]=t;
            i++;
            t=getc(texte);
        }
        if(i!=0)mot2[i+1]='\0';
        if(mot2[0]!='\0'){
            //transforme les caracteres en miniscule
            tosmall(mot2);
            //verification de l'existence du mot dans l'arbre
            verification(mot2,t1);
        }
    }
        
    //destruction de l'arbre
    destruction(t1);
    //fermeure du fichier
    fclose(texte);

    return 0;
} 