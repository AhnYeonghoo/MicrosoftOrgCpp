#include <iostream>

int main()
{
    enum class COLOR
    {
        RED,
        GREEN,
        BLUE
    };
    COLOR c = COLOR::RED;

    switch (c)
    {
    case COLOR::RED:
        std::printf("Color is RED. \n");
        break;
    case COLOR::GREEN:
        std::printf("Color is GREEN. \n");
        break;
    case COLOR::BLUE:
        std::printf("Color is BLUE.\n");
        break;
    default:
        std::printf("There is no correct color\n");
        break;
    }
    return EXIT_SUCCESS;
}