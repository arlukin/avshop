add_library(avutils
    AVString.cpp
    AVDebug.cpp
    Image.cpp
)
target_link_libraries (avutils
        boost_filesystem.so
        ${EXTRA_LIBS}
)

set (EXTRA_LIBS ${EXTRA_LIBS} avutils)

install (TARGETS avutils DESTINATION bin)

SET_TARGET_PROPERTIES(
  avutils
PROPERTIES
  VERSION ${VERSION_SERIES}.${VERSION_MAJOR}.${VERSION_MINOR}
  SOVERSION ${SOVERSION}
  DEBUG_POSTFIX "d"
)

# Unit test
add_executable(avUtilsTest
        test/AVStringTest.cpp
        test/AVImageTest.cpp
        test/MainTest.cpp
)

target_link_libraries (avUtilsTest
        soci_mysql-gcc-3_0
        boost_unit_test_framework
        ${EXTRA_LIBS}
)

# Run all unittests
add_test (AvUtilsTest avUtilsTest)
