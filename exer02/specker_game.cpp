#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

class Game {

  public:

    Game(int heaps, int players);
    ~Game();
    void addHeap(int coins) throw(logic_error);
    void addPlayer(Player *player) throw(logic_error);
    void play(ostream &out) throw(logic_error);

  private:

    int calls;
    int total_heaps;
    int total_players;
    int heaps_placed;
    int players_placed;
    int *Heaps;
    vector <Player*> v;
};

Game::Game(int heaps, int players) {
  calls = 0;
  total_heaps = heaps;
  total_players = players;
  heaps_placed = 0;
  players_placed = 0;
  Heaps = new int[heaps];
  v.clear();
}

Game::~Game() {
  calls = 0;
  total_heaps = 0;
  total_players = 0;
  heaps_placed = 0;
  players_placed = 0;
  v.clear();
  delete []Heaps;
}

void Game::addHeap(int coins) throw(logic_error) {
  if( heaps_placed >= total_heaps) throw logic_error("max heaps");
  else Heaps[heaps_placed++] = coins;
}

void Game::addPlayer(Player *player) throw(logic_error) {
  players_placed++;
  if( players_placed > total_players ) throw logic_error("max players");
  v.push_back(player);
}

void Game::play(ostream &out) throw(logic_error) {
  State s( heaps_placed, Heaps);
  out << "State: " << s << endl;
  for(unsigned i = 0; i < v.size(); i++) {
    if( !s.winning() ) {
      out << *v[i] << " " <<  v[i]->play(s) << endl;
      s.next(v[i]->play(s));
      out << "State: " << s << endl;
    }
    if( !s.winning() && i == v.size()-1 ) i = -1;
    else if(s.winning() ) {
      out << *v[i] << " wins" << endl;
      break;
    }
  }
}