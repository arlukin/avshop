#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include "products/Money.h"

BOOST_AUTO_TEST_SUITE (MoneyTestSuite)

BOOST_AUTO_TEST_CASE( MoneyTestConstrucor )
{
  // Set up
  const double amount = 1234.5678;
  const std::string currency( "SEK" );
  const Money moneyEmpty;

  // Process
  Money money1( amount, currency );
  Money money2( money1 );

  // Check
  BOOST_CHECK_EQUAL( 0, moneyEmpty.amount() );
  BOOST_CHECK_EQUAL( "", moneyEmpty.currency() );

  BOOST_CHECK_EQUAL( amount, money1.amount() );
  BOOST_CHECK_EQUAL( currency, money1.currency() );

  BOOST_CHECK_EQUAL( amount, money2.amount() );
  BOOST_CHECK_EQUAL( currency, money2.currency() );

  BOOST_CHECK_EQUAL( std::string("1234.5678 SEK"), money2.amountFmt());
}

BOOST_AUTO_TEST_CASE( MoneyTestEqual )
{
  // Set up
  const Money money123SEK( 123, "SEK" );
  const Money money123USD( 123, "USD" );
  const Money money12SEK( 12, "SEK" );
  const Money money12USD( 12, "USD" );

  // Process & Check
  BOOST_CHECK( money123SEK == money123SEK );  // ==
  BOOST_CHECK( money12SEK != money123SEK );   // != amount
  BOOST_CHECK( money123USD != money123SEK );  // != currency
  BOOST_CHECK( money12USD != money123SEK );    // != currency and != amount
}

BOOST_AUTO_TEST_CASE( MoneyTestAdd )
{
  // Set up
  const Money money12SEK( 12, "SEK" );
  const Money expectedMoney( 135, "SEK" );

  // Process
  Money money( 123, "SEK" );
  Money moneyAdd = money + money12SEK;
  money += money12SEK;


  // Check
  BOOST_CHECK( expectedMoney == money );
  BOOST_CHECK( expectedMoney == moneyAdd );
  BOOST_CHECK( &money == &(money += money12SEK) );  //  returns ref. on 'this'.
}

BOOST_AUTO_TEST_CASE( MoneyTestSub )
{
  // Set up
  const Money money12SEK( 12, "SEK" );
  const Money expectedMoney( 111, "SEK" );

  // Process
  Money money( 123, "SEK" );
  Money moneySub = money - money12SEK;
  money -= money12SEK;

  // Check
  BOOST_CHECK( expectedMoney == money );
  BOOST_CHECK( expectedMoney == moneySub );
  BOOST_CHECK( &money == &(money -= money12SEK) );  // returns ref. on 'this'.
}

BOOST_AUTO_TEST_CASE( MoneyTestMult )
{
  // Set up
  const Money money10SEK( 10, "SEK" );
  const Money expectedMoney( 100, "SEK" );

  // Process
  Money money( 10, "SEK" );
  Money moneyMul = money * money10SEK;
  money *= money10SEK;

  // Check
  BOOST_CHECK( expectedMoney == money );
  BOOST_CHECK( expectedMoney == moneyMul );
  BOOST_CHECK( &money == &(money *= money10SEK) );  // returns ref. on 'this'.
}

BOOST_AUTO_TEST_CASE( MoneyTestDiv )
{
  // Set up
  const Money money10SEK( 5, "SEK" );
  const Money expectedMoney( 2, "SEK" );

  // Process
  Money money( 10, "SEK" );
  Money moneyDiv = money / money10SEK;
  money /= money10SEK;

  // Check
  BOOST_CHECK( expectedMoney == money );
  BOOST_CHECK( expectedMoney == moneyDiv );
  BOOST_CHECK( &money == &(money /= money10SEK) );  // returns ref. on 'this'.
}

BOOST_AUTO_TEST_CASE( MoneyTestMult2 )
{
  // Set up
  const Money expectedMoney( 20, "SEK" );
  const Money expectedMoney2( 40, "SEK" );
  const int multiple = 2;

  // Process
  Money money10SEK( 10, "SEK" );
  money10SEK *= multiple;

  // Check
  BOOST_CHECK( money10SEK == expectedMoney );
  BOOST_CHECK( ((money10SEK * multiple) == expectedMoney2) );
}


BOOST_AUTO_TEST_CASE( MoneyTestAddThrow )
{
  // Set up
  const Money money123SEK( 123, "SEK" );

  // Process
  Money money( 123, "USD" );
  BOOST_CHECK_THROW (money += money123SEK, IncompatibleMoneyError);

  BOOST_CHECK_THROW ( {Money( 123, "FF"); }; , IncompatibleMoneyError);
}

BOOST_AUTO_TEST_SUITE_END( )
// EOF
