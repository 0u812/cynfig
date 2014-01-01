cmake_minimum_required (VERSION 2.8.9)
project(Synfig)

find_package(PkgConfig)

set(SKIP_PLATFORM_TESTS 0 CACHE BOOL "Skip all tests that require compiling code (useful for cross-compiling)")

set(ENABLE_OPENEXR_HALF 0 CACHE BOOL "Use OpenEXR's \"half\" type for color")

# TODO: GetText

# http://www.cmake.org/Wiki/CMake:How_To_Find_Libraries
# NOTE: build system for all three projects is integrated
# pkg_check_modules(PC_ETL REQUIRED ETL>=0.04.18)
# find_path(ETL_INCLUDE ETL/etl_config.h
#     HINTS ${PC_ETL_INCLUDEDIR} ${PC_ETL_INCLUDE_DIRS}
#     PATH_SUFFIXES ETL)

# TODO: zlib

# layer profiling
set(ENABLE_LAYER_PROFILING 0 CACHE BOOL "Enable layer profiling")
if(ENABLE_LAYER_PROFILING)
    set(SYNFIG_PROFILE_LAYERS 1)
else()
    set(SYNFIG_PROFILE_LAYERS 0)
endif()

# libz
set(WITH_ZLIB 1 CACHE BOOL "Use zlib")
set(ZLIB_PATH "" CACHE PATH "Path to zlib")
if(WITH_ZLIB)
    find_library(ZLIB_LIBRARY NAMES z
        HINTS ${ZLIB_PATH})
    if(NOT ZLIB_LIBRARY)
        message( SEND_ERROR "Cannot find zlib. Set WITH_ZLIB to 0 to disable it." )
    endif()
    find_path(ZLIB_INCLUDE zlib.h
        HINTS ${ZLIB_PATH}/include)
    include_directories(${ZLIB_INCLUDE})
endif()

# imagemagick
set(WITH_IMAGEMAGICK 1 CACHE BOOL "Use ImageMagick")
set(IMAGEMAGICK_PATH "" CACHE PATH "Path to ImageMagick")
if(WITH_IMAGEMAGICK)
    # if the user specified to use imagemagick,
    # try to find the "convert" executable
    find_program(MAGICK_CONVERT convert PATHS ${IMAGEMAGICK_PATH})
    if(NOT MAGICK_CONVERT)
        # FATAL_ERROR
        message( SEND_ERROR "Cannot find ImageMagick. Set WITH_IMAGEMAGICK to 0 to disable it." )
    endif()
endif()

# Magick++
set(WITH_MAGICKPP 1 CACHE BOOL "Use ImageMagick++")
set(MAGICKPP_PATH "" CACHE PATH "Path to ImageMagick++")
if(WITH_MAGICKPP)
    pkg_check_modules(PC_MAGICKPP REQUIRED ImageMagick++>=6.4.2)
    find_library(MAGICKPP_LIBRARY NAMES Magick++
        HINTS ${PC_MAGICKPP_LIBDIR} ${PC_MAGICKPP_LIBRARY_DIRS})
    if(NOT MAGICKPP_LIBRARY)
        message( SEND_ERROR "Cannot find ImageMagick++. Set WITH_MAGICKPP to 0 to disable it." )
    endif()
    find_path(MAGICKPP_INCLUDE Magick++.h
        HINTS ${PC_MAGICKPP_INCLUDEDIR} ${PC_MAGICKPP_INCLUDE_DIRS}
        )
    include_directories(${MAGICKPP_INCLUDE})
endif()

# ffmpeg
set(WITH_FFMPEG 1 CACHE BOOL "Use ffmpeg")
set(FFMPEG_PATH "" CACHE PATH "Path to ffmpeg")
if(WITH_FFMPEG)
    find_program(FFMPEG_EXE ffmpeg PATHS ${FFMPEG_PATH})
    if(NOT FFMPEG_EXE)
        message( SEND_ERROR "Cannot find ffmpeg. Set WITH_FFMPEG to 0 to disable it." )
    endif()
endif()

# libdv
set(WITH_LIBDV 1 CACHE BOOL "Use libdv")
set(LIBDV_PATH "" CACHE PATH "Path to libdv")
if(WITH_LIBDV)
    pkg_check_modules(PC_LIBDV REQUIRED libdv)
    find_library(LIBDV_LIBRARY NAMES dv
        HINTS ${PC_LIBDV_LIBDIR} ${PC_LIBDV_LIBRARY_DIRS})
    if(NOT LIBDV_LIBRARY)
        message( SEND_ERROR "Cannot find libdv. Set WITH_LIBDV to 0 to disable it." )
    endif()
    find_path(LIBDV_INCLUDE libdv/dv.h
        HINTS ${PC_LIBDV_INCLUDEDIR} ${PC_LIBDV_INCLUDE_DIRS}
        PATH_SUFFIXES libdv)
    include_directories(${LIBDV_INCLUDE})
endif()

include(CheckIncludeFiles)

# libavcodec and friends
set(WITH_LIBAVCODEC 1 CACHE BOOL "Use libavcodec (included with ffmpeg)") # define
set(LIBAVCODEC_PATH "" CACHE PATH "Path to libavcodec")
if(WITH_LIBAVCODEC)
    pkg_check_modules(PC_LIBAVCODEC REQUIRED libavcodec)
    pkg_check_modules(PC_LIBAVFORMAT REQUIRED libavformat)
    pkg_check_modules(PC_LIBSWSCALE REQUIRED libswscale)
    
    find_library(LIBAVCODEC_LIBRARY NAMES avcodec
        HINTS ${PC_LIBAVCODEC_LIBDIR} ${PC_LIBAVCODEC_LIBRARY_DIRS})
    if(NOT LIBAVCODEC_LIBRARY)
        message( SEND_ERROR "Cannot find libavcodec. Set WITH_LIBAVCODEC to 0 to disable it." )
    endif()
    
    find_library(LIBAVFORMAT_LIBRARY NAMES avformat
        HINTS ${PC_LIBAVFORMAT_LIBDIR} ${PC_LIBAVFORMAT_LIBRARY_DIRS})
    if(NOT LIBAVFORMAT_LIBRARY)
        message( SEND_ERROR "Cannot find libavformat. Set WITH_LIBAVCODEC to 0 to disable it." )
    endif()
    
    find_library(LIBSWSCALE_LIBRARY NAMES swscale
        HINTS ${PC_LIBSWSCALE_LIBDIR} ${PC_LIBSWSCALE_LIBRARY_DIRS})
    if(NOT LIBSWSCALE_LIBRARY)
        message( SEND_ERROR "Cannot find libswscale. Set WITH_LIBAVCODEC to 0 to disable it." )
    endif()
    
    # these almost always use the same include path - only add once?
    find_path(LIBAVCODEC_INCLUDE libavcodec/avcodec.h
        HINTS ${PC_LIBAVCODEC_INCLUDEDIR} ${PC_LIBAVCODEC_INCLUDE_DIRS}
        PATH_SUFFIXES libavcodec)
    include_directories(${LIBAVCODEC_INCLUDE})
    find_path(LIBAVFORMAT_INCLUDE libavformat/avformat.h
        HINTS ${PC_LIBAVFORMAT_INCLUDEDIR} ${PC_LIBAVFORMAT_INCLUDE_DIRS}
        PATH_SUFFIXES libavformat)
    include_directories(${LIBAVFORMAT_INCLUDE})
    find_path(LIBSWSCALE_INCLUDE libswscale/swscale.h
        HINTS ${PC_LIBSWSCALE_INCLUDEDIR} ${PC_LIBSWSCALE_INCLUDE_DIRS}
        PATH_SUFFIXES libswscale)
    include_directories(${LIBSWSCALE_INCLUDE})
    
    # header checks - try to compile test code using the respective headers
    if(NOT SKIP_PLATFORM_TESTS)
        set(CMAKE_REQUIRED_FLAGS ${PC_LIBAVFORMAT_CFLAGS})
        CHECK_INCLUDE_FILES(libavformat/avformat.h AVFORMAT_HEADER_CHECK)
        if(NOT AVFORMAT_HEADER_CHECK)
            message( SEND_ERROR "Failed to properly compile a test for libavformat - configure the library properly, then wipe the build directory" )
        endif()
        set(CMAKE_REQUIRED_FLAGS ${PC_LIBSWSCALE_CFLAGS})
        CHECK_INCLUDE_FILES(libswscale/swscale.h SWSCALE_HEADER_CHECK)
        if(NOT SWSCALE_HEADER_CHECK)
            message( SEND_ERROR "Failed to properly compile a test for libavformat - configure the library properly, then wipe the build directory" )
        endif()
    endif()
endif()

# freetype2
set(WITH_FREETYPE2 1 CACHE BOOL "Use freetype2")
set(FREETYPE2_PATH "" CACHE PATH "Path to freetype2")
if(WITH_FREETYPE2)
    pkg_check_modules(PC_FREETYPE2 REQUIRED freetype2)
    pkg_check_modules(PC_FREETYPE2 REQUIRED xft)
    find_library(FREETYPE2_LIBRARY NAMES freetype
        HINTS ${PC_FREETYPE2_LIBDIR} ${PC_FREETYPE2_LIBRARY_DIRS})
    if(NOT FREETYPE2_LIBRARY)
        message( SEND_ERROR "Cannot find freetype2. Set WITH_FREETYPE2 to 0 to disable it." )
    endif()
    find_path(FREETYPE2_INCLUDE freetype/freetype.h
        HINTS ${PC_FREETYPE2_INCLUDEDIR} ${PC_FREETYPE2_INCLUDE_DIRS}
        PATH_SUFFIXES freetype)
    include_directories(${FREETYPE2_INCLUDE})
endif()

# fontconfig
set(WITH_FONTCONFIG 1 CACHE BOOL "Use fontconfig")
set(FONTCONFIG_PATH "" CACHE PATH "Path to fontconfig")
if(WITH_FONTCONFIG)
    pkg_check_modules(PC_FONTCONFIG REQUIRED fontconfig)
    find_library(FONTCONFIG_LIBRARY NAMES fontconfig
        HINTS ${PC_FONTCONFIG_LIBDIR} ${PC_FONTCONFIG_LIBRARY_DIRS})
    if(NOT FONTCONFIG_LIBRARY)
        message( SEND_ERROR "Cannot find fontconfig. Set WITH_FONTCONFIG to 0 to disable it." )
    endif()
    find_path(FONTCONFIG_INCLUDE fontconfig/fontconfig.h
        HINTS ${PC_FONTCONFIG_INCLUDEDIR} ${PC_FONTCONFIG_INCLUDE_DIRS}
        PATH_SUFFIXES fontconfig)
    include_directories(${FONTCONFIG_INCLUDE})
    
    # add WITH_FONTCONFIG define to header
endif()

# openexr
set(WITH_OPENEXR 1 CACHE BOOL "Use OpenEXR")
set(OPENEXR_PATH "" CACHE PATH "Path to OpenEXR")
if(WITH_OPENEXR)
    pkg_check_modules(PC_OPENEXR REQUIRED OpenEXR)
    # add pthread
    # link IlmImf Imath Half Iex IexMath IlmThread
    find_library(OPENEXR_IMF_LIBRARY NAMES IlmImf
        HINTS ${PC_OPENEXR_LIBDIR} ${PC_OPENEXR_LIBRARY_DIRS})
    find_library(OPENEXR_IMATH_LIBRARY NAMES Imath
        HINTS ${PC_OPENEXR_LIBDIR} ${PC_OPENEXR_LIBRARY_DIRS})
    find_library(OPENEXR_HALF_LIBRARY NAMES Half
        HINTS ${PC_OPENEXR_LIBDIR} ${PC_OPENEXR_LIBRARY_DIRS})
    find_library(OPENEXR_EX_LIBRARY NAMES Iex
        HINTS ${PC_OPENEXR_LIBDIR} ${PC_OPENEXR_LIBRARY_DIRS})
    find_library(OPENEXR_EXMATH_LIBRARY NAMES IexMath
        HINTS ${PC_OPENEXR_LIBDIR} ${PC_OPENEXR_LIBRARY_DIRS})
    find_library(OPENEXR_THREAD_LIBRARY NAMES IlmThread
        HINTS ${PC_OPENEXR_LIBDIR} ${PC_OPENEXR_LIBRARY_DIRS})
    if(NOT OPENEXR_IMF_LIBRARY OR NOT OPENEXR_IMATH_LIBRARY OR NOT OPENEXR_HALF_LIBRARY OR 
    NOT OPENEXR_EX_LIBRARY OR NOT OPENEXR_EXMATH_LIBRARY OR NOT OPENEXR_THREAD_LIBRARY )
        message( SEND_ERROR "Cannot find OpenEXR. Set WITH_OPENEXR to 0 to disable it." )
    endif()
    find_path(OPENEXR_INCLUDE OpenEXRConfig.h
        HINTS ${PC_OPENEXR_INCLUDEDIR} ${PC_OPENEXR_INCLUDE_DIRS})
    include_directories(${OPENEXR_INCLUDE})
    find_path(OPENEXR_DRM_INCLUDE drm.h
        HINTS ${PC_OPENEXR_INCLUDEDIR} ${PC_OPENEXR_INCLUDE_DIRS})
    include_directories(${OPENEXR_DRM_INCLUDE})
    
    # add HAVE_OPENEXR define to header
endif()

# include(FindPkgConfig)
# pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
pkg_check_modules(PC_GLIBMM REQUIRED glibmm-2.4)
find_library(GLIBMM_LIBRARY NAMES glibmm-2.4
    HINTS ${PC_GLIBMM_LIBDIR} ${PC_GLIBMM_LIBRARY_DIRS})
find_library(GOBJECT_LIBRARY NAMES gobject-2.0
    HINTS ${PC_GLIBMM_LIBDIR} ${PC_GLIBMM_LIBRARY_DIRS})
find_library(SIGC_LIBRARY NAMES sigc-2.0
    HINTS ${PC_GLIBMM_LIBDIR} ${PC_GLIBMM_LIBRARY_DIRS})
find_library(GLIB_LIBRARY NAMES glib-2.0
    HINTS ${PC_GLIBMM_LIBDIR} ${PC_GLIBMM_LIBRARY_DIRS})
# need to use pkg-config's results for include dir directly
# due to significant variability of paths
include_directories(${PC_GLIBMM_INCLUDE_DIRS})

# include(FindPackageHandleStandardArgs)
# find_package_handle_standard_args(glibmm DEFAULT_MSG GLIBMM_LIBRARY)

# giomm
# in glibmm
# pkg_check_modules(PC_GLIBMM REQUIRED giomm-2.4)
find_library(GIOMM_LIBRARY NAMES giomm-2.4
    HINTS ${PC_GLIBMM_LIBDIR} ${PC_GLIBMM_LIBRARY_DIRS})

# libxml++
pkg_check_modules(PC_LIBXMLPP REQUIRED libxml++-2.6)
find_library(LIBXMLPP_LIBRARY NAMES xml++-2.6
    HINTS ${PC_LIBXMLPP_LIBDIR} ${PC_LIBXMLPP_LIBRARY_DIRS})
find_path(LIBXMLPP_INCLUDE libxml++/libxml++.h
    HINTS ${PC_LIBXMLPP_INCLUDEDIR} ${PC_LIBXMLPP_INCLUDE_DIRS}
    PATH_SUFFIXES libxml++)
# too many dirs
include_directories(${PC_LIBXMLPP_INCLUDE_DIRS})

# Cairo
pkg_check_modules(PC_CAIRO REQUIRED cairo>=1.12.0)
find_library(CAIRO_LIBRARY NAMES cairo
    HINTS ${PC_CAIRO_LIBDIR} ${PC_CAIRO_LIBRARY_DIRS})
find_path(CAIRO_INCLUDE cairo.h
    HINTS ${PC_CAIRO_INCLUDEDIR} ${PC_CAIRO_INCLUDE_DIRS}
    )
include_directories(${PC_CAIRO_INCLUDE_DIRS})

# cairomm
pkg_check_modules(PC_CAIROMM REQUIRED cairomm>=1.10.0)
find_library(CAIROMM_LIBRARY NAMES cairomm
    HINTS ${PC_CAIROMM_LIBDIR} ${PC_CAIROMM_LIBRARY_DIRS})
find_path(CAIROMM_INCLUDE cairomm-1.0/cairomm.h
    HINTS ${PC_CAIROMM_INCLUDEDIR} ${PC_CAIROMM_INCLUDE_DIRS}
    PATH_SUFFIXES cairomm-1.0)
include_directories(${PC_CAIROMM_INCLUDE_DIRS})

# Pango
pkg_check_modules(PC_PANGO REQUIRED pango)
find_library(PANGO_LIBRARY NAMES pango-1.0
    HINTS ${PC_PANGO_LIBDIR} ${PC_PANGO_LIBRARY_DIRS})
find_library(PANGOCAIRO_LIBRARY NAMES pangocairo-1.0
    HINTS ${PC_PANGO_LIBDIR} ${PC_PANGO_LIBRARY_DIRS})
find_path(PANGO_INCLUDE pango/pango.h
    HINTS ${PC_PANGO_INCLUDEDIR} ${PC_PANGO_INCLUDE_DIRS}
    )
include_directories(${PC_PANGO_INCLUDE_DIRS})

# Boost
# http://stackoverflow.com/questions/6646405/how-do-you-add-boost-libraries-in-cmakelists-txt
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

set(BOOST_ROOT "" CACHE PATH "Path to Boost installation")
set(BOOST_VERSION "1.54" CACHE STRING "Which version of Boost to use")
find_package(Boost ${BOOST_VERSION} REQUIRED COMPONENTS program_options)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

# PNG
set(WITH_PNG 1 CACHE BOOL "Use libpng")
set(PNG_PATH "" CACHE PATH "Path to libpng")
if(WITH_PNG)
    pkg_check_modules(PC_PNG REQUIRED libpng>=1.4)
    find_library(PNG_LIBRARY NAMES png14
        HINTS ${PC_PNG_LIBDIR} ${PC_PNG_LIBRARY_DIRS})
        
    if(NOT PNG_LIBRARY)
        find_library(PNG_LIBRARY NAMES png15
            HINTS ${PC_PNG_LIBDIR} ${PC_PNG_LIBRARY_DIRS})
    endif()
    if(NOT PNG_LIBRARY)
        find_library(PNG_LIBRARY NAMES png16
            HINTS ${PC_PNG_LIBDIR} ${PC_PNG_LIBRARY_DIRS})
    endif()
    if(NOT PNG_LIBRARY)
        message( SEND_ERROR "Cannot find libpng. Set WITH_PNG to 0 to disable it." )
    endif()
    find_path(PNG_INCLUDE png.h
        HINTS ${PC_PNG_INCLUDEDIR} ${PC_PNG_INCLUDE_DIRS})
    include_directories(${PNG_INCLUDE})
    
    # add HAVE_LIBPNG14, HAVE_LIBPNG define to header
endif()

# MNG
set(MNG_PATH "" CACHE PATH "Path to libmng")
find_library(MNG_LIBRARY NAMES mng
    HINTS ${MNG_PATH}/lib)
if(MNG_LIBRARY)
    find_path(MNG_INCLUDE libmng.h
        HINTS ${MNG_PATH}/include)
    if(MNG_INCLUDE)
        include_directories(${MNG_INCLUDE})
        set(WITH_MNG 1 CACHE BOOL "Use libmng")
    endif()
    # add HAVE_LIBMNG define to header
endif()
set(WITH_MNG 0 CACHE BOOL "Use libmng")

# Poco
set(POCO_PATH "" CACHE PATH "Path to Poco")
find_library(POCO_FOUNDATION_LIBRARY NAMES PocoFoundation
    HINTS ${POCO_PATH}/lib)
if(POCO_FOUNDATION_LIBRARY)
    find_path(POCO_INCLUDE Poco/SharedLibrary.h
        HINTS ${POCO_PATH}/include
        PATH_SUFFIXES Poco)
    include_directories(${POCO_INCLUDE})
else()
    message( SEND_ERROR "Failed to find Poco" );
endif()

add_subdirectory(ETL)
add_subdirectory(synfig-core)

# http://stackoverflow.com/questions/9298278/cmake-print-out-all-accessible-variables-in-a-script
get_cmake_property(_variableNames VARIABLES)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()

message(STATUS "
The style of this summary is based on libSBML's (http://sbml.org/Software/libSBML)

-------------------------------------------------------------------------------
Synfig Configuration Summary
-------------------------------------------------------------------------------
    
    For up-to-date news and releases, visit the Synfig homepage at
    http://http://www.synfig.org
    
    Configured on host $ENV{COMPUTERNAME} ${HOSTNAME}
      host OS                   ${CMAKE_SYSTEM_NAME}
      host architecture         ${CMAKE_SYSTEM_PROCESSOR}
      
    General flags:
      CC                        ${CMAKE_C_COMPILER}
      CXX                       ${CMAKE_CXX_COMPILER}
      CPPFLAGS                  ${BUILD_DEFINITIONS}
      CFLAGS                    ${CMAKE_C_FLAGS}
      CXXFLAGS                  ${CMAKE_CXX_FLAGS}
      LDFLAGS                   ${CMAKE_EXE_LINKER_FLAGS}
      
    Installation prefix:        ${CMAKE_INSTALL_PREFIX}
    
    Options:
      OpenEXR Half Type         ${ENABLE_OPENEXR_HALF}
      Layer profiling           ${ENABLE_LAYER_PROFILING}
      
    Dependencies (packages marked with *NOT FOUND are required):"
)

if(WITH_ZLIB)
    message( "    * zlib                        ${ZLIB_LIBRARY}")
    message( "    * zlib includes               ${ZLIB_INCLUDE}")
else()
    message( "    * zlib                        *NOT FOUND")
endif()
message( "    * ImageMagick                 ${MAGICK_CONVERT}")
if(WITH_MAGICKPP)
    message( "    * ImageMagick++               ${MAGICKPP_LIBRARY}")
    message( "    * ImageMagick++ includes      ${MAGICKPP_INCLUDE}")
else()
    message( "    * ImageMagick++               DISABLED")
endif()
message( "    * glibmm-2.4                  ${GLIBMM_LIBRARY}")
if(WITH_FFMPEG)
    message( "    * ffmpeg                      ${FFMPEG_EXE}")
else()
    message( "    * ffmpeg                      DISABLED")
endif()
if(WITH_LIBDV)
    message( "    * libdv                       ${LIBDV_LIBRARY}")
    message( "    * libdv includes              ${LIBDV_INCLUDE}")
else()
    message( "    * libdv                       DISABLED")
endif()
if(WITH_LIBAVCODEC)
    message( "    * libavcodec                  ${LIBAVCODEC_LIBRARY}")
    message( "    * libavcodec includes         ${LIBAVCODEC_INCLUDE}")
    message( "    * libavformat                 ${LIBAVFORMAT_LIBRARY}")
    message( "    * libavformat includes        ${LIBAVFORMAT_INCLUDE}")
    message( "    * libswscale                  ${LIBSWSCALE_LIBRARY}")
    message( "    * libswscale includes         ${LIBSWSCALE_INCLUDE}")
else()
    message( "    * libavcodec/avformat         DISABLED")
endif()
if(WITH_FREETYPE2)
    message( "    * freetype2                   ${FREETYPE2_LIBRARY}")
    message( "    * freetype2 includes          ${FREETYPE2_INCLUDE}")
else()
    message( "    * freetype2                   DISABLED")
endif()
if(WITH_FONTCONFIG)
    message( "    * fontconfig                  ${FONTCONFIG_LIBRARY}")
    message( "    * fontconfig includes         ${FONTCONFIG_INCLUDE}")
else()
    message( "    * fontconfig                  DISABLED")
endif()
if(WITH_OPENEXR)
    message( "    * OpenEXR                     ${OPENEXR_IMF_LIBRARY}")
    message( "    * OpenEXR includes            ${OPENEXR_INCLUDE}")
else()
    message( "    * OpenEXR                     DISABLED")
endif()
message( "    * glibmm-2.4 includes         ${PC_GLIBMM_INCLUDE_DIRS}")
message( "    * gobject-2.0                 ${GOBJECT_LIBRARY}")
message( "    * sigc-2.0                    ${SIGC_LIBRARY}")
message( "    * glib-2.0                    ${GLIB_LIBRARY}")
message( "    * giomm-2.4                   ${GIOMM_LIBRARY}")
message( "    * libxml++-2.6                ${LIBXMLPP_LIBRARY}")
message( "    * libxml++ includes           ${PC_LIBXMLPP_INCLUDE_DIRS}")
message( "    * cairo                       ${CAIRO_LIBRARY}")
message( "    * cairo includes              ${PC_CAIRO_INCLUDE_DIRS}")
message( "    * cairo mm                    ${CAIROMM_LIBRARY}")
message( "    * cairo mm includes           ${PC_CAIROMM_INCLUDE_DIRS}")
message( "    * pango-1.0                   ${PANGO_LIBRARY}")
message( "    * pango includes              ${PC_PANGO_INCLUDE_DIRS}")
message( "    * pangocairo                  ${PANGOCAIRO_LIBRARY}")
if(Boost_FOUND)
    message( "    * Boost Libraries             ${Boost_LIBRARIES}")
    message( "    * Boost Includes              ${Boost_INCLUDE_DIRS}")
else()
    message( "    * Boost                       *NOT FOUND")
endif()
if(WITH_PNG)
    message( "    * libpng                      ${PNG_LIBRARY}")
    message( "    * libpng includes             ${PNG_INCLUDE}")
else()
    message( "    * libpng                      DISABLED")
endif()
if(WITH_MNG)
    message( "    * libmng                      ${MNG_LIBRARY}")
    message( "    * libmng includes             ${MNG_INCLUDE}")
else()
    message( "    * libmng                      DISABLED")
endif()
if(POCO_FOUNDATION_LIBRARY)
    message( "    * Poco Libraries              ${POCO_FOUNDATION_LIBRARY}")
    message( "    * Poco Includes               ${POCO_INCLUDE}")
else()
    message( "    * Poco                        *NOT FOUND")
endif()
