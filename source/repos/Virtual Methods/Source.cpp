#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;

// Абстрактний базовий клас
class Equation {
public:
    virtual void solve() const = 0;
    virtual void print() const = 0;
    virtual ~Equation() {
        cout << "Destructor Equation\n";
    }
};

// Лінійне рівняння: ax + b = 0
class LinearEquation : public Equation {
    double a, b;
public:
    LinearEquation(double a, double b) : a(a), b(b) {}

    void print() const override {
        cout << a << "x + " << b << " = 0\n";
    }

    void solve() const override {
        if (a == 0) {
            if (b == 0)
                cout << "Нескінченно багато розв'язків\n";
            else
                cout << "Немає розв'язків\n";
        }
        else {
            cout << "x = " << -b / a << "\n";
        }
    }

    ~LinearEquation() override {
        cout << "Destructor LinearEquation\n";
    }
};

// Квадратне рівняння: ax² + bx + c = 0
class QuadraticEquation : public Equation {
    double a, b, c;
public:
    QuadraticEquation(double a, double b, double c) : a(a), b(b), c(c) {
        if (a == 0)
            throw invalid_argument("Коефіцієнт 'a' не може бути 0 для квадратного рівняння");
    }

    void print() const override {
        cout << a << "x² + " << b << "x + " << c << " = 0\n";
    }

    void solve() const override {
        double D = b * b - 4 * a * c;
        if (D > 0) {
            cout << "x1 = " << (-b + sqrt(D)) / (2 * a) << "\n";
            cout << "x2 = " << (-b - sqrt(D)) / (2 * a) << "\n";
        }
        else if (D == 0) {
            cout << "x = " << -b / (2 * a) << "\n";
        }
        else {
            cout << "Немає дійсних коренів (D = " << D << ")\n";
        }
    }

    ~QuadraticEquation() override {
        cout << "Destructor QuadraticEquation\n";
    }
};

void process(const Equation* eq) {
    eq->print();
    eq->solve();
    cout << "\n";
}

int main() {
    Equation* equations[] = {
        new LinearEquation(2, -8),
        new LinearEquation(0, 5),
        new LinearEquation(0, 0),
        new QuadraticEquation(1, -5, 6),
        new QuadraticEquation(1, -2, 1),
        new QuadraticEquation(1, 0, 4)
    };

    for (Equation* eq : equations) {
        process(eq);
        delete eq;
    }

    return 0;
}

