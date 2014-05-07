# - Try to find Freetype2
# Once done, this will define
#
#  Freetype_FOUND - system has Freetype
#  Freetype_INCLUDE_DIRS - the Freetype include directories
#  Freetype_LIBRARIES - link these to use Freetype

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(Freetype_PKGCONF freetype2)

# Include dir
# RPM
find_path(Freetype_INCLUDE_DIR
  NAMES freetype/freetype.h
  PATHS ${Freetype_PKGCONF_INCLUDE_DIRS}
  PATH_SUFFIXES freetype2
)

# APT
if(NOT Freetype_INCLUDE_DIR)   
    find_path(Freetype_INCLUDE_DIR
    NAMES freetype.h
    PATHS ${Freetype_PKGCONF_INCLUDE_DIRS}
    )
endif()

if(SYNFIG_WINDOWS_TARGET)
    # Need ft2build.h
    # message(STATUS "Searching ${Freetype_PKGCONF_INCLUDE_DIRS} for ft2build.h")
    find_path(FreetypeBuild_INCLUDE_DIR
      NAMES ft2build.h
      PATHS ${Freetype_PKGCONF_INCLUDE_DIRS}
    )
endif()

# Finally the library itself
if(NOT SYNFIG_WINDOWS_TARGET)
    find_library(Freetype_LIBRARY
      NAMES freetype
      PATHS ${Freetype_PKGCONF_LIBRARY_DIRS}
    )
endif()

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(Freetype_PROCESS_INCLUDES Freetype_INCLUDE_DIR FreetypeBuild_INCLUDE_DIR)
# set(Freetype_PROCESS_LIBS Freetype_LIBRARY)
libfind_process(Freetype)

