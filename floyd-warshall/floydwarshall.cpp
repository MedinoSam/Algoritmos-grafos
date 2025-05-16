#include <iostream>
#include <limits>
#include <vector>
#include <iomanip>
using namespace std;

const  int INFINITO = numeric_limits<int>::max();

int main(){

    int n, m;
    cin >> n >> m;

    vector<vector<int>> dist(n+1, vector<int>(n+1, INFINITO));
    vector<vector<int>> pred(n+1, vector<int>(n+1, -1));

    for (int i = 1; i <= n; i++){
        dist[i][i] = 0;
        pred[i][i] = i;
    }

    for(int i=1; i<=m; i++){
        int u, v, peso;
        cin >> u >> v >> peso;
        dist[u][v] = peso;
        pred[u][v] = v;
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

    cout << "\nDistancias Minimas:\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (dist[i][j] == INFINITO)
                cout << setw(3) << "*";
            else
                cout << setw(3) << dist[i][j];
        }
        cout << "\n";
    }
}