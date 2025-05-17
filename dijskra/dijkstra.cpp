#include <iostream>
#include <limits>
#include <vector>
#include  <queue>
#include <string.h>
#include <fstream>
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


int main(int argc, char **argv){

    string input_file = "";
    string output_file = "";
    int verticeInicial = 1;
    
    //percorre a string do terminal
    for(int i=1; i<argc; i++){
        if(strcmp(argv[i], "-h") == 0){
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o arquivo" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            cout << "-i: vértice inicial" << endl;
            return 0;
        }
        else if(strcmp(argv[i], "-o") == 0 && i < argc - 1) output_file = argv[++i];

        else if(strcmp(argv[i], "-f") == 0 && i < argc - 1) input_file = argv[++i];

        else if(strcmp(argv[i], "-i") == 0 && i < argc - 1) verticeInicial = atoi(argv[++i]);
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


    int n, m;
    fin >> n >> m;

    Grafo grafo(n+1);

    for(int i=1; i<=m; i++){
        int u, v, peso;
        fin >> u >> v >> peso;
        if (peso < 0){
            cout << "Disjkra nao permite pesos negativos!" << endl;
            return 0;
        }
        grafo[u].emplace_back(v, peso);
        grafo[v].emplace_back(u, peso);
    }

    fin.close();

    if(!output_file.empty()){

        ofstream fout(output_file);
        if(!fout){
            cerr << "Nao foi possivel abrir o arquivo de saida: " << output_file << endl;
            return 1;
        }
        vector<int> dist = dijskra(n, grafo, verticeInicial);

        for(int i=1; i<=n; i++){
            fout << i << ":" << dist[i] << endl;
        }
        fout.close();
    }
    else{
        vector<int> dist = dijskra(n, grafo, verticeInicial);

        for(int i=1; i<=n; i++){
            cout << i << ":" << dist[i];
            if (i!=n)
                cout << " ";
            else
                cout << endl;
        }
    }
    return 0;
}