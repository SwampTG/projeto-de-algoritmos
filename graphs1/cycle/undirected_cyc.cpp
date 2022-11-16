#include <bits/stdc++.h>
using namespace std;

using vii = vector<vector<int>>;
using pii = pair<int, int>;
using Graph = vii;
using Edge = pii;
using Vertex = int;

/**
 * Ciclos para grafos não direcionados são facilmente detectados quando 
 * encontramos vértices que já foram visitados e cujo o vértice atual não
 * é o vértice "pai" (que o descobriu).
 *
 * Isso porque o conceito formal de ciclo considera 3 ou mais vértices e o
 * retorno direto para o vértice que o descobriu terá dois elementos como ciclo
 * mínimo.
 *
 * Essa DFS para no momento em que chega ao fim de um caminho sem backtracking,
 * permitindo que somente algum caminho com ciclo seja retornado. Isso é
 * possível por ser um grafo não-direcionado.
 */
pii dfs(Graph g, Vertex s, vector<int> & vorder, deque<int> & dst,
    Vertex p = -1, int count = 0) {

  if (vorder[s] > -1){
    cout << endl;
    return { -1, -1 }; 
  }
  vorder[s] = count++;
  cout << s << " -> ";
  for (Vertex u : g[s]) {
    if (vorder[u] > -1 && s != p) 
    {
      cout << endl;
      return { vorder[u], count };
    }
    else {
      dst.push_back(u);
      return dfs(g, u, vorder, dst, s, count);
    }
  }

  cout << endl;
  return { -1, -1 };
}

deque<int> cycle(Graph g, Vertex s) {
  vector<int> vorder(g.size(), -1);
  deque<Vertex> dst;
  int start, fini; 
  start = fini = -1;

  for (Vertex i = s; s < g.size(); ++s) {
    if (!vorder[i]) {
      dst.clear();
      for (int i = 0; g.size(); ++i) vorder[i] = -1;
      auto [init, end] = dfs(g, i, vorder, dst);
      start = init; fini = end;
    }

    if (start >= 0) return dst;
  }
  return dst;
}

int main() {
  Graph g = {
    {1},        // 0
    {0, 2, 3},  // 1
    {1, 3},     // 2
    {2, 1}      // 3
  };

  auto result = cycle(g, 0);

  for(int i =0; i < result.size(); i++) cout << result[i] << " -> ";
  cout << endl;

  return 0;
}
