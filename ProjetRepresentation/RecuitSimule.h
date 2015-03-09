#pragma once

//!
//! \file RecuitSimule.h
//!

#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
#define K 1

inline double tirageAleatoire(const double & a, const double &b)
{
	const static int MAX(100);
	const static double MAX1(99);

	int n = rand() % MAX;	// n est tiré au hasard tel que 0 <= n <= MAX-1

	double x = n / MAX1; // x est un nombre réel au hasard entre 0 et 1 compris

	return a + (b - a)*x;
}

/**

Représente une mise en oeuvre de l'algorithme heuristique "recuit simulé"

le but est de trouver le minimum de la fonction cout()

S est l'ensemble des solutions ou encore le domaine d'exploration

@param tInitiale : température initiale
@param tFinale : température finale telle que tFinale <= tInitiale
@param nombreTentativesMax : nombre maximal de tentatives par palier de température
@param nombreSuccesMax : nombre maximal de succès par palier de température
@param solutionInitiale : solution initiale du problème
@param fonction cout1(...) : permet d'évaluer la qualité d'une solution, plus le coût est faible, meilleure est la solution
@param fonction changementAleatoire(...) : construit une nouvelle solution par perturbation aléatoire de la solution courante
@param fonction succ(...) : calcule la température suivante de la température courante. Doit vérifier succ(t) < t, quelque soit t

@return bestSolution : la meilleure solution trouvée
retourne aussi le coût de la meilleure soution grâce au paramètre coutBestSolution
*/
template <class S>
const S recuitSimule(const double & tInitiale, const double & tFinale, const int nombreTentativesMax, const int nombreSuccesMax, const S & solutionInitiale,
	double(*cout1)(const S & solution), const S(*changementAleatoire)(const S & solution), double(*succ)(const double & temperature), double & coutBestSolution)
{
	S solutionCourante, bestSolution;
	double t; // température courante
	double coutCourant;

	solutionCourante = solutionInitiale;
	bestSolution = solutionInitiale;
	for (t = tInitiale, coutBestSolution = coutCourant = cout1(solutionInitiale); t > tFinale; t = succ(t))
	{
		int nombreTentatives, nombreSucces;
		S solutionPrecedente;
		double coutPrecedent;

		for (nombreTentatives = nombreSucces = 0; nombreTentatives < nombreTentativesMax && nombreSucces < nombreSuccesMax; ++nombreTentatives)
		{
			solutionPrecedente = solutionCourante;
			coutPrecedent = coutCourant;
			solutionCourante = changementAleatoire(solutionCourante);
			coutCourant = cout1(solutionCourante);
			
			//cout<< "solution courante = " << solutionCourante<<", cout = " << coutCourant << endl;
			if (coutCourant < coutPrecedent)  // la solution courante est meilleure que la solution précédente
			{
				++nombreSucces;
				if (coutCourant < coutBestSolution)	// la solution courante est meilleure que la meilleure solution trouvée jusqu'à présent
				{
					bestSolution = solutionCourante; coutBestSolution = coutCourant;
				}
			}
			else	// coûtCourant >= coûtPrécédent. La solution courante n'est pas meilleure que la solution précédente
			{
				double v = tirageAleatoire(0, 1);
				double deltaCout = coutCourant - coutPrecedent; // on a deltaCout >= 0
				double metropolis = exp(-K*deltaCout / t);

				if (v < metropolis) ++nombreSucces;		// la solution courante est acceptée bien que moins bonne que la précédente
				else
				{
					solutionCourante = solutionPrecedente; coutCourant = coutPrecedent;
				}	// la solution courante est refusée

			}	// coûtCourant >= coûtPrécédent.

		}	 // for, boucle tentatives d'améliorations

		if (nombreSucces == 0) return bestSolution;		// l'algorithme est stationnaire : il a atteint un minimum, on arrête tout et on retourne la meilleure solution trouvée
	}	// for, boucle température

	return bestSolution;
}
