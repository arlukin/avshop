#define BOOST_TEST_NO_MAIN
#include <iostream>
using namespace std;

#include <boost/test/unit_test.hpp>

#include "general/ShopDb.h"
#include "products/ProductType.h"
#include "products/ProductTypes.h"

struct ProductTypeTestFixture
{
    ProductTypeTestFixture()
    {
    }
    ~ProductTypeTestFixture()
    {
    }

    ShopDb shopDb;
    static int productTypeId;
};

int ProductTypeTestFixture::productTypeId = 0;

BOOST_FIXTURE_TEST_SUITE( ProductTypeTestSuite, ProductTypeTestFixture )

BOOST_AUTO_TEST_CASE( ProductTypesTestTruncate )
{
    //Process
    ProductTypes productTypes(*shopDb.getSession());
    productTypes.destroy();

    // Test
   BOOST_CHECK_EQUAL(productTypes.count(), 0);
}

BOOST_AUTO_TEST_CASE( ProductTypesTestAddToDatabase )
{
    ShopDb shopDb;
    ProductTypes& productTypes = *shopDb.getProductTypes();

    productTypes.push_back(ProductType("REMOTE"));
    productTypes.push_back(ProductType("DONGLE"));
    productTypes.save();

    BOOST_CHECK_EQUAL(productTypes.size(), 2);

    ProductTypes::const_iterator productType = productTypes.begin();

    BOOST_CHECK_EQUAL(productType->name(), "REMOTE");

    ++productType;
    BOOST_CHECK_EQUAL(productType->name(), "DONGLE");
}

BOOST_AUTO_TEST_CASE( ProductTypesTestSelectFromDatabase )
{
    ShopDb shopDb;
    ProductTypes& productTypes = *shopDb.getProductTypes();

    productTypes.load();

    BOOST_CHECK_EQUAL(productTypes.size(), 2);

    ProductTypes::iterator productType = productTypes.begin();

    BOOST_CHECK_EQUAL(productType->name(), "REMOTE");

    ++productType;
    BOOST_CHECK_EQUAL(productType->name(), "DONGLE");
}

BOOST_AUTO_TEST_CASE( ProductsEmptyDatabase )
{
    ShopDb shopDb;
    ProductTypes& productTypes = *shopDb.getProductTypes();

    // Remove everything in the database.
    productTypes.load();
    productTypes.destroy();

    BOOST_CHECK_EQUAL(productTypes.size(), 0);
}

BOOST_AUTO_TEST_CASE( ProductTypeTestConstructor )
{
    //Process
    ProductType productType("USB-Dongle");

    // Test
    BOOST_CHECK_EQUAL(productType.name(), "USB-Dongle");
}

BOOST_AUTO_TEST_CASE( ProductTypeTestCreate )
{
    // Process 1
    ProductType productType;
    productType.setName("USB-Dongle");
    productType.save(*shopDb.getSession());
    productTypeId = productType.productTypeId();

    // Test 1
    BOOST_CHECK_EQUAL(productType.name(), "USB-Dongle");
}

BOOST_AUTO_TEST_CASE( ProductTypeTestLoad )
{
    // Process
    ProductType productType;
    productType.load(*shopDb.getSession(), productTypeId);

    // Test
    BOOST_CHECK_EQUAL(productType.name(), "USB-Dongle");
}

BOOST_AUTO_TEST_CASE( ProductTypeTestUpdate )
{
    // Process
    ProductType productType;
    productType.load(*shopDb.getSession(), productTypeId);
    productType.setName("Remote");
    productType.save(*shopDb.getSession());

    // Test
    BOOST_CHECK_EQUAL(productType.name(), "Remote");
}

BOOST_AUTO_TEST_CASE( ProductTypeTestUpdateLoad )
{
    // Process
    ProductType productType;
    productType.load(*shopDb.getSession(), productTypeId);

    // Test
    BOOST_CHECK_EQUAL(productType.name(), "Remote");
}

BOOST_AUTO_TEST_CASE( ProductTypeTestDestroy )
{
    // Process
    ProductType productType;
    productType.load(*shopDb.getSession(), productTypeId);
    productType.destroy(*shopDb.getSession());

    // Test
    BOOST_CHECK_EQUAL(productType.name(), "");
}

BOOST_AUTO_TEST_CASE( ProductTypeTestDestroyLoad )
{
    // Process
    ProductType productType;
    productType.load(*shopDb.getSession(), productTypeId);

    // Test
    BOOST_CHECK_EQUAL(productType.name(), "");
}

BOOST_AUTO_TEST_CASE( ProductTypeTestUniqueName)
{
    // Setup
    ShopDb shopDb;
    ProductTypes& productTypes = *shopDb.getProductTypes();

    // Process 1
    ProductType productType1;
    productType1.setName("USB-Dongle");
    productType1.save(*shopDb.getSession());
    int productTypeId1 = productType1.productTypeId();

    ProductType productType2;
    productType2.setName("USB-Dongle");
    productType2.save(*shopDb.getSession());
    int productTypeId2 = productType2.productTypeId();

    ProductType productType3;
    productType3.setName("Remote");
    productType3.save(*shopDb.getSession());

    // Test 1
    BOOST_CHECK_EQUAL(productTypeId1, productTypeId2);
    BOOST_CHECK_EQUAL(productTypes.count(), 2);
}

BOOST_AUTO_TEST_CASE( ProductTypesTestListAll)
{
    //Process / test
    ShopDb shopDb;
    ProductTypes& productTypes = *shopDb.getProductTypes();

    productTypes.load();
    for (ProductTypes::const_iterator productType = productTypes.begin();
        productType != productTypes.end();
        ++productType)
    {
        BOOST_CHECK(productType->name().size() > 0);
    }
}

BOOST_AUTO_TEST_SUITE_END( )

// EOF
