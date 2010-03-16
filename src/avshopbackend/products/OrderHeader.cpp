#include "OrderHeader.h"
#include <iostream>
using namespace std;

#include <boost/foreach.hpp>

#include "AVDebug.h"
using namespace AVDebug;

OrderHeader::OrderHeader()
    : _orderHeaderId(0)
{

}

OrderHeader::OrderHeader(const int& orderHeaderId_, const Contact& orginator_)
    : _orderHeaderId(orderHeaderId_), _orginator(orginator_)
{

}

void OrderHeader::setOrderHeaderId(const int& orderHeaderId_)
{
    _orderHeaderId = orderHeaderId_;
}

int OrderHeader::orderHeaderId() const
{
    return _orderHeaderId;
}

Contact& OrderHeader::orginator()
{
    return _orginator;
}

Contact OrderHeader::orginator() const
{
    return _orginator;
}

void OrderHeader::addOrderRow(const OrderRow& orderRow_)
{    
    std::pair<std::map<std::string, OrderRow>::iterator, bool> ret;

    ret = _orderRows.insert
    (
        std::pair<std::string, OrderRow>(orderRow_.product().name(), orderRow_)
    );

    if (ret.second == false)
    {        
        ret.first->second.incNumber(orderRow_.number());
    }
};

void OrderHeader::addProduct(const Product & product_)
{
    addOrderRow(OrderRow(NULL, NULL, product_, 1));
}

std::map<std::string, OrderRow> & OrderHeader::orderRows()
{
    return _orderRows;
};

size_t OrderHeader::numOfOrderRows() const
{
    return _orderRows.size();
};

void OrderHeader::setShowIncVat(const bool incVat_)
{
    _incVat = incVat_;
}

Money OrderHeader::totalSalesPrice()
{
    Money * sum = new Money();    

    BOOST_FOREACH(t_OrderRow orderRow, orderRows())
    {
        *sum += orderRow.second.totalSalesPrice();
    }

    return *sum;    
}

void OrderHeader::clear()
{
    _orderHeaderId = 0;
    _orginator.clear();;
    _orderRows.clear();
    _incVat = false;
}

void OrderHeader::loadOrderRows(session& session_)
{
    rowset<row> rs =
        (
            session_.prepare <<
            "SELECT "
            "   OrderRow.orderRowId, "
            "   OrderRow.orderHeaderId, "
            "   OrderRow.number, "
            "   Product.productId, "
            "   Product.name, "
            "   Product.description, "
            "   Product.manufacturerId, "
            "   Manufacturer.firstName AS Manufacturer_firstName, "
            "   Manufacturer.lastName AS Manufacturer_lastName, "
            "   Manufacturer.companyName AS Manufacturer_companyName, "            
            "   Manufacturer.address AS Manufacturer_address, "
            "   Manufacturer.zip AS Manufacturer_zip, "
            "   Manufacturer.city AS Manufacturer_city, "
            "   Manufacturer.phone AS Manufacturer_phone, "
            "   Manufacturer.email AS Manufacturer_email, "
            "   Manufacturer.webUrl AS Manufacturer_webUrl, "
            "   Product.supplierId, "
            "   Supplier.firstName AS Supplier_firstName, "
            "   Supplier.lastName AS Supplier_lastName, "
            "   Supplier.companyName AS Supplier_companyName, "
            "   Supplier.address AS Supplier_address, "
            "   Supplier.zip AS Supplier_zip, "
            "   Supplier.city AS Supplier_city, "
            "   Supplier.phone AS Supplier_phone, "
            "   Supplier.email AS Supplier_email, "
            "   Supplier.webUrl AS Supplier_webUrl, "
            "   externPartNo, "
            "   internPartNo,"
            "   minOrder, "
            "   deliveryTime, "
            "   ProductType.name AS ProductTypeName, "
            "   supplierAmount, "
            "   supplierCurrency, "
            "   salesAmount, "
            "   salesCurrency "
            "FROM "
            "   OrderRow "
            "   INNER JOIN Product ON(OrderRow.productId = Product.productId) "
            "   INNER JOIN Contact Manufacturer ON (Product.manufacturerId = Manufacturer.contactId) "
            "   INNER JOIN Contact Supplier ON (Product.supplierId = Supplier.contactId) "
            "   INNER JOIN ProductType ON (Product.productTypeId = ProductType.productTypeId) "
            "WHERE "
            "   OrderRow.orderHeaderId = :orderHeaderId",
            use(orderHeaderId(), "orderHeaderId")
        );

    for (rowset<row>::const_iterator it = rs.begin(); it != rs.end(); ++it)
    {
        row const& row = *it;

        Contact manufactor
        (
            row.get<string>("Manufacturer_firstName"),
            row.get<string>("Manufacturer_lastName"),
            row.get<string>("Manufacturer_companyName"),            
            row.get<string>("Manufacturer_address"),
            row.get<string>("Manufacturer_zip"),
            row.get<string>("Manufacturer_city"),
            row.get<string>("Manufacturer_phone"),
            row.get<string>("Manufacturer_email"),
            row.get<string>("Manufacturer_webUrl"),
            row.get<int>("manufacturerId")
        );

        Contact supplier
        (
            row.get<string>("Supplier_firstName"),
            row.get<string>("Supplier_lastName"),
            row.get<string>("Supplier_companyName"),
            row.get<string>("Supplier_address"),
            row.get<string>("Supplier_zip"),
            row.get<string>("Supplier_city"),
            row.get<string>("Supplier_phone"),
            row.get<string>("Supplier_email"),
            row.get<string>("Supplier_webUrl"),
            row.get<int>("supplierId")
        );

        ProductType productType(row.get<string>("ProductTypeName"));

        Money supplierPrice(row.get<double>("supplierAmount"), row.get<string>("supplierCurrency"));
        Money salesPrice(row.get<double>("salesAmount"), row.get<string>("salesCurrency"));

        Product product
        (
            row.get<string>("name"),
            row.get<string>("description"),
            manufactor,
            supplier,
            row.get<string>("externPartNo"),
            row.get<string>("internPartNo"),
            row.get<int>("minOrder"),
            row.get<int>("deliveryTime"),
            productType,
            supplierPrice,
            salesPrice,
            row.get<int>("productId")
        );

        OrderRow orderRow
        (
            row.get<int>("orderRowId"),
            row.get<int>("orderHeaderId"),
            product,
            row.get<int>("number")
        );

        addOrderRow(orderRow);
    }
}

int OrderHeader::save(session& session_)
{
    if (orderHeaderId())
    {
        update(session_);
    }
    else
    {
        insert(session_);
    }

    BOOST_FOREACH(t_OrderRow orderRow, _orderRows)
    {
        orderRow.second.save(session_, _orderHeaderId);
    }

    return orderHeaderId();
}

void OrderHeader::destroy(session& session_)
{
    BOOST_FOREACH(t_OrderRow orderRow, _orderRows)
    {
        orderRow.second.destroy(session_);
    }

    if (orderHeaderId())
    {
        session_ << "DELETE FROM OrderHeader WHERE orderHeaderId = :id",
        use(orderHeaderId(), "id");
    }
    clear();
}

void OrderHeader::insert(session& session_)
{
    session_ << "INSERT INTO OrderHeader (orginatorId) "
    "VALUES (:orginatorId)",
    use(orginator().save(session_), "orginatorId");

    session_ << "SELECT last_insert_id()", into(_orderHeaderId);
}

void OrderHeader::update(session& session_)
{
    orginator().save(session_);
}
