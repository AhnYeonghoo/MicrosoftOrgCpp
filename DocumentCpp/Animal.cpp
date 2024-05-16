#include <iostream>

typedef struct Animal
{
    char name[30];
    int age;
    int health;
    int food;
    int clean;
} Animal;

void CreateAnimal(char *name, int age, Animal *animal)
{
    animal->name = name;
    anima->age = age;
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
    animal->health -= 10;
    animal->food -= 30;
    animal->clean -= 20;
}

void ShowStat(Animal *animal)
{
    std::cout << animal->name << "의 상태" << std::endl;
    std::cout << "체력:  " << animal->health << std::endl;
    std::cout << "배부름 : " << animal->food << std::endl;
    std::cout << "청결:  " << animal->clean << std::endl;
}

int main()
{
    Animal *list[10];
    int animalNum = 0;

    for (;;)
    {
        std::cout << "1. 동물 추가하기" << std::endl;
        std::cout << "2. 놀기" << std::endl;
        std::cout << "3. 상태 보기" << std::endl;

        int input = 2;

        switch (input)
        {
            int playWith;
        case 1:
            list[animalNum] = new Animal;
            CreateAnimal(list[animalNum]);
            animalNum++;
            break;
        case 2:
            std::cout << "누구랑 놀게? : ";
            playWith = 2;
            if (playWith < animalNum)
                Play(list[animalNum]);
            break;
        }
    }
}
