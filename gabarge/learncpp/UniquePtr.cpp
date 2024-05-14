#include <iostream>
#include <cassert>
#include <fstream>
#include <cstdio>
#include <locale>
#include <memory>
#include <stdexcept>

struct B
{
    virtual ~B() = default;
    virtual void bar() { std::cout << "B::bar\n"; }
};

struct D : B
{
    D() { std::cout << "D::D\n"; }
    ~D() { std::cout << "D::~D\n"; }
    void bar() override { std::cout << "D::bar\n"; }
};

std::unique_ptr<D> pass_through(std::unique_ptr<D> p)
{
    p->bar();
    return p;
}

void close_file(std::FILE *fp)
{
    std::fclose(fp);
}

struct List
{
    struct Node
    {
        int data;
        std::unique_ptr<Node> next;
    };

    std::unique_ptr<Node> head;
    ~List()
    {
        while (head)
        {
            auto next = std::move(head->next);
            head = std::move(next);
        }
    }

    void push(int data)
    {
        head = std::unique_ptr<Node>(new Node{data, std::move(head)});
    }
};

int main()
{
    std::cout << "1) Unique ownership semantics demo\n";
    {
        std::unique_ptr<D> p = std::make_unique<D>();
        std::unique_ptr<D> q = pass_through(std::move(p));
        assert(!p);
    }

    std::cout << "\n"
                 "2) Runtime polymorphism demo\n";
    {
        std::unique_ptr<B> p = std::make_unique<D>();
        p->bar();
    }

    std::cout << "\n"
                 "3) Custom deleter demo\n";
    std::ofstream("demo.txt") << 'x';
    {
        using unique_file_t = std::unique_ptr<std::FILE, decltype(&close_file)>;
        unique_file_t fp(std::fopen("demo.txt", "r"), &close_file);
        if (fp)
            std::cout << char(std::fgetc(fp.get())) << '\n';
    }
}