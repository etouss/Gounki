/*
//  partieHeuristique.c
//  ProjetRC
//
//  Created by Etienne Toussaint on 15/04/2014.
//  Copyright (c) 2014 Etienne Toussaint. All rights reserved.
*/

#include "partieHeuristique.h"

void viderBufferc()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}


int partiH()
{

    /*int typeA = -1;
    int typeB = -1;
    printf("Choisiser l'IA de A \n0 pour l'IA standa\n1 pour l'IA aggresive\n2 pour l'IA defence\n3 pour l'IA bizzare\n");
    while (typeA<0||typeA>4) {
        scanf("%d", &typeA);
        viderBufferc();
    }
    printf("Choisiser l'IA de B \n0 pour l'IA standa\n1 pour l'IA aggresive\n2 pour l'IA defence\n3 pour l'IA bizzare\n");
    while (typeB<0||typeB>4) {
        scanf("%d", &typeB);
        viderBufferc();
    }*/

    srand(time(NULL));

    setReglageA(4.226562, 1.513672, 1.734375);
    setReglageB(4.226562, 1.513672, 1.734375);

    int signe = 1;
    double unite = 1;
    int reglage = 0;

    while(1){
    int victoire = 0;
    int t = 0;
    int a=0;
    int b = 0;

    for (t=0; t<1000; t++) {

        victoire = 0;
        initMap();
        pion ** grille = initGrille();
        //affiche();

        int f = 0;
        while (!victoire) {

            {
                f ++;
                if (f>100000) break;
                coup * pere;
                pere = calloc(1,sizeof(coup));
                pere->proto = NULL;
                pere->coupSuivant = NULL;
                pere = coupsPossibles(grille, 'A',pere);
                coup * coupPossible = pere;
                int n = 0;
                int i = 0;
                int max = calculHeuristiqueCoups(pere, grille,'A',-1);

                coupPossible = pere;
                coup *coupHeuri = calloc(1,sizeof(coup));
                coupHeuri->proto = NULL;
                coupHeuri->coupSuivant = NULL;
                coup *coupActuelle = coupHeuri;
                while (coupPossible != NULL){
                    if(coupPossible->heuristique == max){
                        n++;
                        coup * coupSuivant = calloc(1,sizeof(coup)); coupSuivant->proto = NULL;coupSuivant->coupSuivant= NULL;
                        coupActuelle->proto = coupPossible->proto;
                        coupActuelle->heuristique =coupPossible->heuristique;
                        coupActuelle->coupSuivant = coupSuivant;
                        coupActuelle = coupSuivant;
                    }
                    coupPossible = coupPossible->coupSuivant;
                }


                int choix = (rand()%n);
                //i = 0;
                coupPossible = coupHeuri;

                for (i=0; i<choix; i++) {
                    coupPossible = coupPossible->coupSuivant;
                }



                //printf("\n%s\n",coupPossible->proto);
                if(action(grille, coupPossible->proto, pere,1)==1){
                    //printf("efef");
                    a++;
                    victoire = 1;
                    break;
                    //printf("a");
                }

                freeCoup(pere,1);
                freeCoup(coupHeuri,0);
                updateMap(grille);
                //affiche();
            }
            {
                coup * pere;
                pere = calloc(1,sizeof(coup));
                pere->proto = NULL;
                pere->coupSuivant = NULL;
                pere = coupsPossibles(grille, 'B',pere);
                coup * coupPossible = pere;
                int n = 0;
                int i = 0;
                int max = calculHeuristiqueCoups(pere, grille,'B',-1);
                coupPossible = pere;
                coup *coupHeuri = calloc(1,sizeof(coup));
                coupHeuri->proto = NULL;
                coupHeuri->coupSuivant = NULL;
                coup *coupActuelle = coupHeuri;
                while (coupPossible != NULL){
                    if(coupPossible->heuristique == max){
                        n++;
                        coup * coupSuivant = calloc(1,sizeof(coup)); coupSuivant->proto = NULL;coupSuivant->coupSuivant= NULL;
                        coupActuelle->proto = coupPossible->proto;
                        coupActuelle->heuristique =coupPossible->heuristique;
                        coupActuelle->coupSuivant = coupSuivant;
                        coupActuelle = coupSuivant;
                    }
                        coupPossible = coupPossible->coupSuivant;
                }
                int choix = (rand()%n);
                i = 0;
                coupPossible = coupHeuri;

                for (i=0; i<choix; i++) {
                    coupPossible = coupPossible->coupSuivant;
                }

                //printf("\n%s\n",coupPossible->proto);
                if(action(grille, coupPossible->proto, pere,1)==1){
                    //printf("b");
                    b++;
                    victoire = 1;
                    break;
                }

                freeCoup(pere,1);
                freeCoup(coupHeuri,0);
                updateMap(grille);
                //affiche();
            }

        }
        //printf("%d",t);
        freeGrille(grille);
        freeMap();

    }
        double * heuriA = getReglageA();
        double * heuriB = getReglageB();
    FILE * fichier = fopen("heuristique.txt", "a");
        fprintf(fichier,"ArmeA = %f , PerceA = %f , DefenceA = %f \nArmeeB = %f PerceeB = %f , DefenceB = %f \n A = %d || B = %d \n\n\n\n",heuriA[0],heuriA[1],heuriA[2],heuriB[0],heuriB[1],heuriB[2],a,b);
        printf("ArmeA = %f , PerceA = %f , DefenceA = %f \nArmeeB = %f PerceeB = %f , DefenceB = %f \n A = %d || B = %d \n\n\n\n",heuriA[0],heuriA[1],heuriA[2],heuriB[0],heuriB[1],heuriB[2],a,b);
    fclose(fichier);
        if(a>b){
            setReglageB(heuriA[0], heuriA[1], heuriA[2]);
            heuriA[reglage] += unite*signe;
            setReglageA(heuriA[0], heuriA[1], heuriA[2]);
        }
        else if(b>a) {
            signe = signe * -1;
            unite = unite/2;
            if(unite < 0.001){
                reglage += 1;
                if (reglage == 3) reglage = 0;
                unite = 1;
            }
            setReglageA(heuriB[0], heuriB[1], heuriB[2]);
            heuriB[reglage] += unite*signe;
            setReglageA(heuriB[0], heuriB[1], heuriB[2]);
        }
        free(heuriA);
        free(heuriB);


    }
    //printf("a=%d,b=%d",a,b);
    return 0;
}

int jouerCoupIA(pion ** grille, char joueur,int  difficulter,int testIA, int ad,int type){
    coup * pere;
    pere = calloc(1,sizeof(coup));
    pere->proto = NULL;
    pere->coupSuivant = NULL;
    pere = coupsPossibles(grille, joueur,pere);
    coup * coupPossible = pere;
    int n = 0;
    int i = 0;
    int max;
    if(difficulter == 0)max = calculHeuristiqueCoups(pere, grille,joueur,type);
    else max = calculHeuristiqueCoupsMultiples(pere, grille,joueur,difficulter,type);
    coupPossible = pere;
    coup *coupHeuri = calloc(1,sizeof(coup));
    coupHeuri->proto = NULL;
    coupHeuri->coupSuivant = NULL;
    coup *coupActuelle = coupHeuri;
    while (coupPossible != NULL){
        if(coupPossible->heuristique == max){
            n++;
            coup * coupSuivant = calloc(1,sizeof(coup)); coupSuivant->proto = NULL;coupSuivant->coupSuivant= NULL;
            coupActuelle->proto = coupPossible->proto;
            coupActuelle->heuristique =coupPossible->heuristique;
            coupActuelle->coupSuivant = coupSuivant;
            coupActuelle = coupSuivant;
        }
        coupPossible = coupPossible->coupSuivant;
    }
    int choix = (rand()%n);
    i = 0;
    coupPossible = coupHeuri;

    for (i=0; i<choix; i++) {
        coupPossible = coupPossible->coupSuivant;
    }
    if(ad)setAdvice(coupPossible->proto);
    if(!testIA)printf("\n%s\n",coupPossible->proto);
    if(action(grille, coupPossible->proto, pere,1)==1)return 1;

    freeCoup(pere,1);
    freeCoup(coupHeuri,0);
    //updateMap(grille);
    //affiche();

    return 0;
}
