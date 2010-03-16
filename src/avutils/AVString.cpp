#include "boost/lexical_cast.hpp"

#include "AVString.h"

std::string avitos(int str_)
{
    return boost::lexical_cast<std::string>(str_);
}

int avstoi(std::string str_)
{
    return boost::lexical_cast<int>(str_);
}

namespace av
{

    std::string itos(int str_)
    {
        return boost::lexical_cast<std::string>(str_);
    }

    int stoi(std::string str_)
    {
        return boost::lexical_cast<int>(str_);
    }

/*
    String operator+ (const String &value1, const char *value2)
        { String str = value1; str += value2; return str;};

    String operator+ (const char *value2, const String &value1)
        { String str = value1; str += value2; return str;};
};

namespace soci
{

details::use_type_ptr avuse(av::String& t, const char* const name)
{
    std::string str = t;
    use(str, name);
}

details::use_type_ptr avuse(const av::String t, std::string const & name )
{
    std::string str = t;
    use(str, name);
}

details::use_type_ptr avuse(Wt::WString& t, const char* const name)
{
    use(t.toUTF8(), name);
}

details::use_type_ptr avuse(const Wt::WString t, std::string const & name )
{
    use(t.toUTF8(), name);
}
*/
}


