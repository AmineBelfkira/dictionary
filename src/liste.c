#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define MAXLENGTH 29


//EFINITION DE NOTRE STRUCTURE:

typedef struct cellule {
  char* valeur;
  struct cellule* suivante;
} cellule;

typedef struct cellule* liste;



//Allocation et initialisation d'une liste

liste initialistion_liste(char* valeur){

    liste p=calloc(1,sizeof(*p));
    if (p == NULL) {
        perror("Plus de memoire\n");
        exit(EXIT_FAILURE);
    } 

    p->valeur = malloc(strlen(valeur) + 1); //En fait il faut une case contenant '/0'

    if (p->valeur == NULL) {
        perror("Plus de memoire\n");
        exit(EXIT_FAILURE);
    }
    strcpy(p->valeur, valeur); //On copie le mot valeur dans p->mots

    return p;
}



void affichage(liste l){
    liste p=l;
    if(l==NULL){
        printf("NULL");
    }
    else{
        while(p!=NULL){
            if(p->suivante!=NULL) printf("%s //",p->valeur);
            else printf("%s",p->valeur);
            p=p->suivante;
        }
        printf("\n");
    }
}


void insere_tete(char* valeur, liste* pl){
	liste p = initialistion_liste(valeur); //On crée un pointeur de valeur notre nouveau mot qui servira comme nouveau debut de notre liste
	p->suivante = *pl;
        *pl=p;  
}


bool recherche(char* valeur, liste l){
    liste p=l;
    do{
        if((!strcmp(p->valeur,valeur))) return 1; //strcmp renvoie 0 dans le cas où les mots sont identiques
        p=p->suivante;
    }while (p!=NULL);
    return 0;
    
}

//On libere notre structure
void supprimer(liste l){
     liste p=l,q;
     if (!l) return ;
     while(p!=NULL){
         q=p;
         p=p->suivante;
         free(q->valeur);
         free(q);
    }
 }


 #define MAXLENGTH 29





int main(void){

        //On intialise nos 26 listes
    liste t1=initialistion_liste(" ");
    liste t2=initialistion_liste(" ");
    liste t3=initialistion_liste(" ");
    liste t4=initialistion_liste(" ");
    liste t5=initialistion_liste(" ");
    liste t6=initialistion_liste(" ");
    liste t7=initialistion_liste(" ");
    liste t8=initialistion_liste(" ");
    liste t9=initialistion_liste(" ");
    liste t10=initialistion_liste(" ");
    liste t11=initialistion_liste(" ");
    liste t12=initialistion_liste(" ");
    liste t13=initialistion_liste(" ");
    liste t14=initialistion_liste(" ");
    liste t15=initialistion_liste(" ");
    liste t16=initialistion_liste(" ");
    liste t17=initialistion_liste(" ");
    liste t18=initialistion_liste(" ");
    liste t19=initialistion_liste(" ");
    liste t20=initialistion_liste(" ");
    liste t21=initialistion_liste(" ");
    liste t22=initialistion_liste(" ");
    liste t23=initialistion_liste(" ");
    liste t24=initialistion_liste(" ");
    liste t25=initialistion_liste(" ");
    liste t26=initialistion_liste(" ");
   
    
    //Construire notre dictionnaire
    FILE* dictionnaire=fopen("FR.txt","r");
    if(dictionnaire==NULL){
        perror("problem d'ouverture du fichier \n");
        exit(EXIT_FAILURE);
    }
    char mot[MAXLENGTH]="";
    int NOMBRE_MOT_FAUX=0;
    while (fscanf(dictionnaire, "%[^\n] ", mot) != EOF )  {
        int n=mot[0];
        
        if (n==97)insere_tete(mot,&t1);                 //regrouper les mots commencants par a 
        else if(n==98)insere_tete(mot,&t2);             //regrouper les mots commencants par b 
        else if(n==99)insere_tete(mot,&t3);             //regrouper les mots commencants par c
        else if(n==100)insere_tete(mot,&t4);            //regrouper les mots commencants par d
        else if(n==101)insere_tete(mot,&t5);            //regrouper les mots commencants par e
        else if(n==102)insere_tete(mot,&t6);            //regrouper les mots commencants par f
        else if(n==103)insere_tete(mot,&t7);            //regrouper les mots commencants par g
        else if(n==104)insere_tete(mot,&t8);            //regrouper les mots commencants par h
        else if(n==105)insere_tete(mot,&t9);            //regrouper les mots commencants par i
        else if(n==106)insere_tete(mot,&t10);           //regrouper les mots commencants par j
        else if(n==107)insere_tete(mot,&t11);           //regrouper les mots commencants par k
        else if(n==108)insere_tete(mot,&t12);           //regrouper les mots commencants par l
        else if(n==109)insere_tete(mot,&t13);           //regrouper les mots commencants par m
        else if(n==110)insere_tete(mot,&t14);           //regrouper les mots commencants par n
        else if(n==111)insere_tete(mot,&t15);           //regrouper les mots commencants par o
        else if(n==112)insere_tete(mot,&t16);           //regrouper les mots commencants par p
        else if(n==113)insere_tete(mot,&t17);           //regrouper les mots commencants par q
        else if(n==114)insere_tete(mot,&t18);           //regrouper les mots commencants par r
        else if(n==115)insere_tete(mot,&t19);           //regrouper les mots commencants par s
        else if(n==116)insere_tete(mot,&t20);           //regrouper les mots commencants par t
        else if(n==117)insere_tete(mot,&t21);           //regrouper les mots commencants par u
        else if(n==118)insere_tete(mot,&t22);           //regrouper les mots commencants par v
        else if(n==119)insere_tete(mot,&t23);           //regrouper les mots commencants par w
        else if(n==120)insere_tete(mot,&t24);           //regrouper les mots commencants par x
        else if(n==121)insere_tete(mot,&t25);           //regrouper les mots commencants par y
        else insere_tete(mot,&t26);                     //regrouper les mots commencants par z
        
    }
    fclose(dictionnaire);
    
    
        //On lit notre texte.
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
            mot2[i]=tolower(t);
            i++;
            t=getc(texte);
        }
        if(i!=0)mot2[i+1]='\0';
        if(mot2[0]!='\0'){
          //ici teste l'existence.
            
            int comp=mot2[0]-1;
            if (comp==96){
                if(!recherche(mot2,t1) ) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            else if (comp==97){
                if(!recherche(mot2,t2) ) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            else if (comp==98){
                if(!recherche(mot2,t3) ) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            else if (comp==99){
                if(!recherche(mot2,t4) ) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            else if (comp==100){
                if(!recherche(mot2,t5) ) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            else if (comp==101){
                if(!recherche(mot2,t6) ) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            else if (comp==102){
                if(!recherche(mot2,t7)) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            else if (comp==103){
                if(!recherche(mot2,t8) ) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            else if (comp==104){
                if(!recherche(mot2,t9) ) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            else if (comp==105){
                if(!recherche(mot2,t10) ) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            } 
            else if (comp==106){
                if(!recherche(mot2,t11) ) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            else if (comp==107){
                if(!recherche(mot2,t12) ) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            else if (comp==108){
                if(!recherche(mot2,t13) ) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            else if (comp==109){
                if(!recherche(mot2,t14) ) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            else if (comp==110){
                if(!recherche(mot2,t15)) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            else if (comp==111){
                if(!recherche(mot2,t16) ) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            else if (comp==112){
                if(!recherche(mot2,t17) ) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            else if (comp==113){
                if(!recherche(mot2,t18) ) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            else if (comp==114){
                if(!recherche(mot2,t19) ) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            else if (comp==115){
                if(!recherche(mot2,t20) ) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            else if (comp==116){
                if(!recherche(mot2,t21) ) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            else if (comp==117){
                if(!recherche(mot2,t22) ) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            else if (comp==118){
                if(!recherche(mot2,t23) ) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            else if (comp==119){
                if(!recherche(mot2,t24) ) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            else if (comp==120){
                if(!recherche(mot2,t25) ) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            else {
                if(!recherche(mot2,t26) ) {
                        printf("[%s]",mot2);
                        NOMBRE_MOT_FAUX++;
                }
            }
            
             
        }
    }


    
    //affichage nbr de mots faux
    printf("\n\nLe nombre de mots faux est:%d\n",NOMBRE_MOT_FAUX);

    //libere notre structure allouée;
    supprimer(t1);
    supprimer(t2);
    supprimer(t3);
    supprimer(t4);
    supprimer(t5);
    supprimer(t6);
    supprimer(t7);
    supprimer(t8);
    supprimer(t9);
    supprimer(t10);
    supprimer(t11);
    supprimer(t12);
    supprimer(t13);
    supprimer(t14);
    supprimer(t15);
    supprimer(t16);
    supprimer(t17);
    supprimer(t18);
    supprimer(t19);
    supprimer(t20);
    supprimer(t21);
    supprimer(t22);
    supprimer(t23);
    supprimer(t24);
    supprimer(t25);
    supprimer(t26);

    
    
    return 0;
}




