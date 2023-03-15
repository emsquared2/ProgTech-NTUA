#include <iostream>  
#include <stdexcept>  
  
using namespace std;  
  
class Move {  
  public:  
   
    Move();     
    //Take sc coins from heap sh and put tc coins to heap th.  
    Move(int sh, int sc, int th, int tc);  
    int getSource() const;  
    int getSourceCoins() const;  
    int getTarget() const;  
    int getTargetCoins() const;  
    friend ostream & operator << (ostream &out, const Move &move) {  
      out << "takes " << move.Number_of_Coins_Taken << " coins from heap " << move.heap_from << " and puts ";    
      if (move.Number_of_Coins_placed==0) out << "nothing";  
      else out << move.Number_of_Coins_placed << " coins to heap " << move.heap_to;  
      return out;   
    }  
    int Number_of_Coins_Taken;  
    int heap_from;  
    int heap_to;  
    int Number_of_Coins_placed;  
};  
  
Move::Move() {}  
Move::Move(int sh, int sc, int th, int tc) {  
  Number_of_Coins_Taken=sc;  
  heap_from = sh;  
  heap_to = th;  
  Number_of_Coins_placed = tc;  
}  
int Move::getSource() const {  
  return  this->heap_from;  
}  
int Move::getSourceCoins() const {  
  return  this->Number_of_Coins_Taken;  
}   
int Move::getTarget() const {  
  return  this->heap_to;  
}  
int Move::getTargetCoins() const {  
  return  this->Number_of_Coins_placed;  
}  
  
  
class State {  
  public:  
  
    State();  
    Move move;  
    // State with h heaps, where the i-th heap starts with c[i] coins.  
    State(int h, const int c[]);  
    ~State();  
    void next(const Move &move) throw(logic_error);  
    bool winning() const;  
    int getHeaps() const;  
    int getCoins(int h) const throw(logic_error);  
     
    friend ostream & operator << (ostream &out, const State &state) {  
      for(int i = 0; i < state.number_of_heaps - 1; i++)   
        out << state.a[i] << ", ";  
      out << state.a[state.number_of_heaps-1];  
      return out;  
    }  
  
  protected:  
    int number_of_heaps;  
    int *a;  
};  
  
State::State(int h, const int c[]) {  
  number_of_heaps = h;  
  a = new int[h];  
  for(int i = 0; i < h; i++) a[i] = c[i];  
}  
State::~State() {  
  delete []a;  
  a = nullptr;  
}  
void State::next(const Move &move) throw(logic_error) {  
  if( move.heap_from < 0 || move.heap_from > this->number_of_heaps-1 || this->a[move.heap_from] < move.Number_of_Coins_Taken   
      || move.heap_to < 0 || move.heap_to > this->number_of_heaps-1 || move.Number_of_Coins_placed>=move.Number_of_Coins_Taken) throw logic_error("invalid heap");  
  this->a[move.heap_from] -= move.Number_of_Coins_Taken;  
  this->a[move.heap_to] += move.Number_of_Coins_placed;  
}  
  
bool State::winning() const {  
  for(int i = 0; i < this->number_of_heaps; i++)   
    if( this->a[i] != 0 ) return false;  
  return true;  
}  
  
int State::getHeaps() const {  
  return this->number_of_heaps;  
}  
  
int State::getCoins(int h) const throw(logic_error) {  
  if(h < 0 || h > this->number_of_heaps-1) throw logic_error ("invalid heap");  
  return this->a[h];  
}  