#include <bits/stdc++.h>
#include <tuple>

using namespace std;

/**
 *
 * Directed simple graph. The strategy is to detect if there is a cycle O(1)
 * and to identify the cicle by backtracking, because there is
 * no guarantee that all Vertex in the Graph are components of
 * the cycle.
 *
 * Then, when we  have the number of nodes in the cycle, we can determine
 * K % |C|
 *
 * */

using vii = vector<vector<int>>;
using pii = pair<int, int>;
using vi = vector<int>;
using di = deque<int>;
using ll = long long;

bitset<200005>visited;
deque<pii> cycle;

deque<pii> dfs_b(vii rg, int s) {
  if (!visited[s]) {
    visited[s] = true;

//    cout << s << " -> ";
    for (auto u : rg[s]) {

        cycle.push_front({ u, s});
        return dfs_b(rg, u);
    }
  }

//  cout << endl;
  return cycle;
}

/**
 * dfs_f 
 * returns the Vertex that starts a cycle,
 * that means the fist vertex that is finded twice
 **/
int dfs_f(vii g, int s) {
  if (!visited[s]) {
    visited[s] = true;

    for (int u : g[s]) {
      return dfs_f(g,u);
    }
  } 

  return s;
}

/**
 * dfs
 * returns the path before entering a  cycle,
 * if it exists
 */
deque<pii> dfs(vii g, int s, int f, deque<pii> & path) {
  if (s != f && !visited[s]) {
    visited[s] = true;
    //cout << s << " -> ";
    for (int u : g[s]) {
      path.push_back({s, u});
      return dfs(g, u, f, path);
    }
  } 
  
  //cout << endl;
  return path; 
}

/** 
 * Returns all paths that were traveled
 * for the solving
 */
pair<deque<pii>, deque<pii>> cpath(vii g, vii rg) {
  int c = dfs_f(g, 0); 

  cout << "C: " << c << endl;

  for (int i = 0; i < g.size(); ++i) visited[i] = false;
  deque<pii> bpath;
  dfs(g, 0, c, bpath); 

  for (int i = 0; i < g.size(); ++i) visited[i] = false;
  deque<pii> path = dfs_b(rg, c);

  for (int i = 0; i <path.size(); ++i) 
    cout << path[i].first << " -> " ;

  cout << endl;

  for (int i = 0; i < bpath.size(); ++i) 
    cout << bpath[i].first << " -> ";

  cout << endl;
  return  { path, bpath };
}

/**
 * There is always a cycle, because 
 * |E| = |V| + 1
 * AND it's a Simple Directed Graph.
 */
int solve(vii g, vii rg, ll k) {
  auto result = cpath(g, rg);

  auto path = result.first;
  auto bpath = result.second;

  if (bpath.size() >= k) {
    return bpath[k].first;
  }

  int iresult = (k - bpath.size()) % path.size();

  //cout << "Path size " << path.size() << endl;
  //cout << "Bpath size " << bpath.size() << endl;

  //cout << "result index " << iresult << endl; 
  //cout << "Edge " << path[iresult].first << ' '<< path[iresult].second << endl;

  return path[(k - bpath.size()) % (path.size())].first; 
}

int main () {
  int n;
  long long k;
  cin >> n; cin >> k;

  vii g(n); vii rg(n);
  
  for (int i = 0; i < n; ++i) {
    int a; cin >> a;
    //cout << i << " -> " << a - 1 << " ";
    g[i].push_back(a - 1);
    rg[a - 1].push_back(i);
  }

  //cout << endl;

  ll result = solve(g, rg, k);
  cout << result + 1 << endl;
  
  return 0;
}
