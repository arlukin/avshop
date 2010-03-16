#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include "user/User.h"
#include "user/Action.h"
#include "user/Actions.h"
#include "user/ActionGroup.h"
using namespace av;

struct UserTestSuiteFixture
{
    UserTestSuiteFixture()
    {
    }

    ~UserTestSuiteFixture()
    {
    }

    ShopDb shopDb;

    static int userId;
    static int actionGroupId;
};

int UserTestSuiteFixture::userId;
int UserTestSuiteFixture::actionGroupId;

BOOST_FIXTURE_TEST_SUITE (UserTestSuite, UserTestSuiteFixture)

BOOST_AUTO_TEST_CASE( UserAddTest )
{
    // Setup

    // Process
    User user = *shopDb.getUser();
    user.setUserName("Case");
    user.setPassword("Wintermute");
    user.contact() = Contact("Henry Dorsett", "Case", "Tessier-Ashpool S.A.",
        "Villa Straylight", "126 51", "Freeside space station", "+1-800-CYBERSPACE",
        "case@tessierashpool.com", "www.cybercow.se");

    user.save();

    // Test
    BOOST_WARN_GT(user.userAccountId(), 0);
    BOOST_CHECK_EQUAL(user.userName(), "Case");
    BOOST_CHECK_EQUAL(user.contact().firstName(), "Henry Dorsett");
    BOOST_CHECK_EQUAL(user.contact().lastName(), "Case");
    BOOST_CHECK_EQUAL(user.contact().companyName(), "Tessier-Ashpool S.A.");
    BOOST_CHECK_EQUAL(user.contact().address(), "Villa Straylight");
    BOOST_CHECK_EQUAL(user.contact().zip(), "126 51");
    BOOST_CHECK_EQUAL(user.contact().city(), "Freeside space station");
    BOOST_CHECK_EQUAL(user.contact().phone(), "+1-800-CYBERSPACE");
    BOOST_CHECK_EQUAL(user.contact().email(), "case@tessierashpool.com");
    BOOST_CHECK_EQUAL(user.contact().webUrl(), "www.cybercow.se");

    //
    userId = user.userAccountId();
}

BOOST_AUTO_TEST_CASE( UserLoginNoPermissionTest )
{
    // Setup

    // Process
    User user = *shopDb.getUser();
    user.login("Case", "Wintermute");

    // Test
    BOOST_CHECK_EQUAL(user.isLoggedIn(), true);
    BOOST_CHECK_EQUAL(user.isReadable(Action::UserProfile), false);
    BOOST_CHECK_EQUAL(user.isWriteable(Action::UserProfile), false);
    BOOST_CHECK_EQUAL(user.isDeletable(Action::UserProfile), false);
    BOOST_CHECK_EQUAL(user.hasAccess(Action::UserProfile), false);

    BOOST_CHECK_EQUAL(user.userAccountId(), userId);
    BOOST_CHECK_EQUAL(user.userName(), "Case");
    BOOST_CHECK_EQUAL(user.contact().firstName(), "Henry Dorsett");
    BOOST_CHECK_EQUAL(user.contact().lastName(), "Case");
    BOOST_CHECK_EQUAL(user.contact().companyName(), "Tessier-Ashpool S.A.");
    BOOST_CHECK_EQUAL(user.contact().address(), "Villa Straylight");
    BOOST_CHECK_EQUAL(user.contact().zip(), "126 51");
    BOOST_CHECK_EQUAL(user.contact().city(), "Freeside space station");
    BOOST_CHECK_EQUAL(user.contact().phone(), "+1-800-CYBERSPACE");
    BOOST_CHECK_EQUAL(user.contact().email(), "case@tessierashpool.com");
    BOOST_CHECK_EQUAL(user.contact().webUrl(), "www.cybercow.se");
}

BOOST_AUTO_TEST_CASE( UserLoginFailedTest )
{
    // Process
    User user = *shopDb.getUser();
    user.login("arlufgasdfasdfkin", "pasasdfasdfasdfsword");

    // Test
    BOOST_CHECK_EQUAL(user.isLoggedIn(), false);
}

BOOST_AUTO_TEST_CASE( UserActionTest )
{
    // Setup

    // Process
    Actions actions(shopDb.getSession());
    actions.setAction(Action::UserProfile, ALL);
    actions.setAction(Action::ShopProperties, READ);
    actions.setAction(Action::ShopProperties, WRITE);
    actions.setAction(Action::Orders, READ | WRITE);

    // Test
    BOOST_CHECK_EQUAL(actions.isReadable(Action::UserProfile), true);
    BOOST_CHECK_EQUAL(actions.isWriteable(Action::UserProfile), true);
    BOOST_CHECK_EQUAL(actions.isDeletable(Action::UserProfile), true);
    BOOST_CHECK_EQUAL(actions.hasAccess(Action::UserProfile), true);

    BOOST_CHECK_EQUAL(actions.isReadable(Action::ShopProperties), false);
    BOOST_CHECK_EQUAL(actions.isWriteable(Action::ShopProperties), true);
    BOOST_CHECK_EQUAL(actions.isDeletable(Action::ShopProperties), false);
    BOOST_CHECK_EQUAL(actions.hasAccess(Action::ShopProperties), false);

    BOOST_CHECK_EQUAL(actions.isReadable(Action::Orders), true);
    BOOST_CHECK_EQUAL(actions.isWriteable(Action::Orders), true);
    BOOST_CHECK_EQUAL(actions.isDeletable(Action::Orders), false);
    BOOST_CHECK_EQUAL(actions.hasAccess(Action::Orders), false);
}

BOOST_AUTO_TEST_CASE( UserActionGroupAddTest )
{
    // Setup
    User user = *shopDb.getUser();
    user.load(userId);

    // Process
    ActionGroup actionGroup = *shopDb.getActionGroup();
    actionGroup.setName("Standard access");
    actionGroup.setAction(Action::UserProfile, ALL);
    actionGroup.setAction(Action::ShopProperties, READ);
    actionGroup.setAction(Action::ShopProperties, WRITE);
    actionGroup.setAction(Action::Orders, READ | WRITE);
    actionGroup.addUser(user.userAccountId());
    actionGroup.save();

    // Test
    BOOST_WARN_GT(actionGroup.actionGroupId(), 0);

    actionGroupId = actionGroup.actionGroupId();
}

BOOST_AUTO_TEST_CASE( UserActionGroupLoadTest )
{
    // Setup

    // Process
    ActionGroup actionGroup = *shopDb.getActionGroup();
    actionGroup.load(actionGroupId);

    // Test
    BOOST_CHECK_EQUAL(actionGroup.actionGroupId(), actionGroupId);
    BOOST_CHECK_EQUAL(actionGroup.name(), "Standard access");
}

BOOST_AUTO_TEST_CASE( UserLoginTest )
{
    // Setup

    // Process
    User user = *shopDb.getUser();
    user.login("Case", "Wintermute");

    // Test
    BOOST_CHECK_EQUAL(user.isLoggedIn(), true);    
    BOOST_CHECK_EQUAL(user.isReadable(Action::UserProfile), true);
    BOOST_CHECK_EQUAL(user.isWriteable(Action::UserProfile), true);
    BOOST_CHECK_EQUAL(user.isDeletable(Action::UserProfile), true);
    BOOST_CHECK_EQUAL(user.hasAccess(Action::UserProfile), true);

    BOOST_CHECK_EQUAL(user.isReadable(Action::ShopProperties), false);
    BOOST_CHECK_EQUAL(user.isWriteable(Action::ShopProperties), true);
    BOOST_CHECK_EQUAL(user.isDeletable(Action::ShopProperties), false);
    BOOST_CHECK_EQUAL(user.hasAccess(Action::ShopProperties), false);

    BOOST_CHECK_EQUAL(user.isReadable(Action::Orders), true);
    BOOST_CHECK_EQUAL(user.isWriteable(Action::Orders), true);
    BOOST_CHECK_EQUAL(user.isDeletable(Action::Orders), false);
    BOOST_CHECK_EQUAL(user.hasAccess(Action::Orders), false);

    BOOST_CHECK_EQUAL(user.userAccountId(), userId);
    BOOST_CHECK_EQUAL(user.userName(), "Case");
    BOOST_CHECK_EQUAL(user.contact().firstName(), "Henry Dorsett");
    BOOST_CHECK_EQUAL(user.contact().lastName(), "Case");
    BOOST_CHECK_EQUAL(user.contact().companyName(), "Tessier-Ashpool S.A.");
    BOOST_CHECK_EQUAL(user.contact().address(), "Villa Straylight");
    BOOST_CHECK_EQUAL(user.contact().zip(), "126 51");
    BOOST_CHECK_EQUAL(user.contact().city(), "Freeside space station");
    BOOST_CHECK_EQUAL(user.contact().phone(), "+1-800-CYBERSPACE");
    BOOST_CHECK_EQUAL(user.contact().email(), "case@tessierashpool.com");
    BOOST_CHECK_EQUAL(user.contact().webUrl(), "www.cybercow.se");
}

BOOST_AUTO_TEST_CASE( UserUpdateTest )
{
    // Setup
    User user = *shopDb.getUser();
    user.login("Case", "Wintermute");

    // Process
    user.setUserName("Molly");
    user.setPassword("razorgirl");
    user.contact().setFirstName("Molly");
    user.contact().setLastName("Millons");
    user.contact().setCompanyName("Molly Security S.A.");
    user.contact().setAddress("Streets of memmory 123");
    user.contact().setZip("455 5123");
    user.contact().setCity("Chiba city");
    user.contact().setPhone("+1-800-RAZOR1911");
    user.contact().setEmail("molly@tessierashpool.com");
    user.contact().setWebUrl("cybercow.se");

    user.save();

    // Test
    BOOST_CHECK_EQUAL(user.isLoggedIn(), true);
    BOOST_CHECK_EQUAL(user.isReadable(Action::UserProfile), true);
    BOOST_CHECK_EQUAL(user.isWriteable(Action::UserProfile), true);
    BOOST_CHECK_EQUAL(user.isDeletable(Action::UserProfile), true);
    BOOST_CHECK_EQUAL(user.hasAccess(Action::UserProfile), true);

    BOOST_CHECK_EQUAL(user.isReadable(Action::ShopProperties), false);
    BOOST_CHECK_EQUAL(user.isWriteable(Action::ShopProperties), true);
    BOOST_CHECK_EQUAL(user.isDeletable(Action::ShopProperties), false);
    BOOST_CHECK_EQUAL(user.hasAccess(Action::ShopProperties), false);

    BOOST_CHECK_EQUAL(user.isReadable(Action::Orders), true);
    BOOST_CHECK_EQUAL(user.isWriteable(Action::Orders), true);
    BOOST_CHECK_EQUAL(user.isDeletable(Action::Orders), false);
    BOOST_CHECK_EQUAL(user.hasAccess(Action::Orders), false);

    BOOST_CHECK_EQUAL(user.userAccountId(), userId);
    BOOST_CHECK_EQUAL(user.userName(), "Molly");
    BOOST_CHECK_EQUAL(user.contact().firstName(), "Molly");
    BOOST_CHECK_EQUAL(user.contact().lastName(), "Millons");
    BOOST_CHECK_EQUAL(user.contact().companyName(), "Molly Security S.A.");
    BOOST_CHECK_EQUAL(user.contact().address(), "Streets of memmory 123");
    BOOST_CHECK_EQUAL(user.contact().zip(), "455 5123");
    BOOST_CHECK_EQUAL(user.contact().city(), "Chiba city");
    BOOST_CHECK_EQUAL(user.contact().phone(), "+1-800-RAZOR1911");
    BOOST_CHECK_EQUAL(user.contact().email(), "molly@tessierashpool.com");
    BOOST_CHECK_EQUAL(user.contact().webUrl(), "cybercow.se");
}

BOOST_AUTO_TEST_CASE( UserUpdateLoadTest )
{
    // Setup

    // Process
    User user = *shopDb.getUser();
    user.login("Molly", "razorgirl");

    // Test
    BOOST_CHECK_EQUAL(user.isLoggedIn(), true);
    BOOST_CHECK_EQUAL(user.isReadable(Action::UserProfile), true);
    BOOST_CHECK_EQUAL(user.isWriteable(Action::UserProfile), true);
    BOOST_CHECK_EQUAL(user.isDeletable(Action::UserProfile), true);
    BOOST_CHECK_EQUAL(user.hasAccess(Action::UserProfile), true);

    BOOST_CHECK_EQUAL(user.isReadable(Action::ShopProperties), false);
    BOOST_CHECK_EQUAL(user.isWriteable(Action::ShopProperties), true);
    BOOST_CHECK_EQUAL(user.isDeletable(Action::ShopProperties), false);
    BOOST_CHECK_EQUAL(user.hasAccess(Action::ShopProperties), false);

    BOOST_CHECK_EQUAL(user.isReadable(Action::Orders), true);
    BOOST_CHECK_EQUAL(user.isWriteable(Action::Orders), true);
    BOOST_CHECK_EQUAL(user.isDeletable(Action::Orders), false);
    BOOST_CHECK_EQUAL(user.hasAccess(Action::Orders), false);

    BOOST_CHECK_EQUAL(user.userAccountId(), userId);
    BOOST_CHECK_EQUAL(user.userName(), "Molly");
    BOOST_CHECK_EQUAL(user.contact().firstName(), "Molly");
    BOOST_CHECK_EQUAL(user.contact().lastName(), "Millons");
    BOOST_CHECK_EQUAL(user.contact().companyName(), "Molly Security S.A.");
    BOOST_CHECK_EQUAL(user.contact().address(), "Streets of memmory 123");
    BOOST_CHECK_EQUAL(user.contact().zip(), "455 5123");
    BOOST_CHECK_EQUAL(user.contact().city(), "Chiba city");
    BOOST_CHECK_EQUAL(user.contact().phone(), "+1-800-RAZOR1911");
    BOOST_CHECK_EQUAL(user.contact().email(), "molly@tessierashpool.com");
    BOOST_CHECK_EQUAL(user.contact().webUrl(), "cybercow.se");
}

BOOST_AUTO_TEST_CASE( UserDeleteTest )
{
    // Setup
    User userDelete = *shopDb.getUser();    
    userDelete.login("Molly", "razorgirl");

    // Process
    userDelete.destroy();

    // Test
    BOOST_CHECK_EQUAL(userDelete.isReadable(Action::ShopProperties), false);
    BOOST_CHECK_EQUAL(userDelete.isWriteable(Action::ShopProperties), false);
    BOOST_CHECK_EQUAL(userDelete.isDeletable(Action::ShopProperties), false);
    BOOST_CHECK_EQUAL(userDelete.hasAccess(Action::ShopProperties), false);

    User user = *shopDb.getUser();
    user.login("Molly", "razorgirl");
    BOOST_CHECK_EQUAL(user.isLoggedIn(), false);
    BOOST_CHECK_EQUAL(user.isReadable(Action::ShopProperties), false);
    BOOST_CHECK_EQUAL(user.isWriteable(Action::ShopProperties), false);
    BOOST_CHECK_EQUAL(user.isDeletable(Action::ShopProperties), false);
    BOOST_CHECK_EQUAL(user.hasAccess(Action::ShopProperties), false);
}

BOOST_AUTO_TEST_CASE( UserActionGroupDeleteTest )
{
    // Setup
    ActionGroup actionGroupDelete = *shopDb.getActionGroup();
    actionGroupDelete.load(actionGroupId);

    // Process
    actionGroupDelete.destroy();

    // Test
    BOOST_CHECK_EQUAL(actionGroupDelete.actionGroupId(), false);

    ActionGroup actionGroup = *shopDb.getActionGroup();
    actionGroup.load(actionGroupId);

    BOOST_CHECK_EQUAL(actionGroup.actionGroupId(), false);
}

BOOST_AUTO_TEST_SUITE_END( )

// EOF

