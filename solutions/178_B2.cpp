#include <bits/stdc++.h>
using namespace std;


bool found=false;
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

int search_bridges(int u, int t){
	discovery[u] = 1;
	if (u == t){
		found = true;
		return 0;
	}
	int res;
	for (int v : adj[u]){
		if (!found && discovery[v] == -1){
			res = search_bridges(v, t);
			if (found){
				if (binary_search(bridges.begin(), bridges.end(), make_pair(min(u, v), max(u, v))))
				{
					res++;
				}
				return res;
			}
		}
	}
	return 0;
}

int main(){
	ios::sync_with_stdio(false);
	int test_cases;
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

	for (int i = 0; i <= num_v; i++){
		if (discovery[i] == -1){
			tarjan(i, i);
		}
	}

	sort(bridges.begin(), bridges.end());

	int k;
	cin >> k;

	for (int i = 0; i < k; i++){
		cin >> u >> v;
		if (!bridges.empty()){
			found = false;
			discovery.assign(num_v + 1, -1);
			cout << search_bridges(u, v) << endl;
		}
		else{
			cout << 0 << endl;
		}
	}
}
