#include "boost/lexical_cast.hpp"
using boost::lexical_cast;

#include "UserAccount.h"
#include "AVString.h"
UserAccount::UserAccount(soci::session& session_)
    :    _session(session_)
{
    clear();
}

UserAccount::UserAccount
(
    soci::session& session_,
    const std::string& userName_,
    const std::string& password_,
    const Contact& contact_,
    int userAccountId_
)
    : _userName(userName_),
    _contact(contact_),
    _userAccountId(userAccountId_),
    _session(session_)
{
    _logedIn = false;
    setPassword(password_);
}

bool UserAccount::login(const std::string userName_, const std::string password_)
{
    load
    (        
        NULL,
        userName_,
        password_
    );
    if (userAccountId())
    {
        _logedIn = true;
    }
    else
    {
        clear();
    }

    return isLoggedIn();
}

bool UserAccount::isLoggedIn()
{
    return _logedIn;
}

int UserAccount::userAccountId()
{
    return _userAccountId;
}

void UserAccount::setUserName(const std::string& userName_)
{
    _userName = userName_;
}

const std::string& UserAccount::userName() const
{
    return _userName;
}

void UserAccount::setPassword(const std::string& password_)
{
    //@todo: _password = md5(password_);
    _password = password_;
}

Contact& UserAccount::contact()
{
    return _contact;
}

void UserAccount::clear()
{
    _userName = "";
    _password = "";
    _contact.clear();
    _userAccountId = 0;

    _logedIn = false;
}

void UserAccount::load
(
    const int userAccountId_,
    const std::string userName_,
    const std::string password_
)
{
    enum {USERACCOUNTID, USERNAME, PASSWORD, CONTACTID, FIRSTNAME, LASTNAME, COMPANYNAME, EMAIL, WEBURL};

    rowset<row> rs = (_session.prepare << _selectQuery(userAccountId_, userName_, password_));

    rowset<row>::const_iterator it = rs.begin();
    if (it != rs.end())
    {
        row const& row = *it;
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
        ++it;
        assert(it == rs.end());
    }
}


int UserAccount::save()
{
    if (userAccountId())
    {
        update();
    }
    else
    {
        insert();
    }

    return userAccountId();
}

void UserAccount::insert()
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
};

void UserAccount::update()
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
};

void UserAccount::destroy()
{
    clear();
    if (userAccountId())
    {
        _session << "DELETE FROM UserAccount WHERE userAccountId = :userAccountId",
        use(userAccountId(), "userAccountId");
    }
}

std::string UserAccount::_selectQuery
(
    const int userAccountId_,
    const std::string userName_,
    const std::string password_
)
{
    std::string query;
    query =
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
      "	 INNER JOIN Contact USING (contactId)"
      "WHERE ";

    if (userAccountId_)
    {
        query += "  userAccountId = " + boost::lexical_cast<std::string>(userAccountId_);
    }
    else if (!userName_.empty())
    {
        query += "  userName = '" + userName_ + "' AND";
        query += "  password = '" + password_ + "'";
    }

    query += " LIMIT 0, 1";

    return query;
}
