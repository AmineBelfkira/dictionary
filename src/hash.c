#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#define mod 20000
#define MAXLENGTH 29  //taille plus long mot 

typedef struct cellule {
  char* mots;
  struct cellule* suivante;
} cellule;
typedef cellule* liste;

typedef struct {
  liste* table;
  unsigned capacite; /* capacité de la table */
  int nb_motss; /* nombres d'éléments dans la table */
} table_hachage;



 
//Fonction de hachage numero 1

int hash(char* str){ 
  int hache = 0;			
  for (size_t i = 0; str[i] != '\0'; i++) {
    hache += abs((int)pow(str[i],(i+1)));
  }
  return abs(hache%mod);
}

//Fonction de hachage numero 2

int hash1(char* str){ 
  int hache = 0;			
  for (size_t i = 0; str[i] != '\0'; i++) {
    hache += str[i];
  }
  return abs(hache%mod);
}


// Allocation et initialisation d'une table de hachage

table_hachage* intialisation(){

    table_hachage* ht=calloc(1,sizeof(*ht));

    if (ht == NULL) {
        perror("Plus de memoire\n");
        exit(EXIT_FAILURE);
    }

    ht->table = calloc(mod,sizeof((*(ht->table))));
    if (ht->table == NULL) {
      perror("Plus de memoire\n");
      exit(EXIT_FAILURE);
    }

    ht->nb_motss=0;
    ht->capacite=mod;
    // Initialisation de la table
    for (size_t j=0;j<mod;j++) (ht->table[j])=NULL;
    return ht;
}

// Allocation et initialisation d'une liste
liste initialistion_liste(char* valeur){
  
    liste p=calloc(1,sizeof(*p));
    if (p == NULL) {
        perror("Plus de memoire\n");
        exit(EXIT_FAILURE);
    } 

    p->mots = malloc(strlen(valeur) + 1); //En fait il faut une case contenant '/0'

    if (p->mots == NULL) {
      perror("Plus de memoire\n");
      exit(EXIT_FAILURE);
    }

    strcpy(p->mots, valeur); //On copie le mot valeur dans p->mots
    return p;
}

//Verifier si 2 mots sont identiques
bool identiques(char* mots1, char* mots2){
    return (!strcmp(mots1,mots2)); //strcmp renvoie 0 dans le cas où les mots sont identiques
}



//Verifier la prensence dans la table de hachage
bool est_present(char* mots, table_hachage* ht){
  // Liste où doit se trouver la chaîne
  liste l=ht->table[hash(mots)];

  if(l==NULL) return false;
  else{
    while (l!=NULL){
      if(identiques(l->mots,mots)) return true;
      l=l->suivante;
    }
    return false;
  }
}

//inserer dans la tete de la liste un mot
void insere_tete(char* valeur, liste* pl){
	liste p = initialistion_liste(valeur);
	p->suivante = *pl;
    *pl=p;  
}

//inserer dans une table de hachage
void inserer_sans_redimensionner(char* mots, table_hachage* ht){
  if (!est_present(mots,ht)) {
    insere_tete(mots,&ht->table[hash(mots)]); //Suffit d'utiliser la fonction dnas la position hash(mots)
    ht->nb_motss++; // le nombre ainsi augmente
  }
  
}

void affiche(liste l){
    if(l==NULL){
      printf("liste vide \n");
      return;
    }
    do{
        printf("[%s] ",l->mots);
        l=l->suivante;
    }while(l->suivante!=NULL);
    puts(" ");
}

void afficher_table(table_hachage* ht){
  if(ht==NULL)printf("table vide \n");
  else{
    for(size_t i=0;i<(ht->capacite);i++){
      printf("la case numèro %ld contient ces éléments: \n",i);
      affiche(ht->table[i]);
      printf("\n");
    }
  }
}

//suppression de la liste pour ensuite l'utiliser pour supprimer toute les liste dans le tableau d'hachage
void supprimer_liste(liste* l){
     liste p=*l,q;
     if (!l) return ;
     while(p!=NULL){
         q=p;
         p=p->suivante;
         free(q->mots);
         free(q);
    }
 }

void supprime(table_hachage* ht){
    for(size_t i=0;i<(ht->capacite);i++){
        supprimer_liste(&(ht->table[i]));

    }
    free(ht->table);
    free(ht);
}








int main(void){

    table_hachage* ht=intialisation();
    int NOMBRE_DE_MOT_FAUX=0; 



    //PARTIE LECTURE DU DICTIONNAIRE
    if(1){
    FILE* dictionnaire=fopen("FR.txt","r");
    if(dictionnaire==NULL){
        perror("problem d'ouverture du fichier \n");
        exit(EXIT_FAILURE);
    }
    char mot[MAXLENGTH]="";
    
    
    while (fscanf(dictionnaire, "%[^\n] ", mot) != EOF)  {
        inserer_sans_redimensionner(mot,ht);
        
    }
    fclose(dictionnaire);

    /*Lors des tests on a eu besoin d'afficher la distribution et le degré de colision dans la table de hachage*/
    //afficher_table(ht); 

    }

    
    //PARTIE LECTURE DU TEXTE
   
    FILE* texte=fopen("a_la_recherche_du_temps_perdu.txt","r");
    if(texte==NULL){
        perror("problem d'ouverture du fichier \n");
        exit(EXIT_FAILURE);
    } 
    int t=0;
    while(t!=EOF){
        char mot2[MAXLENGTH]="";
        int i=0;
        t=getc(texte);
        while((t>64 && t<91) || (t>96 && t<123)){
            mot2[i]=tolower(t); //Les mots du dictionaire sans en miniscule donc on a besoin de mettre les mots du texte en miniscule pour les comparer
            i++;
            t=getc(texte);
        }
        if(i!=0)mot2[i+1]='\0';
        if(mot2[0]!='\0'){
          //ici teste l'existence.
            if(!est_present(mot2,ht)){
              NOMBRE_DE_MOT_FAUX++;
              printf("[%s]",mot2);  
            }         
        }
    }
    //affiche(pl);
    printf("\n\nLe nombre de mots faux est: %d\n",NOMBRE_DE_MOT_FAUX);
    
    //libere notre structure allouée;
    supprime(ht);
  
    
    return 0;
}
