#include <bits/stdc++.h>
using namespace std;

int MAXN = 123;
int dfs_iteration = 1, counter_sccs = 0;
vector<int> visited_stack;

void tarjanSCC(int u, vector<vector<int>> & adj, vector<int> & discovery, vector<int> & low, vector<bool> & visited){
	discovery[u] = low[u] = dfs_iteration++;
	visited_stack.push_back(u);
	visited[u] = true;
	for (int v: adj[u]){
		if (discovery[v] == -1){
			tarjanSCC(v, adj, discovery, low, visited);
		}
		if (visited[v]){
			low[u] = min(low[u], low[v]);
		}
	}

	if (low[u] == discovery[u]){
		counter_sccs++;
		cout << "SCC " << counter_sccs << ":" << endl;
		while(true){
			int v = visited_stack.back();
			visited_stack.pop_back();
			visited[v] = false;
			cout << v << endl;
			if (v == u){
				break;
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	int t, n;
	cin >> t;
	while(t--){
		cin >> n;
		vector<vector<int>> adj(MAXN, vector<int>());
		vector<int> discovery(MAXN, -1), low(MAXN, -1);
		vector<bool> visited(MAXN, false);
		dfs_iteration = 1;
		counter_sccs = 0;

		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				char c;
				cin >> c;
				if (c == 'Y'){
					adj[i].push_back(j);
				}
			}
		}

		for (int i = 0; i < n; i++){
			if (discovery[i] == -1){
				tarjanSCC(i, adj, discovery, low, visited);
			}
		}

		cout << counter_sccs << endl;
	}
}