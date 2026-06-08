#include <cassert>
#include <string>

#include "../main.cpp"

using namespace std;

void testWrongInput()
{
    assert(
        QuadraticSolver::solve(
            "abc",
            "2",
            "3"
        ) == "WRONG"
    );
}

void testInf()
{
    assert(
        QuadraticSolver::solve(
            "0",
            "0",
            "0"
        ) == "INF"
    );
}

void testNoSolutionLinear()
{
    assert(
        QuadraticSolver::solve(
            "0",
            "0",
            "5"
        ) == "NO SOLUTION"
    );
}

void testLinearEquation()
{
    string result =
        QuadraticSolver::solve(
            "0",
            "2",
            "-4"
        );

    assert(
        result.find("OK")
        != string::npos
    );

    assert(
        result.find("2")
        != string::npos
    );
}

void testOneRoot()
{
    string result =
        QuadraticSolver::solve(
            "1",
            "2",
            "1"
        );

    assert(
        result.find("OK")
        != string::npos
    );
}

void testTwoRoots()
{
    string result =
        QuadraticSolver::solve(
            "1",
            "-3",
            "2"
        );

    assert(
        result.find("OK")
        != string::npos
    );
}

void testNoRoots()
{
    string result =
        QuadraticSolver::solve(
            "1",
            "0",
            "1"
        );

    assert(
        result == "NO SOLUTION"
    );
}

void testNegativeCoefficient()
{
    string result =
        QuadraticSolver::solve(
            "-1",
            "0",
            "1"
        );

    assert(
        result.find("OK")
        != string::npos
    );
}

int main()
{
    testWrongInput();

    testInf();

    testNoSolutionLinear();

    testLinearEquation();

    testOneRoot();

    testTwoRoots();

    testNoRoots();

    testNegativeCoefficient();

    return 0;
}
