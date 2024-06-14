#include <iostream>

typedef struct Animal
{
    char name[30];
    int age;

    int health;
    int food;
    int clean;
} Animal;

void CreateAniaml(Animal *animal)
{
    std::cout << "동물의 이름은? ";
    std::cin >> animal->name;
    std::cout << "동물의 나이? :";
    std::cin >> animal->age;

    animal->health = 100;
    animal->food = 100;
    animal->clean = 100;
}

void Play(Animal *animal)
{
    animal->health += 10;
    animal->food -= 20;
    animal->clean -= 30;
}

void OneDayPass(Animal *animal)
{
    animal->health += 10;
    animal->food -= 20;
    animal->clean -= 30;
}

void ShowStat(Animal *animal)
{
    std::cout << animal->name << "의 상태" << std::endl;
    std::cout << animal->health << std::endl;
    std::cout << animal->food << std::endl;
    std::cout << animal->clean << std::endl;
}

int main()
{
    Animal *list[10];
    int animalNum = 0;

    for (;;)
    {
        }
}