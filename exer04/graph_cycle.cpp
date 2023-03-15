#include <iostream>
#include <vector>
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
    }
    bool cycle(vector<int> &path) const {
        bool *visited = new bool[Vertices];
        bool *recStack = new bool[Vertices];
        for(int i = 0; i < Vertices; ++i) {
            visited[i] = recStack[i] = false;
        }
        for(int i = 0; i < Vertices; ++i) 
            if(cycle_help(i, visited, recStack, path)) 
               return true;
        return false;
    }    

  private:

    int Vertices;
    list<int> *adj;

    bool cycle_help(int v, bool visited[], bool *recStack, vector<int> &path) const {
        if(visited[v] == false) {
            visited[v] = true;
            recStack[v] = true;
            path.push_back(v);
            list<int>::iterator i;
            for(i = adj[v].begin(); i != adj[v].end(); ++i) {
                if(!visited[*i] && cycle_help(*i, visited, recStack, path) ) 
                  return true;
                else if(recStack[*i]) 
                  return true;
            }
        }
        recStack[v] = false;
        if(!path.empty()) path.pop_back();
        return false;
    }
};

#ifndef CONTEST
 int main() {
  int V, E;
  cin >> V >> E;
  Graph g(V);
  for (int i = 0; i < E; ++i) { int u, v; cin >> u >> v; g.addEdge(u, v); }
  vector<int> path;  
  bool c = g.cycle(path);
  if(c) {
    cout << "CYCLE: ";
    for(int i = 0; i < path.size(); ++i) 
      cout << path[i] << (i == path.size()-1 ? "\n" : " ");
  } else {
      cout << "NO CYCLE"<<endl;
  }
}
#endif