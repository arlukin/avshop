#include "boost/foreach.hpp"
#include "boost/lexical_cast.hpp"

#include "Actions.h"

namespace av
{

Actions::Actions(soci::session* session_)
    : _session(*session_)
{
    clear();
}

bool Actions::hasAccess(const action_t& actionId_) const
{
    return (getPermissions(actionId_) == ALL);
}

bool Actions::isReadable(const action_t& actionId_) const
{
    return (getPermissions(actionId_) & READ);
}

bool Actions::isWriteable(const action_t& actionId_) const
{
    return (getPermissions(actionId_) & WRITE);
}

bool Actions::isDeletable(const action_t& actionId_) const
{
    return (getPermissions(actionId_) & DELETE);
}

int Actions::getPermissions(const action_t& actionId_) const
{
    int retval = 0;
    std::map<const action_t, int>::const_iterator iter = _actions.find(actionId_);
    if( iter != _actions.end() )
    {
        retval = iter->second;
    }

    return retval;
}

void Actions::setAction(const action_t& actionId_, const int permissions_ /* = ALL */)
{
    _actions[actionId_] = permissions_;
}

void Actions::clear()
{
    _actions.clear();
}

void Actions::load(const int& userId_)
{                           
    rowset<row> rs = (_session.prepare << _selectQuery(userId_));

    BOOST_FOREACH(row& row, rs)
    {
        setAction(row.get<action_t>("actionId"), row.get<int>("permission"));
    }
}

void Actions::save(const int& actionGroupId_)
{
    _delete(actionGroupId_);
    _insert(actionGroupId_);
}

void Actions::destroy(const int& actionGroupId_)
{
    _delete(actionGroupId_);
    clear();
}

std::string Actions::_selectQuery(const int& userId_)
{
    std::string query =
    "SELECT "    
    "    Action.actionId, "
    "    Action.permission "
    "FROM "
    "    Action "
    "    INNER JOIN ActionGroupUser USING (actionGroupId) "
    "WHERE "
    "    userId = ";
    query += boost::lexical_cast<std::string>(userId_);

    return query;
}

void Actions::_insert(const int& actionGroupId_)
{
    for(std::map<action_t, int>::iterator iter = _actions.begin(); iter != _actions.end(); ++iter)
    {
        _session <<
        "INSERT INTO Action "
        "(actionGroupId, actionId, permission) "
        "VALUES (:actionGroupId, :actionId, :permission)",
        use(actionGroupId_, "actionGroupId"),
        use((*iter).first, "actionId"),
        use((*iter).second, "permission");
    }
}

void Actions::_delete(const int& actionGroupId_)
{
    _session << "DELETE FROM Action WHERE actionGroupId = :actionGroupId",
    use(actionGroupId_, "actionGroupId");
}

}

