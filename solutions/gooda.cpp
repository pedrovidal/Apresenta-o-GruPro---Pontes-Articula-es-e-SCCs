#include <bits/stdc++.h>
using namespace std;


long long dfsIteration = 1;
long long const MAXN = 11234567;
vector<vector<long long>> adj(MAXN, vector<long long>());
vector<bool> visited(MAXN, false);
vector<long long> low(MAXN, -1), discovery(MAXN, -1), visited_stack, scc(MAXN, -1), cost, scc_cost(MAXN, 0), ts;
vector<long long> dist(MAXN, 0);


void tarjanSCC(long long u){
	discovery[u] = low[u] = dfsIteration++;
	visited_stack.push_back(u);
	visited[u] = true;
	for (long long v: adj[u]){
		if(discovery[v] == -1){  // não descoberto/visitado
			tarjanSCC(v);
		}
		if (visited[v]){  // visitado na subtree da dfs
			low[u] = min(low[u], low[v]);
		}
	}

	if (low[u] == discovery[u]){
		while(true){
			long long v = visited_stack.back();
			visited_stack.pop_back();
			scc[v] = u;
			scc_cost[u] += cost[v];
			visited[v] = false;
			if (v == u) {
				break;
			}
		}
	}
}

void topolsort(long long u){
	visited[u] = true;
	for (long long v : adj[u]){
		v = scc[v];
		if (!visited[v]){
			topolsort(v);
		}
	}
	ts.push_back(u);
}

int main(){
	ios::sync_with_stdio(false);
	long long num_v, num_e, source, target;
	cin >> num_v >> num_e >> source >> target;
	
	// Ler custos de vertices
	cost.push_back(0);
	for (long long i = 0; i < num_v; i++){
		long long cost_i;
		cin >> cost_i;
		cost.push_back(cost_i);
	}

	// Ler edges
	long long u, v;
	for (long long i = 0; i < num_e; i++){
		cin >> u >> v;
		adj[u].push_back(v);
	}
	adj[0].push_back(source);


	for (long long i = 0; i <= num_v; i++){
		if (discovery[i] == -1){
			tarjanSCC(i);
		}
	}

	for (int u = 0; u <= num_v; u++){
		if (u == scc[u]){
			continue;
		}
		for (int v : adj[u]){
			adj[scc[u]].push_back(v);
		}
	}

	visited.assign(MAXN, false);
	for (long long i = 0; i <= num_v; i++){
		if (!visited[scc[i]]){
			topolsort(scc[i]);
		}
	}

	// for (int i = 0; i <= num_v; i++){
	// 	cout << "Vert " << i << " scc=" << scc[i] << " scc_cost=" << scc_cost[i] << endl;
	// }

	visited.assign(MAXN, false);

	bool visto = false; 

	for (long long i=ts.size() - 1; i>=0; i--){
		long long u = ts[i];
		// cout << "U=" << u << " scc[source] " << scc[source] << endl;
		if (u == 0){
			visto = true;
		}
		if (u != 0 && !visto){
			continue;
		}
		for (long long v: adj[u]){
			v = scc[v];
			if (u == v){
				continue;
			} 
			// cout << "Edge u,v: " << u << " " << v << endl;
			dist[v] = max(dist[v], dist[u] + scc_cost[v]);
			// cout << "dist[v]=" << dist[v] << endl;
		}
	}

	cout << dist[scc[target]] << endl;
}

