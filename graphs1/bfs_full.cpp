/**
  * Versão não escalável !!!
  * nós são identificados por inteiros.
  * BFS forma uma árvore, provavelmente não binária, de resposta, eliminando os ciclos (árvore é um
  * grafo acíclico ), assim como a DFS.
  *
  * O nó inicial é a raíz da árvore. Conseguimos calcular as distâcias
  * entre os níveis do grafo.
  *
  * Importante para visitar primeiramente os vizinhos do nó inicial.
 *
 * Complexidade: O(N + E). O Somatório dos graus de cada nó é 
 * (2 * m) para grafos não direcionados e m para grafos 
 * direcionados). Sendo m o número de arestas.
 *
 * Três formas: BFS(G), BFS(G, s), BFS(G, s, f)
 * Ou seja, podemos passar o nó inicial ou o inicial e o finial, para 
 * limitar a travessia do grafo.
 *
 * O(V + E) (Vertex + Edges), já que o somatório dos graus é 2 * E. Em casos
 * em que todos os nós se conectam com todos os outros, a complexidade vai para O(n²). Para
 * matrizes de adjacências o algoritmo sempre é O(n²).
 *
 * A bfs gera, implicitamente, uma árvore de arestas de resposta, onde ciclos são eliminados
 * , ou seja, podemos identificar as arestas não utilizadas na árvore para 
 * identificar ciclos.
 *
 */

#include <bits/stdc++.h>
using namespace std;

using Edge = pair<int, int>;
using Id = int;
using Adj = vector<Id>;
using Graph = vector<Adj>;

int bfs(Graph graph, Id init, vector<int> & dists, Graph & answer_tree) {
  if (dists[init] != -1) return 0; 

  queue<Id> q;
  q.emplace(init);
  dists[init] = 0;

  while(!q.empty()) {
    Id parent = q.front(); q.pop();

    for (Id child : graph[parent]) {
      if(dists[child] == -1) {
        q.emplace(child);
        answer_tree[parent].push_back(child);
        dists[child] = dists[parent] + 1;
      }
    }
  }

  return 1;
}

/**
 * Dá o número de componentes conectados do grafo e o vetor de distâncias
 * os nós não alcançáveis são marcados como -1.
 * Varre todos os nós, sem indicar um inicial.
 * Logo, depende de qual o primeiro nó colocado no grafo
 *
 * As distâncias dependem do nó inicial colocado no grafo e só possuem corretude, nessa implementação, para grafos conectados.
 */
tuple<vector<int>, Graph, int> bfs(Graph graph, Id s) {
  vector<int>dists(graph.size(), -1);
  Graph answer_tree(graph.size());
  int connections = -1;

  if (graph.size()) connections = 0;

  for (Adj u : graph) {
    for (Id s : u) {
      if (dists[s] == -1) {
        connections += bfs(graph, s, dists, answer_tree);
      }
    }
  }

  return { dists,  answer_tree, connections};
}

/**
 * Testing the functions
 */
int main () {
  Graph example({ {2, 3, 1}, {0}, {0, 3}, {4, 0, 2}, {3} });
  
  auto [dists, ans_tree, connections] = bfs(example, 0);

  cout << dists[3] << endl;

  for (int u = 0; u < ans_tree.size(); ++u ) {
    cout << u << "-->";
    for (Id v : ans_tree[u]) {
      cout << v << "-->";
    }
    cout << endl;
  }

  cout << "Connections:" << connections << endl;

  return 0;
}
