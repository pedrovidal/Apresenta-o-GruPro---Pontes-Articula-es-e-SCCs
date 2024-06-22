#include <bits/stdc++.h>
using namespace std;

int MAXN = 123;

void dfs(int u, vector<vector<int>> & adj, vector<bool> & visited, vector<int> & visited_stack){
	visited[u] = true;
	for (int v: adj[u]){
		if (!visited[v]){
			dfs(v, adj, visited, visited_stack);
		}
	}
	visited_stack.push_back(u);
}

int main(){
	ios::sync_with_stdio(false);
	int t, n;
	cin >> t;
	while(t--){
		cin >> n;
		vector<vector<int>> adj(MAXN, vector<int>()), adjT(MAXN, vector<int>());
		vector<int> visited_stack, visited_stackT;
		vector<bool> visited(MAXN, false);
		int counter_sccs = 0;

		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				char c;
				cin >> c;
				if (c == 'Y'){
					adj[i].push_back(j);
					adjT[j].push_back(i);
				}
			}
		}

		for (int i = 0; i < n; i++){
			if (!visited[i]){
				dfs(i, adj, visited, visited_stack);
			}
		}
		
		for (int i = 0; i < n; i++){
			visited[i] = false;
		}
		
		for (int i = n - 1; i >= 0; i--){
			int u = visited_stack[i];
			if (!visited[u]){
				counter_sccs++;
				dfs(u, adjT, visited, visited_stackT);
			}
		}

		cout << counter_sccs << endl;
	}
}