#include <iostream>
#include "OrderHeaders.h"


int OrderHeaders::count() const
{
    int count;
    _session << "SELECT COUNT(*) FROM OrderHeader", into(count);
    return count;
}

void OrderHeaders::load()
{
    rowset<row> rs = (_session.prepare <<
        "SELECT "
        "   OrderHeader.orderHeaderId, "
        "   OrderHeader.orginatorID, "
        "   orginator.firstName, "
        "   orginator.lastName, "
        "   orginator.companyName, "        
        "   orginator.address, "
        "   orginator.zip, "
        "   orginator.city, "
        "   orginator.phone, "
        "   orginator.email, "
        "   orginator.webUrl "
        "FROM "
        "   OrderHeader "
        "   INNER JOIN Contact orginator ON (OrderHeader.orginatorID = orginator.contactId) "
    );

    for (rowset<row>::const_iterator it = rs.begin(); it != rs.end(); ++it)
    {
        row const& row = *it;

        push_back(OrderHeader
        (
            row.get<int>(0),
            Contact
            (
                row.get<string>(2),
                row.get<string>(3),
                row.get<string>(4),
                row.get<string>(5),
                row.get<string>(6),
                row.get<string>(7),
                row.get<string>(8),
                row.get<string>(9),
                row.get<string>(10),
                row.get<int>(1)
            )
        ));
        back().loadOrderRows(_session);
    }
}

void OrderHeaders::save()
{
    _session.begin();
    try
    {
        for(OrderHeaders::iterator OrderHeader = begin(); OrderHeader != end(); ++OrderHeader)
        {
            OrderHeader->save(_session);
        }
        _session.commit();
    }
    catch(...)
    {
        _session.rollback();
    }
}

void OrderHeaders::destroy()
{
    _session << "DELETE FROM OrderHeader";
    clear();
}
