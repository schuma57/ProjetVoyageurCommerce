#include "DessinGraphe.h"


/*static*/ void DessinGraphe::ecrireEntete(ofstream & of, const string & titre, const string & legende, const string & resume, const Vecteur2D & coinBG, const Vecteur2D & coinHD)
{
	of << "titre = " << titre << endl;
	of << "legende = " << legende << endl;
	of << "resume = " << resume << endl;
	of << "type de scene = courbes" << endl;
	of << "coin bas gauche de la figure sur l'�cran en coordonn�es monde = " << coinBG << endl;
	of << "coin haut droit de la figure sur l'�cran en coordonn�es monde = " << coinHD << endl;
}


/*static*/ void DessinGraphe::ecritNombrePointsRemarquables(ofstream & of, int nombrePoints)
{
	of << "nombre de points remarquables = " << nombrePoints << endl;
}


/*static*/ void DessinGraphe::ecritRepere(ofstream & of, const string & couleur)
{
	of << "point remarquable = 2 black (0,0) O" << endl;
	of << "point remarquable = 2 black (1,0) 1" << endl;
	of << "point remarquable = 2 black (0,1) 1" << endl;
}


/*static*/ void DessinGraphe::ecritNombreCourbes(ofstream & of, int nombreCourbes)
{
	of << "nombre de courbes = " << nombreCourbes << endl;
}
