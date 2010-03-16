#include <iostream>

#include "boost/lexical_cast.hpp"
using boost::lexical_cast;

#include "AVDebug.h"
using namespace AVDebug;

#include "Products.h"

void Products::load(const int productTypeId_)
{
    _productTypeId = productTypeId_;
    rowset<row> rs = (_session.prepare << selectQuery());

    for (rowset<row>::const_iterator it = rs.begin(); it != rs.end(); ++it)
    {
        row const& row = *it;

        push_back
        (
            Product
            (
                row.get<string>("name"),
                row.get<string>("description"),
                Contact
                (
                    row.get<string>("manufacturer_firstName"),
                    row.get<string>("manufacturer_lastName"),
                    row.get<string>("manufacturer_companyName"),
                    row.get<string>("Manufacturer_address"),
                    row.get<string>("Manufacturer_zip"),
                    row.get<string>("Manufacturer_city"),
                    row.get<string>("Manufacturer_phone"),
                    row.get<string>("manufacturer_email"),
                    row.get<string>("manufacturer_webUrl"),
                    row.get<int>("manufacturerId")
                ),
                Contact
                (
                    row.get<string>("supplier_firstName"),
                    row.get<string>("supplier_lastName"),
                    row.get<string>("supplier_companyName"),
                    row.get<string>("Supplier_address"),
                    row.get<string>("Supplier_zip"),
                    row.get<string>("Supplier_city"),
                    row.get<string>("Supplier_phone"),
                    row.get<string>("supplier_email"),
                    row.get<string>("supplier_webUrl"),
                    row.get<int>("product_supplierId")
                ),
                row.get<string>("externPartNo"),
                row.get<string>("internPartNo"),
                row.get<int>("minOrder"),
                row.get<int>("deliveryTime"),
                ProductType(row.get<string>("productName")),
                Money(row.get<double>("supplierAmount"), row.get<string>("supplierCurrency")),
                Money(row.get<double>("salesAmount"), row.get<string>("salesCurrency")),
                row.get<int>("productId")
            )
        );
    }
}

void Products::save()
{
    _session.begin();
    try
    {
        for (Products::iterator product = begin(); product != end(); ++product)
        {
            product->save(_session);
        }
        _session.commit();
    }
    catch (...)
    {
        _session.rollback();
    }
}

void Products::destroy()
{
    clear();
    _session << "DELETE FROM Product";
}

std::string Products::selectQuery()
{
    std::string query =
        "SELECT "
        "   Product.productId, "
        "   Product.name, "
        "   Product.description, "
        "   Product.manufacturerId, "
        "   Manufacturer.firstName AS manufacturer_firstName, "
        "   Manufacturer.lastName AS manufacturer_lastName, "
        "   Manufacturer.companyName AS manufacturer_companyName, "
        "   Manufacturer.address AS Manufacturer_address, "
        "   Manufacturer.zip AS Manufacturer_zip, "
        "   Manufacturer.city AS Manufacturer_city, "
        "   Manufacturer.phone AS Manufacturer_phone, "
        "   Manufacturer.email AS manufacturer_email, "
        "   Manufacturer.webUrl AS manufacturer_webUrl, "
        "   Product.supplierId AS product_supplierId, "
        "   Supplier.firstName AS supplier_firstName, "
        "   Supplier.lastName AS supplier_lastName, "
        "   Supplier.companyName AS supplier_companyName, "
        "   Supplier.address AS Supplier_address, "
        "   Supplier.zip AS Supplier_zip, "
        "   Supplier.city AS Supplier_city, "
        "   Supplier.phone AS Supplier_phone, "
        "   Supplier.email AS supplier_email, "
        "   Supplier.webUrl AS supplier_webUrl, "
        "   externPartNo, "
        "   internPartNo,"
        "   minOrder, "
        "   deliveryTime, "
        "   ProductType.name as productName, "
        "   supplierAmount, "
        "   supplierCurrency, "
        "   salesAmount, "
        "   salesCurrency "
        "FROM "
        "   Product "
        "   INNER JOIN Contact Manufacturer ON (Product.manufacturerId = Manufacturer.contactId)"
        "   INNER JOIN Contact Supplier ON (Product.supplierId = Supplier.contactId)"
        "   INNER JOIN ProductType ON (Product.productTypeId = ProductType.productTypeId)";

    if (_productTypeId > 0)
    {
        query +=
            "WHERE "
            "   ProductType.productTypeId = " + lexical_cast<std::string>(_productTypeId) + " " ;
    };

    query +=
        "ORDER BY "
        "	Product.productId";
    return query;
}
