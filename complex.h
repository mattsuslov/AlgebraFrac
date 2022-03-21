#ifndef COMPLEX_H
#define COMPLEX_H

#include <QVector2D>

class Complex
{
public:
    Complex();
    Complex(double x, double y) : x_(x), y_(y) {}
    Complex(double x) : x_(x), y_(0) {}

    QVector2D toVector() const { return QVector2D(x_, y_); }

    Complex operator+() const {
        return Complex(x_, -y_);
    }

    friend Complex operator+(const Complex& a, const Complex& b) {
        return Complex(a.x_ + b.x_, a.y_ + b.y_);
    }

    friend Complex operator/(const Complex& a, double b) {
        return Complex(a.x_ / b, a.y_ / b);
    }

    friend Complex operator/(const Complex& a, const Complex& b) {
        return a * +b / b.toVector().lengthSquared();
    }

    friend Complex operator-(const Complex& a, const Complex& b) {
        return a + b * Complex(-1, 0);
    }
    friend Complex operator*(const Complex& a, const Complex& b) {
        return Complex(a.x_*b.x_ - a.y_*b.y_, a.x_*b.y_ + b.x_ * a.y_);
    }

private:
    double x_ = 0, y_ = 0;
};

#endif // COMPLEX_H
