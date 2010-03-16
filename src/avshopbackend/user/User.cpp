#include <string>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#include "user/User.h"

namespace av
{

User::User(soci::session* session_)
        : _session(*session_), _contact(), _actions(session_)
{
    clear();
}

bool User::login(const std::string userName_, const std::string password_)
{    
    _load(userName_, password_);
    if (userAccountId())
    {
        _logedIn = true;
    }

    return isLoggedIn();
}

bool User::isLoggedIn() const
{
    return _logedIn;
}

bool User::hasAccess(const action_t& actionId_) const
{
    return _actions.hasAccess(actionId_);
}

bool User::isReadable(const action_t& actionId_) const
{
    return _actions.isReadable(actionId_);
}

bool User::isWriteable(const action_t& actionId_) const
{
    return _actions.isWriteable(actionId_);
}

bool User::isDeletable(const action_t& actionId_) const
{
    return _actions.isDeletable(actionId_);
}

int User::userAccountId() const
{
    return _userAccountId;
}

void User::setUserName(const std::string& userName_)
{
    _userName = userName_;
}

std::string User::userName() const
{
    return _userName;
}

void User::setPassword(const std::string& password_)
{
    //@todo: _password = md5(password_);
    _password = password_;
}

Contact& User::contact()
{
    return _contact;
}

void User::clear()
{
    _userAccountId = 0;
    _userName.clear();
    _password.clear();    
    _contact.clear();;
    _actions.clear();;

    _logedIn = false;
}

void User::load(const int& userAccountId_)
{
    rowset<row> rs = (_session.prepare << _selectQuery(userAccountId_));
    _loadFromRowset(rs);
    _actions.load(userAccountId_);
}

int User::save()
{
    if (userAccountId())
    {
        _update();
    }
    else
    {
        _insert();
    }

    return userAccountId();
}

void User::destroy()
{
    if (userAccountId())
    {
        _session << "DELETE FROM UserAccount WHERE userAccountId = :userAccountId",
        use(userAccountId(), "userAccountId");
    }
    clear();
}

void User::_load(const std::string userName_, const std::string password_)
{
    rowset<row> rs = (_session.prepare << _selectQuery(userName_, password_));
    _loadFromRowset(rs);

    if (userAccountId())
    {
        _actions.load(userAccountId());
    }
}

void User::_loadFromRowset(const rowset<row>& rs)
{
    clear();

    BOOST_FOREACH(row & row, rs)
    {
        _userAccountId = row.get<int>("userAccountId");
        _userName = row.get<string>("userName");

        _contact = Contact
        (
            row.get<string>("firstName"),
            row.get<string>("lastName"),
            row.get<string>("companyName"),
            row.get<string>("address"),
            row.get<string>("zip"),
            row.get<string>("city"),
            row.get<string>("phone"),
            row.get<string>("email"),
            row.get<string>("webUrl"),
            row.get<int>("contactId")
        );
    }
}

void User::_insert()
{
    contact().save(_session);

    _session <<
    "INSERT INTO UserAccount "
    "(userName, password, contactId) "
    "VALUES (:userName, :password, :contactId)",
    use(userName(), "userName"),
    use(_password, "password"),
    use(contact().contactId(), "contactId");

    _session << "SELECT last_insert_id()", into(_userAccountId);
}

void User::_update()
{
    contact().save(_session);

    if (_password.empty())
    {
        _session <<
        "UPDATE UserAccount "
        "SET "
        "  userName = :userName "
        "WHERE "
        "  userAccountId = :userAccountId",
        use(userName(), "userName"),
        use(userAccountId(), "userAccountId");
    }
    else
    {
        _session <<
        "UPDATE UserAccount "
        "SET "
        "  userName = :userName, "
        "  password = :password "
        "WHERE "
        "  userAccountId = :userAccountId",
        use(userName(), "userName"),
        use(_password, "password"),
        use(userAccountId(), "userAccountId");
    }
}

std::string User::_selectBase()
{
    return
        "SELECT "
        "  userAccountId, "
        "  userName, "
        "  contactId, "
        "  firstName, "
        "  lastName, "
        "  companyName, "
        "  address, "
        "  zip, "
        "  city, "
        "  phone, "
        "  email, "
        "  webUrl "
        "FROM "
        "  UserAccount "
        "  INNER JOIN Contact USING (contactId)"
        "WHERE ";
}

std::string User::_selectQuery(const int userAccountId_)
{
    std::string query;
    query += _selectBase();
    query += "  userAccountId = " + boost::lexical_cast<std::string>(userAccountId_);
    query += " LIMIT 0, 1";

    return query;
}

std::string User::_selectQuery(const std::string userName_, const std::string password_)
{
    std::string query;
    query = _selectBase();
    query += "  userName = '" + userName_ + "' AND";
    query += "  password = '" + password_ + "'";
    query += " LIMIT 0, 1";

    return query;
}

}
