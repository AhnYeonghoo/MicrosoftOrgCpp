#include <iostream>

namespace MyArray
{
    class Array;
    class Int;

    class Array
    {
        friend Int;

        const int dim;
        int *size;

        struct Address
        {
            int level;
            void *next;
        };

        Address *top;

    public:
        Array(int dim, int *arraySize) : dim(dim)
        {
            size = new int[dim];
            for (int i = 0; i < dim; i++)
            {
                size[i] = arraySize[i];
            }
            top = new Address;
            top->level = 0;
            InitializeAddress(top);
        }

        Array(const Array &arr) : dim(arr.dim)
        {
            size = new int[dim];
            for (int i = 0; i < dim; i++)
            {
                size[i] = arr.size[i];
            }
            top = new Address;
            top->level = 0;
            IntiializeAddress(top);
        }

        void InitializeAddress(Address *current)
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
                (static_cast<Address *>(current->next) + i)->next = current->level + 1;
                InitializeAddress(static_cast<Address *>(current->next) + i);
            }
        }

        void DeleteAddress(Address *current)
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

        Int operator[](const int index);

        ~Array()
        {
            DeleteAddress(top);
            delete[] size;
        }
    };

    class Int
    {

        void *data;
        int level;
        Array *array;

    public:
        Int(int size, int level = 0, void *data = NULL, Array *array = NULL)
            : level(level), data(data), array(array)
        {
            if (level < 1 || index >= array->size[level - 1])
            {
                data = NULL;
                return;
            }

            if (level == array->dim)
            {
                data = static_cast<void *>((static_cast<int *>(static_cast<Array::Address *>(data)->next) + index));
            }
            else
            {
                data = static_cast<void *>(static_cast<Array::Address *>(
                    static_cast < Array : Address * > (data)->next + index));
            }
        }
    };

    Int(const Int &i) : data(i.data), level(i.level), array(i.array) {}

    operator int()
    {
        if (data)
            return *static_cast<int *>(data);
        return 0;
    }

    Int &operator=(const int &a)
    {
        if (data)
        {
            *static_cast<int *>(data) = a;
            return *this;
        }
    }

    Int operator[](const int index)
    {
        if (!data)
        {
            return 0;
        }
        return Int(index, level + 1, data, array);
    };

    Int Array::operator[](const int index)
    {
        return Int(index, 1, static_cast<void *>(top), this);
    }
}