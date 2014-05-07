# **  Portions copyright (c) 2013-2014 J Kyle Medley

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

pkg_check_modules(PC_FREETYPE2 freetype2)
pkg_check_modules(PC_FREETYPE2 xft)

find_library(FreeType2_LIBRARY NAMES freetype libfreetype
    HINTS ${PC_FREETYPE2_LIBDIR} ${PC_FREETYPE2_LIBRARY_DIRS} ${FREETYPE2_PATH}/lib)

# RPM
find_path(FreeType2_INCLUDE_DIR freetype/freetype.h
    HINTS ${PC_FREETYPE2_INCLUDEDIR} ${PC_FREETYPE2_INCLUDE_DIRS} ${FREETYPE2_PATH}/include/freetype2
    PATH_SUFFIXES freetype)

if(NOT FreeType2_INCLUDE_DIR)   
    find_path(FreeType2_INCLUDE_DIR freetype.h
        HINTS ${PC_FREETYPE2_INCLUDEDIR} ${PC_FREETYPE2_INCLUDE_DIRS} ${FREETYPE2_PATH}/include/freetype2)
endif()

set(FreeType2_PROCESS_INCLUDES FreeType2_INCLUDE_DIR)
set(FreeType2_PROCESS_LIBS FreeType2_LIBRARY)
libfind_process(FreeType2)

