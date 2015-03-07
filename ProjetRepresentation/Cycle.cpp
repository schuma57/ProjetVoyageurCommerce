#include <set>
#include <stack>
//#include "Cycle.h"
using namespace std;


/*list<int> Cycle::getEulerCycle() const
{	
	//=== test si le nombre de sommets du graphe est impair ====
	int nodes = grapheActuel->nombreSommets();

	if(nodes % 2 == 0){
		cout << "impossible avec ce nombre de sommets" << endl;
		abort();
	}
	//==========================================================

	list<int> current_cycle; //remplacer par list<Sommet<T>>

	vector<list<int>> g_list = creatListeAdj(); //graphe

	int num_vertex = g_list.size(); //nb sommets
	
	current_cycle.push_back(0);
	int V = 0, next_v = -1, curr_v = 0;
	int sum = 0;
	for (int i = 0; i < num_vertex; i++){
		sum += g_list[i].size();
	}
	while (sum > 0){
		list<int> temp_cycle;
		while (V != next_v) {
			next_v = curr_v;
			curr_v = g_list[next_v].back();
			g_list[next_v].pop_back();
			g_list[curr_v].remove(next_v);
			temp_cycle.push_back(curr_v);
			next_v = curr_v;
		}
		sum = 0;
		for (int i = 0; i < num_vertex; i++){
			sum += g_list[i].size();
		}
		current_cycle.splice((++find(current_cycle.begin(), current_cycle.end(), V)), temp_cycle);
		if (sum == 0) break;
		for (int i = 0; i < num_vertex; i++){
			for (int j : g_list[i])
				if (find(current_cycle.begin(), current_cycle.end(), j) != current_cycle.end()) {
				V = j;
				break;
				}
		}
	}
	return current_cycle;
		
}*/
