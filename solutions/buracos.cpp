#include <bits/stdc++.h>
using namespace std;

int MAXP = 3123;
int p, b, teste = 1, dfs_iteration = 1;
bool possible = true;
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
		int scc_sz = 0;
		while(true){
			int v = visited_stack.back();
			visited_stack.pop_back();
			visited[v] = false;
			scc_sz++;
			if (v == u){
				break;
			}
		}
		if (scc_sz != p){
			possible = false;
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	while(cin >> p >> b, p!=0 || b!=0){
		possible = true;
		vector<vector<int>> adj(MAXP, vector<int>());
		vector<int> discovery(MAXP, -1), low(MAXP, -1);
		vector<bool> visited(MAXP, false);
		dfs_iteration = 1;
		for (int i = 0; i < b; i++){
			int x, y;
			cin >> x >> y;
			adj[x].push_back(y);
		}

		tarjanSCC(1, adj, discovery, low, visited);

		cout << "Teste " << teste++ << endl;
		if (possible){
			cout << "S" << endl << endl; 
		}
		else{
			cout << "N" << endl << endl;
		}
	}
}