#include <iostream>

class Complex {
private:
    double re;
    double im;

public:
    Complex(double _re = 0, double _im = 0) : re(_re), im(_im) {}

    friend Complex operator+(const Complex& c1, const Complex& c2) {
        return {c1.re + c2.re, c1.im + c2.im};
    }

    Complex& operator+=(const Complex& c) {
        re += c.re;
        im += c.im;
        return *this;
    }

    friend Complex operator*(const Complex& c1, const Complex& c2) {
        return {c1.re * c2.re - c1.im * c2.im, c1.re * c2.im + c1.im * c2.re};
    }

    Complex& operator*=(const Complex& c) {
        *this = *this * c;
        return *this;
    }

    Complex operator-() const {
        return {-re, im};
    }

    double Re() const {
        return re;
    }

    double& Re() {
        return re;
    }

    double Im() const {
        return im;
    }

    double& Im() {
        return im;
    }

    double operator[](int i) const {
        if (i == 0)
            return re;
        else
            return im;
    }

    double at(int i) const {
        if (i == 0)
            return re;
        if (i == 1)
            return im;
        throw std::out_of_range("index is out of range: " + std::to_string(i));
    }
};

using namespace std;

ostream& operator<<(ostream& out, const Complex& c){
    return out << "(" << c.Re() << ", " << c.Im() << ")\n";
}



int main() {
    Complex z1; //0
    Complex z2 = 5;
    Complex z3(-3, 10);

    cout << z1 + z2 << '\n';
    cout << -z3 * z1 << '\n';
    cout << z3.Re() << ' ' << z3.Im() << '\n';

    return 0;
}
