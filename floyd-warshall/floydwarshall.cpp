#include <iostream>
#include <limits>
#include <vector>
#include <iomanip>
#include <string.h>
#include  <fstream>
using namespace std;

const  int INFINITO = numeric_limits<int>::max();

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

    int n, m;
    fin >> n >> m;

    vector<vector<int>> dist(n+1, vector<int>(n+1, INFINITO));
    vector<vector<int>> pred(n+1, vector<int>(n+1, -1));

    for (int i = 1; i <= n; i++){
        dist[i][i] = 0;
        pred[i][i] = i;
    }

    for(int i=1; i<=m; i++){
        int u, v, peso;
        fin >> u >> v >> peso;
        dist[u][v] = peso;
        dist[v][u] = peso;
        pred[u][v] = v;
    }
    fin.close();

    if(!output_file.empty()){

        ofstream fout(output_file);
        if(!fout){
            cerr << "Nao foi possivel abrir o arquivo de saida: " << output_file << endl;
            return 1;
        }
        for(int k=1; k<=n; k++){
            for(int i=1; i<=n; i++){
                for(int j=1; j<=n; j++){
                    if(dist[i][k] != INFINITO && dist[k][j] != INFINITO){
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][j] == INFINITO)
                    fout << setw(4) << "*";
                else
                    fout << setw(4) << dist[i][j];
            }
            fout << "\n";
        }
        fout.close();
    }
    else{
        for(int k=1; k<=n; k++){
            for(int i=1; i<=n; i++){
                for(int j=1; j<=n; j++){
                    if(dist[i][k] != INFINITO && dist[k][j] != INFINITO){
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][j] == INFINITO)
                    cout << setw(4) << "*";
                else
                    cout << setw(4) << dist[i][j];
            }
            cout << "\n";
        }
    }
    return 0;
}