#include <iostream>

using namespace std;

class Account
{
public:
    Account(double InitialBalance)
    {
        balance = InitialBalance;
    }
    double GetBalance()
    {
        return balance;
    }

private:
    double balance;
};

double Account = 15.37; // hiding class name account

int main()
{
    class Account Checking(Account);
    cout << "Opening account with a balance of : " << Checking.GetBalance() << endl;
}
