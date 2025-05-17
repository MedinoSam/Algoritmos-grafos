#include <vector>
#include <iostream>
#include <stack>
#include <string.h>
#include <fstream>
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


int main(int argc, char **argv){
    
    string input_file = "";
    string output_file = "";
    //percorre a string do terminal
    for(int i=1; i<argc; i++){
        if(strcmp(argv[i], "-h") == 0){
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o arquivo" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            return 0;
        }
        else if(strcmp(argv[i], "-o") == 0 && i < argc - 1) output_file = argv[++i];

        else if(strcmp(argv[i], "-f") == 0 && i < argc - 1) input_file = argv[++i];
    }

    if(input_file == ""){
        cerr << "Sem input especificado. Use o parametro -f" << endl;
        return 1;
    }

    ifstream fin(input_file);

    if(!fin){
        cerr << "Nao foi possivel abrir o arquivo de entrada: " << input_file << endl;
        return 1;
    }

    int  n, m;
    fin >> n >> m;

    vector<vector<int>> grafo(n+1);
    vector<vector<int>> grafoTransposto(n+1);
    vector<vector<int>> componentesFortementesConexas;

    int v,w;
    for (int i=1; i<=m; i++){

        fin >> v >> w;
        grafo[v].push_back(w);
        grafoTransposto[w].push_back(v);
    }

    fin.close();

    kosarajuAlgoritmo(grafo, grafoTransposto, componentesFortementesConexas);

     if(!output_file.empty()){

        ofstream fout(output_file);
        if(!fout){
            cerr << "Nao foi possivel abrir o arquivo de saida: " << output_file << endl;
            return 1;
        }

        for (int i = 0; i < componentesFortementesConexas.size(); i++) {
            fout << "Componente Fortemente Conexa " << i+1 << ": ";
                for (int v : componentesFortementesConexas[i]) {
                    fout << v << " ";
                }
            fout << endl;
        }
        fout.close();
    }
    else{
        for (int i = 0; i < componentesFortementesConexas.size(); i++) {
                for (int v : componentesFortementesConexas[i]) {
                    cout << v << " ";
                }
        cout << endl;
        }
    }
    return 0;
}