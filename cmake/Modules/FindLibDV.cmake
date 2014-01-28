# - Try to find LibDV 6.4.2
# Once done, this will define
#
#  LibDV_FOUND - system has LibDV
#  LibDV_INCLUDE_DIRS - the LibDV include directories
#  LibDV_LIBRARIES - link these to use LibDV

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(LibDV_PKGCONF libdv)

find_library(LIBDV_LIBRARY NAMES dv
    HINTS ${PC_LIBDV_LIBDIR} ${PC_LIBDV_LIBRARY_DIRS})

find_path(LIBDV_INCLUDE libdv/dv.h
    HINTS ${PC_LIBDV_INCLUDEDIR} ${PC_LIBDV_INCLUDE_DIRS}
    PATH_SUFFIXES libdv)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
# set(LibDV_PROCESS_INCLUDES LibDV_INCLUDE_DIR )
# set(LibDV_PROCESS_LIBS LibDV_LIBRARY )
# libfind_process(LibDV)

