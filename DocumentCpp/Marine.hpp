#include <iostream>
#include <string.h>

class Marine
{
    int hp;
    int x, y;
    int damage;
    bool isDead;
    char *name;

public:
    Marine();
    Marine(int x, int y);
    Marine(int x, int y, const char *marineName);
    ~Marine();

    int Attack();
    void BeAttacked(int damageEarn);
    void Move(int x, int y);
    void ShowStatus();
};