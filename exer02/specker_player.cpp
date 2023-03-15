#include <iostream>  
#include <string>  
#include <stdexcept>  
  
using namespace std;  
  
class Player {  
  public:  
  
    Player() {}  
    Player(const string &n);  
    virtual ~Player() {}  
    virtual const string & getType() const = 0;  
    virtual Move play(const State &s) = 0;  
  
    friend ostream & operator << (ostream &out, const Player &player) {  
      out<< player.getType() << " player " << player.name ;  
      return out;  
    }  
    
  protected:  
  
    string name;  
    string type;  
};  
  
Player::Player(const string &n) {  
  name = n;  
}  
  
class GreedyPlayer :public Player {  
  public:  
  
    GreedyPlayer(const string &n);  
    virtual ~GreedyPlayer() override { name = "\0"; }  
    const string & getType() const override { return this->type; }  
    Move play(const State &s) override;  
};  
  
GreedyPlayer::GreedyPlayer(const string &n) {  
  name = n;  
  type = "Greedy";  
}  
  
Move GreedyPlayer::play(const State &s)  {  
  int x = 0,y = 0;  
  for(int i = 0; i < s.getHeaps(); i++)  
    if(x < s.getCoins(i) ) {  
      x = s.getCoins(i);  
      y = i;  
    }  
  return Move(y, x, 0, 0);  
}  
  
  
class SpartanPlayer :public Player {  
  public:  
  
    SpartanPlayer(const string &n);  
    virtual ~SpartanPlayer() override { name = "\0"; }  
    const string & getType() const override { return this->type; }  
    Move play(const State &s) override;  
};  
  
SpartanPlayer::SpartanPlayer(const string &n) {  
  name = n;  
  type = "Spartan";  
}  
  
Move SpartanPlayer::play(const State &s) {  
  int x = 0,y = 0;  
  for(int i = 0; i < s.getHeaps(); i++)  
    if(x < s.getCoins(i) ) {  
      x = s.getCoins(i);  
      y = i;  
    }  
  return Move(y, 1, 0, 0);  
}  
  
class SneakyPlayer :public Player {  
  public:  
    
    SneakyPlayer(const string &n);  
    virtual ~SneakyPlayer() override { name = "\0"; }  
    const string & getType() const override { return this->type; }  
    Move play(const State &s) override;  
};  
  
SneakyPlayer::SneakyPlayer(const string &n) {  
  name = n;  
  type = "Sneaky";  
}  
  
Move SneakyPlayer::play(const State &s) {  
  int x = 1000000, y = 0;  
  for(int i = 0; i < s.getHeaps(); i++)  
    if(x > s.getCoins(i) && s.getCoins(i) != 0) {  
      x = s.getCoins(i);  
      y = i;  
    }  
  return Move(y, x, 0, 0);  
}  
  
class RighteousPlayer :public Player {  
  public:  
  
    RighteousPlayer(const string &n);  
    virtual ~RighteousPlayer() override { name ="\0"; }  
    const string & getType() const override { return this->type; }  
    Move play(const State &s) override;  
};  
  
RighteousPlayer::RighteousPlayer(const string &n) {  
  name = n;  
  type = "Righteous";  
}  
  
Move RighteousPlayer::play(const State &s) {  
  int x = 0,y = 0;  
  for(int i = 0; i < s.getHeaps(); i++)  
    if(x < s.getCoins(i) ) {  
      x = s.getCoins(i);  
      y = i;  
    }  
  int z = 1000000, w = 0;  
  for(int i = 0; i < s.getHeaps(); i++)  
    if(z > s.getCoins(i) ) {  
      z = s.getCoins(i);  
      w = i;  
    }  
  if( x%2 == 0 ) return Move(y, x/2, w, x/2-1);  
  else return Move(y, x/2+1, w, x/2);  
}  