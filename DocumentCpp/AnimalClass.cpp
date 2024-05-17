
#include <iostream>

class Animal
{
private:
    int food;
    int weight;

public:
    void SetAnimal(int food, int weight)
    {
        this->food = food;
        this->weight = weight;
    }

    void IncreaseFood(int inc)
    {
        this->food += inc;
        this->weight += (inc / 3);
    }

    void ViewStat()
    {
        std::cout << "이 동물의 Food : " << this->food << std::endl;
        std::cout << "이 동물의 Weight: " << this->weight << std::endl;
    }
};

int main()
{
    Animal animal;
    animal.SetAnimal(100, 50);
    animal.IncreaseFood(30);

    animal.ViewStat();

    return 0;
}