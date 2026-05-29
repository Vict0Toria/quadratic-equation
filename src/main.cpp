#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Проверка числа через "интерпретатор"
class NumberInterpreter {
public:
    static bool isValid(const string& s) {
        if (s.empty()) return false;

        int i = 0;
        bool hasDigit = false;
        bool hasDot = false;

        // знак
        if (s[i] == '+' || s[i] == '-') {
            i++;
        }

        for (; i < (int)s.size(); i++) {
            if (isdigit(s[i])) {
                hasDigit = true;
            }
            else if (s[i] == '.') {
                if (hasDot) return false;
                hasDot = true;
            }
            else {
                return false;
            }
        }

        return hasDigit;
    }
};

int main() {
    string sa, sb, sc;

    cin >> sa >> sb >> sc;

    // Проверка ввода
    if (!NumberInterpreter::isValid(sa) ||
        !NumberInterpreter::isValid(sb) ||
        !NumberInterpreter::isValid(sc)) {

        cout << "WRONG";
        return 0;
    }

    double a = stod(sa);
    double b = stod(sb);
    double c = stod(sc);

    const double EPS = 1e-9;

    // Если a = 0 -> линейное уравнение
    if (fabs(a) < EPS) {

        // bx + c = 0
        if (fabs(b) < EPS) {

            // c = 0
            if (fabs(c) < EPS) {
                cout << "INF";
            }
            else {
                cout << "NO SOLUTION";
            }
        }
        else {
            double x = -c / b;

            cout << "OK\n";
            cout << 1 << "\n";
            cout << x;
        }

        return 0;
    }

    // Квадратное уравнение
    double D = b * b - 4 * a * c;

    if (D < -EPS) {
        cout << "NO SOLUTION";
    }
    else if (fabs(D) < EPS) {
        double x = -b / (2 * a);

        cout << "OK\n";
        cout << 1 << "\n";
        cout << x;
    }
    else {
        double x1 = (-b - sqrt(D)) / (2 * a);
        double x2 = (-b + sqrt(D)) / (2 * a);

        cout << "OK\n";
        cout << 2 << "\n";

        if (x1 < x2) {
            cout << x1 << "\n" << x2;
        }
        else {
            cout << x2 << "\n" << x1;
        }
    }

    return 0;
}
