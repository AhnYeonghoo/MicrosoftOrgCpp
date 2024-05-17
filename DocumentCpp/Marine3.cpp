#include "Marine3.hpp"

int Marine::totalMarineNum = 0;
void Marine::ShowTotalMarine()
{
    std::cout << "전체 마린수: " << totalMarineNum << std::endl;
}

Marine::Marine()
    : hp(50), x(0), y(0), defaultDamage(5), isDead(false)
{
    totalMarineNum++;
}

Marine::Marine(int x, int y)
    : x(x), y(y), hp(50), defaultDamage(5), isDead(false)
{
    totalMarineNum++;
}

Marine::Marine(int x, int y, int defaultDamage)
    : x(x), y(y), hp(50), defaultDamage(defaultDamage), isDead(false)
{
    totalMarineNum++;
}

void Marine::Move(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Marine::Attack() const { return defaultDamage; }
Marine &Marine::BeAttacked(int damageEarn)
{
    hp -= damageEarn;
    if (hp <= 0)
        isDead = true;
    return *this;
}

void Marine::ShowStatus()
{
    std::cout << "*** Marine ***" << std::endl;
    std::cout << " Location : ( " << x << " , " << y << " ) " << std::endl;
    std::cout << " HP: " << hp << std::endl;
    std::cout << " 현재 총 마린 수: " << totalMarineNum << std::endl;
}
