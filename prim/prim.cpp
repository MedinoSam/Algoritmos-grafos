#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

int main(){

    int n, m;

    cin >> n >> m;

    vector<vector<pair<int, int>>> grafo(n+1);

    for (int i=1; i<=m; i++){
        int u, v, peso;
        cin >> u >> v >> peso;

        grafo[u].emplace_back(v, peso);
        grafo[v].emplace_back(u, peso);
    }

    vector<bool> visitado(n+1, false);
    vector<int> chave(n+1, numeric_limits<int>::max());
    vector<int> pai(n+1, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> fila;
    chave[1] = 0;
    fila.push({0, 1});//primeiro peso depois  vértice.
    
    int custoTotal = 0;

    while(!fila.empty()){
        int pesoAtual = fila.top().first;
        int u = fila.top().second;
        fila.pop();

        if(visitado[u]) continue;

        visitado[u] = true;
        custoTotal += pesoAtual;

        for(auto[v, peso]: grafo[u]){
            if(!visitado[v] && peso < chave[v]){
                chave[v] = peso;
                pai[v] = u;
                fila.push({peso, v});
            }
        } 
    }

    cout << "custo total: " << custoTotal << endl;

    cout << "Arestas da  AGM: " << endl;
    for(int v = 1; v <= n; v++){
        if(pai[v] != -1){
            cout << pai[v]  << " - " << v << " (peso " << chave[v] << ")" << endl;
        }
    }
}