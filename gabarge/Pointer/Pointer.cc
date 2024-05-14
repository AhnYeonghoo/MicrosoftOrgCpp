#include <iostream>
#include <string>

class MyClass
{
public:
    int num;
    std::string name;
    void Print() { std::cout << name << ":" << num << std::endl; }
};

void func_A(MyClass *mc)
{
    mc->num = 3;
}

void func_B(MyClass mc)
{
    mc.num = 21;
    std::cout << "Local copy of mc: ";
    mc.Print();
}

void func(int arr[], int length)
{
    size_t test = sizeof(arr);
    for (int i = 0; i < length; i++)
    {
        std::cout << arr[i] << " ";
    }
}

int main()
{
    MyClass *pmc = new MyClass{108, "Nick"};
    std::cout << pmc << std::endl;

    MyClass mc = *pmc;

    MyClass *pcopy = &mc;

    pmc->Print();

    MyClass *pmc2 = pmc;

    pmc2->name = "Erika";
    pmc->Print();
    pmc2->Print();

    func_A(pmc);
    pmc->Print();

    delete (pmc);

    int i[5]{1, 2, 3, 4, 5};
    int j = sizeof(i) / sizeof(i[0]);
    func(i, j);
    return 0;
}