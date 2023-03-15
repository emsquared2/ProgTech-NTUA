#include <iostream>
#include <list>

using namespace std;

class Graph {
    public:

      Graph(int V) : Vertices(V), adj(new list<int>[V]) {}

      ~Graph() {
          Vertices = 0;
          adj = nullptr;
          delete adj;
      }
      void addEdge(int u, int v) {
          adj[u].push_back(v);
          adj[v].push_back(u);
      }
      bool Eulerian() {
          int odd = 0;
          for(int i = 0; i < Vertices; ++i) {
              if(adj[i].size() % 2 != 0) ++odd; 
          }
          if(odd > 2) return false;
          if(odd == 2) {
              cout << "PATH";
              for(int i = 0; i<Vertices; ++i) {
                  if(adj[i].size() % 2 != 0) cout << " " << i;
              }
              cout << endl;
              return true;
          }
          if(odd == 0) {
              cout << "CYCLE" << endl;
              return true;
          }
      }
    
    private:
      
      int Vertices;
      list<int> *adj;
};

int main() {

    int N, M;
    cin >> N >> M;
    Graph g(N);
    for(int i = 0; i < M; ++i) {
        int u,v;
        cin >> u >> v;
        g.addEdge(u, v);
    }
    if(!g.Eulerian()) cout << "IMPOSSIBLE" << endl;
}