# - Try to find LibXML++ 2.6
# Once done, this will define
#
#  LibXML++_FOUND - system has LibXML++
#  LibXML++_INCLUDE_DIRS - the LibXML++ include directories
#  LibXML++_LIBRARIES - link these to use LibXML++

include(LibFindMacros)

# Dependencies
if(LibXML++_PATH)
    list(APPEND LibXML2_PATH ${LibXML++_PATH})
endif()
libfind_package(LibXML++ LibXML2)
libfind_package(LibXML++ Glibmm)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(LibXML++_PKGCONF libxml++-2.6)

# Main include dir
find_path(LibXML++_INCLUDE_DIR
  NAMES libxml++/libxml++.h
  PATHS ${LibXML++_PKGCONF_INCLUDE_DIRS} ${LibXML++_PATH}/include
  PATH_SUFFIXES libxml++
)

# Glib-related libraries also use a separate config header, which is in lib dir
find_path(LibXML++Config_INCLUDE_DIR
  NAMES libxml++config.h
  PATHS ${LibXML++_PKGCONF_INCLUDE_DIRS} /usr ${LibXML++_PATH}/lib/libxml++-2.6/include
  PATH_SUFFIXES lib/libxml++-2.6/include ../lib/libxml++-2.6/include
)

# Finally the library itself
find_library(LibXML++_LIBRARY
  NAMES xml++-2.6 xml++${SYNFIG_MSVS_STAMP}-2_6
  PATHS ${LibXML++_PKGCONF_LIBRARY_DIRS} ${LibXML++_PATH}/lib
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(LibXML++_PROCESS_INCLUDES LibXML++_INCLUDE_DIR LibXML++Config_INCLUDE_DIR LibXML2_INCLUDE_DIRS Glibmm_INCLUDE_DIRS)
set(LibXML++_PROCESS_LIBS LibXML++_LIBRARY LibXML2_LIBRARIES Glibmm_LIBRARIES)
libfind_process(LibXML++)

