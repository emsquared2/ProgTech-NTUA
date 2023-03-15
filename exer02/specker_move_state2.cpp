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
      out << "takes " << move.getSourceCoins() << " coins from heap " << move.getSource() << " and puts ";    
      if (move.getTargetCoins()==0) out<< "nothing";  
      else out << move.getTargetCoins() << " coins to heap " << move.getTarget();  
      return out;   
    }  
    private:

      int Number_of_Coins_Taken;  
      int heap_from;  
      int heap_to;  
      int Number_of_Coins_placed;  
};  
  
Move::Move() {}  
Move::Move(int sh, int sc, int th, int tc) {  
  Number_of_Coins_Taken=sc;  
  heap_from=sh;  
  heap_to=th;  
  Number_of_Coins_placed=tc;  
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
      for(int i=0; i<state.getHeaps()-1; i++)   
        out<< state.a[i] << ", ";  
      out << state.a[state.getHeaps()-1];  
      return out;  
    }  
  
  protected:  
    int number_of_heaps;  
    int *a;  
};  
  
State::State(int h, const int c[]) {  
  number_of_heaps=h;  
  a=new int[h];  
  for(int i=0; i<h; i++) a[i]=c[i];  
}  
State::~State() {  
  delete []a;  
  a=nullptr;  
}  
void State::next(const Move &move) throw(logic_error) {  
  if( move.getSource() < 0 || move.getSource() > this->getHeaps()-1 || this->a[move.getSource()] < move.getSourceCoins()   
      || move.getTarget() < 0 || move.getTarget() > this->getHeaps()-1 || move.getTargetCoins()>=move.getSourceCoins()) throw logic_error("invalid heap");  
  this->a[move.getSource()]-=move.getSourceCoins();  
  this->a[move.getTarget()]+=move.getTargetCoins();  
}  
  
bool State::winning() const {  
  for(int i=0; i< this->number_of_heaps; i++)   
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