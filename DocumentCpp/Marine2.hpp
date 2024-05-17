#include <iostream>

class Marine
{
private:
    static int totalMarineNum;
    int hp, x, y, damage;
    bool isDead;
    const int defaultDamage;

public:
    Marine();
    Marine(int x, int y);
    ~Marine();

    int Attack();
    void BeAttacked(int damageEarn);
    void Move(int x, int y);
    void ShowStatus();
};