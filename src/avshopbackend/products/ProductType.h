#ifndef PRODUCTTYPE_H
#define PRODUCTTYPE_H

#include <string>
using std::string;

#include "general/DBTable.h"

class ProductType : public DBTable
{
public:
    ProductType();
    ProductType(const string name_, const int productTypeId_ = NULL);
    virtual ~ProductType();

    void setName(const string name_);
    string name() const;

    int productTypeId() const;

    void clear();

    void load(session& session_, int productTypeId_);
    int save(session& session_);
    void destroy(session& session_);

protected:

private:
    void insert(session& session_);
    void update(session& session_);
    int _getIdFromName(session& session_);

    string _name;

    int _productTypeId;
};

#endif // PRODUCTTYPE_H
