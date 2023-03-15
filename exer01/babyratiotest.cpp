#include <iostream>
#include "babyratio.hpp"
using namespace std;

int main() {
    rational a(1, 2);
    rational b(3, 4);
    rational c(5, 6);
    a.add(b).sub(c).print();
    cout << endl;
    a.print();
    cout << " should still be 1/2" << endl;
}