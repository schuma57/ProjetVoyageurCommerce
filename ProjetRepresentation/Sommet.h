#pragma once

//!
//! \file Sommet.h
//!

#include <string>
#include "GElement.h"
using namespace std;

/**
Sommet d'un graphe en général
v est l'information associée au sommet : elle dépend de l'application du graphe
*/

//!
//! \class Sommet
//!
template <class T>
class Sommet : public GElement
{
public:
	int degre;
	T v;
	Sommet(const int clef, const T & v) :GElement(clef), degre(0), v(v){}
	Sommet(const Sommet & som) :GElement(som.clef), degre(0), v(som.v){}

	operator string () const;
};

template <class T>
Sommet<T>::operator string () const
{
	ostringstream oss;

	oss << "Sommet(" << endl;
	oss << GElement::operator string() << endl;
	oss << "degre = " << degre << endl;
	oss << "v = " << v << endl;
	oss << ")";
	return oss.str();
}

template <class T>
ostream & operator << (ostream & os, const Sommet<T> & sommet)
{
	return os << (string)sommet;
}