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

set(SYNFIG_LAYER_STD_SOURCES
    main.cpp
    timeloop.cpp
    warp.cpp
    xorpattern.cpp
    booleancurve.cpp
    bevel.cpp
    shade.cpp
    twirl.cpp
    stretch.cpp
    clamp.cpp
    supersample.cpp
    insideout.cpp
    julia.cpp
    rotate.cpp
    mandelbrot.cpp
    zoom.cpp
    import.cpp
    translate.cpp
    sphere_distort.cpp
    curvewarp.cpp
    stroboscope.cpp)

add_library(lyr_std SHARED ${SYNFIG_LAYER_STD_SOURCES})
target_link_libraries(lyr_std synfig)
target_link_libraries(lyr_std ${SYNFIG_CORE_REQUIRED_LIBRARIES})
install(TARGETS lyr_std DESTINATION lib/synfig/modules)
if(SYNFIG_MODULES_REMOVE_PREFIX)
    set_target_properties(lyr_std PROPERTIES PREFIX "")
endif()
if(SYNFIG_MODULES_COLLATE)
    set_target_properties(lyr_std PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR} RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
endif()
