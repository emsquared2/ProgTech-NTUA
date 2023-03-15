#include <iostream>
using namespace std;

template <typename T>
class stack {

    private:
      T *a;
      int top;
      int SIZE;

    public:
      stack(int size) {  //constructor
          a = new T[size];
          top = 0;
          SIZE = size;
      }
      stack(const stack &s) {  //copy constructor
         a = new T[s.SIZE];
         SIZE = s.SIZE;
         top = s.top;
         for(int i = 0; i < top; i++)
          a[i] = s.a[i];
      }
      ~stack() {
          delete []a;
          a = nullptr;
      }
      const stack & operator = (const stack &s) {
          delete []a;
          a = new T[s.SIZE];
          for(int i = 0; i < s.top; i++) 
            a[i] = s.a[i];
          top = s.top;
          SIZE = s.SIZE;
          return *this;
      }
      bool empty() {
          return top == 0;
      }
      void push(const T &x) {
          a[top++] = x;
      }
      T pop() {
          return a[--top];
      }
      int size() {
          return top;
      }
      friend ostream & operator << (ostream &out, const stack &s) {
          if(s.top == 0) { out << "[]"; 
            return out; }
          else {
            out << "[";
            for(int i = 0; i < s.top-1; i++)
              out << s.a[i] << ", ";
            out <<s.a[s.top-1] << "]";
            return out;
          }
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