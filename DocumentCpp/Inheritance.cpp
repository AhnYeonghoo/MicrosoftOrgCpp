#include <iostream>

using namespace std;

class Document
{
public:
    char *Name;
    void PrintNameOf();
};

void Document::PrintNameOf()
{
    cout << Name << endl;
};

class Book : public Document
{
public:
    Book(char *name, long pagecount);

private:
    long PageCount;
};

Book::Book(char *name, long pagecount)
{
    Name = new char[strlen(name) + 1];
    strcpy_s(Name, strlen(Name), name);
    PageCount = pagecount;
};