#include <iostream>
using namespace std;

template <typename T>

class stack {
  private:
    struct node {
      T data;
      node *next;
      };
      node *top;
      int SIZE;
      
  public:
    stack (int size) {
      top = nullptr;
      SIZE = size;
    }
    stack (const stack &s) {
      while(top != nullptr) 
        top = top->next;
      SIZE = s.SIZE;
      node *p = s.top;
      while(p != nullptr) {
        push(p->data);
        p = p->next;
      }
    }
    ~stack() {
      while(top != nullptr) 
        top = top->next;
      delete top;
    }
    const stack & operator = (const stack &s) {
      while(top != nullptr)
        top = top->next;
      node *p = s.top;
      while(p != nullptr) {
        push(p->data);
        p = p->next;
      }
      return *this;
    }
    bool empty() {
      return top == nullptr;
    }
    void push(const T &x) {
      node *p = new node;
      p->data = x;
      p = top;
      while(p != nullptr) 
        p = p->next;
      node *q = p;
      q->next = p;
      p->next = nullptr;
    }
    T pop() {
      node *p = top;
      while(p->next != nullptr)
        p = p->next;
      node *q = p;
      q->next = nullptr;
      p = p->next;
      delete p;
    }
    int size() {
      int x = 0;
      node *p = top;
      while(p != nullptr) {
        x++;
        p = p->next;
      }
      return x;
    }
    friend ostream & operator << (ostream &out, const stack &s) {
      node *p = s.top;
      out << "[";
      if(p == nullptr) 
        out << "]";
      else out << p->data;
      while(p != nullptr) {
        p = p->next;
        out << ", " << p->data;
      }
      out << "]";
      return out;
    }
};

#ifndef CONTEST

int main() {
  //integers
  stack<int> s(10);
  cout << "s is empty: " << s << endl;
  s.push(42);
  cout << "s has one element: " << s << endl;
  s.push(17);
  s.push(34);
  cout << "s has more elements: " << s << endl;
  cout << "How many? " << s.size() << endl;
  stack<int> t(5);
  t.push(7);
  cout << "t: " << t << endl;
  t=s;
  cout << "popping from s: " << s.pop() << endl;
  s.push(8);
  stack<int> a(s);
  t.push(99);
  a.push(77);
  cout << "s: " << s << endl;
  cout << "t: " << t << endl;
  cout << "a: " << a << endl;
  //doubles
  stack<double> c(4);
  c.push(3.14);
  c.push(1.414);
  cout << "c contains doubles " << c << endl;
  //characters
  stack<char> k(4);
  k.push('$');
  cout << "k contains a character " << k << endl;
}

#endif