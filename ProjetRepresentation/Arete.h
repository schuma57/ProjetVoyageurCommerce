#pragma once

//!
//! \file Arete.h
//!

#include <string>
#include "GElement.h"
#include "Sommet.h"
using namespace std;

/**
repr�sente une ar�te d'un graphe en g�n�ral.
Une ar�te est d�finie par un sommet-d�but et par un sommet-fin et par une information v.

On ne connait pas la nature de v � ce niveau (v pourrait contenir une couleur, une longueur, un nom, etc.)

T est la nature de l'information port�e par un sommet et
S est la nature de l'information port�e par une ar�te
*/

//!
//! \class Arete
//! \brief extends GElement
//!
template <class S, class T>
class Arete : public GElement
{
public:
	Sommet <T> *debut, *fin;
	S v;
	Arete(int clef, Sommet<T> * debut, Sommet<T> * fin, const S & v) :
		GElement(clef), debut(debut), fin(fin), v(v){}

	operator string () const;

	/**
	* v�rifie si *this s'appuie sur s1 et s2
	*
	* DONNEES : *this, s1, s2
	*
	* RESULTATS : true si *this s'appuie sur s1 et s2 c'est-�-dire si (d�but == s1 et fin == s2) ou (d�but == s2 et fin == s1), false sinon
	*
	* */
	bool estEgal(const Sommet<T> * s1, const Sommet<T> * s2) const;

};

template <class S, class T>
Arete<S, T>::operator string () const
{
	ostringstream oss;

	oss << "Arete  (" << endl;
	oss << GElement::operator string() << endl;
	oss << "clef debut = " << debut->clef << endl;
	oss << "clef fin = " << fin->clef << endl;
	oss << "v = " << v << endl;
	oss << ")";
	return oss.str();
}

template <class S, class T>
ostream & operator << (ostream & os, const Arete<S, T> & arete)
{
	return os << (string)arete;
}

/**
* v�rifie si *this s'appuie sur s1 et s2
*
* DONNEES : *this, s1, s2
*
* RESULTATS : true si *this s'appuie sur s1 et s2 c'est - � - dire si(d�but == s1 et fin == s2) ou(d�but == s2 et fin == s1), false sinon
*
**/
template <class S, class T>
bool Arete<S, T>::estEgal(const Sommet<T> * s1, const Sommet<T> * s2) const
{
	return (s1 == debut && s2 == fin) || (s1 == fin && s2 == debut);
}
