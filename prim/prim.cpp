#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <string.h>
#include <fstream>
using namespace std;

int main(int argc, char **argv){
    string input_file = "";
    string output_file = "";
    int verticeInicial = 1;
    bool solucao = false;

    for(int i=1; i<argc; i++){
        if(strcmp(argv[i], "-h") == 0){
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o arquivo" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            cout << "-s: mostra a solução" << endl;
            cout << "-i: vertice  inicial" << endl;
            return 0;
        }
        else if(strcmp(argv[i], "-o") == 0 && i < argc - 1) output_file = argv[++i];

        else if(strcmp(argv[i], "-f") == 0 && i < argc - 1) input_file = argv[++i];

        else if(strcmp(argv[i], "-i") == 0 && i < argc - 1) verticeInicial = atoi(argv[++i]);

        else if(strcmp(argv[i], "-s") == 0) solucao = true;
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

    vector<vector<pair<int, int>>> grafo(n+1);

    for (int i=1; i<=m; i++){
        int u, v, peso;
        fin >> u >> v >> peso;

        grafo[u].emplace_back(v, peso);
        grafo[v].emplace_back(u, peso);
    }
    fin.close();

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

    if(!output_file.empty()){
        ofstream fout(output_file);
        if(!fout){
            cerr << "Nao foi possivel abrir o arquivo de saida: " << output_file << endl;
            return 1;
        }

        if(solucao){
            for(int v = 1; v <= n; v++){
                if(pai[v] != -1){
                    fout << "(" << pai[v] << "," << v << ")";
                    if(v!=n)
                        fout << " ";
                    else
                        fout << endl;
                }
            }  
        }
        else{
            fout << custoTotal << endl;
        }
        fout.close();
    }
    else{
        if(solucao){
            for(int v = 1; v <= n; v++){
                if(pai[v] != -1){
                    cout << "(" << pai[v] << "," << v << ")";
                    if(v!=n)
                        cout << " ";
                    else
                        cout << endl;
                }
            }  
        }
        else{
            cout << custoTotal << endl;
        }
    }
    return 0;
}