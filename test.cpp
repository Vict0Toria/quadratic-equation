#include <cassert>
#include <string>
#include <iostream>

// подключаем solver из main.cpp (упрощённый вариант без .h)
class QuadraticSolver {
public:
    static std::string solve(const std::string& a,
                             const std::string& b,
                             const std::string& c);
};

// копируем реализацию (чтобы тесты компилировались без линковки)
static bool isValid(const std::string& s) {
    if (s.empty()) return false;

    int i = 0;
    bool digit = false;
    bool dot = false;

    if (s[i] == '+' || s[i] == '-') i++;

    for (; i < (int)s.size(); i++) {
        if (isdigit(s[i])) digit = true;
        else if (s[i] == '.') {
            if (dot) return false;
            dot = true;
        } else return false;
    }

    return digit;
}

static bool parse(const std::string& s, double& x) {
    if (!isValid(s)) return false;
    try {
        size_t idx;
        x = std::stod(s, &idx);
        return idx == s.size();
    } catch (...) {
        return false;
    }
}

std::string QuadraticSolver::solve(const std::string& sa,
                                   const std::string& sb,
                                   const std::string& sc)
{
    double a, b, c;

    if (!parse(sa, a) || !parse(sb, b) || !parse(sc, c))
        return "WRONG";

    const double EPS = 1e-9;

    if (fabs(a) < EPS) {
        if (fabs(b) < EPS) {
            if (fabs(c) < EPS) return "INF";
            return "NO SOLUTION";
        }

        double x = -c / b;
        if (fabs(x) < EPS) x = 0;

        return "OK\n1\n" + std::to_string(x);
    }

    double D = b * b - 4 * a * c;

    if (D < -EPS) return "NO SOLUTION";

    if (fabs(D) < EPS) {
        double x = -b / (2 * a);
        if (fabs(x) < EPS) x = 0;

        return "OK\n1\n" + std::to_string(x);
    }

    double x1 = (-b - sqrt(D)) / (2 * a);
    double x2 = (-b + sqrt(D)) / (2 * a);

    if (fabs(x1) < EPS) x1 = 0;
    if (fabs(x2) < EPS) x2 = 0;

    if (x1 > x2) std::swap(x1, x2);

    return "OK\n2\n" + std::to_string(x1) + "\n" + std::to_string(x2);
}

// ================== ТЕСТЫ ==================

void testWrong() {
    assert(QuadraticSolver::solve("abc", "2", "3") == "WRONG");
}

void testInf() {
    assert(QuadraticSolver::solve("0", "0", "0") == "INF");
}

void testNoSolution() {
    assert(QuadraticSolver::solve("0", "0", "5") == "NO SOLUTION");
}

void testLinear() {
    std::string r = QuadraticSolver::solve("0", "2", "-4");
    assert(r.find("OK") != std::string::npos);
}

void testOneRoot() {
    std::string r = QuadraticSolver::solve("1", "2", "1");
    assert(r.find("1") != std::string::npos);
}

void testTwoRoots() {
    std::string r = QuadraticSolver::solve("1", "-3", "2");
    assert(r.find("2") != std::string::npos);
}

void testNegativeA() {
    std::string r = QuadraticSolver::solve("-1", "0", "1");
    assert(r.find("OK") != std::string::npos);
}

void testZeroRoot() {
    std::string r = QuadraticSolver::solve("1", "0", "0");
    assert(r.find("0") != std::string::npos);
}

int main() {
    testWrong();
    testInf();
    testNoSolution();
    testLinear();
    testOneRoot();
    testTwoRoots();
    testNegativeA();
    testZeroRoot();

    std::cout << "ALL TESTS PASSED\n";
}
