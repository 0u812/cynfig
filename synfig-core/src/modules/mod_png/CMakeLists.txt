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

add_library(mod_png SHARED main.cpp trgt_png.cpp trgt_cairo_png.cpp mptr_png.cpp mptr_cairo_png.cpp)
target_link_libraries(mod_png synfig)
target_link_libraries(mod_png ${Png_LIBRARIES})
target_link_libraries(mod_png ${SYNFIG_CORE_REQUIRED_LIBRARIES})
install(TARGETS mod_png DESTINATION lib/synfig/modules)
if(SYNFIG_MODULES_REMOVE_PREFIX)
    set_target_properties(mod_png PROPERTIES PREFIX "")
endif()
if(SYNFIG_MODULES_COLLATE)
    set_target_properties(mod_png PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
endif()
