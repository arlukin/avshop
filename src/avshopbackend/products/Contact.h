#ifndef CONTACT_H_INCLUDED
#define CONTACT_H_INCLUDED

#include <string>
using std::string;

#include "general/DBTable.h"

class Contact : public DBTable
{
public:
    Contact();
    Contact
    (
        const string& firstName_,
        const string& lastName_,
        const string& companyName_,        
        const string& address_,
        const string& zip_,
        const string& city_,
        const string& phone_,
        const string& email_,
        const string& webUrl_,
        int contactId_ = NULL
    );

    int contactId();

    void setFirstName(const string& firstName_);
    const string& firstName() const;

    void setLastName(const string& lastName_);
    const string& lastName() const;

    void setCompanyName(const string& companyName_);
    const string& companyName() const;

    void setAddress(const string& address_);
    const string& address() const;

    void setZip(const string& zip_);
    const string& zip() const;

    void setCity(const string& city_);
    const string& city() const;

    void setPhone(const string& phone_);
    const string& phone() const;

    void setEmail(const string& email_);
    const string& email() const;

    void setWebUrl(const string& webUrl_);
    const string& webUrl() const;

    void clear();

    void load(session& session_, int contactId);
    int save(session& session_);
    void destroy(session& session_);

protected:

private:
    void insert(session& session_);
    void update(session& session_);

    string _firstName;
    string _lastName;
    string _companyName;
    string _address;
    string _zip;
    string _city;
    string _phone;
    string _email;
    string _webUrl;

    int _contactId;
};

#endif // CONTACT_H_INCLUDED
