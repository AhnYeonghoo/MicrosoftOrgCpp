#include <iostream>
#include <sstream>

class UserType;

class UserType
{
public:
    using value_type = char;
    using iterator = value_type *;
    using const_iterator = const value_type *;

    UserType() = default;
    virtual ~UserType() = default;
    UserType(const UserType &user);
    UserType &operator=(const UserType &user);
    UserType(UserType &&user);
    UserType &operator=(UserType &&user);

    struct DataType
    {
        DataType(int year, int month, int day)
            : nYear(year), nMonth(month), nDay(day) {}

        int nYear;
        int nMonth;
        int nDay;
        const std::string to_string() const
        {
            std::ostringstream oss;
            oss << nYear << '.' << nMonth << '.' << nDay;
            return oss.str();
        }
    };

    void setName(std::string_view str);
    void setBirth(const DataType &date);

    const std::string &getName() const { return strName_; }
    const DataType &getBirth() const { return Birth_; }

private:
    std::string strName_;
    DataType Birth_ = DataType{1900, 01, 01};
};

int main()
{
    UserType user;
    std::cout << user.getName() << '\t' << user.getBirth().to_string() << std::endl;
    user.setName("David");
    user.setBirth(UserType::DataType(1999, 12, 31));
    std::cout << user.getName() << '\t' << user.getBirth().to_string() << std::endl;
    return EXIT_SUCCESS;
}