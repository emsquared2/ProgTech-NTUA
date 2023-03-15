#ifndef CONTEST
#include "babyratio.hpp"
#endif
#include <iostream>

using namespace std;

int rational::gcd(int a,int b) {
    a = abs(a);
    b = abs(b);
    if(a == 0 || b == 0) return a+b;
    else if(a > b) return gcd(a % b, b);
    else return gcd(a, b % a);
}
rational::rational(int n, int d) {
    nom = n / gcd(n, d);
    den = d / gcd(n, d);
    if(den < 0) { nom = -nom; den = -den; }
}

rational rational::add(rational r) {
    return rational( nom * r.den + den * r.nom , den * r.den );
}

rational rational::sub(rational r) {
    return rational( nom * r.den - den * r.nom , den * r.den );
}

rational rational::mul(rational r) {
    return rational( nom * r.nom , den * r.den );
}

rational rational::div(rational r) {
    return rational( nom * r.den , den * r.nom );
}

void rational::print() {
    cout << nom << "/" << den;
}
