#include "Array.hpp"

void Array::InitializeAddress(Address *current)
{
    if (!current)
    {
        return;
    }
    if (current->level == dim - 1)
    {
        current->next = new int[size[current->level]];
        return;
    }

    current->next = new Address[size[current->level]];

    for (int i = 0; i != size[current->level]; i++)
    {
        (static_cast<Address *>(current->next) + i)->level = current->level + 1;
        InitializeAddress(static_cast<Address *>(current->next) + i);
    }
}

void Array::DeleteAddress(Address *current)
{
    if (!current)
    {
        return;
    }

    for (int i = 0; current->level < dim - 1 && i < size[current->level]; i++)
    {
        DeleteAddress(static_cast<Address *>(current->next) + i);
    }
    delete[] current->next;
}