#include <iostream>

using namespace std;

constexpr float exp(float x, int n)
{
	return n == 0 ? 1 : n % 2 == 0 ? exp(x * x, n / 2)
		: exp(x * x, (n - 1) / 2) * x;
}

constexpr float exp2(const float& x, const int& n)
{
	return n == 0 ? 1 : n % 2 == 0 ? exp2(x * x, n / 2) :
		exp2(x * x, (n - 1) / 2) * x;
}

template<typename T, int N>
constexpr int length(const T(&)[N])
{
	return N;
}

constexpr int fac(int n)
{
	return n == 1 ? 1 : n * fac(n - 1);
}

class Foo
{
public:
	constexpr explicit Foo(int i) : _i(i) {}
	constexpr int GetValue() const
	{
		return _i;
	}
private:
	int _i;
};