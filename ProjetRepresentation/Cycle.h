#pragma once

//!
//! \file Cycle.h
//!

#include <iostream>
#include <string>
#include <vector>
#include "Graphe.h"
using namespace std;

//!
//! \class Cycle
//!
template<class S, class T>
class Cycle
{

public:
	Cycle(){}
	~Cycle(){}

	static Graphe<S, T> getHamiltonCycle(const Graphe<S, T> & graphe);
};


template<class S, class T>
/*static*/ Graphe<S,T> Cycle<S,T>::getHamiltonCycle(const Graphe<S, T> & graphe)
{
	Graphe<S,T> gr( graphe);
	vector<Arete<S, T>> cycle;
	const int NB = gr.nombreSommets();
	int rando = rand() % NB;

	Arete<S, T>* premier = PElement<Arete<S,T>>::depiler(gr.lAretes);		//premiere arete
	cycle.push_back(*premier);
	PElement<Sommet<T>>::retire(premier->debut, gr.lSommets);	//on supprime le sommet

	PElement<pair<Sommet<T>*, Arete<S, T>*>>* truc = gr.adjacences(premier->debut);
	while (truc != NULL)
	{
		PElement<Arete<S, T>>::retire(truc->v->second, gr.lAretes); //on supprime toutes les aretes partant du sommet supprime
		truc = truc->s;
	}

	Sommet<T>* sommetCourant = NULL;
	Arete<S, T>* nextArete = NULL;
	Arete<S, T>* dernier = NULL;
	Arete<S, T>* derArete = NULL;

	for (int i = 2; i < NB; i++)
	{
		derArete = &cycle.at(cycle.size() - 1);		//on recupere la derniere arete stockee

		sommetCourant = derArete->fin;		//sommet courant

		nextArete = gr.adjacences(sommetCourant)->v->second;		//on recupere l'arete adjacente

		if (sommetCourant == nextArete->fin)
			nextArete = new Arete<S, T>(nextArete->clef, nextArete->fin, nextArete->debut, nextArete->v); //on retourne l'arete

		cycle.push_back(*nextArete);	//on ajoute l'arete
		PElement<Sommet<T>>::retire(nextArete->debut, gr.lSommets);	//on supprime le sommet

		PElement<pair<Sommet<T>*, Arete<S, T>*>>* truc = gr.adjacences(nextArete->debut);
		while (truc != NULL)
		{
			PElement<Arete<S, T>>::retire(truc->v->second, gr.lAretes); //on supprimes toutes les aretes partant du sommet supprime
			truc = truc->s;
		}
	}

	if ((dernier = graphe.getAreteParSommets(cycle.at(cycle.size() - 1).fin, cycle.at(0).debut)) != NULL)
		cycle.push_back(*dernier);
		
	sommetCourant = 0; nextArete = 0; dernier = 0;

	Graphe<S,T> grapheHamilton;
	grapheHamilton.lSommets = new PElement<Sommet<T>>(*graphe.lSommets);
	PElement<Arete<S, T>>* aretes = NULL;
	for (int i = cycle.size()-1; i >= 0; i--)
	{
		grapheHamilton.creeArete( cycle.at(i).debut, cycle.at(i).fin, cycle.at(i).v );
		if (i == cycle.size() - 1)
			grapheHamilton.lAretes->s = NULL;
	}

	return grapheHamilton;
}
