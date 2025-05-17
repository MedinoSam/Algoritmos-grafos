#include <iostream>
#include <limits>
#include <vector>
#include  <queue>
using namespace std;

const  int INFINITO = numeric_limits<int>::max();
using Grafo = vector<vector<pair<int, int>>>;

vector<int> dijskra(int n, const Grafo& grafo, int verticeInicial){

    vector<int> dist(n+1, INFINITO);
    vector<int> visitado(n+1, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> fila;
    dist[verticeInicial] = 0;
    fila.emplace(0, verticeInicial);

    while(!fila.empty()){
        auto[d, u] = fila.top();
        fila.pop();

        if(visitado[u]) continue;

        visitado[u] = true;

        for(auto [v, peso] : grafo[u]){
            if(dist[u] + peso < dist[v]){
                dist[v] = dist[u] + peso;
                fila.emplace(dist[v], v);
            }
        }
    }

    for(int i=1; i<=n; i++){
        if(dist[i] == INFINITO) 
            dist[i] = -1;
    }
    return dist;
}


int main(){

    int n, m;
    cin >> n >> m;

    int verticeInicial = 1;
    Grafo grafo(n+1);

    for(int i=1; i<=m; i++){
        int u, v, peso;
        cin >> u >> v >> peso;
        if (peso < 0){
            cout << "Disjkra nao permite pesos negativos!" << endl;
            return 0;
        }
        grafo[u].emplace_back(v, peso);
        grafo[v].emplace_back(u, peso);
    }

    vector<int> dist = dijskra(n, grafo, verticeInicial);

    for (int i = 1; i <= n; i++) {
        cout << "distancia de " << verticeInicial << " ate " << i << ": ";
        if (dist[i] == -1)
            cout << "vertice inalcancavel";
        else
            cout << dist[i];
        cout << "\n";
    }

    return 0;
}