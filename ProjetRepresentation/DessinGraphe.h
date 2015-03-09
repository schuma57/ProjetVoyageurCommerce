#pragma once

#include <fstream>
#include "Vecteur2D.h"
#include "Graphe.h"
#include "InfoAreteCarte.h"
#include "InfoSommetCarte.h"
using namespace std;


//!
//! \class DessinGraphe
//!
class DessinGraphe
{
public:

	static void ecrireEntete(ofstream & of, const string & titre, const string & legende, const string & resume, const Vecteur2D & coinBG, const Vecteur2D & coinHD);
	static void ecritNombrePointsRemarquables(ofstream & of, int nombrePoints);
	static void ecritRepere(ofstream & of, const string & couleur);

	static void ecritNombreCourbes(ofstream & of, int nombreCourbes);
};
