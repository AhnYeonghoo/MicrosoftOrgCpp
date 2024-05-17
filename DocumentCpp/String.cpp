#include "String.hpp"

MyString::MyString(char c)
{
    stringContent = new char[1];
    stringContent[0] = c;
    memoryCapacity = 1;
    stringLength = 1;
}

MyString::MyString(const char *str)
{
    stringLength = strlen(str);
    memoryCapacity = stringLength;
    stringContent = new char[stringLength];

    for (int i = 0; i != stringLength; i++)
    {
        stringContent[i] = str[i];
    }
}

MyString::MyString(const MyString &str)
{
    stringLength = str.stringLength;
    memoryCapacity = str.stringLength;
    stringContent = new char[stringLength];
    for (int i = 0; i != stringLength; i++)
    {
        stringContent[i] = str.stringContent[i];
    }
}

MyString::~MyString() { delete[] stringContent; }
int MyString::Length() const { return stringLength; }

void Mystring::Print() const
{
    for (int i = 0; i != stringLength; i++)
    {
        std::cout << stringContent[i];
    }
}

void MyString::Println() const
{
    for (int i = 0; i != stringLengt; i++)
    {
        std::cout << stringContent[i];
    }

    std::cout << std::endl;
}

MyString &MyString::Assign(const MyString &str)
{
    if (str.stringLength > stringLength)
    {
        delete[] stringContent;
        stringContent = new char[str.stringLength];
        memoryCapacity = str.stringLength;
    }
    for (int i = 0; i != str.stringLength; i++)
    {
        stringContent = new char[str.stringLength];
    }

    stringLength = str.stringLength;
    return *this;
}

MyString &MyString::Assign(const char *str)
{
    int strLength = strlen(str);
    if (strLength > stringLength)
    {
        delete[] stringContent;
        stringContent = new char[strLength];
        memoryCapacity = strLength;
    }
    for (int i = 0; i != strLength; i++)
    {
        stringContent[i] = str[i];
    }
    stringLength = strLength;

    return *this;
}

int MyString::Capacity() const { return memoryCapacity; }

void MyString::Reserve(int size)
{
    if (size > memoryCapacity)
    {
        char *prevStringContent = stringContent;

        stringContent = new char[size];
        memoryCapacity = size;
        for (int i = 0; i != stringLength; i++)
        {
            stringContent[i] = prevStringContent[i];
        }
        delete[] prevStringContent;
    }
}

MyString &MyString::Insert(int loc, const MyString &str)
{
    if (loc < 0 || loc > stringLength)
        return *this;
    if (stringLength + str.stringLength > memoryCapacity)
    {
        memoryCapacity = stringLength + str.stringLength;
        char *prevStringContent = stringContent;
        stringContent = new char[memoryCapacity];

        int i;
        for (i = 0; i < loc; i++)
        {
            stringContent[i] = prevStringContent[i];
        }

        for (int j = 0; j != str.stringLength; j++)
        {
            stringContent[i + j] = str.stringContent[j];
        }

        for (; i < stringLength; i++)
        {
            stringContent[str.stringLength + i] = prevStringContent[i];
        }

        delete[] prevStringContent;

        stringLength = stringLength + str.stringLength;
        return *this;
    }

    for (int i = stringLength - 1; i > loc; i--)
    {
        stringContent[i + str.stringLength] = stringContent[i];
    }

    for (int i = 0; i < str.stringLength; i++)
    {
        stringContent[i + loc] = str.stringContent[i];
    }

    stringLength = stringLength + str.stringLength;
    return *this;
}

char MyString::at(int i) const
{
    if (i >= stringLength || i < 0)
        return 0;
    else
        return stringContent[i];
}

MyString &MyString::Erase(int loc, int num)
{
    if (num < 0 || loc < 0 || loc > stringLength)
        return *this;

    for (int i = loc + num; i < stringLength; i++)
    {
        stringContent[i - num] = stringContent[i];
    }

    stringLength -= num;
    return *this;
}

int MyString::Find(int findFrom, MyString &str) const
{
    int i, j;
    if (str.stringLength == 0)
        return -1;
    for (i = findFrom; i <= stringLength - str.stringLength; i++)
    {
        for (j = 0; j < str.stringLength; j++)
        {
            if (stringContent[i + j] != str.stringContent[j])
                break;
        }
        if (j == str.stringLength)
            return i;
    }
    return -1;
}

int MyString::Find(int findFrom, const char *str) const
{
    MyString temp(str);
    return Find(findFrom, temp);
}

int MyString::Find(int findFrom, char c) const
{
    MyString temp(c);
    return Find(findFrom, temp);
}

int MyString::Compare(const MyString &str) const
{
    for (int i = 0; i < std::min(string_length, str.stringLength); i++)
    {
        if (stringContent[i] > str.stringContent[i])
            return 1;
        else if (stringContent[i] < str.stringContent[i])
            return -1;
    }

    if (stringLength == str.stringLength)
        return 0;
    else if (stringLength > str.stringLength)
        return 1;

    return -1;
}

bool MyString::operator==(MyString &str)
{
    return !Compare(str);
}