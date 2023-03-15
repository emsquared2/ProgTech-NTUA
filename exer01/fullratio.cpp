#include <iostream>
#ifndef CONTEST
#include "fullratio.hpp"
#endif

using namespace std;

int rational::gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    if(a == 0 || b == 0) return a + b;
    else if( a> b ) return gcd(a % b, b);
    else return gcd(a, b % a);
}
rational::rational(int n, int d) {
    nom = n / gcd(n, d);
    den = d / gcd(n, d);
    if(den < 0) { nom = -nom; den = -den; }
}

rational operator + (const rational &x, const rational &y) {
     return rational(x.nom * y.den + x.den * y.nom , x.den * y.den);
}

rational operator - (const rational &x, const rational &y) {
    return rational(x.nom * y.den - x.den * y.nom, x.den * y.den);
}

rational operator * (const rational &x, const rational &y) {
    return rational( x.nom * y.nom , x.den * y.den);
}

rational operator / (const rational &x, const rational &y) {
    return rational( x.nom * y.den, x.den * y.nom);
}

std::ostream & operator << (std::ostream &out, const rational &x) {
    out << x.nom << "/" << x.den;
    return out;
}