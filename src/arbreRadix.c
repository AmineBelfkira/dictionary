#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>

//#include "../include/arbreprefixe.h"

struct pref{
    char* c;//caractere qu'on a creer
    int terminaison;
    struct pref** fils;//pointeurs sur les caracteres suivants
    int nb_fils;
};



typedef struct pref noeud;
typedef struct pref* arbre;

int R=0;

bool arbre_est_vide(arbre t);
void tosmall(char* mot);
arbre creer_noeud(char* x);
int indice(char c);
void insertion(char* mot,arbre t1);
bool verification(char* mot,arbre t1);
void destruction(arbre t1);
int exist(char* x,arbre t);

void marquage(int longueurmot,arbre t);

int similitude(char* mot1,char* mot2);

int verification_marquage(char* mot,arbre t);



 
//crée un noed d'arbre conenant un caractère x
arbre creer_noeud(char* x){
    arbre t=calloc(1,sizeof(*t));
    if(t==NULL){
        perror("erreur d'allocation \n");
        exit(EXIT_FAILURE);
    }
    t->c = malloc((strlen(x)+1)*sizeof(*(t->c)));
    if (t->c == NULL) {
      perror("Plus de memoire\n");
      exit(EXIT_FAILURE);
    }
    strcpy(t->c, x);
    //marquage(strlen(x),t);
    //printf("je crée %s et sa terminaison vaut : %d \n",t->c,t->terminaison);

    //t->terminaison=calloc(strlen(x),sizeof(int));
    //t->terminaison[strlen(x)]=1;
    //t->nb_fils=0;
    return t;
}

//retourne l'indice d'un caractere [a,z]->[0,26]
int indice(char c){
    return (int)c-97;
} 

int similitude(char* mot1,char* mot2){
    int n=0;
    for (int i = 0; i <(int)strlen(mot1); i++){
        if(mot1[i]!=mot2[i])return n;
        n++;
    }
    return n;
}
int exist(char* x,arbre t){
    if(t->nb_fils==0) return -1;
    for(int i=0;i<t->nb_fils;i++){
        if((t->fils[i])->c[0]==x[0]) return i;
    }
    return -1;
}

//met tout les caracteres du mot en miniscules
void tosmall(char* mot){
    for(int i=0;i<(int)strlen(mot);i++){
        if((int)mot[i]>64 && (int)mot[i]<91) mot[i]=(char)((int)mot[i]+32);
    }
}


void marquage(int longueurmot,arbre t){
    int bit=(t->terminaison)>>(longueurmot-1);
    bit=bit&0b1;
    if(bit==0){
        t->terminaison+=pow(2,longueurmot-1);
    }
}

int verification_marquage(char* mot,arbre t){
    int bit=(t->terminaison)>>(strlen(mot)-1);
    bit=bit&0b1;
    if(bit==0){
        return 0;
    }
    return 1;
}


void insertion(char* mot,arbre t){
    arbre t1=t;
    arbre tavant;
    char* rajout=mot;
    while (rajout[0]!='\0'){
        int e=exist(rajout,t1);
        if(e<0){/*si le mot n'existe pas il suffit de l'insérer*/
            //printf("         étape : %d\n",1);
            t1->fils=realloc(t1->fils,(t1->nb_fils+1)*sizeof(*(t1->fils)));
            if(t1->fils==NULL){
                perror("error realloc");
                exit(EXIT_FAILURE);
            }
            t1->fils[t1->nb_fils]=creer_noeud(rajout);
            marquage(strlen(rajout),t1->fils[t1->nb_fils]);
            t1->nb_fils++;
            rajout=rajout+strlen(rajout);
        }else{//si le mot existe
            tavant=t1;
            t1=t1->fils[e];
            int s=similitude(rajout,t1->c);
            if(s==(int)strlen(rajout)){
                /*si le mot à rajouté existe déja il suffit de le marquer */
                marquage((int)strlen(rajout),t1);
                rajout=rajout+strlen(rajout);
            }else if(s==(int)strlen(t1->c)){
                /*si la similitude vaut tout le mot du noeud il faut ainsi passer au suivant*/
                rajout=rajout+s;
            }else{
                /*le cas le plus difficile, il faut diviser le mot à rajouté, modifier le noeud 
                existant pour prendre la dernière partie du mot afin de ne pas perdre 
                les noeud fils déja crée, et crée un noeud liant la noeud d'avant et celui final*/
                char motavant[26];
                strcpy(motavant,rajout);
                motavant[s]='\0';
                tavant->fils[e]=creer_noeud(motavant);
                int poidfaible=0;
                for(int r=0;r<s;r++){
                    poidfaible+=pow(2,r);
                }                
                tavant->fils[e]->terminaison=t1->terminaison & poidfaible;
                tavant->fils[e]->fils=realloc(tavant->fils[e]->fils,((tavant->fils[e]->nb_fils)+1)*sizeof(*(tavant->fils[e]->fils)));
                int nb=tavant->fils[e]->nb_fils;
                tavant->fils[e]->fils[nb]=t1;
                t1->c=realloc(t1->c,(s+1)*sizeof(*(t1->c)));
                rajout=rajout+s;
                strcpy(t1->c,t1->c+s);

                t1->terminaison=(t1->terminaison)>>s;
                t1=tavant->fils[e];
                tavant->fils[e]->nb_fils++;                
            }
        }

    }
    
}





//verifie l'existence du mot au sein de l'arbre
bool verification(char* mot,arbre t1){
    arbre t=t1;
    char* parcours=mot;
    int e=exist(parcours,t);
    while(e>=0 ){//tant que le mot à parcourir existe
        t=t->fils[e];
        int s=similitude(parcours,t->c);
        if(strlen(parcours)<strlen(t->c)){
            if(s==(int)strlen(parcours)){//similitude égale à parcours 
                if(verification_marquage(parcours,t)){
                    //le marquage existe
                    return true;
                }else{
                    //sinon le marquage n'existe pas
                    printf("%s n'existe pas \n",mot);
                    R++;
                    return false;
                }
            }else{
                R++;
                printf("%s n'existe pas \n",mot);
                return false;
            }
        }else if(strlen(parcours)>strlen(t->c)){
            if(s==(int)strlen(t->c)){
                //si similitude est égale au mot du noeud avec parcours superieur en longueur au mot
                //on modifie parcours afin de passer et revérifier l'existence
                parcours+=s;
                e=exist(parcours,t);
            }else{
                //sinon le mot n'existe pas
                R++;
                printf("%s n'existe pas \n",mot);
                return false;
            }
        }else{
            //si égalité il suffit de vérifier le marquage
            if(verification_marquage(parcours,t)){
                return true;
            }else{
                R++;
                printf("%s n'existe pas \n",mot);
                return false;
            }
        }
    }
    printf("%s n'existe pas \n",mot);
    R++;
    return false;
}


//on détruit tout l'arbre de manière récursive
void destruction(arbre t1){
    if(t1!=NULL){
        //printf("je suis à %s \n",t1->c);
        if(t1->nb_fils==0){
            //printf("je free %s \n",t1->c);
            free(t1->c);
            free(t1);
        }else{
            for (int i=0; i<t1->nb_fils; i++){
                destruction(t1->fils[i]);
            }
            free(t1->fils);
            //printf("je free %s \n",t1->c);
            free(t1->c);
            free(t1);
        }
        
    }
} 

#define MAXLENGTH 29


int main(){
    arbre t=creer_noeud(":");
    insertion("youssef",t);
    //printf("terminaison de youssef est %d == 128 \n",t->fils[0]->terminaison);
    //printf("nombre de fils du noeud est %d\n",t->nb_fils);
    //printf("terminaison de youssef est: %d == 128 \n",t->fils[0]->terminaison);
    insertion("you",t);
    //printf("nombre de fils du noeud est %d\n",t->nb_fils);
    //printf("terminaison de you est: %d == 136 \n",t->fils[0]->terminaison);
    //printf("-----------Debut insertion youzar \n");
    insertion("youzar",t);
    //printf("nombre de fils du noeud est %d\n",t->nb_fils);
    //printf("terminaison de %s : %d \n",t->fils[0]->c,t->fils[0]->terminaison);
    //printf("terminaison de %s : %d \n",t->fils[0]->fils[0]->c,t->fils[0]->fils[0]->terminaison);
    //printf("terminaison de %s : %d \n",t->fils[0]->fils[1]->c,t->fils[0]->fils[1]->terminaison);
    //printf("terminaison de %s est: %d == 8 \n",t->fils[0]->c,t->fils[0]->terminaison);
    //printf("terminaison de %s est: %d == 16 \n",t->fils[0]->fils[0]->c,t->fils[0]->fils[0]->terminaison);
    //printf("terminaison de %s est: %d == 8 \n",t->fils[0]->fils[1]->c,t->fils[0]->fils[1]->terminaison);
    
    //printf("you == %s \n",t->fils[0]->c);
    //printf("le nombre de fils de you est : %d\n",t->fils[0]->nb_fils);
    //printf("ssef == %s \n",t->fils[0]->fils[0]->c);
    //printf("zar == %s \n",t->fils[0]->fils[1]->c);
    //printf("Debut insertion youzarssif \n");
    insertion("youzarssif",t);
    //printf("nombre de fils du noeud est %d\n",t->nb_fils);

    //printf("Debut insertion yassemine \n");
    insertion("yassemine",t);
    //printf("nombre de fils du noeud est %d\n",t->nb_fils);
    //printf("nombre de fils de %s est %d\n",t->fils[0]->c,t->fils[0]->nb_fils);

    //printf("Debut insertion yonar \n");
    insertion("yonar",t);

    //printf("tout est inséré \n");
    //printf("y == %s et son nombre de fils est : %d et sa terminaison %d\n",t->fils[0]->c,t->fils[0]->nb_fils,t->terminaison);
    //t=t->fils[0];
    //printf("o == %s et son nombre de fils est : %d et sa terminaison %d\n",t->fils[0]->c,t->fils[0]->nb_fils,t->terminaison);
    //printf("assemine == %s et sa terminaison %d\n",t->fils[1]->c,t->fils[1]->terminaison);
    //t=t->fils[0];
    //printf("u == %s et son nombre de fils est : %d et sa terminaison %d\n",t->fils[0]->c,t->fils[0]->nb_fils,t->fils[0]->terminaison);
    //printf("nar == %s et son nombre de fils est : %d\n",t->fils[1]->c,t->fils[1]->terminaison);
    //t=t->fils[0];
    //printf("ssef == %s et son nombre de fils est : %d et sa terminaison %d\n",t->fils[0]->c,t->fils[0]->nb_fils,t->fils[0]->terminaison);
    //printf("zar == %s  et son nombre de fils est : %d et sa terminaison %d\n",t->fils[1]->c,t->fils[1]->nb_fils,t->fils[1]->terminaison);
    //t=t->fils[1];
    //printf("ssif == %s et sa terminaison %d\n",t->fils[0]->c,t->terminaison);


    //printf("y == %s \n",t->fils[0]->c);
    //printf("y == %s \n",t->fils[0]->c);

    verification("youssef",t);
    verification("you",t);
    verification("youzarssif",t);
    verification("yassemine",t);
    verification("yasse",t);
    verification("yo",t);
    verification("amine",t);
    verification("youzarssifff",t);
    destruction(t);

    //verification("youz",t);
    //printf("you == %s \n",t->fils[0]->c);
    //printf("zar == %s \n",t->fils[0]->fils[1]->c);
    //printf("ssif == %s \n",t->fils[0]->fils[1]->fils[0]->c);
    
    ///puts("   ");
    ///verification("youssef",t);
    ///puts("   ");
    //insertion("you",t);
    //verification("youssef",t);*/
    
    /*insertion("yous",t);
    puts("   ");
    insertion("youssef",t);
    puts("   ");
    insertion("you",t);
    puts("   ");
    
    insertion("yousseffef",t);
    puts("   ");
    verification("youssef",t);
    verification("yous",t);
    verification("youss",t);
    printf("\n\n\n\n\n\n");
    affichage(t);*/
    //insertion("youssefssef",t);
    //puts("   ");
    //verification("youssef",t);
    //puts("   ");
    //insertion("amine",t);
    //insertion("lokman",t);
    //insertion("ilyas",t);
    //insertion("ilyasmzin",t); 
    
  
    
    
    //verification("youssef",t);
    //verification("youzar",t);
    //puts("   ");
    //verification("yous",t);
    //verification("you",t);
    //verification("amine",t);
    //verification("ilyase",t);
    //destruction(t); 
    //printf("hehehheh");

    return 0;
}

/*
int main(int argc, char* argv[] ){
    //creation de de l'arbre
    arbre t1=creer_noeud(":");
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
    printf("le nombre de mots faux est : %d\n",R);
    //destruction de l'arbre
    destruction(t1);
    //fermeure du fichier
    fclose(texte);

    return 0;
} */
/*
//printf("la similitude vaut: %d\n",s);
        //printf("la longueur du noeud est %d\n",(int)strlen(t->fils[e]->c));
        //printf("le noeud est %s\n",t->fils[e]->c);
        if(s<(int)strlen(t->c)){
            printf("**************%s n'existe pas 1111*****************\n",mot);
            return false;
        }
        printf("%s\n",parcours);
        parcours=parcours+s;
        printf("%s\n",parcours);
        t=t->fils[e];
        lon=lon-s-1;
        printf("longueur vaut:%d \n",lon);
        printf("parcours vaut :%s \n",parcours);
        for (int i=0;i<t->nb_fils;i++)printf("fils %d : %s\n--",i,t->fils[i]->c);
        puts(" ");
        e=exist(parcours,t);
        printf("l'existence vaut: %d\n",e);
    }
    if(lon==0) {
        printf("existe\n");
        return true;
        }
    else{
        printf("******************%s n'existe pas 22222*********************\n",mot);
        return false;
    }
*/