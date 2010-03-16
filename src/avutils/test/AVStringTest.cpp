#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include "AVString.h"

BOOST_AUTO_TEST_SUITE (AVStringTestSuite)

BOOST_AUTO_TEST_CASE( AVStringTestConstructor )
{
//    //Process
//    std::string stdstr("daniel");
//    av::String str(stdstr);
//
//    std::string retstr = str;
//    retstr = "daniel2";
//
//    // Test
//    BOOST_CHECK_EQUAL(stdstr, retstr);
}

void AVStringTestOperatorTestFunc(std::string& str) {};

BOOST_AUTO_TEST_CASE( AVStringTestOperator )
{
//    // Setup
//    av::String str("abcdefghijklmnopqrstuvwxyzåäö");
//    av::String strCp;
//
//    // Process
//    str = "abcåäö";
//    str += "abc";
//    strCp = strCp + "defg";
//    str += " userName = '" + strCp;
//    str += " userName = '" + strCp + "' AND";
//
//    AVStringTestOperatorTestFunc(str);
//
//    Wt::WString wstr = str;
//
//    // Test
//    //BOOST_CHECK_EQUAL(str, "abcåäö");;
}

BOOST_AUTO_TEST_SUITE_END( )

// EOF
