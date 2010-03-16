#ifndef DBTABLE_H
#define DBTABLE_H

#include <soci.h>
using namespace soci;

class DBTable
{
public:

    void clear();

    static void createDatabase(session& session_) {};
    virtual int save(session& session_) = 0;
    virtual void destroy(session& session_) = 0;

protected:
private:
    virtual void insert(session& session_) = 0;
    virtual void update(session& session_) = 0;
};

#endif // DBTABLE_H

