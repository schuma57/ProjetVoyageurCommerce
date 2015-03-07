#include <iostream>
#include <fstream>
#include <string>
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
using namespace std;

#define S1 7				// nombre de sommets du graphe g1
#define A1 (S1*(S1-1)/2)	// nombre d'arêtes du graphe g1 car g1


int main()
{
	string filename = "";
	VisitorBSplines visitor;
	
	cout << "construction d'un graphe complet a 6 sommets" << endl;

	Graphe<InfoAreteCarte, InfoSommetCarte> g1;	// création du graphe g1 vide

	//----------------------- on crée les sommets dans g1 -------------------------------------

	Sommet<InfoSommetCarte> * s[S1];
	s[0] = g1.creeSommet(InfoSommetCarte("s0", Vecteur2D(1, 2)));
	s[1] = g1.creeSommet(InfoSommetCarte("s1", Vecteur2D(3, 1)));
	s[2] = g1.creeSommet(InfoSommetCarte("s2", Vecteur2D(5, 2)));
	s[3] = g1.creeSommet(InfoSommetCarte("s3", Vecteur2D(5, 4)));
	s[4] = g1.creeSommet(InfoSommetCarte("s4", Vecteur2D(3, 5)));
	s[5] = g1.creeSommet(InfoSommetCarte("s5", Vecteur2D(1, 4)));
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
	//--------------- ca y est, g1 est créé et complet ----------------------------------


	// ----------------- on affiche sur la console toutes les informations contenues dans g1
	cout << "g1 = " << endl << g1 << endl;

	//----------------- on crée le fichier texte pour dessiner g1 ------------------------------
	/*cout << "entrez le nom du fichier de sauvegarde (sans extension) : ";
	cin >> filename;

	string nomFichierDessin = "" +filename +".txt";
	ofstream f("sauvegarde/"+nomFichierDessin);							// ouverture de f en écriture, en mode texte (cf. doc cplusplus.com)
	Vecteur2D coinBG(-1, -1), coinHD(5, 5);					// limites de la fenêtre à visualiser. calculées à partir des coordonnées des sommets
	string couleurRepere = "blue";
	int rayonSommet = 5;									// unité :  pixel
	string couleurSommets = "red";
	string couleurAretes = "blue";

	DessinGrapheRecuitSimule::ecritGraphe(f, g1, coinBG, coinHD, couleurRepere, rayonSommet, couleurSommets, couleurAretes);

	cout << "le fichier texte de  dessin " << nomFichierDessin << " a ete cree" << endl;
	*/


	//------------------- creer cycle hamilton -------------------------------
	vector< Arete<InfoAreteCarte, InfoSommetCarte> > cycle = Cycle<InfoAreteCarte, InfoSommetCarte>::getHamiltonCycle(g1);

	cout << "------------- voici le cycle --------------" << endl;
	for (auto t : cycle)
	{
		cout << t << endl;
	}

	//----------------------------------------------------


	//--------------- on dessine via le serveur ------------------------------
	//g1.accept(&visitor);

	return 0;
}