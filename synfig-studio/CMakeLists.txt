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

cmake_minimum_required (VERSION 2.8.9)
project(SynfigCore)

set(SYNFIG_STUDIO_MAJOR ${SYNFIG_MAJOR})
set(SYNFIG_STUDIO_MINOR ${SYNFIG_MINOR})
set(SYNFIG_STUDIO_PATCH ${SYNFIG_PATCH})
set(SYNFIG_STUDIO_VER "${SYNFIG_STUDIO_MAJOR}.${SYNFIG_STUDIO_MINOR}.${SYNFIG_STUDIO_PATCH}")

set(SYNFIG_STUDIO_PREFIX   ${CMAKE_INSTALL_PREFIX})
set(SYNFIG_STUDIO_BIN_PATH ${SYNFIG_STUDIO_PREFIX}/bin)
set(SYNFIG_STUDIO_LIB_PATH ${SYNFIG_STUDIO_PREFIX}/lib)
set(SYNFIG_STUDIO_INCLUDE_PATH ${SYNFIG_STUDIO_PREFIX}/include)
set(SYNFIG_STUDIO_DATA_PATH ${SYNFIG_DATA_PATH})
set(SYNFIG_STUDIO_IMAGE_PATH ${SYNFIG_STUDIO_DATA_PATH}/pixmaps/synfigstudio)
set(SYNFIG_STUDIO_IMAGE_EXT png)
set(SYNFIG_STUDIO_PLUGIN_PATH ${SYNFIG_STUDIO_DATA_PATH}/synfig/plugins)
set(SYNFIG_STUDIO_LOCALE_PATH ${SYNFIG_STUDIO_DATA_PATH}/locale)

include_directories(${SYNFIG_STUDIO_INCLUDE_PATHS})

add_subdirectory(src)