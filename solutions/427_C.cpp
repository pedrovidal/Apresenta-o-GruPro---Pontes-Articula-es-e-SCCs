#include <bits/stdc++.h>
using namespace std;


long long dfsIteration = 1;
long long MAXN = 112345, min_cost = 0, ways = 1, mod=1000000007;
vector<vector<long long>> adj(MAXN, vector<long long>()), scc(MAXN, vector<long long>());
vector<bool> visited(MAXN, false);
vector<long long> low(MAXN, -1), discovery(MAXN, -1), st, cost(MAXN, 0);


void tarjanSCC(long long u){
	discovery[u] = low[u] = dfsIteration++;
	st.push_back(u);
	visited[u] = true;
	for (long long v: adj[u]){
		if(discovery[v] == -1){  // não descoberto/visitado
			tarjanSCC(v);
		}
		if (visited[v]){
			low[u] = min(low[u], low[v]);
		}
	}

	if (low[u] == discovery[u]){
		long long min_scc_value = 1123456789, counter = 0;
		while(true){
			long long v = st.back();
			st.pop_back();
			scc[u].push_back(v);
			visited[v] = false;
			if (cost[v] < min_scc_value){
				min_scc_value = cost[v];
				counter = 1;
			}
			else if (cost[v] == min_scc_value){
				counter+=1;
			}
			if (v == u) {
				break;
			}
		}
		min_cost += min_scc_value;
		ways *= counter;
		ways %= mod;
	}
}

int main(){
	ios::sync_with_stdio(false);
	long long num_v, num_e;
	cin >> num_v;
	
	for (long long i = 1; i <= num_v; i++){
		long long c;
		cin >> c;
		cost[i] = c;
	}

	cin >> num_e;

	long long u, v;
	for (long long i = 0; i < num_e; i++){
		cin >> u >> v;
		adj[u].push_back(v);
	}

	for (long long i = 0; i <= num_v; i++){
		if (discovery[i] == -1){
			tarjanSCC(i);
		}
	}

	cout << min_cost << " " << ways << endl;
}

