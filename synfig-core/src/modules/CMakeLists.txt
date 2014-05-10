# === S Y N F I G =========================================================
# **
# **  \legal
# **  Copyright (c) 2013-2014 J Kyle Medley
# **
# **  This package is free software; you can redistribute it and/or
# **  modify it under the terms of the GNU General Public License as
# **  published by the Free Software Foundation; either version 2 of
# **  the License, or (at your option) any later version.
# **
# **  This package is distributed in the hope that it will be useful,
# **  but WITHOUT ANY WARRANTY; without even the implied warranty of
# **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# **  General Public License for more details.
# **  \endlegal
# =========================================================================

set(SYNFIG_MODULES_REMOVE_PREFIX 0 CACHE BOOL "Remove lib prefix from loadable modules where applicable")
set(SYNFIG_MODULES_COLLATE 1) # Collect in top-level dir (so can generate images)


set(SYNFIG_MODULES  "mod_particle;mod_filter;mod_yuv420p;mod_gif;mod_gradient;mod_geometry;mod_noise;mod_bmp;mod_ppm;lyr_std;mod_svg;mod_example")

add_subdirectory(mod_particle)
add_subdirectory(mod_filter)
add_subdirectory(mod_yuv420p)
add_subdirectory(mod_gif)
add_subdirectory(mod_gradient)
add_subdirectory(mod_geometry)
add_subdirectory(mod_noise)
# if(WITH_LIBAVCODEC)
#     add_subdirectory(mod_libavcodec)
# endif()
# add_subdirectory(mod_jpeg)
if(WITH_OPENEXR)
    add_subdirectory(mod_openexr)
    list(APPEND SYNFIG_MODULES mod_openexr)
endif()
add_subdirectory(mod_bmp)
add_subdirectory(mod_ppm)
if(WITH_PNG)
    add_subdirectory(mod_png)
    list(APPEND SYNFIG_MODULES mod_png)
endif()
if(WITH_LIBDV)
    add_subdirectory(mod_dv)
    list(APPEND SYNFIG_MODULES mod_dv)
endif()

if(MAGICK_CONVERT)
    add_subdirectory(mod_imagemagick)
    list(APPEND SYNFIG_MODULES mod_imagemagick)
endif()

if(WITH_FFMPEG)
    add_subdirectory(mod_ffmpeg)
    list(APPEND SYNFIG_MODULES mod_ffmpeg)
endif()

if(WITH_FREETYPE2)
    add_subdirectory(lyr_freetype)
    list(APPEND SYNFIG_MODULES lyr_freetype)
endif()

add_subdirectory(lyr_std)

if(WITH_MNG)
    add_subdirectory(mod_mng)
    list(APPEND SYNFIG_MODULES mod_mng)
endif()

add_subdirectory(mod_svg)

if(WITH_MAGICKPP)
    add_subdirectory(mod_magickpp)
    list(APPEND SYNFIG_MODULES mod_magickpp)
endif()

add_subdirectory(mod_example)

set(SYNFIG_MODULES "${SYNFIG_MODULES}" PARENT_SCOPE)

# So the tool can generate the images/icons online
configure_file(synfig_modules.cfg ${PROJECT_BINARY_DIR}/synfig_modules.cfg COPYONLY)
# Actually install the modules config
install(FILES synfig_modules.cfg DESTINATION ${SYNFIG_MODULES_DIR})
