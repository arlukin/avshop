#include "AVString.h"

#include "OrderRow.h"

OrderRow::OrderRow()
    : _orderRowId(0), _orderHeaderId(0), _number(0)
{
    //ctor
}

OrderRow::OrderRow(const int& orderRowId_, const int& orderHeaderId_, const Product& product_, const int& number_)
    : _orderRowId(orderRowId_), _orderHeaderId(orderHeaderId_), _product(product_), _number(number_)
{

}

OrderRow::~OrderRow()
{
    //dtor
}

void OrderRow::clear()
{
    _orderRowId = 0;
    _orderHeaderId = 0;
    _product = new Product();
    _number = 0;
}

std::string OrderRow::cartName() const
{
    return avitos(number()) + " - " + product().name();
}

int OrderRow::save(session& session_, const int& orderHeaderId_)
{
    _orderHeaderId = orderHeaderId_;

    session_ << "INSERT INTO OrderRow (orderHeaderId, productId, number) "
                "VALUES (:orderHeaderId, :productId, :number)",
                use(orderHeaderId(), "orderHeaderId"),
                use(product().productId(), "productId"),
                use(number(), "number");

    session_ << "SELECT last_insert_id()", into(_orderRowId);

    return _orderRowId;
}

void OrderRow::destroy(session& session_)
{
    if (orderRowId())
    {
        session_ << "DELETE FROM OrderRow WHERE orderHeaderId = :id",
        use(orderRowId(), "id");
    }
    clear();
}
