#include <bits/stdc++.h>
using namespace std;


int dfsIteration = 0, MAXN=12345;
vector<pair<int, int>> bridges;
vector<bool> is_articulation;
vector<vector<int>> adj(MAXN, vector<int>());
vector<int> low(MAXN, -1), discovery(MAXN, -1), parent(MAXN, 0);


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
	cin >> test_cases;
	for (int tc = 1; tc <= test_cases; tc++){
		dfsIteration = 0;
		int num_v, num_e;
		cin >> num_v >> num_e;
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

		cout << "Caso #" << tc << endl;

		if (bridges.empty()){
			cout << "Sin bloqueos" << endl;
		}
		else{
			cout << bridges.size() << endl;
			sort(bridges.begin(), bridges.end());

			for (pair<int, int> p : bridges){
				cout << p.first << " " << p.second << endl;
			}
		}
	}
}

