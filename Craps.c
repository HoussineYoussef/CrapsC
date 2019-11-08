// Houssine Youssef 21601530
#include <stdio.h>
#include <stdlib.h>
#include "Craps.h" // prototypes
#include <time.h> // pour srand(time(NULL)

//---------------Nombre de joueurs---------------------//
int nombreJoueurs(void) {
	int nbJoueurs;

	printf("Bienvenue sur mon jeu de Craps : Pour r\202gler votre jeu, veuillez suivre les indications suivantes \n");
	printf("Combien de joueurs vont jouer ? (min 1) ");

	scanf("%d", &nbJoueurs);
	printf("Vous serez donc %d joueur(s)\n", nbJoueurs);
	return nbJoueurs;
}

//-------------------Supprimer Joueurs------------------------------------------------------------------------------------//
/*struct joueur *suppr(int nb, struct joueur *joueurs) {
	int reponse;
	int i;
	int j ;

	for (i = 0; i < nb; i++) {
		printf("Avant que le tour ne commence : %s voulez vous quitter la partie maintenant ?( 0 = non , 1 = oui )\n" ,(joueurs + i)->nom);
		scanf("%d", &reponse);
		if (reponse == 1) {
			for ( j = i; i < nb - 1; i++) {
				for (j = i + 1; j < i; j++) {
					joueurs[i] = joueurs[j];
				}
			}
			joueurs = realloc(joueurs, sizeof(int) * --nb);

		}
		else {
			printf("D'accord vous restez\n");
		}
		
	}
	return joueurs;

}
*/

//-------------------Initialisation de ma liste de joueurs ---------------------------------------------------------------//
struct joueur *initialisation(int nb) {
	
	struct joueur *joueurs = (struct joueur*) malloc(nb * sizeof(struct joueur));
	int i;
	for (i = 0; i < nb; i++) {

		printf("Donner le nom du joueur %d : ", i);
		scanf("%s", &joueurs[i].nom);
		printf("Donner le budget %d : ", i);
		scanf("%d", &joueurs[i].poche);
		(joueurs + i)->score = 0; // Nombre de fois ou le joueur fait la bonne mise.
		(joueurs + i)->pStatus = 1; // On part du principe ou tout joueur inscrit va jouer 
	}
	return joueurs;
}

	//--------------------------------------------------Ask mises--------------------------------------------------------------------------
struct joueur *mises(int nb,struct joueur *joueurs) {
	int i = 0;
	int mise;

	for (i; i <nb; i++) {
		mise = 0;
		if ((joueurs + i)->poche > 0 && (joueurs + i)->pStatus == 1) {
			printf("%s , quel type de mise faites vous ? ( 0 rien , 1 pass , 2 don't pass) :\n", (joueurs + i)->nom);
			scanf("%d", &(joueurs + i)->pari);
			if ((joueurs + i)->pari != 0) {
				printf("%s , quelle somme allez vous miser ? Sachant que vous avez %d  \n", (joueurs + i)->nom, (joueurs + i)->poche);
				scanf("%d", &mise);
				if (mise > (joueurs + i)->poche) {
					printf("Mise non valide , elle a donc été remplac\202e par votre budget max\n");
					(joueurs + i)->sum_pari = (joueurs + i)->poche;
				}
				else {
					(joueurs + i)->sum_pari = mise;
				}
			}
			else {
				printf("%s vous ne misez rien sur ce tour \n" , (joueurs + i)->nom );
				(joueurs + i)->pStatus = 0;
				(joueurs + i)->sum_pari = 0; // Pour éviter un affichage matrixé 

			}
		}
	}
	return joueurs;
}
// modification de mise entre deux lancés de dés //---------------------------------------------------------------------------------------------------------------------
struct joueur *mise_suspens(int suspens, int nb , struct joueur *joueurs) {
	int i = 0;
	int reponse = 0;
	int reponse2 = 0;
	for (i = 0; i < nb; i++) {
		if (suspens == 2) {
			if ((joueurs + i)->pari == 2 || (joueurs + i)->pari == 1 && (joueurs + i)->pStatus == 1  && (joueurs + 1)->poche > 0) { //si le joueur parie sur don't pass ou pass il peut que diviser sa mise par 2 que sur le 1er suspens
				printf("%s voulez vous doubler votre mise ? 0 si vous ne voulez pas , 1 si vous le voulez :", (joueurs + i)->nom);
				scanf("%d", &reponse);
				if (reponse == 1) {
					if ((joueurs + i)->poche >= ((joueurs + i)->sum_pari * 2)) {
						(joueurs + i)->sum_pari = ((joueurs + i)->sum_pari * 2);
					}
					else { printf("%s ,Action impossible vous n'avez pas assez\n", (joueurs + i)->nom);
					}
				}
				else {
					printf("Vous avez r\202pondu Non\n");
				}

			}
		}
		if (suspens > 2) {
			if ((joueurs + i)->pari == 2 || (joueurs + i)->pari == 1 && (joueurs + i)->pStatus == 1  && (joueurs + 1)->poche > 1) {
				printf("%s voulez vous diviser votre mise par 2 ? 0 si vous ne voulez pas , 1 si vous le voulez : ", (joueurs + i)->nom);
				scanf("%d", &reponse);
			}
			if (reponse == 1) {
				
				
				if (((joueurs + i)->sum_pari / 2) > 1 ) {
					(joueurs + i)->sum_pari = ((joueurs + i)->sum_pari / 2);
				}
				else {
					printf("Vous etes d\202ja en mise minimale \n");
				}
				}
		}
	}
	return joueurs;
}
//--------------Mise entre phase 1 et phase 2 -------------------------------------------------------------------------------
void mise2(int suspens, int nb, struct joueur *joueurs) {
	int i;
	int rep;
	int rep2;
	if (suspens == 1) {
		for (i = 0; i < nb; i++) {
			if ((joueurs + i)->pari == 1 && (joueurs + i)->pStatus == 1) {
				printf("%s Voulez vous augmenter votre mise sachant qu'elle est actuellement de %d ? (0 = non 1 = oui ) :", (joueurs + i)->nom, (joueurs + i)->sum_pari);
				scanf("%d", &rep);
				if (rep == 1) {
					printf("%s de combien voulez vous l'augmenter sachant qu'elle est actuellement de %d :  ", (joueurs + i)->nom, (joueurs + i)->sum_pari);
					scanf("%d", &rep2);
					if (rep2 >= 0 && ((joueurs + i)->sum_pari + rep2 < (joueurs + i)->poche)) {
						(joueurs + i)->sum_pari += rep2;
					}
					else {
						printf("Votre mise n'est pas valide \n");
					}

				}
				else
				{
					printf("Vous avez r\202pondu non\n");
				}
			}
			if ((joueurs + i)->pari == 2 && (joueurs + i)->pStatus == 1 &&(joueurs + 1)->poche >0) {
				printf("%s voulez vous diminuer ou retirer votre mise sachant qu'elle est actuellement de %d ? : (0 = rien faire 1 = diminuer 2 = retirer ) :\n", (joueurs + i)->nom, (joueurs + i)->sum_pari);
				scanf("%d", &rep);
				if (rep == 1) {
					printf("%s de combien voulez vous la diminuer sachant qu'elle est actuellement de %d :", (joueurs + i)->nom, (joueurs + i)->sum_pari);
					scanf("%d", &rep2);
					if ((joueurs + i)->sum_pari - rep2 > 0) {
						(joueurs + i)->sum_pari = (joueurs + i)->sum_pari - rep2;
					}
					else {
						printf("La diminution demand\202e n'est pas valide donc elle n'a pas \202t\202 accept\202e \n ");
					}

				}
				
				if (rep == 2) {
					printf("Votre mise va etre retir\202e et passer a 0\n");
					(joueurs + i)->sum_pari = 0;
					(joueurs + i)->pStatus = 0;
				}

				if (rep == 0) {
					printf("Vous continuez avec la meme mise\n");
				}
			}
		}
	}

}
// ----------------------------------------- determination du  Point et phase 2 ----------------------------------------------------------------------------------------------
struct joueur *point(int nb , struct joueur *joueurs) {
	int phase = 1;
	int valDes;
	int point = 0;
	int i;
	int suspens = 1; //si on est au premier tour de suspens
	mises(nb ,joueurs);

	printf("Debut de la partie d\202termination du point\n");
	point = lanceDes();

	
	
	if (point == 2 || point == 12 || point == 7 && phase == 1) { // 2 et 12 7 en premiere phase
		for (i = 0; i < nb; i++) {
			if (point == 2) {
				if ((joueurs + i)->pari == 1 ) {
					printf("%s a perdu sa mise\n", (joueurs + i)->nom);
					(joueurs + i)->poche = (joueurs + i)->poche - (joueurs + i)->sum_pari;
					(joueurs + i)->score--;

				}
				if ((joueurs + i)->pari == 2 ) { // don't pass gagnent 
					printf("%s gagne sa mise\n", (joueurs + i)->nom);
					(joueurs + i)->poche = (joueurs + i)->poche + (joueurs + i)->sum_pari;
					(joueurs + i)->score++;
				}
			}
			if (point == 12) {
				if ((joueurs + i)->pari == 1) { // ceux qui misent sur pass perdent leur mise
					printf("%s a perdu sa mise\n", (joueurs + i)->nom);
					(joueurs + i)->poche = (joueurs + i)->poche - (joueurs + i)->sum_pari;
					(joueurs + i)->score--;
				}
				if ((joueurs + i)->pari == 2 ) { //ceux qui misent don't pass bénéficient du tour null
					printf("Tour Nul pour %s ayant mis\202 sur don't pass\n", (joueurs + i)->nom);
				}
			}
			if (point == 7) {
				if ((joueurs + i)->pari == 1) { // ceux qui misent sur pass aussi
					printf("%s gagne sa mise\n", (joueurs + i)->nom);
					(joueurs + i)->poche = (joueurs + i)->poche + (joueurs + i)->sum_pari;
					(joueurs + i)->score++;
				}
				if ((joueurs + i)->pari == 2) { //mise sur don't pass
					printf("%s perd sa mise \n ",(joueurs +i)->nom);
					(joueurs + i)->poche = (joueurs + i)->poche - (joueurs + i)->sum_pari;
					(joueurs + i)->score--;
				}	
			}
			(joueurs + i)->pStatus = 1; //tlm à 1
			if ((joueurs + i)->poche == 0) {
				(joueurs + i)->pStatus = 0;
				(joueurs + i)->sum_pari = 0;
			}
			
		}		
	}

	if (point != 2 && point != 7 && point != 12) {
		printf("Le point est egal a %d\n", point);
		phase++;// On passe en phase 2
	}
	if (point == 2 || point == 12) {
		printf("C'est un Craps comme on en voit plus !\n Au tour suivant maintenant ! \n\n ");
	}
	else {
		printf("Le jeu continue\n\n");
	}




	//-------------------------passage phase 2 -------------------------------------------------------------------/////////////////////

	if (phase == 2) { //si on entre en phase 2

		int j = 0;
		
		while (phase != 1) {
			

			mise2(suspens, nb, joueurs);
			suspens++;
			//
			valDes = lanceDes();
			//

			*mise_suspens(suspens, nb , joueurs);
			
			
			for (j = 0; j < nb; j++) {
				if (valDes == point && point != 7) {
					if ((joueurs + j)->pari == 1 && (joueurs + j)->pStatus == 1) { //Ceux qui misent sur pass gagnent
						printf("%s gagne sa mise\n", (joueurs + j)->nom);
						(joueurs + j)->poche = (joueurs + j)->poche + (joueurs + j)->sum_pari;
						(joueurs + j)->score++;
					}
					if ((joueurs + j)->pari == 2 && (joueurs + j)->pStatus == 1) { // Ceux qui misent don't pass perdent
						printf(" %s perd sa mise\n ", (joueurs + j)->nom);
						(joueurs + j)->poche = (joueurs + j)->poche - (joueurs + j)->sum_pari;
						(joueurs + j)->score--;
					}
					phase = 1;
				}
				if (valDes == 7) {
					if ((joueurs + j)->pari == 1 && (joueurs + j)->pStatus == 1) { //ceux qui jouent pass perdent.
						printf("%s perd sa mise\n", (joueurs + j)->nom);
						(joueurs + j)->poche = (joueurs + j)->poche - (joueurs + j)->sum_pari;
						(joueurs + j)->score--;
					}
					if ((joueurs + j)->pari == 2 && (joueurs + j)->pStatus == 1) { //Ceux qui misent sur don't pass gagnent.
						printf(" %s gagne sa mise \n", (joueurs + j)->nom);
						(joueurs + j)->poche = (joueurs + j)->poche + (joueurs + j)->sum_pari;
						(joueurs + j)->score++;
					}
					phase = 1;
				}
				
				if ((joueurs + j)->poche == 0) {
					(joueurs + j)->pStatus = 0;
					(joueurs + j)->sum_pari = 0;
				}
			}
		}
		for (i = 0; i < nb; i++) { //remet tout à 0 car le prochain tour commence
			(joueurs + i)->pari = 0;
			(joueurs + i)->sum_pari = 0;
			if ((joueurs + i)->poche > 0) {
				(joueurs + i)->pStatus = 1;
			}
		}
	}
	// ici on demande un des joueurs veut quitter.
	
	//*suppr(nb, joueurs);
	return joueurs;
}	

//--------------------Affichage des infos en fin de tour -----------------------------
void Display(int nb ,struct joueur *joueurs) {
	int i;
	printf("Informations Joueurs:\n\n\n");
	for (i = 0; i < nb; ++i) {
		printf("Nom: %s\tBudget= %d  pari= %d somme pari= %d    score personnel= %d\n\n", (joueurs + i)->nom, (joueurs + i)->poche, (joueurs + i)->pari, (joueurs + i)->sum_pari, (joueurs + i)->score);
	}
	
}

//-------------------Score max------------------------
void score(int nb , struct joueur *joueurs) {
	int i = 0;
	int max;
	int numMax;
	max = (joueurs + 0)->score;
	for (i = 0; i < nb; i++) {
		if ((joueurs + i)->score >= max) {
			numMax = i;
			max = ((joueurs + i)->score);
		}
	}
	
	printf("Le score maximum de la partie est obtenu par %s avec un score de %d \n\n", (joueurs + numMax)->nom, max);
}

//--------------- créations du lancé de dés ( 100 % equiprobabale après calcul de l'espérance ) -------------------------------
int lanceDes()
{
	int sommedes;
	int de2;
	int de1;
	de1 = rand() % 7;
	while (de1 == 0)
	{
		de1 = rand() % 7;
	}
	de2 = rand() % 7;
	while (de2 == 0)
	{
		de2 = rand() % 7;
	}
	sommedes = de1 + de2;
	printf("Les d\202s sont lanc\202s et rendent %d \n", sommedes);
	return sommedes;
}

//-----------------Test si au moins un joueur est encore en jeu ( pStatus == 1) -------------------------------------------------
int testj(int nb, struct joueur *joueurs) {
	int i = 0;
	int res = 0;
	for (i; i < nb; i++) {
		if ((joueurs + i)->pStatus == 1) { //au moins un joueur est encore en jeu
			res = 1;
		}
	}
	return res;
}
//------------------------------------JOUER-------------------------------------------------------------------------------------
void play() { //fonction qui lance le jeu.
	struct joueur *ini;
	int nb;
	int rep;
	int status = 1;
	int test = 0; 
	nb = nombreJoueurs(); // c'est le nombre de joueurs pendant la partie.
	ini = initialisation(nb); //C'est la liste des joueurs que je vais manipuler le long de la partie.
	test = testj(nb, ini);
	while (status == 1 && testj) {
		point(nb, ini);
		Display(nb, ini);
		printf("Voulez vous continuer a jouer ? ( 0 = non 1 = oui )R\202ponse : ");
		scanf("%d", &rep);
		if (rep == 0) {
			score(nb, ini);
			Display(nb, ini);
			printf("Fin de la partie, merci d'avoir jou\202 \n");

			status--; 
			free(ini); // Quand on finit on libère la mémoire 
		}
	}
}

