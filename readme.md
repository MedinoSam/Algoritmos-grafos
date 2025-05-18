# Algoritmos de Grafos em C++

Este repositório contém implementações dos principais algoritmos de grafos em C++, incluindo:

- [x] Algoritmo de Prim
- [x] Algoritmo de Kruskal
- [x] Algoritmo de Floyd-Warshall
- [x] Algoritmo de Dijkstra
- [x] Algoritmo de Kosaraju (componentes fortemente conexos)

🧠 Sobre

Estas implementações são importantes para reforçar o aprendizado acerca dos conteúdos abordados na disciplina Teoria dos Grafos


Cada arquivo `.cpp` é independente e pode ser compilado separadamente.


## 🚀 Como executar

### 1. Clonando o repositório

```bash
git clone https://github.com/seu-usuario/seu-repositorio.git
cd seu-repositorio

2. Compilando

Use g++ ou make, dependendo de como estiver estruturado.
Exemplo com g++:
g++ prim.cpp -o prim
g++ kruskal.cpp -o kruskal
g++ dijkstra.cpp -o dijkstra
g++ floyd_warshall.cpp -o floyd
g++ kosaraju.cpp -o kosaraju

3. Executando

Cada algoritmo aceita parâmetros via linha de comando. Exemplo:

./kruskal -f instances/grafo.mtx -s
./dijkstra -f instances/grafo.mtx -i 1

📌 Parâmetros suportados (variam por algoritmo)

-h : mostra o help

-f <arquivo> : arquivo de entrada (.mtx)

-o <arquivo> : redireciona a saída para um arquivo

-s : mostra a solução (AGM, caminhos, componentes, etc.)

-i <vértice> : vértice de origem (para Dijkstra, por exemplo)

✅ Requisitos

    Compilador C++ (recomenda-se g++)

    C++11 ou superior

📫 Contato

Caso tenha dúvidas ou sugestões, sinta-se à vontade para abrir uma issue ou entrar em contato.