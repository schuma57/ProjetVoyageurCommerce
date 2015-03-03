#pragma once

#include <iostream>
#include <string>
#include "Graphe.h"
using namespace std;

class Cycle
{
	Graphe<class S, class T> * grapheActuel;

public:
	Cycle(Graphe<class S, class T> *graphe);

	string *eulerCycle();
};
