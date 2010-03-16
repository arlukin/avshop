#ifndef ACTIONS_H
#define ACTIONS_H

#include <map>

#include "general/ShopDb.h"

namespace av
{
typedef int action_t;

enum Permissions {NONE = 0, READ = 1, WRITE =2, DELETE = 4, ALL = 7};

class Actions
{
public:
    Actions(soci::session* session_);

    bool hasAccess(const action_t& actionId_) const;
    bool isReadable(const action_t& actionId_) const;
    bool isWriteable(const action_t& actionId_) const;
    bool isDeletable(const action_t& actionId_) const;    
    int getPermissions(const action_t& actionId_) const;

    void setAction(const action_t& actionId_, const int permissions_ = ALL);

    void clear();
    void load(const int& userId_);
    void save(const int& actionGroupId_);
    void destroy(const int& actionGroupId_);

private:
    std::string _selectQuery(const int& userId_);
    void _insert(const int& actionGroupId_);
    void _delete(const int& actionGroupId_);

private:
    std::map<const action_t, int> _actions;

    soci::session& _session;
};

}
#endif // ACTIONS_H
