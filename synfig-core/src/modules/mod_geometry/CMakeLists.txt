

add_library(mod_geometry SHARED rectangle.cpp star.cpp checkerboard.cpp circle.cpp region.cpp outline.cpp advanced_outline.cpp main.cpp)
target_link_libraries(mod_geometry synfig)
target_link_libraries(mod_geometry ${SYNFIG_CORE_REQUIRED_LIBRARIES})
install(TARGETS mod_geometry DESTINATION lib/synfig/modules)
if(SYNFIG_MODULES_REMOVE_PREFIX)
    set_target_properties(mod_geometry PROPERTIES PREFIX "")
endif()
