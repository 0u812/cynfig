
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
