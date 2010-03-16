#include <iostream>
using namespace std;

#include "ProductType.h"

ProductType::ProductType()
        : _productTypeId(0)
{}

ProductType::ProductType(const string name_, const int productTypeId_)
        :_name(name_), _productTypeId(productTypeId_)
{
}

ProductType::~ProductType()
{
}

void ProductType::setName(const string name_)
{
    _name = name_;
}

string ProductType::name() const
{
    return _name;
}

void ProductType::clear()
{
    _name = "";
    _productTypeId = 0;
}

void ProductType::load(session& session_, int productTypeId_)
{
    rowset<row> rs =
        (
            session_.prepare <<
            "SELECT "
            "	productTypeId, "
            "	name "
            "FROM "
            "	ProductType "
            "WHERE "
            "	productTypeId = (:id)",
            use(productTypeId_, "id")
        );

    rowset<row>::const_iterator it = rs.begin();
    if (it != rs.end())
    {
        row const& row = *it;

        _productTypeId = row.get<int>("productTypeId");
        _name = row.get<string>("name");

        assert((++it) == rs.end());
    }
}

int ProductType::save(session& session_)
{
    int id = _getIdFromName(session_);

    if (id > 0)
    {
        _productTypeId = id;
    }
    else if (productTypeId())
    {
        update(session_);
    }
    else
    {
        insert(session_);
    }

    return productTypeId();
}


void ProductType::destroy(session& session_)
{
    if (productTypeId())
    {
        session_ << "DELETE FROM ProductType WHERE productTypeId = :id",
        use(productTypeId(), "id");
    }
    clear();
}

void ProductType::insert(session& session_)
{
    session_ << "INSERT INTO ProductType (name) VALUES (:name)",
    use(name(), "name");

    session_ << "SELECT last_insert_id()", into(_productTypeId);
}

void ProductType::update(session& session_)
{
    if (productTypeId())
    {
        session_ <<
        "UPDATE ProductType "
        "SET "
        "	name = :name "
        "WHERE "
        "	productTypeId = :id",
        use(name(), "name"),
        use(productTypeId(), "id");
    }
}

int ProductType::_getIdFromName(session& session_)
{
    rowset<row> rs =
        (
            session_.prepare <<
            "SELECT "
            "   productTypeId "
            "FROM "
            "	ProductType "
            "WHERE "
            "   name = :name",
            use(name(), "name")
        );

    int productTypeId = 0;
    rowset<row>::const_iterator it = rs.begin();
    if (it != rs.end())
    {
        row const& row = *it;

        productTypeId = row.get<int>("productTypeId");

        ++it;
        assert(it == rs.end());
    }
    return productTypeId;
}
