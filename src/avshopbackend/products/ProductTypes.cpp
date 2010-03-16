#include <iostream>
#include <string>

#include "AVDebug.h"
using namespace AVDebug;

#include "ProductTypes.h"

ProductTypes::ProductTypes(soci::session& session_)
    : _session(session_)
{
}

int ProductTypes::count()
{
        int count;
        _session << "SELECT COUNT(*) FROM ProductType", into(count);
        return count;
}

void ProductTypes::addFilter(Filter filter_)
{
    _filter = filter_;
}

void ProductTypes::load()
{
    clear();
    rowset<row> rs =(_session.prepare << selectQuery());

    for (rowset<row>::const_iterator it = rs.begin(); it != rs.end(); ++it)
    {
        row const& row = *it;

        push_back
        (
            ProductType
            (
                row.get<string>("name"),
                row.get<int>("productTypeId")
            )
        );
    }
}

void ProductTypes::save()
{
    _session.begin();
    try
    {
        for (ProductTypes::iterator productType = begin(); productType != end(); ++productType)
        {
            productType->save(_session);
        }
        _session.commit();
    }
    catch (...)
    {
        _session.rollback();
    }
}

void ProductTypes::destroy()
{
    clear();
    _session << "DELETE FROM ProductType";
}

std::string ProductTypes::selectQuery()
{
    std::string query =
        "SELECT "
        "   ProductType.productTypeId, "
        "   ProductType.name "
        "FROM "
        "   ProductType ";

    if (_filter == HAS_PRODUCTS)
    {
        query +=
            "   INNER JOIN Product USING (productTypeId) "
            "WHERE "
            "   Product.productTypeId IS NOT NULL "
            "GROUP BY "
            "   ProductType.productTypeId ";
    }

    query +=
        "ORDER BY "
        "   ProductType.productTypeId";

    return query;
}
