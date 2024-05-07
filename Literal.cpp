#include <iostream>
#include <cmath>
int main()
{
    const int answer = 42;  // integer literal
    double d = sin(108.87); // floating point literal passed to sin
    bool b = true;

    int i = 157;

    int k = 0365;
    int m = 36'000'000;

    unsigned val_1 = 328u;
    long val_2 = 0x7FFFFFL;

    unsigned long val_3 = 0776745ul;
    auto val_4 = 108LL;
    auto val_5 = 0x80000000000000ULL << 16;

    char newline = '\n';
    char tab = '\t';
    char backspace = '\b';
    char backslash = '\\';
    char nullChar = '\0';

    std::cout << "Newline character: " << newline << "ending" << std::endl;
    std::cout << "Tab Character : " << tab << "ending" << std::endl;
    std::cout << "Backspace Character: " << backspace << "ending" << std::endl;
    std::cout << "Backslash Character: " << backslash << "ending" << std::endl;
    std::cout << "Null character: " << nullChar << "ending" << std::endl;
}