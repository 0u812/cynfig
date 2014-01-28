# - Try to find OpenEXR
# Once done, this will define
#
#  OpenEXR_FOUND - system has OpenEXR
#  OpenEXR_INCLUDE_DIRS - the OpenEXR include directories
#  OpenEXR_LIBRARIES - link these to use OpenEXR
#
# See documentation on how to write CMake scripts at
# http://www.cmake.org/Wiki/CMake:How_To_Find_Libraries

include(LibFindMacros)

libfind_pkg_check_modules(OpenEXR_PKGCONF OpenEXR)

# add pthread
# link IlmImf Imath Half Iex IexMath IlmThread
find_library(OPENEXR_IMF_LIBRARY NAMES IlmImf
    HINTS ${OpenEXR_PKGCONF_LIBDIR} ${OpenEXR_PKGCONF_LIBRARY_DIRS})
find_library(OPENEXR_IMATH_LIBRARY NAMES Imath
    HINTS ${OpenEXR_PKGCONF_LIBDIR} ${OpenEXR_PKGCONF_LIBRARY_DIRS})
find_library(OPENEXR_HALF_LIBRARY NAMES Half
    HINTS ${OpenEXR_PKGCONF_LIBDIR} ${OpenEXR_PKGCONF_LIBRARY_DIRS})
find_library(OPENEXR_EX_LIBRARY NAMES Iex
    HINTS ${OpenEXR_PKGCONF_LIBDIR} ${OpenEXR_PKGCONF_LIBRARY_DIRS})
find_library(OPENEXR_EXMATH_LIBRARY NAMES IexMath
    HINTS ${OpenEXR_PKGCONF_LIBDIR} ${OpenEXR_PKGCONF_LIBRARY_DIRS})
find_library(OPENEXR_THREAD_LIBRARY NAMES IlmThread
    HINTS ${OpenEXR_PKGCONF_LIBDIR} ${OpenEXR_PKGCONF_LIBRARY_DIRS})
if(NOT OPENEXR_IMF_LIBRARY OR NOT OPENEXR_IMATH_LIBRARY OR NOT OPENEXR_HALF_LIBRARY OR 
NOT OPENEXR_EX_LIBRARY OR NOT OPENEXR_EXMATH_LIBRARY OR NOT OPENEXR_THREAD_LIBRARY )
    message( SEND_ERROR "Cannot find OpenEXR. Set WITH_OPENEXR to 0 to disable it." )
endif()
find_path(OPENEXR_INCLUDE OpenEXRConfig.h
    HINTS ${OpenEXR_PKGCONF_INCLUDEDIR} ${OpenEXR_PKGCONF_INCLUDE_DIRS})
find_path(OPENEXR_DRM_INCLUDE drm.h
    HINTS ${OpenEXR_PKGCONF_INCLUDEDIR} ${OpenEXR_PKGCONF_INCLUDE_DIRS})

set(OpenEXR_PROCESS_INCLUDES OpenEXR_INCLUDE_DIR)
set(OpenEXR_PROCESS_LIBS OpenEXR_LIBRARY)
libfind_process(OpenEXR)

