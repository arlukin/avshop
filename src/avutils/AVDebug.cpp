#include "AVDebug.h"

namespace AVDebug
{
    void debugEcho(const row& row_)
    {
        std::ostringstream doc;
        doc << "<row>" << std::endl;
        for(std::size_t i = 0; i != row_.size(); ++i)
        {
            const column_properties & props = row_.get_properties(i);

            doc << "   " << props.get_name();

            switch(props.get_data_type())
            {
            case dt_string:
                doc << "-string:" << row_.get<std::string>(i);
                break;
            case dt_double:
                doc << "-double:" << row_.get<double>(i);
                break;
            case dt_integer:
                doc << "-integer:" << row_.get<int>(i);
                break;
            case dt_unsigned_long:
                doc << "-ulong:" << row_.get<unsigned long>(i);
                break;
            case dt_long_long:
                doc << "-long long:" << row_.get<long long>(i);
                break;
            case dt_date:
                std::tm when = row_.get<std::tm>(i);
                doc << "-date:" << asctime(&when);
                break;
            }

            doc << std::endl;
        }
        doc << "</row>" << std::endl;

        std::cout << doc.str();
    }
}
