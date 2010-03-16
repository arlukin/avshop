#ifndef USER_H
#define USER_H

/**
 * GLOSSARY
 *
 * Action
 * ------
 * A specific task/action/windows/widget/webpage/function a user of the
 * application can do. For example a user can send an email from the
 * application. A user can go to his user profile, and change the
 * password and save.
 *
 * ActionGroup
 * -----------
 * A collection of one or more actions with different permissions. One
 * or more users are connected to the ActionGroup. In this way one or
 * more users can have the same permissions to the same actions.
 *
 * Permission
 * ----------
 * Permission levels set on a action such as read and write permissions.
 *
 * User
 * ----
 * A representation of the user that uses the application.
 *
 */

#include <string>

#include "general/ShopDb.h"
#include "products/Contact.h"

#include "Action.h"
#include "Actions.h"

namespace av
{

class User
{
public:
    User(soci::session* session_);

    bool login(const std::string userName_, const std::string password_);

    bool isLoggedIn() const;
    bool hasAccess(const action_t& actionId_) const;
    bool isReadable(const action_t& actionId_) const;
    bool isWriteable(const action_t& actionId_) const;
    bool isDeletable(const action_t& actionId_) const;

    int userAccountId() const;

    void setUserName(const std::string& userName_);
    std::string userName() const;

    void setPassword(const std::string& password_);    

    Contact& contact();

    void clear();
    void load(const int& userAccountId_);
    int  save();
    void destroy();

private:    
    void _load(const std::string userName_, const std::string password_);
    void _loadFromRowset(const rowset<row>& rs);
    void _insert();
    void _update();
    std::string _selectBase();
    std::string _selectQuery(const int userAccountId_);
    std::string _selectQuery(const std::string userName_, const std::string password_);

private:
    int _userAccountId;
    std::string _userName;
    std::string _password;
    Contact _contact;
    Actions _actions;

    int _logedIn;
    soci::session& _session;
};

}
#endif // USER_H
