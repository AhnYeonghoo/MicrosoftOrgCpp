#include <iotream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <typeinfo>

using namespace std;

#ifdef _DEBUG
#define SAMPLE_D_FUNC_INFO cout << __FUNCTION__ << ":" << __LINE__ << ":"
<< __DATE__ << ' ' << __TIME__ << endl
#else
#define SAMPLE_D_FUNC_INFO
#endif

    template <typename Container>
    size_t FnPrintContainer(const Contrainer &c, const char *str = "")
{
    SAMPLE_D_FUNC_INFO;
    cout << str << ":";
    for (const auto &val : c)
    {
        cout << val << ' ';
    }
    cout << endl;
    return c.size();
}

class DataType
{
public:
    explicit DataType(int n = 0, const string &str = "") : nUserID_(n),
                                                           strUserName_(str) {}

    const string ToString() const
    {
        ostringstream oss;
        oss << nUserID_ << ',' << strUserName_;
        return oss.str();
    }

private:
    int nUserID_;
    string strUserName_;
};

std::ostream &operator<<(ostream &os, const DataType &data)
{
    os << data.ToString();
    return os;
}