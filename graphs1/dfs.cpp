#include <bits/stdc++.h>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using Id = int;

template<class T>
class Vertex
{
  public:
    bool visited;
    T id;

    Vertex(T id): visited(false), id(id)
    {}
};

using Id = int;
using Adj = vector<Vertex<Id>>;
using Edge =  pair<Vertex<Id>, Vertex<Id>>;
using Graph = vector<Adj>;

template <class T>
T dfs(Graph g, Vertex<Id> s, function <T (Vertex<Id>)> process) {
  Id id_s = s.id;
  s.visited = true;
  T result = process(s);

  for (Vertex<Id> u : g[id_s]) {
    if (!u.visited) {
      u.visited = true;
      T result = process(u);
      dfs(g, u, process);
    };
  }
}

void print_v(Vertex<Id> u) {
  cout << u.id << endl;
}

int main() 
{
  Vertex<Id> v1(0), v2(1), v3(2), v4(3);
  Graph g({
    {v4},
    {v2, v3},
    {v1, v4},
    {v1},
    {v1, v2}
  });

  dfs(g, 0, print_v);

  return 0;
}
