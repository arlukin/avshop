#include <iostream>
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "Image.h"

BOOST_AUTO_TEST_SUITE (AVImageTestSuite)

BOOST_AUTO_TEST_CASE( AVImageTestConstructor )
{
    // Setup
    std::string cwd = boost::filesystem::current_path().string() + "/";
    //Process
    av::Image image("src/", "avutils/test/resource/", "orginalLogo.gif");

    // Test
    BOOST_CHECK_EQUAL(image.getFullUrl(),       "avutils/test/resource/orginalLogo.gif");
    BOOST_CHECK_EQUAL(image.getThumbUrl(),      "avutils/test/resource/thumb/orginalLogo.jpg");

    //BOOST_CHECK_EQUAL(image.getFullPath(),      cwd + "src/avutils/test/resource/orginalLogo.gif");
    //BOOST_CHECK_EQUAL(image.getThumbFullPath(), cwd + "src/avutils/test/resource/thumb/orginalLogo.jpg");
}

BOOST_AUTO_TEST_SUITE_END( )

// EOF
