#include <iostream>
#include <string>
#include <cstddef>
#include <cstdio>

struct Distance
{
private:
    explicit Distance(long double val) : kilometers(val)
    {
    }

    friend Distance operator"" _km(long double val);
    friend Distance operator"" _mi(long double val);

    long double kilometers{0};

public:
    const static long double km_per_mile;
    long double GetKilometers() { return kilometers; }

    Distance operator+(Distance other)
    {
        return Distance(GetKilometers() + other.GetKilometers());
    }
};

const long double Distance::km_per_mile = 1.609344L;

Distance operator"" _km(long double val)
{
    return Distance(val);
}

Distance operator"" _mi(long double val)
{
    return Distance(val * Distance::km_per_mile);
}

void operator"" _dump(unsigned long long int lit)
{
    printf("operator \"\" _dump(unsigned long long int) : ===>%llu<===\n", lit);
};

void operator"" _dump(char32_t lit)
{
    printf("operator \"\" _dump(char32_t) : ===>%d<===\n", lit);
};

void operator"" _dump(const char *lit, size_t)
{
    printf("operator \"\" _dump(const char*, size_t) : ===>%s<===\n", lit);
};

void operator"" _dump(const wchar_t *lit, size_t)
{
    printf("operator \"\" _dump(const wchar_t*, size_t): ===>%ls<===\n", lit);
};

void operator"" _dump(const char16_t *lit, size_t)
{
    printf("operator \"\" _dump(const char16_t*, size_t_): \n");
};

void operator"" _dump(const char32_t *lit, size_t)
{
    printf("operator \"\" _dump(const char32_t*, size_t):\n");
};

void operator"" _dump_raw(const char *lit)
{
    printf("operator \"\" _dump_raw(const char*) : ===>%s<===\n", lit);
};

template <char...>
void operator"" _dump_template();

int main()
{
    Distance d{402.0_km};
    std::cout << "Kilometers in d: " << d.GetKilometers() << std::endl;

    Distance d2{402.0_mi};
    std::cout << "Kilometers in d2: " << d2.GetKilometers() << std::endl;

    Distance d3 = 36.0_mi + 42.0_km;
    std::cout << "d3 value = " << d3.GetKilometers() << std::endl;

    std::string s;
    std::getline(std::cin, s);
    return 0;
}