#pragma once

//!
//! \file Graphe.h
//!

#include <string>
#include <sstream>
#include <list>
#include "Erreur.h"
#include "PElement.h"
#include "Arete.h"
#include "Sommet.h"
using namespace std;

class Visitor;

//!
//! \class Graphe
//!
template <class S, class T>
class Graphe
{
protected:
	int prochaineClef;
public:
	/**
	* liste des sommets
	**/
	PElement< Sommet<T> > * lSommets;
	/**
	* liste des aretes
	**/
	PElement< Arete<S, T> > * lAretes;

	/**
	* crée un graphe vide
	**/
	Graphe();

	/**
	* constructeur de copie obligatoire car la classe comporte une partie dynamique
	**/
	Graphe(const Graphe<S, T> & graphe);

	/**
	* destructeur
	**/
	~Graphe();

	int nombreSommets() const;
	int nombreAretes() const;

	/**
	* crée un sommet isolé
	**/
	Sommet<T> * creeSommet(const T & info);

	/**
	* crée une arête joignant les 2 sommets debut et fin 
	* met à jour les champs degré de debut et de fin
	**/
	Arete<S, T> *
		creeArete(Sommet<T> * debut, Sommet<T> * fin, const S & info);

	/**
	* recherche la liste des paires (voisin, arête) adjacentes de sommet dans le graphe
	**/
	PElement< pair< Sommet<T> *, Arete<S, T>* > >  *
		adjacences(const Sommet<T> * sommet) const;

	/**
	* cherche l'arête s1 - s2 ou l'arête s2 - s1 si elle existe
	*
	* DONNEES : s1 et s2 deux sommets quelconques du graphe
	* RESULTATS : l'arête s'appuyant sur s1 et s2 si elle existe, NULL sinon
	*
	**/
	Arete<S, T> * getAreteParSommets(const Sommet<T> * s1, const Sommet<T> * s2) const;

	/**
	* detecte si le graphe est eulerien
	*/
	bool estEulerien();
	

	/**
	* opérateur = obligatoire car la classe comporte une partie dynamique
	**/
	const Graphe<S, T> & operator = (const Graphe<S, T> & graphe);

	//!
	//! operateur string()
	//!
	operator string() const;

	//!
	//! design pattern Visitor
	//! \param v : pointeur d'objet Visitor
	//!
	void accept(Visitor * v) const;

	//---------------------- Graphe ----------------------------------
};

/**
* crée un graphe vide
*
**/
template <class S, class T>
Graphe<S, T>::Graphe() :prochaineClef(0), lAretes(NULL), lSommets(NULL){}

template <class S, class T>
Graphe<S, T>::Graphe(const Graphe<S, T> & graphe)
{
	//throw Erreur("pas encore écrit : reste à faire");
	this->prochaineClef = graphe.prochaineClef;
	memcpy(&lAretes, &graphe.lAretes, sizeof(graphe.lAretes));
	memcpy(&lSommets, &graphe.lSommets, sizeof(graphe.lSommets));
}

template <class S, class T>
const Graphe<S, T> & Graphe<S, T>::operator = (const Graphe<S, T> & graphe)
{
	throw Erreur("pas encore écrit : reste à faire");
}

template <class S, class T>
Graphe<S, T>::~Graphe()
{
	//PElement< Arete<S, T>>::efface2(this->lAretes);
	//PElement<Sommet<T> >::efface2(this->lSommets);
}

/**
* crée un sommet isolé
*
**/
template <class S, class T>
Sommet<T> * Graphe<S, T>::creeSommet(const T & info)
{
	Sommet<T> * sommetCree = new Sommet<T>(prochaineClef++, info);
	lSommets = new PElement< Sommet<T> >(sommetCree, lSommets);

	return sommetCree;
}

/**
* crée une arête joignant les 2 sommets debut et fin
*
* met à jour les champs degre de debut et de fin
**/
template <class S, class T>
Arete<S, T> * Graphe<S, T>::creeArete(Sommet<T> * debut, Sommet<T> * fin, const S & info)
{
	Arete<S, T> * nouvelleArete;

	// ici tester que les 2 sommets sont bien existants dans le graphe
	//if (!PElement< Sommet<T> >::appartient(debut, lSommets)) throw Erreur("début d'arête non défini");
	//if (!PElement< Sommet<T> >::appartient(fin, lSommets)) throw Erreur("fin d'arête non définie");

	nouvelleArete = new Arete<S, T>(prochaineClef++, debut, fin, info);

	lAretes = new PElement< Arete<S, T> >(nouvelleArete, lAretes);
	debut->degre++; fin->degre++;

	return nouvelleArete;
}

template <class S, class T>
int Graphe<S, T>::nombreSommets() const
{
	return PElement< Sommet<T> >::taille(lSommets);
}

template <class S, class T>
int Graphe<S, T>::nombreAretes() const
{
	return PElement< Arete<S, T> >::taille(lAretes);
}


/**
* cherche l'arête s1 - s2 ou l'arête s2 - s1 si elle existe
*
* DONNEES : s1 et s2 deux sommets quelconques du graphe
* RESULTATS : l'arête s'appuyant sur s1 et s2 si elle existe, NULL sinon
*
**/
template <class S, class T>
Arete<S, T> * Graphe<S, T>::getAreteParSommets(const Sommet<T> * s1, const Sommet<T> * s2) const
{
	PElement<Arete<S, T> > * l;

	for (l = this->lAretes; l; l = l->s)
		if (l->v->estEgal(s1, s2))
			return l->v;

	return NULL;
}

/**
* recherche la liste des paires (voisin, arête) adjacentes de sommet dans le graphe
*/
template <class S, class T>
PElement< pair< Sommet<T> *, Arete<S, T>* > >  *  Graphe<S, T>::adjacences(const Sommet<T> * sommet) const
{
	const PElement< Arete<S, T> > * l;

	PElement< pair< Sommet<T> *, Arete<S, T>* > > * r;				// pair< Sommet<T> *, Arete<S,T>* >

	for (l = lAretes, r = NULL; l; l = l->s)

		if (sommet == l->v->debut)
			r = new PElement< pair< Sommet<T> *, Arete<S, T>* > >
			(new pair< Sommet<T> *, Arete<S, T>* >(l->v->fin, l->v), r);
		else
			if (sommet == l->v->fin)
				r = new PElement< pair< Sommet<T> *, Arete<S, T>* > >
				(new pair< Sommet<T> *, Arete<S, T>* >
				(l->v->debut, l->v), r);
	return r;
}


template <class S, class T>
ostream & operator << (ostream & os, const Graphe<S, T> & gr)
{
	return os << (string)gr;
}


template <class S, class T>
Graphe<S, T>::operator string() const
{
	ostringstream oss;
	oss << "Graphe( \n";
	oss << "prochaine clef = " << this->prochaineClef << endl;
	oss << "nombre de sommets = " << this->nombreSommets() << "\n";

	oss << PElement<Sommet<T> >::toString(lSommets, "", "\n", "");

	oss << "nombre d'aretes = " << this->nombreAretes() << "\n";

	oss << PElement<Arete<S, T> >::toString(lAretes, "", "\n", "");
	oss << ")";
	return oss.str();
}


template<class S, class T>
void Graphe<S, T>::accept(Visitor * v) const
{
	v->visiteGraphe();
}
