#include <bits/stdc++.h>
using namespace std;


int dfsIteration = 1;
vector<int> visited_stack;

string neg(string s){
	if(s[0] == '!'){
		return s.substr(1, s.size() - 1);
	}
	return "!" + s;
}

bool tarjanSCC(int u, vector<vector<int>> & adj, vector<bool> & visited, vector<int> & low, vector<int> & discovery, vector<string> & its){
	discovery[u] = low[u] = dfsIteration++;
	visited_stack.push_back(u);
	visited[u] = true;
	bool f = true;
	for (int v: adj[u]){
		if(discovery[v] == -1){  // não descoberto/visitado
			f &= tarjanSCC(v, adj, visited, low, discovery, its);
		}
		if (visited[v]){  // visitado na subtree da dfs
			low[u] = min(low[u], low[v]);
		}
	}
	if (low[u] == discovery[u]){
		while(true){
			int v = visited_stack.back();
			visited_stack.pop_back();
			if (its[u] == neg(its[v])){
				f = false;
			}
			visited[v] = false;
			if (v == u) {
				break;
			}
		}
	}
	return f;
}

int main(){
	ios::sync_with_stdio(false);
	int n, t=1;
	while(cin >> n){
		int max_n = n + 1;
		max_n *= 4;
		vector<vector<int>> adj(max_n, vector<int>());
		vector<bool> visited(max_n, false);
		vector<int> low(max_n, -1), discovery(max_n, -1);
		map<string, int> sti;
		vector<string> its;
		int counter = 1;
		dfsIteration = 1;
		its.push_back("");
	
		for (int i = 0; i < n; i++){
			string a, b;
			cin >> a >> b;
			vector<string> possibilites = {a, b, neg(a), neg(b)};
			for (string possibility : possibilites){
				if (sti[possibility] == 0){
					sti[possibility] = counter++;
					its.push_back(possibility);
				}
			}
			adj[sti[neg(a)]].push_back(sti[b]);
			adj[sti[neg(b)]].push_back(sti[a]);
		}

		bool possible = true;

		for (int i = 0; i < counter; i++){
			if (discovery[i] == -1){
				possible &= tarjanSCC(i, adj, visited, low, discovery, its);
			}
		}

		cout << "Instancia " << t++ << endl;
		if (possible){
			cout << "sim" << endl << endl;
		}
		else{
			cout << "nao" << endl << endl;
		}
	}
}

