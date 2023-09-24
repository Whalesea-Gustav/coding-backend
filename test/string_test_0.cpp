#include <bits/stdc++.h>

class string {
public:
    string(const char* cstr = nullptr)
    {
        if (cstr) {
            m_data = new char[strlen(cstr) + 1];
            strcpy(m_data, cstr);
        } else {
            m_data = new char[1];
            *m_data = '\0';
        }
    }
    string(const string& str)
    {
        m_data = new char[strlen(str.m_data) + 1];
        strcpy(m_data, str.m_data);
    }
    ~string()
    {
        delete[] m_data;
    }
    string& operator = (const string& rhs)
    {
        if (this == &rhs)
            return *this;

        delete[] m_data;
        m_data = new char[strlen(rhs.m_data) + 1];
        strcpy(m_data, rhs.m_data);
        return *this;
    }

    friend std::ostream& operator << (std::ostream& os, const string& rhs)
    {
        return os << rhs.m_data;
    }
private:
    char* m_data;
};

int main()
{
   string a("test1");
   string b("test2");

   a = b;

   return 0;
}