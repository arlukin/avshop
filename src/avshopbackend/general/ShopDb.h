#ifndef SHOPDB_H
#define SHOPDB_H

#include <soci.h>
#include <mysql/soci-mysql.h>
using namespace soci;

class ProductTypes;
class ProductType;
class Contact;
class Products;
class OrderHeaders;
class UserAccount;

namespace av
{
    class User;
    class ActionGroup;
};
using namespace av;

class ShopDb
{
    public:
        ShopDb();
        ~ShopDb();

        soci::session* getSession();

        ProductTypes* getProductTypes();
        ProductType* getProductType();
        Contact* getContact();
        Products* getProducts();
        OrderHeaders* getOrderHeaders();
        UserAccount* getUserAccount();
        User* getUser();
        ActionGroup* getActionGroup();

    protected:

    private:
        void _buildSession();

        soci::session* _session;
};

#endif // SHOPDB_H
