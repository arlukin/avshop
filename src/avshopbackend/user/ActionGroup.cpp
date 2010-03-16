#include "boost/foreach.hpp"
#include "boost/lexical_cast.hpp"

#include "ActionGroup.h"

namespace av
{

ActionGroup::ActionGroup(soci::session* session_)
    : _session(*session_), _actions(session_)
{
    clear();
}

int ActionGroup::actionGroupId() const
{
    return _actionGroupId;
}

void ActionGroup::setName(const std::string& name_)
{
    _name = name_;
}

std::string ActionGroup::name() const
{
    return _name;
}

void ActionGroup::setAction(const action_t& actionId_, const int& permissions_ /*= ALL*/)
{
    _actions.setAction(actionId_, permissions_);
}

void ActionGroup::addUser(const int& userId_)
{    
    _usersAcountIds.insert(userId_);
}

void ActionGroup::removeUser(const int& userId_)
{    
    _usersAcountIds.erase(userId_);
}

void ActionGroup::clear()
{
    _actionGroupId = 0;
    _name.clear();
    _actions.clear();
    _usersAcountIds.clear();
}

void ActionGroup::load(const int& actionGroupId_)
{
    clear();
    _selectActionGroup(actionGroupId_);
    if (actionGroupId())
    {
        _selectActionGroupUser(actionGroupId_);
        _selectAction(actionGroupId_);
    }
}

bool ActionGroup::save()
{
    if (actionGroupId())
    {
        _update();
    }
    else
    {
        _insert();
    }

    _actions.save(actionGroupId());

    _deleteActionGroupUser();
    _insertActionGroupUser();

    return actionGroupId();
}

void ActionGroup::destroy()
{
    if (actionGroupId())
    {
        _session << "DELETE FROM ActionGroup WHERE actionGroupId = :actionGroupId",
        use(actionGroupId(), "actionGroupId");

        //_actions.destroy(actionGroupId());
        //_deleteActionGroupUser();
    }
    clear();
}

void ActionGroup::_selectActionGroup(const int& actionGroupId_)
{
    std::string query =
    "SELECT "
    "   name "
    "FROM "
    "   ActionGroup "
    "WHERE "
    "   actionGroupId = ";
    query += boost::lexical_cast<std::string>(actionGroupId_);

    rowset<row> rs = (_session.prepare << query);

    BOOST_FOREACH(row& row, rs)
    {
        _actionGroupId = actionGroupId_;
        setName(row.get<std::string>("name"));
    }
}

void ActionGroup::_selectActionGroupUser(const int& actionGroupId_)
{
    std::string query =
    "SELECT "
    "   userId "
    "FROM "
    "   ActionGroupUser "
    "WHERE "
    "   actionGroupId = ";
    query += boost::lexical_cast<std::string>(actionGroupId_);

    rowset<row> rs = (_session.prepare << query);

    BOOST_FOREACH(row& row, rs)
    {
        addUser(row.get<int>("userId"));
    }
}

void ActionGroup::_selectAction(const int& actionGroupId_)
{
    std::string query =
    "SELECT "
    "   actionId, "
    "   permission "
    "FROM "
    "   Action "
    "WHERE "
    "   actionGroupId = ";
    query += boost::lexical_cast<std::string>(actionGroupId_);

    rowset<row> rs = (_session.prepare << query);

    BOOST_FOREACH(row& row, rs)
    {
        setAction(row.get<int>("actionId"), row.get<int>("permission"));
    }
}

void ActionGroup::_insert()
{
    _session <<
    "INSERT INTO ActionGroup "
    "(name) "
    "VALUES (:name)",
    use(name(), "name");

    _session << "SELECT last_insert_id()", into(_actionGroupId);
}

void ActionGroup::_insertActionGroupUser()
{    
    BOOST_FOREACH(const int& userId, _usersAcountIds)
    {
        _session <<
        "INSERT INTO ActionGroupUser "
        "(userId, actionGroupId) "
        "VALUES (:userId, :actionGroupId)",
        use(userId, "userId"),
        use(actionGroupId(), "actionGroupId");
    }
}

void ActionGroup::_deleteActionGroupUser()
{
    _session << "DELETE FROM ActionGroupUser WHERE actionGroupId = :actionGroupId",
    use(actionGroupId(), "actionGroupId");
}

void ActionGroup::_update()
{
    _session <<
    "UPDATE ActionGroup "
    "SET "
    "  name = :name "
    "WHERE "
    "  actionGroupId = :actionGroupId",
    use(name(), "name"),
    use(actionGroupId(), "actionGroupId");
}

}
