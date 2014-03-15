cmake_minimum_required (VERSION 2.8.9)
project(Synfig)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(SYNFIG_MAJOR "0")
set(SYNFIG_MINOR "65")
set(SYNFIG_PATCH "0")

if(WIN32)
    set(SYNFIG_WINDOWS_TARGET 1)
    set(SYNFIG_DEPENDENCY_PATH CACHE PATH "Path to Synfig dependencies")
    set(BOOST_ROOT CACHE PATH "Path to Boost installation")
else()
    set(SYNFIG_WINDOWS_TARGET 0)
endif()

if(SYNFIG_WINDOWS_TARGET)
    set(SYNFIG_MSVS_STAMP "-vc100")
    set(SYNFIG_HAVE_VASPRINTF 0)
    if(NOT SYNFIG_DEPENDENCY_PATH AND NOT BOOST_ROOT)
        message( FATAL_ERROR "Set SYNFIG_WINDOWS_TARGET to point to the dependencies and BOOST_ROOT to point to the location where Boost is installed resp.")
    endif()
    if(NOT SYNFIG_DEPENDENCY_PATH)
        message( FATAL_ERROR "Set SYNFIG_WINDOWS_TARGET to point to the dependencies")
    endif()
    if(NOT BOOST_ROOT)
        message( FATAL_ERROR "Set BOOST_ROOT to point to the location where Boost is installed")
    endif()
    if(MSVC)
        set(SYNFIG_MSVS_TARGET 1)
        set(SYNFIG_CAIRO_FALLBACK 1) # Cairo binaries outdated
        set(SYNFIG_GNU_EXTENSIONS 0)
        set(SYNFIG_HAVE_UNISTD_H 0)
        set(SYNFIG_ATTR_UNUSED "")
    else()
        set(SYNFIG_MSVS_TARGET 0)
        set(SYNFIG_CAIRO_FALLBACK 0) # Cairo binaries outdated
        set(SYNFIG_GNU_EXTENSIONS 1)
        set(SYNFIG_HAVE_UNISTD_H 1)
        set(SYNFIG_ATTR_UNUSED "\"SYNFIG_ATTR_UNUSED\"")
    endif()
else()
    set(SYNFIG_HAVE_VASPRINTF 1)
    set(SYNFIG_ATTR_UNUSED "\"__attribute__ ((unused))\"")
    add_definitions("-DSYNFIG_ATTR_UNUSED=__attribute__ ((unused))")
    set(SYNFIG_HAVE_UNISTD_H 1)
    set(SYNFIG_CAIRO_FALLBACK 0)
    set(SYNFIG_GNU_EXTENSIONS 1)
    set(SYNFIG_MSVS_TARGET 0)
endif()

if(NOT SYNFIG_WINDOWS_TARGET)
    find_package(PkgConfig)
endif()

set(SKIP_PLATFORM_TESTS 0 CACHE BOOL "Skip all tests that require compiling code (useful for cross-compiling)")

set(ENABLE_OPENEXR_HALF 0 CACHE BOOL "Use OpenEXR's \"half\" type for color")

set(SYNFIG_DATA_PATH ${CMAKE_INSTALL_PREFIX}/share)

set(SYNFIG_MODULES_DIR ${CMAKE_INSTALL_PREFIX}/etc)

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
        find_library(ZLIB_LIBRARY NAMES z zdll
            HINTS ${ZLIB_PATH} ${SYNFIG_DEPENDENCY_PATH}/zlib/lib)
        if(NOT ZLIB_LIBRARY)
            message( SEND_ERROR "Cannot find zlib. Set WITH_ZLIB to 0 to disable it." )
        endif()
        find_path(ZLIB_INCLUDE zlib.h
            HINTS ${ZLIB_PATH}/include ${SYNFIG_DEPENDENCY_PATH}/zlib/include)
        list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${ZLIB_INCLUDE})
    endif()

    # imagemagick
    # set(WITH_IMAGEMAGICK 1 CACHE BOOL "Use ImageMagick")
    # set(IMAGEMAGICK_PATH "" CACHE PATH "Path to ImageMagick")
    # if(WITH_IMAGEMAGICK)
        # # if the user specified to use imagemagick,
        # # try to find the "convert" executable
        # # Windows has a convert.exe in the System32 dir
        # find_program(MAGICK_CONVERT convert PATHS ${IMAGEMAGICK_PATH})
        # if(NOT MAGICK_CONVERT)
            # # FATAL_ERROR
            # message( SEND_ERROR "Cannot find ImageMagick. Set WITH_IMAGEMAGICK to 0 to disable it." )
        # endif()
    # endif()

    # Magick++
    set(WITH_MAGICKPP 0 CACHE BOOL "Use ImageMagick++")
    set(MAGICKPP_PATH "" CACHE PATH "Path to ImageMagick++")
    if(WITH_MAGICKPP)
        find_package(ImageMagick COMPONENTS Magick++ REQUIRED)
        if(NOT ImageMagick_Magick++_FOUND)
            message( SEND_ERROR "Cannot find ImageMagick/Magick++. Set WITH_MAGICKPP to 0 to disable it." )
        endif()
        list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${ImageMagick_Magick++_INCLUDE_DIR})
    endif()

    # ffmpeg
    # set(WITH_FFMPEG 1 CACHE BOOL "Use ffmpeg")
    # set(FFMPEG_PATH "" CACHE PATH "Path to ffmpeg")
    # if(WITH_FFMPEG)
        # find_program(FFMPEG_EXE ffmpeg PATHS ${FFMPEG_PATH})
        # if(NOT FFMPEG_EXE)
            # message( SEND_ERROR "Cannot find ffmpeg. Set WITH_FFMPEG to 0 to disable it." )
        # endif()
    # endif()

    # libdv
    if(NOT SYNFIG_WINDOWS_TARGET)
        set(LIBDV_PATH "" CACHE PATH "Path to libdv")
        find_package(LibDV)
        if(LIBDV_LIBRARY)
            set(WITH_LIBDV 1 CACHE BOOL "Use libdv")
            list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${LIBDV_INCLUDE})
        else()
            message( STATUS "Cannot find libdv. Some features will be disabled." )
        endif()
        set(WITH_LIBDV 0 CACHE BOOL "Use libdv")
    else()
        set(WITH_LIBDV 0 CACHE BOOL "Use libdv")
    endif()

    include(CheckIncludeFiles)

    # libavcodec and friends
    set(WITH_LIBAVCODEC 1 CACHE BOOL "Use libavcodec (included with ffmpeg)") # define
    if(SYNFIG_WINDOWS_TARGET)
        set(AVUTIL_PATH ${SYNFIG_DEPENDENCY_PATH}/ffmpeg CACHE PATH "Path to libavutil")
        set(AVCODEC_PATH ${SYNFIG_DEPENDENCY_PATH}/ffmpeg CACHE PATH "Path to libavcodec")
        set(AVFORMAT_PATH ${SYNFIG_DEPENDENCY_PATH}/ffmpeg CACHE PATH "Path to libavformat")
        set(SWSCALE_PATH ${SYNFIG_DEPENDENCY_PATH}/ffmpeg CACHE PATH "Path to libswscale")
    else()
        set(AVUTIL_PATH "" CACHE PATH "Path to libavutil")
        set(AVCODEC_PATH "" CACHE PATH "Path to libavcodec")
        set(AVFORMAT_PATH "" CACHE PATH "Path to libavformat")
    endif()
    if(WITH_LIBAVCODEC)
        find_package(AVCodec REQUIRED)
        find_package(AVFormat REQUIRED)
        find_package(SWScale REQUIRED)
        
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
        if(NOT SKIP_PLATFORM_TESTS AND NOT SYNFIG_WINDOWS_TARGET)
#             set(CMAKE_REQUIRED_INCLUDES ${AVFormat_INCLUDE_DIRS})
#             message(STATUS "AV format includes: ${AVFormat_INCLUDE_DIRS}")
            set(CMAKE_REQUIRED_FLAGS ${AVFormat_PKGCONF_CFLAGS})
            CHECK_INCLUDE_FILES("libavformat/avformat.h" AVFORMAT_HEADER_CHECK)
            if(NOT AVFORMAT_HEADER_CHECK)
                message( SEND_ERROR "Failed to properly compile a test for libavformat - configure the library properly, then wipe the build directory" )
            endif()
            foreach(include ${SWScale_INCLUDE_DIRS})
                set(SWSCALE_CFLAGS "${SWSCALE_CFLAGS} -I${include}")
            endforeach()
#             message(STATUS "SWScale flags ${SWSCALE_CFLAGS}")
            set(CMAKE_REQUIRED_FLAGS ${SWSCALE_CFLAGS})
            CHECK_INCLUDE_FILES(libswscale/swscale.h SWSCALE_HEADER_CHECK)
            if(NOT SWSCALE_HEADER_CHECK)
                message( SEND_ERROR "Failed to properly compile a test for swscale - configure the library properly, then wipe the build directory" )
            endif()
        endif()
    endif()

    # freetype2
    set(WITH_FREETYPE2 1 CACHE BOOL "Use freetype2")
    if(SYNFIG_WINDOWS_TARGET)
        set(FREETYPE2_PATH ${SYNFIG_DEPENDENCY_PATH}/freetype2 CACHE PATH "Path to freetype2")
    else()
        set(FREETYPE2_PATH "" CACHE PATH "Path to freetype2")
    endif()
    if(WITH_FREETYPE2)
        find_package(FreeType2 REQUIRED)
        if(NOT FreeType2_FOUND)
            message( SEND_ERROR "Cannot find freetype2. Set WITH_FREETYPE2 to 0 to disable it." )
        endif()
        list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${FreeType2_INCLUDE_DIR})
    endif()

    # fontconfig
    if(NOT SYNFIG_WINDOWS_TARGET)
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
    else()
        set(WITH_FONTCONFIG 0 CACHE BOOL "Use fontconfig")
    endif()

    # openexr
    set(OPENEXR_PATH "" CACHE PATH "Path to OpenEXR")
    find_package(OpenEXR)
    if(NOT OPENEXR_IMF_LIBRARY OR NOT OPENEXR_IMATH_LIBRARY OR NOT OPENEXR_HALF_LIBRARY OR 
    NOT OPENEXR_EX_LIBRARY OR NOT OPENEXR_EXMATH_LIBRARY OR NOT OPENEXR_THREAD_LIBRARY )
        message( STATUS "Cannot find OpenEXR. Some features will be disabled." )
        set(WITH_OPENEXR 0 CACHE BOOL "Use OpenEXR")
    else()
        set(WITH_OPENEXR 1 CACHE BOOL "Use OpenEXR")
        set(MOD_OPENEXR_CFG "mod_openexr")
        list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${OPENEXR_INCLUDE})
        list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${OPENEXR_DRM_INCLUDE})
    endif()
    
    # add HAVE_OPENEXR define to header\
    
    find_package(Glibmm REQUIRED)
    message("Glibmm_LIBRARIES = ${Glibmm_LIBRARIES}")
#     message(FATAL_ERROR "STOP")
    # need to use pkg-config's results for include dir directly
    # due to significant variability of paths
    list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${Glibmm_INCLUDE_DIRS})
    
    find_package(GIOmm REQUIRED)
    
    list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${GIOmm_INCLUDE_DIRS})

    # libxml++
    if(SYNFIG_WINDOWS_TARGET)
        set(LibXML++_PATH ${SYNFIG_DEPENDENCY_PATH}/gtkmm)
        # set(LibXML2_SKIP_HEADERS 1)
    endif()
    find_package(LibXML++ REQUIRED)
    list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${LibXML++_INCLUDE_DIRS})

    # cairomm
    find_package(Cairomm REQUIRED)
    list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${Cairomm_INCLUDE_DIRS})

    # Pango
    find_package(Pango REQUIRED)
    list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${Pango_INCLUDE_DIRS})
    
    # Pango-cairo
    find_package(PangoCairo REQUIRED)
    list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${PangoCairo_INCLUDE_DIRS})

    # Boost
    # http://stackoverflow.com/questions/6646405/how-do-you-add-boost-libraries-in-cmakelists-txt
    set(Boost_USE_STATIC_LIBS OFF)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)
    if(SYNFIG_MSVS_TARGET)
        set(BOOST_ALL_DYN_LINK ON CACHE BOOL "Use shared libs for Boost")
        if(BOOST_ALL_DYN_LINK)
            add_definitions(-DBOOST_ALL_DYN_LINK)
        endif()
    endif()

    # if(SYNFIG_WINDOWS_TARGET)
        # set(BOOST_ROOT ${SYNFIG_DEPENDENCY_PATH}/boost CACHE PATH "Path to Boost installation")
    # endif()
    message(STATUS "BOOST_ROOT = ${BOOST_ROOT}")
    set(BOOST_VERSION "1.53" CACHE STRING "Which version of Boost to use")
    find_package(Boost ${BOOST_VERSION} REQUIRED COMPONENTS program_options filesystem system)
    message("Boost libs = ${Boost_LIBRARIES}")
    if(Boost_FOUND)
        list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${Boost_INCLUDE_DIRS})
    endif()
    if(SYNFIG_MSVS_TARGET)
        set(SYNFIG_BOOST_LIB_PATH ${Boost_LIBRARY_DIR})
    endif()

    # PNG
    set(WITH_PNG 1 CACHE BOOL "Use libpng")
    if(SYNFIG_WINDOWS_TARGET)
        set(PNG_PATH ${SYNFIG_DEPENDENCY_PATH}/png CACHE PATH "Path to libpng")
    else()
        set(PNG_PATH "" CACHE PATH "Path to libpng")
    endif()
    if(WITH_PNG)
        find_package(Png REQUIRED)
        if(NOT Png_FOUND)
            message( SEND_ERROR "Cannot find libpng. Set WITH_PNG to 0 to disable it." )
        endif()
        list(APPEND SYNFIG_CORE_INCLUDE_PATHS ${Png_INCLUDE_DIRS})
        
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
    if(SYNFIG_WINDOWS_TARGET)
        set(POCO_PATH ${SYNFIG_DEPENDENCY_PATH}/poco CACHE PATH "Path to Poco")
    else()
        set(POCO_PATH "" CACHE PATH "Path to Poco") 
    endif()
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
        ${LibXML++_LIBRARIES}
        ${Cairomm_LIBRARIES}
        ${Pango_LIBRARIES}
        ${PangoCairo_LIBRARIES}
        ${POCO_FOUNDATION_LIBRARY}
        ${Boost_LIBRARIES})
    if(SYNFIG_MSVS_TARGET OR CYGWIN)
        list(APPEND SYNFIG_CORE_REQUIRED_LIBRARIES ${ZLIB_LIBRARY})
    endif()
else()
    set(ENABLE_SYNFIG_STUDIO 0 CACHE BOOL "Enable Synfig Studio")
endif(ENABLE_SYNFIG_CORE)

set(ENABLE_SYNFIG_STUDIO 1 CACHE BOOL "Enable Synfig Studio")
if(ENABLE_SYNFIG_STUDIO)
    if(NOT ENABLE_SYNFIG_CORE)
        message( FATAL_ERROR "Must enable Synfig Core in order to enable Synfig Studio")
    endif()
    set(SYNFIG_STUDIO_INCLUDE_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/synfig-core/src)
    list(APPEND SYNFIG_STUDIO_INCLUDE_PATHS ${LibXML++_INCLUDE_DIRS})
    # gtkmm
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
      Data directory            ${SYNFIG_DATA_PATH}
      Modules directory         ${SYNFIG_MODULES_DIR}
    
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
if(WITH_MAGICKPP)
    message( "    * ImageMagick++               ${ImageMagick_Magick++_LIBRARY}")
    message( "    * ImageMagick++ includes      ${ImageMagick_Magick++_INCLUDE_DIR}")
else()
    message( "    * ImageMagick++               DISABLED")
endif()
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
    message( "    * fontconfig                  ${Fontconfig_LIBRARIES}")
    message( "    * fontconfig includes         ${Fontconfig_INCLUDE_DIRS}")
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
message( "  *** libxml++-2.6                ${LibXML++_LIBRARIES}")
message( "  *** libxml++ includes           ${LibXML++_INCLUDE_DIRS}")
# message( "  *** cairo                       ${CAIRO_LIBRARY}")
# message( "  *** cairo includes              ${PC_CAIRO_INCLUDE_DIRS}")
message( "  *** cairo mm                    ${Cairomm_LIBRARIES}")
message( "  *** cairo mm includes           ${Cairomm_INCLUDE_DIRS}")
message( "  *** pango-1.0                   ${Pango_LIBRARIES}")
message( "  *** pango includes              ${Pango_INCLUDE_DIRS}")
message( "  *** pangocairo                  ${PangoCairo_LIBRARIES}")
if(Boost_FOUND)
    message( "    * Boost Libraries             ${Boost_LIBRARIES}")
    message( "    * Boost Includes              ${Boost_INCLUDE_DIRS}")
    if(SYNFIG_MSVS_TARGET)
        message( "    * Boost Lib path              ${SYNFIG_BOOST_LIB_PATH}")
    endif()
else()
    message( "  *** Boost                       *NOT FOUND")
endif()
if(WITH_PNG)
    message( "    * libpng                      ${Png_LIBRARIES}")
    message( "    * libpng includes             ${Png_INCLUDE_DIRS}")
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
