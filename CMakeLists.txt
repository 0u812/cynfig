cmake_minimum_required (VERSION 2.8.9)
project(Synfig)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(SYNFIG_MAJOR "0")
set(SYNFIG_MINOR "65")
set(SYNFIG_PATCH "0")

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

set(ENABLE_FULL_RPATH 1 CACHE BOOL "Adds installation RPATH to executables so setting LD_LIBRARY_PATH is not required")
if(ENABLE_FULL_RPATH) #http://www.cmake.org/Wiki/CMake_RPATH_handling
    SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
    
    SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 
    
    SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
    
    SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
    
    LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
    IF("${isSystemDir}" STREQUAL "-1")
        SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
    ENDIF("${isSystemDir}" STREQUAL "-1")
endif()

set(ETL_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ETL)

set(ENABLE_SYNFIG_CORE 1 CACHE BOOL "Enable Synfig Core")
if(ENABLE_SYNFIG_CORE)
    set(SYNFIG_CORE_INCLUDE_PATHS "")
    
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
        list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${ZLIB_INCLUDE})
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
        find_package(ImageMagickpp REQUIRED)
        if(NOT ImageMagickpp_LIBRARY)
            message( SEND_ERROR "Cannot find ImageMagick++. Set WITH_MAGICKPP to 0 to disable it." )
        endif()
        list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${ImageMagickpp_INCLUDE})
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
        find_package(LibDV REQUIRED)
        if(NOT LIBDV_LIBRARY)
            message( SEND_ERROR "Cannot find libdv. Set WITH_LIBDV to 0 to disable it." )
        endif()
        list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${LIBDV_INCLUDE})
    endif()

    include(CheckIncludeFiles)

    # libavcodec and friends
    set(WITH_LIBAVCODEC 1 CACHE BOOL "Use libavcodec (included with ffmpeg)") # define
    set(LIBAVCODEC_PATH "" CACHE PATH "Path to libavcodec")
    if(WITH_LIBAVCODEC)
        find_package(AVCodec REQUIRED)
        find_package(AVFormat REQUIRED)
        find_package(SWScale REQUIRED)
        pkg_check_modules(PC_LIBSWSCALE REQUIRED libswscale)
        
        if(NOT AVCodec_FOUND)
            message( SEND_ERROR "Cannot find libavcodec. Set WITH_LIBAVCODEC to 0 to disable it." )
        endif()
        
        if(NOT AVFormat_FOUND)
            message( SEND_ERROR "Cannot find libavformat. Set WITH_LIBAVCODEC to 0 to disable it." )
        endif()
        
        if(NOT SWScale_LIBRARY)
            message( SEND_ERROR "Cannot find libswscale. Set WITH_LIBAVCODEC to 0 to disable it." )
        endif()
        
        list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${AVCodec_INCLUDE_DIR})
        list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${AVFormat_INCLUDE_DIR})
        list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${SWScale_INCLUDE_DIR})
        
        # header checks - try to compile test code using the respective headers
        if(NOT SKIP_PLATFORM_TESTS)
            set(CMAKE_REQUIRED_FLAGS ${AVFormat_PKGCONF_CFLAGS})
            CHECK_INCLUDE_FILES(libavformat/avformat.h AVFORMAT_HEADER_CHECK)
            if(NOT AVFORMAT_HEADER_CHECK)
                message( SEND_ERROR "Failed to properly compile a test for libavformat - configure the library properly, then wipe the build directory" )
            endif()
            set(CMAKE_REQUIRED_FLAGS ${SWScale_PKGCONF_CFLAGS})
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
        find_package(FreeType2 REQUIRED)
        if(NOT FreeType2_FOUND)
            message( SEND_ERROR "Cannot find freetype2. Set WITH_FREETYPE2 to 0 to disable it." )
        endif()
        list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${FreeType2_INCLUDE_DIR})
    endif()

    # fontconfig
    set(WITH_FONTCONFIG 1 CACHE BOOL "Use fontconfig")
    set(FONTCONFIG_PATH "" CACHE PATH "Path to fontconfig")
    if(WITH_FONTCONFIG)
        find_package(Fontconfig REQUIRED)
        if(NOT Fontconfig_FOUND)
            message( SEND_ERROR "Cannot find fontconfig. Set WITH_FONTCONFIG to 0 to disable it." )
        endif()
        list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${Fontconfig_INCLUDE_DIR})
        
        # add WITH_FONTCONFIG define to header
    endif()

    # openexr
    set(WITH_OPENEXR 1 CACHE BOOL "Use OpenEXR")
    set(OPENEXR_PATH "" CACHE PATH "Path to OpenEXR")
    if(WITH_OPENEXR)
        find_package(OpenEXR REQUIRED)
        if(NOT OPENEXR_IMF_LIBRARY OR NOT OPENEXR_IMATH_LIBRARY OR NOT OPENEXR_HALF_LIBRARY OR 
        NOT OPENEXR_EX_LIBRARY OR NOT OPENEXR_EXMATH_LIBRARY OR NOT OPENEXR_THREAD_LIBRARY )
            message( SEND_ERROR "Cannot find OpenEXR. Set WITH_OPENEXR to 0 to disable it." )
        endif()
        list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${OPENEXR_INCLUDE})
        list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${OPENEXR_DRM_INCLUDE})
        
        # add HAVE_OPENEXR define to header
    endif()

    # include(FindPkgConfig)
    # pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
#     pkg_check_modules(PC_GLIBMM REQUIRED glibmm-2.4)
#     find_library(GLIBMM_LIBRARY NAMES glibmm-2.4
#         HINTS ${PC_GLIBMM_LIBDIR} ${PC_GLIBMM_LIBRARY_DIRS})
#     find_library(GOBJECT_LIBRARY NAMES gobject-2.0
#         HINTS ${PC_GLIBMM_LIBDIR} ${PC_GLIBMM_LIBRARY_DIRS})
#     find_library(SIGC_LIBRARY NAMES sigc-2.0
#         HINTS ${PC_GLIBMM_LIBDIR} ${PC_GLIBMM_LIBRARY_DIRS})
#     find_library(GLIB_LIBRARY NAMES glib-2.0
#         HINTS ${PC_GLIBMM_LIBDIR} ${PC_GLIBMM_LIBRARY_DIRS})
    find_package(Glibmm REQUIRED)
    # need to use pkg-config's results for include dir directly
    # due to significant variability of paths
    list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${Glibmm_INCLUDE_DIRS})
    
    find_package(GIOmm REQUIRED)
    
    list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${GIOmm_INCLUDE_DIRS})

    # libxml++
    pkg_check_modules(PC_LIBXMLPP REQUIRED libxml++-2.6)
    find_library(LIBXMLPP_LIBRARY NAMES xml++-2.6
        HINTS ${PC_LIBXMLPP_LIBDIR} ${PC_LIBXMLPP_LIBRARY_DIRS})
    find_path(LIBXMLPP_INCLUDE libxml++/libxml++.h
        HINTS ${PC_LIBXMLPP_INCLUDEDIR} ${PC_LIBXMLPP_INCLUDE_DIRS}
        PATH_SUFFIXES libxml++)
    # too many dirs
    list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${PC_LIBXMLPP_INCLUDE_DIRS})

    # Cairo
    pkg_check_modules(PC_CAIRO REQUIRED cairo>=1.12.0)
    find_library(CAIRO_LIBRARY NAMES cairo
        HINTS ${PC_CAIRO_LIBDIR} ${PC_CAIRO_LIBRARY_DIRS})
    find_path(CAIRO_INCLUDE cairo.h
        HINTS ${PC_CAIRO_INCLUDEDIR} ${PC_CAIRO_INCLUDE_DIRS}
        )
    list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${PC_CAIRO_INCLUDE_DIRS})

    # cairomm
    pkg_check_modules(PC_CAIROMM REQUIRED cairomm-1.0)
    find_library(CAIROMM_LIBRARY NAMES cairomm-1.0
        HINTS ${PC_CAIROMM_LIBDIR} ${PC_CAIROMM_LIBRARY_DIRS})
    find_path(CAIROMM_INCLUDE cairomm-1.0/cairomm.h
        HINTS ${PC_CAIROMM_INCLUDEDIR} ${PC_CAIROMM_INCLUDE_DIRS}
        PATH_SUFFIXES cairomm-1.0)
    list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${PC_CAIROMM_INCLUDE_DIRS})

    # Pango
    pkg_check_modules(PC_PANGO REQUIRED pango)
    find_library(PANGO_LIBRARY NAMES pango-1.0
        HINTS ${PC_PANGO_LIBDIR} ${PC_PANGO_LIBRARY_DIRS})
    find_library(PANGOCAIRO_LIBRARY NAMES pangocairo-1.0
        HINTS ${PC_PANGO_LIBDIR} ${PC_PANGO_LIBRARY_DIRS})
    find_path(PANGO_INCLUDE pango/pango.h
        HINTS ${PC_PANGO_INCLUDEDIR} ${PC_PANGO_INCLUDE_DIRS}
        )
    list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${PC_PANGO_INCLUDE_DIRS})

    # Boost
    # http://stackoverflow.com/questions/6646405/how-do-you-add-boost-libraries-in-cmakelists-txt
    set(Boost_USE_STATIC_LIBS OFF)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)

    set(BOOST_ROOT "" CACHE PATH "Path to Boost installation")
    set(BOOST_VERSION "1.54" CACHE STRING "Which version of Boost to use")
    find_package(Boost ${BOOST_VERSION} REQUIRED COMPONENTS program_options filesystem)
    if(Boost_FOUND)
        list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${Boost_INCLUDE_DIRS})
    endif()

    # PNG
    set(WITH_PNG 1 CACHE BOOL "Use libpng")
    set(PNG_PATH "" CACHE PATH "Path to libpng")
    if(WITH_PNG)
        pkg_check_modules(PC_PNG REQUIRED libpng>=1.4)
        find_library(PNG_LIBRARY NAMES png16
            HINTS ${PC_PNG_LIBDIR} ${PC_PNG_LIBRARY_DIRS})
            
        if(NOT PNG_LIBRARY)
            find_library(PNG_LIBRARY NAMES png15
                HINTS ${PC_PNG_LIBDIR} ${PC_PNG_LIBRARY_DIRS})
        endif()
        if(NOT PNG_LIBRARY)
            find_library(PNG_LIBRARY NAMES png14
                HINTS ${PC_PNG_LIBDIR} ${PC_PNG_LIBRARY_DIRS})
        endif()
        if(NOT PNG_LIBRARY)
            message( SEND_ERROR "Cannot find libpng. Set WITH_PNG to 0 to disable it." )
        endif()
        find_path(PNG_INCLUDE png.h
            HINTS ${PC_PNG_INCLUDEDIR} ${PC_PNG_INCLUDE_DIRS})
        list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${PNG_INCLUDE})
        
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
            list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${MNG_INCLUDE})
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
        list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${POCO_INCLUDE})
    else()
        message( SEND_ERROR "Failed to find Poco" )
    endif()

    # FIXME: add pthread to synfig-core & synfig-studio
    set(SYNFIG_CORE_REQUIRED_LIBRARIES
        ${Glibmm_LIBRARIES}
        ${GIOmm_LIBRARIES}
        ${LIBXMLPP_LIBRARY}
        ${CAIRO_LIBRARY}
        ${CAIROMM_LIBRARY}
        ${PANGO_LIBRARY}
        ${PANGOCAIRO_LIBRARY}
        ${POCO_FOUNDATION_LIBRARY}
        ${Boost_LIBRARIES})
else()
    set(ENABLE_SYNFIG_STUDIO 0 CACHE BOOL "Enable Synfig Studio")
endif(ENABLE_SYNFIG_CORE)

set(ENABLE_SYNFIG_STUDIO 1 CACHE BOOL "Enable Synfig Studio")
if(ENABLE_SYNFIG_STUDIO)
    if(NOT ENABLE_SYNFIG_CORE)
        message( FATAL_ERROR "Must enable Synfig Core in order to enable Synfig Studio")
    endif()
    set(SYNFIG_STUDIO_INCLUDE_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/synfig-core/src)
    list(APPEND SYNFIG_STUDIO_INCLUDE_PATHS ${PC_LIBXMLPP_INCLUDE_DIRS})
    # gtkmm
#     set(GTKMM_PATH "" CACHE PATH "Path to gtkmm")
#     pkg_check_modules(PC_GTKMM gtkmm-2.4)
    # no prayer of a non-pkg-config solution
    find_package(GTKmm REQUIRED)
    # link with GTKmm_LIBRARIES
    # include GTKmm_INCLUDE_DIRS
    list(APPEND SYNFIG_STUDIO_INCLUDE_PATHS ${GTKmm_INCLUDE_DIRS})
endif(ENABLE_SYNFIG_STUDIO)

add_subdirectory(ETL)
if(ENABLE_SYNFIG_CORE)
    add_subdirectory(synfig-core)
endif()
if(ENABLE_SYNFIG_STUDIO)
    add_subdirectory(synfig-studio)
endif()

# http://stackoverflow.com/questions/9298278/cmake-print-out-all-accessible-variables-in-a-script
# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()

message(STATUS "
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
      
    Dependencies (packages marked with *** are required):"
)

if(WITH_ZLIB)
    message( "    * zlib                        ${ZLIB_LIBRARY}")
    message( "    * zlib includes               ${ZLIB_INCLUDE}")
else()
    message( "  *** zlib                        *NOT FOUND")
endif()
message( "    * ImageMagick                 ${MAGICK_CONVERT}")
if(WITH_MAGICKPP)
    message( "    * ImageMagick++               ${MAGICKPP_LIBRARY}")
    message( "    * ImageMagick++ includes      ${ImageMagickpp_INCLUDE}")
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
    message( "    * libavcodec                  ${AVCodec_LIBRARY}")
    message( "    * libavcodec includes         ${AVCodec_INCLUDE_DIR}")
    message( "    * libavformat                 ${AVFormat_LIBRARY}")
    message( "    * libavformat includes        ${AVFormat_INCLUDE_DIR}")
    message( "    * libswscale                  ${SWScale_LIBRARY}")
    message( "    * libswscale includes         ${SWScale_INCLUDE_DIR}")
else()
    message( "    * libavcodec/avformat         DISABLED")
endif()
if(WITH_FREETYPE2)
    message( "    * freetype2                   ${FreeType2_LIBRARY}")
    message( "    * freetype2 includes          ${FreeType2_INCLUDE_DIR}")
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
message( "  *** glibmm-2.4                  ${Glibmm_LIBRARIES}")
message( "  *** glibmm-2.4 includes         ${Glibmm_INCLUDE_DIRS}")
message( "  *** giomm                       ${GIOmm_LIBRARIES}")
# message( "  *** gobject-2.0                 ${GOBJECT_LIBRARY}")
# message( "  *** sigc-2.0                    ${SIGC_LIBRARY}")
# message( "  *** glib-2.0                    ${GLIB_LIBRARY}")
# message( "  *** giomm-2.4                   ${GIOMM_LIBRARY}")
message( "  *** libxml++-2.6                ${LIBXMLPP_LIBRARY}")
message( "  *** libxml++ includes           ${PC_LIBXMLPP_INCLUDE_DIRS}")
message( "  *** cairo                       ${CAIRO_LIBRARY}")
message( "  *** cairo includes              ${PC_CAIRO_INCLUDE_DIRS}")
message( "  *** cairo mm                    ${CAIROMM_LIBRARY}")
message( "  *** cairo mm includes           ${PC_CAIROMM_INCLUDE_DIRS}")
message( "  *** pango-1.0                   ${PANGO_LIBRARY}")
message( "  *** pango includes              ${PC_PANGO_INCLUDE_DIRS}")
message( "  *** pangocairo                  ${PANGOCAIRO_LIBRARY}")
if(Boost_FOUND)
    message( "    * Boost Libraries             ${Boost_LIBRARIES}")
    message( "    * Boost Includes              ${Boost_INCLUDE_DIRS}")
else()
    message( "  *** Boost                       *NOT FOUND")
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
    message( "  *** Poco                        *NOT FOUND")
endif()
if(Glibmm_FOUND)
    message( "    * gtkmm                       ${GTKmm_LIBRARY}")
    message( "    * gtkmm includes              ${GTKmm_INCLUDE_DIR}")
else()
    message( "  *** gtkmm                       *NOT FOUND")
endif()
