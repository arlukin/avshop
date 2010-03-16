#ifndef ACTIONGROUP_H
#define ACTIONGROUP_H

#include <string>
#include <set>

#include "Actions.h"
#include "User.h"

namespace av
{

class ActionGroup
{
public:
    ActionGroup(soci::session* session_);

    int actionGroupId() const;

    void setName(const std::string& name_);
    std::string name() const;

    void setAction(const action_t& actionId_, const int& permissions_ = ALL);

    void addUser(const int& userId_);
    void removeUser(const int& userId_);

    void clear();
    void load(const int& actionGroupId_);
    bool save();
    void destroy();

private:
    void _selectActionGroup(const int& actionGroupId_);
    void _selectActionGroupUser(const int& actionGroupId_);
    void _selectAction(const int& actionGroupId_);
    void _insert();
    void _insertActionGroupUser();
    void _deleteActionGroupUser();
    void _update();

private:
    int _actionGroupId;
    std::string _name;
    Actions _actions;
    std::set<int> _usersAcountIds;

    soci::session& _session;
};

}

#endif // ACTIONGROUP_H
