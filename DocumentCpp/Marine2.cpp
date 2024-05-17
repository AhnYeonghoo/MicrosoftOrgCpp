#include "Marine2.hpp"

Marine::Marine()
    : hp(50), x(0), y(0), damage(5), isDead(false), defaultDamage(5)
{
    totalMarineNum++;
}

Marine::Marine(int x, int y)
    : x(x), y(y), hp(50), damage(5), isDead(false), defaultDamage(5)
{
    totalMarineNum++;
}

void Marine::Move(int x, int y)
{
    this->x = x;
    this->y = y;
}

Marine::~Marine()
{
    totalMarineNum--;
}

int Marine::Attack() { return defaultDamage; }

void Marine::BeAttacked(int damageEarn)
{
    ho -= damageEarn;
    if (hp <= 0)
        isDead = true;
}

void Marine::ShowStatus()
{
    std::cout << " *** Marine *** " << std::endl;
    std::cout << " Location : ( " << x << " , " << y << " ) "
              << std::endl;
    std::cout << " HP : " << hp << std::endl;
    std::cout << " 현재 총 마린수 : " << totalMarineNum << std::endl;
}