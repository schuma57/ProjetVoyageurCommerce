#pragma once

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

	int n = rand() % MAX;	// n est tir� au hasard tel que 0 <= n <= MAX-1

	double x = n / MAX1; // x est un nombre r�el au hasard entre 0 et 1 compris

	return a + (b - a)*x;
}

/**

Repr�sente une mise en oeuvre de l'algorithme heuristique "recuit simul�"

le but est de trouver le minimum de la fonction cout()

S est l'ensemble des solutions ou encore le domaine d'exploration

@param tInitiale : temp�rature initiale
@param tFinale : temp�rature finale telle que tFinale <= tInitiale
@param nombreTentativesMax : nombre maximal de tentatives par palier de temp�rature
@param nombreSuccesMax : nombre maximal de succ�s par palier de temp�rature
@param solutionInitiale : solution initiale du probl�me
@param fonction cout1(...) : permet d'�valuer la qualit� d'une solution, plus le co�t est faible, meilleure est la solution
@param fonction changementAleatoire(...) : construit une nouvelle solution par perturbation al�atoire de la solution courante
@param fonction succ(...) : calcule la temp�rature suivante de la temp�rature courante. Doit v�rifier succ(t) < t, quelque soit t

@return bestSolution : la meilleure solution trouv�e
retourne aussi le co�t de la meilleure soution gr�ce au param�tre coutBestSolution
*/
template <class S>
const S recuitSimule1(const double & tInitiale, const double & tFinale, const int nombreTentativesMax, const int nombreSuccesMax, const S & solutionInitiale,
	double(*cout1)(const S & solution), const S(*changementAleatoire)(const S & solution), double(*succ)(const double & temperature), double & coutBestSolution)
{
	S solutionCourante, bestSolution;
	double t; // temp�rature courante
	double coutCourant;

	for (t = tInitiale, bestSolution = solutionCourante = solutionInitiale, coutBestSolution = coutCourant = cout1(solutionInitiale); t > tFinale; t = succ(t))
	{
		int nombreTentatives, nombreSucces;
		S solutionPrecedente; double coutPrecedent;

		for (nombreTentatives = nombreSucces = 0; nombreTentatives < nombreTentativesMax && nombreSucces < nombreSuccesMax; ++nombreTentatives)
		{
			solutionPrecedente = solutionCourante;
			coutPrecedent = coutCourant;
			solutionCourante = changementAleatoire(solutionCourante);
			coutCourant = cout1(solutionCourante);
			
			//cout<< "solution courante = " << solutionCourante<<", cout = " << coutCourant << endl;
			if (coutCourant < coutPrecedent)  // la solution courante est meilleure que la solution pr�c�dente
			{
				++nombreSucces;
				if (coutCourant < coutBestSolution)	// la solution courante est meilleure que la meilleure solution trouv�e jusqu'� pr�sent
				{
					bestSolution = solutionCourante; coutBestSolution = coutCourant;
				}
			}
			else	// co�tCourant >= co�tPr�c�dent. La solution courante n'est pas meilleure que la solution pr�c�dente
			{
				double v = tirageAleatoire(0, 1);
				double deltaCout = coutCourant - coutPrecedent; // on a deltaCout >= 0
				double metropolis = exp(-K*deltaCout / t);

				if (v < metropolis) ++nombreSucces;		// la solution courante est accept�e bien que moins bonne que la pr�c�dente
				else
				{
					solutionCourante = solutionPrecedente; coutCourant = coutPrecedent;
				}	// la solution courante est refus�e

			}	// co�tCourant >= co�tPr�c�dent.

		}	 // for, boucle tentatives d'am�liorations

		if (nombreSucces == 0) return bestSolution;		// l'algorithme est stationnaire : il a atteint un minimum, on arr�te tout et on retourne la meilleure solution trouv�e
	}	// for, boucle temp�rature

	return bestSolution;
}

template <class S>
class SolutionCout
{
public:
	S solution;
	double cout; // cout de solution

	SolutionCout(const S & solution, double(*cout1)(const S & solution)) :solution(solution), cout(cout1(solution)) {}

	const SolutionCout<S> change(const S(*changementAleatoire) (const S & solution), double(*cout1) (const S & solution)) const;

	operator string() const;
};

template <class S>
ostream & operator << (ostream & os, const SolutionCout<S> & solutionCout)
{
	return os << (string)solutionCout;
}

template <class S>
const SolutionCout<S> SolutionCout<S>::change(const S(*changementAleatoire) (const S & solution), double(*cout1) (const S & solution)) const
{
	return SolutionCout<S>(changementAleatoire(this->solution), cout1);
}

template <class S>
SolutionCout<S>::operator string() const
{
	ostringstream oss;

	oss << "( " << solution << ", " << cout << ")";
	return oss.str();
}

template <class S>
const SolutionCout<S> recuitSimule(const double & tInitiale, const double & tFinale, const int nombreTentativesMax, const int nombreSuccesMax, const S & solutionInitiale,
	double(*cout1)(const S & solution), const S(*changementAleatoire)(const S & solution), double(*succ)(const double & temperature))
{
	SolutionCout<S>  solutionCourante(solutionInitiale, cout1);
	SolutionCout<S> bestSolution(solutionCourante);
	double t; // temp�rature courante

	for (t = tInitiale; t > tFinale; t = succ(t))
	{
		int nombreTentatives, nombreSucces;

		for (nombreTentatives = nombreSucces = 0; nombreTentatives < nombreTentativesMax && nombreSucces < nombreSuccesMax; ++nombreTentatives)
		{

			SolutionCout<S> solutionPrecedente(solutionCourante);
			solutionCourante = solutionCourante.change(changementAleatoire, cout1);

			//cout<< "solution courante = " << solutionCourante << endl;
			if (solutionCourante.cout < solutionPrecedente.cout)  // la solution courante est meilleure que la solution pr�c�dente
			{
				++nombreSucces;
				if (solutionCourante.cout < bestSolution.cout)	// la solution courante est meilleure que la meilleure solution trouv�e jusqu'� pr�sent
					bestSolution = solutionCourante;
			}
			else	// co�tCourant >= co�tPr�c�dent. La solution courante n'est pas meilleure que la solution pr�c�dente
			{
				double v = tirageAleatoire(0, 1);
				double deltaCout = solutionCourante.cout - solutionPrecedente.cout; // on a deltaCout >= 0
				double metropolis = exp(-K*deltaCout / t);

				if (v < metropolis) ++nombreSucces;		// la solution courante est accept�e bien que moins bonne que la pr�c�dente

				else
					solutionCourante = solutionPrecedente;	// la solution courante est refus�e

			}	// co�tCourant >= co�tPr�c�dent.

		}	 // for, boucle tentatives d'am�liorations

		if (nombreSucces == 0) return bestSolution;		// l'algorithme est stationnaire : il a atteint un minimum, on arr�te tout et on retourne la meilleure solution trouv�e

	}	// for, boucle temp�rature

	return bestSolution;
}
