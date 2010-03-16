#ifndef ORDERHEADER_H_INCLUDED
#define ORDERHEADER_H_INCLUDED

#include <vector>

#include "Contact.h"
#include "OrderRow.h"

class OrderHeader
{
public:
    typedef std::pair<std::string, OrderRow> t_OrderRow;

public:
    OrderHeader();
    OrderHeader(const int& OrderHeaderId_, const Contact& orginator_);

    void setOrderHeaderId(const int& orderHeaderId_);
    int orderHeaderId() const;

    Contact& orginator();
    Contact orginator() const;

    void addOrderRow(const OrderRow& orderRow_);    
    void addProduct(const Product & product_);
    std::map<std::string, OrderRow> & orderRows();
    size_t numOfOrderRows() const;

    void setShowIncVat(const bool incVat_);
    Money totalSalesPrice();

    void clear();

    void loadOrderRows(session& session_);
    int save(session& session_);
    void destroy(session& session_);

protected:

private:
    void insert(session& session_);
    void update(session& session_);

private:
    int _orderHeaderId;
    Contact _orginator;
    std::map<std::string, OrderRow> _orderRows;
    bool _incVat;
};


#endif // ORDERHEADER_H_INCLUDED


