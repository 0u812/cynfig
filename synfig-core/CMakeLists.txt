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

set(SYNFIG_CORE_MAJOR ${SYNFIG_MAJOR})
set(SYNFIG_CORE_MINOR ${SYNFIG_MINOR})
set(SYNFIG_CORE_PATCH ${SYNFIG_PATCH})
set(SYNFIG_CORE_VER "${SYNFIG_CORE_MAJOR}.${SYNFIG_CORE_MINOR}.${SYNFIG_CORE_PATCH}")

set(SYNFIG_CORE_PREFIX   ${CMAKE_INSTALL_PREFIX})
set(SYNFIG_CORE_BIN_PATH ${SYNFIG_CORE_PREFIX}/bin)
set(SYNFIG_CORE_LIB_PATH ${SYNFIG_CORE_PREFIX}/lib)
set(SYNFIG_CORE_INCLUDE_PATH ${SYNFIG_CORE_PREFIX}/include)

configure_file(synfig.pc.in synfig.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/synfig.pc DESTINATION lib/pkgconfig)

include_directories(${SYNFIG_CORE_INCLUDE_PATHS})

add_subdirectory(src)