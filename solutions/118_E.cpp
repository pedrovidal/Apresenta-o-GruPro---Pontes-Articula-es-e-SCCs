#include <bits/stdc++.h>
using namespace std;


bool found=false;
long long dfsIteration = 0, MAXN = 112345, MAXM = 3 * MAXN;
map<pair<long long, long long>, long long> position;
vector<pair<long long, long long>> bridges, response;
vector<vector<long long>> adj(MAXN, vector<long long>());
vector<bool> is_articulation(MAXN, false), is_directed(MAXM, false);
vector<long long> low(MAXN, -1), discovery(MAXN, -1), parent(MAXN, 0);


void tarjan(long long u, long long root){
	discovery[u] = low[u] = dfsIteration++;
	long long children = 0;
	for (long long v: adj[u]){
		pair<long long, long long> p = make_pair(u, v);
		// long long x = position[p];

		// cout << "u=" << p.first << " v=" << p.second << " pos=" << x << " directed=" << is_directed[x] << " resp=(" << response[x].first << ", " << response[x].second << ")" << endl;
		if (!is_directed[position[p]]){
			// cout << "Save\n";
			is_directed[position[p]] = true;
			response[position[p]] = p;
		}
		// cout << "u=" << p.first << " v=" << p.second << " pos=" << x << " directed=" << is_directed[x] << " resp=(" << response[x].first << ", " << response[x].second << ")" << endl;
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
	long long test_cases;
	long long num_v, num_e;
	cin >> num_v >> num_e;

	long long u, v;
	for (long long i = 0; i < num_e; i++){
		cin >> u >> v;
		position[make_pair(u, v)] = i;
		position[make_pair(v, u)] = i;
		response.emplace_back(u, v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	for (long long i = 0; i <= num_v; i++){
		if (discovery[i] == -1){
			tarjan(i, i);
		}
	}

	if (!bridges.empty()){
		cout << 0 << endl;
		return 0;
	}

	for (int i = 0; i < num_e; i++){
		cout << response[i].first << " " << response[i].second << endl;
	}
}
