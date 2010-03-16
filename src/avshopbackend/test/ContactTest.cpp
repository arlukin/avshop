#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include "general/ShopDb.h"
#include "products/Contact.h"

BOOST_AUTO_TEST_SUITE (ContactTestSuite)

BOOST_AUTO_TEST_CASE( ContactTestConstructor )
{
    //Process
    Contact contact("Daniel", "Lindh", "Amivono AB",
                    "Linnegatan 7", "126 51", "STOCKHOLM", "+46-73-626 54 49",
                    "daniel@cybercow.se", "www.cybercow.se");

    // Test
    BOOST_CHECK_EQUAL(contact.firstName(), "Daniel");
    BOOST_CHECK_EQUAL(contact.lastName(), "Lindh");
    BOOST_CHECK_EQUAL(contact.companyName(), "Amivono AB");
    BOOST_CHECK_EQUAL(contact.address(), "Linnegatan 7");
    BOOST_CHECK_EQUAL(contact.zip(), "126 51");
    BOOST_CHECK_EQUAL(contact.city(), "STOCKHOLM");
    BOOST_CHECK_EQUAL(contact.phone(), "+46-73-626 54 49");
    BOOST_CHECK_EQUAL(contact.email(), "daniel@cybercow.se");
    BOOST_CHECK_EQUAL(contact.webUrl(), "www.cybercow.se");
}

BOOST_AUTO_TEST_CASE( ContactTest )
{
    // Setup 1
    ShopDb shopDb;

    // Process 1
    Contact contact;
    contact.setFirstName("Daniel");
    contact.setLastName("Lindh");
    contact.setCompanyName("Amivono AB");
    contact.setAddress("Linnegatan 7");
    contact.setZip("126 51");
    contact.setCity("STOCKHOLM");
    contact.setPhone("+46-73-626 54 49");
    contact.setEmail("daniel@cybercow.se");
    contact.setWebUrl("www.cybercow.se");
    contact.save(*shopDb.getSession());

    // Test 1
    BOOST_CHECK_EQUAL(contact.firstName(), "Daniel");
    BOOST_CHECK_EQUAL(contact.lastName(), "Lindh");
    BOOST_CHECK_EQUAL(contact.companyName(), "Amivono AB");
    BOOST_CHECK_EQUAL(contact.address(), "Linnegatan 7");
    BOOST_CHECK_EQUAL(contact.zip(), "126 51");
    BOOST_CHECK_EQUAL(contact.city(), "STOCKHOLM");
    BOOST_CHECK_EQUAL(contact.phone(), "+46-73-626 54 49");
    BOOST_CHECK_EQUAL(contact.email(), "daniel@cybercow.se");
    BOOST_CHECK_EQUAL(contact.webUrl(), "www.cybercow.se");  

    // Process 2
    Contact contactLoad;
    contactLoad.load(*shopDb.getSession(), contact.contactId());

    // Test 2
    BOOST_CHECK_EQUAL(contactLoad.firstName(), "Daniel");
    BOOST_CHECK_EQUAL(contactLoad.lastName(), "Lindh");
    BOOST_CHECK_EQUAL(contactLoad.companyName(), "Amivono AB");
    BOOST_CHECK_EQUAL(contact.address(), "Linnegatan 7");
    BOOST_CHECK_EQUAL(contact.zip(), "126 51");
    BOOST_CHECK_EQUAL(contact.city(), "STOCKHOLM");
    BOOST_CHECK_EQUAL(contact.phone(), "+46-73-626 54 49");
    BOOST_CHECK_EQUAL(contactLoad.email(), "daniel@cybercow.se");
    BOOST_CHECK_EQUAL(contactLoad.webUrl(), "www.cybercow.se");

    // Process 3
    contactLoad.setFirstName("Carina");
    contactLoad.setLastName("Neren");
    contactLoad.setCompanyName("Hest AB");
    contactLoad.setAddress("Linnegatan 3");
    contactLoad.setZip("129 32");
    contactLoad.setCity("HÄGERSTEN");
    contactLoad.setPhone("+1-800-more cows");
    contactLoad.setEmail("carina@cybercow.se");
    contactLoad.setWebUrl("sarina.cybercow.se");
    contactLoad.save(*shopDb.getSession());

    // Test 3
    BOOST_CHECK_EQUAL(contactLoad.firstName(), "Carina");
    BOOST_CHECK_EQUAL(contactLoad.lastName(), "Neren");
    BOOST_CHECK_EQUAL(contactLoad.companyName(), "Hest AB");
    BOOST_CHECK_EQUAL(contactLoad.address(), "Linnegatan 3");
    BOOST_CHECK_EQUAL(contactLoad.zip(), "129 32");
    BOOST_CHECK_EQUAL(contactLoad.city(), "HÄGERSTEN");
    BOOST_CHECK_EQUAL(contactLoad.phone(), "+1-800-more cows");
    BOOST_CHECK_EQUAL(contactLoad.email(), "carina@cybercow.se");
    BOOST_CHECK_EQUAL(contactLoad.webUrl(), "sarina.cybercow.se");

    // Process 4
    Contact contactLoadUpdated;
    contactLoadUpdated.load(*shopDb.getSession(), contact.contactId());

    // Test 4
	BOOST_CHECK_EQUAL(contactLoadUpdated.firstName(), "Carina");
    BOOST_CHECK_EQUAL(contactLoadUpdated.lastName(), "Neren");
    BOOST_CHECK_EQUAL(contactLoadUpdated.companyName(), "Hest AB");
    BOOST_CHECK_EQUAL(contactLoadUpdated.address(), "Linnegatan 3");
    BOOST_CHECK_EQUAL(contactLoadUpdated.zip(), "129 32");
    BOOST_CHECK_EQUAL(contactLoadUpdated.city(), "HÄGERSTEN");
    BOOST_CHECK_EQUAL(contactLoadUpdated.phone(), "+1-800-more cows");
    BOOST_CHECK_EQUAL(contactLoadUpdated.email(), "carina@cybercow.se");
    BOOST_CHECK_EQUAL(contactLoadUpdated.webUrl(), "sarina.cybercow.se");

    // Process 5
    contactLoadUpdated.destroy(*shopDb.getSession());

    // Test 5
    BOOST_CHECK_EQUAL(contactLoadUpdated.firstName(), "");
    BOOST_CHECK_EQUAL(contactLoadUpdated.lastName(), "");
    BOOST_CHECK_EQUAL(contactLoadUpdated.companyName(), "");
    BOOST_CHECK_EQUAL(contactLoadUpdated.address(), "");
    BOOST_CHECK_EQUAL(contactLoadUpdated.zip(), "");
    BOOST_CHECK_EQUAL(contactLoadUpdated.city(), "");
    BOOST_CHECK_EQUAL(contactLoadUpdated.phone(), "");
    BOOST_CHECK_EQUAL(contactLoadUpdated.email(), "");
    BOOST_CHECK_EQUAL(contactLoadUpdated.webUrl(), "");
}

BOOST_AUTO_TEST_CASE( ContactsEmptyDatabase )
{
    ShopDb shopDb;
    Contact& contact = *shopDb.getContact();

    // Remove everything in the database.
    contact.load(*shopDb.getSession(), 1);
    contact.destroy(*shopDb.getSession());

    // Test
    BOOST_CHECK_EQUAL(contact.firstName(), "");
    BOOST_CHECK_EQUAL(contact.lastName(), "");
    BOOST_CHECK_EQUAL(contact.companyName(), "");
    BOOST_CHECK_EQUAL(contact.address(), "");
    BOOST_CHECK_EQUAL(contact.zip(), "");
    BOOST_CHECK_EQUAL(contact.city(), "");
    BOOST_CHECK_EQUAL(contact.phone(), "");
    BOOST_CHECK_EQUAL(contact.email(), "");
    BOOST_CHECK_EQUAL(contact.webUrl(), "");
}

BOOST_AUTO_TEST_SUITE_END( )

// EOF
