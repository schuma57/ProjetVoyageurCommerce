#include <set>
#include <vector>
#include <stack>
#include "Cycle.h"
using namespace std;


Cycle::Cycle(Graphe<class S, class T> *graphe) : grapheActuel(graphe)
{}

/*
string *Cycle::eulerCycle()
{	
	int nodes = PElement<class T>::taille(grapheActuel->lSommets) ;
	int **adj = grapheActuel->adjacencyMatrix();
	vector<int> deg(nodes);
	for (int i = 0; i < nodes; i++)
	{
		for (int ii = 0; ii < nodes; ii++)
		{
			deg[i] += adj[i][ii];
		}
	}
	int curr = 0;
	while (!deg[curr])
	{
		curr++;
	}

	int v1 = -1;
	int v2 = -1;
	bool bad = false;
	for (int i = 0; i < nodes; i++)
	{
		if (deg[i] & 1)
		{
			if (v1 == -1)
				v1 = i;
			else if (v2 == -1)
				v2 = i;
			else
				bad = true;
		}
	}
	if (v1 != -1)
	{
		adj[v1][v2]++;
		adj[v2][v1]++;
	}
	if (bad)
	{
		return NULL;
	}

	stack<int> st;
	st.push(curr);
	vector<int> res;
	while (!st.empty())
	{
		int v = st.top();
		int i;
		for (i = 0; i < nodes; i++)
			if (adj[v][i])
				break;
		if (i == nodes)
		{
			res.push_back(v);
			st.pop();
		}
		else
		{
			--adj[v][i];
			--adj[i][v];
			st.push(i);
		}
	}
	if (v1 != -1)
	{
		for (size_t i = 0; i + 1 < res.size(); ++i)
		{
			if ((res[i] == v1 && res[i + 1] == v2) || (res[i] == v2 && res[i + 1] == v1))
			{
				vector<int> res2;
				for (size_t j = i + 1; j < res.size(); ++j)
					res2.push_back(res[j]);
				for (size_t j = 1; j <= i; ++j)
					res2.push_back(res[j]);
				res = res2;
				break;
			}
		}
	}
	for (int i = 0; i < nodes; ++i)
	{
		for (int j = 0; j < nodes; ++j)
		{
			if (adj[i][j])
				bad = true;
		}
	}

	if (bad) {
		return NULL;
	}
	else
	{
		NodesID *IDs = _currGraph->nodesKeys();
		string *str = new string;
		if (v1 == -1) {
			*str = "Cycle: ";
		}
		else {
			*str = "Path: ";
		}
		for (int i = 0; i < res.size(); i++)
		{
			*str += IDs->nodeForID(res[i]);
			*str += " ";
		}
		return str;
	}
}
*/