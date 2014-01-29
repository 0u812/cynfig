# - Try to find FreeType2
# Once done, this will define
#
#  FreeType2_FOUND - system has FreeType2
#  FreeType2_INCLUDE_DIRS - the FreeType2 include directories
#  FreeType2_LIBRARIES - link these to use FreeType2
#
# See documentation on how to write CMake scripts at
# http://www.cmake.org/Wiki/CMake:How_To_Find_Libraries

include(LibFindMacros)

pkg_check_modules(PC_FREETYPE2 REQUIRED freetype2)
pkg_check_modules(PC_FREETYPE2 REQUIRED xft)

find_library(FreeType2_LIBRARY NAMES freetype
    HINTS ${PC_FREETYPE2_LIBDIR} ${PC_FREETYPE2_LIBRARY_DIRS})

find_path(FreeType2_INCLUDE_DIR freetype/freetype.h
    HINTS ${PC_FREETYPE2_INCLUDEDIR} ${PC_FREETYPE2_INCLUDE_DIRS}
    PATH_SUFFIXES freetype)

set(FreeType2_PROCESS_INCLUDES FreeType2_INCLUDE_DIR)
set(FreeType2_PROCESS_LIBS FreeType2_LIBRARY)
libfind_process(FreeType2)
