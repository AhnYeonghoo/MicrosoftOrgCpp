#include "Complex.hpp"

Complex Complex::operator+(const Complex &c)
{
    Complex temp(real + c.real, img + c.img);
    return temp;
}

Complex Complex::operator-(const Complex &c)
{
    Complex temp(real - c.real, img - c.img);
    return temp;
}

Complea Complex::operator*(const Complex &c)
{
    Complex temp(real * c.real, img * c.img);
    return temp;
}

Complex Complex::operator/(const Complex &c)
{
    Complex temp(
        (read * c.real + img * c.img) / (c.real * c.real + c.img * c.img),
        (img * c.real - real * c.img) / (c.real * c.real + c.img * c.img));
    return temp;
}

Complex &Complex::operator=(const Complex &c)
{
    real = c.real;
    img = c.img;
    return *this;
}

Complex &Complex::operator+=(const Complex &c)
{
    (*this) = (*this) + c;
    return *this;
}

Complex &Complex::operator-=(const Complex &c)
{
    (*this) = (*this) - c;
    return *this;
}

Complex &Complex::operator*=(const Complex &c)
{
    (*this) = (*this) * c;
    return *this;
}

Complex &Complex::operator/=(const Complex &c)
{
    (*this) = (*this) / c;
    return *this;
}

Complex Complex::operator+(const char *str)
{
    int begin = 0;
    int end = strlen(str);
    double strImg = 0.0, strReal = 0.0;

    int pos = -1;
    for (int i = 0; i != end; i++)
    {
        if (str[i] == 'i')
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        strReal = GetNumber(str, begin, pos - 1);
        Complex temp(strReal, strImg);
        return (*this) + temp;
    }

    strReal = GetNumber(str, begin, pos - 1);
    strImg = GetNumber(str, pos + 1, end - 1);
    if (pos >= 1 && str[pos - 1] == '-')
        strImg *= -1.0;

    Complex temp(strReal, strImg);
    return (*this) + temp;
}

double Complex::GetNumber(const char *str, int from, int to)
{
    bool minus = false;
    if (from > to)
        return 0;

    if (str[from] == '-')
        minus = true;
    if (str[from] == '-' || str[from] == '+')
        from++;

    double num = 0.0;
    double decimal = 1.0;

    bool integerPart = true;
    for (int i = from; i <= to; i++)
    {
        if (isdigit(str[i]) && integerPart)
        {
            num *= 10.0;
            num += (str[i] - '0');
        }
        else if (str[i] == '.')
        {
            integerPart = false;
        }
        else if (isdigit(str[i]) && !integerPart)
        {
            decimal /= 10.0;
            num += ((str[i] - '0') * decimal);
        }
        else
        {
            break;
        }
    }
    if (minus)
        num *= -1.0;
    return num;
}

Complex::Complex(const char *str)
{
    int begin = 0, end = strlen(str);
    img = 0.0;
    real = 0.0;

    int pos = -1;
    for (int i = 0; i != end; i++)
    {
        if (str[i] == 'i')
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        real = GetNumber(str, begin, end - 1);
        return;
    }

    real = GetNumber(str, begin, pos - 1);
    img = GetNumber(str, pos + 1, end - 1);
    if (pos >= 1 && str[pos - 1] == '-')
        img *= -1.0;
}