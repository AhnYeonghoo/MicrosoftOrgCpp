#include <iostream>
#include <algorithm>

using namespace std;

#define MYNUMBER 9
#define MAX(a, b) ((a > b) ? a : b)
#define LIKE_APPLE

int main()
{

    cout << MYNUMBER << endl;
    cout << std::max(3, 4) << endl;
    cout << MAX(3, 4) << endl;

#ifdef LIKE_APPLE
    cout << "APple" << endl;
#endif

#ifndef LIKE_APPLE
    cout << "Orange" << endl;
#endif

    return 0;
}