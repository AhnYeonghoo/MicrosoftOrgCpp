#include <iostream>

class Complex
{
private:
    double real, img;

public:
    Complex(double real, double img) : real(real), img(img) {}
    Complex(const Complex &c) { real = c.real, img = c.img; }
    Complex(const char *str);

    Complex operator+(const Complex &c);
    Complex operator-(const Complex &c);
    Complex operator*(const Complex &c);
    Complex operator/(const Complex &c);
    Complex &operator=(const Complex &c);

    Complex &operator+=(const Complex &c);
    Complex &operator-=(const Complex &c);
    Complex &operator*=(const Complex &c);
    Complex &operator/=(const Complex &c);

    Complex Complex::operator+(const char *str);

    void Println() { std::cout << "( " << real << " , " << img << " ) " << std::endl; }
    double GetNumber(const char *str, int from, int to);
};