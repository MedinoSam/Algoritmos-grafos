#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <string.h>
#include <fstream>
using namespace std;

class UnionFind{
    private:
        vector<int> pai, rank;

    public:
        UnionFind(int n){
            pai.resize(n+1);
            rank.resize(n+1, 0);
            for(int i=1; i<=n;++i){
                pai[i] = i;
            }
        }

        int find(int x){
            if(pai[x] != x){
                pai[x] = find(pai[x]);
            }
            return pai[x];
        }

        void Union(int x, int y){
            int px = find(x);
            int py = find(y);

            if (px == py) 
                return;

            if (rank[px] >= rank[py]){
                pai[py] = px;
                if(rank[px] == rank[py]){
                    rank[px]++;
                }
            } else{
                pai[px] = py;
            }
        }
};

void mostraSolucao(){

}

int main(int argc, char **argv){

    string input_file = "";
    string output_file = "";
    bool solucao = false;

    for(int i=1; i<argc; i++){
        if(strcmp(argv[i], "-h") == 0){
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o arquivo" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            cout << "-s: mostra a solução" << endl;
            return 0;
        }
        else if(strcmp(argv[i], "-o") == 0 && i < argc - 1) output_file = argv[++i];

        else if(strcmp(argv[i], "-f") == 0 && i < argc - 1) input_file = argv[++i];

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

    vector<tuple<int, int, int>> arestas;
    for(int i=0; i < m; ++i){
        int u, v, peso;
        fin >> u >> v >> peso;
        arestas.emplace_back(peso, u, v);
    }
    fin.close();

    sort(arestas.begin(), arestas.end());

    int custoTotal =  0;
    UnionFind  unionFind(n);
    vector<tuple<int, int, int>> agm;

    for(auto [peso, u, v] : arestas){
        if(unionFind.find(u) != unionFind.find(v)){
            unionFind.Union(u, v);
            agm.emplace_back(u, v, peso);
            custoTotal += peso;
        }
    }
    
    if(!output_file.empty()){
        ofstream fout(output_file);
        if(!fout){
            cerr << "Nao foi possivel abrir o arquivo de saida: " << output_file << endl;
            return 1;
        }

        if(solucao){
            for(size_t i = 0; i < agm.size(); ++i){
                auto [u, v, peso] = agm[i];
                fout << "(" << u << "," << v << ")";
                if(i < agm.size() - 1)
                    fout << " ";
                else
                    fout << endl;
            }  
        }
        else{
            fout << custoTotal << endl;
        }
        fout.close();
    }
    else{
        if(solucao){
            for(size_t i = 0; i < agm.size(); ++i){
                auto [u, v, peso] = agm[i];
                cout << "(" << u << "," << v << ")";
                if(i < agm.size() - 1)
                    cout << " ";
                else
                    cout << endl;
            }  
        }
        else{
            cout << custoTotal << endl;
        }

    }
    return 0;
}