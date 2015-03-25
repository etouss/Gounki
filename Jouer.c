/*
//  Jouer.c
//  Gounki
//
//  Created by andres quiroz on 30/04/2014.
//  Copyright (c) 2014 andres quiroz. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include "Jouer.h"
/*1=48,8=56*/
/*a=97,h=104*/

int victoire = 0;
int ready_to_play = 0;
pion ** grilleCancel;
pion ** grilleReDo;

char * correrction(pion ** grille,char * proto,coup* pere)
{
    if(proto[2] == '*' || proto[2] == '+')
        {
            pion ** grilleCpy = copieGrille(grille);
            char * protoA = calloc(5, sizeof(char));
            char * protoB = calloc(8, sizeof(char));
            int i =0;
            switch (strlen(proto))
                {
                case 8:
                    if(action(grilleCpy, proto, pere, 0)!=-1)
                        {
                            break;
                        }
                    for (i=0; i<5; i++)
                        {
                            protoA[i]= proto[i];
                        }

                    if(action(grilleCpy, protoA, pere, 0)!=-1)
                        {
                            proto[5]=0;
                            break;
                        }

                    for (i=3; i<5; i++)
                        {
                            protoA[i]= proto[i+3];
                        }

                    if(action(grilleCpy, protoA, pere, 0)!=-1)
                        {
                            for (i=0; i<5; i++)
                                {
                                    proto[i]= protoA[i];
                                }
                            proto[5]=0;
                            break;
                        }
                    break;
                case 11:
                    for (i=0; i<5; i++)
                        {
                            protoA[i]= proto[i];
                        }

                    if(action(grilleCpy, protoA, pere, 0)!=-1)
                        {
                            proto[5]=0;
                            break;
                        }

                    for (i=3; i<5; i++)
                        {
                            protoA[i]= proto[i+3];
                        }

                    if(action(grilleCpy, protoA, pere, 0)!=-1)
                        {
                            for (i=0; i<5; i++)
                                {
                                    proto[i]= protoA[i];
                                }
                            proto[5]=0;
                            break;
                        }

                    for (i=3; i<5; i++)
                        {
                            protoA[i]= proto[i+6];
                        }

                    if(action(grilleCpy, protoA, pere, 0)!=-1)
                        {
                            for (i=0; i<5; i++)
                                {
                                    proto[i]= protoA[i];
                                }
                            proto[5]=0;
                            break;
                        }

                    for (i=0; i<8; i++)
                        {
                            protoB[i]= proto[i];
                        }
                    if(action(grilleCpy, protoB, pere, 0)!=-1)
                        {
                            proto[8]=0;
                            break;
                        }

                    for (i=5; i<8; i++)
                        {
                            protoB[i]= proto[i+3];
                        }
                    if(action(grilleCpy, protoB, pere, 0)!=-1)
                        {
                            for (i=0; i<8; i++)
                                {
                                    proto[i]= protoB[i];
                                }
                            proto[8]=0;
                            break;
                        }


                    for (i=3; i<8; i++)
                        {
                            protoB[i]= proto[i+3];
                        }

                    if(action(grilleCpy, protoB, pere, 0)!=-1)
                        {
                            for (i=0; i<8; i++)
                                {
                                    proto[i]= protoB[i];
                                }
                            proto[8]=0;
                            break;
                        }
                    break;
                }
            free(protoA);
            protoA=NULL;
            free(protoB);
            protoB = NULL;
            freeGrille(grilleCpy);
        }
    return proto;
}

void setVictoire(int v)
{
    victoire = v;
}


void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
        {
            c = getchar();
        }
}

void interaction(char * coup , pion ** grille , char* joueur , int mode, struct coup * pere,int pipe)
{
    int len;
    len = read(pipe,coup,13);
    //fgets(coup, 13, stdin);
    coup[len]=0;
    coup = correrction(grille, coup, pere);


    /* int len; */
    /* read(0,coup,13) */
    /* fgets(coup, 13, stdin); */
    /* len = (int)strlen(coup); */
    /* coup[len-1]=0; */
    /* coup = correrction(grille, coup, pere); */
}

void * jouer_radio(void * rdy_p)
{
    char *coup;
    int * rdy = (int *)rdy_p;
    struct coup * pere;
    char joueur;
    int i;
    int pipeDes[2];
    pipe(pipeDes);
    pion ** grille;
    initMap();
    joueur='A';
    grille = initGrille();
    coup =malloc(sizeof(char)*13);
    for(i=0; i<13; i++)
        {
            coup[i]=0;
        }

    int mode = 2;
    int difficulter = 1;
    int type = 0;
    while (!victoire)
        {
            ready_to_play = 0;
            if(joueur == 'A')
                {
                    updateMap(grille);
                    //affiche();
                    *rdy = pipeDes[1];

                    pere = malloc(sizeof(struct coup));
                    pere->proto = NULL;
                    pere->coupSuivant = NULL;
                    pere = coupsPossibles(grille, 'A',pere);
                    do
                        {
                            interaction(coup, grille, &joueur, mode,pere,pipeDes[0]);
                        }
                    while (action(grille, coup, pere,1)==-1);
                    freeCoup(pere,1);
                    joueur = 'B';
                }
            if(joueur == 'B')
                {
                    updateMap(grille);
                    //affiche();

                    if(!victoire)
                        {
                            jouerCoupIA(grille, 'B',difficulter,0,0,type);
                            joueur = 'A';
                        }
                }
        }
    freeMap();
    free(grille);
    free(coup);
    return NULL;
}

