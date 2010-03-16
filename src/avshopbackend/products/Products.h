#ifndef PRODUCT_LIST_H_INCLUDED
#define PRODUCT_LIST_H_INCLUDED

#include <vector>
#include <string>

#include <soci/soci.h>
using namespace soci;

#include "Product.h"

class Products : public std::vector<Product>
{
public:
    Products(soci::session& session_) : _session(session_) { };
    ~Products() { };

    void load(const int productTypeId_ = NULL);
    void save();
    void destroy();
private:
    std::string selectQuery();

private:
    soci::session& _session;

    int _productTypeId;
};

#endif // PRODUCT_LIST_H_INCLUDED
