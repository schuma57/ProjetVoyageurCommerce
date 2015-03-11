//!
//! \file Principale.cpp
//!

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "Graphe.h"
#include "Arete.h"
#include "Sommet.h"
#include "Cycle.h"
#include "Vecteur2D.h"
#include "InfoAreteCarte.h"
#include "InfoSommetCarte.h"
#include "DessinGrapheRecuitSimule.h"
#include "OutilsCarteRecuitSimule.h"
#include "VisitorBSplines.h"
#include "RecuitSimule.h"
using namespace std;

#define S1 7				// nombre de sommets du graphe g1
#define A1 (S1*(S1-1)/2)	// nombre d'arêtes du graphe g1 car g1


double coutCycle(const Graphe<InfoAreteCarte, InfoSommetCarte> & cycle)
{
	double somme(0);
	PElement<Arete<InfoAreteCarte, InfoSommetCarte>>* aretes = new PElement<Arete<InfoAreteCarte, InfoSommetCarte>>(*cycle.lAretes);
	
	while (aretes)
	{
		somme += aretes->v->v.cout;
		aretes = aretes->s;
	}
	return somme;
}


const Graphe<InfoAreteCarte, InfoSommetCarte> transformationCycle(const Graphe<InfoAreteCarte, InfoSommetCarte> & cycle)
{
	bool continuer = false;
	Graphe<InfoAreteCarte, InfoSommetCarte> nouveau = cycle;
	const int NB = cycle.nombreSommets();

	PElement<Arete<InfoAreteCarte, InfoSommetCarte>>* it1;
	PElement<Arete<InfoAreteCarte, InfoSommetCarte>>* it2;

	do
	{
		continuer = false;
		it1 = nouveau.lAretes;

		int random = rand() % NB;
		for (int j = 0; j < random; j++)
		{
			it1 = it1->s;
		}

		do
		{
			it2 = nouveau.lAretes;
			int random2 = rand() % NB;
			for (int j = 0; j < random2; j++)
			{
				it2 = it2->s;
			}

		} while (it1->v->debut == it2->v->debut || it1->v->debut == it2->v->fin
			|| it1->v->fin == it2->v->debut || it1->v->fin == it2->v->fin);

		Sommet<InfoSommetCarte> *droite1, *droite2, *gauche1, *gauche2;
		gauche1 = it1->v->debut;
		gauche2 = it2->v->debut;
		droite1 = it1->v->fin;
		droite2 = it2->v->fin;

		if (nouveau.getAreteParSommets(gauche1, droite2) != NULL
			|| nouveau.getAreteParSommets(gauche2, droite1) != NULL)
				continuer = true;
		else
		{
			PElement<Arete<InfoAreteCarte, InfoSommetCarte>>::retire(it1->v, nouveau.lAretes);
			PElement<Arete<InfoAreteCarte, InfoSommetCarte>>::retire(it2->v, nouveau.lAretes);

			double d = OutilsCarteRecuitSimule::distance(gauche1, droite2);
			nouveau.creeArete(gauche1, droite2, InfoAreteCarte(d));

			d = OutilsCarteRecuitSimule::distance(gauche2, droite1);
			nouveau.creeArete(gauche2, droite1, InfoAreteCarte(d));
		}
	} while (continuer);

	return nouveau;
}


double successeur(const double & temperature)
{
	return temperature - 1;
}


void creerFichier(Graphe<InfoAreteCarte, InfoSommetCarte> & graphe)
{
	string filename = "";

	cout << "entrez le nom du fichier de sauvegarde (sans extension) : ";
	cin >> filename;

	string nomFichierDessin = "" + filename + ".txt";
	ofstream f("sauvegarde/" + nomFichierDessin);				// ouverture de f en écriture, en mode texte (cf. doc cplusplus.com)
	Vecteur2D coinBG(-1, -1), coinHD(5, 5);					// limites de la fenêtre à visualiser. calculées à partir des coordonnées des sommets
	string couleurRepere = "blue";
	int rayonSommet = 5;									// unité :  pixel
	string couleurSommets = "red";
	string couleurAretes = "blue";

	DessinGrapheRecuitSimule::ecritGraphe(f, graphe, coinBG, coinHD, couleurRepere, rayonSommet, couleurSommets, couleurAretes);

	cout << "le fichier texte de  dessin " << nomFichierDessin << " a ete cree" << endl;
}


int main()
{
	srand(time(NULL));
	VisitorBSplines visitor;

	//---------------------------- les pointeurs de fonction ---------------------------------
	double(*succ)(const double & temperature);
	succ = successeur;

	double(*coutSolution)(const Graphe<InfoAreteCarte, InfoSommetCarte> & solution);
	coutSolution = coutCycle;

	const Graphe<InfoAreteCarte, InfoSommetCarte>(*changementAleatoire)(const Graphe<InfoAreteCarte, InfoSommetCarte> & solution);
	changementAleatoire = transformationCycle;
	
	double  tInitiale = 1000;
	double  tFinale = 0;
	int nombreTentativesMax = 50;
	int nombreSuccesMax = 25;
	double coutMeilleureSolution;


	//--------------------------- construction du graphe -------------------------------------
	cout << "construction d'un graphe complet a 6 sommets" << endl;
	Graphe<InfoAreteCarte, InfoSommetCarte> g1;


	//----------------------- on crée les sommets dans g1 -------------------------------------
	Sommet<InfoSommetCarte> * s[S1];
	s[0] = g1.creeSommet(InfoSommetCarte("s0", Vecteur2D(1, 2)));
	s[1] = g1.creeSommet(InfoSommetCarte("s1", Vecteur2D(4, 1)));
	s[2] = g1.creeSommet(InfoSommetCarte("s2", Vecteur2D(6, 2)));
	s[3] = g1.creeSommet(InfoSommetCarte("s3", Vecteur2D(5, 4)));
	s[4] = g1.creeSommet(InfoSommetCarte("s4", Vecteur2D(3, 5)));
	s[5] = g1.creeSommet(InfoSommetCarte("s5", Vecteur2D(0, 4)));
	s[6] = g1.creeSommet(InfoSommetCarte("s6", Vecteur2D(2, 4)));


	//----------------------- on crée les arêtes dans g1 --------------------------------------
	Arete<InfoAreteCarte, InfoSommetCarte> * a[A1];

	int i, j;	// indices des sommets
	int k;		// indice de l'arête courante

	for (i = 0, k = 0; i < S1; ++i)
		for (j = i + 1; j < S1; ++j)
		{
			double d = OutilsCarteRecuitSimule::distance(s[i], s[j]);  // calcul de la distance du sommet s[i] à s[j]
			a[k++] = g1.creeArete(s[i], s[j], InfoAreteCarte(d));
		}
	//-------------------------- g1 est créé et complet ----------------------------------


	// ----------------- on affiche sur la console toutes les informations contenues dans g1
	cout << "g1 = " << endl << g1 << endl;


	//----------------- on crée le fichier texte pour dessiner g1 ------------------------------
	//creerFichier(g1);


	//-------------------------- creer cycle hamilton --------------------------------
	Graphe<InfoAreteCarte, InfoSommetCarte> cycleHamilton = Cycle<InfoAreteCarte, InfoSommetCarte>::getHamiltonCycle(g1);

	cout << "------------- voici le cycle --------------" << endl;
	cout << cycleHamilton << endl;
	//creerFichier(cycleHamilton);
	

	//---------------------------- Cout du cycle initial -------------------------------
	cout <<"Cout du cycle initial : "<< coutCycle(cycleHamilton) << endl;
	

	//---------------------------- on utilise le recuit simule ---------------------------
	Graphe<InfoAreteCarte, InfoSommetCarte> solution = recuitSimule(
		tInitiale, tFinale, nombreTentativesMax, nombreSuccesMax,
		cycleHamilton,
		coutSolution,
		changementAleatoire,
		succ,
		coutMeilleureSolution
		);
	

	//---------------------------- on affiche le meilleur cout ---------------------------
	cout << endl << "le meilleur cout !" << endl;
	//cout << endl << solution << endl;
	cout << coutCycle(solution) << endl;
	//creerFichier(solution);


	//--------------- on dessine via le serveur ------------------------------
	//g1.accept(&visitor);
	//solution.accept(&visitor);

	return 0;
}
