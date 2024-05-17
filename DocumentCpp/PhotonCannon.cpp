#include "PhotonCannon.hpp"

PhotonCannon::PhotonCannon(const PhotonCannon &pc)
{
    std::cout << "복사 생성자 호출! " << std::endl;
    this->hp = pc.hp;
    shield = pc.shield;
    x = pc.x;
    y = pc.y;
    damage = pc.damage;

    name = new char[strlen(pc.name) + 1];
    strcpy(name, pc.name);
}

PhotonCannon::PhotonCannon(int x, int y)
{
    std::cout << "생성자 호출!" << std::endl;
    hp = shield = 100;
    this->x = x;
    this->y = y;
    damage = 20;
    name = NULL;
}

void PhotonCannon::ShowStatus()
{
    std::cout << "Photon Cannon " << name << std::endl;
    std::cout << " Location : ( " << x << " , " << y << " ) "
              << std::endl;
    std::cout << " HP : " << hp << std::endl;
}

PhotonCannon::PhotonCannon(int x, int y, const char *cannonName)
{
    hp = shield = 100;
    this->x = x;
    this->y = y;
    damage = 20;
    name = new char[strlen(cannonName) + 1];
    strcpy(name, cannonName);
}

PhotonCannon::~PhotonCannon()
{
    if (name)
        delete[] name;
}