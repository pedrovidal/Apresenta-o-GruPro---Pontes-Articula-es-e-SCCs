#include <bits/stdc++.h>
using namespace std;


bool found=false;
long long dfsIteration = 0, MAXN = 112345, MAXM = 3 * MAXN;
vector<pair<long long, long long>> bridges;
vector<vector<long long>> adj(MAXN, vector<long long>());
vector<long long> low(MAXN, -1), discovery(MAXN, -1), parent(MAXN, 0);


void tarjan(long long u, long long root){
	discovery[u] = low[u] = dfsIteration++;
	for (long long v: adj[u]){
		if(discovery[v] == -1){  // não descoberto/visitado
			parent[v] = u;
			tarjan(v, root);

			if (low[v] > discovery[u]){
				bridges.emplace_back(min(u, v), max(u, v));
			}

			low[u] = min(low[u], low[v]);
		}
		else if (v != parent[u]){
			low[u] = min(low[u], discovery[v]);
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	long long num_v, num_e;
	while(cin >> num_v >> num_e){
		long long u, v;
		for (long long i = 0; i < num_e; i++){
			cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}

		for (long long i = 0; i <= num_v; i++){
			if (discovery[i] == -1){
				tarjan(i, i);
			}
		}

		cout << bridges.size() << endl;
		for (long long i = 0; i <= num_v; i++){
			adj[i].clear();
			discovery[i] = low[i] = -1;
			parent[i] = 0;
		}
		bridges.clear();
	}
}
