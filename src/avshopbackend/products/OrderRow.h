#ifndef ORDERROW_H
#define ORDERROW_H

#include "Product.h"

class OrderRow
{
public:
    OrderRow();
    OrderRow(const int& orderRowId_, const int& orderHeaderId_, const Product& product_, const int& number_);
    virtual ~OrderRow();

    int orderRowId() { return _orderRowId; };
    int orderHeaderId() { return _orderHeaderId; };

    Product& product() { return _product; };
    Product product() const { return _product; };

    std::string cartName() const;

    void incNumber(int steps_ = 1) { _number += steps_; };
    void setNumber(int num_) { _number = num_; };
    int number() const { return _number; };
    Money totalSalesPrice() const { return product().salesPrice() * number(); };

    void clear();

    int save(session& session_)  { return 1; } ;
    int save(session& session_, const int& orderHeaderId_);
    void destroy(session& session_);
protected:
private:
    int _orderRowId;
    int _orderHeaderId;
    Product _product;
    int _number; // @todo: Alternative namequantity??
};

#endif // ORDERROW_H
