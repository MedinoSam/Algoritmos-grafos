#include <iostream>
#include <vector>

using namespace std;

int cnt = 0;
void DFSrec(vector<vector<int> >& adj, vector<int>& pre, int v)
{
	pre[v] = cnt++;
	// for(int w : adj[v])
	for(int i=0; i< adj[v].size(); i++)
	{
		int w = adj[v][i];
		if(pre[w] == -1)
			DFSrec(adj, pre, w);
	}
}

void DFS(vector<vector<int> >& adj, vector<int>& pre)
{
	cnt = 0;
	int n = adj.size();

	for(int v=0; v<n; v++)  
		pre[v] = -1;

	for(int v=0; v<n; v++)
	{
		if(pre[v] == -1)
			DFSrec(adj, pre, v);
	}

}

int main()
{

	// Leitura do grafo
	int n, m;
	cin >> n >> m;

	vector<vector<int> > adj(n, vector<int>());
	int v, w;
	for(int i=0; i<m;i++)
	{
		cin >> v >> w;
		adj[v].push_back(w);
		adj[w].push_back(v);
	}

	// cout << n << " " << m << endl;

	vector<int> pre(n, -1);

	DFS(adj, pre);

	for(int i=0; i<n; i++)
		cout << "Vertice " << i << " pre " << pre[i] << endl;

}