#include <memory>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <list>

#define SIZE 10          // C-style
constexpr int size = 10; // modern C++
class Widget
{
private:
    std::unique_ptr<int[]> data;

public:
    Widget(const int size) { data = std::make_unique_ptr<int[]>(size); }
    void DoSomething() {}
};

void FunctionUsingWidget()
{
    Widget w(1000000);
    w.DoSomething();
}

struct S
{
    std::string name;
    float num;
    S(std::string s, float f) : name(s), num(f) {}
};

int main()
{
    std::vector<std::string> apples;
    apples.push_back("Granny Smith");

    std::map<std::string, std::string> apple_color;

    apple_color["Granny Smith"] = "Green";

    auto comp = [](const Widget &w1, const Widget &w2)
    {
        return w1.Weight() < w2.Weight();
    }

    std::sort(v.begin(), v.end(), comp);

    auto i = lower_bound(v.begin(), v.end(), Widget{0}, comp);

    std::map<int, std::list<std::string>>::iterator i = m.begin();
    auto i = m.begin();

    std::vector<int> v{1, 2, 3};
    // C-style
    for (int i = 0; i < v.size(); i++)
    {
        std::cout << v[i];
    }
    for (auto &num : v)
    {
        std::cout << num;
    }

    // C-style initialization
    std::vector<S> v;
    S s1("Norah", 2.7);
    S s2("Frank", 3.5);
    S s3("Jeri", 85.9);

    v.push_back(s1);
    v.push_back(s2);
    v.push_back(s3);

    // Modern C++
    std::vector<S> v2{s1, s2, s3};
    
}