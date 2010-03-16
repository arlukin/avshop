#ifndef AVSTRING_H
#define AVSTRING_H

#include <string>

#include <Wt/WString>

std::string avitos(int str_);
int avstoi(std::string str_);

namespace av
{
    std::string itos(int str_);
    int stoi(std::string str_);
    /*
    class String
    {
    public:
        String() {};
        String(const char *value) { _str = value; };
        String(const std::string& str_) {_str = str_; };
        String(const Wt::WString& str_) {_str = str_.toUTF8(); };        

        operator std::string() const { return _str; };
        operator std::string&()      { return _str; };
        operator Wt::WString() const {Wt::WString str(_str, Wt::UTF8);return str;};

        String& operator= (const char *value)           { _str = value; return *this;};
        String& operator= (const std::string& value)    { _str = value; return *this;};
        String& operator= (const String& value)         { _str = value.operator std::string(); return *this;};

        String& operator+= (const char *value)          { _str += *value; return *this;};
        String& operator+= (const std::string& value)   { _str += value; return *this;};
        String& operator+= (const String& value)        { _str = value.operator std::string(); return *this;};

        String operator+ (const char *value)           { String str=_str; str += value; return str;};
        String operator+ (const std::string& value)    { String str=_str; str += value; return str;};
        String operator+ (const String& value)         { String str=_str; str += value; return str;};

        bool operator ==( const char *value ) const { return (_str == value);};
        bool operator ==( const std::string& value ) const { return (_str == value);};
        bool operator ==( const String& value ) const { return (_str == value.operator std::string());};

        bool empty() const { return _str.empty(); };
    private:
        std::string _str;
    };

    String operator+ (const String &value1, const char *value2);

    String operator+ (const char *value2, const String &value1);
};

#include <soci.h>
namespace soci
{

details::use_type_ptr avuse(av::String& t, const char* const name);
details::use_type_ptr avuse(const av::String t, std::string const & name = std::string());

details::use_type_ptr avuse(Wt::WString& t, const char* const name);
details::use_type_ptr avuse(const Wt::WString t, std::string const & name = std::string());
*/
}

#endif // AVSTRING_H
