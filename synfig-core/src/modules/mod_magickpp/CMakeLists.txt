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

add_library(mod_magickpp SHARED main.cpp trgt_magickpp.cpp)
target_link_libraries(mod_magickpp synfig)
target_link_libraries(mod_magickpp ${ImageMagickpp_LIBRARY})
target_link_libraries(mod_magickpp ${SYNFIG_CORE_REQUIRED_LIBRARIES})
install(TARGETS mod_magickpp DESTINATION lib/synfig/modules)
if(SYNFIG_MODULES_REMOVE_PREFIX)
    set_target_properties(mod_magickpp PROPERTIES PREFIX "")
endif()
if(SYNFIG_MODULES_COLLATE)
    set_target_properties(mod_magickpp PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR} RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
endif()
