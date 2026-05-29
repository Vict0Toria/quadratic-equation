#include <cassert>
#include <string>
#include <cmath>

using namespace std;

double solveLinear(double b, double c) {
    return -c / b;
}

void testLinear() {
    double x = solveLinear(2, -4);

    assert(abs(x - 2.0) < 1e-9);
}

void testDiscriminant() {
    double D = 2 * 2 - 4 * 1 * 1;

    assert(D == 0);
}

int main() {

    testLinear();
    testDiscriminant();

    return 0;
}
