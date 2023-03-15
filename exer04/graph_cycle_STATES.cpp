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
    enum State {UNVISITED, VISITING, VISITED};

    bool cycle(vector<int> &path) const{
        int *State = new int[Vertices]; 
        for (int i = 0; i < Vertices; i++) 
          State[i] = UNVISITED;

        vector<int> v;  
        for (int i = 0; i < Vertices; ++i) {
          if(State[i] == UNVISITED) {
            if(cycle_help(i, State, path, v) == true) 
              return true; 
          }
        }
        return false;
    }

  private:

    int Vertices;
    list<int> *adj;

    bool cycle_help(int u, int State[], vector<int> &path,vector<int> &vec) const {
        State[u] = VISITING; 
        vec.push_back(u);
        list<int>::iterator i; 
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {
            int v = *i;
            if(State[v] == VISITING) {
              int x=0;
              while(vec[x]!=v) {
                vec[x] = 0;
                ++x;
              }
              while(x < vec.size()) {
                path.push_back(vec[x]);
                ++x;
              }
              return true;
            }
            if(State[v] == UNVISITED && cycle_help(v, State, path, vec))
              return true;
        }
        if(!vec.empty())
          vec.pop_back();
        State[u] = VISITED;
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
    for(int i=0; i<path.size(); ++i) 
      cout << path[i] << (i == path.size()-1 ? "\n" : " ");
  } else {
      cout << "NO CYCLE"<<endl;
  }
}
#endif