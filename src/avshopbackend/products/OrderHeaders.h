#ifndef ORDERHEADER_LIST_H_INCLUDED
#define ORDERHEADER_LIST_H_INCLUDED

#include <vector>

#include <soci/soci.h>
using namespace soci;

#include "OrderHeader.h"

class OrderHeaders : public std::vector<OrderHeader>
{
public:
    OrderHeaders(soci::session& session_) : _session(session_) { };
    ~OrderHeaders() { };

    int count() const;
    void load();
    void save();
    void destroy();    

protected:

private:
    soci::session& _session;
};

#endif // ORDERHEADER_LIST_H_INCLUDED
