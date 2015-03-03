#pragma once

#include "Graphe.h"
#include "Sommet.h"
#include "InfoSommetCarte.h"
#include "Arete.h"
#include "InfoAreteCarte.h"


class OutilsCarteRecuitSimule
{
public:
	static double distance(const Sommet<InfoSommetCarte> * s1, const Sommet<InfoSommetCarte> * s2);
	static Arete<InfoAreteCarte, InfoSommetCarte> *  creeArete(Sommet<InfoSommetCarte> * sA,
		Sommet<InfoSommetCarte> * sB,
		Graphe<InfoAreteCarte,
		InfoSommetCarte> & graphe);
};
