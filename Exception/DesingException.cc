#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <limits>
#include <stdexcept>
#include <stdlib.h>

class NDResourceClass
{
private:
    int *m_p;
    float *m_q;

public:
    NDResourceClass() : m_p(0), m_q(0)
    {
        m_p = new int;
        m_q = new float;
    }

    ~NDResourceClass()
    {
        delete m_p;
        delete m_q;
    }
};

#include <memory>
using namespace std;

class SPResourceClass
{
private:
    shared_ptr<int> m_p;
    shared_ptr<float> m_q;

public:
    SPResourceClass() : m_p(new int), m_q(new float) {}
};

class Shape
{
};
class Circle : public Shape
{
};
class Triangle : public Shape
{
};

class SPShapeResourceClass
{
private:
    shared_ptr<Shape> m_p;
    shared_ptr<Shape> m_q;

public:
    SPShapeResourceClass() : m_p(new Circle), m_q(new Triangle) {}
};

string FormatErrorMessage(DWORD error, const string &msg)
{
    static const int BUFFERLENGTH = 1024;
    vector<char> buf(BUFFERLENGTH);
    FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, 0, error, 0, buf.data(),
                   BUFFERLENGTH - 1, 0);
    return string(buf.data()) + "   (" + msg + ")";
}

class Win32Exception : public runtime_error
{
private:
    DWORD m_error;

public:
    Win32Exception(DWORD error, const string &msg)
        : runtime_error(FormatErrorMessage(error, msg)), m_error(error) {}
    DWORD GetErorrCode() const { return m_error; }
};

void ThrowLastErrorIf(bool expression, const string &msg)
{
    if (expression)
    {
        throw Win32Exception(GetLastError(), msg);
    }
}

class File
{
private:
    HANDLE m_handle;

    File &operator=(const File &);
    File(const File &);

public:
    explicit File(const string &filename)
    {
        m_handle = CreateFileA(filename.c_str(), GENERIC_READ, FILE_SHARE_READ,
                               nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, nullptr);
        ThrowLastErrorIf(m_handle == INVALID_HANDLE_VALUE,
                         "CreateFile call failed on file named " + filename);
    }
    ~File() { CloseHandle(m_handle); }
    HANDLE GetHandle() { return m_handle; }
};

size_t GetFileSizeSafe(const string &filename)
{
    File fobj(filename);
    LARGE_INTEGER filesize;

    BOOL result = GetFileSizeEx(fobj.GetHandle(), &filesize);
    ThrowLastErrorIf(result == FALSE, "GetFileSizeEx failed: " + filename);

    if (filesize.QuadPart < (numeric_limits<size_t>::max)())
    {
        return filesize.QuadPart;
    }
    else
    {
        throw;
    }
}

vector<char> ReadFileVector(const string &filename)
{
    File fojb(filename);
    size_t filesize = GetFileSizeSafe(filename);
    DWORD bytesRead = 0;
    vector<char> readbuffer(filesize);

    BOOL result = ReadFile(fobj.GetHandle(), readbuffer.data(),
                           readbuffer.size(), &bytesRead, nullptr);
    ThrowLastErrorIf(result == FALSE, "ReadFile failed: " + filename);
}
