#include "products/Contact.h"
#include "products/Products.h"
#include "products/ProductTypes.h"
#include "products/OrderHeaders.h"
#include "user/UserAccount.h"
#include "user/User.h"
#include "user/ActionGroup.h"
using namespace av;

#include "ShopDb.h"

ShopDb::ShopDb()
{
    _session = 0;
}

ShopDb::~ShopDb()
{
    if (_session)
    {
        delete _session;
    }
}

soci::session* ShopDb::getSession()
{
    _buildSession();
    return _session;
}

ProductTypes* ShopDb::getProductTypes()
{
    return new ProductTypes(*getSession());
}

ProductType* ShopDb::getProductType()
{
    return new ProductType;
}

Contact* ShopDb::getContact()
{
    return new Contact;
}

Products* ShopDb::getProducts()
{
    return new Products(*getSession());
}

OrderHeaders* ShopDb::getOrderHeaders()
{
    return new OrderHeaders(*getSession());
}

UserAccount* ShopDb::getUserAccount()
{
    return new UserAccount(*getSession());
}

User* ShopDb::getUser()
{
    return new User(getSession());
}

ActionGroup* ShopDb::getActionGroup()
{
    return new ActionGroup(getSession());
}

void ShopDb::_buildSession()
{
    if (_session == 0)
    {
        _session = new soci::session(mysql, "db=shop user=shop password='password'");
        *_session << "SET NAMES 'utf8'";
    }
}
