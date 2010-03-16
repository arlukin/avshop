#ifndef PRODUCTTYPES_H
#define PRODUCTTYPES_H

#include <vector>
#include <string>

#include <soci/soci.h>
using namespace soci;

#include "ProductType.h"

class ProductTypes : public std::vector<ProductType>
{
public:
    ProductTypes(soci::session& session_);

    enum Filter {HAS_PRODUCTS = 1};

    int count();
    void addFilter(Filter filter_);
    void load();
    void save();
    void destroy();
private:
    std::string selectQuery();

private:
    soci::session& _session;

    Filter _filter;
};

#endif // PRODUCTTYPES_H
