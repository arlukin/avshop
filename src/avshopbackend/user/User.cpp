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
    if (userId())
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

int User::userId() const
{
    return _userId;
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
    _userId = 0;
    _userName.clear();
    _password.clear();    
    _contact.clear();;
    _actions.clear();;

    _logedIn = false;
}

void User::load(const int& userId_)
{
    rowset<row> rs = (_session.prepare << _selectQuery(userId_));
    _loadFromRowset(rs);
    _actions.load(userId_);
}

int User::save()
{
    if (userId())
    {
        _update();
    }
    else
    {
        _insert();
    }

    return userId();
}

void User::destroy()
{
    if (userId())
    {
        _session << "DELETE FROM User WHERE userId = :userId",
        use(userId(), "userId");
    }
    clear();
}

void User::_load(const std::string userName_, const std::string password_)
{
    rowset<row> rs = (_session.prepare << _selectQuery(userName_, password_));
    _loadFromRowset(rs);

    if (userId())
    {
        _actions.load(userId());
    }
}

void User::_loadFromRowset(const rowset<row>& rs)
{
    clear();

    BOOST_FOREACH(row & row, rs)
    {
        _userId = row.get<int>("userId");
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
    "INSERT INTO User "
    "(userName, password, contactId) "
    "VALUES (:userName, :password, :contactId)",
    use(userName(), "userName"),
    use(_password, "password"),
    use(contact().contactId(), "contactId");

    _session << "SELECT last_insert_id()", into(_userId);
}

void User::_update()
{
    contact().save(_session);

    if (_password.empty())
    {
        _session <<
        "UPDATE User "
        "SET "
        "  userName = :userName "
        "WHERE "
        "  userId = :userId",
        use(userName(), "userName"),
        use(userId(), "userId");
    }
    else
    {
        _session <<
        "UPDATE User "
        "SET "
        "  userName = :userName, "
        "  password = :password "
        "WHERE "
        "  userId = :userId",
        use(userName(), "userName"),
        use(_password, "password"),
        use(userId(), "userId");
    }
}

std::string User::_selectBase()
{
    return
        "SELECT "
        "  userId, "
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
        "  User "
        "  INNER JOIN Contact USING (contactId)"
        "WHERE ";
}

std::string User::_selectQuery(const int userId_)
{
    std::string query;
    query += _selectBase();
    query += "  userId = " + boost::lexical_cast<std::string>(userId_);
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
