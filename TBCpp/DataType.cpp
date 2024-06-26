#include <iostream>

int main()
{

    using namespace std;

    bool bValue = true;

    cout << (bValue ? 1 : 0) << endl;

    char chValue = 'A';
    cout << chValue << endl;
    cout << (int)chValue << endl;
    chValue = 65;
    cout << chValue << endl;
    cout << (int)chValue << endl;
    cout << bValue << endl;

    float fValue = 3.141592f;
    double dValue = 3.141592;
    cout << fValue << endl;
    cout << dValue << endl;

        return 0;
}