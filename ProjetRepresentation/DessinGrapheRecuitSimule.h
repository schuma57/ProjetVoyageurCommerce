#pragma once

//!
//! \file DessinGrapheRecuitSimule.h
//!

#include <fstream>
#include <string>
#include "Graphe.h"
#include "InfoSommetCarte.h"
#include "InfoAreteCarte.h"
using namespace std;

//!
//! \class DessinGrapheRecuitSimule
//!
class DessinGrapheRecuitSimule
{
public:
	/**

	rayonSommet est le rayon des sommets sur l'�cran
	*/
	static void ecritSommets(ofstream & of, const Graphe<InfoAreteCarte, InfoSommetCarte> & graphe, const double & rayonSommet, const string & couleur);

	static void ecritAretes(ofstream & of, const Graphe<InfoAreteCarte, InfoSommetCarte> & graphe, const string & couleur);


	/**
	�crit le graphe-carte routi�re sur le fichier texte de dessin of.
	suppose of d�j� ouvert en �criture seule

	rayonSommet est le rayon des sommets sur l'�cran
	*/
	static void ecritGraphe(ofstream & of, Graphe<InfoAreteCarte, InfoSommetCarte> & graphe,
		const Vecteur2D & coinBG, const Vecteur2D & coinHD,
		const string & couleurRepere,
		const double & rayonSommet,
		const string & couleurSommets,
		const string & couleurAretes);
};
