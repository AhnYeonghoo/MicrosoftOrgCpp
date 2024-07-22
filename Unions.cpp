#include <iostream>

union UserType
{
    int nValue;
    double dValue;
};

struct S
{
    unsigned int b : 2;
};

int main()
{
    UserType user;

    printf("%d\n", sizeof(user));

    user.nValue = 10;
    printf("%d\n", sizeof(user));
    printf("%p \n", &user.nValue);
    printf("%d\n", user.nValue);

    user.dValue = 12.34;
    printf("%d\n", sizeof(user.dValue));
    printf("%p\n", &user.dValue);
    printf("%lf\n", user.dValue);

    printf("%d, %lf\n", user.nValue, user.dValue);

    S s = {2};
    ++s.b;
    printf("%d\n", s.b);
    ++s.b;
    printf("%d\n", s.b);
    return EXIT_SUCCESS;
}