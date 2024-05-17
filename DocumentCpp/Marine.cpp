#include "Marine.hpp"

Marine::Marine()
{
    hp = 50;
    x = y = 0;
    damage = 5;
    isDead = false;
    name = NULL;
}

Marine::Marine(int x, int y, const char *marineName)
{
    name = new char[strlen(marineName) + 1];
    strcpy(name, marineName);

    this->x = x;
    this->y = y;
    ho = 50;
    damage = 5;
    isDead = false;
}

Marine::Marine(int x, int y)
{
    this->x = x;
    this->y = y;
    hp = 50;
    damage = 5;
    isDead = false;
    name = NULL;
}

void Marine::Move(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Marine::Attack()
{
    return damage;
}

void Marine::BeAttacked(int damageEarn)
{
    ho -= damageEarn;
    if (hp <= 0)
        isDead = true;
}

void Marine::ShowStatus()
{
    std::cout << "***Marine: " << name << " ***" << std::endl;
    std::cout << " Location : ( " << x << " , " << y << " ) "
              << std::endl;
    std::cout << " HP : " << hp << std::endl;
}

Marine::~Marine()
{
    std::cout << name << " 의 소멸자 호출! " << std::endl;
    if (name != NULL)
    {
        delete[] name;
    }
}