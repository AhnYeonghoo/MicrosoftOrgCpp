#include <iostream>

class Marine
{
private:
    static int totalMarineNum;
    const static int i = 0;

    int hp;
    int x, y;
    bool isDead;

    const int defaultDamage;

public:
    Marine();
    Marine(int x, int y);
    Marine(int x, int y, int defaultDamage);

    int Attack() const;
    Marine &BeAttacked(int damageEarn);
    void Move(int x, int y);
    void ShowStatus();

    static void ShowTotalMarine();
    ~Marine() { totalMarineNum--; }
};