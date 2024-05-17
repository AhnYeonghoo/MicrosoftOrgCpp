#include <string.h>
#include <iostream>

class PhotonCannon
{
private:
    int hp, shield;
    int x, y, damage;
    char *name;

public:
    PhotonCannon(int x, int y);
    PhotonCannon(int x, int y, const char *cannonName);
    PhotonCannon(const PhotonCannon &pc);
    ~PhotonCannon();

    void ShowStatus();
};