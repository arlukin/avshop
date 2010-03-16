#include <assert.h>

#include "Contact.h"

Contact::Contact()
        : _contactId(0)
{
}

Contact::Contact
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
    int contactId_
)
        : _firstName(firstName_), _lastName(lastName_),
        _companyName(companyName_),
        _address(address_), _zip(zip_), _city(city_), _phone(phone_),
        _email(email_), _webUrl(webUrl_),
        _contactId(contactId_)
{
}

int Contact::contactId()
{
    return _contactId;
};

void Contact::setFirstName(const string& firstName_)
{
    _firstName = firstName_;
};

const string& Contact::firstName() const
{
    return _firstName;
};

void Contact::setLastName(const string& lastName_)
{
    _lastName = lastName_;
};

const string& Contact::lastName() const
{
    return _lastName;
};

void Contact::setCompanyName(const string& companyName_)
{
    _companyName = companyName_;
};

const string& Contact::companyName() const
{
    return _companyName;
};

void Contact::setAddress(const string& address_)
{
    _address = address_;
};

const string& Contact::address() const
{
    return _address;
};

void Contact::setZip(const string& zip_)
{
    _zip = zip_;
};

const string& Contact::zip() const
{
    return _zip;
};

void Contact::setCity(const string& city_)
{
    _city = city_;
};

const string& Contact::city() const
{
    return _city;
};

void Contact::setPhone(const string& phone_)
{
    _phone = phone_;
};

const string& Contact::phone() const
{
    return _phone;
};

void Contact::setEmail(const string& email_)
{
    _email = email_;
};

const string& Contact::email() const
{
    return _email;
};

void Contact::setWebUrl(const string& webUrl_)
{
    _webUrl = webUrl_;
};

const string& Contact::webUrl() const
{
    return _webUrl;
}

void Contact::clear()
{
    _firstName = "";
    _lastName = "";
    _companyName = "";
    _address = "";
    _zip = "";
    _city = "";
    _phone = "";
    _email = "";
    _webUrl = "";
    _contactId = 0;
}

void Contact::load(session& session_, int contactId_)
{
    enum {CONTACTID, FIRSTNAME, LASTNAME, COMPANYNAME, EMAIL, WEBURL};

    rowset<row> rs = (session_.prepare <<
                      "SELECT "
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
                      "	Contact "
                      "WHERE "
                      "   contactId = :contactId",
                      use(contactId_, "contactId"));

    rowset<row>::const_iterator it = rs.begin();
    if (it != rs.end())
    {
        row const& row = *it;

        _contactId = row.get<int>("contactId");
        _firstName = row.get<string>("firstName");
        _lastName = row.get<string>("lastName");
        _companyName = row.get<string>("companyName");
        _address = row.get<string>("address");
        _zip = row.get<string>("zip");
        _city = row.get<string>("city");
        _phone = row.get<string>("phone");
        _email = row.get<string>("email");
        _webUrl = row.get<string>("webUrl");

        ++it;
        assert(it == rs.end());
    }
}

int Contact::save(session& session_)
{
    if (contactId())
    {
        update(session_);
    }
    else
    {
        insert(session_);
    }

    return _contactId;
}

void Contact::insert(session& session_)
{
    session_ <<
    "INSERT INTO Contact "
    "(firstName, lastName, companyName, address, zip, city, phone, email, webUrl) "
    "VALUES (:firstName, :lastName, :companyName, :address, :zip, :city, :phone, :email, :webUrl)",
    use(firstName(), "firstName"),
    use(lastName(), "lastName"),
    use(companyName(), "companyName"),
    use(address(), "address"),
    use(zip(), "zip"),
    use(city(), "city"),
    use(phone(), "phone"),
    use(email(), "email"),
    use(webUrl(), "webUrl");

    session_ << "SELECT last_insert_id()", into(_contactId);
};

void Contact::update(session& session_)
{
    session_ <<
    "UPDATE Contact "
    "SET "
    "  firstName = :firstName, "
    "  lastName = :lastName, "
    "  companyName = :companyName, "
    "  address = :address, "
    "  zip = :zip, "
    "  city = :city, "
    "  phone = :phone, "
    "  email = :email, "
    "  webUrl = :webUrl "
    "WHERE "
    "   contactId = :contactId",
    use(firstName(), "firstName"),
    use(lastName(), "lastName"),
    use(companyName(), "companyName"),
    use(address(), "address"),
    use(zip(), "zip"),
    use(city(), "city"),
    use(phone(), "phone"),
    use(email(), "email"),
    use(webUrl(), "webUrl"),
    use(contactId(), "contactId");
};

void Contact::destroy(session& session_)
{
    clear();
    if (contactId())
    {
        session_ << "DELETE FROM Contact WHERE contactId = :contactId",
        use(contactId(), "contactId");
    }
}
