#include <bits/stdc++.h>
using namespace std;


int dfsIteration = 0;
vector<pair<int, int>> bridges;
vector<vector<int>> adj;
vector<bool> is_articulation;
vector<int> low, discovery, parent;


void tarjan(int u, int root){
	discovery[u] = low[u] = dfsIteration++;
	int children = 0;
	for (int v: adj[u]){
		if(discovery[v] == -1){  // não descoberto/visitado
			parent[v] = u;
			children++;
			tarjan(v, root);

			if (low[v] >= discovery[u] && u != root){
				is_articulation[u] = true;
			}
			if (low[v] > discovery[u]){
				bridges.emplace_back(min(u, v), max(u, v));
			}

			low[u] = min(low[u], low[v]);
		}
		else if (v != parent[u]){
			low[u] = min(low[u], discovery[v]);
		}
	}
	if (u == root && children > 1){
		is_articulation[u] = true;
	}
}

int main(){
	ios::sync_with_stdio(false);
	int test_cases;
	int num_v, num_e;
	while(cin >> num_v >> num_e, num_v != 0 && num_e !=0){
		dfsIteration = 0;
		adj.assign(num_v + 1, vector<int>());
		is_articulation.assign(num_v + 1, false);
		low.assign(num_v + 1, -1);
		discovery.assign(num_v + 1, -1);
		parent.assign(num_v + 1, -1);

		int u, v;
		for (int i = 0; i < num_e; i++){
			cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}

		bridges.clear();

		for (int i = 0; i <= num_v; i++){
			if (discovery[i] == -1){
				tarjan(i, i);
			}
		}

		cout << count(is_articulation.begin(), is_articulation.end(), true) << endl;
	}
}

