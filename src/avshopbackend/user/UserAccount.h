#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include "AVString.h"

#include <soci/soci.h>
using namespace soci;

#include "products/Contact.h"

class UserAccount
{
public:
    UserAccount(soci::session& session_);
    UserAccount
    (
        soci::session& session_,
        const std::string& userName_,
        const std::string& password_,
        const Contact& contact_,
        int userId_ = NULL
    );

    bool login(const std::string userName_, const std::string password_);
    bool isLoggedIn();

    int userAccountId();
    void setUserName(const std::string& userName_);
    const std::string& userName() const;

    void setPassword(const std::string& password_);

    Contact& contact();

    void clear();

    void load
    (        
        const int userAccountId_,
        const std::string userName_ = "",
        const std::string password_ = ""
    );
    int save();
    void destroy();

protected:

private:
    void insert();
    void update();
    std::string _selectQuery
    (
        const int userAccountId_,
        const std::string userName_ = "",
        const std::string password_ = ""
    );

private:
    soci::session& _session;

    std::string _userName;
    std::string _password;
    Contact _contact;
    int _userAccountId;

    int _logedIn;
};

#endif // USERACCOUNT_H
