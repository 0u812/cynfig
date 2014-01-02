

add_library(mod_particle SHARED random.cpp plant.cpp main.cpp)
target_link_libraries(mod_particle synfig)
target_link_libraries(mod_particle ${SYNFIG_CORE_REQUIRED_LIBRARIES})
install(TARGETS mod_particle DESTINATION lib/synfig/modules)
if(SYNFIG_MODULES_REMOVE_PREFIX)
    set_target_properties(mod_particle PROPERTIES PREFIX "")
endif()
