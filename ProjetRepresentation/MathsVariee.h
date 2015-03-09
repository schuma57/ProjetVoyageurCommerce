#pragma once

#include <math.h>
#include "AlgebreLineaire.h"
//#include "MesMaths.h"
#include "Vecteur2D.h"

#define M_PI 5

/**
fonction dont la courbe C est une parabole de sommet (2,3). (2,3) est le point de la courbe C d'ordonn�e la plus petite
*/
inline double f1(const double & x)
{
	double t = x - 2;
	return t*t + 3;		// f1(x) = (x-2)^2 + 3  donc le minimum est f1(2) = 3
}


/**
fonction dont la courbe C est une sinuso�de amortie de minimum -5 en 0 de pseudo p�riode 1.
*/
inline double f2(const double & t)
{
	static double A = 5;
	static double w = 2 * M_PI;

	return -A*cos(w*t) / (1 + abs(t));
}

/**
fonction � 2 variables (x,y) dont la surface  S est un parabolo�de de sommet (2,2,3). (2,2,3) est le point de la surface S de cote la plus petite
*/
inline double f1(const Vecteur2D & u)
{
	Vecteur2D t = u - Vecteur2D(2, 2);
	return t*t + 3;	// f1(x,y) = (x-2)^2 + (y-2)^2 +  3  donc le minimum est f12(2,2) = 3
}


/**
fonction � 2 variables dont la surface est une onde plane radiale amortie de maximum 5 en (0,0) de pseudo p�riode 1.
*/
inline double f2(const Vecteur2D & u)
{
	return f2(norme(u));
}
