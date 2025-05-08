#include <vector>
#include <iostream>
#include <stack>
using namespace std;

void dfsComPilhaPrioridade(vector<vector<int>> grafo, stack<int>&pilhaPrioridade, vector<bool>&visitado, int v){

    //percorre o grafo e ja cria a pilha com a prioridade dos vértices
    visitado[v] = true;
    for(auto i: grafo[v]){
        if (!visitado[i]){
            dfsComPilhaPrioridade(grafo, pilhaPrioridade, visitado, i);
        }
    }
    pilhaPrioridade.push(v);
}

void dfsComum(vector<vector<int>> grafoTransposto, vector<bool>&visitado, vector<int> &componenteAtual, int v){

    //a cada finalização do dfs, acha-se uma componente fortemente conexa
    visitado[v] = true;
    componenteAtual.push_back(v);
    for(auto i: grafoTransposto[v]){
        if (!visitado[i]){
            dfsComum(grafoTransposto, visitado, componenteAtual, i);
        }
    }
}

void kosarajuAlgoritmo(vector<vector<int>> grafo, vector<vector<int>> grafoTransposto, vector<vector<int>> &componentesFortementeConexas){

    stack<int> prioridadeVertices;
    vector<bool> visitado(grafo.size() ,false);
    vector<int> componenteAtual;
    
    for(int i=1; i<visitado.size(); i++){
        if(!visitado[i]){
            dfsComPilhaPrioridade(grafo, prioridadeVertices, visitado, i);
        }
    }
    visitado.assign(grafo.size(), false);

    while(!prioridadeVertices.empty()){
        int v = prioridadeVertices.top();
        prioridadeVertices.pop();

        if(!visitado[v]){
            dfsComum(grafoTransposto, visitado, componenteAtual, v);
            componentesFortementeConexas.push_back(componenteAtual);
            componenteAtual.clear();
        }
    }   
}


int main(){

    int  n, m;
    cin >> n >> m;

    vector<vector<int>> grafo(n+1);
    vector<vector<int>> grafoTransposto(n+1);
    vector<vector<int>> componentesFortementesConexas;

    int v,w;
    for (int i=1; i<=m; i++){

        cin >> v >> w;
        grafo[v].push_back(w);
        grafoTransposto[w].push_back(v);
    }
    
    kosarajuAlgoritmo(grafo, grafoTransposto, componentesFortementesConexas);

    for (int i = 0; i < componentesFortementesConexas.size(); i++) {
        cout << "Componente Fortemente Conexa " << i+1 << ": ";
        for (int v : componentesFortementesConexas[i]) {
        cout << v << " ";
        }
        cout << endl;
    }
}