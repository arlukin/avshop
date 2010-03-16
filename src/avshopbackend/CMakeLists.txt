add_library(avshopbackend 
	general/DBTable.cpp
	general/ShopDb.cpp
	products/Contact.cpp
	products/Money.cpp
	products/OrderHeader.cpp
	products/OrderHeaders.cpp
	products/OrderRow.cpp
	products/Product.cpp
	products/ProductType.cpp
        products/ProductTypes.cpp
	products/Products.cpp	
        user/UserAccount.cpp
        user/User.cpp
        user/Action.cpp
        user/Actions.cpp
        user/ActionGroup.cpp
)

target_link_libraries (avshopbackend 
	soci_mysql-gcc-3_0
        avutils
	${EXTRA_LIBS}
)

set (EXTRA_LIBS ${EXTRA_LIBS} avshopbackend)

install (TARGETS avshopbackend DESTINATION bin)

SET_TARGET_PROPERTIES(
  avshopbackend
PROPERTIES
  VERSION ${VERSION_SERIES}.${VERSION_MAJOR}.${VERSION_MINOR}
  SOVERSION ${SOVERSION}
  DEBUG_POSTFIX "d"
)

# Unit test
add_executable(avShopBackEndTest        
        test/ContactTest.cpp
	test/MainTest.cpp
	test/MoneyTest.cpp
	test/OrderTest.cpp        
	test/ProductTest.cpp
	test/ProductTypeTest.cpp    
        test/UserTest.cpp        
)

target_link_libraries (avShopBackEndTest 
	boost_unit_test_framework 	
	${EXTRA_LIBS}
)

# Run all unittests
add_test (AvShopBackEndTest avShopBackEndTest)
