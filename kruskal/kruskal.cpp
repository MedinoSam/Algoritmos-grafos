#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
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

int main(){

    int n, m;

    cin >> n >> m;

    vector<tuple<int, int, int>> arestas;
    for(int i=0; i < m; ++i){
        int u, v, peso;
        cin >> u >> v >> peso;
        arestas.emplace_back(peso, u, v);
    }

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
    
    cout << "Custo total da AGM " << custoTotal << endl;

    cout << "AGM " << endl;
    for(auto[u, v, peso] : agm){
        cout << u << " - " << v << " peso " << peso << endl;
    }
}