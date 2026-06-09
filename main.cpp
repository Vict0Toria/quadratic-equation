#include <iostream>
#include <string>
#include <cmath>
#include <sstream>

class QuadraticSolver {
private:
    static bool isValid(const std::string& s) {
        if (s.empty()) return false;

        int i = 0;
        bool digit = false;
        bool dot = false;

        if (s[i] == '+' || s[i] == '-') i++;

        for (; i < (int)s.size(); i++) {
            if (isdigit(s[i])) {
                digit = true;
            } else if (s[i] == '.') {
                if (dot) return false;
                dot = true;
            } else {
                return false;
            }
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

public:
    static std::string solve(const std::string& sa,
                             const std::string& sb,
                             const std::string& sc)
    {
        double a, b, c;

        if (!parse(sa, a) || !parse(sb, b) || !parse(sc, c))
            return "WRONG";

        const double EPS = 1e-9;

        std::ostringstream out;

        // линейный случай
        if (fabs(a) < EPS) {
            if (fabs(b) < EPS) {
                if (fabs(c) < EPS) return "INF";
                return "NO SOLUTION";
            }

            double x = -c / b;
            if (fabs(x) < EPS) x = 0;

            out << "OK\n1\n" << x;
            return out.str();
        }

        double D = b * b - 4 * a * c;

        if (D < -EPS) {
            return "NO SOLUTION";
        }

        if (fabs(D) < EPS) {
            double x = -b / (2 * a);
            if (fabs(x) < EPS) x = 0;

            out << "OK\n1\n" << x;
            return out.str();
        }

        double x1 = (-b - sqrt(D)) / (2 * a);
        double x2 = (-b + sqrt(D)) / (2 * a);

        if (fabs(x1) < EPS) x1 = 0;
        if (fabs(x2) < EPS) x2 = 0;

        if (x1 > x2) std::swap(x1, x2);

        out << "OK\n2\n" << x1 << "\n" << x2;
        return out.str();
    }
};

int main() {
    std::string a, b, c;
    std::cin >> a >> b >> c;

    std::cout << QuadraticSolver::solve(a, b, c);
}
