#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include "general/ShopDb.h"
#include "products/Products.h"

BOOST_AUTO_TEST_SUITE (ProductTestSuite)

BOOST_AUTO_TEST_CASE( ShopDbTest )
{
     ShopDb shopDb;
     soci::session* session;
     BOOST_CHECK_NE(session = shopDb.getSession(), (soci::session*)0 );
}

BOOST_AUTO_TEST_CASE( ProductsTestAddToDatabase )
{
    ShopDb shopDb;
    Products& products = *shopDb.getProducts();

    Contact contact("Daniel", "Lindh", "Amivono AB",
                    "Linnegatan 7", "126 51", "STOCKHOLM", "+46-73-626 54 49",
                    "daniel@cybercow.se", "www.cybercow.se");

    products.push_back(Product("Z-Wave remote", "This is a remote control", contact, contact, "XT100", "IN100", 2, 3, ProductType("Remote"), Money(100, "SEK"), Money(120, "SEK")));
    products.push_back(Product("Z-Wave dongle", "This is a z-wave usb dongle", contact, contact, "XT100", "IN100", 4, 5, ProductType("DONGLE"), Money(123, "SEK"), Money(144, "SEK")));
    products.save();

    BOOST_CHECK_EQUAL(products.size(), 2);

    Products::const_iterator product = products.begin();

    BOOST_CHECK_EQUAL(product->name(), "Z-Wave remote");
    BOOST_CHECK_EQUAL(product->description(), "This is a remote control");

    BOOST_CHECK_EQUAL(product->manufacturer().firstName(), "Daniel");
    BOOST_CHECK_EQUAL(product->manufacturer().lastName(), "Lindh");
    BOOST_CHECK_EQUAL(product->manufacturer().companyName(), "Amivono AB");
    BOOST_CHECK_EQUAL(product->manufacturer().email(), "daniel@cybercow.se");
    BOOST_CHECK_EQUAL(product->manufacturer().webUrl(), "www.cybercow.se");

    BOOST_CHECK_EQUAL(product->supplier().firstName(), "Daniel");
    BOOST_CHECK_EQUAL(product->supplier().lastName(), "Lindh");
    BOOST_CHECK_EQUAL(product->supplier().companyName(), "Amivono AB");
    BOOST_CHECK_EQUAL(product->supplier().email(), "daniel@cybercow.se");
    BOOST_CHECK_EQUAL(product->supplier().webUrl(), "www.cybercow.se");

    BOOST_CHECK_EQUAL(product->externPartNo(), "XT100");
    BOOST_CHECK_EQUAL(product->internPartNo(), "IN100");
    BOOST_CHECK_EQUAL(product->minOrder(), 2);
    BOOST_CHECK_EQUAL(product->deliveryTime(), 3);

    BOOST_CHECK_EQUAL(product->productType().name(), "Remote");

    BOOST_CHECK(product->supplierPrice() == Money(100, "SEK"));
    BOOST_CHECK(product->salesPrice() ==  Money(120, "SEK"));

    ++product;

    BOOST_CHECK_EQUAL(product->name(), "Z-Wave dongle");
    BOOST_CHECK_EQUAL(product->description(), "This is a z-wave usb dongle");
}

BOOST_AUTO_TEST_CASE( ProductsTestSelectFromDatabase )
{
    ShopDb shopDb;
    Products& products = *shopDb.getProducts();

    products.load();

    BOOST_CHECK_EQUAL(products.size(), 2);

    Products::iterator product = products.begin();

    BOOST_CHECK_EQUAL(product->name(), "Z-Wave remote");
    BOOST_CHECK_EQUAL(product->description(), "This is a remote control");

    BOOST_CHECK_EQUAL(product->manufacturer().firstName(), "Daniel");
    BOOST_CHECK_EQUAL(product->manufacturer().lastName(), "Lindh");
    BOOST_CHECK_EQUAL(product->manufacturer().companyName(), "Amivono AB");
    BOOST_CHECK_EQUAL(product->manufacturer().email(), "daniel@cybercow.se");
    BOOST_CHECK_EQUAL(product->manufacturer().webUrl(), "www.cybercow.se");

    BOOST_CHECK_EQUAL(product->supplier().firstName(), "Daniel");
    BOOST_CHECK_EQUAL(product->supplier().lastName(), "Lindh");
    BOOST_CHECK_EQUAL(product->supplier().companyName(), "Amivono AB");
    BOOST_CHECK_EQUAL(product->supplier().email(), "daniel@cybercow.se");
    BOOST_CHECK_EQUAL(product->supplier().webUrl(), "www.cybercow.se");

    BOOST_CHECK_EQUAL(product->externPartNo(), "XT100");
    BOOST_CHECK_EQUAL(product->internPartNo(), "IN100");
    BOOST_CHECK_EQUAL(product->minOrder(), 2);
    BOOST_CHECK_EQUAL(product->deliveryTime(), 3);

    BOOST_CHECK_EQUAL(product->productType().name(), "Remote");

    BOOST_CHECK(product->supplierPrice() == Money(100, "SEK"));
    BOOST_CHECK(product->salesPrice() ==  Money(120, "SEK"));

    ++product;

    BOOST_CHECK_EQUAL(product->name(), "Z-Wave dongle");
    BOOST_CHECK_EQUAL(product->description(), "This is a z-wave usb dongle");
}

BOOST_AUTO_TEST_CASE( ProductsEmptyDatabase )
{
    ShopDb shopDb;
    Products& products = *shopDb.getProducts();

    // Remove everything in the database.
    products.load();
    products.destroy();

    BOOST_CHECK_EQUAL(products.size(), 0);
}

BOOST_AUTO_TEST_CASE( ProductTypesTestListAll)
{
    //Process / test
    ShopDb shopDb;
    Products& products = *shopDb.getProducts();

    products.load();
    for
    (
        Products::const_iterator product = products.begin();
        product != products.end();
        ++product
    )
    {
        BOOST_CHECK(product->name().size() > 0);
    }
}

BOOST_AUTO_TEST_SUITE_END( )

// EOF
