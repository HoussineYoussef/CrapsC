// Houssine Youssef 21601530
#include <stdio.h>
#include <stdlib.h>


struct joueur 
{
	
	char* nom[20];
	int poche; 
	int pari ; // 0 = aucun , 1 = pass , 2 = don't pass
	int sum_pari; // somme du pari en cours
	int pStatus; // 1 si il joue 2 si il ne joue pas 
	int score; // score du joueurs = Nombre de fois ou il mise correctement pendant une partie
};
//*****************FONCTIONS DE BASE *****************************************
int lanceDes();//ALGORITHME DU LANCER DE DES , DE MANIERE EQUIPROBABLE
//****************************************************************************
//-------------Determination du nombre de joueurs-------------//
int nombreJoueurs(void);
//---------------------------------------------------------------------------------------------------------
// Display des infos joueurs 
void Display(int nb, struct joueur *joueurs);
//*****************MISE EN PLACE DU MENU**************************************
struct joueur *initialisation(int nb); // Lance le menu 



//--------------mises
struct joueur *mises(int nb , struct joueur *joueurs);
//---Mise au premier suspens -------------------------------------------------------------------------------------------------------------------
void mise2(int suspens ,int nb, struct joueur *joueurs);
//--------------mises pendant le suspens du point càd quand on a ni le point ni un 7 on peut changer la mise de manière spécifique.-----------
struct joueur *mise_suspens(int suspens,int nb , struct joueur *joueurs);
//-----------------determination du point 
struct joueur *point(int nb , struct joueur *joueurs);

void play(); // fonction pour jouer

void score(int nb, struct joueur *joueurs); // fonction du score 

int testj(int nb, struct joueur *joueurs); // test si au moins encore 1 joueur est en jeu
