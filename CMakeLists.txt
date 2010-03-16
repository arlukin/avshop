cmake_minimum_required (VERSION 2.6)
project (avShop)

# The version number.
SET(VERSION_SERIES 0)
SET(VERSION_MAJOR 0)
SET(VERSION_MINOR 1)

SET(SOVERSION 1)
                                                     
SET( CMAKE_INSTALL_PREFIX "../approot/" CACHE STRING
"Where to install the app" FORCE )

# All libs will be build for dynamic loading.
SET(BUILD_SHARED_LIBS "ON" CACHE BOOL "Build .so files." FORCE)

#
SET(CMAKE_BUILD_TYPE Debug)

# Enables "make test".
enable_testing ()

SUBDIRS(src)

install (FILES CHANGEDLOG DESTINATION .)

# @todo:
# include all resource files in the install.
# install (FILES MathFunctions.h DESTINATION var/www)
# INSTALL_FILES(/include/Wt/Chart "^W.*[^C~]$")

