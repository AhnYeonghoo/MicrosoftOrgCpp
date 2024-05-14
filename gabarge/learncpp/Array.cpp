#include <iostream>
#include <limits>

const int cMkts = 4, cFacts = 2;

double TransportCosts[][cMkts] = {
    {32.19, 47.29, 31.99, 19.11},
    {11.29, 22.49, 33.47, 17.29},
    {41.97, 22.09, 9.76, 22.55}};

const int cFactories = sizeof TransportCosts / sizeof(double[cMkts]);

double FindMinToMkt(int Mkt, double myTransportCosts[][cMkts], int mycFacts);
// Heap Allocate
using namespace std;

void DoSomething(size_t size)
{

    double *numbers = new double[size]{0};
    numbers[0] = 1;

    for (size_t i = 1; i < size; i++)
    {
        numbers[i] = numbers[i - 1] * 1.1;
    }

    for (size_t i = 0; i < size; i++)
    {
        std::cout << numbers[i] << " ";
    }

    double *p = numbers;

    for (size_t i = 0; i < size; i++)
    {
        std::cout << *p++ << " ";
    }

    p = numbers;

    while (p < (numbers + size))
    {
        std::cout << *p++ << " ";
    }

    delete[] numbers;
}

void Process(double *p, const size_t len)
{
    std::cout << "Process:\n";
    for (size_t i = 0; i < len; i++)
    {
    }
}
int main(int argc, char *argv[])
{
    double MinCost;

    if (argv[1] == 0)
    {
        cout << "You Must Specify the number of markets. " << endl;
        exit(0);
    }
    MinCost = FindMinToMkt(*argv[1] - '0', TransportCosts, cFacts);
    cout << "The Minimum cost to Market " << argv[1] << " is: " << MinCost << "\n";
    constexpr size_t size = 1000;
    double numbers[size]{0};

    numbers[0] = 1;
    for (size_t i = 1; i < size; i++)
    {
        numbers[i] = numbers[i - 1] * 1.1;
    }

    for (size_t i = 0; i < size; i++)
    {
        std::cout << numbers[i] << " ";
    }

    std::cout << std::endl;

    DoSomething(108);

    // 배열 초기화

    int a[10];

    for (int i = 0; i < 10; i++)
        a[i] = i + 1;

    int b[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
}

double FindMinToMkt(int Mkt, double myTransportCosts[][cMkts], int mycFacts)
{
    double MinCost = DBL_MAX;
    for (size_t i = 0; i < mycfacts; i++)
    {
        MinCost = (MinCost < TransportCosts[i][Mkt]) ? MinCost : TransportCosts[i][Mkt];
    }
    return MinCost;
}