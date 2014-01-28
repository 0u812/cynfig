# - Try to find ImageMagickpp 6.4.2
# Once done, this will define
#
#  ImageMagickpp_FOUND - system has ImageMagickpp
#  ImageMagickpp_INCLUDE_DIRS - the ImageMagickpp include directories
#  ImageMagickpp_LIBRARIES - link these to use ImageMagickpp

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(ImageMagickpp_PKGCONF ImageMagick++>=6.4.2)

find_library(ImageMagickpp_LIBRARY NAMES Magick++
    HINTS ${ImageMagickpp_PKGCONF_LIBDIR} ${ImageMagickpp_PKGCONF_LIBRARY_DIRS})

find_path(ImageMagickpp_INCLUDE Magick++.h
    HINTS ${ImageMagickpp_PKGCONF_INCLUDEDIR} ${ImageMagickpp_PKGCONF_INCLUDE_DIRS}
    )

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
# set(ImageMagickpp_PROCESS_INCLUDES ImageMagickpp_INCLUDE_DIR )
# set(ImageMagickpp_PROCESS_LIBS ImageMagickpp_LIBRARY )
# libfind_process(ImageMagickpp)

