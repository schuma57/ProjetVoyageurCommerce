#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Graphe.h"
using namespace std;

template<class S, class T>
class Cycle
{

public:
	Cycle(){}
	~Cycle(){}

	static vector<Arete<S, T>> getHamiltonCycle(const Graphe<S, T> & graphe);
};


template<class S, class T>
/*static*/ vector<Arete<S, T>> Cycle<S,T>::getHamiltonCycle(const Graphe<S, T> & graphe)
{
	Graphe<S, T> gr( graphe);
	vector<Arete<S, T>> cycle;

	Arete<S, T> premier = *(gr.lAretes->v);		//premiere arete
	cycle.push_back(premier);
	PElement<Sommet<T>>::retire(premier.debut, gr.lSommets);	//on supprime le sommet
	PElement<Arete<S,T>>::retire(&premier, gr.lAretes);		//on supprime l'arete

	PElement<pair<Sommet<T>*, Arete<S, T>*>>* truc = gr.adjacences(premier.debut);
	while (truc != NULL)
	{
		PElement<Arete<S, T>>::retire(truc->v->second, gr.lAretes);
		truc = truc->s;
	}

	Sommet<T>* temp = NULL;
	Arete<S, T>* nextArete = NULL;

	while (gr.nombreSommets() > 1)
	{
		Arete<S, T>* derArete = &cycle.at(cycle.size() - 1);	//on recupere la derniere arete stockee

		temp = derArete->fin;		//sommet courant

		nextArete = gr.adjacences(temp)->v->second;		//on recupere l'arete adjacente

		if (temp == nextArete->fin)
			nextArete = new Arete<S, T>(nextArete->clef, nextArete->fin, nextArete->debut, nextArete->v); //on retourne l'arete

		cycle.push_back(*nextArete);	//on ajoute l'arete
		PElement<Sommet<T>>::retire(nextArete->debut, gr.lSommets);	//on supprime le sommet

		PElement<pair<Sommet<T>*, Arete<S, T>*>>* truc = gr.adjacences(nextArete->debut);
		while (truc != NULL)
		{
			PElement<Arete<S, T>>::retire(truc->v->second, gr.lAretes);
			truc = truc->s;
		}
	}
	PElement<Arete<S, T>>::efface2(gr.lAretes);
	PElement<Sommet<T> >::efface2(gr.lSommets);

	return cycle;
}
