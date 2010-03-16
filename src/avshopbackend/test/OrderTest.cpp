#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/foreach.hpp>

#include "general/ShopDb.h"
#include "products/OrderHeaders.h"
#include "products/Products.h"
#include "user/User.h"
using namespace av;

struct OrderHeaderTestSuiteFixture
{
    OrderHeaderTestSuiteFixture()
    {
    }

    ~OrderHeaderTestSuiteFixture()
    {
    }

    ShopDb shopDb;
};

BOOST_FIXTURE_TEST_SUITE( OrderHeaderTestSuite, OrderHeaderTestSuiteFixture )

BOOST_AUTO_TEST_CASE( OrderHeadersTestTruncate )
{
    //Process
    OrderHeaders orderHeaders(*shopDb.getSession());
    orderHeaders.destroy();

    // Test
   BOOST_CHECK_EQUAL(orderHeaders.count(), 0);
}

BOOST_AUTO_TEST_CASE( OrderHeadersTestPrepareProductTables )
{
    ShopDb shopDb;
    Products& products = *shopDb.getProducts();

    Contact contact("Daniel", "Lindh", "Amivono AB",
                    "Linnegatan 7", "126 51", "STOCKHOLM", "+46-73-626 54 49",
                    "daniel@cybercow.se", "www.cybercow.se");

    products.push_back(Product("Z-Wave remote", "This is a remote control", contact, contact, "XT100", "IN100", 2, 3, ProductType("REMOTE"), Money(100, "SEK"), Money(120, "SEK")));
    products.push_back(Product( "Z-Wave dongle", "This is a z-wave usb dongle", contact, contact, "XT110", "IN110", 4, 5, ProductType("DONGLE"), Money(123, "SEK"), Money(144, "SEK")));
    products.save();

    BOOST_REQUIRE_EQUAL(products.size(), 2);
}

BOOST_AUTO_TEST_CASE( OrderHeadersTestAddToDatabase )
{
    ShopDb shopDb;
    OrderHeaders& orderHeaders = *shopDb.getOrderHeaders();

    Contact contact("Daniel", "Lindh", "Amivono AB",
                    "Linnegatan 7", "126 51", "STOCKHOLM", "+46-73-626 54 49",
                    "daniel@cybercow.se", "www.cybercow.se");

    orderHeaders.push_back(OrderHeader(NULL, contact));
    orderHeaders.push_back(OrderHeader(NULL, contact));
    orderHeaders.save();

    BOOST_CHECK_EQUAL(orderHeaders.size(), 2);

    OrderHeaders::const_iterator orderHeader = orderHeaders.begin();

    BOOST_CHECK_EQUAL(orderHeader->orginator().firstName(), "Daniel");
    BOOST_CHECK_EQUAL(orderHeader->orginator().lastName(), "Lindh");
    BOOST_CHECK_EQUAL(orderHeader->orginator().companyName(), "Amivono AB");
    BOOST_CHECK_EQUAL(orderHeader->orginator().email(), "daniel@cybercow.se");
    BOOST_CHECK_EQUAL(orderHeader->orginator().webUrl(), "www.cybercow.se");

    ++orderHeader;
}

BOOST_AUTO_TEST_CASE( OrderHeadersTestSelectFromDatabase )
{
    ShopDb shopDb;
    OrderHeaders& orderHeaders = *shopDb.getOrderHeaders();

    orderHeaders.load();

    BOOST_CHECK_EQUAL(orderHeaders.size(), 2);

    OrderHeaders::iterator orderHeader = orderHeaders.begin();
    BOOST_CHECK_EQUAL(orderHeader->orginator().firstName(), "Daniel");
    BOOST_CHECK_EQUAL(orderHeader->orginator().lastName(), "Lindh");
    BOOST_CHECK_EQUAL(orderHeader->orginator().companyName(), "Amivono AB");
    BOOST_CHECK_EQUAL(orderHeader->orginator().email(), "daniel@cybercow.se");
    BOOST_CHECK_EQUAL(orderHeader->orginator().webUrl(), "www.cybercow.se");

    ++orderHeader;
}

BOOST_AUTO_TEST_CASE( OrderHeadersTestOrderRow )
{
    // Setup
    ShopDb shopDb;
    Products& products = *shopDb.getProducts();
    products.load();
    Products::iterator product = products.begin();

    // Process
    OrderHeaders& orderHeaders = *shopDb.getOrderHeaders();
    orderHeaders.load();

    OrderHeader orderHeader = orderHeaders.front();
    orderHeader.addOrderRow(OrderRow(NULL, NULL, *product, 2));
    ++product;
    orderHeader.addOrderRow(OrderRow(NULL, NULL, *product, 2));
    orderHeader.save(*shopDb.getSession());

    // Check OrderHeader
    BOOST_REQUIRE_EQUAL(orderHeaders.size(), 2);
    BOOST_CHECK_EQUAL(orderHeader.orginator().firstName(), "Daniel");
    BOOST_CHECK_EQUAL(orderHeader.orginator().lastName(), "Lindh");
    BOOST_CHECK_EQUAL(orderHeader.orginator().companyName(), "Amivono AB");
    BOOST_CHECK_EQUAL(orderHeader.orginator().email(), "daniel@cybercow.se");
    BOOST_CHECK_EQUAL(orderHeader.orginator().webUrl(), "www.cybercow.se");

    // Check OrderRow
    BOOST_FOREACH(OrderHeader::t_OrderRow orderRows, orderHeader.orderRows())
    {
        if (orderRows.second.product().name() == "Z-Wave remote")
        {
            BOOST_CHECK_EQUAL(orderRows.second.product().name(), "Z-Wave remote");
            BOOST_CHECK_EQUAL(orderRows.second.product().description(), "This is a remote control");

            BOOST_CHECK_EQUAL(orderRows.second.product().manufacturer().firstName(), "Daniel");
            BOOST_CHECK_EQUAL(orderRows.second.product().manufacturer().lastName(), "Lindh");
            BOOST_CHECK_EQUAL(orderRows.second.product().manufacturer().companyName(), "Amivono AB");
            BOOST_CHECK_EQUAL(orderRows.second.product().manufacturer().email(), "daniel@cybercow.se");
            BOOST_CHECK_EQUAL(orderRows.second.product().manufacturer().webUrl(), "www.cybercow.se");

            BOOST_CHECK_EQUAL(orderRows.second.product().supplier().firstName(), "Daniel");
            BOOST_CHECK_EQUAL(orderRows.second.product().supplier().lastName(), "Lindh");
            BOOST_CHECK_EQUAL(orderRows.second.product().supplier().companyName(), "Amivono AB");
            BOOST_CHECK_EQUAL(orderRows.second.product().supplier().email(), "daniel@cybercow.se");
            BOOST_CHECK_EQUAL(orderRows.second.product().supplier().webUrl(), "www.cybercow.se");

            BOOST_CHECK_EQUAL(orderRows.second.product().externPartNo(), "XT100");
            BOOST_CHECK_EQUAL(orderRows.second.product().internPartNo(), "IN100");
            BOOST_CHECK_EQUAL(orderRows.second.product().minOrder(), 2);
            BOOST_CHECK_EQUAL(orderRows.second.product().deliveryTime(), 3);

            BOOST_CHECK_EQUAL(orderRows.second.product().productType().name(), "Remote");

            BOOST_CHECK(orderRows.second.product().supplierPrice() == Money(100, "SEK"));
            BOOST_CHECK(orderRows.second.product().salesPrice() ==  Money(120, "SEK"));
        }
        else
        {
            BOOST_CHECK_EQUAL(orderRows.second.product().name(), "Z-Wave dongle");
            BOOST_CHECK_EQUAL(orderRows.second.product().description(), "This is a z-wave usb dongle");

            BOOST_CHECK_EQUAL(orderRows.second.product().manufacturer().firstName(), "Daniel");
            BOOST_CHECK_EQUAL(orderRows.second.product().manufacturer().lastName(), "Lindh");
            BOOST_CHECK_EQUAL(orderRows.second.product().manufacturer().companyName(), "Amivono AB");
            BOOST_CHECK_EQUAL(orderRows.second.product().manufacturer().email(), "daniel@cybercow.se");
            BOOST_CHECK_EQUAL(orderRows.second.product().manufacturer().webUrl(), "www.cybercow.se");

            BOOST_CHECK_EQUAL(orderRows.second.product().supplier().firstName(), "Daniel");
            BOOST_CHECK_EQUAL(orderRows.second.product().supplier().lastName(), "Lindh");
            BOOST_CHECK_EQUAL(orderRows.second.product().supplier().companyName(), "Amivono AB");
            BOOST_CHECK_EQUAL(orderRows.second.product().supplier().email(), "daniel@cybercow.se");
            BOOST_CHECK_EQUAL(orderRows.second.product().supplier().webUrl(), "www.cybercow.se");

            BOOST_CHECK_EQUAL(orderRows.second.product().externPartNo(), "XT110");
            BOOST_CHECK_EQUAL(orderRows.second.product().internPartNo(), "IN110");
            BOOST_CHECK_EQUAL(orderRows.second.product().minOrder(), 4);
            BOOST_CHECK_EQUAL(orderRows.second.product().deliveryTime(), 5);

            BOOST_CHECK_EQUAL(orderRows.second.product().productType().name(), "DONGLE");

            BOOST_CHECK(orderRows.second.product().supplierPrice() == Money(123, "SEK"));
            BOOST_CHECK(orderRows.second.product().salesPrice() ==  Money(144, "SEK"));
        }
    }
}

BOOST_AUTO_TEST_CASE( OrderHeadersTestOrderRowLoad )
{
    // Setup
    ShopDb shopDb;

    // Process
    OrderHeaders& orderHeaders = *shopDb.getOrderHeaders();
    orderHeaders.load();
    OrderHeader orderHeader = orderHeaders.front();

    // Check OrderHeader
    BOOST_CHECK_EQUAL(orderHeader.orginator().firstName(), "Daniel");
    BOOST_CHECK_EQUAL(orderHeader.orginator().lastName(), "Lindh");
    BOOST_CHECK_EQUAL(orderHeader.orginator().companyName(), "Amivono AB");
    BOOST_CHECK_EQUAL(orderHeader.orginator().email(), "daniel@cybercow.se");
    BOOST_CHECK_EQUAL(orderHeader.orginator().webUrl(), "www.cybercow.se");

    // Check OrderRow
    BOOST_FOREACH(OrderHeader::t_OrderRow orderRows, orderHeader.orderRows())
    {
        if (orderRows.second.product().name() == "Z-Wave remote")
        {
            BOOST_CHECK_EQUAL(orderRows.second.product().name(), "Z-Wave remote");
            BOOST_CHECK_EQUAL(orderRows.second.product().description(), "This is a remote control");

            BOOST_CHECK_EQUAL(orderRows.second.product().manufacturer().firstName(), "Daniel");
            BOOST_CHECK_EQUAL(orderRows.second.product().manufacturer().lastName(), "Lindh");
            BOOST_CHECK_EQUAL(orderRows.second.product().manufacturer().companyName(), "Amivono AB");
            BOOST_CHECK_EQUAL(orderRows.second.product().manufacturer().email(), "daniel@cybercow.se");
            BOOST_CHECK_EQUAL(orderRows.second.product().manufacturer().webUrl(), "www.cybercow.se");

            BOOST_CHECK_EQUAL(orderRows.second.product().supplier().firstName(), "Daniel");
            BOOST_CHECK_EQUAL(orderRows.second.product().supplier().lastName(), "Lindh");
            BOOST_CHECK_EQUAL(orderRows.second.product().supplier().companyName(), "Amivono AB");
            BOOST_CHECK_EQUAL(orderRows.second.product().supplier().email(), "daniel@cybercow.se");
            BOOST_CHECK_EQUAL(orderRows.second.product().supplier().webUrl(), "www.cybercow.se");

            BOOST_CHECK_EQUAL(orderRows.second.product().externPartNo(), "XT100");
            BOOST_CHECK_EQUAL(orderRows.second.product().internPartNo(), "IN100");
            BOOST_CHECK_EQUAL(orderRows.second.product().minOrder(), 2);
            BOOST_CHECK_EQUAL(orderRows.second.product().deliveryTime(), 3);

            BOOST_CHECK_EQUAL(orderRows.second.product().productType().name(), "Remote");

            BOOST_CHECK(orderRows.second.product().supplierPrice() == Money(100, "SEK"));
            BOOST_CHECK(orderRows.second.product().salesPrice() ==  Money(120, "SEK"));
        }
        else
        {
            BOOST_CHECK_EQUAL(orderRows.second.product().name(), "Z-Wave dongle");
            BOOST_CHECK_EQUAL(orderRows.second.product().description(), "This is a z-wave usb dongle");

            BOOST_CHECK_EQUAL(orderRows.second.product().manufacturer().firstName(), "Daniel");
            BOOST_CHECK_EQUAL(orderRows.second.product().manufacturer().lastName(), "Lindh");
            BOOST_CHECK_EQUAL(orderRows.second.product().manufacturer().companyName(), "Amivono AB");
            BOOST_CHECK_EQUAL(orderRows.second.product().manufacturer().email(), "daniel@cybercow.se");
            BOOST_CHECK_EQUAL(orderRows.second.product().manufacturer().webUrl(), "www.cybercow.se");

            BOOST_CHECK_EQUAL(orderRows.second.product().supplier().firstName(), "Daniel");
            BOOST_CHECK_EQUAL(orderRows.second.product().supplier().lastName(), "Lindh");
            BOOST_CHECK_EQUAL(orderRows.second.product().supplier().companyName(), "Amivono AB");
            BOOST_CHECK_EQUAL(orderRows.second.product().supplier().email(), "daniel@cybercow.se");
            BOOST_CHECK_EQUAL(orderRows.second.product().supplier().webUrl(), "www.cybercow.se");

            BOOST_CHECK_EQUAL(orderRows.second.product().externPartNo(), "XT110");
            BOOST_CHECK_EQUAL(orderRows.second.product().internPartNo(), "IN110");
            BOOST_CHECK_EQUAL(orderRows.second.product().minOrder(), 4);
            BOOST_CHECK_EQUAL(orderRows.second.product().deliveryTime(), 5);

            BOOST_CHECK_EQUAL(orderRows.second.product().productType().name(), "DONGLE");

            BOOST_CHECK(orderRows.second.product().supplierPrice() == Money(123, "SEK"));
            BOOST_CHECK(orderRows.second.product().salesPrice() ==  Money(144, "SEK"));
        }
    }
}

BOOST_AUTO_TEST_CASE( OrderHeadersEmptyDatabase )
{
    ShopDb shopDb;
    OrderHeaders& orderHeaders = *shopDb.getOrderHeaders();

    // Remove everything in the database.
    orderHeaders.load();
    orderHeaders.destroy();

    BOOST_CHECK_EQUAL(orderHeaders.size(), 0);
}

BOOST_AUTO_TEST_CASE( OrderHeadersCartTest )
{
    //Setup
    Contact contact
    (
        "Daniel", "Lindh", "Amivono AB",
        "Linnegatan 7 ", "126 41", "STOCKHOLM",
        "073-626 54 40", "daniel@cybercow.se", "www.cybercow.se"
    );

    Product product1("Z-Wave remote", "This is a remote control", contact, contact, "XT100", "IN100", 2, 3, ProductType("Remote"), Money(100, "SEK"), Money(120, "SEK"));
    Product product2("Z-Wave dongle", "This is a z-wave usb dongle", contact, contact, "XT100", "IN100", 4, 5, ProductType("DONGLE"), Money(123, "SEK"), Money(144, "SEK"));

    Money expectedMoneyExVat(264, "SEK");
    Money expectedMoneyIncVat(264, "SEK");
    Money expectedMoneyIncVat2(528, "SEK");

    //Process
    OrderHeader cart;
    cart.addProduct(product1);
    cart.addProduct(product2);

    // Test
    BOOST_CHECK(cart.totalSalesPrice() == expectedMoneyExVat);

    cart.setShowIncVat(false);
    BOOST_CHECK(cart.totalSalesPrice() == expectedMoneyExVat);

    cart.setShowIncVat(true);
    BOOST_CHECK(cart.totalSalesPrice() == expectedMoneyIncVat);

    //Process second
    cart.addProduct(product1);
    cart.addProduct(product2);

    // Test second
    BOOST_CHECK(cart.totalSalesPrice() == expectedMoneyIncVat2);

    // Test third
    BOOST_FOREACH(OrderHeader::t_OrderRow orderRows, cart.orderRows())
    {
        if (orderRows.second.cartName() == std::string("2 - Z-Wave dongle"))
        {
            BOOST_CHECK_EQUAL(orderRows.second.cartName(), std::string("2 - Z-Wave dongle") );
        }
        else
        {
            BOOST_CHECK_EQUAL(orderRows.second.cartName(), std::string("2 - Z-Wave remote") );
        }
    }
}

BOOST_AUTO_TEST_CASE( OrderHeadersFullTest)
{
    // Setup products
    Contact company
    (
        "No", "Honesty", "Buffalo and Bullshit Corp",
        "Goldenrood 69", "44 444", "DUCKBORG", "+1-800-DO-YOU-FELL-LUCKY",
        "honesty@bullshit.com", "www.bullshit.com"
    );

    Product product1 = new Product
    (
        "Z-Wave remote", "This is a remote control",
        company, company, "XT100", "IN100", 2, 3, ProductType("Remote"),
        Money(100, "SEK"), Money(120, "SEK")
    );
    product1.save(*shopDb.getSession());

    Product product2 = new Product
    (
        "Z-Wave dongle", "This is a z-wave usb dongle",
        company, company, "XT110", "IN110", 4, 5, ProductType("DONGLE"),
        Money(123, "SEK"), Money(144, "SEK")
    );
    product2.save(*shopDb.getSession());

    // Setup user account
    User user = *shopDb.getUser();
    user.setUserName("arlukin");
    user.setPassword("password");
    user.contact() = Contact
    (
        "Daniel", "Lindh", "Amivono AB",
        "Linnegatan 7", "126 51", "STOCKHOLM", "+46-73-626 54 49",
        "daniel@cybercow.se", "www.cybercow.se"
    );

    user.save();

    // Setup cart
    OrderHeader cart;

    // Set buyer
    cart.orginator() = user.contact();

    // Add products
    cart.addOrderRow(OrderRow(NULL, NULL, product1, 2));
    cart.addOrderRow(OrderRow(NULL, NULL, product2, 2));

    // Store
    cart.save(*shopDb.getSession());

    // Test
    BOOST_CHECK_EQUAL(cart.orginator().firstName(), "Daniel");
    BOOST_CHECK_EQUAL(cart.orginator().lastName(), "Lindh");
    BOOST_CHECK_EQUAL(cart.orginator().companyName(), "Amivono AB");
    BOOST_CHECK_EQUAL(cart.orginator().email(), "daniel@cybercow.se");
    BOOST_CHECK_EQUAL(cart.orginator().webUrl(), "www.cybercow.se");

    // Clean up
    cart.destroy(*shopDb.getSession());
    user.destroy();
    product1.destroy(*shopDb.getSession());
    product2.destroy(*shopDb.getSession());

}
BOOST_AUTO_TEST_SUITE_END( )

// EOF
