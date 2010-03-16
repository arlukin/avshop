# add the binary tree to the search path for include files
# so that we will find version.h
include_directories ("${PROJECT_BINARY_DIR}")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "version.h.in"
  "${PROJECT_BINARY_DIR}/version.h"
)

include_directories ("/usr/include/soci/")
include_directories ("/usr/include/mysql/")
include_directories ("avutils")
include_directories ("avshopbackend")
include_directories ("avshop")
SUBDIRS(avutils avshopbackend avshop avshopdbinstall)
