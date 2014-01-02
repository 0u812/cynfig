

add_library(mod_example SHARED main.cpp simplecircle.cpp filledrect.cpp metaballs.cpp)
target_link_libraries(mod_example synfig)
target_link_libraries(mod_example ${SYNFIG_CORE_REQUIRED_LIBRARIES})
install(TARGETS mod_example DESTINATION lib/synfig/modules)
if(SYNFIG_MODULES_REMOVE_PREFIX)
    set_target_properties(mod_example PROPERTIES PREFIX "")
endif()
