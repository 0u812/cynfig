# - Try to find Png
# Once done, this will define
#
#  Png_FOUND - system has Png
#  Png_INCLUDE_DIRS - the Png include directories
#  Png_LIBRARIES - link these to use Png
#
# See documentation on how to write CMake scripts at
# http://www.cmake.org/Wiki/CMake:How_To_Find_Libraries

include(LibFindMacros)

libfind_pkg_check_modules(Png_PKGCONF libpng>=1.4)

find_library(Png_LIBRARY NAMES png16
    HINTS ${PC_PNG_LIBDIR} ${Png_PKGCONF_LIBRARY_DIRS})
    
if(NOT Png_LIBRARY)
    find_library(Png_LIBRARY NAMES png15
        HINTS ${PC_PNG_LIBDIR} ${Png_PKGCONF_LIBRARY_DIRS})
endif()
if(NOT Png_LIBRARY)
    find_library(Png_LIBRARY NAMES png14
        HINTS ${PC_PNG_LIBDIR} ${Png_PKGCONF_LIBRARY_DIRS})
endif()

find_path(Png_INCLUDE_DIR
  NAMES pngconf.h
  PATHS ${Png_PKGCONF_INCLUDE_DIRS}
)

set(Png_PROCESS_INCLUDES Png_INCLUDE_DIR)
set(Png_PROCESS_LIBS Png_LIBRARY)
libfind_process(Png)

