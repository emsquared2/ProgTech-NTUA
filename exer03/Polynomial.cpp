#include <iostream>

using namespace std;

class Polynomial {
  protected:

    class Term {
      protected:

        int exponent;
        int coefficient;
        Term *next;
        Term(int exp, int coeff, Term *n) : exponent(exp), coefficient(coeff), next(n) {}
        friend class Polynomial;
    };
    Term *head;
    int the_size;

  public:

    Polynomial() : head(nullptr), the_size(0) {}
    Polynomial(const Polynomial &p): head(nullptr), the_size(0) { copy(p); }
    ~Polynomial() { purge(); }

    Polynomial & operator = (const Polynomial &p) {
      purge();
      head = nullptr;
      the_size = 0;
      copy(p);
      return *this;
    }

    void addTerm(int expon, int coeff) {
      Term *p = new Term(expon, coeff, nullptr);
      if(coeff == 0) return;
      if(head == nullptr) { head = p; return; }
      if( exist(expon,coeff,*this) != nullptr ) { exist(expon,coeff,*this)->coefficient += coeff; return; }
      if(head->exponent < p->exponent) { p->next = head; head = p; }
      else {
        for(Term *q = head; q->next != nullptr; q = q->next) {
          if(q->next->exponent < p->exponent) { p->next = q->next; q->next = p; return; }
        }
        Term *q = head;
        while(q->next != nullptr) q = q->next;
        q->next = p;
      }
    }
    double evaluate(double x) {
      if(head == nullptr) return 0;
      double sum = 0;
      if(x == 0) {
        Term *q = head;
        while(q->next != nullptr) q = q->next;
        if(q->exponent == 0) sum = q->coefficient;
        return sum;
      }
      else {
        for(Term *q = head; q != nullptr; q = q->next) {
          double power = 1;
          for(int i = 0; i < q->exponent; i++) { power *=  x; }
          sum += (power * q->coefficient);
        }
      }
      return sum;
    }

    friend Polynomial operator+ (const Polynomial &p, const Polynomial &q) { return add(p, q); }

    friend Polynomial operator* (const Polynomial &p, const Polynomial &q) { return mult(p,q); }

    friend ostream & operator << (ostream &out, const Polynomial &p) { print(p); return out; }

  protected:

    void copy(const Polynomial &p) {
      for (Term *q = p.head; q != nullptr; q = q->next)
        addTerm(q->exponent, q->coefficient);
    }

    void purge() {
      Term *p = head;
      while (p != nullptr) {
        Term *q = p;
        p = p->next;
        delete q;
      }
    }

    Term * exist(int expon,int coeff,const Polynomial &p) {
      for(Term *q = p.head; q!= nullptr; q = q->next)
        if(q->exponent == expon) return q;
      return nullptr;
    }
     static void print(const Polynomial &p) {
      if(p.head == nullptr) { cout << 0; return; }
      if(p.head->next == nullptr && p.head->coefficient == 0) { cout << 0; return; }
      Term *Z = p.head;
      while(Z->coefficient == 0 && Z->next != nullptr) Z = Z->next;
      if(Z == nullptr || Z->coefficient == 0) { cout << 0; return; }
      if(Z->exponent == 0 && Z->coefficient > 0) { cout  << Z->coefficient; return; }
      if(Z->exponent == 0 && Z->coefficient < 0) { cout <<"- " << abs(Z->coefficient);  return; }
      if(Z->exponent == 1 && Z->coefficient == 1) cout << "x";
      else if(Z->exponent == 1 && Z->coefficient == -1) cout << "- x";
      else if(Z->exponent == 1) cout << Z->coefficient << "x";
      else if(Z->coefficient == 1) cout << "x^" << Z->exponent;
      else if(Z->coefficient == -1) cout << "- x^"<< Z->exponent;
      else if(Z->coefficient < 0) cout << "- "<< abs(Z->coefficient) << "x^" << Z->exponent;
      else cout << Z->coefficient << "x^" << Z->exponent;

      if(Z->next == nullptr) return;
      for(Term *q = Z->next; q != nullptr; q = q->next) {
        if(q->coefficient != 0) {
          if(q->exponent == 0 && q->coefficient > 0) { cout << " + " << q->coefficient; return; }
          else if(q->exponent == 0 && q->coefficient < 0) {cout << " - " << abs(q->coefficient); return; }
          if(q->exponent == 1 && q->coefficient == 1) cout<< " + x";
          else if(q->exponent == 1 && q->coefficient == -1) cout<< " - x";
          else if(q->exponent == 1 && q->coefficient > 0) cout << " + " << q->coefficient << "x";
          else if(q->exponent == 1 && q->coefficient < 0) cout << " - " << abs(q->coefficient) << "x";
          else {
            if(q->coefficient == 1) cout << " + x^" << q->exponent;
            else if(q->coefficient == -1) cout << " - x^" << q->exponent;
            else if(q->coefficient > 1) cout << " + " << q->coefficient << "x^" << q->exponent;
            else cout << " - " << abs(q->coefficient) << "x^" << q->exponent;
          }
        }
      }
     }
      static Polynomial add(const Polynomial &p, const Polynomial &q) {
      Term *a=p.head;
      Term *b=q.head;
      Polynomial A;
      while(a!=nullptr && b!=nullptr) {
        if(a->exponent > b->exponent) { A.addTerm(a->exponent, a->coefficient); a=a->next; }
        else if(a->exponent < b->exponent) { A.addTerm(b->exponent, b->coefficient); b=b->next; }
        else { A.addTerm( (a->exponent), (a->coefficient + b->coefficient) ); a=a->next; b=b->next; }
        if(a == nullptr)
          while(b != nullptr) { A.addTerm(b->exponent, b->coefficient); b=b->next; }
        else if(b == nullptr)
          while(a != nullptr) { A.addTerm(a->exponent, a->coefficient); a=a->next; }
      }
      return A;
    }
    static Polynomial mult(const Polynomial &p, const Polynomial &q) {
      Polynomial A;
      for(Term *a = p.head; a != nullptr; a = a->next)
        for(Term *b = q.head; b != nullptr; b = b->next)
          A.addTerm( (a->exponent + b->exponent) , (a->coefficient * b->coefficient) );
      return A;
    }
};